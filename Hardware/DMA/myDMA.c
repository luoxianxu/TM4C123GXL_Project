#include "myDMA.h"

char g_ui8RxBuf[64] = {0};
static uint8_t ControlTable[1024] __attribute__ ((aligned(1024)));

//void DMA_IntHandler(void){
//	uint32_t state = uDMAIntStatus();
//	if(state & )
//}
void DMA_Config(void){
	//DMAʱ��ʹ��
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	uDMAEnable();
	uDMAControlBaseSet(&ControlTable);
	
	
	//�ж�����
//	IntMasterEnable();
//	IntEnable(INT_UDMA);
//	
//	uDMAIntRegister(UDMA_INT_SW, DMA_IntHandler);
}

void USART_DMA_Config(void){
	//ѡ�񴮿�����ΪDMAͨ��
	uDMAChannelAssign(DMA_CH);
	
//	uDMAChannelControlSet(ChannelStructIndex,Control);
	
	//�������    ���ͨ�����ã�ͨ������Ϊ��Ӧ��������ͻ������  ���ÿ��ƿ�Ϊ�����ƿ�   ʹ��Ĭ�����ȼ�  ͨ������DMA����
    uDMAChannelAttributeDisable(DMA_Channel,
									UDMA_ATTR_USEBURST|
                                    UDMA_ATTR_ALTSELECT |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);
	//���������ƿ����    ͨ��ѡ�������ƿ�     8λ    Դ��ַ������   Ŀ�ĵ�ַ����8λ
    uDMAChannelControlSet(DMA_Channel | UDMA_PRI_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
                              UDMA_ARB_1);
	//���ø����ƿ����
    uDMAChannelControlSet(DMA_Channel | UDMA_ALT_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
                              UDMA_ARB_1);
	
	//�����ƿ鷢������     ƹ��ģʽ   Դ��ַ   Ŀ�ĵ�ַ
    uDMAChannelTransferSet(DMA_Channel | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)DMA_SRC,
                               g_ui8RxBuf, 1);
	//�����ƿ鷢������						   
    uDMAChannelTransferSet(DMA_Channel | UDMA_ALT_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)DMA_SRC,
                               g_ui8RxBuf, 1);
	// 										ͻ���������       �����ȼ�
    uDMAChannelAttributeEnable(DMA_Channel, UDMA_ATTR_USEBURST|UDMA_ATTR_HIGH_PRIORITY);
    //ͨ��ʹ��
	uDMAChannelEnable(DMA_Channel);
}

