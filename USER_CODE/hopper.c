/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           hopper.c
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        Hopper��������
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
#include "evb.h"
#include "uart.h"
#include "hopper.h"

#include "Changer.h"//120401 by cq change structor

#if 0
#define IsChangeLowStat()		   (SYSPara.HopperStat[g_ChangeMinCh] & HOPPER_INSUFFICIENT_BIT)
#define IsChangeErrStat()		   (SYSPara.HopperStat[g_ChangeMinCh] & HOPPER_MALFUN_MASK)
#endif



uint8_t HopperSN[HOPPERCHMAX],HopperNo[HOPPERCHMAX];   //ͬ����ż�Hopper���
/*****************************************************************************
** Function name:	Hopper_Command	
**
** Descriptions:	hopper����	
**					
**
** parameters:		hoppercom:hopper����
** Returned value:	��ȷ��Ӧ����0�����򷵻ش�����
** 
*****************************************************************************/
static uint8_t Hopper_Command(EVBCommand hoppercom)
{
   uint8_t *pcombuf;
   uint8_t checksum, i, j;
   uint8_t  status, lenth;

   Uart2_ClrBuf();
   Uart2_SetEvbMode();
   Uart2_SetParity(PARITY_DIS);
   
   hoppercom.Head = 0xED;
   hoppercom.Lenth = 0x08;

   pcombuf = (uint8_t *)&hoppercom;

   checksum = 0;

   for(i = 0; i < hoppercom.Lenth - 1; i++) 
   {
	  checksum ^= pcombuf[i];
   }

   hoppercom.chksum = checksum;

   for(i = 0; i < 3; i++) 
   {
   
	   Trace("\r\nHPW-");
   
      Uart2_Write((uint8_t *)&hoppercom, hoppercom.Lenth);

	  OSTimeDly(OS_TICKS_PER_SEC);

      status = 0;
      checksum = 0;

	  Trace("\r\nHPL-");

	 //120821 by cq HoppeyUse	 
	 lenth = Uart2_Read(evbbuf,8);
	 /*
	  if(hoppercom.Com == HOPPER_PAYOUT) 
	  {
	     lenth = Uart2_Read(evbbuf,6);
	  } 
	  else 
	  {
	     lenth = Uart2_Read(evbbuf,8);
	  }
	  */
	  if(lenth > 0) 
	  {	  
		  if(evbbuf[0] != 0xFD) 
		  //if(evbbuf[0] != 0xEE) 
		 {
		 	Trace("\r\nERR_STX");
		    status = ERR_STX;
		 } 
		 else 
		 {
			for(j = 0; j < lenth - 1; j++) 
			{
		       checksum ^= evbbuf[j];
		    }

			if(checksum != evbbuf[j]) 
			{			
			 	Trace("\r\nERR_CHKSUM");
		       status = ERR_CHKSUM;
			}
			else 
			{			
			   break;
		    }
		 }
	  }
	  else 
	  {	  
		  Trace("\r\nERR_TIMEOUT");
         status = ERR_TIMEOUT;
	  }

	  OSTimeDly(OS_TICKS_PER_SEC / 10);
   }

   return status;
}

/*****************************************************************************
** Function name:	HopperPayout	
**
** Descriptions:	����	
**						
**
** parameters:		hopperch:hopperͨ���� amount:������	
** Returned value:	��ȷ��Ӧ����0�����򷵻ش�����	
**						
**						
** 
*****************************************************************************/
uint8_t HopperPayout(uint8_t hopperch, uint16_t amount)
{
   EVBCommand hoppercom;
   uint8_t  status;

   hoppercom.SN = HopperSN[hopperch];
   hoppercom.Com = HOPPER_PAYOUT;
   hoppercom.DevNo = HopperNo[hopperch];
   hoppercom.rsv1 = (uint8_t)amount;
   hoppercom.rsv2 = (uint8_t)(amount >> 8);

   status = Hopper_Command(hoppercom);

   return status;
}

