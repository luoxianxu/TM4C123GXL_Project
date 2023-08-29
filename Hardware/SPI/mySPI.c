
#include "mySPI.h"

void SPI_Config(void){
	//时钟使能
	SysCtlPeripheralEnable(SPI_SYSCTL_PERIPH);
	SysCtlPeripheralEnable(SPIGPIO_SYSCTL_PERIPH);
	//GPIO复用
	GPIOPinConfigure(SPI_CLK);
	GPIOPinConfigure(SPI_FSS);
	GPIOPinConfigure(SPI_RX);
	GPIOPinConfigure(SPI_TX);
	GPIOPinTypeSSI(SPI_GPIO, SPICLKGPIO_Pin);
	GPIOPinTypeSSI(SPI_GPIO, SPIFSSGPIO_Pin);
	GPIOPinTypeSSI(SPI_GPIO, SPIRXGPIO_Pin);
	GPIOPinTypeSSI(SPI_GPIO, SPITXGPIO_Pin);
	
	//                       系统时钟  时钟线初始信号为低，在第一个跳变沿采样  主机模式   1M(不宜过快，否则会造成收发异常)
	SSIConfigSetExpClk(SPI, SysCtlClockGet(),SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);
	
	IntEnable(SPI_INT);
    IntMasterEnable();
	SSIIntEnable(SPI, SSI_RXTO);
	SSIIntRegister(SPI, SPI_Handler);
	SSIEnable(SPI);
}

void SPI_Write(uint8_t *data,uint8_t len){
	uint8_t i = 0;
	
	for(i=0;i<len;i++){
		SSIDataPut(SPI, data[i]);
		while(SSIBusy(SPI));
	}
//	while(SSIBusy(SPI));
}

uint32_t *SPI_Read(uint8_t len){
	uint32_t *rec;
	for(uint8_t i=0;i<len;i++){
		SSIDataGet(SPI, rec+i);
		while(SSIBusy(SPI));
	}
	return rec;
}

void SPI_Handler(void){
	uint32_t status = 0;
	uint32_t rec_data = 0;
	status = SSIIntStatus(SPI, 1);
	SSIIntClear(SPI, status);
	if(status & SSI_RXTO){
		SSIDataGetNonBlocking(SPI,&rec_data);
		UARTprintf("123 rec_data:%d\r\n",rec_data);
	}
}

