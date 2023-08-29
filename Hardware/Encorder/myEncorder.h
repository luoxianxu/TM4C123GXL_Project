
#ifndef _MYENCORDER_H
#define _MYENCORDER_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"		//GPIO
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"	//SYSCTL
#include "inc/hw_memmap.h"		//GPIO_PORTF_BASE
#include "driverlib/qei.h"
#include "inc/hw_qei.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"

#define Encorder1_SYSCTL_PERIPH			SYSCTL_PERIPH_QEI1
#define Encorder1GPIO_SYSCTL_PERIPH		SYSCTL_PERIPH_GPIOC
#define Encorder1						QEI1_BASE
#define Encorder1_GPIO					GPIO_PORTC_BASE
#define Encorder1_A_GPIOPin				GPIO_PIN_5
#define Encorder1_B_GPIOPin				GPIO_PIN_6
#define Encorder1_PHA					GPIO_PC5_PHA1
#define Encorder1_PHB					GPIO_PC6_PHB1

void Encorder_Config(void);

#endif /*_MYENCORDER_H*/
