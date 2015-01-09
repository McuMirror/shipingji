/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           bsp.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        �弶��ض���
**                      
**------------------------------------------------------------------------------------------------------
** Created by:           
** Created date:        2011-07-22
** Version:              
** Descriptions:        The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:        
**
********************************************************************************************************/
#ifndef __BSP_H 
#define __BSP_H

#include "..\config.h"
#include "..\driver\LPC17xx.h"
#include "..\driver\lpc17xx_gpio.h"
#include "..\driver\lpc17xx_pinsel.h"
#include "global.h"

#define UART2MODESELECT0 (1<<29)			//P1.29 select as GPIO IN LPC1700PinCfg.h
#define UART2MODESELECT1 (1<<28)			//P1.28 select as GPIO IN LPC1700PinCfg.h
#define MDB_MODE_SET()   		LPC_GPIO1->FIODIR |= UART2MODESELECT0;\
								LPC_GPIO1->FIODIR |= UART2MODESELECT1;\
								LPC_GPIO1->FIOCLR |= UART2MODESELECT0;\
								LPC_GPIO1->FIOCLR |= UART2MODESELECT1
#define EVB0_MODE_SET()   		LPC_GPIO1->FIODIR |= UART2MODESELECT0;\
								LPC_GPIO1->FIODIR |= UART2MODESELECT1;\
								LPC_GPIO1->FIOSET |= UART2MODESELECT0;\
								LPC_GPIO1->FIOCLR |= UART2MODESELECT1
#define EVB1_MODE_SET()   		LPC_GPIO1->FIODIR |= UART2MODESELECT0;\
								LPC_GPIO1->FIODIR |= UART2MODESELECT1;\
 								LPC_GPIO1->FIOCLR |= UART2MODESELECT0;\
								LPC_GPIO1->FIOSET |= UART2MODESELECT1
#define EVB_MODE_SET()   		LPC_GPIO1->FIODIR |= UART2MODESELECT0;\
								LPC_GPIO1->FIODIR |= UART2MODESELECT1;\
 								LPC_GPIO1->FIOSET |= UART2MODESELECT0;\
								LPC_GPIO1->FIOSET |= UART2MODESELECT1

//EVB_PWR P2.9	Modfiy & add by chensunwei
#define EVB_PWR        (1ul << 9)
#define EVB_PWRON()    GPIO_SetDir(2, EVB_PWR, 1);  GPIO_ClearValue(2, EVB_PWR)                     
#define EVB_PWROFF()   GPIO_SetDir(2, EVB_PWR, 1);  GPIO_SetValue(2, EVB_PWR)  

