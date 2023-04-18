################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/BSP/Src/74HC595.c \
../Middlewares/Third_Party/BSP/Src/AD5322.c \
../Middlewares/Third_Party/BSP/Src/AD7980.c \
../Middlewares/Third_Party/BSP/Src/AD9834.c \
../Middlewares/Third_Party/BSP/Src/ADS8681.c \
../Middlewares/Third_Party/BSP/Src/DAC8565.c \
../Middlewares/Third_Party/BSP/Src/DWT_Delay.c \
../Middlewares/Third_Party/BSP/Src/EE24.c \
../Middlewares/Third_Party/BSP/Src/EEPROM.c \
../Middlewares/Third_Party/BSP/Src/FGEN.c \
../Middlewares/Third_Party/BSP/Src/GPIO.c \
../Middlewares/Third_Party/BSP/Src/HDC1080.c \
../Middlewares/Third_Party/BSP/Src/LED.c \
../Middlewares/Third_Party/BSP/Src/MAX5127.c \
../Middlewares/Third_Party/BSP/Src/bsp.c \
../Middlewares/Third_Party/BSP/Src/scpi_def.c \
../Middlewares/Third_Party/BSP/Src/scpi_fetch.c \
../Middlewares/Third_Party/BSP/Src/scpi_measure.c \
../Middlewares/Third_Party/BSP/Src/scpi_sense.c \
../Middlewares/Third_Party/BSP/Src/scpi_server.c \
../Middlewares/Third_Party/BSP/Src/scpi_source.c \
../Middlewares/Third_Party/BSP/Src/scpi_system.c \
../Middlewares/Third_Party/BSP/Src/scpi_trigger.c 

OBJS += \
./Middlewares/Third_Party/BSP/Src/74HC595.o \
./Middlewares/Third_Party/BSP/Src/AD5322.o \
./Middlewares/Third_Party/BSP/Src/AD7980.o \
./Middlewares/Third_Party/BSP/Src/AD9834.o \
./Middlewares/Third_Party/BSP/Src/ADS8681.o \
./Middlewares/Third_Party/BSP/Src/DAC8565.o \
./Middlewares/Third_Party/BSP/Src/DWT_Delay.o \
./Middlewares/Third_Party/BSP/Src/EE24.o \
./Middlewares/Third_Party/BSP/Src/EEPROM.o \
./Middlewares/Third_Party/BSP/Src/FGEN.o \
./Middlewares/Third_Party/BSP/Src/GPIO.o \
./Middlewares/Third_Party/BSP/Src/HDC1080.o \
./Middlewares/Third_Party/BSP/Src/LED.o \
./Middlewares/Third_Party/BSP/Src/MAX5127.o \
./Middlewares/Third_Party/BSP/Src/bsp.o \
./Middlewares/Third_Party/BSP/Src/scpi_def.o \
./Middlewares/Third_Party/BSP/Src/scpi_fetch.o \
./Middlewares/Third_Party/BSP/Src/scpi_measure.o \
./Middlewares/Third_Party/BSP/Src/scpi_sense.o \
./Middlewares/Third_Party/BSP/Src/scpi_server.o \
./Middlewares/Third_Party/BSP/Src/scpi_source.o \
./Middlewares/Third_Party/BSP/Src/scpi_system.o \
./Middlewares/Third_Party/BSP/Src/scpi_trigger.o 

