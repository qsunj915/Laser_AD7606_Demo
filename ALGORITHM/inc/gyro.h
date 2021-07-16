/**
  ******************************************************************************
  * @file    gyro.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-11-24
  * @brief   
  ******************************************************************************
  */
  
#ifndef __GYRO_H
#define __GYRO_H


#include "stm32f4xx.h"
#include "drv_uart.h"

#define NOMINAL_FACTOR (4.702317f * 10000)

typedef struct gyro
{
	int32_t Gyro_Message;
    float   Gyro_Temperature;
    double  Angular_velocity_z;
}Gyro_Init_Info;

typedef enum Gyro_Mode
{ 
  Message      = 0x00,
  Temprature   = 0x01
}Gyro_Mode_Typedef;

void Get_Gyro_Info(uint8_t Rxbuf);
uint8_t XOR_Check(uint8_t *Temp, Gyro_Mode_Typedef Gyro_Mode);


#endif


