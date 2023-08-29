#include "oled.h"
#include "oledfont.h"

u8 OLED_GRAM[144][8];
//写数据/命令函数(0命令1数据)
void OLED_WR_Byte(u8 dat,u8 cmd)
{		
	uint8_t order = 0x00;
	if(cmd)
		order = 0x40;
	else order = 0x00;
	I2C0_SEND(0x3C, order, &dat, 1);
}
//画点
void OLED_DrawPoint(u8 x,u8 y)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]|=n;
}
//清除一个点
void OLED_ClearPoint(u8 x,u8 y)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	OLED_GRAM[x][i]|=n;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
}

u32 OLED_Pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)
	  result*=m;
	return result;
}
//显示汉字//num:汉字对应的序号
void OLED_ShowChinese(u8 x,u8 y,u8 num)
{
	u8 i,m,n=0,temp,chr1;
	u8 x0=x,y0=y;
	u8 size3=2;
	while(size3--)
	{
		chr1=num*2+n;
		n++;
		for(i=0;i<16;i++)
		{
			temp=Hzk1[chr1][i];
			for(m=0;m<8;m++)
			{
				if(temp&0x01)OLED_DrawPoint(x,y);
				else OLED_ClearPoint(x,y);
				temp>>=1;
				y++;
			}
			x++;
			if((x-x0)==16)
			{
				x=x0;
				y0=y0+8;
			}
			y=y0;
		}
	}
}
//配置写入数据的起始位置
void OLED_WR_BP(u8 x,u8 y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);//设置行起始地址
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OLED_DisplayTurn(void)
{
			OLED_WR_Byte(0xC0,OLED_CMD);               
			OLED_WR_Byte(0xA0,OLED_CMD);
}
void OLED_Refresh(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); 
	   OLED_WR_Byte(0x00,OLED_CMD);    
	   OLED_WR_Byte(0x10,OLED_CMD);   
	   for(n=0;n<128;n++)
		 OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
	}
}
void OLED_Clear(void)
{ 
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	}
}
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2)
{
	u8 i,k,k1,k2;
//	if((x1<0)||(x2>128)||(y1<0)||(y2>64)||(x1>x2)||(y1>y2))return;
	if((x2>128)||(y2>64)||(x1>x2)||(y1>y2))return;
	if(x1==x2)                                                                   
	{
			for(i=0;i<(y2-y1);i++)
			{
				OLED_DrawPoint(x1,y1+i);
			}
  }
	else if(y1==y2)                                                             
	{
			for(i=0;i<(x2-x1);i++)
			{
				OLED_DrawPoint(x1+i,y1);
			}
  }
	else                                                                        
	{
		k1=y2-y1;
		k2=x2-x1;
		k=k1*10/k2;
		for(i=0;i<(x2-x1);i++)
			{
			  OLED_DrawPoint(x1+i,y1+i*k/10);
			}
	}
} 
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk1[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk1[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
}
/*
void OLED_ShowFloat(u8 x,u8 y,double num,double len)
{
	unsigned char len1=len/1;
	int len2=(int)(len*10-len1*10);
	int num1;
	double num2;
	if(num<0)
	{
		OLED_ShowChar((x-1)*8,(y-1)*16,'-',16);
		x++;		
		num=-num;
	}
	num+=0.0000000001;
	num1=(int)num;
	num2=num-num1;
	OLED_ShowInt(x,y,num1,len1);
	num1=0;
	x=(x+len1-1)*8;
	y=(y-1)*16;
	OLED_ShowChar(x,y,'.',16);
	x+=8;
	num2*=OLED_Pow(10,len2);
	num1+=num2;
	OLED_ShowInt(x/8+1,y/16+1,num1,len2);
}*/
/*
void OLED_DrowFrame(u8 x1,u8 y1,u8 x2,u8 y2)
{
	OLED_DrawLine(x1,y1,x1,y2);
	OLED_DrawLine(x1,y1,x2,y1);
	OLED_DrawLine(x2,y1,x2,y2);
	OLED_DrawLine(x1,y2,x2,y2);	
}*/
void OLED_Init(void)
{ 
	
	OLED_WR_Byte(0xAE,OLED_CMD); 
	OLED_WR_Byte(0x00,OLED_CMD); 
	OLED_WR_Byte(0x10,OLED_CMD); 
	OLED_WR_Byte(0x40,OLED_CMD); 
	OLED_WR_Byte(0x81,OLED_CMD); 
	OLED_WR_Byte(0xCF,OLED_CMD); 
	OLED_WR_Byte(0xA1,OLED_CMD); 
	OLED_WR_Byte(0xC8,OLED_CMD); 
	OLED_WR_Byte(0xA6,OLED_CMD); 
	OLED_WR_Byte(0xA8,OLED_CMD); 
	OLED_WR_Byte(0x3f,OLED_CMD); 
	OLED_WR_Byte(0xD3,OLED_CMD); 
	OLED_WR_Byte(0x00,OLED_CMD); 
	OLED_WR_Byte(0xd5,OLED_CMD); 
	OLED_WR_Byte(0x80,OLED_CMD); 
	OLED_WR_Byte(0xD9,OLED_CMD); 
	OLED_WR_Byte(0xF1,OLED_CMD); 
	OLED_WR_Byte(0xDA,OLED_CMD); 
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD); 
	OLED_WR_Byte(0x40,OLED_CMD); 
	OLED_WR_Byte(0x20,OLED_CMD); 
	OLED_WR_Byte(0x02,OLED_CMD); 
	OLED_WR_Byte(0x8D,OLED_CMD); 
	OLED_WR_Byte(0x14,OLED_CMD); 
	OLED_WR_Byte(0xA4,OLED_CMD); 
	OLED_WR_Byte(0xA6,OLED_CMD); 
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_Clear();
	OLED_WR_Byte(0xA6,OLED_CMD);                                           
	OLED_WR_Byte(0xC8,OLED_CMD);                                            
	OLED_WR_Byte(0xA1,OLED_CMD);
	OLED_Refresh();
	
}