/*****************************************************************************
** Function name:	HopperInquire	
**
** Descriptions:	��ѯ����״��	
**						
**
** parameters:		hopperch:hopperͨ���� timeout:�ȴ����ճ�ʱʱ��	
** Returned value:	��ȷ��Ӧ����0�����򷵻ش�����	
**						
**						
** 
*****************************************************************************/
uint8_t HopperInquire(uint8_t hopperch)
{
   EVBCommand hoppercom;
   uint8_t  status;

   hoppercom.SN = HopperSN[hopperch];
   hoppercom.Com = HOPPER_INQUIRE;
   hoppercom.DevNo = HopperNo[hopperch];
   hoppercom.rsv1 = 0;
   hoppercom.rsv2 = 0;

   status = Hopper_Command(hoppercom);

   return status;
}

/*****************************************************************************
** Function name:	Hopper_ErrJudge	
**
** Descriptions:	�ж�Hopper����״̬
**						
**
** parameters:		x:Hopper����ص�״ֵ̬
** Returned value:	������TRUE�����򷵻�FALSE	
** 
*****************************************************************************/
uint8_t Hopper_ErrJudge(uint8_t x)
{
  if(x > 0) {
     return TRUE;
  }
  return FALSE;
} 

/*****************************************************************************
** Function name:	Hopper_GetStatus	
**
** Descriptions:	�ж�Hopper����״̬
**						
**
** parameters:		��
** Returned value:	״̬��	
** 
*****************************************************************************/
uint8_t Hopper_GetStatus(void)
{  
  return evbbuf[3];
}


#if 0
/*���������״̬*/
void CheckChangerStat(void)
{
    if(SYSPara.ChangerEnable == HOPPER_CHANGER_EN) {		
	    if(IsChangeErrStat()) {
			CashState.ChangerState |= CHANGER_ER;	 
		} else {
		    CashState.ChangerState &= ~CHANGER_ER;	
		}
		if(IsChangeLowStat()) {
			CashState.ChangerState |= CHANGER_LOW;	 
		} else {
		    CashState.ChangerState &= ~CHANGER_LOW;			
		}
	}
}
#endif

#if 0
/*���Hopper״̬*/
void CheckHopperStat(void)
{
    uint8_t      pStatus,i,j;
	uint32_t	 ChangeBase;
	uint32_t	 temp;
	ChangerPara  ParaTemp;
	
	#if HOPPERDEVICE
	if(SYSPara.ChangerEnable == HOPPER_CHANGER_EN) {
		g_ChangeMinCh = 0;
		temp = 0;
		HopperNo[0] = HOPPERNO;
		HopperNo[1] = HOPPERNO2;
		HopperNo[2] = HOPPERNO3;
		for(i = 0; i < HOPPERCHMAX; i++) {	
			ChangeBase = SYSPara.ChangeValue[i];
			if(ChangeBase > 0) {
				if((temp == 0) || (ChangeBase < temp)) {
				    temp = ChangeBase;
					g_ChangeMinCh = i;							 //��С��ֵͨ��
				}
				HopperSN[i] = 0;
				pStatus = HopperPayout(i, 0)				
				if(Hopper_ErrJudge(pStatus) == TRUE) {	 //��Hopper���к�	
				   //����������		   
				   SYSPara.HopperStat[i] = HOPPER_COMMERR_BIT;
				} else {
				    pStatus = Hopper_GetStatus();			   
				    if(pStatus & HOPPER_ERR_MASK) {						    							
				       SYSPara.HopperStat[i] = pStatus;				   
				    } else {
					   SYSPara.HopperStat[i] = 0;
					}
				}										
			} else {
			    SYSPara.HopperStat[i] = HOPPER_DISABLE_BIT;
			}
			OutcomeValue[CHANGE_HOPPER_BASE+i] = SYSPara.ChangeValue[i];
				
			OSTimeDly(OS_TICKS_PER_SEC/10);	
		}
	} else {
		for(i = 0; i < HOPPERCHMAX; i++) {
		    SYSPara.HopperStat[i] = HOPPER_DISABLE_BIT;			 //����������
		}
	}
	#else
	for(i = 0; i < HOPPERCHMAX; i++) {
	    SYSPara.HopperStat[i] = HOPPER_DISABLE_BIT;
	}
	#endif 

	if(SYSPara.ChangerEnable == HOPPER_CHANGER_EN) {		
	    CheckChangerStat(); 
		
		for(i = 0; i < HOPPERCHMAX; i++) {		  //��HopperPara[]��ֵ
		    HopperPara[i].Channel = i;
			HopperPara[i].Value = SYSPara.ChangeValue[i];
		}
		
		for(i = 1; i < HOPPERCHMAX; i++) {		  //��HopperPara[]����
		    for(j = 0; j < i; j++) {
			    if(HopperPara[j].Value > HopperPara[i].Value) {
				    ParaTemp = HopperPara[j];
					HopperPara[j] = HopperPara[i];
					HopperPara[i] =	ParaTemp;
				}
			}
		}
	}    
}
#endif

