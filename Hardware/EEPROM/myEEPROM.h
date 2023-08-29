
#ifndef _EEPROM_H
#define _EEPROM_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_eeprom.h"
#include "inc/hw_flash.h"
#include "inc/hw_ints.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/flash.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/eeprom.h"

#define		SYSCTL_PERIPH_EEPROM	SYSCTL_PERIPH_EEPROM0

void EEPROM_Config(void);

#endif /*_EEPROM_H*/
