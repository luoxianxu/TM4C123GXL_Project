
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/fpu.h"
#include "key.h"
#include "rgb.h"
#include "usart.h"
#include "myTimer.h"
#include "myPwm.h"
#include "myI2C.h"
#include "mySPI.h"
#include "myDMA.h"
#include "myAdc.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "myEncorder.h"
#include "oled.h"
#include "myEEPROM.h"
//#include ""
//PD7和PF0以及PC[0:3]被lock
extern uint32_t up_count;
extern uint32_t down_count;
extern float duty;

float Get_Position(u16 times)
{
//	u16 temp_count = 0;
//	float Position_Sum = 0;
//	for(temp_count = 0;temp_count < times;temp_count++)
//	{
//		Position_Sum += ((uint32_t)up_count/(uint32_t)down_count*4098-1);
//		__nop();//
//		__nop();//小延时
//	}
//	Position_Sum = Position_Sum/times/4098*360;//计算位置信息，数值是0--360
//	UARTprintf("%d\r\n",(uint32_t)Position_Sum);
	
	float Position_Sum = 0;
	Position_Sum = duty*360;
	UARTprintf("Position_Sum = %d\r\n",(uint32_t)Position_Sum);
	/*传感器输出角度的零点调整，Angle为零点偏差值*/
	if(Position_Sum>310)
	{
			Position_Sum=Position_Sum-310;
	}
	else
	{
		Position_Sum=Position_Sum+360-310;
	}
	UARTprintf("Position_Sum = %d\r\n",(uint32_t)Position_Sum);
	return Position_Sum;
	
}

int main(){
	
	//80M
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	FPULazyStackingEnable();//使能FPU浮点运算
//	DMA_Config();
//	Rgb_Init();
//	Key_Config();
//	Key_Interrupt_Config();

//	ADC_Config();
	UART_Config();
	Capture_Init();
//	printf("hello\r\n");
	UARTprintf("hello\r\n");			//不支持浮点数
	UARTprintf("%d\r\n",SysCtlClockGet());
	
//	EEPROM_Config(); 
//	Timer_Config();
//	DMA_Config();
//	USART_DMA_Config();
//	Encorder_Config();
//	Timer_PWM_Config();
//	Pwm_Config();
//	I2C_Config();
//	SysCtlDelay(800*(80000/3));
//	SPI_Config();
//	uint8_t ID;
//	ID = I2C0_READ_Byte(0x68, 0x75);
//	UARTprintf("%d\r\n",ID);
//	float pitch=0.0,roll=0.0,yaw=0.0;
//	MPU_Init();
//	while(mpu_dmp_init()){}
//	OLED_Init();
//	OLED_Clear();
//	OLED_ShowNum(0,2,1,1,8);
//	OLED_ShowCHinese(0,4,0);
//	OLED_ShowString(0,6,"ASCII:",8);
//	uint8_t data[5] = {0x12,0x13,0x14,0x15,0x16};
	float angle = 0.0;
    while(1)
    {
		angle = Get_Position(100);
		UARTprintf("angle = %d\r\n",(uint32_t)(angle*100));
//		SPI_Write(data,5);
		SysCtlDelay(1000*(80000/3));
//		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
//		SysCtlDelay(100*(80000/3));
//		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
//		SysCtlDelay(100*(80000/3));
		//MPU6050
//        while(mpu_dmp_get_data(&pitch, &roll, &yaw) != 0);
//		UARTprintf("pitch = %d\r\n",(int16_t)(pitch*100));
//		UARTprintf("roll = %d\r\n",(int16_t)(roll*100));
//		UARTprintf("yaw = %d\r\n\r\n\r\n",(int16_t)(yaw*100));
//		SysCtlDelay(100*(80000/3));
    }

}
