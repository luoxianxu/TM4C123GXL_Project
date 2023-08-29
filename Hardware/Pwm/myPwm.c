
#include "myPwm.h"

void Pwm_Config(void){
	SysCtlPeripheralEnable(PWM_SYSCTL_PERIPH);	//enable pwm
	SysCtlPeripheralEnable(PWMGPIO_SYSCTL_PERIPH);	//enable gpio
	
	//配置GPIO为PWM
	GPIOPinConfigure(PWMGPIO_Mode);
	GPIOPinTypePWM(PWMGPIO, PWMGPIO_Pin);
	//配置PWM时钟
	SysCtlPWMClockSet(SYSCTL_PWMDIV_2);
	
	//PWM输出模式设置
//	PWMGenConfigure(PWM, PWM_GEN, PWM_GEN_MODE_DOWN);
	PWMGenConfigure(PWM, PWM_GEN, PWM_GEN_MODE_UP_DOWN);
	//PWM周期设置
	PWMGenPeriodSet(PWM, PWM_GEN, 30000);
	
	//比较值设置
	PWMPulseWidthSet(PWM, PWM_OUT, PWMGenPeriodGet(PWM, PWM_GEN)/3);
	//PWM输出通道使能
	PWMOutputState(PWM, PWM_OUT_Bit, true);
	//PWM使能
	PWMGenEnable(PWM, PWM_GEN);
	
}