/*
��ʼ������Hopper������ʼ��Hopper��SN���к�

���Hopper�����ã���������
���Hopper���ϣ������ù��ϣ�����Hopper��SN���к�

�������Hopper״̬���ǲ��㻹��������Ȼ����ұҵ�Hopper��������

*/
void Hopper_InitProc(void)
{
    uint8_t      pStatus,i,j;
	uint32_t	 ChangeBase;
	uint32_t	 temp;
	ChangerPara  ParaTemp;
	
	#if HOPPERDEVICE
	g_ChangeMinCh = 0;
	temp = 0;
	HopperNo[0] = HOPPERNO;
	HopperNo[1] = HOPPERNO2;
	HopperNo[2] = HOPPERNO3;
	for(i = 0; i < HOPPERCHMAX; i++) 
	{	
		ChangeBase = SYSPara.ChangeValue[i];
		if(ChangeBase > 0) 
		{
			if((temp == 0) || (ChangeBase < temp)) 
			{
			    temp = ChangeBase;
				g_ChangeMinCh = i;							 //��С��ֵͨ��				
			}
			HopperSN[i] = 0;
			pStatus = HopperPayout(i, 0);
			if(Hopper_ErrJudge(pStatus) == TRUE)
			{	 //��Hopper���к�	
			   //����������		   
			   Changer_SetCommErr(i);
			} 
			else 
			{
			    pStatus = Hopper_GetStatus();			   
			    Changer_UpDateStat(pStatus,i);
			}										
		} 
		else 
		{
		    Changer_SetDisStat(i);
		}
		OutcomeValue[CHANGE_HOPPER_BASE+i] = SYSPara.ChangeValue[i];
			
		OSTimeDly(OS_TICKS_PER_SEC/10);	
	}
	#else
	for(i = 0; i < HOPPERCHMAX; i++) 
	{
	    Changer_SetDisStat(i);
	}
	#endif 		
	
	for(i = 0; i < HOPPERCHMAX; i++) 		  //��HopperPara[]��ֵ
	{
	    HopperPara[i].Channel = i;
		HopperPara[i].Value = SYSPara.ChangeValue[i];
		//Trace("\r\n i=%d,channel=%d,value=%d,changevalue=%d",i,HopperPara[i].Channel,HopperPara[i].Value,SYSPara.ChangeValue[i]);
	}

	/*
	for(i = 1; i < HOPPERCHMAX; i++) 		  //��HopperPara[]����
	{
	    for(j = 0; j < i; j++) 
		{
		    if(HopperPara[j].Value > HopperPara[i].Value) 
			{
			    ParaTemp = HopperPara[j];
				HopperPara[j] = HopperPara[i];
				HopperPara[i] =	ParaTemp;
			}
		}
	}
	*/
	for(i = 0; i < HOPPERCHMAX; i++) 		  //��HopperPara[]��С��������,�������һ���Ļ�����hopper��ţ���С��������
	{
	    for(j = i + 1; j < HOPPERCHMAX; j++) 
		{
			//Trace("\r\n i=%d,channeli=%d,valuei=%d,j=%d,channelj=%d,valuej=%d",i,HopperPara[i].Channel, HopperPara[i].Value,j,HopperPara[j].Channel,HopperPara[j].Value);
		    if( (HopperPara[j].Value < HopperPara[i].Value)||((HopperPara[j].Value == HopperPara[i].Value)&&(HopperPara[j].Channel<HopperPara[i].Channel)) ) 
			{
			    ParaTemp = HopperPara[j];
				HopperPara[j] = HopperPara[i];
				HopperPara[i] =	ParaTemp;
				//Trace("\r\n +++i=%d,channeli=%d,valuei=%d,j=%d,channelj=%d,valuej=%d",i,HopperPara[i].Channel, HopperPara[i].Value,j,HopperPara[j].Channel,HopperPara[j].Value);
			}
		}
	}
	
	g_CoinMinValue = SYSPara.ChangeValue[g_ChangeMinCh];	

	//for(i = 0; i < HOPPERCHMAX; i++) 		  //��HopperPara[]��ֵ
	//{
	//    Trace("\r\n i=%d,channel=%d,value=%d",i,HopperPara[i].Channel,HopperPara[i].Value);
	//}
}

