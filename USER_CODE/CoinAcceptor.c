/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           CoinAcceptor.c
** Last modified Date:  2011-10-27
** Last Version:         
** Descriptions:        Ӳ������������
**                      
**------------------------------------------------------------------------------------------------------
** Created by:           
** Created date:        2011-10-27
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
#include "mdb.h"
#include "MdbCoin.h"
//#include "MdbCoinApp.h"//120401 by cq change structor
#include "PulseCoin.h"
//#include "PulseCoinApp.h"//120401 by cq change structor
#include "CoinAcceptor.h"
#include "VMC_PC.h"


#if 0
//#define IsLessCoinStat()           (g_CoinTypeNum[g_ChangeMinCh] < MDB_COINNUMMIN)
#define IsLessCoinStat()		   (CoinLeft < CoinPara.Decimal * MDB_COINNUMMIN)
#endif

CoinParaStruct CoinPara;

extern uint8_t Changer_LowStat(void);

/*���յ�Ӳ�Ҳ����ṹ��*/
struct CoinDeposit
{
	uint8_t Route;	      //�н��յ�Ӳ��ΪCOINACCEPTOR_STACKED�����˱�ΪCOINACCEPTOR_RETURN������Ϊ0
	uint8_t Channel;	  //Ӳ��ͨ��
} CoinDpst;

uint8_t  CoinRstStat;	  //Ӳ�����ո��Ƿ�λ��־
uint8_t  CoinCommErr;     //Ӳ����ͨѶ״̬ TRUE:���� FALSE:�쳣
uint8_t  CoinValueErr;	  //Ӳ������ͨ����ֵ�����Ƿ���ȷ TRUE:���� FALSE:�쳣
uint8_t  CoinTubeFull;    //Ӳ��������״̬ TRUE:�� FALSE:δ��
uint16_t CoinStat;		  //Ӳ����״̬,״ֵ̬��Ӳ�������Э���ֲ�
uint32_t CoinsInTube;	  //������Ӳ������

