
#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "driverlib/sysctl.h"	//SYSCTL


//Timer
#define TimerSYSCTL_Peripheral				SYSCTL_PERIPH_TIMER0
#define Timer								TIMER0_BASE
#define TimerX								TIMER_A
#define Timer_Interrupt						INT_TIMER0A

//PWM
#define PwmTimerSYSCTL_Peripheral			SYSCTL_PERIPH_TIMER1
#define PwmTimer							TIMER1_BASE
#define PwmTimerX							TIMER_B

#define PwmGPIOSYSCTL_Peripheral			SYSCTL_PERIPH_GPIOB
#define PwmGPIO								GPIO_PORTB_BASE
#define PwmGPIO_Pin0						GPIO_PIN_4
#define PwmGPIO_Pin1						GPIO_PIN_5
#define PwmPin0Config						GPIO_PB4_T1CCP0
#define PwmPin1Config						GPIO_PB5_T1CCP1

//Capture
#define SYSCTL_PERIPH_Capture_TIMER		 	SYSCTL_PERIPH_TIMER1
#define SYSCTL_PERIPH_Capture_GPIO			SYSCTL_PERIPH_GPIOB
#define Capture_GPIOPinConfig				GPIO_PB4_T1CCP0
#define Capture_GPIO						GPIO_PORTB_BASE
#define Capture_GPIO_Pin					GPIO_PIN_4
#define Capture_GPIO_Mode					GPIO_DIR_MODE_HW
#define Capture_Timer						TIMER1_BASE
#define Capture_Timer_INT					INT_TIMER1A

void Timer_Config(void);
void Timer_PWM_Config(void);
void Capture_Init(void);
void Timer_Handler(void);
void Timer_Capture_Handler(void);


#endif /*_TIMER_H*/
