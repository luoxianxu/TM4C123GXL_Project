
#include "usart.h"
uint8_t ui8ControlTable[1024] __attribute__ ((aligned(1024)));

uint8_t g_ui8TxBuf[10]={0};
uint8_t g_ui8RxBufA[50]={0};
uint8_t g_ui8RxBufB[50]={0};
void USART_Init(void){
	//����ʱ��ʹ��
	SysCtlPeripheralEnable(USART_Peripheral);
	//����GPIOʹ��
	SysCtlPeripheralEnable(USART_GPIOPeripheral);
	
	//����PD7
//	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
//    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= (1<<7);//����
//    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
	//��������ΪPPģʽ
	GPIOPinConfigure(Tx_PinConfig);
	GPIOPinConfigure(Rx_PinConfig);
	
	//GPIO ����ģʽ����
	GPIOPinTypeUART(USART_GPIO, Tx_GPIO_Pin);
	GPIOPinTypeUART(USART_GPIO, Rx_GPIO_Pin);
	//ʱ��16MHZ
	UARTClockSourceSet(USART, UART_CLOCK_PIOSC);	//1
	//115200  8bit  ����żУ��Ϊ  1��ֹͣλ
	UARTStdioConfig(USART_Num, USART_Bound, 16000000);	//2 ����һ��ֻ������ UART0~2��ͬʱҲ����ʹ��UARTprintf��ӡ����
//	UARTConfigSetExpClk(USART, SysCtlClockGet(), 115200,	
//						(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));	//���������д��� ������ʹ��UARTprintf��ӡ����
	//�������������������˴���ʹ�ܺ���
	//UARTEnable(USART);
	
	//���ڽ���DMAʹ��
//	UARTDMAEnable(USART, UART_DMA_RX);
}

void Interrupt_Config(void){
	//�������ж�
	IntMasterEnable();
	//���������ж�
	IntEnable(USART_Int);
	//���ڽ����ж�ʹ��
	UARTIntEnable(USART, UART_INT_RX);
	//FIFO��������ֹ
//	UARTFIFODisable(USART);
	
	//FIFO������ʹ��
	UARTFIFOEnable(USART);
	UARTFIFOLevelSet(USART, UART_FIFO_TX2_8, UART_FIFO_RX2_8);		//16Ϊ�ֽڵĻ�����
	
	//�����жϺ���ע��
	UARTIntRegister(USART, UART_RxHandler);
	//�����ж����ȼ�����
	IntPrioritySet(USART_Int, 0);
}

void UART_DMA_Config(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	uDMAChannelAssign(UDMA_CH8_UART1RX);
	uDMAEnable();
	uDMAControlBaseSet(ui8ControlTable);

    UARTDMAEnable(UART1_BASE, UART_DMA_RX);
//		����ģʽ
//    HWREG(UART1_BASE + UART_O_CTL) |= UART_CTL_LBE;

	//����DMAͨ��    UART2RXͨ��     ����ͨ��|ͻ���¼�����|�����ȼ�|���費�ܷ���DMA����
    uDMAChannelAttributeDisable(UDMA_CHANNEL_UART1RX,
                                    UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);
	//DMAͨ�����ƿ�����    ͨ��|�����ƿ�  ���������ݴ�С|Դ��ַ����|Ŀ�ĵ�ַ����|�ٲ���Ŀ����
    uDMAChannelControlSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
                              UDMA_ARB_4);
	//DMAͨ�����ƿ�����    ͨ��|�����ƿ�  ���������ݴ�С|Դ��ַ����|Ŀ�ĵ�ַ����|�ٲ���Ŀ����
//    uDMAChannelControlSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
//                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
//                              UDMA_ARB_4);
	//����DMAͨ�����Ʋ���  ͨ��|�����ƿ飬ƹ��ģʽ��Դ��ַ��Ŀ�ĵ�ַ���������ݴ�С
    uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)(UART1_BASE + UART_O_DR),
                               g_ui8RxBufA, sizeof(g_ui8RxBufA));
	//����DMAͨ�����Ʋ���  ͨ��|�����ƿ飬ƹ��ģʽ��Դ��ַ��Ŀ�ĵ�ַ���������ݴ�С
//    uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
//                               UDMA_MODE_PINGPONG,
//                               (void *)(UART1_BASE + UART_O_DR),
//                               g_ui8RxBufB, sizeof(g_ui8RxBufB));
							   
	//ʹ�ܲ�����DMAͨ��    ͨ����ֻ��Ӧͻ���¼�����|��Ӧ�õ�ʹ�������ƿ�|Ĭ�����ȼ�|������Բ���DMA��������
    uDMAChannelAttributeEnable(UDMA_CHANNEL_UART1RX, UDMA_ATTR_USEBURST);
	
	//DMAͨ��ʹ��
    uDMAChannelEnable(UDMA_CHANNEL_UART1RX);
	IntEnable(INT_UDMA);						 
	uDMAIntRegister(UDMA_INT_SW, Dma_Handler);
	//�����������
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
	if(states & 0x0040){		//��ʱ�жϴ���
		uDMAChannelRequest(UDMA_CHANNEL_UART1RX);
		Rxdata = UARTCharGetNonBlocking(USART);
		UARTprintf("%d\r\n",Rxdata);
	}
	else if(states & 0x0010){	//�����жϴ���
		
		
////		UARTprintf("%d\r\n",states);
//		while(UARTCharsAvail(USART)==true){				//�ж�FIFO���������Ƿ�������
//			Rxdata = UARTCharGetNonBlocking(USART);		//��ȡ���ݣ�������Զ����
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


/************printf�ض������**************/
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

