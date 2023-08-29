
#include "rgb.h"

void Rgb_Init(void){
	//时钟使能
	SysCtlPeripheralEnable(RGBSYSCTL_Peripheral);
	//引脚输出模式配置
	GPIOPinTypeGPIOOutput(RGB_GPIO, RGB1GPIO_Pin | RGB2GPIO_Pin | RGB3GPIO_Pin);
	//输出引脚值设置
	GPIOPinWrite(GPIO_PORTF_BASE, RGB1GPIO_Pin | RGB2GPIO_Pin | RGB3GPIO_Pin, RGB1GPIO_Pin);
}
