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

#define MOTOR_FORWARD 1 /*电机正转，顺时针旋转*/
#define MOTOR_REVERSE 0 /*电机反转，逆时针旋转*/

/* 电机引脚初始化 */
void motor_gpio_init(void); 

/* 控制电机的旋转圈数、旋转方向以及间隔时间 */
void motor_circle(char n, char derection, char delay);

/* 控制电机四个引脚的高低电平 */
static void set_motor_pin(char pin_data);
	
#endif /* no define HARDWARE_MOTOR_H */
