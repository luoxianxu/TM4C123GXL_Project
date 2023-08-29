
#include "myTimer.h"
#include "usart.h"
#include "myEncorder.h"
#include "myAdc.h"
#include "myDMA.h"

extern char g_ui8RxBuf[64];

void Timer_Config(void){
	SysCtlPeripheralEnable(TimerSYSCTL_Peripheral);
	
	//循环计数   配置定时器的位数
	TimerConfigure(Timer, TIMER_CFG_PERIODIC);
	TimerLoadSet(Timer, TimerX, SysCtlClockGet()/50-1);
	
	//定时器超时中断使能
	TimerIntEnable(Timer, TIMER_TIMA_TIMEOUT);
	//定时器中断服务函数注册
	TimerIntRegister(Timer, TimerX, Timer_Handler);
	//定时器中断使能
	IntEnable(Timer_Interrupt);
	//使能总中断
	IntMasterEnable();
	//定时器使能
	TimerEnable(Timer, TimerX);
	
}


void Timer_PWM_Config(void){
	SysCtlPeripheralEnable(PwmTimerSYSCTL_Peripheral);
	SysCtlPeripheralEnable(PwmGPIOSYSCTL_Peripheral);
	
	GPIOPinConfigure(PwmPin1Config);
	GPIOPinTypeTimer(PwmGPIO, PwmGPIO_Pin1);
//	//PWM模式   
	TimerConfigure(PwmTimer, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);
//	//设置初始值  递减计数    选择PwmTimerX作为时钟信号或者触发信号
	TimerLoadSet(PwmTimer,PwmTimerX,30000);
	//设置比较值
	TimerMatchSet(PwmTimer,PwmTimerX,10000);

	TimerEnable(PwmTimer, PwmTimerX);
	//设置翻转
	HWREG(PwmTimer + 0x000C) |= 0x40;
	
}

void Capture_Init(void){
	//使能TIMER1
	SysCtlPeripheralEnable(SYSCTL_PERIPH_Capture_TIMER);
	//使能GPIOB
	SysCtlPeripheralEnable(SYSCTL_PERIPH_Capture_GPIO);
  //使能引脚复用
	GPIOPinConfigure(Capture_GPIOPinConfig);	
  //将PB4复用为定时器功能
	GPIOPinTypeTimer(Capture_GPIO,Capture_GPIO_Pin);		
  //设置引脚为硬件控制
	GPIODirModeSet(Capture_GPIO,Capture_GPIO_Pin,Capture_GPIO_Mode);
  //设置为推挽上拉输入
	GPIOPadConfigSet(Capture_GPIO,Capture_GPIO_Pin,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
  //A定时器捕获模式				两个半宽|向上计数捕获
	TimerConfigure(Capture_Timer,TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_CAP_TIME_UP);
//  //B定时器定时模式
//	TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC_UP);
//	//A定时器默认装载65535
//  TimerLoadSet(TIMER1_BASE,TIMER_A,65535);
//	//为B定时器也装载65535
//  TimerLoadSet(TIMER1_BASE,TIMER_B,SysCtlClockGet()/10000-1);	
  //注册定时器A中断函数
	TimerIntRegister(Capture_Timer,TIMER_A,Timer_Capture_Handler);
//  //注册定时器B中断函数
//	TimerIntRegister(TIMER1_BASE,TIMER_B,TIMER1B_IRQHandler);	
  //使能定时器A中断的捕获中断
	TimerIntEnable(Capture_Timer,TIMER_CAPA_EVENT);
//  //使能定时器B中断的计时中断
//	TimerIntEnable(TIMER1_BASE,TIMER_TIMB_TIMEOUT);
  //设置中断优先级
	IntPrioritySet(Capture_Timer_INT,0x03);
//  //设置中断优先级
//	IntPrioritySet(INT_TIMER1B,0x04);			
	//定时器A设置为上升沿触发
	TimerControlEvent(Capture_Timer,TIMER_A,TIMER_EVENT_POS_EDGE);
//	//定时器B设置为超时触发
//	TimerControlEvent(TIMER1_BASE,TIMER_B,TIMER_TIMB_TIMEOUT);
  //使能定时器A中断
	IntEnable(Capture_Timer_INT);
//  //使能定时器B中断
//	IntEnable(INT_TIMER1B);	
	TimerEnable(Capture_Timer,TIMER_A);
//	//两个定时器同时开启
//	TimerEnable(TIMER1_BASE,TIMER_BOTH);
	IntMasterEnable();
}

void Timer_Handler(void){
	uint32_t states = TimerIntStatus(Timer, 1);
	TimerIntClear(Timer, states);
	if(states & 0x0001){
//		uint32_t cnt = QEIPositionGet(Encorder1);
//		QEIPositionSet(Encorder1, 1000);		//设置初始值
		ADCProcessorTrigger(ADC0_BASE, 0);
//		UARTprintf("position = %d \n", QEIPositionGet(QEI1_BASE));
//		UARTprintf("velocity = %d \n\n", QEIVelocityGet(QEI1_BASE) * QEIDirectionGet(QEI1_BASE));
//		UARTprintf("%d\r\n",cnt-1000);
//		UARTprintf("hello\r\n");
//		UARTprintf(g_ui8RxBuf);
	}
}

//以下两个变量可以使用 extern 直接引用，其会在每一次捕获完成后自动更新
//输入捕获算出的频率(Hz)
uint32_t freq=0;
//输入捕获算出的占空比(%)
//uint32_t duty=0;
float duty=0;
uint32_t timer_flag=0;
uint32_t capture_1=0,capture_2=0,capture_3=0;
uint32_t up_count=0,down_count=0;
void Timer_Capture_Handler(void){
	//读取中断状态
	uint32_t status=TimerIntStatus(Capture_Timer,true);
	//清除中断标志位
	TimerIntClear(Capture_Timer,status);
//	printf("%d\r\n",status);
	//第一次进中断(上升沿)
	if(timer_flag==0){
		//配置为下降沿捕获
		TimerControlEvent(Capture_Timer,TIMER_A,TIMER_EVENT_NEG_EDGE);
		capture_1=TimerValueGet(Capture_Timer,TIMER_A);
		timer_flag=1;
	}
	//第二次进中断(下降沿)，此时可以得出高电平持续时间
	else if(timer_flag==1){
		TimerControlEvent(Capture_Timer,TIMER_A,TIMER_EVENT_POS_EDGE);	//上升沿捕获
		capture_2=TimerValueGet(Capture_Timer,TIMER_A);
		timer_flag=2;
	}
	//第三次进中断(上升沿)，此时可以得出频率和占空比
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
		//频率用主频除周期即可得到
		freq=SysCtlClockGet()/(up_count+down_count);
		//占空比为高电平占周期的比值即可得到
		duty=(float)up_count/(up_count+down_count);
//		UARTprintf("%d\r\n",(uint32_t)duty);
	}
}
