/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           drv.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        ������������������غ�������
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
#ifndef __DRV_H 
#define __DRV_H

#define DRV_DISPENSE        0x70		//��������
#define DRV_INQUIRE         0x71		//��ѯ
#define DRV_GOODSCHK        0x80		//�������
#define DRV_STATUSCHK       0x81		//��ѯ�������޻�
#define DRV_OPENSLUICE      0x70		//�򿪷���
#define DRV_CLOSESLUICE     0x70		//�رշ���
#define DRV64_CLEARSN       0x72		//��SN��
#define DRV64_TEST          0x73		//����
#define DRV_CLEARSN         0xFF		//��SN��

#define GOODSCHK_OPEN       1			//�����޻����
#define GOODSCHK_CLOSE      0			//�ر����޻����

#define DRV_ALLCHNDIS_BIT      (1 << 0)	//���л���������
#define DRV_NOGOODS_BIT        (1 << 1)	//�޻�
#define DRV_HARDERR_BIT        (1 << 2)	//Ӳ������
#define DRV_COMMERR_BIT        (1 << 3)	//ͨѶ����
#define DRV_CHNSET_BIT         (1 << 7)	//����״̬ ��е�ṹͨ��ʹ��
#define DRV_STAT_MASK		   0x7F		//����Ϊ�������״̬

/*����״̬λ*/
#define DRV_MISSIONFAIL_BIT     (1 << 0)   //����ʧ��

#if DRV_TYPE == DRV_12
#define DRV_BUSY_BIT            (1 << 1)   //æ
#define GOODS_SOLDOUT_BIT       (1 << 3)   //��Ʒ������
#define MOTO_NOTRETURN_BIT      (1 << 4)   //���û�ص���ȷλ��
#define MOTO_MISPLACE_BIT       (1 << 5)   //���������ȷ��λ����
#define DRV_ERR_MASK            0x30	   //����״̬����
#elif DRV_TYPE == DRV_64
#define GOODS_SOLD_ERR          (1 << 0)   //bit0�ܹ���λ
#define GOODS_SOLDOUT_BIT       (1 << 1)   //bit1�������
#define MOTO_MISPLACE_BIT       (1 << 2)   //bit2�����ת֮ǰ�Ͳ�����ȷ��λ����(Ҳ��������)
#define MOTO_NOTMOVE_BIT        (1 << 3)   //bit3�������ת(Ҳ��������)
#define MOTO_NOTRETURN_BIT      (1 << 4)   //bit4���ûת����ȷλ��(Ҳ��������)
#define GOODS_NOTPASS_BIT       (1 << 5)   //bit5��Ʒû��(����ȷ��û��⵽)
#define DRV_CMDERR_BIT          (1 << 6)   //bit6�������(ֻ�з�������Ͳ�ѯ������������������������������ͱ���)
#define DRV_HOLESTA_BIT         (1 << 7)   //����״̬
#define DRV_GOCERR_BIT          (1 << 7)   //bit7�������ģ��״̬(GOC����)
#define DRV_ERR_MASK            0x5C	   //����״̬����
#endif

#define DRV_NOGOOGS   0x01				   //�޻�

uint8_t GetDrvStatus(void);
uint8_t Drv_ErrJudge(uint8_t x);
uint8_t DRV_ChnChk(uint8_t channelno,uint8_t *channelx, uint8_t *channely);
uint8_t DRV_Dispense(uint8_t DRVNo, uint8_t chksign);
uint8_t DRV_Inquire(uint8_t DRVNo, uint8_t chksign);
uint8_t DRV_GetStatus(uint8_t DRVNo, uint8_t chksign);
uint8_t DRV_ClearSN(uint8_t DRVNo, uint8_t chksign);
uint8_t DRV_Test(uint8_t DRVNo, uint8_t chksign);


//120401 by cq change structor
//** Descriptions:        ��������Ӧ�ó�����غ�������

uint8_t ChannelCheck(void);
void CheckDriverStat(void);
void DrvCheckCommand(uint8_t channel);
void DrvOutCommand(uint8_t channel);


#endif /* end __DRV_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
