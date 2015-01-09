/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Mdbcoin.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        MDBӲ��������������غ�������
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
#ifndef __MDBCOIN_H 
#define __MDBCOIN_H

/*״̬��*/
#define COIN_NOCREDIT          0x03	   //���ܽ����Ӧͨ��
#define COIN_SENSORERR         0x04	   //����������
#define COIN_UNPLUGGED         0x06	   //unplugged
#define COIN_TUBEJAM           0x07	   //���ҿ���
#define COIN_ROMCHKERR         0x08	   //ROM����
#define COIN_ROUTINGERR        0x09	   //����ͨ������
#define COIN_JAM               0x0C	   //Ͷ�ҿ���
#define COIN_REMOVAL           0x0D	   //��ͼ�Ƴ�Ӳ��
/*
#define COIN_NOCREDIT_BIT        (1 << 0)
#define COIN_SENSORERR_BIT       (1 << 1)
#define COIN_UNPLUGGED_BIT       (1 << 2)
#define COIN_TUBEJAM_BIT         (1 << 3)
#define COIN_ROMCHKERR_BIT       (1 << 4)
#define COIN_ROUTINGERR_BIT      (1 << 5)
#define COIN_JAM_BIT             (1 << 6)
*/
#define COIN_VALUE_BIT          0//(1 << 13)	 //ͨ��ֵ�Դ��־
#define COIN_FULL_BIT			0//(1 << 14)	 //Ӳ������־
#define COIN_COMMERR_BIT        (1 << 15)	 //ͨѶ����

#define COIN_STAT_OK			0

#define COIN_RESET        0x08		 //��λ����
#define COIN_SETUP        0x09		 //��ȡ������Ϣ
#define TUBE_STATUS       0x0A		 //��ȡͨ��Ӳ����
#define COIN_POLL         0x0B		 //��ѯ
#define COIN_TYPE         0x0C		 //ʹ��Ͷ��ͨ��
#define COIN_DISPENSE     0x0D		 //����
#define COIN_EXPANSION    0x0F		 //��չ����
#define COIN_ID           0x00		 //��ȡID
#define COIN_FEATURE_EN   0x01		 //ʹ����չ����
#define COIN_PAYOUT       0x02		 //����
#define COIN_PAYOUT_ST    0x03		 //����״̬
#define COIN_PAYOUT_POLL  0x04		 //������ѯ
#define COIN_DIAGNOSTIC   0x05		 //״̬���

uint8_t MdbCoin_Reset(void);
uint8_t MdbCoin_Setup(void);
uint8_t MdbCoin_GetTubeStatus(void);
uint8_t MdbCoin_Enable(uint16_t CoinsTypeEn);
uint8_t MdbCoin_Disable(void);
uint8_t MdbCoin_Dispense(uint8_t amount, uint8_t type);
uint8_t MdbCoin_Poll(void);
uint8_t MdbCoin_GetID(void);
uint8_t MdbCoin_FeatureEN(void);
uint8_t MdbCoin_PayOut(uint8_t amount);
uint8_t MdbCoin_GetPaySt(void);
uint8_t MdbCoin_PayoutPoll(void);
uint8_t MdbCoin_Diagnostic(void);
void MdbCoin_PackAnalysis(uint8_t *buf, uint8_t len);



//120401 by cq change structor
//** Descriptions:        MDBӲ����Ӧ�ó�����غ�������
void MdbCoin_InitProc(void);
void CoinPayoutCmd(uint32_t MoneyPay);
uint16_t MdbCoin_CheckTubeStat(uint32_t *coinleft);
void MdbCoin_PayoutProc(uint32_t MoneyPay);


#endif /* end __COIN_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
