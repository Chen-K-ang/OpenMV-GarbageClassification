#ifndef HARDWARE_MOTOR_H
#define HARDWARE_MOTOR_H

#include <stm32f10x.h>
#include <delay.h>

#define _MOTOR_RCC_PERIPH RCC_APB2Periph_GPIOC
#define _MOTOR_PERIPH     GPIOC

#define _ULN2004A_PIN_1 GPIO_Pin_0
#define _ULN2004A_PIN_2 GPIO_Pin_1
#define _ULN2004A_PIN_3 GPIO_Pin_2
#define _ULN2004A_PIN_4 GPIO_Pin_3

#define MOTOR_FORWARD 1 /*�����ת��˳ʱ����ת*/
#define MOTOR_REVERSE 0 /*�����ת����ʱ����ת*/

/* ������ų�ʼ�� */
void motor_gpio_init(void); 

/* ���Ƶ������תȦ������ת�����Լ����ʱ�� */
void motor_circle(char n, char derection, char delay);

/* ���Ƶ���ĸ����ŵĸߵ͵�ƽ */
static void set_motor_pin(char pin_data);
	
#endif /* no define HARDWARE_MOTOR_H */
