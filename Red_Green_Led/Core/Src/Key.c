#include "key.h"
#include "stdio.h"

Button btn1;

uint8_t read_button1_GPIO(void)
{
		return HAL_GPIO_ReadPin(POWER_IN_GPIO_Port,POWER_IN_Pin);
}


void BTN1_SINGLE_Click_Handler(void* btn)//�����ص�����
{
	
}

void BTN1_DOUBLE_Click_Handler(void* btn)//˫���ص�����
{
	HAL_GPIO_WritePin(GPIOB,POWER_OUT_Pin, GPIO_PIN_RESET);
}

void BTN1_PRESS_REPEAT_Handler(void* btn)//�������ص�����
{
		
}

void BTN1_LONG_PRESS_START_Handler(void* btn)//�����ص�����
{
	
}


#define EVENT_CB(ev)    \
	if (handle->cb[ev]) \
	handle->cb[ev]((Button *)handle)

//button handle list head.
//�����ṹ��������ʼ��ָ��ΪNULL��������
static struct Button *head_handle = NULL;

/**
  * @brief  Initializes the button struct handle.
  * @param  handle: the button handle strcut.
  * @param  pin_level: read the HAL GPIO of the connet button level.
  * @param  active_level: pressed GPIO level.
  * @retval None
  */
 //�����ṹ���ʼ�������谴����ȡ��ƽ�ĺ���ָ�룬��������ǰ��ƽ
void button_init(struct Button *handle, uint8_t (*pin_level)(), uint8_t active_level)
{
		memset(handle, 0, sizeof(struct Button));		   //�ṹ���ʼ��Ϊȫ0
		handle->event = (uint8_t)NONE_PRESS;			   //��ʼ��Ϊû�а����¼�
		handle->hal_button_Level = pin_level;			   //��ȡ������ƽ״̬����ָ��
		handle->button_level = handle->hal_button_Level(); //��ȡһ�ε�ǰ������ƽ
		handle->active_level = active_level;			   //���µ���Ч��ƽ��1����0
}

/**
  * @brief  Attach the button event callback function.
  * @param  handle: the button handle strcut.
  * @param  event: trigger event type.
  * @param  cb: callback function.
  * @retval None
  */
 //����ע�ᣨ�����ض��İ����¼��Իص�������
void button_attach(struct Button *handle, PressEvent event, BtnCallback cb)
{
	handle->cb[event] = cb; //����ĳ�ض������¼��Ļص�����ָ��
}

/**
  * @brief  Inquire the button event happen.
  * @param  handle: the button handle strcut.
  * @retval button event.
  */
 //��ȡ�����¼����ص������ṹ��
PressEvent get_button_event(struct Button *handle)
{
	return (PressEvent)(handle->event); //���ذ����¼�
}

/**
  * @brief  Button driver core function, driver state machine.
  * @param  handle: the button handle strcut.
  * @retval None
  */
