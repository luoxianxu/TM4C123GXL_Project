
#include "key.h"
#include "rgb.h"
#include "utils/uartstdio.h"

void Key_Config(void){
	//ʱ��ʹ��
	SysCtlPeripheralEnable(KeySYSCTL_Peripheral);
//	HWREG(Key2GPIO +  GPIO_O_LOCK) = 0;
	
	//����PF0
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;//����
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;


	
	//GPIO_Pin����Ϊ����
	GPIOPinTypeGPIOInput(Key1GPIO, Key1GPIO_Pin);	//sw1
	GPIOPinTypeGPIOInput(Key2GPIO, Key2GPIO_Pin);	//sw2
	//ѡ������ģʽ
	GPIOPadConfigSet(Key1GPIO, Key1GPIO_Pin,GPIO_STRENGTH_2MA, KeyPinMode);
	GPIOPadConfigSet(Key2GPIO, Key2GPIO_Pin,GPIO_STRENGTH_2MA, KeyPinMode);
}

void Key_Detect(void){
	if(GPIOPinRead(Key2GPIO, Key2GPIO_Pin)==0){
		GPIOPinWrite(Key2GPIO, RGB1GPIO_Pin | RGB2GPIO_Pin | RGB3GPIO_Pin, RGB2GPIO_Pin);
	}
	if(GPIOPinRead(Key1GPIO, Key1GPIO_Pin)==0){
		GPIOPinWrite(Key1GPIO, RGB1GPIO_Pin | RGB2GPIO_Pin | RGB3GPIO_Pin, RGB2GPIO_Pin);
	}
}

void Key_Interrupt_Config(void){
	
	
//	����GPIOIS�Ĵ���  ѡ���ж�Դ  ��Ե����
//	HWREG(SYSCTL_PERIPH_GPIOF + GPIO_O_IS) &= ~0x10;
//	//ѡ����GPIOIEV�Ĵ���ѡ���ж�
//	HWREG(SYSCTL_PERIPH_GPIOF + GPIO_O_IBE) &= ~0x10;
//	//����GPIOIEV�Ĵ��� ѡ���½��ش����ж�
//	HWREG(SYSCTL_PERIPH_GPIOF + GPIO_O_IEV) &= ~0x10;
	
	//�ж�ʹ��
    IntMasterEnable();
    //GPIOF�ж�ʹ��
    IntEnable(Key_IntGPIO);
	//�ж����ã��½��ش���
	GPIOIntTypeSet(Key1GPIO, Key1GPIO_Pin,GPIO_FALLING_EDGE);
	GPIOIntTypeSet(Key1GPIO, Key2GPIO_Pin,GPIO_FALLING_EDGE);
	//�����ж�ʹ��
	GPIOIntEnable(Key1GPIO, Key1_GPIOIntPin);
	GPIOIntEnable(Key1GPIO, Key2_GPIOIntPin);
	//ע���жϴ�����
	GPIOIntRegister(Key1GPIO, SW2_Handler);
	//����жϱ�־λ
	GPIOIntClear(Key1GPIO, Key1_GPIOIntPin);
	GPIOIntClear(Key1GPIO, Key2_GPIOIntPin);
	
	//�ж����ȼ�����
	IntPrioritySet(Key_IntGPIO, 0);
}

void SW2_Handler(void){
	uint8_t status = 0;
	status = GPIOIntStatus(Key1GPIO, 1);
	
	GPIOIntClear(Key1GPIO, status);
	if(status & GPIO_INT_PIN_4){
		UARTprintf("hello\r\n");
		GPIOPinWrite(Key1GPIO, RGB1GPIO_Pin | RGB2GPIO_Pin | RGB3GPIO_Pin, RGB3GPIO_Pin);
	}
	if(status & GPIO_INT_PIN_0){
		GPIOPinWrite(Key1GPIO, RGB1GPIO_Pin | RGB2GPIO_Pin | RGB3GPIO_Pin, RGB2GPIO_Pin);
	}
}
