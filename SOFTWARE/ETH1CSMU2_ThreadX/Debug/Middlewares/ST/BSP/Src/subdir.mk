################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/BSP/Src/scpi_def.c \
../Middlewares/ST/BSP/Src/scpi_server.c 

OBJS += \
./Middlewares/ST/BSP/Src/scpi_def.o \
./Middlewares/ST/BSP/Src/scpi_server.o 

C_DEPS += \
./Middlewares/ST/BSP/Src/scpi_def.d \
./Middlewares/ST/BSP/Src/scpi_server.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/BSP/Src/%.o Middlewares/ST/BSP/Src/%.su Middlewares/ST/BSP/Src/%.cyclo: ../Middlewares/ST/BSP/Src/%.c Middlewares/ST/BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DTX_INCLUDE_USER_DEFINE_FILE -DNX_INCLUDE_USER_DEFINE_FILE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_ThreadX/Middlewares/ST/BSP/Inc" -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_ThreadX/Middlewares/ST/scpi-2.1/libscpi/inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../AZURE_RTOS/App -I../NetXDuo/App -I../NetXDuo/Target -I../Middlewares/ST/netxduo/common/drivers/ethernet/ -I../Middlewares/ST/netxduo/addons/sntp/ -I../Middlewares/ST/netxduo/addons/auto_ip/ -I../Middlewares/ST/netxduo/common/inc/ -I../Middlewares/ST/netxduo/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/netxduo/addons/ppp/ -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/threadx/utility/low_power/ -I../Drivers/BSP/Components/lan8742/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-BSP-2f-Src

clean-Middlewares-2f-ST-2f-BSP-2f-Src:
	-$(RM) ./Middlewares/ST/BSP/Src/scpi_def.cyclo ./Middlewares/ST/BSP/Src/scpi_def.d ./Middlewares/ST/BSP/Src/scpi_def.o ./Middlewares/ST/BSP/Src/scpi_def.su ./Middlewares/ST/BSP/Src/scpi_server.cyclo ./Middlewares/ST/BSP/Src/scpi_server.d ./Middlewares/ST/BSP/Src/scpi_server.o ./Middlewares/ST/BSP/Src/scpi_server.su

.PHONY: clean-Middlewares-2f-ST-2f-BSP-2f-Src

