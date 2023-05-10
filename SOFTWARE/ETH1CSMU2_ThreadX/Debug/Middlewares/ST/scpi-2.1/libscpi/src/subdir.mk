################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/scpi-2.1/libscpi/src/error.c \
../Middlewares/ST/scpi-2.1/libscpi/src/expression.c \
../Middlewares/ST/scpi-2.1/libscpi/src/fifo.c \
../Middlewares/ST/scpi-2.1/libscpi/src/ieee488.c \
../Middlewares/ST/scpi-2.1/libscpi/src/lexer.c \
../Middlewares/ST/scpi-2.1/libscpi/src/minimal.c \
../Middlewares/ST/scpi-2.1/libscpi/src/parser.c \
../Middlewares/ST/scpi-2.1/libscpi/src/units.c \
../Middlewares/ST/scpi-2.1/libscpi/src/utils.c 

OBJS += \
./Middlewares/ST/scpi-2.1/libscpi/src/error.o \
./Middlewares/ST/scpi-2.1/libscpi/src/expression.o \
./Middlewares/ST/scpi-2.1/libscpi/src/fifo.o \
./Middlewares/ST/scpi-2.1/libscpi/src/ieee488.o \
./Middlewares/ST/scpi-2.1/libscpi/src/lexer.o \
./Middlewares/ST/scpi-2.1/libscpi/src/minimal.o \
./Middlewares/ST/scpi-2.1/libscpi/src/parser.o \
./Middlewares/ST/scpi-2.1/libscpi/src/units.o \
./Middlewares/ST/scpi-2.1/libscpi/src/utils.o 

C_DEPS += \
./Middlewares/ST/scpi-2.1/libscpi/src/error.d \
./Middlewares/ST/scpi-2.1/libscpi/src/expression.d \
./Middlewares/ST/scpi-2.1/libscpi/src/fifo.d \
./Middlewares/ST/scpi-2.1/libscpi/src/ieee488.d \
./Middlewares/ST/scpi-2.1/libscpi/src/lexer.d \
./Middlewares/ST/scpi-2.1/libscpi/src/minimal.d \
./Middlewares/ST/scpi-2.1/libscpi/src/parser.d \
./Middlewares/ST/scpi-2.1/libscpi/src/units.d \
./Middlewares/ST/scpi-2.1/libscpi/src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/scpi-2.1/libscpi/src/%.o Middlewares/ST/scpi-2.1/libscpi/src/%.su Middlewares/ST/scpi-2.1/libscpi/src/%.cyclo: ../Middlewares/ST/scpi-2.1/libscpi/src/%.c Middlewares/ST/scpi-2.1/libscpi/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DTX_INCLUDE_USER_DEFINE_FILE -DNX_INCLUDE_USER_DEFINE_FILE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_ThreadX/Middlewares/ST/scpi-2.1/libscpi/inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../AZURE_RTOS/App -I../NetXDuo/App -I../NetXDuo/Target -I../Middlewares/ST/netxduo/common/drivers/ethernet/ -I../Middlewares/ST/netxduo/addons/sntp/ -I../Middlewares/ST/netxduo/addons/auto_ip/ -I../Middlewares/ST/netxduo/common/inc/ -I../Middlewares/ST/netxduo/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/netxduo/addons/ppp/ -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/threadx/utility/low_power/ -I../Drivers/BSP/Components/lan8742/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-scpi-2d-2-2e-1-2f-libscpi-2f-src

clean-Middlewares-2f-ST-2f-scpi-2d-2-2e-1-2f-libscpi-2f-src:
	-$(RM) ./Middlewares/ST/scpi-2.1/libscpi/src/error.cyclo ./Middlewares/ST/scpi-2.1/libscpi/src/error.d ./Middlewares/ST/scpi-2.1/libscpi/src/error.o ./Middlewares/ST/scpi-2.1/libscpi/src/error.su ./Middlewares/ST/scpi-2.1/libscpi/src/expression.cyclo ./Middlewares/ST/scpi-2.1/libscpi/src/expression.d ./Middlewares/ST/scpi-2.1/libscpi/src/expression.o ./Middlewares/ST/scpi-2.1/libscpi/src/expression.su ./Middlewares/ST/scpi-2.1/libscpi/src/fifo.cyclo ./Middlewares/ST/scpi-2.1/libscpi/src/fifo.d ./Middlewares/ST/scpi-2.1/libscpi/src/fifo.o ./Middlewares/ST/scpi-2.1/libscpi/src/fifo.su ./Middlewares/ST/scpi-2.1/libscpi/src/ieee488.cyclo ./Middlewares/ST/scpi-2.1/libscpi/src/ieee488.d ./Middlewares/ST/scpi-2.1/libscpi/src/ieee488.o ./Middlewares/ST/scpi-2.1/libscpi/src/ieee488.su ./Middlewares/ST/scpi-2.1/libscpi/src/lexer.cyclo ./Middlewares/ST/scpi-2.1/libscpi/src/lexer.d ./Middlewares/ST/scpi-2.1/libscpi/src/lexer.o ./Middlewares/ST/scpi-2.1/libscpi/src/lexer.su ./Middlewares/ST/scpi-2.1/libscpi/src/minimal.cyclo ./Middlewares/ST/scpi-2.1/libscpi/src/minimal.d ./Middlewares/ST/scpi-2.1/libscpi/src/minimal.o ./Middlewares/ST/scpi-2.1/libscpi/src/minimal.su ./Middlewares/ST/scpi-2.1/libscpi/src/parser.cyclo ./Middlewares/ST/scpi-2.1/libscpi/src/parser.d ./Middlewares/ST/scpi-2.1/libscpi/src/parser.o ./Middlewares/ST/scpi-2.1/libscpi/src/parser.su ./Middlewares/ST/scpi-2.1/libscpi/src/units.cyclo ./Middlewares/ST/scpi-2.1/libscpi/src/units.d ./Middlewares/ST/scpi-2.1/libscpi/src/units.o ./Middlewares/ST/scpi-2.1/libscpi/src/units.su ./Middlewares/ST/scpi-2.1/libscpi/src/utils.cyclo ./Middlewares/ST/scpi-2.1/libscpi/src/utils.d ./Middlewares/ST/scpi-2.1/libscpi/src/utils.o ./Middlewares/ST/scpi-2.1/libscpi/src/utils.su

.PHONY: clean-Middlewares-2f-ST-2f-scpi-2d-2-2e-1-2f-libscpi-2f-src

