#ifndef  _LCD_GPIOConfig
#define  _LCD_GPIOConfig

//LCD_CS PB0
#define	LCD_CS					GPIOB
#define PIO_CS					GPIO_Pin_0
#define LCD_CS_H				GPIO_SetBits( LCD_CS , PIO_CS )
#define LCD_CS_L	    	    GPIO_ResetBits( LCD_CS , PIO_CS )

//LCD_RES PB1
#define	LCD_RES					GPIOB
#define PIO_RES					GPIO_Pin_1
#define LCD_RES_H				GPIO_SetBits( LCD_RES , PIO_RES )
#define LCD_RES_L				GPIO_ResetBits( LCD_RES , PIO_RES )

//LCD_A0 PB5
#define	LCD_A0					GPIOB
#define PIO_A0					GPIO_Pin_5
#define LCD_A0_H				GPIO_SetBits( LCD_A0 , PIO_A0 )
#define LCD_A0_L				GPIO_ResetBits( LCD_A0 , PIO_A0 ) 

//LCD_SCK PB6
#define	LCD_CLK					GPIOB
#define PIO_CLK					GPIO_Pin_6
#define LCD_CLK_H				GPIO_SetBits( LCD_CLK, PIO_CLK)
#define LCD_CLK_L				GPIO_ResetBits( LCD_CLK, PIO_CLK)
 
//LCD_SDI PB7
#define	LCD_SDI					GPIOB
#define PIO_SDI		    	    GPIO_Pin_7
#define LCD_SDI_H				GPIO_SetBits( LCD_SDI, PIO_SDI)
#define LCD_SDI_L				GPIO_ResetBits( LCD_SDI , PIO_SDI)

#endif
