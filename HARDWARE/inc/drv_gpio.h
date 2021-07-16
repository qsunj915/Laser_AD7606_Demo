#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

#include "stm32f4xx.h"
#include "drv_uart.h"


void GPIO_Format_Init(GPIO_TypeDef * GPIOX, uint16_t PinX, GPIOMode_TypeDef Mode, \
					GPIOOType_TypeDef OType, GPIOPuPd_TypeDef PuPd, GPIOSpeed_TypeDef Speed);


#endif
