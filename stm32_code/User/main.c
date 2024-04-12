#include "main.h"

int main(void)
{
	led_init();
	uart1_init(OPENMV_BAUDRATE); /* 初始化串口1，与OpenMV通信*/
	motor_gpio_init();
	
	while (1) {
		if (openmv_recflag) {
			openmv_recflag = 0;
			
			/* 根据接收的数据，电机旋转相应角度， 并亮起指示灯 */
			switch (openmv_recdate_pack[OPENMV_SEND_DATA]) {
				
			case IS_RECYCLABLE:
				motor_circle(16, MOTOR_FORWARD, 2);
				turn_recyclable();
				break;
			
			case IS_HAZARDOUS:
				motor_circle(32, MOTOR_FORWARD, 2);
				turn_hazardous();
				break;
			
			case IS_DRY:
				motor_circle(48, MOTOR_FORWARD, 2);
				turn_dry();
				break;
			
			case IS_WET:
				motor_circle(64, MOTOR_FORWARD, 2);
				turn_wet();
				break;
			}
		}
		
	}
}
