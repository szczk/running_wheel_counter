#ifndef __LEDS_HH__
#define __LEDS_HH__

#include "gpio_pins.h"
#include "stm32f0xx_ll_gpio.h"

// this is c++, but can be used from withing c files if needed

struct LED
{
    GPIO_TypeDef *PORT;
    unsigned int PIN;
};

extern const struct LED ENC1_LED1;
extern const struct LED ENC1_LED2;

extern const struct LED ENC2_LED1;
extern const struct LED ENC2_LED2;

extern const struct LED ENC3_LED1;
extern const struct LED ENC3_LED2;

extern const struct LED ENC4_LED1;
extern const struct LED ENC4_LED2;

extern const struct LED ENC5_LED1;
extern const struct LED ENC5_LED2;

extern const struct LED ENC6_LED1;
extern const struct LED ENC6_LED2;

extern const struct LED ENC7_LED1;
extern const struct LED ENC7_LED2;

extern const struct LED ENC8_LED1;
extern const struct LED ENC8_LED2;

#ifdef __cplusplus
extern "C"
{
#endif

    void Init_LEDS();
    void On(const struct LED);
    void Off(const struct LED);
    void Toggle(const struct LED);

#ifdef __cplusplus
}
#endif

#endif