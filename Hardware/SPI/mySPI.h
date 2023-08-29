
#ifndef _MYSPI_H
#define _MYSPI_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"		//GPIO
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"	//SYSCTL
#include "inc/hw_memmap.h"		//GPIO_PORTF_BASE
#include "inc/hw_types.h"		//HWREG
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "inc/hw_ssi.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

#define SPI_SYSCTL_PERIPH			SYSCTL_PERIPH_SSI0
#define SPIGPIO_SYSCTL_PERIPH		SYSCTL_PERIPH_GPIOA
#define SPI_CLK						GPIO_PA2_SSI0CLK
#define SPI_FSS						GPIO_PA3_SSI0FSS		//
#define SPI_RX						GPIO_PA4_SSI0RX
#define SPI_TX						GPIO_PA5_SSI0TX
#define SPI							SSI0_BASE
#define SPI_GPIO					GPIO_PORTA_BASE
#define SPICLKGPIO_Pin				GPIO_PIN_2
#define SPIFSSGPIO_Pin				GPIO_PIN_3
#define SPIRXGPIO_Pin				GPIO_PIN_4
#define SPITXGPIO_Pin				GPIO_PIN_5


#define SPI_INT						INT_SSI0

void SPI_Config(void);
void SPI_Write(uint8_t *data,uint8_t len);
uint32_t *SPI_Read(uint8_t len);
void SPI_Handler(void);

#endif /*_MySPI_H*/
