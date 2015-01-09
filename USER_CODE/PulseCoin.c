/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           pulse.c
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        ������������
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
#include "..\config.h"
#include "global.h"
#include "PulseCoin.h"


#include "..\driver\lpc_types.h"//120401 by cq change structor



/*****************************************************************************
** Function name:		Coin_Accept
**
** Descriptions:		��ȡͶ��ֵ
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void Coin_Accept(void)
{
   uint8_t pvalue, pChannel, moneych;
   static uint8_t pLChannel, pSure;  
   
   pvalue = (~CoinP_Get()) & 0x3F;

   //Trace("\r\npvalue = %02x",pvalue);

   switch(pvalue) 
   {
      case 0x00:	  //��Ͷ��״̬
		  if(pSure == 1) 
		  {	     
			 pSure = 0;
			 moneych = pLChannel-1;
			 MsgBack.coinPlusback = SYSPara.CoinsValue[moneych] | 0x8000;
			 //money = SYSPara.CoinsValue[pChannel-1] | 0x8000;	//money���루16λ�������λ��1������Ϊ��ֵ
			 //money = COIN_PULSE_BASE | 0x8000;	//money���루16λ�������λ��1������Ϊͨ����
			 if(BeSaleStat()) 
			 {
				 TranData.IncomeCH[COIN_PULSE_BASE+moneych]++;
				 TranTotal.IncomeCH[COIN_PULSE_BASE+moneych]++;
				 TranTotal.Income += SYSPara.CoinsValue[moneych];
				 TranTotal.CoinsIncome += SYSPara.CoinsValue[moneych];

				 //���ڼ��Ƚ�����;by gzz 20121009
	   			 TranTotal.IncomeJidu += SYSPara.CoinsValue[moneych];				 
				 TranTotal.CoinsIncomeJidu += SYSPara.CoinsValue[moneych];
			 }
			 //OSMboxPost(g_KeyMsg,&MsgBack.moneyback);
			 //120621 by cq KeySlowly
			 //while( OSMboxPost(g_KeyMsg,&MsgBack.moneyback) != OS_NO_ERR)
		     {
		   		//OSTimeDly(OS_TICKS_PER_SEC / 100);
		     }			 
			 //OSMboxPost(g_MoneyMsg,&MsgBack.moneyback);
			 OSQPost(g_CoinPlusMsg,&MsgBack.coinPlusback);
		  }
		  if(pLChannel > 0) 
		  {
		      #if BEEPDEBUG
			  BEEPOFF();
			  #endif
		  }
		  pChannel = 0;
		  pLChannel = 0;
		  break;
	  
	  //120712 by cq CoinChannel
	  case 0x01:	   //Ӳ��ͨ��1
		  //pChannel = 1;
		  pChannel = 6;
		  break;

	  case 0x02:	   //Ӳ��ͨ��2
		  //pChannel = 2;
		  pChannel = 5;
		  break;

	  case 0x04:	   //Ӳ��ͨ��3
		  //pChannel = 3;
		  pChannel = 4;		  
		  break;

	  case 0x08:	   //Ӳ��ͨ��4
		  //pChannel = 4;		  
		  pChannel = 3;
		  break;
		  
	  case 0x10:	   //Ӳ��ͨ��5 //1Y -- 2
		  //pChannel = 5;
		  pChannel = 2;
		  break;

	  case 0x20:	   //Ӳ��ͨ��6 //5J -- 1
		  //pChannel = 6;
		  pChannel = 1;
		  break;

	  default:		   //����
		  pChannel = 0;
		  break;
   }

   if(pSure == 0) 
   {
      //���β���0����ȣ���ȷ��Ͷ�ҳɹ�
      if((pLChannel > 0) && (pLChannel == pChannel)) 
	  {
	     pSure = 1;				
		 #if BEEPDEBUG
		 BEEPON();
		 #endif
	  } 
	  else 
	  {
	     pLChannel = pChannel;
	  }
   }
}





/*��ʼ������Ӳ����*/
void Pulse_InitProc(void)
{
    uint8_t i;
	
	#if PULSEDEVICE	
		if((SYSPara1.CoinsStat & COIN_VALUE_BIT) == 0) 
		{
		    Pulse_Enable();						       //ʹ������Ӳ����
		}

		for(i = 0; i < COIN_PULSE_NUM; i++) 
		{
		   IncomeValue[COIN_PULSE_BASE+i] = SYSPara.CoinsValue[i];
		}
	#endif
}


/******************************************************************************
**                            End Of File
******************************************************************************/
