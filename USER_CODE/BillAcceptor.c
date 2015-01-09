/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           BillAcceptor.c
** Last modified Date:  2011-10-26
** Last Version:         
** Descriptions:        ֽ������������
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
#include "..\driver\LPC17xx.h"
#include "..\driver\lpc_types.h"
#include "..\config.h"
#include "global.h"
#include "MdbNote.h"
#include "Gbahr1.h"
//#include "Gbahr1App.h"//120401 by cq change structor
#include "MdbNote.h"
//#include "MdbNoteApp.h"//120401 by cq change structor
#include "ITL.h"
#include "mdb.h"
#include "BillAcceptor.h"
#include "VMC_PC.h"


extern uint8_t GbaAck;

BillParaStruct BillPara;

/*���յ�ֽ�Ҳ����ṹ��*/
struct BillAccept
{
	uint8_t Route;	      //Bill Routing,����ֵBILLACCEPTOR_STACKED�ȣ����MDB�ֲ�
	                      //rount:BILLACCEPTOR_STACKED,BILLACCEPTOR_ESCROWED,BILLACCEPTOR_RETURNED�ȣ���ʾ��ǰֽ��������λ��
	uint8_t Channel;	  //ֽ��ͨ��
} BillAcpt;

uint8_t  BillRstStat;	  //ֽ�����Ƿ�ոո�λ��־
uint8_t  BillCommErr;     //ֽ����ͨѶ״̬ TRUE:���� FALSE:�쳣
uint8_t  BillValueErr;	  //ֽ�Ҹ�ͨ����ֵ�����Ƿ���ȷ TRUE:���� FALSE:�쳣
uint8_t  BillStackerFull; //ֽ��������״̬ TRUE:�� FALSE:δ��
uint8_t  BillInValid;	  //�յ���ֽ���Ƿ��ʶ�� TRUE:����ʶ��ֽ�� FALSE:����ֽ��
uint16_t BillStat;		  //ֽ����״̬,״ֵ̬��ֽ�������Э���ֲ�

/*****************************************************************************
** Function name:	BillAcceptor_StatInit	
**
** Descriptions:	��ʼ��ֽ����״ֵ̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_StatInit(void)
{
	BillAcpt.Route = 0;
	BillAcpt.Channel = 0;
	BillRstStat = FALSE;
	BillInValid = FALSE;
	BillStackerFull = FALSE;
	BillValueErr = FALSE;
	BillCommErr = FALSE;

	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
		BillStat = HR_STAT_OK;	     //��ʼ״̬��Ϊ����
		BillPara.EscrowFun = FALSE;	 //GBA HR1�����ݴ�
		break;

		case MDB_NOTE_EN:
		BillStat = MBV_STAT_OK;
		//BillPara.EscrowFun = TRUE;
		break;

		case ITL_STAT_OK:
		BillStat = ITL_STAT_OK;
		BillPara.EscrowFun = FALSE;	 //ITL�����ݴ�
		break;

		default:
		break;
	}
}

/*****************************************************************************
** Function name:	BillAcceptor_ClearStat	
**
** Descriptions:	����ϴ��յ���ֽ�Ҽ�¼�������ظ��ۼ�ͬһ��Ͷ�ң�ÿ��POLLǰ����
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_ClearStat(void)
{
	BillAcpt.Route = 0;
	BillAcpt.Channel = 0;
}

/*****************************************************************************
** Function name:	BillAcceptor_CommErr	
**
** Descriptions:	�����ж��Ƿ���ͨѶ����
**						
**
** parameters:		��
** Returned value:	TRUE:���� FALSE:����	
** 
*****************************************************************************/
uint8_t BillAcceptor_CommErr(void)
{
	return BillCommErr;
}

/*****************************************************************************
** Function name:	BillAcceptor_RstStat	
**
** Descriptions:	�����жϸո��Ƿ�λ��
**						
**
** parameters:		��
** Returned value:	TRUE:��λ�� FALSE:û��λ	
** 
*****************************************************************************/
uint8_t BillAcceptor_RstStat(void)
{
	return BillRstStat;
}

