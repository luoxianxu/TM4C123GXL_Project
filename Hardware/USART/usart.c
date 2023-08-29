
#include "usart.h"
uint8_t ui8ControlTable[1024] __attribute__ ((aligned(1024)));

uint8_t g_ui8TxBuf[10]={0};
uint8_t g_ui8RxBufA[50]={0};
uint8_t g_ui8RxBufB[50]={0};
void USART_Init(void){
	//串口时钟使能
	SysCtlPeripheralEnable(USART_Peripheral);
	//串口GPIO使能
	SysCtlPeripheralEnable(USART_GPIOPeripheral);
	
	//解锁PD7
//	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
//    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= (1<<7);//解锁
//    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
	//配置引脚为PP模式
	GPIOPinConfigure(Tx_PinConfig);
	GPIOPinConfigure(Rx_PinConfig);
	
	//GPIO 串口模式配置
	GPIOPinTypeUART(USART_GPIO, Tx_GPIO_Pin);
	GPIOPinTypeUART(USART_GPIO, Rx_GPIO_Pin);
	//时钟16MHZ
	UARTClockSourceSet(USART, UART_CLOCK_PIOSC);	//1
	//115200  8bit  无奇偶校验为  1个停止位
	UARTStdioConfig(USART_Num, USART_Bound, 16000000);	//2 步骤一二只能用于 UART0~2。同时也可以使用UARTprintf打印函数
//	UARTConfigSetExpClk(USART, SysCtlClockGet(), 115200,	
//						(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));	//可用于所有串口 ，不能使用UARTprintf打印函数
	//以上两个函数都包含了串口使能函数
	//UARTEnable(USART);
	
	//串口接收DMA使能
//	UARTDMAEnable(USART, UART_DMA_RX);
}

void Interrupt_Config(void){
	//开启总中断
	IntMasterEnable();
	//开启串口中断
	IntEnable(USART_Int);
	//串口接收中断使能
	UARTIntEnable(USART, UART_INT_RX);
	//FIFO缓冲区禁止
//	UARTFIFODisable(USART);
	
	//FIFO缓冲区使能
	UARTFIFOEnable(USART);
	UARTFIFOLevelSet(USART, UART_FIFO_TX2_8, UART_FIFO_RX2_8);		//16为字节的缓冲区
	
	//串口中断函数注册
	UARTIntRegister(USART, UART_RxHandler);
	//串口中断优先级设置
	IntPrioritySet(USART_Int, 0);
}

void UART_DMA_Config(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	uDMAChannelAssign(UDMA_CH8_UART1RX);
	uDMAEnable();
	uDMAControlBaseSet(ui8ControlTable);

    UARTDMAEnable(UART1_BASE, UART_DMA_RX);
//		环回模式
//    HWREG(UART1_BASE + UART_O_CTL) |= UART_CTL_LBE;

	//禁用DMA通道    UART2RX通道     备用通道|突发事件请求|高优先级|外设不能发出DMA请求
    uDMAChannelAttributeDisable(UDMA_CHANNEL_UART1RX,
                                    UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);
	//DMA通道控制块设置    通道|主控制块  ，传输数据大小|源地址增量|目的地址增量|仲裁项目数量
    uDMAChannelControlSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
                              UDMA_ARB_4);
	//DMA通道控制块设置    通道|副控制块  ，传输数据大小|源地址增量|目的地址增量|仲裁项目数量
//    uDMAChannelControlSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
//                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
//                              UDMA_ARB_4);
	//设置DMA通道控制参数  通道|主控制块，乒乓模式，源地址，目的地址，传输数据大小
    uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)(UART1_BASE + UART_O_DR),
                               g_ui8RxBufA, sizeof(g_ui8RxBufA));
	//设置DMA通道控制参数  通道|副控制块，乒乓模式，源地址，目的地址，传输数据大小
