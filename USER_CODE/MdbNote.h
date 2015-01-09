/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           gba.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        MDBֽ��������������غ�������
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
#ifndef __MDBNOTE_H 
#define __MDBNOTE_H

/*MBV: Mdb Bill Validator*/
#define MBV_RESET        0x30		 //��λ����
#define MBV_SETUP        0x31		 //SETUP ��ȡ������Ϣ
#define MBV_POLL         0x33		 //��ѯ
#define MBV_BILLTYPE     0x34		 //ʹ��Ͷ��ͨ������
#define MBV_ESCROW	     0x35		 //����״̬����
#define MBV_STACKER      0x36		 //��ȡ�����
#define MBV_EXPANSION    0x37		 //��չ����

#define MBV_ID           0x00		 //��ȡID

//״̬��
#define MBV_DEFMOTOERR         0x01		   //MOTO����
#define MBV_SENSORERR          0x02		   //����������
#define MBV_ROMCHKERR		   0x04		   //ROM����
#define MBV_VALIDATORJAM       0x05		   //����
#define MBV_BILLREMOVED        0x07		   //δ֪����ȡ��
#define MBV_CASHBOXERR         0x08		   //�������
#define MBV_BILLREMOVAL        0x0C		   //��ͼȡ��
/*
#define MBV_DEFMOTOERR_BIT         (1 << 0)
#define MBV_SENSORERR_BIT          (1 << 1)
#define MBV_ROMCHKERR_BIT		   (1 << 2)
#define MBV_VALIDATORJAM_BIT       (1 << 3)
#define MBV_BILLREMOVED_BIT        (1 << 4)
#define MBV_CASHBOXERR_BIT         (1 << 5)
#define MBV_BILLREMOVAL_BIT        (1 << 6)
*/
#define MBV_VALUE_BIT 			   (1 << 8)	 //ͨ��ֵ�Դ��־
#define MBV_BILLFULL_BIT		   (1 << 9)	 //��������־
#define MBV_COMMERR_BIT			   (1 << 15) //ͨѶ����

#define MBV_STAT_OK                0

uint8_t MdbNote_Reset(void);
uint8_t MdbNote_Setup(void);
uint8_t MdbNote_Enable(uint16_t NoteTypeEn);
uint8_t MdbNote_Poll(void);
uint8_t MdbNote_Stack(void);
uint8_t MdbNote_Return(void);
uint8_t MdbNote_GetStackerStat(void);
uint8_t MdbNote_IDRead(void);
void MdbNote_PackAnalysis(uint8_t *buf,uint8_t len);


//120401 by cq change structor
//** Descriptions:        MDBֽ����Ӧ�ó�����غ�������
void MdbNote_RstProc(void);
void MdbNote_InitProc(void);
void MdbNote_UpDateStackerStat(void);


#endif /* end __GBA_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