/*****************************************************************************
** Function name:	BillAcceptor_ValueSetErr	
**
** Descriptions:	�����ж�ֽ�Ҹ�ͨ����ֵ�����Ƿ���ȷ
**						
**
** parameters:		��
** Returned value:	TRUE:���ô��� FALSE:��������	
** 
*****************************************************************************/
uint8_t BillAcceptor_ValueSetErr(void)
{
	return BillValueErr;
}

/*****************************************************************************
** Function name:	BillAcceptor_StackerFull	
**
** Descriptions:	�����жϳ����Ƿ�����
**						
**
** parameters:		��
** Returned value:	TRUE:������ FALSE:δ��	
** 
*****************************************************************************/
uint8_t BillAcceptor_StackerFull(void)
{
	return BillStackerFull;
}

/*****************************************************************************
** Function name:	IsBillInValid	
**
** Descriptions:	�����ж��յ���ֽ���Ƿ��ʶ��
**						
**
** parameters:		��
** Returned value:	TRUE:����ʶ�� FALSE:��ʶ��	
** 
*****************************************************************************/
uint8_t IsBillInValid(void)
{
	return BillInValid;
}

/*****************************************************************************
** Function name:	BillAcceptor_EscrowFun	
**
** Descriptions:	�����ж�ֽ�����Ƿ����ݴ湦��
**						
**
** parameters:		��
** Returned value:	TRUE:���ݴ湦�� FALSE:���ݴ湦��	
** 
*****************************************************************************/
uint8_t BillAcceptor_EscrowFun(void)
{
	return BillPara.EscrowFun;
}

