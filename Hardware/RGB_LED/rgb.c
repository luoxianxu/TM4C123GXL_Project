
#include "rgb.h"

void Rgb_Init(void){
	//ʱ��ʹ��
	SysCtlPeripheralEnable(RGBSYSCTL_Peripheral);
	//�������ģʽ����
	GPIOPinTypeGPIOOutput(RGB_GPIO, RGB1GPIO_Pin | RGB2GPIO_Pin | RGB3GPIO_Pin);
	//�������ֵ����
	GPIOPinWrite(GPIO_PORTF_BASE, RGB1GPIO_Pin | RGB2GPIO_Pin | RGB3GPIO_Pin, RGB1GPIO_Pin);
}
