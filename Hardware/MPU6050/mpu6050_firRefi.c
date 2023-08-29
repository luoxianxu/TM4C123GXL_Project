/*
 * mpu6050_firRefi.c
 *
 *  Created on: 2016年7月6日
 *      Author: lenovo
 */

#include "mpu6050_firRefi.h"
#include "mpu6050.h"
#include "myI2C.h"

//IIC写一个字节
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Byte(u8 reg,u8 data){

	I2C0_SEND(MPU_RW>>1,reg,&data,1);
	return 0;
}


u8 MPU_Read_Byte(u8 reg){
	u8 res;

	res = I2C0_READ_Byte(MPU_RW>>1,reg);
	
	return res;
}



//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf){
	
	I2C0_READ(addr,reg,buf,len);
	return 0;
}



//IIC连续写
//addr:器件地址
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	I2C0_SEND(addr,reg,buf,len);
	return 0;
}
