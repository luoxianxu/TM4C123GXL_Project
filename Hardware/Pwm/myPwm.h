
#ifndef _MYPWM_H
#define _MYPWM_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"		//GPIO
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"	//SYSCTL
#include "inc/hw_memmap.h"		//GPIO_PORTF_BASE
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"		//HWREG
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"

#define	 PWM_SYSCTL_PERIPH			SYSCTL_PERIPH_PWM0
#define  PWMGPIO_SYSCTL_PERIPH		SYSCTL_PERIPH_GPIOB
#define  PWMGPIO					GPIO_PORTB_BASE
#define  PWMGPIO_Pin				GPIO_PIN_6
#define  PWMGPIO_Mode				GPIO_PB6_M0PWM0
#define  PWM						PWM0_BASE
#define  PWM_GEN					PWM_GEN_0
#define  PWM_OUT					PWM_OUT_0
#define  PWM_OUT_Bit				PWM_OUT_0_BIT


void Pwm_Config(void);

#endif /*_MYPWM_H*/