/*****************************************************************************
** Function name:	BillAcceptor_SetCommErr	
**
** Descriptions:	����ֽ����ͨѶ����״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_SetCommErr(void)  
{
    BillCommErr = TRUE;
}

/*****************************************************************************
** Function name:	BillAcceptor_SetValueErr	
**
** Descriptions:	����ֽ������ֵ���ô���״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_SetValueErr(void)   
{
	BillValueErr = TRUE;
}

/*****************************************************************************
** Function name:	BillAcceptor_SetStackerFull	
**
** Descriptions:	���ó�����״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_SetStackerFull(void)
{
    BillStackerFull = TRUE;
}

/*****************************************************************************
** Function name:	BillAcceptor_SetBillPara	
**
** Descriptions:	����ֽ�Ҳ���
**						
**
** parameters:		ֽ�Ҳ����ṹ��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_SetBillPara(BillParaStruct billpara)
{
	BillPara = billpara;
}

/*****************************************************************************
** Function name:	BillAcceptor_SetRstStat	
**
** Descriptions:	����ֽ������λ״̬����ʾֽ�����ոո�λ��
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_SetRstStat(void)
{
    BillRstStat = TRUE;
}

/*****************************************************************************
** Function name:	BillAcceptor_CLrRstStat	
**
** Descriptions:	���ֽ������λ״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_ClrRstStat(void)
{
    BillRstStat = FALSE;
}

/*****************************************************************************
** Function name:	BillAcceptor_SetInValid	
**
** Descriptions:	�����յ���ֽ��Ϊ����ʶ��
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_SetInValid(void)  
{
    BillInValid = TRUE;
}

/*****************************************************************************
** Function name:	BillAcceptor_ClrInValid	
**
** Descriptions:	�����յ���ֽ��Ϊ��ʶ��
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_ClrInValid(void)  
{
    BillInValid = FALSE;
}

/*****************************************************************************
** Function name:	BillAcceptor_Available	
**
** Descriptions:	�ж�ֽ�����Ƿ����
**					ͨѶ�Ƿ���������ֵ�����Ƿ���ȷ��	
**
** parameters:		��
** Returned value:	TRUE:ֽ�������� FALSE:������	
** 
*****************************************************************************/
uint8_t BillAcceptor_Available(void)
{
	if((BillCommErr == FALSE) && (BillValueErr == FALSE))  
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*****************************************************************************
** Function name:	IsBillEscrowed	
**
** Descriptions:	�ж��Ƿ���ֽ�Ҵ����ݴ�״̬
**						
**
** parameters:		��
** Returned value:	TRUE:�� FALSE:��	
** 
*****************************************************************************/
uint8_t IsBillEscrowed(void)
{
	if(BillAcpt.Route == BILLACCEPTOR_ESCROWED) 
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

/*****************************************************************************
** Function name:	IsBillStacked	
**
** Descriptions:	�ж��Ƿ���ֽ����ѹ��
**						
**
** parameters:		��
** Returned value:	TRUE:�� FALSE:��	
** 
*****************************************************************************/
uint8_t IsBillStacked(void)
{
	if(BillAcpt.Route == BILLACCEPTOR_STACKED) 
	{
		return TRUE;
	} 
	else 
	{
		return FALSE;
	}
}

/*****************************************************************************
** Function name:	IsBillReturned	
**
** Descriptions:	�ж��Ƿ����˳�
**						
**
** parameters:		��
** Returned value:	TRUE:�� FALSE:��	
** 
*****************************************************************************/
uint8_t IsBillReturned(void)
{
	if(BillAcpt.Route == BILLACCEPTOR_RETURNED) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*****************************************************************************
** Function name:	BillAcceptor_UpDateStat	
**
** Descriptions:	���µ�ǰֽ����״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_UpDateStat(uint16_t status)
{
	BillStat = status;
}

/*****************************************************************************
** Function name:	BillAcceptor_UpDateSysStat	
**
** Descriptions:	���µ�ǰֽ����״̬��SYSPara
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_UpDateSysStat(void)
{
	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			SYSPara1.NoteStat = BillStat;
			if(BillAcceptor_CommErr() == TRUE) 
			{
				SYSPara1.NoteStat |= HR_COMMERR_BIT;
			}
			if(BillAcceptor_ValueSetErr() == TRUE) 
			{
				SYSPara1.NoteStat |= HR_VALUE_BIT;
			}
			if(BillAcceptor_StackerFull() == TRUE) 
			{
				SYSPara1.NoteStat |= HR_BILLFULL_BIT;
			}
			break;

		case MDB_NOTE_EN:
			SYSPara1.NoteStat = BillStat;
			if(BillAcceptor_CommErr() == TRUE) 
			{
				SYSPara1.NoteStat |= MBV_COMMERR_BIT;
			}
			if(BillAcceptor_ValueSetErr() == TRUE) 
			{
				SYSPara1.NoteStat |= MBV_VALUE_BIT;
			}
			if(BillAcceptor_StackerFull() == TRUE) 
			{
				SYSPara1.NoteStat |= MBV_BILLFULL_BIT;
			}		
			break;

		case ITL_NOTE_EN:
			SYSPara1.NoteStat = BillStat;
			if(BillAcceptor_CommErr() == TRUE) 
			{
				SYSPara1.NoteStat |= ITL_COMMERR_BIT;
			}
			if(BillAcceptor_ValueSetErr() == TRUE) 
			{
				//SYSPara1.NoteStat |= MBV_VALUE_BIT;
			}
			if(BillAcceptor_StackerFull() == TRUE) 
			{
				//SYSPara1.NoteStat |= MBV_BILLFULL_BIT;
			}		
			break;	

		default:
			break;
	}
}

/*****************************************************************************
** Function name:	BillAcceptor_CheckStat	
**
** Descriptions:	����NoteStat(NoteStatֽ����״̬û�о����״̬�룬ֻ�������ж�ֽ�����Ƿ�������)
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_CheckStat(void)
{
	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			if(SYSPara1.NoteStat != HR_STAT_OK) 
			{
			    if(SYSPara1.NoteStat & HR_VALUE_BIT)	
				{
					CashState.NoteState |= NOTE_DEV_PERR;
					CashState.NoteState |= NOTE_DEV_DIS;
				}
				if(SYSPara1.NoteStat & HR_BILLFULL_BIT)
				{
					CashState.NoteState |= NOTE_DEV_DIS;
				}
				if(SYSPara1.NoteStat & (~HR_VALUE_BIT)) 
				{
				    CashState.NoteState |= NOTE_DEV_ER;
				}
			} 
			else 
			{
				CashState.NoteState &= NOTE_DEV_DIS;
				if(CashTypeEnBit.BillType == 0) 
				{
					CashState.NoteState |= NOTE_DEV_DIS;
				} 
				else 
				{
					CashState.NoteState = NOTE_DEV_OK;
				}
			}	
			break;

		case MDB_NOTE_EN:
			if(SYSPara1.NoteStat != MBV_STAT_OK) 
			{
			    if(SYSPara1.NoteStat & MBV_VALUE_BIT) 
				{
					CashState.NoteState |= NOTE_DEV_PERR;
					CashState.NoteState |= NOTE_DEV_DIS;
				}
				if(SYSPara1.NoteStat & MBV_BILLFULL_BIT) 
				{
					CashState.NoteState |= NOTE_DEV_DIS;
				}
				if(SYSPara1.NoteStat & (~MBV_VALUE_BIT)) 
				{
				    CashState.NoteState |= NOTE_DEV_ER;
				}
			} 
			else 
			{
			    CashState.NoteState &= NOTE_DEV_DIS;
				if(CashTypeEnBit.BillType == 0) 
				{
					CashState.NoteState |= NOTE_DEV_DIS;
				} 
				else 
				{
					CashState.NoteState = NOTE_DEV_OK;
				}
			}
			break;

		case ITL_NOTE_EN:
			if(SYSPara1.NoteStat != ITL_STAT_OK) 
			{
				/*
			    if(SYSPara1.NoteStat & HR_VALUE_BIT)	
				{
					CashState.NoteState |= NOTE_DEV_PERR;
					CashState.NoteState |= NOTE_DEV_DIS;
				}
				if(SYSPara1.NoteStat & HR_BILLFULL_BIT)
				{
					CashState.NoteState |= NOTE_DEV_DIS;
				}
				if(SYSPara1.NoteStat & (~HR_VALUE_BIT)) 
				{
				    CashState.NoteState |= NOTE_DEV_ER;
				}
				*/
				CashState.NoteState |= NOTE_DEV_ER;
			} 
			else 
			{
				CashState.NoteState &= NOTE_DEV_DIS;
				if(CashTypeEnBit.BillType == 0) 
				{
					CashState.NoteState |= NOTE_DEV_DIS;
				} 
				else 
				{
					CashState.NoteState = NOTE_DEV_OK;
				}
			}	
			break;	

		default:
			CashState.NoteState = NOTE_DEV_NONE;
			break;
	}
}

