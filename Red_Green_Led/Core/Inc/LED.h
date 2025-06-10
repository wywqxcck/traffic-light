#ifndef LED_H_
#define LED_H_


#include "main.h"

typedef enum ENUM_LED_COLOUR{
	RED,
	GREEN,
	YELLOW,
}Led_Colour;

void EW_Led(Led_Colour data);
void NS_Led(Led_Colour data);

#endif
