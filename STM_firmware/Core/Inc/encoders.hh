#ifndef __ENCODERS_HH__
#define __ENCODERS_HH__

#include "main.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define N_CHANNELS 8

#define ENCODER_1 0
#define ENCODER_2 1
#define ENCODER_3 2
#define ENCODER_4 3
#define ENCODER_5 4
#define ENCODER_6 5
#define ENCODER_7 6
#define ENCODER_8 7

    // 0 - left, 1 - right
    extern uint8_t rotation_direction[N_CHANNELS];

    // encoders have 2 channels, but counts on them will be the same within 1-2 ticks
    // for this use it's enough to read from one 
    extern uint32_t channel1_steps[N_CHANNELS];
    extern uint32_t channel2_steps[N_CHANNELS];

    extern float rotation_speed_rps[N_CHANNELS];

    const float steps_per_rotation = 400; //this is custom to the encoded model

#ifdef __cplusplus
}
#endif

#endif