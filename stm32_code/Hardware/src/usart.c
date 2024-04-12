#include "usart.h"

void uart1_init(u32 bound)
{
	/* 串口一相关引脚初始化*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);   /* 使能USART1，GPIOA时钟 */

	/* 发送数据引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; /* 复用推挽输出 */
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 接收数据引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; /* 浮空输入 */
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 串口一配置 */
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = bound;                                     /* 串口波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     /* 字长为8位数据格式 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          /* 一个停止位 */
	USART_InitStructure.USART_Parity = USART_Parity_No;                             /* 无奇偶校验位 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /* 无硬件数据流控制 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 /* 收发模式 */

	USART_Init(USART1, &USART_InitStructure);      /* 初始化串口1 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); /* 开启串口接受中断 */
	USART_Cmd(USART1, ENABLE);                     /* 使能串口1 */

	/* 串口一中断配置 */
	NVIC_InitTypeDef  NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; /* 抢占优先级3 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	   /* 子优先级3   */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		   /* IRQ通道使能 */
	NVIC_Init(&NVIC_InitStructure);
}

uint8_t	openmv_recflag = 0;
uint8_t openmv_recdata = 0;
uint8_t openmv_recdate_sum = 0;
uint8_t openmv_recdate_pack[OPENMV_BUF_SIZE] = {0};

void USART1_IRQHandler(void)
{
	openmv_recdata = (uint8_t)(USART3->DR & (uint8_t)0x00FF);

	switch (openmv_recflag) {
	case 0: 
		if (openmv_recdata == OPENMV_BUF_HEAD) {
			/* 
			 * 如果数据包包头为 OPENMV_BUF_HEAD 即 0xAA，进行接收数据
			 * 并置openmv_recflag=1，待重新进入中断时，可以进入下一个case
			 */
			openmv_recdate_sum = 1;
			openmv_recdate_pack[0] = openmv_recdata;
			openmv_recflag = 1;
		}
		break;
	case 1:
		/* 
		 * 对接收的数据进行计数，如果为 OPENMV_BUF_SIZE 即 3，则判断包尾 OPENMV_BUF_TAIL
		 */
		openmv_recdate_pack[openmv_recdate_sum] = openmv_recdata;
		openmv_recdate_sum++;
		if (openmv_recdate_sum == OPENMV_BUF_SIZE) {
			if(openmv_recdate_pack[OPENMV_BUF_SIZE - 1] == OPENMV_BUF_TAIL) {
				openmv_recflag = 2; /* 数据包正确，数据未丢失 */
			} else {
				openmv_recflag = 0;
			}
		}
		break;
	}
}
