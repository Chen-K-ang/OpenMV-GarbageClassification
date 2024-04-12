#ifndef HARDWARE_LED_H
#define HARDWARE_LED_H

#include <stm32f10x.h>

#define _LED_RCC_PERIPH RCC_APB2Periph_GPIOA
#define _LED_PERIPH     GPIOA

#define _LED_PIN_RECYCLABLE GPIO_Pin_1
#define _LED_PIN_HAZARDOUS  GPIO_Pin_2
#define _LED_PIN_DRY        GPIO_Pin_3
#define _LED_PIN_WET        GPIO_Pin_4

/* LED引脚初始化 */
void led_init(void);

/* 不同模式下的指示灯 */
void turn_recyclable(void); /* 蓝灯 */
void turn_hazardous(void);  /* 红灯 */
void turn_dry(void);        /* 黄灯 */
void turn_wet(void);        /* 绿灯 */

#endif /* no define HARDWARE_LED_H */