C_DEPS += \
./Middlewares/Third_Party/BSP/Src/74HC595.d \
./Middlewares/Third_Party/BSP/Src/AD5322.d \
./Middlewares/Third_Party/BSP/Src/AD7980.d \
./Middlewares/Third_Party/BSP/Src/AD9834.d \
./Middlewares/Third_Party/BSP/Src/ADS8681.d \
./Middlewares/Third_Party/BSP/Src/DAC8565.d \
./Middlewares/Third_Party/BSP/Src/DWT_Delay.d \
./Middlewares/Third_Party/BSP/Src/EE24.d \
./Middlewares/Third_Party/BSP/Src/EEPROM.d \
./Middlewares/Third_Party/BSP/Src/FGEN.d \
./Middlewares/Third_Party/BSP/Src/GPIO.d \
./Middlewares/Third_Party/BSP/Src/HDC1080.d \
./Middlewares/Third_Party/BSP/Src/LED.d \
./Middlewares/Third_Party/BSP/Src/MAX5127.d \
./Middlewares/Third_Party/BSP/Src/bsp.d \
./Middlewares/Third_Party/BSP/Src/scpi_def.d \
./Middlewares/Third_Party/BSP/Src/scpi_fetch.d \
./Middlewares/Third_Party/BSP/Src/scpi_measure.d \
./Middlewares/Third_Party/BSP/Src/scpi_sense.d \
./Middlewares/Third_Party/BSP/Src/scpi_server.d \
./Middlewares/Third_Party/BSP/Src/scpi_source.d \
./Middlewares/Third_Party/BSP/Src/scpi_system.d \
./Middlewares/Third_Party/BSP/Src/scpi_trigger.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/BSP/Src/%.o Middlewares/Third_Party/BSP/Src/%.su Middlewares/Third_Party/BSP/Src/%.cyclo: ../Middlewares/Third_Party/BSP/Src/%.c Middlewares/Third_Party/BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/MCU/Middlewares/Third_Party/BSP/Inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/MCU/Middlewares/Third_Party/scpi-2.1/libscpi/inc" -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/MCU/Middlewares/Third_Party/scpi-2.1/libscpi/inc/scpi" -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-BSP-2f-Src

