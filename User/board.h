#ifndef __BOARD_H__
#define __BOARD_H__

/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/
/* STM32 固件库头文件 */
#include "stm32f10x.h"

/* 开发板硬件bsp头文件 */
#include "bsp_led.h"
#include "bsp_usart.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./lcd/bsp_xpt2046_lcd.h"
#include "./flash/bsp_spi_flash.h"
#include "./led/bsp_led.h" 
//#include "palette.h"
/*
*************************************************************************
*                               函数声明
*************************************************************************
*/
void rt_hw_board_init(void);
void SysTick_Handler(void);
	

#endif /* __BOARD_H__ */