/*****************************************************************************
** Function name:	CoinAcceptor_StatInit	
**
** Descriptions:	��ʼ��Ӳ����״ֵ̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_StatInit(void)
{
	CoinDpst.Route = 0;
	CoinRstStat = FALSE;
	CoinCommErr = FALSE;
	CoinValueErr = FALSE;
	CoinStat = COIN_STAT_OK;
}

/*****************************************************************************
** Function name:	CoinAcceptor_UpDateDeposit	
**
** Descriptions:	���յ�Ӳ��ʱ������Ӳ�Ҳ���
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_UpDateDeposit(uint8_t route, uint8_t chn)
{
	CoinDpst.Route = route;
	CoinDpst.Channel = chn;
}

/*****************************************************************************
** Function name:	CoinAcceptor_ClrDeposit	
**
** Descriptions:	����ϴ��ձ�Ӳ�Ҳ���
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_ClrDeposit(void)
{
	CoinDpst.Route = 0;
}

/*****************************************************************************
** Function name:	IsCoinStacked	
**
** Descriptions:	��ѯ�󷵻���Ϣ���ж��Ƿ���Ͷ����Ϣ����
**						
**
** parameters:		��
** Returned value:	TRUE:��Ͷ�� FALSE:��	
** 
*****************************************************************************/
uint8_t IsCoinStacked(void)
{
	if(CoinDpst.Route == COINACCEPTOR_STACKED) 
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*****************************************************************************
** Function name:	IsCoinReturn	
**
** Descriptions:	��ѯ�󷵻���Ϣ���ж��Ƿ����˱���Ϣ����
**						
**
** parameters:		��
** Returned value:	TRUE:��Ͷ�� FALSE:��	
** 
*****************************************************************************/
uint8_t IsCoinReturn(void)
{
	if(CoinDpst.Route == COINACCEPTOR_RETURN) 
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*****************************************************************************
** Function name:	CoinAcceptor_CommErr	
**
** Descriptions:	�����ж��Ƿ���ͨѶ����
**						
**
** parameters:		��
** Returned value:	TRUE:���� FALSE:����	
** 
*****************************************************************************/
uint8_t CoinAcceptor_CommErr(void)
{
	return CoinCommErr;
}

/*****************************************************************************
** Function name:	CoinAcceptor_RstStat	
**
** Descriptions:	�����жϸո��Ƿ�λ��
**						
**
** parameters:		��
** Returned value:	TRUE:��λ�� FALSE:û��λ	
** 
*****************************************************************************/
uint8_t CoinAcceptor_RstStat(void)
{
	return CoinRstStat;
}

/*****************************************************************************
** Function name:	CoinAcceptor_ValueSetErr	
**
** Descriptions:	�����ж���ֵ�����Ƿ�����
**						
**
** parameters:		��
** Returned value:	TRUE:���ô��� FALSE:��ȷ	
** 
*****************************************************************************/
uint8_t CoinAcceptor_ValueSetErr(void)
{
	return CoinValueErr;
}

/*****************************************************************************
** Function name:	CoinAcceptor_TubeFull	
**
** Descriptions:	�����жϴ������Ƿ�Ϊ��
**						
**
** parameters:		��
** Returned value:	TRUE:�� FALSE:δ��	
** 
*****************************************************************************/
uint8_t CoinAcceptor_TubeFull(void)
{
	return CoinTubeFull;
}

/*****************************************************************************
** Function name:	CoinAcceptor_Available	
**
** Descriptions:	�ж�Ӳ�����Ƿ����
**					ͨѶ�Ƿ���������ֵ�����Ƿ���ȷ��	
**
** parameters:		��
** Returned value:	TRUE:Ӳ�������� FALSE:������	
** 
*****************************************************************************/
uint8_t CoinAcceptor_Available(void)
{
	if((CoinCommErr == FALSE) && (CoinValueErr == FALSE))  
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

/*****************************************************************************
** Function name:	CoinAcceptor_SetTubeFull	
**
** Descriptions:	���ô�������״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_SetTubeFull(void)
{
	CoinTubeFull = TRUE;
}

/*****************************************************************************
** Function name:	CoinAcceptor_SetCommErr	
**
** Descriptions:	����ͨѶ����״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_SetCommErr(void)
{
	CoinCommErr = TRUE;	
}

/*****************************************************************************
** Function name:	CoinAcceptor_SetValueErr	
**
** Descriptions:	������ֵ����״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_SetValueErr(void)
{
	CoinValueErr = TRUE;	
}

/*****************************************************************************
** Function name:	CoinAcceptor_SetCoinPara	
**
** Descriptions:	����Ӳ��������
**						
**
** parameters:		Ӳ��������
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_SetCoinPara(CoinParaStruct coinpara)
{
	CoinPara = coinpara;
}

/*****************************************************************************
** Function name:	CoinAcceptor_GetCoinLevel	
**
** Descriptions:	��ȡӲ�����ȼ�
**						
**
** parameters:		��
** Returned value:	Ӳ�����ȼ�	
** 
*****************************************************************************/
uint8_t CoinAcceptor_GetCoinLevel(void)
{
	return CoinPara.Level;
}

/*****************************************************************************
** Function name:	CoinAcceptor_GetCoinScale	
**
** Descriptions:	��ȡӲ������������
**						
**
** parameters:		��
** Returned value:	Ӳ������������	
** 
*****************************************************************************/
uint8_t CoinAcceptor_GetCoinScale(void)
{
	return CoinPara.Scale;
}

/*****************************************************************************
** Function name:	CoinAcceptor_GetCoinDecimal	
**
** Descriptions:	��ȡӲ����С��λ��
**						
**
** parameters:		��
** Returned value:	С��λ��Ϊn���򷵻�10^n	
** 
*****************************************************************************/
uint8_t CoinAcceptor_GetCoinDecimal(void)
{
	return CoinPara.Decimal;
}

/*****************************************************************************
** Function name:	CoinAcceptor_SetRstStat	
**
** Descriptions:	����Ӳ������λ״̬����ʾӲ�����ոո�λ��
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_SetRstStat(void)
{
    CoinRstStat = TRUE;
}

/*****************************************************************************
** Function name:	BillAcceptor_CLrRstStat	
**
** Descriptions:	���Ӳ������λ״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_ClrRstStat(void)
{
    CoinRstStat = FALSE;
}

/*****************************************************************************
** Function name:	CoinAcceptor_UpDateStat	
**
** Descriptions:	���ڸ���Ӳ����������ͨѶ״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_UpDateStat(uint16_t stat)
{
	CoinStat = stat;
}

/*****************************************************************************
** Function name:	CoinAcceptor_ReadBuf	
**
** Descriptions:	��ȡӲ������������
**						
**
** parameters:		buf:���ݻ��棬len:���ݳ���
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_ReadBuf(uint8_t *buf, uint8_t len)
{
	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			break;

		case MDB_COIN_EN:
			Mdb_ReadBuf(buf,len);
			break;

		default:
			break;
	}	
}

/*****************************************************************************
** Function name:	CoinAcceptor_ErrJudge	
**
** Descriptions:	�ж�Ӳ����ͨѶ״̬
**						
**
** parameters:		len:�������Э�飬����ʱ��ʾ���ݳ��ȣ��쳣ʱ��ʾ�쳣״̬
** Returned value:	TRUE:���� FALSE:����	
** 
*****************************************************************************/
uint8_t CoinAcceptor_ErrJudge(uint8_t len)
{
	uint8_t status = TRUE;

	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			break;

		case MDB_COIN_EN:
			status = Mdb_ErrJudge(len);
			break;

		default:
			break;
	}
	return status;
}

/*****************************************************************************
** Function name:	CoinAcceptor_UpDateSysStat	
**
** Descriptions:	���µ�ǰӲ����״̬��SYSPara.CoinsStat
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_UpDateSysStat(void)
{
	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			break;

		case MDB_COIN_EN:
			SYSPara1.CoinsStat = CoinStat;
			if(CoinAcceptor_CommErr() == TRUE) 
			{
				SYSPara1.CoinsStat |= COIN_COMMERR_BIT;
			}
			if(CoinAcceptor_ValueSetErr() == TRUE) 
			{
				SYSPara1.CoinsStat |= COIN_VALUE_BIT;
			}
			if(CoinAcceptor_TubeFull() == TRUE) 
			{
				SYSPara1.CoinsStat |= COIN_FULL_BIT;
			} 
			break;

		default:
			break;
	}
}

/*****************************************************************************
** Function name:	CoinAcceptor_CheckStat	
**
** Descriptions:	����CoinStat(CoinStatӲ����״̬û�о����״̬�룬ֻ�������ж�Ӳ�����Ƿ�������)
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_CheckStat(void)
{
	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			if(SYSPara1.CoinsStat & COIN_VALUE_BIT) 
			{
				CashState.CoinState |= COIN_DEV_PERR;
			}
			break;

		case MDB_COIN_EN:
			if(SYSPara1.CoinsStat != COIN_STAT_OK) 
			{			 //����
			     if(SYSPara1.CoinsStat & COIN_VALUE_BIT) 
				 {
					 //120703 by cq MDBCompatible
				     //CashState.CoinState |= COIN_DEV_PERR;
				     
					 CashState.CoinState = COIN_DEV_OK;
					 if(SYSPara.ChangerEnable == MDB_CHANGER_EN) 
					 {
						 CashState.ChangerState &= ~CHANGER_ER;
					 }
				 }
				 if(SYSPara1.CoinsStat & (~COIN_VALUE_BIT)) 
				 {
				     CashState.CoinState |= COIN_DEV_ER;
				 }
				 if((SYSPara.ChangerEnable == MDB_CHANGER_EN) 
				   && ((SYSPara1.CoinsStat & (~COIN_FULL_BIT)) != COIN_STAT_OK)) 
				 {
			         CashState.ChangerState |= CHANGER_ER;
			     }			 			 
			} 
			else
			{
			     CashState.CoinState = COIN_DEV_OK;
				 if(SYSPara.ChangerEnable == MDB_CHANGER_EN) 
				 {
			         CashState.ChangerState &= ~CHANGER_ER;
			     }
			}
						       
		    if(Changer_LowStat() == TRUE) 
			{
			    CashState.ChangerState |= CHANGER_LOW;			   
		    } 
			else 
			{
			    CashState.ChangerState &= ~CHANGER_LOW;
		    }
			break;

		default:
			CashState.CoinState |= COIN_DEV_NONE;
			break;
	}
}

/*****************************************************************************
** Function name:	CoinAcceptor_UpDateTubeStat	
**
** Descriptions:	���´��ҹ�״̬��ʣ����
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_UpDateTubeStat(void)
{
	   uint16_t tbstat;
	 	 
	   tbstat = CoinAcceptor_CheckTubeStat(CashTypeEnBit.CoinType,&CoinsInTube);

	   if(CashTypeEnBit.CoinFullBit != tbstat) 
	   {
		   CashTypeEnBit.CoinFullBit = tbstat;
		   						   
		   OSTimeDly(OS_TICKS_PER_SEC / 10);
		   //��������,ԭ����Ӧͨ�������󣬻�Ѷ�Ӧͨ�����ܡ����ڲ������;by gzz 20121025
		   //CashTypeEnBit.CoinType = CashTypeEnBit.CoinTypeEN & (~CashTypeEnBit.CoinFullBit);
		   CashTypeEnBit.CoinType = CashTypeEnBit.CoinTypeEN;
	       CoinAcceptor_Enable(CashTypeEnBit.CoinType);	         //ʹ��Ӳ������Ӧ��ֵ
	
		   if(CashTypeEnBit.CoinFullBit && ((CashTypeEnBit.CoinFullBit & CashTypeEnBit.CoinTypeEN) == CashTypeEnBit.CoinTypeEN)) 
		   {
			  CoinAcceptor_SetTubeFull();
		   }
	   }	  	   

	   g_CoinLeft = CoinsInTube;

	   if(g_CoinLeft > SYSPara.MoneyMaxin) 
	   {
          g_CoinLeft = SYSPara.MoneyMaxin;
       }
}

/*****************************************************************************
** Function name:	CoinAcceptor_StackProc	
**
** Descriptions:	��Ͷ��ʱ������ϵͳ���ݣ�������
**						
**
** parameters:		moneych:Ͷ��ͨ��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_StackProc(uint8_t moneych)
{
   uint8_t chnbase = 0;
   uint32_t PcValue = 0;

   switch(SYSPara.CoinEnable) 
   {
		case PULSE_COIN_EN:
			chnbase = COIN_PULSE_BASE;
			break;

		case MDB_COIN_EN:
			chnbase = COIN_MDB_BASE;
			break;

		default:
			break;
	}
   
   if(BeSaleStat()) 
   {
	   TranData.IncomeCH[chnbase+moneych]++;
	   TranTotal.IncomeCH[chnbase+moneych]++;
	   TranTotal.Income += SYSPara.CoinsValue[moneych];
	   TranTotal.CoinsIncome += SYSPara.CoinsValue[moneych];

	   //���ڼ��Ƚ�����;by gzz 20121009
	   TranTotal.IncomeJidu += SYSPara.CoinsValue[moneych];	   
	   TranTotal.CoinsIncomeJidu += SYSPara.CoinsValue[moneych];
	   
	   //���pc�п������ϱ�pc��Ӳ��
	   if( SYSPara.PCEnable == 1 )//120620 by cq PCcommunication
	   {
	      if(SYSPara.Decimal==1)
		  {
		  	PcValue = SYSPara.CoinsValue[moneych] * 10;
		  }
		  else if(SYSPara.Decimal==2)
		  {
		  	PcValue = SYSPara.CoinsValue[moneych]; 
		  }
	   	  VPMission_Payin_RPT( VP_DEV_COIN, PcValue );		
	   }
   }   
   
   //MsgBack.moneyback = (SYSPara.CoinsValue[moneych]) | 0x8000;  //money���루16λ�������λ��1������Ϊ��ֵ	   
   //120621 by cq KeySlowly
   //while( OSMboxPost(g_KeyMsg,&MsgBack.moneyback) != OS_NO_ERR)   	
   //while( OSMboxPost(g_MoneyMsg,&MsgBack.moneyback) != OS_NO_ERR)
   //{
   //		OSTimeDly(OS_TICKS_PER_SEC / 100);
   //}
   //ʹ�������mdbӲ��;by gzz 20130105
    MsgBack.coinPlusback = (SYSPara.CoinsValue[moneych]) | 0x8000;
	OSQPost(g_CoinPlusMsg,&MsgBack.coinPlusback);
	OSTimeDly(OS_TICKS_PER_SEC / 5);   
	//Trace("\r\n coinPlus=%d", MsgBack.coinPlusback&(0x7FFF));
}

/*****************************************************************************
** Function name:	CoinAcceptor_ReturnProc	
**
** Descriptions:	���˱Ұ�ťʱ����Ӳ����״̬
**						
**
** parameters:		��
** Returned value:	��	
**
*****************************************************************************/ 
void CoinAcceptor_ReturnProc(void)
{
	uint8_t returnkey;//120621 by cq KeySlowly


   switch(SYSPara.CoinEnable) 
   {
	   case PULSE_COIN_EN:
	   		break;

	   case MDB_COIN_EN:
		   if(CoinAcceptor_GetCoinLevel() < 3) 
		   {
			   if(CoinStat == COIN_JAM)//���ԭ���п��� 
			   {
			       CoinAcceptor_UpDateStat(0);
				   CoinAcceptor_UpDateSysStat();							   
				   
				   if(SYSPara1.CoinsStat == COIN_STAT_OK) 
				   {						       
					   ClrDevStatus(DEV_ERR_BIT_COIN);
					   if(Changer_LowStat() == TRUE) 
					   {
					       CashState.ChangerState |= CHANGER_LOW;
						   if(SYSPara.ChangeServer == 0) 
						   {
							   SetDevStatus(DEV_ERR_BIT_COINLOW);
						   }
					   }							   						   
				   
					   if((BeSaleStat()) && IsDeviceOK() 
					       && (CashTypeEnBit.CoinType == 0) && (g_Amount < SYSPara.MoneyMaxin)) 
					   {
					       OSTimeDly(OS_TICKS_PER_SEC / 10);
						   //��������,ԭ����Ӧͨ�������󣬻�Ѷ�Ӧͨ�����ܡ����ڲ������;by gzz 20121025
						   //CashTypeEnBit.CoinType = CashTypeEnBit.CoinTypeEN & (~CashTypeEnBit.CoinFullBit);
						   CashTypeEnBit.CoinType = CashTypeEnBit.CoinTypeEN;

						   Trace("if((BeSaleStat()) && IsDeviceOK() && (CashTypeEnBit.CoinType == 0) && (g_Amount < SYSPara.MoneyMaxin))");

						   MdbCoin_Enable(CashTypeEnBit.CoinType);	  //ʹ��	
					   }
				   }				   						   
			   }
		   }
		
		   if((BeSaleStat()) && IsDeviceOK()) 
		   {
			   //120621 by cq KeySlowly
			   //MsgBack.moneyback = RETURN_MONEY_INDEX << 8;
			   MsgBack.keyback = RETURN_MONEY_INDEX << 8;
		       //OSMboxPost(g_KeyMsg,&MsgBack.moneyback);

			   /*
		       while( OSMboxPost(g_KeyMsg,&MsgBack.moneyback) != OS_NO_ERR)
			   {
			   		OSTimeDly(OS_TICKS_PER_SEC / 100);
			   }
			   */
			   returnkey=OSQPost(g_KeyMsg,&MsgBack.keyback);//120621 by cq KeySlowly
			   
		   }
		   break;

	   default:
	   	   break;
	}
}

/*****************************************************************************
** Function name:	CoinAcceptor_Diagnostic	
**
** Descriptions:	�ж�Ӳ����״̬
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_Diagnostic(void)
{
	uint8_t buf[16],lenth,i;
	uint16_t status;
	
	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			break;

		case MDB_COIN_EN:
			if(CoinAcceptor_GetCoinLevel() >= 3) 
			{
				lenth = MdbCoin_Diagnostic();	     //���״̬
				
				if(lenth <= 16) 
				{				      
					Mdb_ReadBuf(buf,lenth);
					for(i = 0; i < lenth-1; i=i+2) 
					{	
						/*
						if((buf[i] == 0x03) && (buf[i+1] == 0)) 
						{
						    CoinAcceptor_UpDateStat(0);
						} 
						//121011 by cq NRITubeRemoved
						else if((buf[i] == 0x06) && (buf[i+1] == 0))
						{
						    CoinAcceptor_UpDateStat(0);
						}
						else if((buf[i] & 0x10) && (buf[i+1] > 0)) 
						{
						    if(!((buf[i] == 0x11) && (buf[i+1] == 0x10))) 
							{
							    status = (buf[i] << 8) | buf[i+1];
								CoinAcceptor_UpDateStat(status);
							    break;
						    }
						} 
						else 
						{
						  //
						}
						*/
						//Trace("\r\n dispense=%d,%d",buf[0],buf[1]);
						if(buf[i] > 0x06)
						{
						    status = (buf[i] << 8) | buf[i+1];
							CoinAcceptor_UpDateStat(status);
						    break;
					    }	
						else
						{
						    CoinAcceptor_UpDateStat(0);
						} 	
					}
				}
			}
			break;

		default:
			break;
	}
}

