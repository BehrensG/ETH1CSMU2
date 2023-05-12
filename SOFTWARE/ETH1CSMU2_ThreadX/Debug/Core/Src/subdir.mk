################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Src/tx_initialize_low_level.s 

C_SRCS += \
../Core/Src/74HC595.c \
../Core/Src/AD5322.c \
../Core/Src/AD7980.c \
../Core/Src/AD9834.c \
../Core/Src/ADS8681.c \
../Core/Src/BSP.c \
../Core/Src/DAC8565.c \
../Core/Src/DWT_Delay.c \
../Core/Src/EE24.c \
../Core/Src/EEPROM.c \
../Core/Src/FGEN.c \
../Core/Src/GPIO.c \
../Core/Src/HDC1080.c \
../Core/Src/MAX5127.c \
../Core/Src/app_threadx.c \
../Core/Src/main.c \
../Core/Src/scpi_def.c \
../Core/Src/scpi_fetch.c \
../Core/Src/scpi_measure.c \
../Core/Src/scpi_sense.c \
../Core/Src/scpi_server.c \
../Core/Src/scpi_source.c \
../Core/Src/scpi_system.c \
../Core/Src/scpi_trigger.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_hal_timebase_tim.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c 

OBJS += \
./Core/Src/74HC595.o \
./Core/Src/AD5322.o \
./Core/Src/AD7980.o \
./Core/Src/AD9834.o \
./Core/Src/ADS8681.o \
./Core/Src/BSP.o \
./Core/Src/DAC8565.o \
./Core/Src/DWT_Delay.o \
./Core/Src/EE24.o \
./Core/Src/EEPROM.o \
./Core/Src/FGEN.o \
./Core/Src/GPIO.o \
./Core/Src/HDC1080.o \
./Core/Src/MAX5127.o \
./Core/Src/app_threadx.o \
./Core/Src/main.o \
./Core/Src/scpi_def.o \
./Core/Src/scpi_fetch.o \
./Core/Src/scpi_measure.o \
./Core/Src/scpi_sense.o \
./Core/Src/scpi_server.o \
./Core/Src/scpi_source.o \
./Core/Src/scpi_system.o \
./Core/Src/scpi_trigger.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_hal_timebase_tim.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o \
./Core/Src/tx_initialize_low_level.o 

S_DEPS += \
./Core/Src/tx_initialize_low_level.d 