/*****************************************************************************
** Function name:	BillAcceptor_UpdateAcpt	
**
** Descriptions:	�յ�ֽ�ң�����ֽ��״̬��Ϣ
**						
**
** parameters:		rount:BILLACCEPTOR_STACKED,BILLACCEPTOR_ESCROWED,BILLACCEPTOR_RETURNED�ȣ���ʾ��ǰֽ��������λ��
**					chn:  ֽ��ͨ��ֵ
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_UpdateAcpt(uint8_t route,uint8_t chn)
{
	 BillAcpt.Route = route;
	 BillAcpt.Channel = chn;
}

/*****************************************************************************
** Function name:	BillAcceptor_UpDateStackerStat	
**
** Descriptions:	���³���״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_UpDateStackerStat(void)
{
	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			Gbahr1_UpDateStackerStat();
			break;

		case MDB_NOTE_EN:
			MdbNote_UpDateStackerStat();
			break;

		case ITL_NOTE_EN:
			ITL_UpDateStackerStat();
			break;

		default:
			break;
	}
}

/*****************************************************************************
** Function name:	BillAcceptor_RstProc	
**
** Descriptions:	���׽�����ֽ������λ�󣬣����³�ʼ��ֽ������������ʹ��ֽ����
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_RstProc(void)
{
	uint8_t lenth;

	BillAcceptor_ClrRstStat();
	//121106 by cq BillSingleWork	
	//if(BeSaleStat() && (CashState.ChangerState == CHANGER_OK) && (CashTypeEnBit.BillType > 0)) 
	if((BeSaleStat() && (CashState.ChangerState == CHANGER_OK) && (CashTypeEnBit.BillType > 0)) 
	|| ( isBillSingleWork() && (BeSaleStat()) && (CashTypeEnBit.BillType > 0)))
	{
		lenth = BillAcceptor_Enable(CashTypeEnBit.BillType);

		if(BillAcceptor_ErrJudge(lenth) == TRUE)
		{
			BillAcceptor_SetCommErr();
		}
	}
}

/*****************************************************************************
** Function name:	BillAcceptor_PackAnalysis	
**
** Descriptions:	����ֽ������ǰ���ݰ���Ϣ�������ݵ�ǰֽ�������ڵ�״̬��
**					������һ������Ӧ����
**
** parameters:		buf:���ݻ��棬len:���ݳ���
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_PackAnalysis(uint8_t *buf, uint8_t len)
{
	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			Gbahr1_PackAnalysis(buf,len);
			break;

		case MDB_NOTE_EN:
			MdbNote_PackAnalysis(buf,len);
			break;

		case ITL_NOTE_EN:
			ITLNote_PackAnalysis(buf,len);
			break;

		default:
		break;
	}

	BillAcceptor_UpDateSysStat();		
	BillAcceptor_CheckStat();
	
	if(BillAcceptor_RstStat() == TRUE)
	{
		OSTimeDly(OS_TICKS_PER_SEC / 10);
		BillAcceptor_RstProc();
	}
	
	if(IsBillEscrowed() == TRUE) 
	{		
		BillAcceptor_EscrowProc(BillAcpt.Channel);
	} 
	else if(IsBillStacked()) 
	{
		BillAcceptor_StackProc(BillAcpt.Channel);
		OSTimeDly(OS_TICKS_PER_SEC / 10);
		BillAcceptor_UpDateStackerStat();
		NoteEscrowClr();	
	} 
	else if(IsBillReturned() == TRUE) 
	{
	    if(IsEscrowHold()) 
		{
	       BillAcceptor_ReturnProc(BillAcpt.Channel);
	    }
	    NoteEscrowClr();	
	} 		
	
	if((BillAcceptor_StackerFull() == TRUE) && (CashTypeEnBit.BillType > 0)) 
	{
		CashTypeEnBit.BillType = 0;								  //����ֽ����
		BillAcceptor_Enable(CashTypeEnBit.BillType);
	}	
}

/*****************************************************************************
** Function name:	BillAcceptor_ReadBuf	
**
** Descriptions:	��ȡֽ������������
**						
**
** parameters:		buf:���ݻ��棬len:���ݳ���
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_ReadBuf(uint8_t *buf, uint8_t len)
{
	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			Gbahr1_ReadBuf(buf,len);
			break;

		case MDB_NOTE_EN:
			Mdb_ReadBuf(buf,len);
			break;
	    case ITL_NOTE_EN:
			//
			break;
			
		default:
			break;
	}	
}

/*****************************************************************************
** Function name:	BillAcceptor_ErrJudge	
**
** Descriptions:	�ж�ֽ����ͨѶ״̬
**						
**
** parameters:		len:�������Э�飬����ʱ��ʾ���ݳ��ȣ��쳣ʱ��ʾ�쳣״̬
** Returned value:	TRUE:���� FALSE:����	
** 
*****************************************************************************/
uint8_t BillAcceptor_ErrJudge(uint8_t len)
{
	uint8_t status = TRUE;

	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			status = Gbahr1_ErrJudge(len);
			break;

		case MDB_NOTE_EN:
			status = Mdb_ErrJudge(len);
			break;

		case ITL_NOTE_EN:
			status = ITL_ErrJudge(len);
			break;
		default:
			break;
	}
	return status;
}

