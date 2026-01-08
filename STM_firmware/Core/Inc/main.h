#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f0xx_hal.h"

#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_tim.h"
#include "stm32f0xx_ll_gpio.h"
#ifdef __cplusplus
extern "C"
{
#endif



  void Error_Handler(void);
  void SystemClock_Config(void);

#define USBF4_DM_Pin LL_GPIO_PIN_11
#define USBF4_DM_GPIO_Port GPIOA
#define USBF4_DP_Pin LL_GPIO_PIN_12
#define USBF4_DP_GPIO_Port GPIOA

#ifdef __cplusplus
}
#endif

#endif
