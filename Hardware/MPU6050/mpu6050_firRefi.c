/*
 * mpu6050_firRefi.c
 *
 *  Created on: 2016��7��6��
 *      Author: lenovo
 */

#include "mpu6050_firRefi.h"
#include "mpu6050.h"
#include "myI2C.h"

//IICдһ���ֽ�
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data){

	I2C0_SEND(MPU_RW>>1,reg,&data,1);
	return 0;
}


u8 MPU_Read_Byte(u8 reg){
	u8 res;

	res = I2C0_READ_Byte(MPU_RW>>1,reg);
	
	return res;
}



//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf){
	
	I2C0_READ(addr,reg,buf,len);
	return 0;
}



//IIC����д
//addr:������ַ
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	I2C0_SEND(addr,reg,buf,len);
	return 0;
}