/*****************************************************************************
** Function name:	BillAcceptor_Init	
**
** Descriptions:	ֽ������ʼ��
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_Init(void)
{
	BillAcceptor_StatInit();
	
	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			Gbahr1_InitProc();
			break;

		case MDB_NOTE_EN:
			MdbNote_InitProc();
			break;

		case ITL_NOTE_EN:
			ITLMission_Init(0);
			break;

		default:
			break;
	}
	
	BillAcceptor_UpDateSysStat();
	BillAcceptor_CheckStat();	
}

/*****************************************************************************
** Function name:	BillAcceptor_PollProc	
**
** Descriptions:	��ѯֽ��������ȡ״̬����������Ӧ����
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_PollProc(void)
{	
	uint8_t len;
	uint8_t BillStatBuf[16];

	BillAcceptor_ClearStat();
	len = BillAcceptor_Poll(CashTypeEnBit.BillType);

	if(BillAcceptor_ErrJudge(len) == TRUE) 
	{
		BillAcceptor_SetCommErr();
	} 
	else 
	{
		len &= 0x0F;
		BillAcceptor_ReadBuf(BillStatBuf,len);
		BillAcceptor_PackAnalysis(BillStatBuf,len);
	}
	
	BillAcceptor_UpDateSysStat();		
	BillAcceptor_CheckStat();		
}

/*****************************************************************************
** Function name:	BillAcceptor_EscrowProc	
**
** Descriptions:	ֽ���������ݴ�״̬ʱ���ж�ֽ����ֵ����������Ӧ����
**						
**
** parameters:		moneych:�ձ�ͨ��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_EscrowProc(uint8_t moneych)
{
	uint32_t PcValue = 0;
	
	//121106 by cq BillSingleWork
	//if(BeSaleStat() && ((IsBillInValid() == TRUE) || (g_Amount+SYSPara.BillValue[moneych] > g_CoinLeft))) 
	if((!isBillSingleWork()) && BeSaleStat() && ((IsBillInValid() == TRUE) || (g_Amount+SYSPara.BillValue[moneych] > g_CoinLeft))) 
	{
	   BillAcceptor_Return(CashTypeEnBit.BillType);
	   MsgBack.moneyback = OVER_VALUE_INDEX << 8;
	   //OSMboxPost(g_KeyMsg,&MsgBack.moneyback);
	   //120621 by cq KeySlowly
	   //while( OSMboxPost(g_KeyMsg,&MsgBack.moneyback) != OS_NO_ERR)
	   while( OSMboxPost(g_MoneyMsg,&MsgBack.moneyback) != OS_NO_ERR)
	   {
	   		OSTimeDly(OS_TICKS_PER_SEC / 100);
	   }
    } 
	else 
	{
       	      /*ֽ�������ݴ湦��*/              /*�ж��Ƿ������ݴ�*/
	//120622 by cq HoldBill		  
	//if((BillAcceptor_EscrowFun() == TRUE) && (moneych >= g_EscrowMinCh))    
	if((BillAcceptor_EscrowFun() == TRUE) &&(BeSaleStat()) && (moneych >= g_EscrowMinCh))    
	   {
	       NoteEscrowHold();
		   //���pc�п������ϱ�pc�ݴ�ֽ��
		   if( SYSPara.PCEnable == 1 )//120620 by cq PCcommunication
		   {
		   	  if(SYSPara.Decimal==1)
			  {
			  	PcValue = SYSPara.BillValue[moneych] * 10;
			  }
			  else if(SYSPara.Decimal==2)
			  {
			  	PcValue = SYSPara.BillValue[moneych]; 
			  }	
			  sysVPMission.billHoldingValue = PcValue;
			  sysVPMission.billHoldingFlag = 1;
		   	  VPMission_Payin_RPT( VP_DEV_ESCROWIN, PcValue );		
		   }
		   MsgBack.moneyback = (SYSPara.BillValue[moneych])|0x8000;   //money���루16λ�������λ��1������Ϊ��ֵ				   		 
	       //OSMboxPost(g_KeyMsg,&MsgBack.moneyback);
	       //120621 by cq KeySlowly
	       //while( OSMboxPost(g_KeyMsg,&MsgBack.moneyback) != OS_NO_ERR)		   	
	       while( OSMboxPost(g_MoneyMsg,&MsgBack.moneyback) != OS_NO_ERR)
		   {
		   		OSTimeDly(OS_TICKS_PER_SEC / 100);
		   }
	   }
	   else 
	   {
		   NoteEscrowSet();
		   BillAcceptor_Stack(CashTypeEnBit.BillType);	                 //ִ��ѹ������
		   if(BeSaleStat()) 
		   {
		       TranTotal.DoubtMoney += SYSPara.BillValue[moneych];
		   }
	   }	  
    }
}

