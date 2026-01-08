
#include "main.h"
#include "usb_device.h"
#include "gpio_pins.h"
#include "led.hh"
#include <encoders.hh>

static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);

extern uint32_t interval;

LED leds1[8] = {ENC1_LED1, ENC2_LED1, ENC3_LED1, ENC4_LED1, ENC5_LED1, ENC6_LED1, ENC7_LED1, ENC8_LED1};
LED leds2[8] = {ENC1_LED2, ENC2_LED2, ENC3_LED2, ENC4_LED2, ENC5_LED2, ENC6_LED2, ENC7_LED2, ENC8_LED2};

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();

  MX_USB_DEVICE_Init();

  Init_LEDS();
  for (int i = 0; i < 8; i++)
    On(leds1[i]);

  HAL_Delay(250);
  for (int i = 0; i < 8; i++)
    On(leds2[i]);
  HAL_Delay(250);

  for (int i = 0; i < 8; i++)
    Off(leds1[i]);
  HAL_Delay(250);

  MX_TIM6_Init();

  while (1)
  {
    HAL_Delay(50);

    for (uint8_t i = 0; i < N_CHANNELS; i++)
    {
      if (rotation_speed_rps[i] < 0.05)
      {
        Off(leds1[i]);
        Off(leds2[i]);
      }
      else
      {
        if (rotation_direction[i])
        {
          On(leds1[i]);
          Off(leds2[i]);
        }
        else
        {
          On(leds2[i]);
          Off(leds1[i]);
        }
      }
    }
  }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
  {
  }
  LL_RCC_HSI_Enable();

  /* Wait till HSI is ready */
  while (LL_RCC_HSI_IsReady() != 1)
  {
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI48_Enable();

  /* Wait till HSI48 is ready */
  while (LL_RCC_HSI48_IsReady() != 1)
  {
  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_6, LL_RCC_PREDIV_DIV_1);
  LL_RCC_PLL_Enable();

  /* Wait till PLL is ready */
  while (LL_RCC_PLL_IsReady() != 1)
  {
  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

  /* Wait till System clock is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }
  LL_SetSystemCoreClock(48000000);

  /* Update the time base */
  if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
  LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_HSI48);
}

/**
 * @brief TIM6 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM6_Init(void)
{
  // timer clocks: 48mhz (from internal oscillator)
  uint32_t clockFreq = 48000000;
  int InitialAutoreload = 0;
  LL_TIM_ClearFlag_UPDATE(TIM7);

  //=================== TIM7 timer - USB transmission - every 1/10 s
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
  LL_TIM_SetPrescaler(TIM7, __LL_TIM_CALC_PSC(clockFreq, 1000));                   // 100 kHz
  InitialAutoreload = __LL_TIM_CALC_ARR(clockFreq, LL_TIM_GetPrescaler(TIM7), 10); // 10 Hz
  LL_TIM_SetAutoReload(TIM7, InitialAutoreload);
  NVIC_SetPriority(TIM7_IRQn, 1);
  NVIC_EnableIRQ(TIM7_IRQn);
  LL_TIM_EnableCounter(TIM7);

  LL_TIM_EnableIT_UPDATE(TIM7);
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

  //===========================================
  // ENCODER pins

  // all encoders are on GPIO B
  GPIO_InitStruct.Pin = ENC1_OUT1_PIN | ENC1_OUT2_PIN | ENC2_OUT1_PIN | ENC2_OUT2_PIN |
                        ENC3_OUT1_PIN | ENC3_OUT2_PIN | ENC4_OUT1_PIN | ENC4_OUT2_PIN |
                        ENC5_OUT1_PIN | ENC5_OUT2_PIN | ENC6_OUT1_PIN | ENC6_OUT2_PIN |
                        ENC7_OUT1_PIN | ENC7_OUT2_PIN | ENC8_OUT1_PIN | ENC8_OUT2_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE0);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE1);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE2);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE3);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE4);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE5);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE6);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE7);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE8);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE9);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE10);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE11);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE12);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE13);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE14);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE15);

  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_0 | LL_EXTI_LINE_1 | LL_EXTI_LINE_2 | LL_EXTI_LINE_3 |
                              LL_EXTI_LINE_4 | LL_EXTI_LINE_5 | LL_EXTI_LINE_6 | LL_EXTI_LINE_7 |
                              LL_EXTI_LINE_8 | LL_EXTI_LINE_9 | LL_EXTI_LINE_10 | LL_EXTI_LINE_11 |
                              LL_EXTI_LINE_12 | LL_EXTI_LINE_13 | LL_EXTI_LINE_14 | LL_EXTI_LINE_15;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  // NVIC_SetPriority(EXTI4_15_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
  NVIC_EnableIRQ(EXTI4_15_IRQn);
  NVIC_EnableIRQ(EXTI0_1_IRQn);
  NVIC_EnableIRQ(EXTI2_3_IRQn);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
