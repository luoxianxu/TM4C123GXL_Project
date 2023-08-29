
#ifndef _MYDMA_H
#define _MYDMA_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"	//SYSCTL
#include "inc/hw_memmap.h"		
#include "driverlib/pin_map.h"
#include "driverlib/udma.h"
#include "inc/hw_udma.h"
#include "inc/hw_uart.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"

#define DMA_CH					UDMA_CH12_UART2RX
#define DMA_Channel				UDMA_SEC_CHANNEL_UART2RX_0
#define ChannelStructIndex		DMA_CH|DMA_Channel
#define DMA_Data_Size			UDMA_SIZE_8				//dma传输数据的大小
#define DMA_SRC_INC				UDMA_SRC_INC_NONE		//源地址的增量
#define DMA_DST_INC				UDMA_DST_INC_8			//目标地址的增量
#define DMA_ARB					UDMA_ARB_1				//?
#define Control					DMA_Data_Size|DMA_SRC_INC|DMA_DST_INC|DMA_ARB

#define DMA_SDT
#define DMA_SRC					(UART2_BASE+UART_O_DR)		

void DMA_Config(void);
void USART_DMA_Config(void);
#endif/*_myDMA_H*/