/*****************************************************************************
** Function name:	BillAcceptor_StackProc	
**
** Descriptions:	��ֽ��ѹ��ʱ�����½�������
**						
**
** parameters:		moneych:�ձ�ͨ��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_StackProc(uint8_t moneych)
{	
	uint8_t chnbase = 0;
	//uint32_t PcValue = 0;

	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			chnbase = NOTE_GBA_BASE;
			break;

		case MDB_NOTE_EN:
			chnbase = NOTE_MDB_BASE;
			break;
			
		case ITL_NOTE_EN:
			chnbase = NOTE_ITL_BASE;
			break;

		default:
			break;
	}
	
	if(BeSaleStat()) 
	{
	   TranData.IncomeCH[chnbase+moneych]++;
	   TranTotal.IncomeCH[chnbase+moneych]++;
	   TranTotal.Income += SYSPara.BillValue[moneych];
	   TranTotal.NoteIncome += SYSPara.BillValue[moneych];

	   if(TranTotal.DoubtMoney >= SYSPara.BillValue[moneych]) 
	   {						   				   
           TranTotal.DoubtMoney -= SYSPara.BillValue[moneych];
	   }

	   //���ڼ��Ƚ�����;by gzz 20121009
	   TranTotal.IncomeJidu += SYSPara.BillValue[moneych];
	   TranTotal.NoteIncomeJidu += SYSPara.BillValue[moneych];

	   //���pc�п������ϱ�pc��ֽ��
	   //if( SYSPara.PCEnable == 1 )
	   //{
	   //	  if(SYSPara.Decimal==1)
		//  {
		//  	PcValue = SYSPara.BillValue[moneych] * 10;
		//  }
		//  else if(SYSPara.Decimal==2)
		//  {
		//  	PcValue = SYSPara.BillValue[moneych]; 
		//  }	
	   	//  VPMission_Payin_RPT( VP_DEV_BILL, PcValue );
	   //}
    }
    if(!IsEscrowHold()) 
	{
	    MsgBack.moneyback = (SYSPara.BillValue[moneych])|0x8000;   //money���루16λ�������λ��1������Ϊ��ֵ				   		 
	    //OSMboxPost(g_KeyMsg,&MsgBack.moneyback); 
	    //120621 by cq KeySlowly
	    //while( OSMboxPost(g_KeyMsg,&MsgBack.moneyback) != OS_NO_ERR)
	    while( OSMboxPost(g_MoneyMsg,&MsgBack.moneyback) != OS_NO_ERR)
	    {
	   		OSTimeDly(OS_TICKS_PER_SEC / 100);
	    }
    } 
	else 
	{
        MsgBack.pBackMsg = moneych;					 
	    OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);
    }
}

/*****************************************************************************
** Function name:	BillAcceptor_ReturnProc	
**
** Descriptions:	�ݴ�ֽ���˳�
**						
**
** parameters:		moneych:�ձ�ͨ��
** Returned value:	��	
** 
*****************************************************************************/
void BillAcceptor_ReturnProc(uint8_t moneych)
{
	if(BillAcceptor_EscrowFun() == TRUE) 
	{
		MsgBack.pBackMsg = moneych;					 
		OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);
	}
}

