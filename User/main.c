/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 ����ģ��
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
#include "board.h"
#include "rtthread.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./lcd/bsp_xpt2046_lcd.h"
/*
*************************************************************************
*                               ����
*************************************************************************
*/
/* �����߳̿��ƿ� */
static rt_thread_t test_thread = RT_NULL;

/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void test_thread_entry(void* parameter);

/*
*************************************************************************
*                             main ����
*************************************************************************
*/
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
    /* 
	 * ������Ӳ����ʼ����RTTϵͳ��ʼ���Ѿ���main����֮ǰ��ɣ�
	 * ����component.c�ļ��е�rtthread_startup()����������ˡ�
	 * ������main�����У�ֻ��Ҫ�����̺߳������̼߳��ɡ�
	 */
	test_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "test",              /* �߳����� */
                      test_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      512,                 /* �߳�ջ��С */
                      3,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (test_thread != RT_NULL)
        rt_thread_startup(test_thread);
    else
        return -1;
		
}

/*
*************************************************************************
*                             �̶߳���
*************************************************************************
*/
/************************************************************
  * @brief   test_thread_entry
  * @param   NULL
  * @return  NULL
  * @author  fire
  * @github  
  * @date    2018-xx-xx
  * @version v1.0
	* @note    �˴���dma����ʵ�飬Ұ�����д��rt_hw_console_output������
						 rt_kprintf��ʹ���˴���dma��ӡ��
  ***********************************************************/
static void test_thread_entry(void* parameter)
{
	while (1)
	{
		if (touchcount==0)
		{
			XPT2046_initialmap(map);
		}
	XPT2046_TouchEvenHandler();
	unsigned char * title1 ="ƴ";
	unsigned char * title2 ="ͼ";
	unsigned char * title3 ="��";
	unsigned char * title4 ="Ϸ";
	ILI9341_DisplayStringEx(20,20,40,40,title1,0);
	ILI9341_DisplayStringEx(20,60,40,40,title2,0);
	ILI9341_DisplayStringEx(20,100,40,40,title3,0);
	ILI9341_DisplayStringEx(20,140,40,40,title4,0);
	rt_thread_delay(10);
	}
}

/********************************END OF FILE****************************/
