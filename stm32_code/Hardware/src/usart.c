#include "usart.h"

void uart1_init(u32 bound)
{
	/* ����һ������ų�ʼ��*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);   /* ʹ��USART1��GPIOAʱ�� */

	/* ������������ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; /* ����������� */
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ������������ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; /* �������� */
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* ����һ���� */
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = bound;                                     /* ���ڲ����� */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     /* �ֳ�Ϊ8λ���ݸ�ʽ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          /* һ��ֹͣλ */
	USART_InitStructure.USART_Parity = USART_Parity_No;                             /* ����żУ��λ */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /* ��Ӳ������������ */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 /* �շ�ģʽ */

	USART_Init(USART1, &USART_InitStructure);      /* ��ʼ������1 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); /* �������ڽ����ж� */
	USART_Cmd(USART1, ENABLE);                     /* ʹ�ܴ���1 */

	/* ����һ�ж����� */
	NVIC_InitTypeDef  NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; /* ��ռ���ȼ�3 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	   /* �����ȼ�3   */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		   /* IRQͨ��ʹ�� */
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
			 * ������ݰ���ͷΪ OPENMV_BUF_HEAD �� 0xAA�����н�������
			 * ����openmv_recflag=1�������½����ж�ʱ�����Խ�����һ��case
			 */
			openmv_recdate_sum = 1;
			openmv_recdate_pack[0] = openmv_recdata;
			openmv_recflag = 1;
		}
		break;
	case 1:
		/* 
		 * �Խ��յ����ݽ��м��������Ϊ OPENMV_BUF_SIZE �� 3�����жϰ�β OPENMV_BUF_TAIL
		 */
		openmv_recdate_pack[openmv_recdate_sum] = openmv_recdata;
		openmv_recdate_sum++;
		if (openmv_recdate_sum == OPENMV_BUF_SIZE) {
			if(openmv_recdate_pack[OPENMV_BUF_SIZE - 1] == OPENMV_BUF_TAIL) {
				openmv_recflag = 2; /* ���ݰ���ȷ������δ��ʧ */
			} else {
				openmv_recflag = 0;
			}
		}
		break;
	}
}