C_DEPS += \
./Core/Src/74HC595.d \
./Core/Src/AD5322.d \
./Core/Src/AD7980.d \
./Core/Src/AD9834.d \
./Core/Src/ADS8681.d \
./Core/Src/BSP.d \
./Core/Src/DAC8565.d \
./Core/Src/DWT_Delay.d \
./Core/Src/EE24.d \
./Core/Src/EEPROM.d \
./Core/Src/FGEN.d \
./Core/Src/GPIO.d \
./Core/Src/HDC1080.d \
./Core/Src/MAX5127.d \
./Core/Src/app_threadx.d \
./Core/Src/main.d \
./Core/Src/scpi_def.d \
./Core/Src/scpi_fetch.d \
./Core/Src/scpi_measure.d \
./Core/Src/scpi_sense.d \
./Core/Src/scpi_server.d \
./Core/Src/scpi_source.d \
./Core/Src/scpi_system.d \
./Core/Src/scpi_trigger.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_hal_timebase_tim.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DTX_INCLUDE_USER_DEFINE_FILE -DNX_INCLUDE_USER_DEFINE_FILE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_ThreadX/Core/scpi-2.1/libscpi/inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../AZURE_RTOS/App -I../NetXDuo/App -I../NetXDuo/Target -I../Middlewares/ST/netxduo/common/drivers/ethernet/ -I../Middlewares/ST/netxduo/addons/sntp/ -I../Middlewares/ST/netxduo/addons/auto_ip/ -I../Middlewares/ST/netxduo/common/inc/ -I../Middlewares/ST/netxduo/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/netxduo/addons/ppp/ -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/threadx/utility/low_power/ -I../Drivers/BSP/Components/lan8742/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o: ../Core/Src/%.s Core/Src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/74HC595.cyclo ./Core/Src/74HC595.d ./Core/Src/74HC595.o ./Core/Src/74HC595.su ./Core/Src/AD5322.cyclo ./Core/Src/AD5322.d ./Core/Src/AD5322.o ./Core/Src/AD5322.su ./Core/Src/AD7980.cyclo ./Core/Src/AD7980.d ./Core/Src/AD7980.o ./Core/Src/AD7980.su ./Core/Src/AD9834.cyclo ./Core/Src/AD9834.d ./Core/Src/AD9834.o ./Core/Src/AD9834.su ./Core/Src/ADS8681.cyclo ./Core/Src/ADS8681.d ./Core/Src/ADS8681.o ./Core/Src/ADS8681.su ./Core/Src/BSP.cyclo ./Core/Src/BSP.d ./Core/Src/BSP.o ./Core/Src/BSP.su ./Core/Src/DAC8565.cyclo ./Core/Src/DAC8565.d ./Core/Src/DAC8565.o ./Core/Src/DAC8565.su ./Core/Src/DWT_Delay.cyclo ./Core/Src/DWT_Delay.d ./Core/Src/DWT_Delay.o ./Core/Src/DWT_Delay.su ./Core/Src/EE24.cyclo ./Core/Src/EE24.d ./Core/Src/EE24.o ./Core/Src/EE24.su ./Core/Src/EEPROM.cyclo ./Core/Src/EEPROM.d ./Core/Src/EEPROM.o ./Core/Src/EEPROM.su ./Core/Src/FGEN.cyclo ./Core/Src/FGEN.d ./Core/Src/FGEN.o ./Core/Src/FGEN.su ./Core/Src/GPIO.cyclo ./Core/Src/GPIO.d ./Core/Src/GPIO.o ./Core/Src/GPIO.su ./Core/Src/HDC1080.cyclo ./Core/Src/HDC1080.d ./Core/Src/HDC1080.o ./Core/Src/HDC1080.su ./Core/Src/MAX5127.cyclo ./Core/Src/MAX5127.d ./Core/Src/MAX5127.o ./Core/Src/MAX5127.su ./Core/Src/app_threadx.cyclo ./Core/Src/app_threadx.d ./Core/Src/app_threadx.o ./Core/Src/app_threadx.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/scpi_def.cyclo ./Core/Src/scpi_def.d ./Core/Src/scpi_def.o ./Core/Src/scpi_def.su ./Core/Src/scpi_fetch.cyclo ./Core/Src/scpi_fetch.d ./Core/Src/scpi_fetch.o ./Core/Src/scpi_fetch.su ./Core/Src/scpi_measure.cyclo ./Core/Src/scpi_measure.d ./Core/Src/scpi_measure.o ./Core/Src/scpi_measure.su ./Core/Src/scpi_sense.cyclo ./Core/Src/scpi_sense.d ./Core/Src/scpi_sense.o ./Core/Src/scpi_sense.su ./Core/Src/scpi_server.cyclo ./Core/Src/scpi_server.d ./Core/Src/scpi_server.o ./Core/Src/scpi_server.su ./Core/Src/scpi_source.cyclo ./Core/Src/scpi_source.d ./Core/Src/scpi_source.o ./Core/Src/scpi_source.su ./Core/Src/scpi_system.cyclo ./Core/Src/scpi_system.d ./Core/Src/scpi_system.o ./Core/Src/scpi_system.su ./Core/Src/scpi_trigger.cyclo ./Core/Src/scpi_trigger.d ./Core/Src/scpi_trigger.o ./Core/Src/scpi_trigger.su ./Core/Src/stm32f7xx_hal_msp.cyclo ./Core/Src/stm32f7xx_hal_msp.d ./Core/Src/stm32f7xx_hal_msp.o ./Core/Src/stm32f7xx_hal_msp.su ./Core/Src/stm32f7xx_hal_timebase_tim.cyclo ./Core/Src/stm32f7xx_hal_timebase_tim.d ./Core/Src/stm32f7xx_hal_timebase_tim.o ./Core/Src/stm32f7xx_hal_timebase_tim.su ./Core/Src/stm32f7xx_it.cyclo ./Core/Src/stm32f7xx_it.d ./Core/Src/stm32f7xx_it.o ./Core/Src/stm32f7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f7xx.cyclo ./Core/Src/system_stm32f7xx.d ./Core/Src/system_stm32f7xx.o ./Core/Src/system_stm32f7xx.su ./Core/Src/tx_initialize_low_level.d ./Core/Src/tx_initialize_low_level.o

.PHONY: clean-Core-2f-Src

