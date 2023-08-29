#ifndef _MYADC_H
#define _MYADC_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"	//SYSCTL
#include "inc/hw_memmap.h"		
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/adc.h"
#include "inc/hw_adc.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

#define ADC_SYSCTL_PERIPH			SYSCTL_PERIPH_ADC0
#define ADCGPIO_SYSCTL_PERIPH		SYSCTL_PERIPH_GPIOE

#define ADC_GPIO					GPIO_PORTE_BASE
#define ADC_GPIO_Pin				GPIO_PIN_3


#define ADC							ADC0_BASE
#define SequenceNum					0
#define ADC_INT						INT_ADC0SS0
#define Priority					0

void ADC_Config(void);

#endif /*_MYADC_H*/
