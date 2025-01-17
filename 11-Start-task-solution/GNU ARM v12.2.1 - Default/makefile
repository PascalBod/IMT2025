################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/MemMang/subdir.mk
-include simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/subdir.mk
-include simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/subdir.mk
-include simplicity_sdk_2024.6.2/util/third_party/freertos/cmsis/Source/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/udelay/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/system/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/sleeptimer/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/memory_manager/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/interrupt_manager/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/device_manager/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/device_manager/devices/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/device_manager/clocks/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/device_init/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/service/clock_manager/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/peripheral/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/emlib/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/driver/leddrv/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/common/src/subdir.mk
-include simplicity_sdk_2024.6.2/platform/Device/SiliconLabs/EFR32MG24/Source/subdir.mk
-include simplicity_sdk_2024.6.2/platform/CMSIS/RTOS2/Source/subdir.mk
-include simplicity_sdk_2024.6.2/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/subdir.mk
-include simplicity_sdk_2024.6.2/hardware/board/src/subdir.mk
-include autogen/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 11-Start-task-solution
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: 11-Start-task-solution.axf

# Tool invocations
11-Start-task-solution.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "/home/developer/Dev/RTOS-presentation-private/solutions-to-exercises/11-Start-task-solution/autogen/linkerfile.ld" -Wl,--wrap=_free_r -Wl,--wrap=_malloc_r -Wl,--wrap=_calloc_r -Wl,--wrap=_realloc_r -Wl,--no-warn-rwx-segments -Xlinker --gc-sections -Xlinker -Map="11-Start-task-solution.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o 11-Start-task-solution.axf -Wl,--start-group "./app.o" "./blink.o" "./main.o" "./autogen/sl_board_default_init.o" "./autogen/sl_event_handler.o" "./autogen/sl_simple_led_instances.o" "./simplicity_sdk_2024.6.2/hardware/board/src/sl_board_control_gpio.o" "./simplicity_sdk_2024.6.2/hardware/board/src/sl_board_init.o" "./simplicity_sdk_2024.6.2/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.o" "./simplicity_sdk_2024.6.2/platform/CMSIS/RTOS2/Source/os_systick.o" "./simplicity_sdk_2024.6.2/platform/Device/SiliconLabs/EFR32MG24/Source/startup_efr32mg24.o" "./simplicity_sdk_2024.6.2/platform/Device/SiliconLabs/EFR32MG24/Source/system_efr32mg24.o" "./simplicity_sdk_2024.6.2/platform/common/src/sl_assert.o" "./simplicity_sdk_2024.6.2/platform/common/src/sl_core_cortexm.o" "./simplicity_sdk_2024.6.2/platform/common/src/sl_syscalls.o" "./simplicity_sdk_2024.6.2/platform/driver/leddrv/src/sl_led.o" "./simplicity_sdk_2024.6.2/platform/driver/leddrv/src/sl_simple_led.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_burtc.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_cmu.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_core.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_emu.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_gpio.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_msc.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_prs.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_system.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_timer.o" "./simplicity_sdk_2024.6.2/platform/emlib/src/em_usart.o" "./simplicity_sdk_2024.6.2/platform/peripheral/src/sl_hal_sysrtc.o" "./simplicity_sdk_2024.6.2/platform/service/clock_manager/src/sl_clock_manager.o" "./simplicity_sdk_2024.6.2/platform/service/clock_manager/src/sl_clock_manager_hal_s2.o" "./simplicity_sdk_2024.6.2/platform/service/clock_manager/src/sl_clock_manager_init.o" "./simplicity_sdk_2024.6.2/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.o" "./simplicity_sdk_2024.6.2/platform/service/device_init/src/sl_device_init_dcdc_s2.o" "./simplicity_sdk_2024.6.2/platform/service/device_init/src/sl_device_init_emu_s2.o" "./simplicity_sdk_2024.6.2/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.o" "./simplicity_sdk_2024.6.2/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg24.o" "./simplicity_sdk_2024.6.2/platform/service/device_manager/src/sl_device_clock.o" "./simplicity_sdk_2024.6.2/platform/service/device_manager/src/sl_device_peripheral.o" "./simplicity_sdk_2024.6.2/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.o" "./simplicity_sdk_2024.6.2/platform/service/memory_manager/src/sl_memory_manager.o" "./simplicity_sdk_2024.6.2/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.o" "./simplicity_sdk_2024.6.2/platform/service/memory_manager/src/sl_memory_manager_pool.o" "./simplicity_sdk_2024.6.2/platform/service/memory_manager/src/sl_memory_manager_region.o" "./simplicity_sdk_2024.6.2/platform/service/memory_manager/src/sl_memory_manager_retarget.o" "./simplicity_sdk_2024.6.2/platform/service/memory_manager/src/sli_memory_manager_common.o" "./simplicity_sdk_2024.6.2/platform/service/sleeptimer/src/sl_sleeptimer.o" "./simplicity_sdk_2024.6.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.o" "./simplicity_sdk_2024.6.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.o" "./simplicity_sdk_2024.6.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.o" "./simplicity_sdk_2024.6.2/platform/service/system/src/sl_system_init.o" "./simplicity_sdk_2024.6.2/platform/service/system/src/sl_system_kernel.o" "./simplicity_sdk_2024.6.2/platform/service/udelay/src/sl_udelay.o" "./simplicity_sdk_2024.6.2/platform/service/udelay/src/sl_udelay_armv6m_gcc.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/cmsis/Source/cmsis_os2.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/croutine.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/event_groups.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/list.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/queue.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/stream_buffer.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/tasks.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/timers.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.o" "./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/MemMang/heap_3.o" -lgcc -lc -lm -lnosys -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building out file: 11-Start-task-solution.out'
	arm-none-eabi-objcopy "11-Start-task-solution.axf" "11-Start-task-solution.out"
	@echo ' '

	@echo 'Building hex file: 11-Start-task-solution.hex'
	arm-none-eabi-objcopy -O ihex "11-Start-task-solution.axf" "11-Start-task-solution.hex"
	@echo ' '

	@echo 'Building bin file: 11-Start-task-solution.bin'
	arm-none-eabi-objcopy -O binary "11-Start-task-solution.axf" "11-Start-task-solution.bin"
	@echo ' '

	@echo 'Building s37 file: 11-Start-task-solution.s37'
	arm-none-eabi-objcopy -O srec "11-Start-task-solution.axf" "11-Start-task-solution.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "11-Start-task-solution.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) 11-Start-task-solution.axf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
