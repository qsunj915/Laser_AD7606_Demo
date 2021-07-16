/**
  ******************************************************************************
  * @file    distance.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-10-11
  * @brief   
  ******************************************************************************
  */
	
#ifndef __DISTANCE_H
#define __DISTANCE_H

#include "stm32f4xx.h"
#include "drv_adc.h"
#include "math.h"
//#include ".h"

uint32_t* ADC_Queue_Updata(uint32_t* adc_val);
uint32_t* Dis_Caculate(uint32_t* queue_val);
uint32_t* Dis_get(void);
float Get_Beta(void);


#endif
