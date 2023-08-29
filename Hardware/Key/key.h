
#ifndef _KEY_H
#define _KEY_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"		//GPIO
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"	//SYSCTL
#include "inc/hw_memmap.h"		//GPIO_PORTF_BASE
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"		//HWREG


#define KeySYSCTL_Peripheral		SYSCTL_PERIPH_GPIOF
#define Key1GPIO					GPIO_PORTF_BASE
#define Key1GPIO_Pin				GPIO_PIN_4

#define Key2GPIO					GPIO_PORTF_BASE
#define Key2GPIO_Pin				GPIO_PIN_0

#define KeyPinMode					GPIO_PIN_TYPE_STD_WPU

#define Key_IntGPIO					INT_GPIOF
#define Key1_GPIOIntPin				GPIO_PIN_4
#define Key2_GPIOIntPin				GPIO_PIN_0

void Key_Config(void);
void Key_Detect(void);
void Key_Interrupt_Config(void);
void SW2_Handler(void);

#endif/*_KEY_H*/
