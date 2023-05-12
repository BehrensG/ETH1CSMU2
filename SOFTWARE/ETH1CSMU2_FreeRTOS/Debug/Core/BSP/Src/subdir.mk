################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/BSP/Src/74HC595.c \
../Core/BSP/Src/AD5322.c \
../Core/BSP/Src/AD7980.c \
../Core/BSP/Src/AD9834.c \
../Core/BSP/Src/ADS8681.c \
../Core/BSP/Src/DAC8565.c \
../Core/BSP/Src/DWT_Delay.c \
../Core/BSP/Src/EE24.c \
../Core/BSP/Src/EEPROM.c \
../Core/BSP/Src/FGEN.c \
../Core/BSP/Src/GPIO.c \
../Core/BSP/Src/HDC1080.c \
../Core/BSP/Src/LED.c \
../Core/BSP/Src/MAX5127.c \
../Core/BSP/Src/SCPI_Def.c \
../Core/BSP/Src/SCPI_Fetch.c \
../Core/BSP/Src/SCPI_Measure.c \
../Core/BSP/Src/SCPI_Sense.c \
../Core/BSP/Src/SCPI_Server.c \
../Core/BSP/Src/SCPI_Source.c \
../Core/BSP/Src/SCPI_System.c \
../Core/BSP/Src/SCPI_Trigger.c \
../Core/BSP/Src/TCP_Package.c \
../Core/BSP/Src/bsp.c 

OBJS += \
./Core/BSP/Src/74HC595.o \
./Core/BSP/Src/AD5322.o \
./Core/BSP/Src/AD7980.o \
./Core/BSP/Src/AD9834.o \
./Core/BSP/Src/ADS8681.o \
./Core/BSP/Src/DAC8565.o \
./Core/BSP/Src/DWT_Delay.o \
./Core/BSP/Src/EE24.o \
./Core/BSP/Src/EEPROM.o \
./Core/BSP/Src/FGEN.o \
./Core/BSP/Src/GPIO.o \
./Core/BSP/Src/HDC1080.o \
./Core/BSP/Src/LED.o \
./Core/BSP/Src/MAX5127.o \
./Core/BSP/Src/SCPI_Def.o \
./Core/BSP/Src/SCPI_Fetch.o \
./Core/BSP/Src/SCPI_Measure.o \
./Core/BSP/Src/SCPI_Sense.o \
./Core/BSP/Src/SCPI_Server.o \
./Core/BSP/Src/SCPI_Source.o \
./Core/BSP/Src/SCPI_System.o \
./Core/BSP/Src/SCPI_Trigger.o \
./Core/BSP/Src/TCP_Package.o \
./Core/BSP/Src/bsp.o 

C_DEPS += \
./Core/BSP/Src/74HC595.d \
./Core/BSP/Src/AD5322.d \
./Core/BSP/Src/AD7980.d \
./Core/BSP/Src/AD9834.d \
./Core/BSP/Src/ADS8681.d \
./Core/BSP/Src/DAC8565.d \
./Core/BSP/Src/DWT_Delay.d \
./Core/BSP/Src/EE24.d \
./Core/BSP/Src/EEPROM.d \
./Core/BSP/Src/FGEN.d \
./Core/BSP/Src/GPIO.d \
./Core/BSP/Src/HDC1080.d \
./Core/BSP/Src/LED.d \
./Core/BSP/Src/MAX5127.d \
./Core/BSP/Src/SCPI_Def.d \
./Core/BSP/Src/SCPI_Fetch.d \
./Core/BSP/Src/SCPI_Measure.d \
./Core/BSP/Src/SCPI_Sense.d \
./Core/BSP/Src/SCPI_Server.d \
./Core/BSP/Src/SCPI_Source.d \
./Core/BSP/Src/SCPI_System.d \
./Core/BSP/Src/SCPI_Trigger.d \
./Core/BSP/Src/TCP_Package.d \
./Core/BSP/Src/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/BSP/Src/%.o Core/BSP/Src/%.su Core/BSP/Src/%.cyclo: ../Core/BSP/Src/%.c Core/BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_FreeRTOS/Core/BSP/Inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_FreeRTOS/Middlewares/Third_Party/scpi-2.1/libscpi/inc" -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_FreeRTOS/Middlewares/Third_Party/scpi-2.1/libscpi/inc/scpi" -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-BSP-2f-Src

