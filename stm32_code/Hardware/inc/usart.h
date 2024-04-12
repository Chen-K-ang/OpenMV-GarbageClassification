#ifndef HARDWARE_USART_H
#define HARDWARE_USART_H

#include <stm32f10x.h>

#define OPENMV_BUF_SIZE 3
#define OPENMV_BUF_HEAD 0xAA    /* 包头 */
#define OPENMV_BUF_TAIL 0x55    /* 包尾 */
#define OPENMV_SEND_DATA 1

#define OPENMV_BAUDRATE 115200  /* 波特率 */
 
#define IS_RECYCLABLE 0x00
#define IS_HAZARDOUS  0x01
#define IS_DRY        0x02
#define IS_WET        0x03

void uart1_init(u32 bound);

extern uint8_t openmv_recflag;
extern uint8_t openmv_recdate_pack[OPENMV_BUF_SIZE];

#endif /* no define HARDWARE_USART_H */