/*****************************************************************************
** Function name:	BillAcceptor_Stack
**
** Descriptions:	ѹ��
**						
**
** parameters:		billtype:GBAHR1ֽ����ʹ��ͨ��
** Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���	
** 
*****************************************************************************/
uint8_t BillAcceptor_Stack(uint16_t billtype)
{
	uint8_t len = 0;
	uint32_t PcValue = 0;

	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			ACKSwitch();
			len = Gbahr1_Stack(billtype);
			break;

		case MDB_NOTE_EN:
			len = MdbNote_Stack();
			break;

		case ITL_NOTE_EN:
			len = ITLMission_HB_Stack();
			break;	

		default:
			break;
	}
	//���pc�п������ϱ�pc��ֽ��
    if( SYSPara.PCEnable == 1 )//120620 by cq PCcommunication
    {
      if(SYSPara.Decimal==1)
	  {
	  	PcValue = SYSPara.BillValue[BillAcpt.Channel] * 10;
	  }
	  else if(SYSPara.Decimal==2)
	  {
	  	PcValue = SYSPara.BillValue[BillAcpt.Channel]; 
	  }	

	  if(sysVPMission.billHoldingFlag == 1)	
	  {
	  	 VPMission_Payin_RPT( VP_DEV_BILL, sysVPMission.billHoldingValue );
	  	 sysVPMission.billHoldingValue = 0;
		 sysVPMission.billHoldingFlag = 0;
	  }	 
	  else
	  {
	  	VPMission_Payin_RPT( VP_DEV_BILL, PcValue );
	  }
    }

	return len;
}

