
#include "myEncorder.h"

void Encorder_Config(void){
	//时钟使能
	SysCtlPeripheralEnable(Encorder1_SYSCTL_PERIPH);
	SysCtlPeripheralEnable(Encorder1GPIO_SYSCTL_PERIPH);
	
	//GPIO配置
	GPIOPinConfigure(Encorder1_PHA);
	GPIOPinConfigure(Encorder1_PHB);
	GPIOPinTypeQEI(Encorder1_GPIO, Encorder1_A_GPIOPin);
	GPIOPinTypeQEI(Encorder1_GPIO, Encorder1_B_GPIOPin);
	
	//编码器模式配置 	    配置为A和B相之间采样   计数达到最大值时复位  A和B相正交          A和B相不交换 		最大量程
	QEIConfigure(Encorder1, QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE|QEI_CONFIG_NO_SWAP, 5000);
	//设置编码器的初始值
	QEIPositionSet(Encorder1, 1000);		//设置初始值
	//编码器使能
	QEIEnable(Encorder1);
	
	//配置正交脉冲的频率，周期  用于速度检测
//	QEIVelocityConfigure(Encorder1, QEI_VELDIV_2, SysCtlClockGet());
//	QEIVelocityEnable(Encorder1);
//	QEIEnable(Encorder1);

}

