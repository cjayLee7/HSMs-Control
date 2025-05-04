
  

#include "bsp_key.h" 
//����+LED��

//���尴��ʵ��
Button_Typedef button[Button_Quan];

/**

  * @brief  ���ð����õ���I/O��

  * @param  ��

  * @retval ��

  */

void Key_GPIO_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    /*��������GPIO�ڵ�ʱ��*/

    KEY1_GPIO_CLK_ENABLE();

    /*ѡ�񰴼������� PE1 PE2 PE3 PE4 PE0*/	
		GPIO_InitStructure.Pin = KEY1_PIN|KEY2_PIN|KEY3_PIN|KEY4_PIN
														|KEY5_PIN;

    /*��������Ϊ����ģʽ*/

    GPIO_InitStructure.Mode = GPIO_MODE_INPUT; 


    /*������������*/

    GPIO_InitStructure.Pull = GPIO_PULLUP ;

    /*ʹ������Ľṹ���ʼ������*/

    HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
		
}





/**
  * @brief  ������ȡ
  * @param  NULL
  * @retval true  : ����
  * @retval false : ����
***/
bool Button_Read_Level(uint16_t button_num)
{
	switch(button_num)
	{
		#ifdef KEY1_GPIO_CLK_ENABLE
		case Button_1:			return ((bool)HAL_GPIO_ReadPin(KEY1_GPIO_PORT,KEY1_PIN));		//�ߵ�ƽΪ����
		#endif
		#ifdef KEY2_GPIO_CLK_ENABLE
		case Button_2:			return ((bool)HAL_GPIO_ReadPin(KEY2_GPIO_PORT,KEY2_PIN));		//�ߵ�ƽΪ����
		#endif
		#ifdef KEY3_GPIO_CLK_ENABLE
		case Button_3:		return ((bool)HAL_GPIO_ReadPin(KEY3_GPIO_PORT,KEY3_PIN));	//�ߵ�ƽΪ����
		#endif
		#ifdef KEY4_GPIO_CLK_ENABLE
		case Button_4:			return ((bool)HAL_GPIO_ReadPin(KEY4_GPIO_PORT,KEY4_PIN));		//�ߵ�ƽΪ����
		#endif
		#ifdef KEY5_GPIO_CLK_ENABLE
		case Button_5:		return ((bool)HAL_GPIO_ReadPin(KEY5_GPIO_PORT,KEY5_PIN));	//�ߵ�ƽΪ����
		#endif

		default:						return false;
	}
}



/**
  * @brief  ������ʼ��
  * @param  NULL
  * @retval NULL
***/
void Button_Init(void)
{
	//��������
	Key_GPIO_Config();
	
	for(uint16_t i=0; i<Button_Quan; i++)
	{
		//����
		button[i].level = false;
		button[i].state = Button_Bit_Up;
		button[i].time_ms = 0;
	}
}

/**
  * @brief  ��ȡ����״̬
  * @param  NULL
  * @retval NULL
***/
Button_State_Typedef Button_Inquice_State(uint16_t button_num)
{
	if(button_num < Button_Quan)
	{
		return button[button_num].state;
	}
	else
	{
		return Button_Bit_Up;
	}
}

/**
  * @brief  ������ʱɨ��
  * @param  NULL
  * @retval NULL
***/
void Button_Scan_ms(uint32_t _time)
{
	for(uint16_t i=0; i<Button_Quan; i++)
	{
		//��ȡ����
		button[i].level = Button_Read_Level(i);

		//����״̬����
		switch(button[i].state)
		{
			//״̬_����
			case Button_Bit_Up:
				if(button[i].level){
					button[i].state = Button_Bit_Shake;
					button[i].time_ms = 0;
				}
			break;
			//״̬_����
			case Button_Bit_Shake:
				if(button[i].level){
					button[i].time_ms += _time;
					if(button[i].time_ms > Button_Shake_Time)
					{
						button[i].state = Button_Bit_Drop;
						button[i].time_ms = 0;
					}
				}
				else{
					button[i].state = Button_Bit_Up;
					button[i].time_ms = 0;
				}
			break;
			//״̬_����
			case Button_Bit_Press:
				if(button[i].level){
					button[i].time_ms += _time;
					if(button[i].time_ms > Button_Long_Time)
					{
						button[i].state = Button_Bit_LongDrop;
						button[i].time_ms = 0;
					}
				}
				else{
					button[i].state = Button_Bit_Rise;
					button[i].time_ms = 0;
				}
			break;
			//״̬_����
			case Button_Bit_Long:
				if(button[i].level){
					button[i].state = Button_Bit_Long;
				}
				else{
					button[i].state = Button_Bit_LongRise;
				}
			break;
			//����_����
			case Button_Bit_Drop:
				if(button[i].level){
					button[i].state = Button_Bit_Press;
					button[i].time_ms = 0;
				}
				else{
					button[i].state = Button_Bit_Up;
				}
			break;
			//����_����
			case Button_Bit_Rise:
				button[i].state = Button_Bit_Up;
			break;
			//����_��������
			case Button_Bit_LongDrop:
				if(button[i].level){
					button[i].state = Button_Bit_Long;
					button[i].time_ms = 0;
				}
				else{
					button[i].state = Button_Bit_Up;
				}
			break;
			//����_��������
			case Button_Bit_LongRise:
				button[i].state = Button_Bit_Up;
			break;
		}	
	}
}

/**

  * @brief   ����Ƿ��а�������

  *		@arg KEY_ON:��������

  *		@arg KEY_OFF:����û����

  */

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)

{			

	/*����Ƿ��а������� */

	if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON )  

	{	 

		/*�ȴ������ͷ� */

		while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON);   

		return 	KEY_ON;	 

	}

	else

		return KEY_OFF;

}

/**

  * @brief  ����LED���õ���I/O��

  * @param  ��

  * @retval ��

  */
void LED_GPIO_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;

    /*��������GPIO�ڵ�ʱ��*/

		__HAL_RCC_GPIOE_CLK_ENABLE();
		__HAL_RCC_GPIOH_CLK_ENABLE();


		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOH, GPIO_PIN_9, GPIO_PIN_RESET);

    /*ʹ������Ľṹ���ʼ������*/

		/*Configure GPIO pins : PE5 PE6 */
		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		/*Configure GPIO pin : PH9 */
		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
		
}
/*********************************************END OF FILE**********************/