/*****************************************************************************
** Function name:	CoinAcceptor_RstProc	
**
** Descriptions:	���׽�����Ӳ������λ�󣬣����³�ʼ��Ӳ������������ʹ��Ӳ����
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_RstProc(void)
{
	uint8_t lenth;

	CoinAcceptor_ClrRstStat();
	if(BeSaleStat())
	{
		//��������,ԭ����Ӧͨ�������󣬻�Ѷ�Ӧͨ�����ܡ����ڲ������;by gzz 20121025
       //CashTypeEnBit.CoinType = CashTypeEnBit.CoinTypeEN & (~CashTypeEnBit.CoinFullBit);
       CashTypeEnBit.CoinType = CashTypeEnBit.CoinTypeEN;
	   if(CashTypeEnBit.CoinType > 0) 
	   {
           lenth = CoinAcceptor_Enable(CashTypeEnBit.CoinType);	 //ʹ��Ӳ������Ӧ��ֵ

		   if(CoinAcceptor_ErrJudge(lenth) == TRUE) 
		   {
		   		CoinAcceptor_CommErr();
		   }
	   }
	}
}

/*****************************************************************************
** Function name:	CoinAcceptor_PackAnalysis	
**
** Descriptions:	����Ӳ������ǰ���ݰ���Ϣ�������ݵ�ǰֽ�������ڵ�״̬��������һ������Ӧ����
**						
**
** parameters:		buf:���ݻ��棬len:���ݳ���
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_PackAnalysis(uint8_t *buf, uint8_t len)
{
	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			break;

		case MDB_COIN_EN:
			MdbCoin_PackAnalysis(buf,len);
			break;

		default:
			break;
	}

	CoinAcceptor_UpDateSysStat();		
	CoinAcceptor_CheckStat();
	
    if(CoinAcceptor_RstStat() == TRUE) 
	{
		OSTimeDly(OS_TICKS_PER_SEC / 10);
		CoinAcceptor_RstProc();
	}
	
	if(IsCoinStacked()) 
	{
		CoinAcceptor_StackProc(CoinDpst.Channel);
		OSTimeDly(OS_TICKS_PER_SEC / 10);
		CoinAcceptor_UpDateTubeStat();	
	}
	else if(IsCoinReturn() == TRUE) 
	{
	    CoinAcceptor_ReturnProc();	
	} 	
}

/*****************************************************************************
** Function name:	CoinAcceptor_Init	
**
** Descriptions:	Ӳ������ʼ��
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_Init(void)
{
	CoinAcceptor_StatInit();
	
	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			Pulse_InitProc();
			break;

		case MDB_COIN_EN:
			MdbCoin_InitProc();
			break;

		default:
			break;
	}
	
	CoinAcceptor_UpDateSysStat();
	CoinAcceptor_CheckStat();	
}

/*****************************************************************************
** Function name:	CoinAcceptor_PollProc	
**
** Descriptions:	��ѯӲ��������ȡ״̬����������Ӧ����
**						
**
** parameters:		��
** Returned value:	��	
** 
*****************************************************************************/
void CoinAcceptor_PollProc(void)
{	
	uint8_t len;
	uint8_t CoinStatBuf[16];
	static uint8_t time = 5;

	CoinAcceptor_ClrDeposit();
	len = CoinAcceptor_Poll(CashTypeEnBit.CoinType);

	if(CoinAcceptor_ErrJudge(len) == TRUE) 
	{
		CoinAcceptor_SetCommErr();
	} 
	else 
	{
		len &= 0x0F;
		CoinAcceptor_ReadBuf(CoinStatBuf,len);
		CoinAcceptor_PackAnalysis(CoinStatBuf,len);
	}
	
	if(time-- == 0) 
	{
		time = 5;
		OSTimeDly(OS_TICKS_PER_SEC / 10);
		CoinAcceptor_Diagnostic();
	}
	
	CoinAcceptor_UpDateSysStat();
	CoinAcceptor_CheckStat();		
}