clean-Core-2f-BSP-2f-Src:
	-$(RM) ./Core/BSP/Src/74HC595.cyclo ./Core/BSP/Src/74HC595.d ./Core/BSP/Src/74HC595.o ./Core/BSP/Src/74HC595.su ./Core/BSP/Src/AD5322.cyclo ./Core/BSP/Src/AD5322.d ./Core/BSP/Src/AD5322.o ./Core/BSP/Src/AD5322.su ./Core/BSP/Src/AD7980.cyclo ./Core/BSP/Src/AD7980.d ./Core/BSP/Src/AD7980.o ./Core/BSP/Src/AD7980.su ./Core/BSP/Src/AD9834.cyclo ./Core/BSP/Src/AD9834.d ./Core/BSP/Src/AD9834.o ./Core/BSP/Src/AD9834.su ./Core/BSP/Src/ADS8681.cyclo ./Core/BSP/Src/ADS8681.d ./Core/BSP/Src/ADS8681.o ./Core/BSP/Src/ADS8681.su ./Core/BSP/Src/DAC8565.cyclo ./Core/BSP/Src/DAC8565.d ./Core/BSP/Src/DAC8565.o ./Core/BSP/Src/DAC8565.su ./Core/BSP/Src/DWT_Delay.cyclo ./Core/BSP/Src/DWT_Delay.d ./Core/BSP/Src/DWT_Delay.o ./Core/BSP/Src/DWT_Delay.su ./Core/BSP/Src/EE24.cyclo ./Core/BSP/Src/EE24.d ./Core/BSP/Src/EE24.o ./Core/BSP/Src/EE24.su ./Core/BSP/Src/EEPROM.cyclo ./Core/BSP/Src/EEPROM.d ./Core/BSP/Src/EEPROM.o ./Core/BSP/Src/EEPROM.su ./Core/BSP/Src/FGEN.cyclo ./Core/BSP/Src/FGEN.d ./Core/BSP/Src/FGEN.o ./Core/BSP/Src/FGEN.su ./Core/BSP/Src/GPIO.cyclo ./Core/BSP/Src/GPIO.d ./Core/BSP/Src/GPIO.o ./Core/BSP/Src/GPIO.su ./Core/BSP/Src/HDC1080.cyclo ./Core/BSP/Src/HDC1080.d ./Core/BSP/Src/HDC1080.o ./Core/BSP/Src/HDC1080.su ./Core/BSP/Src/LED.cyclo ./Core/BSP/Src/LED.d ./Core/BSP/Src/LED.o ./Core/BSP/Src/LED.su ./Core/BSP/Src/MAX5127.cyclo ./Core/BSP/Src/MAX5127.d ./Core/BSP/Src/MAX5127.o ./Core/BSP/Src/MAX5127.su ./Core/BSP/Src/SCPI_Def.cyclo ./Core/BSP/Src/SCPI_Def.d ./Core/BSP/Src/SCPI_Def.o ./Core/BSP/Src/SCPI_Def.su ./Core/BSP/Src/SCPI_Fetch.cyclo ./Core/BSP/Src/SCPI_Fetch.d ./Core/BSP/Src/SCPI_Fetch.o ./Core/BSP/Src/SCPI_Fetch.su ./Core/BSP/Src/SCPI_Measure.cyclo ./Core/BSP/Src/SCPI_Measure.d ./Core/BSP/Src/SCPI_Measure.o ./Core/BSP/Src/SCPI_Measure.su ./Core/BSP/Src/SCPI_Sense.cyclo ./Core/BSP/Src/SCPI_Sense.d ./Core/BSP/Src/SCPI_Sense.o ./Core/BSP/Src/SCPI_Sense.su ./Core/BSP/Src/SCPI_Server.cyclo ./Core/BSP/Src/SCPI_Server.d ./Core/BSP/Src/SCPI_Server.o ./Core/BSP/Src/SCPI_Server.su ./Core/BSP/Src/SCPI_Source.cyclo ./Core/BSP/Src/SCPI_Source.d ./Core/BSP/Src/SCPI_Source.o ./Core/BSP/Src/SCPI_Source.su ./Core/BSP/Src/SCPI_System.cyclo ./Core/BSP/Src/SCPI_System.d ./Core/BSP/Src/SCPI_System.o ./Core/BSP/Src/SCPI_System.su ./Core/BSP/Src/SCPI_Trigger.cyclo ./Core/BSP/Src/SCPI_Trigger.d ./Core/BSP/Src/SCPI_Trigger.o ./Core/BSP/Src/SCPI_Trigger.su ./Core/BSP/Src/TCP_Package.cyclo ./Core/BSP/Src/TCP_Package.d ./Core/BSP/Src/TCP_Package.o ./Core/BSP/Src/TCP_Package.su ./Core/BSP/Src/bsp.cyclo ./Core/BSP/Src/bsp.d ./Core/BSP/Src/bsp.o ./Core/BSP/Src/bsp.su

.PHONY: clean-Core-2f-BSP-2f-Src

