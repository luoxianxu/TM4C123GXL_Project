
#include "myTimer.h"
#include "usart.h"
#include "myEncorder.h"
#include "myAdc.h"
#include "myDMA.h"

extern char g_ui8RxBuf[64];

void Timer_Config(void){
	SysCtlPeripheralEnable(TimerSYSCTL_Peripheral);
	
	//ѭ������   ���ö�ʱ����λ��
	TimerConfigure(Timer, TIMER_CFG_PERIODIC);
	TimerLoadSet(Timer, TimerX, SysCtlClockGet()/50-1);
	
	//��ʱ����ʱ�ж�ʹ��
	TimerIntEnable(Timer, TIMER_TIMA_TIMEOUT);
	//��ʱ���жϷ�����ע��
	TimerIntRegister(Timer, TimerX, Timer_Handler);
	//��ʱ���ж�ʹ��
	IntEnable(Timer_Interrupt);
	//ʹ�����ж�
	IntMasterEnable();
	//��ʱ��ʹ��
	TimerEnable(Timer, TimerX);
	
}


void Timer_PWM_Config(void){
	SysCtlPeripheralEnable(PwmTimerSYSCTL_Peripheral);
	SysCtlPeripheralEnable(PwmGPIOSYSCTL_Peripheral);
	
	GPIOPinConfigure(PwmPin1Config);
	GPIOPinTypeTimer(PwmGPIO, PwmGPIO_Pin1);
//	//PWMģʽ   
	TimerConfigure(PwmTimer, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);
//	//���ó�ʼֵ  �ݼ�����    ѡ��PwmTimerX��Ϊʱ���źŻ��ߴ����ź�
	TimerLoadSet(PwmTimer,PwmTimerX,30000);
	//���ñȽ�ֵ
	TimerMatchSet(PwmTimer,PwmTimerX,10000);

	TimerEnable(PwmTimer, PwmTimerX);
	//���÷�ת
	HWREG(PwmTimer + 0x000C) |= 0x40;
	
}