/*
//CS-P1.25,MOSI-P1.26,Clk-P2.8	Modfiy & add by chensunwei
//Ƭѡ��ѡͨ����LCD�������������Ƿ������ݣ�����ʱ����ͨ������ʱ�������������ݵ�
//�����µĴ�����ʵ����������ƴ����һ��ģ��������ϰ������ϰ�����ʱ���ߣ��°������°�����ʱ���ߣ��������ʱ���߾���ʹ������
#define CS_SET()     	LPC_GPIO1->FIODIR |= (1ul << 25); LPC_GPIO1->FIOSET |= (1ul << 25)	   //����ѡͨ
#define CS_CLR()     	LPC_GPIO1->FIODIR |= (1ul << 25); LPC_GPIO1->FIOCLR |= (1ul << 25)
#define SID_SET()    	LPC_GPIO1->FIODIR |= (1ul << 26); LPC_GPIO1->FIOSET |= (1ul << 26)    //��������
#define SID_CLR()    	LPC_GPIO1->FIODIR |= (1ul << 26); LPC_GPIO1->FIOCLR |= (1ul << 26) 
#define SCLK_SET()   	LPC_GPIO2->FIODIR |= (1ul << 8);  LPC_GPIO2->FIOSET |= (1ul << 8)    //����ʱ��,�°���
#define SCLK_CLR()   	LPC_GPIO2->FIODIR |= (1ul << 8);  LPC_GPIO2->FIOCLR |= (1ul << 8)
#define SCLK_SET_Up()   LPC_GPIO1->FIODIR |= (1ul << 24); LPC_GPIO1->FIOSET |= (1ul << 24)    //����ʱ��,�ϰ���
#define SCLK_CLR_Up()   LPC_GPIO1->FIODIR |= (1ul << 24); LPC_GPIO1->FIOCLR |= (1ul << 24)
*/
//CS-P3.25,MOSI-P1.24,Clk0-P1.25,Clk1-P1.26	LCD_BL_EN-P2.8Modfiy & add by chensunwei
//ƬѡCS��ѡͨ����LCD������������MOSI�Ƿ������ݣ�����ʱ��CLK0��ͨ������ʱ���������������°����ģ�CLK1��ͨ������ʱ���������������ϰ�����
//�����µĴ�����ʵ����������ƴ����һ��ģ��������ϰ������ϰ�����ʱ���ߣ��°������°�����ʱ���ߣ��������ʱ���߾���ʹ������
//LCD_BL_EN���Ʊ�������Ͱ�
#define CS_SET()     	LPC_GPIO3->FIODIR |= (1ul << 25); LPC_GPIO3->FIOSET |= (1ul << 25)	   //����ѡͨ
#define CS_CLR()     	LPC_GPIO3->FIODIR |= (1ul << 25); LPC_GPIO3->FIOCLR |= (1ul << 25)
#define SID_SET()    	LPC_GPIO1->FIODIR |= (1ul << 24); LPC_GPIO1->FIOSET |= (1ul << 24)    //��������
#define SID_CLR()    	LPC_GPIO1->FIODIR |= (1ul << 24); LPC_GPIO1->FIOCLR |= (1ul << 24) 
#define SCLK_SET_Up()   LPC_GPIO1->FIODIR |= (1ul << 25); LPC_GPIO1->FIOSET |= (1ul << 25)    //����ʱ��,�ϰ���
#define SCLK_CLR_Up()   LPC_GPIO1->FIODIR |= (1ul << 25); LPC_GPIO1->FIOCLR |= (1ul << 25)
#define SCLK_SET()   	LPC_GPIO1->FIODIR |= (1ul << 26);  LPC_GPIO1->FIOSET |= (1ul << 26)    //����ʱ��,�°���
#define SCLK_CLR()   	LPC_GPIO1->FIODIR |= (1ul << 26);  LPC_GPIO1->FIOCLR |= (1ul << 26)
#define SCLK_BL_SET()   LPC_GPIO2->FIODIR |= (1ul << 8);  LPC_GPIO2->FIOSET |= (1ul << 8)    //�������
#define SCLK_BL_CLR()   LPC_GPIO2->FIODIR |= (1ul << 8);  LPC_GPIO2->FIOCLR |= (1ul << 8)


//���Ʒ;��Ļ�ļ���;by gzz 20121025
//����ƴͼ����Ļ
#define SCL_SET()   LPC_GPIO3->FIODIR |= (1ul << 25); LPC_GPIO3->FIOSET |= (1ul << 25)	//SCL Clock,P3.25
#define SCL_CLR()   LPC_GPIO3->FIODIR |= (1ul << 25); LPC_GPIO3->FIOCLR |= (1ul << 25)

#define SDA_SET()   LPC_GPIO1->FIODIR |= (1ul << 24); LPC_GPIO1->FIOSET |= (1ul << 24) 	//SDL DATA,P1.24
#define SDA_CLR()   LPC_GPIO1->FIODIR |= (1ul << 24); LPC_GPIO1->FIOCLR |= (1ul << 24) 

#define nCS_SET()   LPC_GPIO1->FIODIR |= (1ul << 25); LPC_GPIO1->FIOSET |= (1ul << 25) 	//CS ChipSel,P1.25
#define nCS_CLR()   LPC_GPIO1->FIODIR |= (1ul << 25); LPC_GPIO1->FIOCLR |= (1ul << 25)

#define CD_SET()    LPC_GPIO1->FIODIR |= (1ul << 26); LPC_GPIO1->FIOSET |= (1ul << 26) 	//CD Data&CMD,P1.26
#define CD_CLR()    LPC_GPIO1->FIODIR |= (1ul << 26); LPC_GPIO1->FIOCLR |= (1ul << 26)


//��Ϸ������P1.27
#define GAME_LED_ON()   LPC_GPIO1->FIODIR |= (1ul << 27); LPC_GPIO1->FIOSET |= (1ul << 27)  
#define GAME_LED_OFF()  LPC_GPIO1->FIODIR |= (1ul << 27); LPC_GPIO1->FIOCLR |= (1ul << 27)  
//��Ϸ��������P2.7
#define GAMEKey_SetInput() LPC_GPIO2->FIODIR &= ~(1ul << 7)//��Ϊ����ģʽ
#define GAMEKey_Get()      ( ((LPC_GPIO2->FIOPIN >> 7) & 0x01) == 0 )

