#include "APP.h"

Red_Green_Led Red_Green_Led_Data = {
	.NS_Red_Time = 5,
	.NS_Green_Time = 5,
	.EW_Red_Time = 5,
	.EW_Green_Time = 5,
};

Usart_Data usart_data = { 0 };

uint8_t usart_buf;

void Red_Green_Led_Con(void)
{
    static Red_Green_Led new_Red_Green_Led = { 0, 0, 0, 0 };
    static uint8_t NS_yellow_led_time = 0, EW_yellow_led_time = 0,send_flage = 0;

    if (new_Red_Green_Led.NS_Green_Time > 0) {
        new_Red_Green_Led.NS_Green_Time--;
        new_Red_Green_Led.EW_Red_Time--;
        NS_Nixie_Show(new_Red_Green_Led.NS_Green_Time);
        EW_Nixie_Show(new_Red_Green_Led.EW_Red_Time);
        NS_Led(GREEN);
        EW_Led(RED);
    } else if (NS_yellow_led_time > 0) {
        NS_Led(YELLOW);
        EW_Led(RED);
        NS_yellow_led_time--;
        new_Red_Green_Led.EW_Red_Time--;
        NS_Nixie_Show(NS_yellow_led_time);
        EW_Nixie_Show(new_Red_Green_Led.EW_Red_Time);
    } else if (new_Red_Green_Led.EW_Green_Time > 0) {
				if(send_flage == 0){
						printf("*\r\n");
						HAL_UART_Transmit(&huart2, (uint8_t*)"*", strlen("*"), HAL_MAX_DELAY);
						send_flage = 1;
				}
        new_Red_Green_Led.NS_Red_Time--;
        new_Red_Green_Led.EW_Green_Time--;
        NS_Nixie_Show(new_Red_Green_Led.NS_Red_Time);
        EW_Nixie_Show(new_Red_Green_Led.EW_Green_Time);
        NS_Led(RED);
        EW_Led(GREEN);
    } else if (EW_yellow_led_time > 0) {
        NS_Led(RED);
        EW_Led(YELLOW);
        EW_yellow_led_time--;
        new_Red_Green_Led.NS_Red_Time--;
        NS_Nixie_Show(new_Red_Green_Led.NS_Red_Time);
        EW_Nixie_Show(EW_yellow_led_time);
    } else {
        new_Red_Green_Led.NS_Green_Time = Red_Green_Led_Data.NS_Green_Time;
        new_Red_Green_Led.NS_Red_Time = Red_Green_Led_Data.NS_Red_Time + 3;
        new_Red_Green_Led.EW_Green_Time = Red_Green_Led_Data.EW_Green_Time;
        new_Red_Green_Led.EW_Red_Time = Red_Green_Led_Data.EW_Red_Time + 3;
        NS_yellow_led_time = 3;
        EW_yellow_led_time = 3;
        NS_Led(GREEN);
        EW_Led(RED);
        new_Red_Green_Led.NS_Green_Time--;
        new_Red_Green_Led.EW_Red_Time--;
        NS_Nixie_Show(new_Red_Green_Led.NS_Green_Time);
        EW_Nixie_Show(new_Red_Green_Led.EW_Red_Time);
				send_flage = 0;
				printf("#\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t*)"#", strlen("#"), HAL_MAX_DELAY);
    }
}

uint8_t Invert(uint8_t Data){
    if(Data >= '0' && Data <= '9')
        return Data - 48;
    return 0xFF;
}



// 提取数字的函数
void extract_numbers(const char *input, int8_t *first_num, int8_t *second_num) {
    const char *g_pos = strchr(input, N_S_G);
    const char *r_pos = strchr(input, N_S_R);

    if (g_pos == NULL || r_pos == NULL || r_pos < g_pos) {
        // 输入格式不符合要求
        *first_num = 0;
        *second_num = 0;
        return;
    }

    g_pos++;  // 跳过 'G'
    r_pos++;  // 跳过 'R'

    char first_str[10], second_str[10];
    int i = 0;
    // 提取 'G' 到 'R' 之间的数字
    while (g_pos < r_pos) {
        first_str[i++] = *g_pos++;
    }
    first_str[i] = '\0';

    i = 0;
    // 提取 'R' 之后的数字
    while (*r_pos != '\0') {
        second_str[i++] = *r_pos++;
    }
    second_str[i] = '\0';

    // 将字符串转换为整数
    *first_num = atoi(first_str);
    *second_num = atoi(second_str);
}

void Usart_Init(void)
{
		memset(usart_data.usart_data,0,sizeof(usart_data.usart_data));
		usart_data.usart_len = 0;
}


void Usart_Con(void)
{
	if(usart_buf != '#'){
		usart_data.usart_data[usart_data.usart_len++] = usart_buf;
	}
	else{
		usart_data.usart_data[usart_data.usart_len] = '\0';
		extract_numbers((const char*)(usart_data.usart_data),&(Red_Green_Led_Data.NS_Red_Time),&(Red_Green_Led_Data.NS_Green_Time));
		Red_Green_Led_Data.EW_Green_Time = Red_Green_Led_Data.NS_Red_Time;
		Red_Green_Led_Data.EW_Red_Time = Red_Green_Led_Data.NS_Green_Time;
		printf("usart_data.usart_data = %s\r\n",usart_data.usart_data);
		printf("Red_Green_Led_Data.NS_Green_Time = %d\r\n",Red_Green_Led_Data.NS_Green_Time);
		printf("Red_Green_Led_Data.NS_Red_Time = %d\r\n",Red_Green_Led_Data.NS_Red_Time);
		printf("Red_Green_Led_Data.EW_Green_Time = %d\r\n",Red_Green_Led_Data.EW_Green_Time);
		printf("Red_Green_Led_Data.EW_Red_Time = %d\r\n",Red_Green_Led_Data.EW_Red_Time);
		printf("set ok\r\n\r\n");
		memset(usart_data.usart_data,0,sizeof(usart_data.usart_data));
		usart_data.usart_len = 0;
	}
	HAL_UART_Receive_IT(&huart1,&usart_buf,1);
	HAL_UART_Receive_IT(&huart2,&usart_buf,1);
}
