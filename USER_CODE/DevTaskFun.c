/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           DevTaskFun.c
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        ֽ����Ӳ�������ܣ�ʹ�ܣ�������ʹ�õ���س��������ﲻ���廮����һ����ձ������豸
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
#include "..\driver\LPC17xx.h"
#include "..\driver\lpc_types.h"
#include "..\config.h"
#include "global.h"
#include "drv.h"
#include "PulseCoin.h"
#include "hopper.h"
#include "BillAcceptor.h"
#include "CoinAcceptor.h"
#include "Changer.h"
#include "DevTaskFun.h"



//121106 by cq BillSingleWork
uint8_t cBillSingleWork = 0;
uint8_t isBillSingleWork()
{
	return cBillSingleWork;
}

//121108 by cq GOCErrorSevice
uint8_t cGOCErrorSevice = 0;
uint8_t isGOCErrorSevice()
{
	if(cGOCErrorSevice)
		SYSPara.GOCCtr = 1;

	return cGOCErrorSevice;
}

//121108 by cq RecordPassword
uint8_t cRecordPassword = 0;
uint8_t isRecordPassword()
{
	return cRecordPassword;
}

//121108 by cq DontReduceNum 
uint8_t cDontReduceNum = 0;
uint8_t isDontReduceNum()
{
	return cDontReduceNum;
}




/*��ʼ����MDBͶ�������豸״̬*/
void InitMoneyDevStat(void)
{
    uint8_t i;
		
	CashState.CoinState = COIN_DEV_OK;
	CashState.NoteState = NOTE_DEV_OK;
	CashState.ChangerState = CHANGER_OK;

    SYSPara1.CoinsStat &= 0;//COIN_VALUE_BIT;		  //��ʼ��״ֵ̬�������»�ȡ
	if(SYSPara.GBAEnable == HR_NOTE_EN) 
	{
		SYSPara1.NoteStat &= 0;//HR_VALUE_BIT;
	} 
	else 
	{
	    SYSPara1.NoteStat &= 0;//GBA_VALUE_BIT;
	}	
	
    //������������
	if(SYSPara.ChangerEnable == 0) 
	{					   
	    CashState.ChangerState |= CHANGER_NONE;
		for(i = 0; i < HOPPERCHMAX; i++) 
		{
		    SYSPara1.HopperStat[i] = HOPPER_DISABLE_BIT;   //����������
		}
	}

	//ֽ����������
	if(SYSPara.GBAEnable == 0) 
	{						   
	    CashState.NoteState |= NOTE_DEV_NONE;
		SYSPara1.NoteStat |= MBV_COMMERR_BIT;
	}

	//Ӳ����������
	if(SYSPara.CoinEnable == 0) 
	{						   
	    SYSPara1.CoinsStat |= COIN_COMMERR_BIT;
		CashState.CoinState |= COIN_DEV_NONE;
	}

	//��������MDB�豸����Ӳ��������MDB�豸����������״̬��Ϊ��
	if((SYSPara.CoinEnable != MDB_COIN_EN) && (SYSPara.ChangerEnable == MDB_CHANGER_EN)) 
	{
	    CashState.ChangerState |= CHANGER_NONE;
	}
}

/*���۸������Ƿ���0Ԫ��ֵ*/
void CheckPricePara(void)	 
{
    uint8_t i,j;

	for(i = 0; i < MAXLAYER; i++) 
	{
	   if(SYSPara.LayEnable[i] == 0) 
	   {
		   continue;
	   }
	   for(j = 0; j < MAXCHANNEL; j++) 
	   {	      
		  if(Channels[i][j].ChannelStat == (DRV_CHNSET_BIT|CHANNELOK)) 
		  {		  
			  if(Channels[i][j].GoodsPrice == 0) 
			  {
		          SetDevStatus(DEV_ERR_BIT_PRICESET);				 //�۸����ô���
		      }
		  }
	   }
	}
 }


/*���Flash״̬*/
void CheckFlashStat(void)
{
    if(SYSPara1.FlashStat > 0)
	{
	    SetDevStatus(DEV_ERR_BIT_FLASH);
	} 
}

