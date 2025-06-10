#ifndef _MULTI_BUTTON_H_
#define _MULTI_BUTTON_H_

#include "stdint.h"
#include "string.h"
#include "main.h"



//According to your need to modify the constants.
#define TICKS_INTERVAL 5 //ms��ϵͳ����5ms
#define DEBOUNCE_TICKS 5 //MAX 8��ȥ���Ĵ���
#define SHORT_TICKS (300 / TICKS_INTERVAL)	//�����̰�����ʱ����300ms����
#define LONG_TICKS (1000 / TICKS_INTERVAL)	//��������ʱ����1000ms����
#define LONG_HOLD_CYC (500 / TICKS_INTERVAL)	//���ڳ��������ִ���״̬ʱ��ÿ500ms����һ�λص�����




typedef void (*BtnCallback)(void *);

//����һ�������¼���ö�����ͣ����������еİ�����������
typedef enum
{
	PRESS_DOWN = 0,	//�������£�ÿ�ΰ��¶����� 
	PRESS_UP,		//��������ÿ���ɿ�������
	SINGLE_CLICK,	//���������¼�
	DOUBLE_CLICK,	//˫�������¼�
	PRESS_REPEAT,	//���������¼�
	LONG_PRESS_START,	//�ﵽ����ʱ����ֵʱ����һ��
	LONG_PRESS_HOLD,	//�����ڼ�һֱ����
	number_of_event,	//�¼�����
	NONE_PRESS		//û���κΰ����¼�
} PressEvent;

//����һ�������ṹ�����ͣ�����
typedef struct Button
{
	uint16_t ticks;			//ϵͳ���ļ���
	uint8_t repeat : 4;		//�ظ�������˫������������
	uint8_t event : 4;		//��ǰ�����¼�
	uint8_t state : 3;		//��ǰ����״̬
	uint8_t debounce_cnt : 3;	//ȥ������	
	uint8_t active_level : 1;	//�������µ���Ч��ƽ			
	uint8_t button_level : 1;	//������ƽ״̬����ȡһ�θ���һ��
	uint8_t (*hal_button_Level)(void);	//��ȡ������ƽ�ĺ���ָ��
	BtnCallback cb[number_of_event];	//�����ص�����ָ������
	struct Button *next;	//ָ���������һ��
} Button;

extern Button btn1;

#ifdef __cplusplus
extern "C"
{
#endif
	//�����ṹ���ʼ�������谴����ȡ��ƽ�ĺ���ָ�룬��������ǰ��ƽ
	void button_init(struct Button *handle, uint8_t (*pin_level)(), uint8_t active_level);
	//����ע�ᣨ�����ض��İ����¼��Իص�������
	void button_attach(struct Button *handle, PressEvent event, BtnCallback cb);
	//��ȡ�����¼����ص������ṹ��
	PressEvent get_button_event(struct Button *handle);
	//����һ��������������һ�������ṹ������ڵ�
	int button_start(struct Button *handle);
	//ֹͣһ������������������ɾ���ð����ڵ�
	void button_stop(struct Button *handle);
	//�������ģ�ÿһ�ν����¼����������б������а�����������������
	void button_ticks(void);
	//��ȡ����״̬
	uint8_t read_button1_GPIO(void);
	//�������ų�ʼ��
	void KEY_GPIO_Init(void);	//�����ص�����
	void BTN1_SINGLE_Click_Handler(void* btn);
	//˫���ص�����
	void BTN1_DOUBLE_Click_Handler(void* btn);
	//��������74������
	void BTN1_PRESS_REPEAT_Handler(void* btn);
	//�����ص�����
	void BTN1_LONG_PRESS_START_Handler(void* btn);
#ifdef __cplusplus
}
#endif

#endif
