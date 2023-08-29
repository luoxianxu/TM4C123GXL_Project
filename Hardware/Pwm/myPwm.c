
#include "myPwm.h"

void Pwm_Config(void){
	SysCtlPeripheralEnable(PWM_SYSCTL_PERIPH);	//enable pwm
	SysCtlPeripheralEnable(PWMGPIO_SYSCTL_PERIPH);	//enable gpio
	
	//����GPIOΪPWM
	GPIOPinConfigure(PWMGPIO_Mode);
	GPIOPinTypePWM(PWMGPIO, PWMGPIO_Pin);
	//����PWMʱ��
	SysCtlPWMClockSet(SYSCTL_PWMDIV_2);
	
	//PWM���ģʽ����
//	PWMGenConfigure(PWM, PWM_GEN, PWM_GEN_MODE_DOWN);
	PWMGenConfigure(PWM, PWM_GEN, PWM_GEN_MODE_UP_DOWN);
	//PWM��������
	PWMGenPeriodSet(PWM, PWM_GEN, 30000);
	
	//�Ƚ�ֵ����
	PWMPulseWidthSet(PWM, PWM_OUT, PWMGenPeriodGet(PWM, PWM_GEN)/3);
	//PWM���ͨ��ʹ��
	PWMOutputState(PWM, PWM_OUT_Bit, true);
	//PWMʹ��
	PWMGenEnable(PWM, PWM_GEN);
	
}