/*���RTC״̬*/
void CheckRTCStat(void)
{
    if(SYSPara1.RTCStat > 0) {
	    //SetDevStatus(DEV_ERR_BIT_RTC);//120920 by cq DebugModify
	} 
}

/*
���״̬:ÿ��һ��ʱ�䣬�Լ��ж�һ�θ��豸�Ĺ������������ĸ������˻�������ʲôԭ���޷������������豸��Ϊ���ϵ��������������ٴι����ˣ�������
״̬����Ϊ����
���ж��Ƿ���Ϊ���ԭ���»�����Ҫ�������״̬����������Ϊ����  
*/
void CheckMoneyDevStat(void)
{
	//120703 by cq MDBCompatible

     //�Ƿ���Ҫ��������Ϊ����״̬
     
	//121106 by cq BillSingleWork
	//121113 by cq Cashless
	if(isBillSingleWork() || SYSPara.ReaderEnable)
	{
		ClrDevStatus(DEV_ERR_BIT_PARASET);
	}
	else
	{
	     if(((CashState.CoinState & COIN_DEV_NONE) && ((CashState.NoteState & (NOTE_DEV_NONE|NOTE_DEV_PERR)) || (CashState.ChangerState & CHANGER_NONE))) 
		     || ((CashState.CoinState & COIN_DEV_PERR) && ((CashState.NoteState & (NOTE_DEV_NONE|NOTE_DEV_PERR|NOTE_DEV_ER)) || (CashState.ChangerState != CHANGER_OK)))
			 || ((CashState.CoinState & COIN_DEV_ER) && (CashState.NoteState & NOTE_DEV_PERR))
			 || ((SYSPara.ChangeServer == 0) && (CashState.ChangerState & CHANGER_NONE))) 
		 {	 
		     SetDevStatus(DEV_ERR_BIT_PARASET);
		 } 
		 else 
		 {
		     ClrDevStatus(DEV_ERR_BIT_PARASET);
		 }
	}

	 //�Ƿ���Ҫ��Ӳ��������
	 //121106 by cq BillSingleWork
	 if(isBillSingleWork())
	 {
	     ClrDevStatus(DEV_ERR_BIT_COIN);
	 }
	 else if((CashState.CoinState & COIN_DEV_ER) 
	   && ((CashState.NoteState & (NOTE_DEV_NONE|NOTE_DEV_ER)) || (CashState.ChangerState != CHANGER_OK)))
	 {
		 SetDevStatus(DEV_ERR_BIT_COIN);
	 }
	 else 
	 {
	     ClrDevStatus(DEV_ERR_BIT_COIN);
	 }

	 //�Ƿ���Ҫ��ֽ��������
	 if((CashState.CoinState & COIN_DEV_NONE) && (CashState.NoteState & NOTE_DEV_ER)) 
	 {
	     SetDevStatus(DEV_ERR_BIT_NOTE);
	 }
	 else 
	 {
	     ClrDevStatus(DEV_ERR_BIT_NOTE);
	 } 

	 //�Ƿ���Ҫ��������Ӳ�Ҳ���
	 if((CashState.CoinState & COIN_DEV_NONE) && (CashState.ChangerState & CHANGER_LOW)) 
	 {
	     SetDevStatus(DEV_ERR_BIT_COINLOW);
	 }

	 //�Ƿ���Ҫ������������
	 if((CashState.CoinState & COIN_DEV_NONE) && (CashState.ChangerState & CHANGER_ER)) 
	 {
	     SetDevStatus(DEV_ERR_BIT_CHANGER);
	 }

	 if(SYSPara.ChangeServer == 0) 
	 {
	     if(CashState.ChangerState & CHANGER_LOW) 
		 {
		     SetDevStatus(DEV_ERR_BIT_COINLOW);
		 } else 
		 {
		     ClrDevStatus(DEV_ERR_BIT_COINLOW);
		 }
		 
		 if(CashState.ChangerState & CHANGER_ER)
		 {
		     SetDevStatus(DEV_ERR_BIT_CHANGER);
	 	 } 
		 else 
		 {
			 ClrDevStatus(DEV_ERR_BIT_CHANGER);
		 }
	 } 
	 else 
	 {
	     if((CashState.ChangerState & CHANGER_LOW) == 0) 
		 {
			 ClrDevStatus(DEV_ERR_BIT_COINLOW);
		 }
		 if((CashState.ChangerState & CHANGER_ER) == 0) 
		 {
			 ClrDevStatus(DEV_ERR_BIT_CHANGER);
		 }
	 }

	//121106 by cq BillSingleWork
	if(isBillSingleWork())
	{
		ClrDevStatus(DEV_ERR_BIT_PARASET);
		ClrDevStatus(DEV_ERR_BIT_NOTE);
		ClrDevStatus(DEV_ERR_BIT_COIN);
		ClrDevStatus(DEV_ERR_BIT_COINLOW);
		ClrDevStatus(DEV_ERR_BIT_CHANGER);
	}

	//Ӳ�������Բ���;by gzz 20130128
	if(SYSPara.CoinEnable == 0) 
	{
		//ȡ��Ӳ����������������
		ClrDevStatus(DEV_ERR_BIT_PARASET);
		ClrDevStatus(DEV_ERR_BIT_NOTE);
		ClrDevStatus(DEV_ERR_BIT_COIN);
		ClrDevStatus(DEV_ERR_BIT_COINLOW);
		ClrDevStatus(DEV_ERR_BIT_CHANGER);
		//������״̬��Ϊ����
		CashState.ChangerState = CHANGER_OK; 
	}
}


