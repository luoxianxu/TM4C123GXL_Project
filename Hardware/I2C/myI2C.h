
#ifndef _MYI2C_H
#define _MYI2C_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"		//GPIO
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"	//SYSCTL
#include "inc/hw_memmap.h"		//GPIO_PORTF_BASE
#include "inc/hw_types.h"		//HWREG
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"
#include "inc/hw_i2c.h"

#define I2C_SYSCTL_PERIPH				SYSCTL_PERIPH_I2C3
#define I2CGPIO_SYSCTL_PERIPH			SYSCTL_PERIPH_GPIOD

#define I2C_SCLGPIO						GPIO_PD0_I2C3SCL
#define I2C_SDAGPIO						GPIO_PD1_I2C3SDA

#define I2C_GPIO						GPIO_PORTD_BASE
#define I2C_SCLGPIO_PIN					GPIO_PIN_0
#define I2C_SDAGPIO_PIN					GPIO_PIN_1

#define I2C								I2C3_BASE

void I2C_Config(void);
void I2C0_SEND(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t num);
uint8_t I2C0_READ_Byte(uint8_t addr, uint8_t reg);
void I2C0_READ(uint8_t addr,uint8_t reg,uint8_t *data,uint8_t len);
#endif /*_MYI2C_H*/
