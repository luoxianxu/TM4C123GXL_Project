#include "myDMA.h"

char g_ui8RxBuf[64] = {0};
static uint8_t ControlTable[1024] __attribute__ ((aligned(1024)));

//void DMA_IntHandler(void){
//	uint32_t state = uDMAIntStatus();
//	if(state & )
//}
void DMA_Config(void){
	//DMA时钟使能
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	uDMAEnable();
	uDMAControlBaseSet(&ControlTable);
	
	
	//中断配置
//	IntMasterEnable();
//	IntEnable(INT_UDMA);
//	
//	uDMAIntRegister(UDMA_INT_SW, DMA_IntHandler);
}

void USART_DMA_Config(void){
	//选择串口设置为DMA通道
	uDMAChannelAssign(DMA_CH);
	
//	uDMAChannelControlSet(ChannelStructIndex,Control);
	
	//清除配置    清除通道配置，通道配置为响应单个或者突发请求  设置控制块为主控制块   使用默认优先级  通道启用DMA传输
    uDMAChannelAttributeDisable(DMA_Channel,
									UDMA_ATTR_USEBURST|
                                    UDMA_ATTR_ALTSELECT |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);
	//配置主控制块参数    通道选择主控制块     8位    源地址不增长   目的地址增长8位
    uDMAChannelControlSet(DMA_Channel | UDMA_PRI_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
                              UDMA_ARB_1);
	//配置副控制块参数
    uDMAChannelControlSet(DMA_Channel | UDMA_ALT_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
                              UDMA_ARB_1);
	
	//主控制块发送设置     乒乓模式   源地址   目的地址
    uDMAChannelTransferSet(DMA_Channel | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)DMA_SRC,
                               g_ui8RxBuf, 1);
	//副控制块发送设置						   
    uDMAChannelTransferSet(DMA_Channel | UDMA_ALT_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)DMA_SRC,
                               g_ui8RxBuf, 1);
	// 										突发情况触发       高优先级
    uDMAChannelAttributeEnable(DMA_Channel, UDMA_ATTR_USEBURST|UDMA_ATTR_HIGH_PRIORITY);
    //通道使能
	uDMAChannelEnable(DMA_Channel);
}