/*Hopper��������*/
/*���� MoneyOut:����ֵ*/
/*���� hopperch:Hopper��*/
void HopperPayoutCmd(uint32_t MoneyOut, uint8_t hopperch)
{
	  uint8_t   pStatus;
	  uint32_t 	ChangeBase;

	   Trace("\r\n start payout");
	  ChangeBase = SYSPara.ChangeValue[hopperch];
	  ChangeSN(HopperSN[hopperch]);				  				  
	  if(ChangeBase > 0) 
	  {
	      pStatus = HopperPayout(hopperch, MoneyOut/ChangeBase);	//����				  			  

		  //�ȴ�ʱ�������������ٶ�4pcs/sec����
		  //OSTimeDly(OS_TICKS_PER_SEC*(MoneyOut/ChangeBase/4+2));				  
		  OSTimeDly(OS_TICKS_PER_SEC);

		  
		  //120716 by cq HoppeyUse XX
		  TimerDly.TimeDly =	(((MoneyOut/ChangeBase) >> 2) + 30)	* 100;		  
		  
		  while(TimerDly.TimeDly > 0) 
		  {				     
		     pStatus = HopperInquire(hopperch);                    //��ȡ�������
			 if(Hopper_ErrJudge(pStatus) != TRUE) 
			 {
				if(!(Hopper_GetStatus() & HOPPER_BUSY_BIT)) 
				{
				   break;
				}
				break;
			 }
			 OSTimeDly(OS_TICKS_PER_SEC/10);
		  }
		  if(Hopper_ErrJudge(pStatus) != TRUE)
		  {
	         pStatus = Hopper_GetStatus();

			 SYSPara1.HopperStat[hopperch] &= ~HOPPER_COMMERR_BIT;
			 SYSPara1.HopperStat[hopperch] &= 0xFF00;						    							
			 SYSPara1.HopperStat[hopperch] |= pStatus;				 

			 MoneyOut = ((((uint16_t)evbbuf[6]) << 8) | evbbuf[5]) * ChangeBase;  //������
			 
			 if(BeSaleStat()) 
			 {
				 TranData.OutcomeCH[CHANGE_HOPPER_BASE+hopperch] += evbbuf[5];
				 TranTotal.OutcomeCH[CHANGE_HOPPER_BASE+hopperch] += evbbuf[5];	
				 TranTotal.TotalChange += MoneyOut;
			     //TranTotal.CoinsChange += MoneyOut;						 						 
				 TranTotal.CoinsChange[hopperch] += evbbuf[5];

				 //���ڼ��Ƚ�����;by gzz 20121009
				 TranTotal.TotalChangeJidu += MoneyOut;				 
				 TranTotal.CoinsChangeJidu[hopperch] += evbbuf[5];
				 Trace("\r\npayout hopperch=%d,0=%d,1=%d,2=%d",hopperch,TranTotal.CoinsChange[0],TranTotal.CoinsChange[1],TranTotal.CoinsChange[2]);
			 }
			 MsgBack.pBackMsg = MoneyOut;					 
		     //OSMboxPost(g_CommBackMsg,&MoneyOut);
			 OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);						 					 				     			    					 
		  }  
		  else 
		  {					     						 
			 SYSPara1.HopperStat[hopperch] |= HOPPER_COMMERR_BIT;
		  }	
	  }				  			  

	  if(hopperch == g_ChangeMinCh) 
	  {
	      //CheckChangerStat();
	  }
}

