
#include "myEncorder.h"

void Encorder_Config(void){
	//ʱ��ʹ��
	SysCtlPeripheralEnable(Encorder1_SYSCTL_PERIPH);
	SysCtlPeripheralEnable(Encorder1GPIO_SYSCTL_PERIPH);
	
	//GPIO����
	GPIOPinConfigure(Encorder1_PHA);
	GPIOPinConfigure(Encorder1_PHB);
	GPIOPinTypeQEI(Encorder1_GPIO, Encorder1_A_GPIOPin);
	GPIOPinTypeQEI(Encorder1_GPIO, Encorder1_B_GPIOPin);
	
	//������ģʽ���� 	    ����ΪA��B��֮�����   �����ﵽ���ֵʱ��λ  A��B������          A��B�಻���� 		�������
	QEIConfigure(Encorder1, QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE|QEI_CONFIG_NO_SWAP, 5000);
	//���ñ������ĳ�ʼֵ
	QEIPositionSet(Encorder1, 1000);		//���ó�ʼֵ
	//������ʹ��
	QEIEnable(Encorder1);
	
	//�������������Ƶ�ʣ�����  �����ٶȼ��
//	QEIVelocityConfigure(Encorder1, QEI_VELDIV_2, SysCtlClockGet());
//	QEIVelocityEnable(Encorder1);
//	QEIEnable(Encorder1);

}

