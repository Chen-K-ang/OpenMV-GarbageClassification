#include "motor.h"

void motor_gpio_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(_MOTOR_RCC_PERIPH, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = _ULN2004A_PIN_1 | _ULN2004A_PIN_2 | _ULN2004A_PIN_3 | _ULN2004A_PIN_4;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(_MOTOR_PERIPH, &GPIO_InitStructure);
	
	GPIO_SetBits(_MOTOR_PERIPH, _ULN2004A_PIN_1 | _ULN2004A_PIN_2 | _ULN2004A_PIN_3 | _ULN2004A_PIN_4);
}

/*步进电机四相八拍*/
static const unsigned char reverse[8] = {0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09}; /* 逆时针旋转 */
static const unsigned char forward[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08}; /* 顺时针旋转 */

/*
 * 输入参数：n, 电机旋转圈数, 64为一圈
 *           direction, 电机旋转方向
 *           delay, 步进间隔时间
 */
void motor_circle(char n, char direction, char delay)
{
	for (char i = 0; i < n; i++) {
		for (char j = 0; j < 8; j++) {
			if (direction == 1) {
				set_motor_pin(forward[j]);
			} else {
				set_motor_pin(reverse[j]);
			}
			delay_ms(2);
		}
	}
}

static void set_motor_pin(char pin_data)
{
	if (pin_data & 0x01) {
		GPIO_SetBits(_MOTOR_PERIPH, _ULN2004A_PIN_1);
	} else {
		GPIO_ResetBits(_MOTOR_PERIPH, _ULN2004A_PIN_1);
	}

	if (pin_data & 0x02) {
		GPIO_SetBits(_MOTOR_PERIPH, _ULN2004A_PIN_2);
	} else {
		GPIO_ResetBits(_MOTOR_PERIPH, _ULN2004A_PIN_2);
	}

	if (pin_data & 0x04) {
		GPIO_SetBits(_MOTOR_PERIPH, _ULN2004A_PIN_3);
	} else {
		GPIO_ResetBits(_MOTOR_PERIPH, _ULN2004A_PIN_3);
	}
	
	if (pin_data & 0x08) {
		GPIO_SetBits(_MOTOR_PERIPH, _ULN2004A_PIN_4);
	} else {
		GPIO_ResetBits(_MOTOR_PERIPH, _ULN2004A_PIN_4);
	}
}