/*****************************************************************************
** Function name:	Hoppern_Payout	
**
** Descriptions:	ָ��Hopper������������ݸ���
**						
**
** parameters:		pNum:����ö�� hopperch:ָ����Hopper���
** Returned value:	����ʵ�����������	
** 
*****************************************************************************/
uint8_t Hoppern_Payout(uint8_t pNum, uint8_t hopperch)
{
	  uint8_t   pStatus;
	  uint8_t  num = 0;

	  if(( ((SYSPara1.HopperStat[hopperch] & HOPPER_ERR_MASK) == 0) && (pNum > 0) )   //�������
	  //	 || (((SYSPara1.HopperStat[hopperch] & HOPPER_MALFUN_MASK) == 0) && (hopperch == g_ChangeMinCh) && (pNum == 0)))
	                                                                // ����һ����������ʱ����Ƿ�ӱ���
	  //|| (((SYSPara1.HopperStat[hopperch] & HOPPER_MALFUN_MASK) == 0) && (pNum == 0)))
	  || ((SYSPara1.HopperStat[hopperch] & HOPPER_INSUFFICIENT_BIT) && (pNum == 0)))
	  {
	  	  Trace("\r\n Hoppern:pNum=%d,hopperch=%d,stat=%#x",pNum,hopperch,SYSPara1.HopperStat[hopperch]);	
		  ChangeSN(HopperSN[hopperch]);				  				  
	      pStatus = HopperPayout(hopperch, pNum);	//����				  			  
					  
		  OSTimeDly(OS_TICKS_PER_SEC);
		  TimerDly.TimeDly =	((pNum >> 2) + 30)	* 100;
		  while(TimerDly.TimeDly > 0) 
		  {				     
		     pStatus = HopperInquire(hopperch);               //��ȡ�������
			 if(Hopper_ErrJudge(pStatus) != TRUE) 
			 {
				if(!(Hopper_GetStatus() & HOPPER_BUSY_BIT)) 
				{
				   break;
				}
				break;
			 }
			 OSTimeDly(OS_TICKS_PER_SEC/10);
		  }
		  if(Hopper_ErrJudge(pStatus) != TRUE) 
		  {
			  //120830 by cq HopperOutAdd
			  if(BeSaleStat()) 
			  {
				  TranTotal.CoinsChange[hopperch] += evbbuf[5];		

				  //���ڼ��Ƚ�����;by gzz 20121009
				  TranTotal.CoinsChangeJidu[hopperch] += evbbuf[5];	
				  Trace("\r\nTranTotal.CoinsChange[%x] = %x",hopperch,evbbuf[5]);
			  }
		  
	         pStatus = Hopper_GetStatus();
			 Changer_UpDateStat(pStatus,hopperch);				 
			 num = (((uint16_t)evbbuf[6]) << 8) | evbbuf[5];   //������	
			 Changer_UpDatepBuf(num,hopperch);				 					 				     			    					 
		  } 
		  else 
		  {					     						 
			 Changer_SetCommErr(hopperch);
		  }	
	  }				  			  

	  return num;
}

/*****************************************************************************
** Function name:	Hopper_PayoutProc	
**
** Descriptions:	Hopper��������
**						
**
** parameters:		moneyout:����ֵ
** Returned value:	��	
** 
*****************************************************************************/
void Hopper_PayoutProc(uint32_t moneyout)
{
	uint8_t   i,j,pNum,bNum;
	uint32_t  ChangeBase;
	uint32_t  temp;
	
	temp = moneyout;
	#if HOPPERDEVICE  //����	
	//for(i = 0; i < HOPPERCHMAX; i++) 		  //��HopperPara[]��ֵ
	//{
	//    Trace("\r\n i=%d,channel=%d,value=%d",i,HopperPara[i].Channel,HopperPara[i].Value);
	//}
	
	for(i = HOPPERCHMAX; i > 0; i--) 
	{           
		ChangeBase = HopperPara[i-1].Value;
		j = HopperPara[i-1].Channel;
		//Trace("\r\n i=%d,Channel=%d,value=%d,min=%d",i,j,ChangeBase,g_ChangeMinCh);
		if(ChangeBase > 0) 
		{
			pNum = temp / ChangeBase;
			Trace("\r\n out:i=%d,Channel=%d,value=%d,min=%d",i,j,ChangeBase,g_ChangeMinCh);
			//if((pNum > 0) || (j == g_ChangeMinCh)) 
			{
				bNum = Hoppern_Payout(pNum,j);
				if(bNum > pNum)	
				{
					bNum = pNum;
				}			
				temp -= ChangeBase * bNum;  	 			 
			}				    
		}
		OSTimeDly(OS_TICKS_PER_SEC/10);
	}				 
	#endif	
}