//�ܵ��豸���ģ��
void CheckVMCStat(void)
{  
	CheckMoneyDevStat();
	CheckFlashStat();
	CheckRTCStat();
}

/*��ȡ�����ֵ��ֽ���ݴ�ͨ�������������ֵ���ձҶ������ݴ�*/
void GetEscrowMinCh(void)
{
    uint8_t i;

	g_EscrowMinCh = 0;
	for(i = BILLCHMAX-1; i > 0; i--) 
	{
		if(SYSPara.BillValue[i] > 0) 
		{
			g_EscrowMinCh = i;
			break;
		}
	}

	if(SYSPara.NoteEscrow > 0) 
	{
		for(i = 0; i < BILLCHMAX; i++) 
		{
			if(SYSPara.NoteEscrowType[i] > 0) 
			{
				g_EscrowMinCh = i;
				break;
			}
		}
	}
}

/*��ȡֽ��ʹ��ͨ����Ϊ���õ�ʹ��λ*/
void GetNoteEnBit(void)
{
    uint8_t i;
	
	CashTypeEnBit.BillTypeEN = 0;

	//121106 by cq MDBCompatible
	CashTypeEnBit.BillTypeEN = 0xff;

	//��ȡֽ��ʹ��ͨ��
	for(i = 0; i < NOTE_GBA_NUM; i++)
	{			      
	   IncomeValue[NOTE_GBA_BASE+i] = SYSPara.BillValue[i];
	   if((SYSPara.BillValue[i] > 0) &&((SYSPara2.BillEnable>>i)&0x01))
	   {	   
	      CashTypeEnBit.BillTypeEN |= (1 << i);
		  //�������ò���ֽ��;by gzz 20121219
		  //if(!((SYSPara2.BillEnable>>i)&0x01)) 
		  //{	   
		  //    CashTypeEnBit.BillTypeEN &= ~(1 << i);
		  //}
	   }
	}	
	Trace("\r\n **+enable=%#02x",SYSPara2.BillEnable);
	Trace("\r\n **+BillTypeEN=%#02x",CashTypeEnBit.BillTypeEN);
	
	if(CashTypeEnBit.BillTypeEN == 0)	
	{
	    if(SYSPara.GBAEnable == HR_NOTE_EN) 
		{
		    SYSPara1.NoteStat |= HR_VALUE_BIT;
		}  
		else 
		{
		    SYSPara1.NoteStat |= MBV_VALUE_BIT;
		}  
	}

	#if GBAHRDEVICE == 0 && MBVDEVICE == 0
	if(SYSPara.GBAEnable > 0) 
	{
	    SYSPara.NoteStat = 0x8000;
	}
	#endif
}

