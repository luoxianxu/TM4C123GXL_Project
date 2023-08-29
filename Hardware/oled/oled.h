#ifndef _HARDWARE_OLED_H
#define _HARDWARE_OLED_H 

#include "myI2C.h"

//#include <stdlib.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define OLED_SCL GPIO_PORT_P6,GPIO_PIN7    //���Ĵ˴��Ը�����Ļ����MSP432�Ľӿ�
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

#define OLED_CMD  0	                                               //д����
#define OLED_DATA 1	//д����

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
void OLED_DisplayTurn(void);                                                   //��Ļ��ʾ��ת
void OLED_Refresh(void);                                                       //�����Դ浽OLED	
void OLED_Clear(void);                                                         //��������                            
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);//��ʾ�ַ���(�ַ�������x��y,�ַ���,��С)
void OLED_ShowCHinese(u8 x,u8 y,u8 no);//��ʾ�����ַ���
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//��ʾ����(��ʾλ��x��y,��Ҫ��ʾ����ֵ,��ʾλ��<��λС����λ��ʾ������λ��0����>)
void OLED_Init(void);                                                          //OLED�ĳ�ʼ��

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��Ļ��������:128*64
//�ַ�ȡģ��ʽ;����ʽ,����ȡģ��ʽ:����ʽ
//��OLED_ShowFloat()�����У����Զ�Ϊnum+0.000 000 001
//��ʾ�����ַ�������ʾ���������������Զ�����
//���޸�����Ļ��ʾ���ݺ�Ҫ�����Դ浽OLED	