//120821 by cq ReturnCoinKey
//�˱Ұ�������P0.22
#define ReturnCoinKey_SetInput() LPC_GPIO0->FIODIR &= ~(1ul << 22)//��Ϊ����ģʽ
#define ReturnCoinKey_Get()      ( ((LPC_GPIO0->FIOPIN >> 22) & 0x01) == 0 )




//W_CTL0 P3.26	Modfiy & add by chensunwei
#define WM_POWER        (1ul << 26)
#define WM_POWERON()   GPIO_SetDir(3, GPRS_POWER, 1);  GPIO_ClearValue(3, GPRS_POWER) //GPRS��Դ��
#define WM_POWEROFF()  GPIO_SetDir(3, GPRS_POWER, 1);  GPIO_SetValue(3, GPRS_POWER)   //GPRS��Դ��

//Buzzer P1.30	Modfiy & add by chensunwei
#define BEEP         (1ul << 30)                     
#define BEEPON()     GPIO_SetDir(1, BEEP, 1);  GPIO_SetValue(1, BEEP) 
#define BEEPOFF()    GPIO_SetDir(1, BEEP, 1);  GPIO_ClearValue(1, BEEP) 

//����5.0V��Դ����,P0.23��Դ���ƶ� Modfiy & add by chensunwei
#define VCC_POWER		 (1ul<<23)		
#define VCC_POWEROFF()	 GPIO_SetDir(0, VCC_POWER, 1);  GPIO_ClearValue(0, VCC_POWER)
#define VCC_POWERON()	 GPIO_SetDir(0, VCC_POWER, 1);  GPIO_SetValue(0, VCC_POWER)

#define MAINTEN_SWITCH()     (LPC_GPIO4->FIOPIN & (1ul << 29))	 //ά������p4-29


#define CS_GET()     (LPC_GPIO1->FIOPIN & (1ul << 24))
#define SID_GET()    (LPC_GPIO1->FIOPIN & (1ul << 25))
#define SCLK_GET()   (LPC_GPIO1->FIOPIN & (1ul << 26))

/*����*/
#if KEY_MODE == KEY_4X6

#define KeyX_SetInput() LPC_GPIO1->FIODIR &= ~(0x0F	<< 14)
#define KeyY_SetInput() LPC_GPIO0->FIODIR &= ~(0x3F << 4)
#define KeyX_Set0()     {LPC_GPIO1->FIODIR |= 0x0F << 14; LPC_GPIO1->FIOCLR |= 0x0F << 14;}
#define KeyY_Set0()     {LPC_GPIO0->FIODIR |= 0x3F << 4; LPC_GPIO0->FIOCLR |= 0x3F << 4;}
#define KeyX_Get()      ((LPC_GPIO1->FIOPIN >> 14) & 0x0F) 
#define KeyY_Get()      ((LPC_GPIO0->FIOPIN >> 4) & 0x3F)

#elif KEY_MODE == KEY_2X8

#define KeyX	 	(0x03 << 14)												 							//�� ��Ӧ����
#define KeyY	  	(0x3F << 4)													 							//�� ��Ӧ����
#define KeyY0		(0x03 << 16)												 							//�� ��Ӧ����

#define KeyX_SetInput() GPIO_SetDir(1, KeyX, 0)			   													//������Ϊ����״̬
#define KeyY_SetInput() {GPIO_SetDir(0, KeyY, 0); GPIO_SetDir(1, KeyY0, 0);}   								//������Ϊ����״̬
#define KeyX_Set0()     {GPIO_SetDir(1, KeyX, 1); GPIO_ClearValue(1, KeyX);}   								//�����0
#define KeyY_Set0()     {GPIO_SetDir(0, KeyY, 1); GPIO_SetDir(1, KeyY0, 1); GPIO_ClearValue(0, KeyY); GPIO_ClearValue(1, KeyY0);}	//�����0
#define KeyX_Get()      ((GPIO_ReadValue(1) >> 14) & 0x03) 			 										//��ȡ��ֵ
#define KeyY_Get()      (((GPIO_ReadValue(0) >> 4) & 0x3F) << 2) | ((GPIO_ReadValue(1) >> 16) & 0x03)	 	//��ȡ��ֵ

#endif
/*���̽���*/
#endif
