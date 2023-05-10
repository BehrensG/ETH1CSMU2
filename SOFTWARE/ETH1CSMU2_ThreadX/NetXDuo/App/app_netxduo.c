/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_netxduo.c
  * @author  MCD Application Team
  * @brief   NetXDuo applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_netxduo.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
NX_IP				nx_ipv4_instance;
NX_PACKET_POOL		nx_ipv4_packet_pool;
extern UCHAR*		tx_memory_ptr;
TX_THREAD			app_link_thread;
TX_QUEUE			link_queue;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static void app_link_thread_entry(ULONG thread_input);
/* USER CODE END PFP */
/**
  * @brief  Application NetXDuo Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT MX_NetXDuo_Init(VOID *memory_ptr)
{
  UINT ret = NX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN MX_NetXDuo_MEM_POOL */
  (void)byte_pool;
  /* USER CODE END MX_NetXDuo_MEM_POOL */

  /* USER CODE BEGIN MX_NetXDuo_Init */

  /* Allocate the memory for NX_PACKET_POOL instalce */
  if (tx_byte_allocate(byte_pool, (VOID **) &tx_memory_ptr, NX_PACKET_POOL_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return TX_POOL_ERROR;
  }

  ret = nx_packet_pool_create(&nx_ipv4_packet_pool, "Main Packet Pool", PAYLOAD_SIZE, tx_memory_ptr, NX_PACKET_POOL_SIZE);

  if (ret != NX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return NX_NOT_ENABLED;
  }

  /* Allocate the memory for  nx_ip_create */
  if (tx_byte_allocate(byte_pool, (VOID **) &tx_memory_ptr, 2*DEFAULT_MEMORY_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return TX_POOL_ERROR;
  }

  /* Create the main NX_IP instance */
  ret = nx_ip_create(&nx_ipv4_instance,
		  	  	  	 "IPv4 Instance",
					 IP_ADDRESS(192,168,1,123),
					 IP_ADDRESS(255,255,255,0),
					 &nx_ipv4_packet_pool,
					 nx_stm32_eth_driver,
					 tx_memory_ptr,
					 DEFAULT_MEMORY_SIZE,
					 1);

  if (ret != NX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return NX_NOT_ENABLED;
  }

  /* Allocate the memory for ARP */
  if (tx_byte_allocate(byte_pool, (VOID **) &tx_memory_ptr, ARP_MEMORY_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return TX_POOL_ERROR;
  }

  /*  Enable the ARP protocol and provide the ARP cache size for the IP instance */
  ret = nx_arp_enable(&nx_ipv4_instance, (VOID *)tx_memory_ptr, ARP_MEMORY_SIZE);
  if (ret != NX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return NX_NOT_ENABLED;
  }

  /* Enable the ICMP */
  ret = nx_icmp_enable(&nx_ipv4_instance);
  if (ret != NX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return NX_NOT_ENABLED;
  }

  ret = nx_tcp_enable(&nx_ipv4_instance);
  if (ret != NX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return NX_NOT_ENABLED;
  }

  if (tx_byte_allocate(byte_pool, (VOID **) &tx_memory_ptr, DEFAULT_MEMORY_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return TX_POOL_ERROR;
  }

  /* create the Link thread */
  ret = tx_thread_create(&app_link_thread, "App link thread", app_link_thread_entry, 0, tx_memory_ptr, DEFAULT_MEMORY_SIZE,
                         11, 11, TX_NO_TIME_SLICE, TX_AUTO_START);

  if (ret != TX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return TX_NOT_DONE;
  }

  if (tx_byte_allocate(byte_pool, (VOID **) &tx_memory_ptr, 4, TX_NO_WAIT) != TX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return TX_POOL_ERROR;
  }

  ret = tx_queue_create(&link_queue, "link queue", TX_1_ULONG,tx_memory_ptr, 4);

  if (ret != TX_SUCCESS)
  {
	  LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);
	  return TX_NOT_DONE;
  }

  /* USER CODE END MX_NetXDuo_Init */

  return ret;
}

/* USER CODE BEGIN 1 */
static void app_link_thread_entry(ULONG thread_input)
{
  ULONG actual_status;
  UINT linkdown = 0, ret, queue_msg;

  nx_ip_driver_direct_command(&nx_ipv4_instance, NX_LINK_ENABLE, &actual_status);

  while(1)
  {

	  ret = nx_ip_interface_status_check(&nx_ipv4_instance, 0, NX_IP_LINK_ENABLED, &actual_status, 10);

    if(ret == NX_SUCCESS)
    {
      queue_msg = LINK_UP;

      if(1 == linkdown)
      {
        linkdown = 0;

        ret = nx_ip_interface_status_check(&nx_ipv4_instance, 0, NX_IP_ADDRESS_RESOLVED, &actual_status, 10);
        if(ret == NX_SUCCESS)
        {

        	queue_msg = LINK_UP;
        }
        else
        {
        	nx_ip_driver_direct_command(&nx_ipv4_instance, NX_LINK_ENABLE, &actual_status);
        	queue_msg = LINK_DOWN;
        }
      }
    }
    else
    {
      if(0 == linkdown)
      {
        linkdown = 1;
        /* The network cable is not connected. */
        queue_msg = LINK_DOWN;
      }
    }
    ret = tx_queue_send(&link_queue, &queue_msg, TX_NO_WAIT);
    tx_thread_sleep(500);
  }
}

/* USER CODE END 1 */
