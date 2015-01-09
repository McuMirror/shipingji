/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           hopper.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        hopper����������غ�������
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
#ifndef __HOPPER_H 
#define __HOPPER_H

#define HOPPERNO    0			//hopper1��
#define HOPPERNO2   1			//hopper2��
#define HOPPERNO3   2			//hopper3��

#define HOPPER_PAYOUT    0x50	//��������
#define HOPPER_INQUIRE   0x51	//��ѯ����

/*״̬λ*/
#define HOPPER_REPEATSN_BIT           (1 << 0)	   //�ظ���������
#define HOPPER_PAYOUTFAIL_BIT         (1 << 0)	   //����ʧ��
#define HOPPER_BUSY_BIT               (1 << 1)	   //æ
#define HOPPER_DATAERR_BIT            (1 << 2)	   //���ݳ���
#define HOPPER_COINEMPTY_BIT          (1 << 3)	   //Ӳ������
#define HOPPER_SENSORERR_BIT          (1 << 4)	   //����������
#define HOPPER_INSUFFICIENT_BIT       (1 << 5)	   //Ӳ�Ҳ���
#define HOPPER_MALFUNCTION_BIT        (1 << 6)	   //����
#define HOPPER_CMDERR_BIT             (1 << 7)	   //�������
/*��չ״̬λ*/
#define HOPPER_DISABLE_BIT			  (1 << 10)	   //����������
#define HOPPER_COMMERR_BIT			  (1 << 15)	   //ͨѶ����

#define HOPPER_ERR_MASK               0xFFFC	   //����״̬����
#define HOPPER_MALFUN_MASK            0xFFD4	   //����״̬����

uint8_t Hopper_ErrJudge(uint8_t x);
uint8_t Hopper_GetStatus(void);
uint8_t HopperPayout(uint8_t hopperno, uint16_t amount);
uint8_t HopperInquire(uint8_t hopperno);



//120401 by cq change structor
//** Descriptions:        HopperӦ�ó�����غ�������
void CheckHopperStat(void);
void Hopper_InitProc(void);
void HopperPayoutCmd(uint32_t MoneyOut, uint8_t hopperch);
void Hopper_PayoutProc(uint32_t moneyout);


#endif
