
  

#include "bsp_key.h" 
//按键+LED灯

//定义按键实例
Button_Typedef button[Button_Quan];

/**

  * @brief  配置按键用到的I/O口

  * @param  无

  * @retval 无

  */

void Key_GPIO_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启按键GPIO口的时钟*/

    KEY1_GPIO_CLK_ENABLE();

    /*选择按键的引脚 PE1 PE2 PE3 PE4 PE0*/	
		GPIO_InitStructure.Pin = KEY1_PIN|KEY2_PIN|KEY3_PIN|KEY4_PIN
														|KEY5_PIN;

    /*设置引脚为输入模式*/

    GPIO_InitStructure.Mode = GPIO_MODE_INPUT; 


    /*设置引脚上拉*/

    GPIO_InitStructure.Pull = GPIO_PULLUP ;

    /*使用上面的结构体初始化按键*/

    HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
		
}





/**
  * @brief  按键读取
  * @param  NULL
  * @retval true  : 按下
  * @retval false : 弹起
***/
bool Button_Read_Level(uint16_t button_num)
{
	switch(button_num)
	{
		#ifdef KEY1_GPIO_CLK_ENABLE
		case Button_1:			return ((bool)HAL_GPIO_ReadPin(KEY1_GPIO_PORT,KEY1_PIN));		//高电平为按下
		#endif
		#ifdef KEY2_GPIO_CLK_ENABLE
		case Button_2:			return ((bool)HAL_GPIO_ReadPin(KEY2_GPIO_PORT,KEY2_PIN));		//高电平为按下
		#endif
		#ifdef KEY3_GPIO_CLK_ENABLE
		case Button_3:		return ((bool)HAL_GPIO_ReadPin(KEY3_GPIO_PORT,KEY3_PIN));	//高电平为按下
		#endif
		#ifdef KEY4_GPIO_CLK_ENABLE
		case Button_4:			return ((bool)HAL_GPIO_ReadPin(KEY4_GPIO_PORT,KEY4_PIN));		//高电平为按下
		#endif
		#ifdef KEY5_GPIO_CLK_ENABLE
		case Button_5:		return ((bool)HAL_GPIO_ReadPin(KEY5_GPIO_PORT,KEY5_PIN));	//高电平为按下
		#endif

		default:						return false;
	}
}



/**
  * @brief  按键初始化
  * @param  NULL
  * @retval NULL
***/
void Button_Init(void)
{
	//配置外设
	Key_GPIO_Config();
	
	for(uint16_t i=0; i<Button_Quan; i++)
	{
		//数据
		button[i].level = false;
		button[i].state = Button_Bit_Up;
		button[i].time_ms = 0;
	}
}

/**
  * @brief  获取按键状态
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
  * @brief  按键定时扫描
  * @param  NULL
  * @retval NULL
***/
void Button_Scan_ms(uint32_t _time)
{
	for(uint16_t i=0; i<Button_Quan; i++)
	{
		//提取按键
		button[i].level = Button_Read_Level(i);

		//按键状态处理
		switch(button[i].state)
		{
			//状态_弹起
			case Button_Bit_Up:
				if(button[i].level){
					button[i].state = Button_Bit_Shake;
					button[i].time_ms = 0;
				}
			break;
			//状态_抖动
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
			//状态_按下
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
			//状态_长按
			case Button_Bit_Long:
				if(button[i].level){
					button[i].state = Button_Bit_Long;
				}
				else{
					button[i].state = Button_Bit_LongRise;
				}
			break;
			//边沿_按下
			case Button_Bit_Drop:
				if(button[i].level){
					button[i].state = Button_Bit_Press;
					button[i].time_ms = 0;
				}
				else{
					button[i].state = Button_Bit_Up;
				}
			break;
			//边沿_弹起
			case Button_Bit_Rise:
				button[i].state = Button_Bit_Up;
			break;
			//边沿_长按按下
			case Button_Bit_LongDrop:
				if(button[i].level){
					button[i].state = Button_Bit_Long;
					button[i].time_ms = 0;
				}
				else{
					button[i].state = Button_Bit_Up;
				}
			break;
			//边沿_长按弹起
			case Button_Bit_LongRise:
				button[i].state = Button_Bit_Up;
			break;
		}	
	}
}

/**

  * @brief   检测是否有按键按下

  *		@arg KEY_ON:按键按下

  *		@arg KEY_OFF:按键没按下

  */

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)

{			

	/*检测是否有按键按下 */

	if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON )  

	{	 

		/*等待按键释放 */

		while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON);   

		return 	KEY_ON;	 

	}

	else

		return KEY_OFF;

}

/**

  * @brief  配置LED灯用到的I/O口

  * @param  无

  * @retval 无

  */
void LED_GPIO_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;

    /*开启按键GPIO口的时钟*/

		__HAL_RCC_GPIOE_CLK_ENABLE();
		__HAL_RCC_GPIOH_CLK_ENABLE();


		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOH, GPIO_PIN_9, GPIO_PIN_RESET);

    /*使用上面的结构体初始化按键*/

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

