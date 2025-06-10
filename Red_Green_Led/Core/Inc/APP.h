#ifndef APP_H_
#define APP_H_


#include "main.h"
#include "Nixie.h"
#include "LED.h"
#include "stdio.h"
#include "usart.h"
#include "string.h"
#include <stdlib.h>


#define N_S_G 'G'
#define N_S_R 'R'


typedef struct Struct_Red_Green_Led_Data{
	int8_t NS_Red_Time;
	int8_t NS_Green_Time;
	int8_t EW_Red_Time;
	int8_t EW_Green_Time;
}Red_Green_Led;

typedef struct Struct_Usart_Data{
	uint8_t usart_len;
	uint8_t usart_data[256];
}Usart_Data;

extern uint8_t usart_buf;
void Usart_Init(void);
void Red_Green_Led_Con(void);
void Usart_Con(void);


#endif
