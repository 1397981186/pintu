#ifndef __BSP_XPT2046_LCD_H
#define	__BSP_XPT2046_LCD_H


#include "stm32f10x.h"


/******************************* XPT2046 触摸屏触摸信号指示引脚定义(不使用中断) ***************************/
#define             XPT2046_PENIRQ_GPIO_CLK                        RCC_APB2Periph_GPIOE   
#define             XPT2046_PENIRQ_GPIO_PORT                       GPIOE
#define             XPT2046_PENIRQ_GPIO_PIN                        GPIO_Pin_4

//触屏信号有效电平
#define             XPT2046_PENIRQ_ActiveLevel                     0
#define             XPT2046_PENIRQ_Read()                          GPIO_ReadInputDataBit ( XPT2046_PENIRQ_GPIO_PORT, XPT2046_PENIRQ_GPIO_PIN )



/******************************* XPT2046 触摸屏模拟SPI引脚定义 ***************************/
#define             XPT2046_SPI_GPIO_CLK                         RCC_APB2Periph_GPIOE| RCC_APB2Periph_GPIOD

#define             XPT2046_SPI_CS_PIN		                        GPIO_Pin_13
#define             XPT2046_SPI_CS_PORT		                      GPIOD

#define	            XPT2046_SPI_CLK_PIN	                        GPIO_Pin_0
#define             XPT2046_SPI_CLK_PORT	                        GPIOE

#define	            XPT2046_SPI_MOSI_PIN	                        GPIO_Pin_2
#define	            XPT2046_SPI_MOSI_PORT	                      GPIOE

#define	            XPT2046_SPI_MISO_PIN	                        GPIO_Pin_3
#define	            XPT2046_SPI_MISO_PORT	                      GPIOE


#define             XPT2046_CS_ENABLE()                          GPIO_SetBits ( XPT2046_SPI_CS_PORT, XPT2046_SPI_CS_PIN )    
#define             XPT2046_CS_DISABLE()                         GPIO_ResetBits ( XPT2046_SPI_CS_PORT, XPT2046_SPI_CS_PIN )  

#define             XPT2046_CLK_HIGH()                           GPIO_SetBits ( XPT2046_SPI_CLK_PORT, XPT2046_SPI_CLK_PIN )    
#define             XPT2046_CLK_LOW()                            GPIO_ResetBits ( XPT2046_SPI_CLK_PORT, XPT2046_SPI_CLK_PIN ) 

#define             XPT2046_MOSI_1()                             GPIO_SetBits ( XPT2046_SPI_MOSI_PORT, XPT2046_SPI_MOSI_PIN ) 
#define             XPT2046_MOSI_0()                             GPIO_ResetBits ( XPT2046_SPI_MOSI_PORT, XPT2046_SPI_MOSI_PIN )

#define             XPT2046_MISO()                               GPIO_ReadInputDataBit ( XPT2046_SPI_MISO_PORT, XPT2046_SPI_MISO_PIN )



/******************************* XPT2046 触摸屏参数定义 ***************************/
//校准触摸屏时触摸坐标的AD值相差门限 
#define             XPT2046_THRESHOLD_CalDiff                    2               

#define	            XPT2046_CHANNEL_X 	                          0x90 	          //通道Y+的选择控制字	
#define	            XPT2046_CHANNEL_Y 	                          0xd0	          //通道X+的选择控制字

//触摸参数写到FLASH里的标志
#define							FLASH_TOUCH_PARA_FLAG_VALUE					0xA5

//触摸标志写到FLASH里的地址
#define 							FLASH_TOUCH_PARA_FLAG_ADDR						(1*1024)

//触摸参数写到FLASH里的地址
#define 							FLASH_TOUCH_PARA_ADDR									(2*1024)


/*信息输出*/
#define XPT2046_DEBUG_ON         0

