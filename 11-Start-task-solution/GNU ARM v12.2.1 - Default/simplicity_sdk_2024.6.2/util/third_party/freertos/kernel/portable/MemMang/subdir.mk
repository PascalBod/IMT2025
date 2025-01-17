################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2/util/third_party/freertos/kernel/portable/MemMang/heap_3.c 

OBJS += \
./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/MemMang/heap_3.o 

C_DEPS += \
./simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/MemMang/heap_3.d 


# Each subdirectory must supply rules for building sources it contributes
simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/MemMang/heap_3.o: /home/developer/SimplicityStudio/SDKs/simplicity_sdk_2/util/third_party/freertos/kernel/portable/MemMang/heap_3.c simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/MemMang/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c18 '-DDEBUG_EFM=1' '-DEFR32MG24B310F1536IM48=1' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=39000000' '-DSL_BOARD_NAME="BRD2601B"' '-DSL_BOARD_REV="A01"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DSL_CODE_COMPONENT_PERIPHERAL_SYSRTC=hal_sysrtc' '-DCMSIS_NVIC_VIRTUAL=1' '-DCMSIS_NVIC_VIRTUAL_HEADER_FILE="cmsis_nvic_virtual.h"' '-DSL_MEMORY_POOL_LIGHT=1' '-DSL_CODE_COMPONENT_CORE=core' '-DSL_CODE_COMPONENT_SLEEPTIMER=sleeptimer' -I"/home/developer/Dev/RTOS-presentation-private/solutions-to-exercises/11-Start-task-solution/config" -I"/home/developer/Dev/RTOS-presentation-private/solutions-to-exercises/11-Start-task-solution/autogen" -I"/home/developer/Dev/RTOS-presentation-private/solutions-to-exercises/11-Start-task-solution" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/Device/SiliconLabs/EFR32MG24/Include" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/common/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//hardware/board/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/clock_manager/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/clock_manager/src" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/CMSIS/Core/Include" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/CMSIS/RTOS2/Include" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/device_manager/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/device_init/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/emlib/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//util/third_party/freertos/cmsis/Include" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//util/third_party/freertos/kernel/include" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/peripheral/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/interrupt_manager/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/interrupt_manager/inc/arm" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/driver/leddrv/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/memory_manager/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/memory_manager/src" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/common/toolchain/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/system/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/sleeptimer/inc" -I"/home/developer/SimplicityStudio/SDKs/simplicity_sdk_2//platform/service/udelay/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"simplicity_sdk_2024.6.2/util/third_party/freertos/kernel/portable/MemMang/heap_3.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


