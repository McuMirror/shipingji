/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           evb.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        evbЭ������������غ�������
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
#ifndef __EVB_H 
#define __EVB_H

#define ChangeSN(sn)           ++sn? sn : sn++
           		 				 
typedef struct          //���������ʽ 
{				 
   uint8_t Head;  		//����ͷ
   uint8_t Lenth;  		//����
   uint8_t SN;	      	//ͬ�����
   uint8_t Com;	     	//������
   uint8_t DevNo;     	//�豸��
   uint8_t rsv1;	  	//����
   uint8_t rsv2;	  	//������⣨1:�� 0:�أ�
   uint8_t chksum;    	//У����
} EVBCommand;

#ifdef EVBDEF
uint8_t evbbuf[8];
#else
extern uint8_t evbbuf[8];	   
#endif

#endif /* end __EVB_H */

/*****************************************************************************
**                            End Of File
******************************************************************************/
