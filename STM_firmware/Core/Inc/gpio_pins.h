#ifndef __GPIO_PINS_H__
#define __GPIO_PINS_H__
#include "stm32f0xx_ll_gpio.h"

#ifdef __cplusplus
extern "C"
{
#endif

        // encoder 1 = P17 on the board

#define ENC1_OUT1_PIN LL_GPIO_PIN_14
#define ENC1_OUT1_PORT GPIOB
#define ENC1_OUT2_PIN LL_GPIO_PIN_15
#define ENC1_OUT2_PORT GPIOB
    // encoder1 LED = P5
#define ENC1_LED1_PIN LL_GPIO_PIN_6
#define ENC1_LED1_PORT GPIOC
#define ENC1_LED2_PIN LL_GPIO_PIN_7
#define ENC1_LED2_PORT GPIOC
//==========================================
// encoder 2 = P15
#define ENC2_OUT1_PIN LL_GPIO_PIN_12
#define ENC2_OUT1_PORT GPIOB
#define ENC2_OUT2_PIN LL_GPIO_PIN_13
#define ENC2_OUT2_PORT GPIOB
    // encoder2 LED = P9
#define ENC2_LED1_PIN LL_GPIO_PIN_4
#define ENC2_LED1_PORT GPIOC
#define ENC2_LED2_PIN LL_GPIO_PIN_5
#define ENC2_LED2_PORT GPIOC
//==========================================
// encoder 3 = P11
#define ENC3_OUT1_PIN LL_GPIO_PIN_10
#define ENC3_OUT1_PORT GPIOB
#define ENC3_OUT2_PIN LL_GPIO_PIN_11
#define ENC3_OUT2_PORT GPIOB
    // encoder3 LED = P4
#define ENC3_LED1_PIN LL_GPIO_PIN_6
#define ENC3_LED1_PORT GPIOA
#define ENC3_LED2_PIN LL_GPIO_PIN_7
#define ENC3_LED2_PORT GPIOA
//==========================================
// encoder 4 = P10
#define ENC4_OUT1_PIN LL_GPIO_PIN_2
#define ENC4_OUT1_PORT GPIOB
#define ENC4_OUT2_PIN LL_GPIO_PIN_3
#define ENC4_OUT2_PORT GPIOB
    // encoder4 LED = P8
#define ENC4_LED1_PIN LL_GPIO_PIN_4
#define ENC4_LED1_PORT GPIOA
#define ENC4_LED2_PIN LL_GPIO_PIN_5
#define ENC4_LED2_PORT GPIOA
//==========================================
// encoder 5 = P12
#define ENC5_OUT1_PIN LL_GPIO_PIN_0
#define ENC5_OUT1_PORT GPIOB
#define ENC5_OUT2_PIN LL_GPIO_PIN_1
#define ENC5_OUT2_PORT GPIOB
    // encoder5 LED = P6
#define ENC5_LED1_PIN LL_GPIO_PIN_2
#define ENC5_LED1_PORT GPIOA
#define ENC5_LED2_PIN LL_GPIO_PIN_3
#define ENC5_LED2_PORT GPIOA
//==========================================
// encoder 6 = P14
#define ENC6_OUT1_PIN LL_GPIO_PIN_4
#define ENC6_OUT1_PORT GPIOB
#define ENC6_OUT2_PIN LL_GPIO_PIN_5
#define ENC6_OUT2_PORT GPIOB
    // encoder6 LED = P2
#define ENC6_LED1_PIN LL_GPIO_PIN_0
#define ENC6_LED1_PORT GPIOA
#define ENC6_LED2_PIN LL_GPIO_PIN_1
#define ENC6_LED2_PORT GPIOA
//==========================================
// encoder 7 = P16
#define ENC7_OUT1_PIN LL_GPIO_PIN_6
#define ENC7_OUT1_PORT GPIOB
#define ENC7_OUT2_PIN LL_GPIO_PIN_7
#define ENC7_OUT2_PORT GPIOB
    // encoder7 LED = P7
#define ENC7_LED1_PIN LL_GPIO_PIN_2
#define ENC7_LED1_PORT GPIOC
#define ENC7_LED2_PIN LL_GPIO_PIN_3
#define ENC7_LED2_PORT GPIOC
//==========================================
// encoder 8 = P13
#define ENC8_OUT1_PIN LL_GPIO_PIN_8
#define ENC8_OUT1_PORT GPIOB
#define ENC8_OUT2_PIN LL_GPIO_PIN_9
#define ENC8_OUT2_PORT GPIOB
    // encoder8 LED = P3
#define ENC8_LED1_PIN LL_GPIO_PIN_0
#define ENC8_LED1_PORT GPIOC
#define ENC8_LED2_PIN LL_GPIO_PIN_1
#define ENC8_LED2_PORT GPIOC
    //==========================================

#ifdef __cplusplus
}
#endif

#endif