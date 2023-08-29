
#include "myEEPROM.h"
uint32_t Rdata[1] = {0};
uint32_t Wdata[1] = {0x12};
void EEPROM_Config(void){
	//ʱ��ʹ��
	SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM);
	//���ڼ��EEPROM�еĴ���
	if(EEPROMInit() != EEPROM_INIT_OK)
		return;
	//д������   ����Դ  ��ַ    ��С
	EEPROMProgram(Wdata, 0, 1*4);
	//��ȡ����   Ŀ�ĵ�ַ   eeprom�ĵ�ַ   ��С
	EEPROMRead(Rdata, 0,1*4);
	UARTprintf("EEPROM Read data:%d\r\n",*Rdata);
}

