################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include NetXDuo/App/subdir.mk
-include Middlewares/ST/threadx/utility/low_power/subdir.mk
-include Middlewares/ST/threadx/ports/cortex_m7/gnu/src/subdir.mk
-include Middlewares/ST/threadx/common/src/subdir.mk
-include Middlewares/ST/netxduo/common/src/subdir.mk
-include Middlewares/ST/netxduo/common/drivers/ethernet/lan8742/subdir.mk
-include Middlewares/ST/netxduo/common/drivers/ethernet/subdir.mk
-include Middlewares/ST/netxduo/addons/sntp/subdir.mk
-include Middlewares/ST/netxduo/addons/ppp/subdir.mk
-include Middlewares/ST/netxduo/addons/auto_ip/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/Components/lan8742/subdir.mk
-include Core/scpi-2.1/libscpi/src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include AZURE_RTOS/App/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ETH1CSMU2_ThreadX
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ETH1CSMU2_ThreadX.elf \

MAP_FILES += \
ETH1CSMU2_ThreadX.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ETH1CSMU2_ThreadX.list \


# All Target
all: main-build

# Main-build Target
main-build: ETH1CSMU2_ThreadX.elf secondary-outputs

# Tool invocations
ETH1CSMU2_ThreadX.elf ETH1CSMU2_ThreadX.map: $(OBJS) $(USER_OBJS) /home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_ThreadX/STM32F746ZGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ETH1CSMU2_ThreadX.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"/home/grzegorz/git/ETH1CSMU2/SOFTWARE/ETH1CSMU2_ThreadX/STM32F746ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ETH1CSMU2_ThreadX.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ETH1CSMU2_ThreadX.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ETH1CSMU2_ThreadX.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ETH1CSMU2_ThreadX.elf ETH1CSMU2_ThreadX.list ETH1CSMU2_ThreadX.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