/*****************************************************************************
** Function name:	CoinAcceptor_Enable	
**
** Descriptions:	Ӳ����ʹ��
**						
**
** parameters:		cointype:Ӳ����ʹ��ͨ��
** Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���	
** 
*****************************************************************************/
uint8_t CoinAcceptor_Enable(uint16_t cointype)
{
	uint8_t len = 0;

	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			if(cointype > 0) 
			{
				Pulse_Enable();
			} 
			else 
			{
				Pulse_Disable();
			}
			break;

		case MDB_COIN_EN:
			
			Trace("\r\ncase MDB_COIN_EN:");
			
			len = MdbCoin_Enable(cointype);
			break;

		default:
			break;
	}

	return len;
}

/*****************************************************************************
** Function name:	CoinAcceptor_Poll	
**
** Descriptions:	Ӳ������ѯ
**						
**
** parameters:		cointype:Ӳ������ѯͨ��
** Returned value:	������0x80ΪͨѶ����״̬������Ϊ���ܵ������ݳ���	
** 
*****************************************************************************/
uint8_t CoinAcceptor_Poll(uint16_t cointype)
{
	uint8_t len = 0;

	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			break;

		case MDB_COIN_EN:
			len = MdbCoin_Poll();
			break;

		default:
			break;
	}

	return len;
}

/*****************************************************************************
** Function name:	CoinAcceptor_CheckTubeStat	
**
** Descriptions:	��ȡ���ҹ�״̬��ʣ����
**						
**
** parameters:		cointype:Ӳ����ʹ��ͨ����coinleft:ʣ���ܱ�ֵ
** Returned value:	���ҹ���״̬λ	
** 
*****************************************************************************/
uint16_t CoinAcceptor_CheckTubeStat(uint16_t cointype, uint32_t *coinleft)
{
	uint16_t status = 0;

	switch(SYSPara.CoinEnable) 
	{
		case PULSE_COIN_EN:
			*coinleft = g_CoinLeft;
			break;

		case MDB_COIN_EN:
			status = MdbCoin_CheckTubeStat(coinleft);
			break;

		default:
			break;
	}

	return status;
}

