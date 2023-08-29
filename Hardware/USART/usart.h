
#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"		//GPIO
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"	//SYSCTL
#include "inc/hw_memmap.h"		//GPIO_PORTF_BASE
#include "inc/hw_uart.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"		//HWREG

#include "driverlib/udma.h"
#include "inc/hw_udma.h"

#define USART_Peripheral		SYSCTL_PERIPH_UART1
#define USART_GPIOPeripheral	SYSCTL_PERIPH_GPIOB
#define USART_GPIO				GPIO_PORTB_BASE
#define Tx_GPIO_Pin				GPIO_PIN_1
#define Rx_GPIO_Pin				GPIO_PIN_0
#define Tx_PinConfig			GPIO_PB1_U1TX
#define Rx_PinConfig			GPIO_PB0_U1RX

#define USART					UART1_BASE
#define USART_Num				1
#define USART_Bound				115200

#define USART_Int				INT_UART1	

void USART_Init(void);
void Interrupt_Config(void);
void UART_DMA_Config(void);
void UART_Config(void);
void UART_RxHandler(void);
void Dma_Handler(void);

#endif /*_USART_H*/
