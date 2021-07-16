/**
  ******************************************************************************
  * @file    protocol.H
  * @author  jOKERII
  * @version v1.0
  * @date    20-10-11
  * @brief   
  ******************************************************************************
  */
  
#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "stm32f4xx.h"
#include "stdio.h"


uint8_t pack_deal(char * buff,uint32_t *distance, float beta);
uint8_t unpack_deal(char * buff,uint32_t *distance, float* beta);



#endif