//�����������ĺ���������״̬��
void button_handler(struct Button *handle)
{
	//��ȡ��ǰ��ƽ״̬
	uint8_t read_gpio_level = handle->hal_button_Level();

	//ticks counter working..
	//ֻҪ����״̬����0���͵�����¼ϵͳ���Ĵ���
	if ((handle->state) > 0)
		handle->ticks++;

	/*------------button debounce handle---------------*/
	//�����һ�λ�ȡ�ĵ�ƽ״̬����һ��״̬����������������ȥ�����ܸ�ֵ��ǰ��ƽ
	if (read_gpio_level != handle->button_level)
	{ //not equal to prev one
		//continue read 3 times same new level change
		if (++(handle->debounce_cnt) >= DEBOUNCE_TICKS)
		{
			handle->button_level = read_gpio_level;
			handle->debounce_cnt = 0;
		}
	}
	//������ȥ����⴦��
	else
	{ //leved not change ,counter reset.
		handle->debounce_cnt = 0;
	}

	/*-----------------State machine-------------------*/
	switch (handle->state)
	{
	case 0: //���ǰ�ΰ���״̬��0���ҵ�ǰ������ƽ������Ч��ƽ������Ϊ�ǰ�����ʼ������
		if (handle->button_level == handle->active_level)
		{										 //start press down
			handle->event = (uint8_t)PRESS_DOWN; //�а��������¼�����
			EVENT_CB(PRESS_DOWN);				 //������ڻص�������ִ��
			handle->ticks = 0;					 //���ļ�������
			handle->repeat = 1;					 //�¼��ظ�����Ϊ1
			handle->state = 1;					 //����״̬����Ϊ1�����£�
		}
		else //���������Ч��ƽ�����ް����¼�
		{
			handle->event = (uint8_t)NONE_PRESS;
		}
		break;

	case 1: //���ǰ�ΰ���״̬��1�������ˣ����ҵ�ǰ��ƽ������Ч��ƽ������Ϊ�����ɿ���
		if (handle->button_level != handle->active_level)
		{									   //released press up
			handle->event = (uint8_t)PRESS_UP; //�а����ɿ������¼�����
			EVENT_CB(PRESS_UP);				   //������ڻص�������ִ��
			handle->ticks = 0;				   //���ļ�������
			handle->state = 2;				   //����״̬����Ϊ2���ɿ���
		}
		//������ļ��������˳�������ֵ������Ϊ��һ�γ������¼�
		else if (handle->ticks > LONG_TICKS)
		{
			handle->event = (uint8_t)LONG_PRESS_START; //�г�������ʼ�¼�����
			EVENT_CB(LONG_PRESS_START);				   //������ڻص�������ִ��
			handle->state = 5;						   //����״̬����Ϊ5��������ʼ��
		}
		break;

	case 2: //���ǰ�ΰ���״̬��2���ɿ��ˣ����ҵ�ǰ��ƽ����Ч��ƽ������Ϊ�����ְ�����
		if (handle->button_level == handle->active_level)
		{										 //press down again
			//handle->event = (uint8_t)PRESS_DOWN; //�а��������¼�����
			EVENT_CB(PRESS_DOWN);				 //������ڻص�������ִ��
			handle->repeat++;					 //��һ�ΰ��£��ظ�������1
			handle->ticks = 0;					 //���ļ�������
			handle->state = 3;					 //����״̬����Ϊ3���ظ�������
		}
		//���������Ч��ƽ��˵���ɿ��ˣ���ô������µ�ʱ���Ƿ񳬹��˶̰����Ľ��ļ�����ֵ
		else if (handle->ticks > SHORT_TICKS)
		{ //released timeout
			//������ֵ����ֻ������1�Σ�����Ϊ��һ�ε����¼�
			if (handle->repeat == 1)
			{
				handle->event = (uint8_t)SINGLE_CLICK; //�е����¼�����
				EVENT_CB(SINGLE_CLICK);				   //������ڻص�������ִ��
			}
			//���������2�Σ�����Ϊ��һ��˫���¼�
			else if (handle->repeat == 2)
			{
				handle->event = (uint8_t)DOUBLE_CLICK; //��˫���¼�����
				EVENT_CB(DOUBLE_CLICK);				   // repeat hit ������ڻص�������ִ��
			}
			else if (handle->repeat == 3)
			{
				handle->event = (uint8_t)PRESS_REPEAT; //�������¼�����
				EVENT_CB(PRESS_REPEAT);				   // repeat hit ������ڻص�������ִ��
			}
			handle->state = 0; //����״̬����Ϊ0��δ���£�
		}
		break;

	case 3: //���ǰ�ΰ���״̬��3���ظ����£����ҵ�ǰ��ƽ������Ч��ƽ������Ϊ�ǰ��������̰����¼�
		if (handle->button_level != handle->active_level)
		{									   //released press up
			handle->event = (uint8_t)PRESS_UP; //�а��������¼�����
			EVENT_CB(PRESS_UP);				   //������ڻص�������ִ��
			//�����¼�Ľ���ʱ��С��300ms��
			if (handle->ticks < SHORT_TICKS)
			{
				handle->ticks = 0; //���ļ�������
				handle->state = 2; //repeat press����״̬����Ϊ2���ɿ���
			}
			else
			{
				handle->state = 0; //����״̬����Ϊ0��δ���£�
			}
		}
		break;

	case 5: //���ǰ�ΰ���״̬��5����������ʼ�����ҵ�ǰ��ƽ����Ч��ƽ������Ϊ���ڳ��������ֳ���״̬
		if (handle->button_level == handle->active_level)
		{
			//continue hold trigger
			handle->event = (uint8_t)LONG_PRESS_HOLD; //�а��������¼�����
			if (handle->ticks % LONG_HOLD_CYC == 0)	//ÿ500ms����һ�λص�����
			{
				EVENT_CB(LONG_PRESS_HOLD); //������ڻص�������ִ��
			}
		}
		else								   //���������Ч��ƽ������Ϊ�ǰ��������¼�
		{									   //releasd
			handle->event = (uint8_t)PRESS_UP; //�а��������¼�����
			EVENT_CB(PRESS_UP);				   //������ڻص�������ִ��
			handle->state = 0;				   //reset����״̬��λ
		}
		break;
	}
}

/**
  * @brief  Start the button work, add the handle into work list.
  * @param  handle: target handle strcut.
  * @retval 0: succeed. -1: already exist.
  */
 //����һ��������������һ�������ṹ������ڵ�
int button_start(struct Button *handle)
{
	struct Button *target = head_handle;
	while (target)
	{
		if (target == handle)
			return -1; //already exist.
		target = target->next;
	}
	handle->next = head_handle;
	head_handle = handle;
	return 0;
}

/**
  * @brief  Stop the button work, remove the handle off work list.
  * @param  handle: target handle strcut.
  * @retval None
  */
 //ֹͣһ������������������ɾ���ð����ڵ�
void button_stop(struct Button *handle)
{
	struct Button **curr;
	for (curr = &head_handle; *curr;)
	{
		struct Button *entry = *curr;
		if (entry == handle)
		{
			*curr = entry->next;
			//			free(entry);
		}
		else
			curr = &entry->next;
	}
}

/**
  * @brief  background ticks, timer repeat invoking interval 5ms.
  * @param  None.
  * @retval None
  */
 //�������ģ�ÿһ�ν����¼����������б������а�����������������
void button_ticks()
{
	struct Button *target;
	for (target = head_handle; target; target = target->next)
	{
		button_handler(target);
	}
}