#define XPT2046_INFO(fmt,arg...)           printf("<<-XPT2046-INFO->> "fmt"\n",##arg)
#define XPT2046_ERROR(fmt,arg...)          printf("<<-XPT2046-ERROR->> "fmt"\n",##arg)
#define XPT2046_DEBUG(fmt,arg...)          do{\
                                          if(XPT2046_DEBUG_ON)\
                                          printf("<<-XPT2046-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)

/******************************* 声明 XPT2046 相关的数据类型 ***************************/
typedef	struct          //液晶坐标结构体 
{		
	/*负数值表示无新数据*/
   int16_t x;			//记录最新的触摸参数值
   int16_t y; 
	
	/*用于记录连续触摸时(长按)的上一次触摸位置*/
	 int16_t pre_x;		
   int16_t pre_y;
	
} strType_XPT2046_Coordinate;   


typedef struct         //校准因子结构体 
{
	 float An,  		 //注:sizeof(long double) = 8
					Bn,     
					Cn,   
					Dn,    
					En,    
					Fn,     
					Divider;
	
} strType_XPT2046_Calibration;


typedef struct         //校准系数结构体（最终使用）
{
	 float dX_X,  			 
					dX_Y,     
					dX,   
					dY_X,    
					dY_Y,    
					dY;

} strType_XPT2046_TouchPara;

/******触摸状态机相关******/
typedef enum
{
	XPT2046_STATE_RELEASE  = 0,	//触摸释放
	XPT2046_STATE_WAITING,			//触摸按下
	XPT2046_STATE_PRESSED,			//触摸按下
}enumTouchState	;

#define TOUCH_PRESSED 				1
#define TOUCH_NOT_PRESSED			0

//触摸消抖阈值
#define DURIATION_TIME				2

/******************************* 声明 XPT2046 相关的外部全局变量 ***************************/
extern volatile uint8_t               ucXPT2046_TouchFlag;

extern strType_XPT2046_TouchPara      strXPT2046_TouchPara[];
extern int touchcount;
extern char* map[][3];
extern int flag;

/******************************** XPT2046 触摸屏函数声明 **********************************/
void XPT2046_Init( void );
void XPT2046_initialmap(char* map[][3]);
void display(char* map[][3]);
uint8_t XPT2046_Touch_Calibrate( uint8_t LCD_Mode );
uint8_t XPT2046_Get_TouchedPoint( strType_XPT2046_Coordinate * displayPtr, strType_XPT2046_TouchPara * para );
void XPT2046_TouchDown(strType_XPT2046_Coordinate * touch);
void XPT2046_TouchUp(strType_XPT2046_Coordinate * touch);
void XPT2046_TouchEvenHandler(void );
void Calibrate_or_Get_TouchParaWithFlash(uint8_t LCD_Mode,uint8_t forceCal);

////////////////////////////////////////////

#define COLOR_BLOCK_WIDTH   40
#define COLOR_BLOCK_HEIGHT  28

#define BUTTON_NUM 1
#define PALETTE_START_Y   0
#define PALETTE_END_Y     LCD_Y_LENGTH

#if 1     //按钮栏在左边
  #define BUTTON_START_X      0
  #define PALETTE_START_X   (COLOR_BLOCK_WIDTH*2+1)
  #define PALETTE_END_X     LCD_X_LENGTH

#else     //按钮栏在右边，(存在触摸按键时也会的bug仅用于测试触摸屏左边界)
  #define BUTTON_START_X      (LCD_X_LENGTH-2*COLOR_BLOCK_WIDTH)
  #define PALETTE_START_X   	0
  #define PALETTE_END_X     	(LCD_X_LENGTH-2*COLOR_BLOCK_WIDTH)

#endif



/*
	LCD 颜色代码，CL_是Color的简写
	16Bit由高位至低位， RRRR RGGG GGGB BBBB

	下面的RGB 宏将24位的RGB值转换为16位格式。
	启动windows的画笔程序，点击编辑颜色，选择自定义颜色，可以获得的RGB值。

	推荐使用迷你取色器软件获得你看到的界面颜色。
*/
#if LCD_RGB_888
/*RGB888颜色转换*/
#define RGB(R,G,B)	( (R<< 16) | (G << 8) | (B))	/* 将8位R,G,B转化为 24位RGB888格式 */

#else 
/*RGB565 颜色转换*/
#define RGB(R,G,B)	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	/* 将8位R,G,B转化为 16位RGB565格式 */
#define RGB565_R(x)  ((x >> 8) & 0xF8)
#define RGB565_G(x)  ((x >> 3) & 0xFC)
#define RGB565_B(x)  ((x << 3) & 0xF8)

#endif


enum
{
	CL_WHITE    = RGB(255,255,255),	/* 白色 */
	CL_BLACK    = RGB(  0,  0,  0),	/* 黑色 */
	CL_RED      = RGB(255,	0,  0),	/* 红色 */
	CL_GREEN    = RGB(  0,255,  0),	/* 绿色 */
	CL_BLUE     = RGB(  0,	0,255),	/* 蓝色 */
	CL_YELLOW   = RGB(255,255,  0),	/* 黄色 */

	CL_GREY    = RGB( 98, 98, 98), 	/* 深灰色 */
	CL_GREY1		= RGB( 150, 150, 150), 	/* 浅灰色 */
	CL_GREY2		= RGB( 180, 180, 180), 	/* 浅灰色 */
	CL_GREY3		= RGB( 200, 200, 200), 	/* 最浅灰色 */
	CL_GREY4		= RGB( 230, 230, 230), 	/* 最浅灰色 */

	CL_BUTTON_GREY	= RGB( 195, 195, 195), /* WINDOWS 按钮表面灰色 */

	CL_MAGENTA      = RGB(255, 0, 255),	/* 红紫色，洋红色 */
	CL_CYAN         = RGB( 0, 255, 255),	/* 蓝绿色，青色 */

	CL_BLUE1        = RGB(  0,  0, 240),		/* 深蓝色 */
	CL_BLUE2        = RGB(  0,  0, 128),		/* 深蓝色 */
	CL_BLUE3        = RGB(  68, 68, 255),		/* 浅蓝色1 */
	CL_BLUE4        = RGB(  0, 64, 128),		/* 浅蓝色1 */

	/* UI 界面 Windows控件常用色 */
	CL_BTN_FACE		  = RGB(236, 233, 216),	/* 按钮表面颜色(灰) */
	CL_BOX_BORDER1	= RGB(172, 168,153),	/* 分组框主线颜色 */
	CL_BOX_BORDER2	= RGB(255, 255,255),	/* 分组框阴影线颜色 */

	CL_MASK			    = 0x7FFF	/* RGB565颜色掩码，用于文字背景透明 */
};

typedef struct 
{
  uint16_t start_x;   //按键的x起始坐标  
  uint16_t start_y;   //按键的y起始坐标
  uint16_t end_x;     //按键的x结束坐标 
  uint16_t end_y;     //按键的y结束坐标
  uint32_t para;      //颜色按钮中表示选择的颜色，笔迹形状按钮中表示选择的画刷
  uint8_t touch_flag; //按键按下的标志
    
  void (*draw_btn)(void * btn);     //按键描绘函数
  void (*btn_command)(void * btn);  //按键功能执行函数，例如切换颜色、画刷
 
}Touch_Button;


void Show(uint16_t x,uint16_t y);
void Palette_Init(uint8_t LCD_Mode);
void Touch_Button_Init(void);

#endif /* __BSP_TOUCH_H */

