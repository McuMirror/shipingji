/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           pulse.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        ����Ӳ��������������غ�������
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
#ifndef __PULSE_H 
#define __PULSE_H

#include "..\driver\LPC17xx.h"

#ifndef  COIN_VALUE_BIT
#define  COIN_VALUE_BIT	         (1 << 13)	 //ͨ��ֵ�Դ��־
#endif

#ifndef  COIN_COMMERR_BIT
#define  COIN_COMMERR_BIT        (1 << 15)	 //ͨѶ����
#endif

#define  CoinP1_Get()  ((LPC_GPIO1->FIOPIN >> 10) & 0x01)        //Ͷ��ͨ��1
#define  CoinP2_Get()  ((LPC_GPIO1->FIOPIN >> 9) & 0x01)		 //Ͷ��ͨ��2
#define  CoinP3_Get()  ((LPC_GPIO1->FIOPIN >> 8) & 0x01)		 //Ͷ��ͨ��3
#define  CoinP4_Get()  ((LPC_GPIO1->FIOPIN >> 4) & 0x01)		 //Ͷ��ͨ��4
#define  CoinP5_Get()  ((LPC_GPIO1->FIOPIN >> 1) & 0x01)		 //Ͷ��ͨ��5
#define  CoinP6_Get()  ((LPC_GPIO1->FIOPIN >> 0) & 0x01)		 //Ͷ��ͨ��6

/*Ͷ��ͨ��*/
#define  CoinP_Get()   (CoinP1_Get() |       \
                       (CoinP2_Get() << 1) | \
					   (CoinP3_Get() << 2) | \
					   (CoinP4_Get() << 3) | \
					   (CoinP5_Get() << 4) | \
					   (CoinP6_Get() << 5))

#define  Pulse_Enable()    LPC_GPIO1->FIODIR |= (1UL << 20); LPC_GPIO1->FIOCLR |= (1UL << 20)	 //ʹ��Ͷ��
#define  Pulse_Disable()   LPC_GPIO1->FIODIR |= (1UL << 20); LPC_GPIO1->FIOSET |= (1UL << 20)	 //����Ͷ��


void Coin_Accept(void);


//120401 by cq change structor
//** Descriptions:        ����Ӳ����Ӧ�ó�����غ�������
void Pulse_InitProc(void);


#endif
