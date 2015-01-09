/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           gbahr.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        GBAֽ��������������غ�������
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
#ifndef __GBAHR1_H 
#define __GBAHR1_H

/*״̬λ*/
#define  HR_ESCROWED_BIT	 (1 << 2)	   //�ݴ�״̬
#define  HR_STACKED_BIT		 (1 << 4)	   //ѹ��״̬
#define  HR_RETURNED_BIT	 (1 << 6)	   //�˳�״̬

#define  HR_CHEATED_BIT      (1 << 0)	   //�̱�
#define  HR_BILLREJ_BIT      (1 << 1)	   //����
#define  HR_BILLJAM_BIT      (1 << 2)	   //����
#define  HR_BILLFULL_BIT     (1 << 3)	   //������
#define  HR_LCBPRESENT_BIT   (1 << 4)	   //�г���
#define  HR_VALUE_BIT        (1 << 7)	   //ͨ��ֵ�Դ�״̬

#define  HR_POWERUP_BIT      (1 << 0)	   //�ϵ�״̬
#define  HR_CMDERR_BIT       (1 << 1)	   //�������
#define  HR_FAILURE_BIT      (1 << 2)	   //����
#define  HR_COMMERR_BIT      (1 << 15)	   //ͨѶ����

#define  HR_ERR_MASK1   0x8C			   //��һ�ֽڴ���״̬����
#define  HR_ERR_MASK2   0x06			   //�ڶ��ֽڴ���״̬����

#define  HR_STAT_OK		0                  //HR_LCBPRESENT_BIT

#define ACKSwitch()            GbaAck = GbaAck ? 0 : 1

typedef struct               //�����ʽ
{				 
   uint8_t Stx;  		     //����ͷ
   uint8_t Lenth;  			 //����
   uint8_t Ack : 4;			 //ACKֵ
   uint8_t Msgtype : 3;	 	 //��Ϣ����
   uint8_t Reserve : 1;	     //����
   uint8_t Data0;	     	 //����0
   uint8_t Data1;     		 //����1
   uint8_t Data2;	  		 //����2
   uint8_t Etx;	  			 //����β
   uint8_t chksum;    		 //У����
} GBACommand;

void Gbahr1_PackAnalysis(uint8_t *buf, uint8_t len);
void Gbahr1_ReadBuf(uint8_t *buf, uint8_t len);
uint8_t Gbahr1_Enable(uint16_t billtype);
uint8_t Gbahr1_Poll(uint16_t billtype);
uint8_t Gbahr1_Stack(uint16_t billtype);
uint8_t Gbahr1_Return(uint16_t billtype);
uint8_t Gbahr1_ErrJudge(uint8_t x);


//120401 by cq change structor
//** Descriptions:        GBAֽ����Ӧ�ó�����غ�������
void Gbahr1_InitProc(void);
void Gbahr1_UpDateStackerStat(void);


#endif
