
#include "myI2C.h"

void I2C_Config(void){
	
	SysCtlPeripheralEnable(I2C_SYSCTL_PERIPH);
	SysCtlPeripheralEnable(I2CGPIO_SYSCTL_PERIPH);
	//SCL GPIO
	GPIOPinConfigure(I2C_SCLGPIO);
	//SDA GPIO
	GPIOPinConfigure(I2C_SDAGPIO);
	GPIOPinTypeI2CSCL(I2C_GPIO, I2C_SCLGPIO_PIN);				//注意
	GPIOPinTypeI2C(I2C_GPIO, I2C_SDAGPIO_PIN);
	//I2C 设置I2C时钟频率
	I2CMasterInitExpClk(I2C, 80000000, true);
//	SysCtlDelay(2);
}

void I2C0_SEND(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t num)
{
    I2CMasterSlaveAddrSet(I2C, addr, false); // 写
    I2CMasterDataPut(I2C, reg);// 设置要写的寄存器地址
    I2CMasterControl(I2C, I2C_MASTER_CMD_BURST_SEND_START); // Send start condition
    while (I2CMasterBusy(I2C)); // 等待传输完成
    for (uint8_t i = 0; i < num - 1; i++)
    {
        I2CMasterDataPut(I2C, data[i]);                        // Place data into data register
        I2CMasterControl(I2C, I2C_MASTER_CMD_BURST_SEND_CONT); // Send continues condition
        while (I2CMasterBusy(I2C)); //等待传输完成
    }
    I2CMasterDataPut(I2C, data[num - 1]);// Place data into data register
    I2CMasterControl(I2C, I2C_MASTER_CMD_BURST_SEND_FINISH); // 传输完成
    while (I2CMasterBusy(I2C)); // 等待传输完成
}

uint8_t I2C0_READ_Byte(uint8_t addr, uint8_t reg)
{
    I2CMasterSlaveAddrSet(I2C, addr, false); //写
    I2CMasterDataPut(I2C, reg); // 选择要读的寄存器地址
    I2CMasterControl(I2C, I2C_MASTER_CMD_SINGLE_SEND); //发送数据
    while (I2CMasterBusy(I2C)); //等待发送完成
    I2CMasterSlaveAddrSet(I2C, addr, true); //读
    I2CMasterControl(I2C, I2C_MASTER_CMD_SINGLE_RECEIVE); //接收
    while (I2CMasterBusy(I2C));// 等待接收完成
    return I2CMasterDataGet(I2C); // 读取数据
}

void I2C0_READ(uint8_t addr,uint8_t reg,uint8_t *data,uint8_t len){
	I2CMasterSlaveAddrSet(I2C, addr, false);

    I2CMasterDataPut(I2C, reg);
    I2CMasterControl(I2C, I2C_MASTER_CMD_SINGLE_SEND);
    while (I2CMasterBusy(I2C));

    I2CMasterSlaveAddrSet(I2C, addr, true);

    I2CMasterControl(I2C, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while (I2CMasterBusy(I2C));
    data[0] = I2CMasterDataGet(I2C);

    for (uint8_t i = 1; i < len - 1; i++)
    {
        I2CMasterControl(I2C, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        while (I2CMasterBusy(I2C));
        data[i] = I2CMasterDataGet(I2C);
    }

    I2CMasterControl(I2C, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while (I2CMasterBusy(I2C));
    data[len - 1] = I2CMasterDataGet(I2C);
}