void Capture_Init(void){
	//ʹ��TIMER1
	SysCtlPeripheralEnable(SYSCTL_PERIPH_Capture_TIMER);
	//ʹ��GPIOB
	SysCtlPeripheralEnable(SYSCTL_PERIPH_Capture_GPIO);
  //ʹ�����Ÿ���
	GPIOPinConfigure(Capture_GPIOPinConfig);	
  //��PB4����Ϊ��ʱ������
	GPIOPinTypeTimer(Capture_GPIO,Capture_GPIO_Pin);		
  //��������ΪӲ������
	GPIODirModeSet(Capture_GPIO,Capture_GPIO_Pin,Capture_GPIO_Mode);
  //����Ϊ������������
	GPIOPadConfigSet(Capture_GPIO,Capture_GPIO_Pin,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
  //A��ʱ������ģʽ				�������|���ϼ�������
	TimerConfigure(Capture_Timer,TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_CAP_TIME_UP);
//  //B��ʱ����ʱģʽ
//	TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC_UP);
//	//A��ʱ��Ĭ��װ��65535
//  TimerLoadSet(TIMER1_BASE,TIMER_A,65535);
//	//ΪB��ʱ��Ҳװ��65535
//  TimerLoadSet(TIMER1_BASE,TIMER_B,SysCtlClockGet()/10000-1);	
  //ע�ᶨʱ��A�жϺ���
	TimerIntRegister(Capture_Timer,TIMER_A,Timer_Capture_Handler);
//  //ע�ᶨʱ��B�жϺ���
//	TimerIntRegister(TIMER1_BASE,TIMER_B,TIMER1B_IRQHandler);	
  //ʹ�ܶ�ʱ��A�жϵĲ����ж�
	TimerIntEnable(Capture_Timer,TIMER_CAPA_EVENT);
//  //ʹ�ܶ�ʱ��B�жϵļ�ʱ�ж�
//	TimerIntEnable(TIMER1_BASE,TIMER_TIMB_TIMEOUT);
  //�����ж����ȼ�
	IntPrioritySet(Capture_Timer_INT,0x03);
//  //�����ж����ȼ�
//	IntPrioritySet(INT_TIMER1B,0x04);			
	//��ʱ��A����Ϊ�����ش���
	TimerControlEvent(Capture_Timer,TIMER_A,TIMER_EVENT_POS_EDGE);
//	//��ʱ��B����Ϊ��ʱ����
//	TimerControlEvent(TIMER1_BASE,TIMER_B,TIMER_TIMB_TIMEOUT);
  //ʹ�ܶ�ʱ��A�ж�
	IntEnable(Capture_Timer_INT);
//  //ʹ�ܶ�ʱ��B�ж�
//	IntEnable(INT_TIMER1B);	
	TimerEnable(Capture_Timer,TIMER_A);
//	//������ʱ��ͬʱ����
//	TimerEnable(TIMER1_BASE,TIMER_BOTH);
	IntMasterEnable();
}

void Timer_Handler(void){
	uint32_t states = TimerIntStatus(Timer, 1);
	TimerIntClear(Timer, states);
	if(states & 0x0001){
//		uint32_t cnt = QEIPositionGet(Encorder1);
//		QEIPositionSet(Encorder1, 1000);		//���ó�ʼֵ
		ADCProcessorTrigger(ADC0_BASE, 0);
//		UARTprintf("position = %d \n", QEIPositionGet(QEI1_BASE));
//		UARTprintf("velocity = %d \n\n", QEIVelocityGet(QEI1_BASE) * QEIDirectionGet(QEI1_BASE));
//		UARTprintf("%d\r\n",cnt-1000);
//		UARTprintf("hello\r\n");
//		UARTprintf(g_ui8RxBuf);
	}
}

//����������������ʹ�� extern ֱ�����ã������ÿһ�β�����ɺ��Զ�����
//���벶�������Ƶ��(Hz)
uint32_t freq=0;
//���벶�������ռ�ձ�(%)
//uint32_t duty=0;
float duty=0;
uint32_t timer_flag=0;
uint32_t capture_1=0,capture_2=0,capture_3=0;
uint32_t up_count=0,down_count=0;
void Timer_Capture_Handler(void){
	//��ȡ�ж�״̬
	uint32_t status=TimerIntStatus(Capture_Timer,true);
	//����жϱ�־λ
	TimerIntClear(Capture_Timer,status);
//	printf("%d\r\n",status);
	//��һ�ν��ж�(������)
	if(timer_flag==0){
		//����Ϊ�½��ز���
		TimerControlEvent(Capture_Timer,TIMER_A,TIMER_EVENT_NEG_EDGE);
		capture_1=TimerValueGet(Capture_Timer,TIMER_A);
		timer_flag=1;
	}
	//�ڶ��ν��ж�(�½���)����ʱ���Եó��ߵ�ƽ����ʱ��
	else if(timer_flag==1){
		TimerControlEvent(Capture_Timer,TIMER_A,TIMER_EVENT_POS_EDGE);	//�����ز���
		capture_2=TimerValueGet(Capture_Timer,TIMER_A);
		timer_flag=2;
	}
	//�����ν��ж�(������)����ʱ���Եó�Ƶ�ʺ�ռ�ձ�
	else if(timer_flag==2){
		timer_flag=0;
		capture_3=TimerValueGet( Capture_Timer,TIMER_A);
		if(capture_2>capture_1){
			up_count=capture_2-capture_1;
		}
		else{
			up_count=0xffff-capture_1+capture_2;
		}
		if(capture_3>capture_2){
			down_count=capture_3-capture_2;
		}
		else{
			down_count=0xffff-capture_2+capture_3;
		}
		//Ƶ������Ƶ�����ڼ��ɵõ�
		freq=SysCtlClockGet()/(up_count+down_count);
		//ռ�ձ�Ϊ�ߵ�ƽռ���ڵı�ֵ���ɵõ�
		duty=(float)up_count/(up_count+down_count);
//		UARTprintf("%d\r\n",(uint32_t)duty);
	}
}
