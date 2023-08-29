
#include "myEEPROM.h"
uint32_t Rdata[1] = {0};
uint32_t Wdata[1] = {0x12};
void EEPROM_Config(void){
	//时钟使能
	SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM);
	//用于检查EEPROM中的错误
	if(EEPROMInit() != EEPROM_INIT_OK)
		return;
	//写入数据   数据源  地址    大小
	EEPROMProgram(Wdata, 0, 1*4);
	//读取数据   目的地址   eeprom的地址   大小
	EEPROMRead(Rdata, 0,1*4);
	UARTprintf("EEPROM Read data:%d\r\n",*Rdata);
}

