
#include "key.h"
#include "rgb.h"
#include "utils/uartstdio.h"

void Key_Config(void){
	//时钟使能
	SysCtlPeripheralEnable(KeySYSCTL_Peripheral);
//	HWREG(Key2GPIO +  GPIO_O_LOCK) = 0;
	
	//解锁PF0
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;//解锁
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;


	
	//GPIO_Pin设置为输入
	GPIOPinTypeGPIOInput(Key1GPIO, Key1GPIO_Pin);	//sw1
	GPIOPinTypeGPIOInput(Key2GPIO, Key2GPIO_Pin);	//sw2
	//选择引脚模式
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
	
	
//	配置GPIOIS寄存器  选择中断源  边缘触发
//	HWREG(SYSCTL_PERIPH_GPIOF + GPIO_O_IS) &= ~0x10;
//	//选择由GPIOIEV寄存器选择中断
//	HWREG(SYSCTL_PERIPH_GPIOF + GPIO_O_IBE) &= ~0x10;
//	//配置GPIOIEV寄存器 选择下降沿触发中断
//	HWREG(SYSCTL_PERIPH_GPIOF + GPIO_O_IEV) &= ~0x10;
	
	//中断使能
    IntMasterEnable();
    //GPIOF中断使能
    IntEnable(Key_IntGPIO);
	//中断配置，下降沿触发
	GPIOIntTypeSet(Key1GPIO, Key1GPIO_Pin,GPIO_FALLING_EDGE);
	GPIOIntTypeSet(Key1GPIO, Key2GPIO_Pin,GPIO_FALLING_EDGE);
	//引脚中断使能
	GPIOIntEnable(Key1GPIO, Key1_GPIOIntPin);
	GPIOIntEnable(Key1GPIO, Key2_GPIOIntPin);
	//注册中断处理函数
	GPIOIntRegister(Key1GPIO, SW2_Handler);
	//清除中断标志位
	GPIOIntClear(Key1GPIO, Key1_GPIOIntPin);
	GPIOIntClear(Key1GPIO, Key2_GPIOIntPin);
	
	//中断优先级设置
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