//    uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
//                               UDMA_MODE_PINGPONG,
//                               (void *)(UART1_BASE + UART_O_DR),
//                               g_ui8RxBufB, sizeof(g_ui8RxBufB));
							   
	//使能并配置DMA通道    通道，只响应突发事件请求|相应用到使用主控制块|默认优先级|外设可以产生DMA运输请求
    uDMAChannelAttributeEnable(UDMA_CHANNEL_UART1RX, UDMA_ATTR_USEBURST);
	
	//DMA通道使能
    uDMAChannelEnable(UDMA_CHANNEL_UART1RX);
	IntEnable(INT_UDMA);						 
	uDMAIntRegister(UDMA_INT_SW, Dma_Handler);
	//发起软件请求
//	uDMAChannelRequest(UDMA_CHANNEL_UART1RX)
//	uDMAChannelAssign();
}

void UART_Config(void){
	USART_Init();
	
	Interrupt_Config();
	
	UART_DMA_Config();
	UARTprintf("%d\r\n",g_ui8RxBufA[0]);
	UARTprintf("%d\r\n",g_ui8RxBufB[0]);
}
uint32_t cntA = 0;
uint32_t cntB = 0;
void UART_RxHandler(void){
	uint32_t Rxdata;
	uint32_t Txdata;
	uint32_t states = UARTIntStatus(USART, 1);
	UARTIntClear(USART, states);
	if(states & 0x0040){		//超时中断处理
		uDMAChannelRequest(UDMA_CHANNEL_UART1RX);
		Rxdata = UARTCharGetNonBlocking(USART);
		UARTprintf("%d\r\n",Rxdata);
	}
	else if(states & 0x0010){	//接收中断处理
		
		
////		UARTprintf("%d\r\n",states);
//		while(UARTCharsAvail(USART)==true){				//判断FIFO缓冲区中是否有数据
//			Rxdata = UARTCharGetNonBlocking(USART);		//获取数据，好像会自动清楚
//			UARTprintf("%d\r\n",Rxdata);
//		}
//		UARTprintf("hello\r\n");
//		Rxdata = UARTCharGetNonBlocking(USART);
//		UARTprintf("%d\r\n",Rxdata);
		
		
		
		UARTprintf("hello\r\n");
		uint32_t ui32Status;
		uint32_t ui32Mode;

		ui32Mode = uDMAChannelModeGet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT);

		if(ui32Mode == UDMA_MODE_STOP)
		{
			UARTprintf("1\r\n");
			cntA++;

			uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
									   UDMA_MODE_PINGPONG,
									   (void *)(UART1_BASE + UART_O_DR),
									   g_ui8RxBufA, sizeof(g_ui8RxBufA));
			uDMAChannelEnable(UDMA_CHANNEL_UART1RX);
		}

//		ui32Mode = uDMAChannelModeGet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT);

//    
//		if(ui32Mode == UDMA_MODE_STOP)
//		{
//			cntB++;

//			uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
//									   UDMA_MODE_PINGPONG,
//									   (void *)(UART1_BASE + UART_O_DR),
//									   g_ui8RxBufB, sizeof(g_ui8RxBufB));
//		}
		
		uDMAChannelRequest(UDMA_CHANNEL_UART1RX);
		
	}
}
//uint32_t cnt = 0;
void Dma_Handler(void){
	UARTprintf("dma handler\r\n");
	for(int i=0;i<50;i++){
		UARTprintf("%d\r\n",g_ui8RxBufA[i]);
		UARTprintf("%d\r\n",g_ui8RxBufB[i]);
	}
//	uint32_t ui32Mode;
//	UARTprintf("dma handler\r\n");
//	ui32Mode = uDMAChannelModeGet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT);
//	if(ui32Mode == UDMA_MODE_STOP)
//	{
//		UARTprintf("%d\r\n",g_ui8RxBufA[cntA++]);
////		g_ui8RxBufA[0] = 0;
//	}
//	ui32Mode = uDMAChannelModeGet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT);
//	if(ui32Mode == UDMA_MODE_STOP)
//	{
//		UARTprintf("%d\r\n",g_ui8RxBufB[cntB++]);
////		g_ui8RxBufB[0] = 0;
//	}
}


/************printf重定向相关**************/
int fputc(int ch, FILE *f)
{
	UARTCharPut(USART, (char)ch);
	return ch;
}

int fgetc(FILE *f)
{
  uint8_t ch = 0;
  ch = UARTCharGet(USART);
  return ch;
}

