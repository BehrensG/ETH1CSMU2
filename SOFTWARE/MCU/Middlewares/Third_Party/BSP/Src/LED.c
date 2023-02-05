/*
 * LED.c
 *
 *  Created on: Feb 5, 2023
 *      Author: grzegorz
 */


#include "cmsis_os2.h"
#include "LED.h"
#include "main.h"

extern osThreadId_t LEDTaskHandle;
extern osMessageQueueId_t QueueLEDHandle;


void LED_Switch(uint8_t LED_state)
{

	static uint8_t led_color_send;

	LL_GPIO_SetOutputPin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
	LL_GPIO_SetOutputPin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	LL_GPIO_SetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);

	switch(LED_state)
	{
		case LED_IDLE:
		{
			led_color_send = GREEN;
			osMessageQueuePut(QueueLEDHandle, &led_color_send, 0U, osWaitForever);

		}; break;

		case LED_ERROR:
		{
			led_color_send = RED;
			osMessageQueuePut(QueueLEDHandle, &led_color_send, 0U, osWaitForever);

		}; break;

		case LED_BUSY:
		{
			LL_GPIO_ResetOutputPin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);

		}; break;

		case LED_DEFUALT:
		{
			led_color_send = BLUE;
			osMessageQueuePut(QueueLEDHandle, &led_color_send, 0U, osWaitForever);

		}; break;

	}
}
