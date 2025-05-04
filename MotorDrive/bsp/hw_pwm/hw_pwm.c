#include "hw_pwm.h"
Spwm_typedef spwm={0,0,0,0};

void Hbrige_GPIO_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;

    /*开启按键GPIO口的时钟*/

		__HAL_RCC_GPIOF_CLK_ENABLE();


		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

    /*使用上面的结构体初始化按键*/

		/*Configure GPIO pins : PF3467 */
		GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}
//短接
void Out_AP_CLOSE(void)
{
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET);
}
//悬空
void Out_AM_CLOSE(void)
{
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET);
}
//短接
void Out_BP_CLOSE(void)
{
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
}
//悬空
void Out_BM_CLOSE(void) \
{
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
} 

//pwm
void Out_PWM_AP(uint32_t value)
{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, (value));
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET);
}
void Out_PWM_AM(uint32_t value)
{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, (value));
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET);
}

void Out_PWM_BP(uint32_t value)
{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, (value));
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
}
void Out_PWM_BM(uint32_t value)
{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, (value));
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
}

