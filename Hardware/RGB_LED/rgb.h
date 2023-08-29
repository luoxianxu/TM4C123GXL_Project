
#ifndef _RGB_H
#define _RGB_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"

#define RGBSYSCTL_Peripheral		SYSCTL_PERIPH_GPIOF
#define RGB_GPIO					GPIO_PORTF_BASE
#define RGB1GPIO_Pin				GPIO_PIN_1
#define RGB2GPIO_Pin				GPIO_PIN_2
#define RGB3GPIO_Pin				GPIO_PIN_3

void Rgb_Init(void);


#endif /*_RGB_H*/
