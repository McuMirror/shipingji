/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           BillAcceptor.h
** Last modified Date:  2011-10-26
** Last Version:         
** Descriptions:        ֽ��������������غ�������
**                      
**------------------------------------------------------------------------------------------------------
** Created by:           
** Created date:        2011-10-26
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
#ifndef __BILLACCEPTOR_H 
#define __BILLACCEPTOR_H

#define BILLACCEPTOR_STACKED    0x80
#define BILLACCEPTOR_ESCROWED   0x81
#define BILLACCEPTOR_RETURNED   0x82

typedef struct
{
	uint8_t  Level;			  //ֽ�����ȼ�
	uint16_t Code;			  //���Ҵ���
	uint16_t Scale;			  //��������
	uint16_t Decimal;		  //10^С��λ��
	uint16_t StkCapacity;	  //��������
	uint16_t Security;		  //��ȫ�ȼ�
	uint8_t  EscrowFun;		  //�ݴ湦��
}  BillParaStruct;

uint8_t isBillSingleWork(void);//121106 by cq BillSingleWork

//BillAcceptor.c//ֽ������������
void BillAcceptor_Init(void);//ֽ������ʼ��
uint8_t BillAcceptor_Enable(uint16_t billtype);//ֽ����ʹ��
//parameters:		billtype:ֽ����ʹ��ͨ��
//Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���	
uint8_t BillAcceptor_Poll(uint16_t billtype);//ֽ������ѯ
//Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���	
void BillAcceptor_PollProc(void);//��ѯֽ��������ȡ״̬����������Ӧ����
uint8_t BillAcceptor_Return(uint16_t billtype);//�˱�
//Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���	
uint8_t BillAcceptor_Stack(uint16_t billtype);//ѹ��
//Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���	
void BillAcceptor_UpDateStat(uint16_t status);//���µ�ǰֽ����״̬
void BillAcceptor_UpdateAcpt(uint8_t route,uint8_t chn);//�յ�ֽ�ң�����ֽ��״̬��Ϣ
//parameters:		rount:BILLACCEPTOR_STACKED,BILLACCEPTOR_ESCROWED,BILLACCEPTOR_RETURNED�ȣ���ʾ��ǰֽ��������λ��
//					chn:  ֽ��ͨ��ֵ
void BillAcceptor_ReturnProc(uint8_t moneych);//��ֽ��ѹ��ʱ��������
//parameters:		moneych:�ձ�ͨ��
void BillAcceptor_StackProc(uint8_t moneych);//��ֽ��ѹ��ʱ�����½�������
void BillAcceptor_EscrowProc(uint8_t moneych);//ֽ�������ڴ���״̬ʱ���ж�ֽ����ֵ����������Ӧ����
void BillAcceptor_SetBillPara(BillParaStruct billpara);//����ֽ�Ҳ���
//parameters:		ֽ�Ҳ����ṹ��
uint8_t BillAcceptor_ErrJudge(uint8_t len);//�ж�ֽ����ͨѶ״̬
// parameters:		len:�������Э�飬����ʱ��ʾ���ݳ��ȣ��쳣ʱ��ʾ�쳣״̬
// Returned value:	TRUE:���� FALSE:����	
uint8_t BillAcceptor_CommErr(void);//�����ж��Ƿ���ͨѶ����
// Returned value:	TRUE:���� FALSE:����	
uint8_t BillAcceptor_ValueSetErr(void);//�����ж�ֽ�Ҹ�ͨ����ֵ�����Ƿ���ȷ
// Returned value:	TRUE:���� FALSE:����	
uint8_t BillAcceptor_StackerFull(void);//�����жϳ����Ƿ�����
// Returned value:	TRUE:���� FALSE:����	
uint8_t BillAcceptor_Available(void);//�ж�ֽ�����Ƿ����
//					ͨѶ�Ƿ���������ֵ�����Ƿ���ȷ��	
// Returned value:	TRUE:���� FALSE:����	
void BillAcceptor_SetCommErr(void);//����ֽ����ͨѶ����״̬
void BillAcceptor_SetValueErr(void);//����ֽ������ֵ���ô���״̬
void BillAcceptor_SetStackerFull(void);//���ó�����״̬
void BillAcceptor_SetRstStat(void);//����ֽ������λ״̬����ʾֽ�����ոո�λ��
void BillAcceptor_SetInValid(void);//����ֽ�Ҳ���ʶ��״̬
void BillAcceptor_ClrInValid(void);//���ֽ�Ҳ���ʶ��״̬
void BillAcceptor_CheckStat(void);//����NoteStat(NoteStatֽ����״̬û�о����״̬�룬ֻ�������ж�ֽ�����Ƿ�������)
#endif
