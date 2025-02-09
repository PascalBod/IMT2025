#include "sl_event_handler.h"

#include "em_chip.h"
#include "sl_interrupt_manager.h"
#include "sl_board_init.h"
#include "sl_clock_manager_init.h"
#include "sl_device_init_dcdc.h"
#include "sl_clock_manager.h"
#include "sl_device_init_emu.h"
#include "sl_memory_manager.h"
#include "sl_board_control.h"
#include "sl_sleeptimer.h"
#include "sl_simple_led_instances.h"
#include "cmsis_os2.h"

void sl_platform_init(void)
{
  CHIP_Init();
  sl_interrupt_manager_init();
  sl_board_preinit();
  sl_clock_manager_init();
  sl_device_init_dcdc();
  sl_clock_manager_runtime_init();
  sl_device_init_emu();
  sl_memory_init();
  sl_board_init();
  osKernelInitialize();
}

void sl_kernel_start(void)
{
  osKernelStart();
}

void sl_driver_init(void)
{
  sl_simple_led_init_instances();
}

void sl_service_init(void)
{
  sl_board_configure_vcom();
  sl_sleeptimer_init();
}

void sl_stack_init(void)
{
}

void sl_internal_app_init(void)
{
}