/*��ȡӲ��ʹ��ͨ����Ϊ���õ�ʹ��λ*/
void GetCoinEnBit(void)
{
    uint8_t i;
	
	CashTypeEnBit.CoinTypeEN = 0;

	//121106 by cq MDBCompatible
	CashTypeEnBit.CoinTypeEN = 0xff; 
	
	//��ȡӲ��ʹ��ͨ��
	for(i = 0; i < COIN_MDB_NUM; i++)
	{			  
	   if(SYSPara.CoinsValue[i] > 0) 
	   {
	       CashTypeEnBit.CoinTypeEN |= (1 << i);
	   }
	}
	if(CashTypeEnBit.CoinTypeEN == 0)	
	{
	    SYSPara1.CoinsStat |= COIN_VALUE_BIT;
	}	
}

/*����Ƿ��ֶ���ֽ�����쳣*/
void CheckNotePara(void)
{
    if(((SYSPara.GBAEnable == HR_NOTE_EN) && (SYSPara1.NoteStat & HR_VALUE_BIT))
	   || ((SYSPara.GBAEnable == MDB_NOTE_EN) && (SYSPara1.NoteStat & MBV_VALUE_BIT)))
	{
		CashTypeEnBit.BillType = 0;
	}
}

/*����Ƿ��ֶ���Ӳ�����쳣*/
void CheckCoinPara(void)
{
	if(SYSPara1.CoinsStat & COIN_VALUE_BIT) 
	{
		CashTypeEnBit.CoinType = 0;
	} 
}

/*�����õ�ʹ��λ���뵱ǰ��ʹ��λ*/
void EnableMoneyType(void) 
{	
	if(CashState.ChangerState == CHANGER_OK) 
	{
	    CashTypeEnBit.BillType = CashTypeEnBit.BillTypeEN;
	}
	else 
	{
	    CashTypeEnBit.BillType = 0;
	}
	CashTypeEnBit.CoinType = CashTypeEnBit.CoinTypeEN;
}

/*����Ӳ��������*/
void DisCoinDevCmd(void)
{
     CashTypeEnBit.CoinType = 0;
     CoinAcceptor_Enable(CashTypeEnBit.CoinType);	                 //ʹ��
}

/*����ֽ��������*/
void DisNoteDevCmd(void)
{    
     CashTypeEnBit.BillType = 0;
     BillAcceptor_Enable(CashTypeEnBit.BillType);	                 //����
}

/*ʹ��Ӳ��������*/
void EnCoinDevCmd(void)
{
     if((CashState.CoinState == COIN_DEV_OK) || IsMaintainStat())
	 {
	 	//��������,ԭ����Ӧͨ�������󣬻�Ѷ�Ӧͨ�����ܡ����ڲ������;by gzz 20121025
	     //CashTypeEnBit.CoinType = CashTypeEnBit.CoinTypeEN & (~CashTypeEnBit.CoinFullBit);
	     CashTypeEnBit.CoinType = CashTypeEnBit.CoinTypeEN;
		 CoinAcceptor_Enable(CashTypeEnBit.CoinType);	                 //ʹ��
	 }
}

/*ʹ��ֽ��������*/
void EnNoteDevCmd(void)
{
	//121106 by cq BillSingleWork
     //if(((CashState.ChangerState == CHANGER_OK) && (BillAcceptor_Available() == TRUE)) || IsMaintainStat())
	if((((isBillSingleWork()) || (CashState.ChangerState == CHANGER_OK))&& (BillAcceptor_Available() == TRUE)) || IsMaintainStat())
	 {				     					 
	     if(BillAcceptor_ErrJudge(BillAcceptor_Enable(CashTypeEnBit.BillTypeEN)) != TRUE) 
		 {	             //ʹ��				     
			 CashTypeEnBit.BillType = CashTypeEnBit.BillTypeEN;
		 }
	 }
}
