#include "led.h"

void led_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(_LED_RCC_PERIPH, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = _LED_PIN_RECYCLABLE | _LED_PIN_HAZARDOUS | _LED_PIN_DRY | _LED_PIN_WET;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(_LED_PERIPH, &GPIO_InitStructure);
	
	GPIO_SetBits(_LED_PERIPH, _LED_PIN_RECYCLABLE | _LED_PIN_HAZARDOUS | _LED_PIN_DRY | _LED_PIN_WET);					
}

/*
 * ¿É»ØÊÕÀ¬»ø
 */
void turn_recyclable(void)
{
	GPIO_SetBits(_LED_PERIPH, _LED_PIN_HAZARDOUS | _LED_PIN_DRY | _LED_PIN_WET);
	GPIO_ResetBits(_LED_PERIPH, _LED_PIN_RECYCLABLE);
}

/*
 * ÓÐº¦À¬»ø
 */
void turn_hazardous(void)
{
	GPIO_SetBits(_LED_PERIPH, _LED_PIN_RECYCLABLE | _LED_PIN_DRY | _LED_PIN_WET);
	GPIO_ResetBits(_LED_PERIPH, _LED_PIN_HAZARDOUS);
}

/*
 * ¸ÉÀ¬»ø
 */
void turn_dry(void)
{
	GPIO_SetBits(_LED_PERIPH, _LED_PIN_RECYCLABLE | _LED_PIN_HAZARDOUS | _LED_PIN_WET);
	GPIO_ResetBits(_LED_PERIPH, _LED_PIN_DRY);
}

/*
 * ÊªÀ¬»ø
 */
void turn_wet(void)
{
	GPIO_SetBits(_LED_PERIPH, _LED_PIN_RECYCLABLE | _LED_PIN_HAZARDOUS | _LED_PIN_DRY);
	GPIO_ResetBits(_LED_PERIPH, _LED_PIN_WET);
}