/*****************************************************************************
** Function name:	BillAcceptor_Return	
**
** Descriptions:	�˱�
**						
**
** parameters:		billtype:GBAHR1ֽ����ʹ��ͨ��
** Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���
** 
*****************************************************************************/
uint8_t BillAcceptor_Return(uint16_t billtype)
{
	uint8_t len = 0;
	//uint32_t PcValue = 0;

	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			ACKSwitch();
			len = Gbahr1_Return(billtype);
			break;

		case MDB_NOTE_EN:
			len = MdbNote_Return();
			break;

		case ITL_NOTE_EN:
			len = ITLMission_Reject();
			break;	

		default:
			break;
	}
	//���pc�п������ϱ�pc�ݴ�ֽ���˳�
    if( SYSPara.PCEnable == 1 )//120620 by cq PCcommunication
    {	      
	   	  VPMission_Payin_RPT( VP_DEV_ESCROWOUT, sysVPMission.billHoldingValue );	
		  sysVPMission.billHoldingValue = 0;
		  sysVPMission.billHoldingFlag = 0;
    }
	

	return len;
}

/*****************************************************************************
** Function name:	BillAcceptor_Enable	
**
** Descriptions:	ֽ����ʹ��
**						
**
** parameters:		billtype:ֽ����ʹ��ͨ��
** Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���	
** 
*****************************************************************************/
uint8_t BillAcceptor_Enable(uint16_t billtype)
{
	uint8_t len = 0;

	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			ACKSwitch();
			len = Gbahr1_Enable(billtype);
			break;

		case MDB_NOTE_EN:
			len = MdbNote_Enable(billtype);
			break;
		
		case ITL_NOTE_EN:
			len = ITLMission_Enable(billtype);
			break;
		default:
			break;
	}

	return len;
}

/*****************************************************************************
** Function name:	BillAcceptor_Poll
**
** Descriptions:	ֽ������ѯ
**						
**
** parameters:		billtype:GBAHR1ֽ����ʹ��ͨ��
** Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���	
** 
*****************************************************************************/
uint8_t BillAcceptor_Poll(uint16_t billtype)
{
	uint8_t len = 0;

	switch(SYSPara.GBAEnable) 
	{
		case HR_NOTE_EN:
			ACKSwitch();
			len = Gbahr1_Poll(billtype);
			break;

		case MDB_NOTE_EN:
			len = MdbNote_Poll();
			break;

		case ITL_NOTE_EN:
			len = ITLMission_Poll();
			break;	

		default:
			break;
	}

	return len;
}
