#ifndef HARDWARE_LED_H
#define HARDWARE_LED_H

#include <stm32f10x.h>

#define _LED_RCC_PERIPH RCC_APB2Periph_GPIOA
#define _LED_PERIPH     GPIOA

#define _LED_PIN_RECYCLABLE GPIO_Pin_1
#define _LED_PIN_HAZARDOUS  GPIO_Pin_2
#define _LED_PIN_DRY        GPIO_Pin_3
#define _LED_PIN_WET        GPIO_Pin_4

/* LED���ų�ʼ�� */
void led_init(void);

/* ��ͬģʽ�µ�ָʾ�� */
void turn_recyclable(void); /* ���� */
void turn_hazardous(void);  /* ��� */
void turn_dry(void);        /* �Ƶ� */
void turn_wet(void);        /* �̵� */

#endif /* no define HARDWARE_LED_H */
