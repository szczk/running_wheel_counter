#include "main.h"
#include "usbd_cdc_if.h"
#include <stm32f0xx_ll_tim.h>
#include "gpio_pins.h"
#include "encoders.hh"
extern PCD_HandleTypeDef hpcd_USB_FS;

char chan_buf[8][30];
char buff[255];
/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
  while (1)
  {
  }
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void)
{
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles USB global interrupt / USB wake-up interrupt through EXTI line 18.
 */
void USB_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
}

void TIM7_IRQHandler(void)
{
  if (LL_TIM_IsActiveFlag_UPDATE(TIM7))
  {
    LL_TIM_ClearFlag_UPDATE(TIM7);
    // this is called when 1/10 s passed
    // during which encoder N did channel1_steps[N];

    for (uint8_t i = 0; i < N_CHANNELS; i++)
    {
      // this can be used to send both counts channels for every encoder
      // sprintf(chan_buf[i], "%d %d\t", channel1_steps[i], channel2_steps[i]);

      // send only one channel per encoder (depending on the direction)
      // we transmit just the raw counts, let the readout software do the calculation of RPS
      sprintf(chan_buf[i], "%c%d\t", (rotation_direction[i] ? '-' : '+'), channel1_steps[i]);

      rotation_speed_rps[i] = 10.0 * channel1_steps[i] / steps_per_rotation;
      channel1_steps[i] = 0;
      channel2_steps[i] = 0;
    }

    sprintf(buff, "%s %s %s %s %s %s %s %s\r\n", chan_buf[ENCODER_1], chan_buf[ENCODER_2], chan_buf[ENCODER_3], chan_buf[ENCODER_4], chan_buf[ENCODER_5], chan_buf[ENCODER_6], chan_buf[ENCODER_7], chan_buf[ENCODER_8]);
    CDC_Transmit_FS(buff, strlen(buff));
  }
}

void EXTI4_15_IRQHandler(void)
{
  // 4-5   - ENCODER 6
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_4))
  {
    ++channel1_steps[ENCODER_6];
    rotation_direction[ENCODER_6] = LL_GPIO_IsInputPinSet(ENC6_OUT2_PORT, ENC6_OUT2_PIN);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_5))
  {
    ++channel2_steps[ENCODER_6];
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);
  }

  // 6-7   - ENCODER 7
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_6))
  {
    ++channel1_steps[ENCODER_7];
    rotation_direction[ENCODER_7] = LL_GPIO_IsInputPinSet(ENC7_OUT2_PORT, ENC7_OUT2_PIN);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_7))
  {
    ++channel2_steps[ENCODER_7];
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_7);
  }

  // 8-9   - ENCODER 8
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_8))
  {
    ++channel1_steps[ENCODER_8];
    rotation_direction[ENCODER_8] = LL_GPIO_IsInputPinSet(ENC8_OUT2_PORT, ENC8_OUT2_PIN);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8);
  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_9))
  {
    ++channel2_steps[ENCODER_8];
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_9);
  }

  // 10-11 - ENCODER 3
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_10))
  {
    ++channel1_steps[ENCODER_3];
    rotation_direction[ENCODER_3] = LL_GPIO_IsInputPinSet(ENC3_OUT2_PORT, ENC3_OUT2_PIN);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);
  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11))
  {
    ++channel2_steps[ENCODER_3];
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
  }

  // 12-13 - ENCODER 2
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_12))
  {
    ++channel1_steps[ENCODER_2];
    rotation_direction[ENCODER_2] = LL_GPIO_IsInputPinSet(ENC2_OUT2_PORT, ENC2_OUT2_PIN);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);
  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_13))
  {
    ++channel2_steps[ENCODER_2];
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
  }

  // 14-15 - ENCODER 1
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_14))
  {
    ++channel1_steps[ENCODER_1];
    rotation_direction[ENCODER_1] = LL_GPIO_IsInputPinSet(ENC1_OUT2_PORT, ENC1_OUT2_PIN);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);
  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_15))
  {
    ++channel2_steps[ENCODER_1];
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_15);
  }
}

void EXTI0_1_IRQHandler(void)
{
  // 0-1 - ENCODER 5
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0))
  {
    ++channel1_steps[ENCODER_5];
    rotation_direction[ENCODER_5] = LL_GPIO_IsInputPinSet(ENC5_OUT2_PORT, ENC5_OUT2_PIN);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1))
  {
    ++channel2_steps[ENCODER_5];
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
  }
}

void EXTI2_3_IRQHandler(void)
{
  // 2-3 - ENCODER 4
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_2))
  {
    ++channel1_steps[ENCODER_4];
    rotation_direction[ENCODER_4] = LL_GPIO_IsInputPinSet(ENC4_OUT2_PORT, ENC4_OUT2_PIN);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_3))
  {
    ++channel2_steps[ENCODER_4];
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
  }
}