clean-Middlewares-2f-Third_Party-2f-BSP-2f-Src:
	-$(RM) ./Middlewares/Third_Party/BSP/Src/74HC595.cyclo ./Middlewares/Third_Party/BSP/Src/74HC595.d ./Middlewares/Third_Party/BSP/Src/74HC595.o ./Middlewares/Third_Party/BSP/Src/74HC595.su ./Middlewares/Third_Party/BSP/Src/AD5322.cyclo ./Middlewares/Third_Party/BSP/Src/AD5322.d ./Middlewares/Third_Party/BSP/Src/AD5322.o ./Middlewares/Third_Party/BSP/Src/AD5322.su ./Middlewares/Third_Party/BSP/Src/AD7980.cyclo ./Middlewares/Third_Party/BSP/Src/AD7980.d ./Middlewares/Third_Party/BSP/Src/AD7980.o ./Middlewares/Third_Party/BSP/Src/AD7980.su ./Middlewares/Third_Party/BSP/Src/AD9834.cyclo ./Middlewares/Third_Party/BSP/Src/AD9834.d ./Middlewares/Third_Party/BSP/Src/AD9834.o ./Middlewares/Third_Party/BSP/Src/AD9834.su ./Middlewares/Third_Party/BSP/Src/ADS8681.cyclo ./Middlewares/Third_Party/BSP/Src/ADS8681.d ./Middlewares/Third_Party/BSP/Src/ADS8681.o ./Middlewares/Third_Party/BSP/Src/ADS8681.su ./Middlewares/Third_Party/BSP/Src/DAC8565.cyclo ./Middlewares/Third_Party/BSP/Src/DAC8565.d ./Middlewares/Third_Party/BSP/Src/DAC8565.o ./Middlewares/Third_Party/BSP/Src/DAC8565.su ./Middlewares/Third_Party/BSP/Src/DWT_Delay.cyclo ./Middlewares/Third_Party/BSP/Src/DWT_Delay.d ./Middlewares/Third_Party/BSP/Src/DWT_Delay.o ./Middlewares/Third_Party/BSP/Src/DWT_Delay.su ./Middlewares/Third_Party/BSP/Src/EE24.cyclo ./Middlewares/Third_Party/BSP/Src/EE24.d ./Middlewares/Third_Party/BSP/Src/EE24.o ./Middlewares/Third_Party/BSP/Src/EE24.su ./Middlewares/Third_Party/BSP/Src/EEPROM.cyclo ./Middlewares/Third_Party/BSP/Src/EEPROM.d ./Middlewares/Third_Party/BSP/Src/EEPROM.o ./Middlewares/Third_Party/BSP/Src/EEPROM.su ./Middlewares/Third_Party/BSP/Src/FGEN.cyclo ./Middlewares/Third_Party/BSP/Src/FGEN.d ./Middlewares/Third_Party/BSP/Src/FGEN.o ./Middlewares/Third_Party/BSP/Src/FGEN.su ./Middlewares/Third_Party/BSP/Src/GPIO.cyclo ./Middlewares/Third_Party/BSP/Src/GPIO.d ./Middlewares/Third_Party/BSP/Src/GPIO.o ./Middlewares/Third_Party/BSP/Src/GPIO.su ./Middlewares/Third_Party/BSP/Src/HDC1080.cyclo ./Middlewares/Third_Party/BSP/Src/HDC1080.d ./Middlewares/Third_Party/BSP/Src/HDC1080.o ./Middlewares/Third_Party/BSP/Src/HDC1080.su ./Middlewares/Third_Party/BSP/Src/LED.cyclo ./Middlewares/Third_Party/BSP/Src/LED.d ./Middlewares/Third_Party/BSP/Src/LED.o ./Middlewares/Third_Party/BSP/Src/LED.su ./Middlewares/Third_Party/BSP/Src/MAX5127.cyclo ./Middlewares/Third_Party/BSP/Src/MAX5127.d ./Middlewares/Third_Party/BSP/Src/MAX5127.o ./Middlewares/Third_Party/BSP/Src/MAX5127.su ./Middlewares/Third_Party/BSP/Src/bsp.cyclo ./Middlewares/Third_Party/BSP/Src/bsp.d ./Middlewares/Third_Party/BSP/Src/bsp.o ./Middlewares/Third_Party/BSP/Src/bsp.su ./Middlewares/Third_Party/BSP/Src/scpi_def.cyclo ./Middlewares/Third_Party/BSP/Src/scpi_def.d ./Middlewares/Third_Party/BSP/Src/scpi_def.o ./Middlewares/Third_Party/BSP/Src/scpi_def.su ./Middlewares/Third_Party/BSP/Src/scpi_fetch.cyclo ./Middlewares/Third_Party/BSP/Src/scpi_fetch.d ./Middlewares/Third_Party/BSP/Src/scpi_fetch.o ./Middlewares/Third_Party/BSP/Src/scpi_fetch.su ./Middlewares/Third_Party/BSP/Src/scpi_measure.cyclo ./Middlewares/Third_Party/BSP/Src/scpi_measure.d ./Middlewares/Third_Party/BSP/Src/scpi_measure.o ./Middlewares/Third_Party/BSP/Src/scpi_measure.su ./Middlewares/Third_Party/BSP/Src/scpi_sense.cyclo ./Middlewares/Third_Party/BSP/Src/scpi_sense.d ./Middlewares/Third_Party/BSP/Src/scpi_sense.o ./Middlewares/Third_Party/BSP/Src/scpi_sense.su ./Middlewares/Third_Party/BSP/Src/scpi_server.cyclo ./Middlewares/Third_Party/BSP/Src/scpi_server.d ./Middlewares/Third_Party/BSP/Src/scpi_server.o ./Middlewares/Third_Party/BSP/Src/scpi_server.su ./Middlewares/Third_Party/BSP/Src/scpi_source.cyclo ./Middlewares/Third_Party/BSP/Src/scpi_source.d ./Middlewares/Third_Party/BSP/Src/scpi_source.o ./Middlewares/Third_Party/BSP/Src/scpi_source.su ./Middlewares/Third_Party/BSP/Src/scpi_system.cyclo ./Middlewares/Third_Party/BSP/Src/scpi_system.d ./Middlewares/Third_Party/BSP/Src/scpi_system.o ./Middlewares/Third_Party/BSP/Src/scpi_system.su ./Middlewares/Third_Party/BSP/Src/scpi_trigger.cyclo ./Middlewares/Third_Party/BSP/Src/scpi_trigger.d ./Middlewares/Third_Party/BSP/Src/scpi_trigger.o ./Middlewares/Third_Party/BSP/Src/scpi_trigger.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-BSP-2f-Src

