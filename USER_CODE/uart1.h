/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           uart.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        ��������������غ�������
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
#ifndef __UART1_H 
#define __UART1_H

//#define  ERR_STX            0x81		//֡ͷ����
//#define  ERR_ETX            0x82		//֡β����
//#define  ERR_CHKSUM         0x83		//У�����
//#define  ERR_TIMEOUT        0x84		//��ʱ



void Uart1_Init(void);
void Uart1_ClrBuf(void);
uint8_t Uart1_Read(uint8_t *buf, uint8_t len);
void Uart1_SendByte(uint8_t byte);
void Uart1_Write(uint8_t *buf,uint8_t lenth);
void Uart1_IRQHandler(void);
#endif
