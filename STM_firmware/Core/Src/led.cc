
#include "led.hh"
#include "stm32f0xx_ll_gpio.h"

const LED ENC1_LED1{ENC1_LED1_PORT, ENC1_LED1_PIN};
const LED ENC1_LED2{ENC1_LED2_PORT, ENC1_LED2_PIN};

const LED ENC2_LED1{ENC2_LED1_PORT, ENC2_LED1_PIN};
const LED ENC2_LED2{ENC2_LED2_PORT, ENC2_LED2_PIN};

const LED ENC3_LED1{ENC3_LED1_PORT, ENC3_LED1_PIN};
const LED ENC3_LED2{ENC3_LED2_PORT, ENC3_LED2_PIN};

const LED ENC4_LED1{ENC4_LED1_PORT, ENC4_LED1_PIN};
const LED ENC4_LED2{ENC4_LED2_PORT, ENC4_LED2_PIN};

const LED ENC5_LED1{ENC5_LED1_PORT, ENC5_LED1_PIN};
const LED ENC5_LED2{ENC5_LED2_PORT, ENC5_LED2_PIN};

const LED ENC6_LED1{ENC6_LED1_PORT, ENC6_LED1_PIN};
const LED ENC6_LED2{ENC6_LED2_PORT, ENC6_LED2_PIN};

const LED ENC7_LED1{ENC7_LED1_PORT, ENC7_LED1_PIN};
const LED ENC7_LED2{ENC7_LED2_PORT, ENC7_LED2_PIN};

const LED ENC8_LED1{ENC8_LED1_PORT, ENC8_LED1_PIN};
const LED ENC8_LED2{ENC8_LED2_PORT, ENC8_LED2_PIN};

void Init_LEDS()
{
    auto init = [&](const LED &l)
    {
        LL_GPIO_SetPinMode(l.PORT, l.PIN, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinPull(l.PORT, l.PIN, LL_GPIO_PULL_DOWN);
    };

    init(ENC1_LED1);
    init(ENC1_LED2);
    init(ENC2_LED1);
    init(ENC2_LED2);
    init(ENC3_LED1);
    init(ENC3_LED2);
    init(ENC4_LED1);
    init(ENC4_LED2);

    init(ENC5_LED1);
    init(ENC5_LED2);

    init(ENC6_LED1);
    init(ENC6_LED2);
    init(ENC7_LED1);
    init(ENC7_LED2);
    init(ENC8_LED1);
    init(ENC8_LED2);
}

void On(const LED l)
{
    LL_GPIO_SetOutputPin(l.PORT, l.PIN);
}
void Off(const LED l)
{
    LL_GPIO_ResetOutputPin(l.PORT, l.PIN);
}
void Toggle(const LED l)
{
    l.PORT->ODR ^= l.PIN;
}
