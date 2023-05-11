################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/nx_stm32_phy_driver.c 

OBJS += \
./Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/nx_stm32_phy_driver.o 

C_DEPS += \
./Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/nx_stm32_phy_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/%.o Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/%.su Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/%.cyclo: ../Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/%.c Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DTX_INCLUDE_USER_DEFINE_FILE -DNX_INCLUDE_USER_DEFINE_FILE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_ThreadX/Core/scpi-2.1/libscpi/inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../AZURE_RTOS/App -I../NetXDuo/App -I../NetXDuo/Target -I../Middlewares/ST/netxduo/common/drivers/ethernet/ -I../Middlewares/ST/netxduo/addons/sntp/ -I../Middlewares/ST/netxduo/addons/auto_ip/ -I../Middlewares/ST/netxduo/common/inc/ -I../Middlewares/ST/netxduo/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/netxduo/addons/ppp/ -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/threadx/utility/low_power/ -I../Drivers/BSP/Components/lan8742/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-netxduo-2f-common-2f-drivers-2f-ethernet-2f-lan8742

clean-Middlewares-2f-ST-2f-netxduo-2f-common-2f-drivers-2f-ethernet-2f-lan8742:
	-$(RM) ./Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/nx_stm32_phy_driver.cyclo ./Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/nx_stm32_phy_driver.d ./Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/nx_stm32_phy_driver.o ./Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/nx_stm32_phy_driver.su

.PHONY: clean-Middlewares-2f-ST-2f-netxduo-2f-common-2f-drivers-2f-ethernet-2f-lan8742

