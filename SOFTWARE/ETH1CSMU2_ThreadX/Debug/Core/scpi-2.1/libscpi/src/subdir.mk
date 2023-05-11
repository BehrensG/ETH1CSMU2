################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/scpi-2.1/libscpi/src/error.c \
../Core/scpi-2.1/libscpi/src/expression.c \
../Core/scpi-2.1/libscpi/src/fifo.c \
../Core/scpi-2.1/libscpi/src/ieee488.c \
../Core/scpi-2.1/libscpi/src/lexer.c \
../Core/scpi-2.1/libscpi/src/minimal.c \
../Core/scpi-2.1/libscpi/src/parser.c \
../Core/scpi-2.1/libscpi/src/units.c \
../Core/scpi-2.1/libscpi/src/utils.c 

OBJS += \
./Core/scpi-2.1/libscpi/src/error.o \
./Core/scpi-2.1/libscpi/src/expression.o \
./Core/scpi-2.1/libscpi/src/fifo.o \
./Core/scpi-2.1/libscpi/src/ieee488.o \
./Core/scpi-2.1/libscpi/src/lexer.o \
./Core/scpi-2.1/libscpi/src/minimal.o \
./Core/scpi-2.1/libscpi/src/parser.o \
./Core/scpi-2.1/libscpi/src/units.o \
./Core/scpi-2.1/libscpi/src/utils.o 

C_DEPS += \
./Core/scpi-2.1/libscpi/src/error.d \
./Core/scpi-2.1/libscpi/src/expression.d \
./Core/scpi-2.1/libscpi/src/fifo.d \
./Core/scpi-2.1/libscpi/src/ieee488.d \
./Core/scpi-2.1/libscpi/src/lexer.d \
./Core/scpi-2.1/libscpi/src/minimal.d \
./Core/scpi-2.1/libscpi/src/parser.d \
./Core/scpi-2.1/libscpi/src/units.d \
./Core/scpi-2.1/libscpi/src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/scpi-2.1/libscpi/src/%.o Core/scpi-2.1/libscpi/src/%.su Core/scpi-2.1/libscpi/src/%.cyclo: ../Core/scpi-2.1/libscpi/src/%.c Core/scpi-2.1/libscpi/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DTX_INCLUDE_USER_DEFINE_FILE -DNX_INCLUDE_USER_DEFINE_FILE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_ThreadX/Core/scpi-2.1/libscpi/inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../AZURE_RTOS/App -I../NetXDuo/App -I../NetXDuo/Target -I../Middlewares/ST/netxduo/common/drivers/ethernet/ -I../Middlewares/ST/netxduo/addons/sntp/ -I../Middlewares/ST/netxduo/addons/auto_ip/ -I../Middlewares/ST/netxduo/common/inc/ -I../Middlewares/ST/netxduo/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/netxduo/addons/ppp/ -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/ -I../Middlewares/ST/threadx/utility/low_power/ -I../Drivers/BSP/Components/lan8742/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-scpi-2d-2-2e-1-2f-libscpi-2f-src

clean-Core-2f-scpi-2d-2-2e-1-2f-libscpi-2f-src:
	-$(RM) ./Core/scpi-2.1/libscpi/src/error.cyclo ./Core/scpi-2.1/libscpi/src/error.d ./Core/scpi-2.1/libscpi/src/error.o ./Core/scpi-2.1/libscpi/src/error.su ./Core/scpi-2.1/libscpi/src/expression.cyclo ./Core/scpi-2.1/libscpi/src/expression.d ./Core/scpi-2.1/libscpi/src/expression.o ./Core/scpi-2.1/libscpi/src/expression.su ./Core/scpi-2.1/libscpi/src/fifo.cyclo ./Core/scpi-2.1/libscpi/src/fifo.d ./Core/scpi-2.1/libscpi/src/fifo.o ./Core/scpi-2.1/libscpi/src/fifo.su ./Core/scpi-2.1/libscpi/src/ieee488.cyclo ./Core/scpi-2.1/libscpi/src/ieee488.d ./Core/scpi-2.1/libscpi/src/ieee488.o ./Core/scpi-2.1/libscpi/src/ieee488.su ./Core/scpi-2.1/libscpi/src/lexer.cyclo ./Core/scpi-2.1/libscpi/src/lexer.d ./Core/scpi-2.1/libscpi/src/lexer.o ./Core/scpi-2.1/libscpi/src/lexer.su ./Core/scpi-2.1/libscpi/src/minimal.cyclo ./Core/scpi-2.1/libscpi/src/minimal.d ./Core/scpi-2.1/libscpi/src/minimal.o ./Core/scpi-2.1/libscpi/src/minimal.su ./Core/scpi-2.1/libscpi/src/parser.cyclo ./Core/scpi-2.1/libscpi/src/parser.d ./Core/scpi-2.1/libscpi/src/parser.o ./Core/scpi-2.1/libscpi/src/parser.su ./Core/scpi-2.1/libscpi/src/units.cyclo ./Core/scpi-2.1/libscpi/src/units.d ./Core/scpi-2.1/libscpi/src/units.o ./Core/scpi-2.1/libscpi/src/units.su ./Core/scpi-2.1/libscpi/src/utils.cyclo ./Core/scpi-2.1/libscpi/src/utils.d ./Core/scpi-2.1/libscpi/src/utils.o ./Core/scpi-2.1/libscpi/src/utils.su

.PHONY: clean-Core-2f-scpi-2d-2-2e-1-2f-libscpi-2f-src

