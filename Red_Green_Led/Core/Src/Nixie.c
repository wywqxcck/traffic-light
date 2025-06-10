#include "Nixie.h"

const uint8_t seg1[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};


void NS_Nixie_Show(uint8_t Num)
{
	if(Num > 99)
		return;
	uint8_t Num1,Num2,temp_data,i;
	Num1 = Num / 10;
	Num2 = Num % 10;
	temp_data = seg1[Num2];
	for(i = 0;i < 8;i++){
		if(temp_data & 0x80)
			HAL_GPIO_WritePin(NS_SDI_GPIO_Port,NS_SDI_Pin,GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(NS_SDI_GPIO_Port,NS_SDI_Pin,GPIO_PIN_RESET);
		temp_data <<= 1;
		HAL_GPIO_WritePin(NS_SCL_GPIO_Port,NS_SCL_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(NS_SCL_GPIO_Port,NS_SCL_Pin,GPIO_PIN_SET);
	}
	temp_data = seg1[Num1];
	for(i = 0;i < 8;i++){
		if(temp_data & 0x80)
			HAL_GPIO_WritePin(NS_SDI_GPIO_Port,NS_SDI_Pin,GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(NS_SDI_GPIO_Port,NS_SDI_Pin,GPIO_PIN_RESET);
		temp_data <<= 1;
		HAL_GPIO_WritePin(NS_SCL_GPIO_Port,NS_SCL_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(NS_SCL_GPIO_Port,NS_SCL_Pin,GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(NS_LOAD_GPIO_Port,NS_LOAD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(NS_LOAD_GPIO_Port,NS_LOAD_Pin,GPIO_PIN_RESET);
}


void EW_Nixie_Show(uint8_t Num)
{
	if(Num > 99)
		return;
	uint8_t Num1,Num2,temp_data,i;
	Num1 = Num / 10;
	Num2 = Num % 10;
	temp_data = seg1[Num2];
	for(i = 0;i < 8;i++){
		if(temp_data & 0x80)
			HAL_GPIO_WritePin(EW_SDI_GPIO_Port,EW_SDI_Pin,GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(EW_SDI_GPIO_Port,EW_SDI_Pin,GPIO_PIN_RESET);
		temp_data <<= 1;
		HAL_GPIO_WritePin(EW_SCL_GPIO_Port,EW_SCL_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EW_SCL_GPIO_Port,EW_SCL_Pin,GPIO_PIN_SET);
	}
	temp_data = seg1[Num1];
	for(i = 0;i < 8;i++){
		if(temp_data & 0x80)
			HAL_GPIO_WritePin(EW_SDI_GPIO_Port,EW_SDI_Pin,GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(EW_SDI_GPIO_Port,EW_SDI_Pin,GPIO_PIN_RESET);
		temp_data <<= 1;
		HAL_GPIO_WritePin(EW_SCL_GPIO_Port,EW_SCL_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EW_SCL_GPIO_Port,EW_SCL_Pin,GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(EW_LOAD_GPIO_Port,EW_LOAD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(EW_LOAD_GPIO_Port,EW_LOAD_Pin,GPIO_PIN_RESET);
}