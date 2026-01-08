 

# Counter for 8 encoders built on STM32

Counts pulses from up to 8 encoders, 2 pins per single encoder.
Sends the number of pulses through usb (virtal serial port) on 10Hz rate.

Target Microcontroller: `STM32F072RBTx` series. Tested on STM32F072RBT6.


## General remarks
* Basic functionality like GPIO access,  interrupts and timers is handled with Low Level (LL_) driver

Code was first generated with CubeMX to configure pins, setup USB etc, timers, clocks, etc.
CubeMX generates __C__ code and makefile to compile it. All the __C++__ code was added later and is compiled separately.


## MCU
Using **STM32F072** microcontroller 

* clock source: internal high speed clock (HSI), frequency 48 MHz (same as for USB).
* does not use external oscillator on the board


## Requirements for command line compilation (Linux)
###  `gcc-arm-none-eabi` compiler

```
> apt-get install gcc-arm-none-eabi
```

###  `stlink-tools` cmdline utility for flashing
```
> apt-get install stlink-tools 
```

## Code compilation
Configured to compile as C++ code with `arm-none-eabi-g++` package
```
> make
```

## MCU Flashing 


In linux manully with command 
```
> st-flash write [file].bin 0x8000000
```

Or through dedicated makefile target `load`

```
> make load
```

`make load` will flash + reset the MCU afterwards (convinient for resetting counters, interrupts, etc.) 

**CPU can be also flashed with STM32CubeProgrammer by loading compiled `.bin` file.**


