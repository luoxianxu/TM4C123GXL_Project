#ifndef _HARDWARE_OLED_H
#define _HARDWARE_OLED_H 

#include "myI2C.h"

//#include <stdlib.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define OLED_SCL GPIO_PORT_P6,GPIO_PIN7    //更改此处以更改屏幕接入MSP432的接口
//#define OLED_SDA GPIO_PORT_P6,GPIO_PIN6
//#define OLED_RES GPIO_PORT_P3,GPIO_PIN5
//#define OLED_DC  GPIO_PORT_P4,GPIO_PIN4
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D0
//#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_0)           //SCK
//#define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_0)
////DI
//#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_1)           //MOSI
//#define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_1)
////RES
//#define OLED_RST_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)           //RST
//#define OLED_RST_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_4)
////DC
//#define OLED_DC_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_5)           //DC
//#define OLED_DC_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define OLED_CMD  0	                                               //写命令
#define OLED_DATA 1	//写数据

#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

#define u8 unsigned char
#define u32 unsigned int
void OLED_DisplayTurn(void);                                                   //屏幕显示翻转
void OLED_Refresh(void);                                                       //更新显存到OLED	
void OLED_Clear(void);                                                         //清屏函数                            
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);//显示字符串(字符串行列x、y,字符串,大小)
void OLED_ShowCHinese(u8 x,u8 y,u8 no);//显示中文字符串
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//显示整数(显示位置x、y,需要显示的数值,显示位数<从位小到大位显示，多余位用0补齐>)
void OLED_Init(void);                                                          //OLED的初始化

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//屏幕像素数量:128*64
//字符取模方式;逐列式,汉字取模方式:列行式
//在OLED_ShowFloat()函数中，会自动为num+0.000 000 001
//显示中文字符串和显示浮点数函数不会自动换行
//在修改完屏幕显示内容后都要更新显存到OLED	
