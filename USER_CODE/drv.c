/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           drv.c
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        ����������������
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
#define EVBDEF
#include "..\driver\LPC17xx.h"
#include "..\driver\lpc_types.h"
#include "..\config.h"
#include "global.h"
#include "uart.h"
#include "evb.h"
#include "drv.h"
#include "VMC_PC.h"


uint8_t DRVSN;	   //ͬ�����
/*****************************************************************************
** Function name:	DRV_Command	
**
** Descriptions:	������������	
**					
**
** parameters:		drvcom:������������
** Returned value:	��ȷ��Ӧ����0�����򷵻ش�����
** 
*****************************************************************************/
static uint8_t DRV_Command(EVBCommand drvcom)
{
   uint8_t *pcombuf;
   uint8_t checksum, i, j;
   uint8_t  status, lenth;

   Uart2_ClrBuf();
   Uart2_SetEvbMode();
   Uart2_SetParity(PARITY_DIS);
   
   #if DRV_TYPE == DRV_12
   		drvcom.Head = 0xED;
   #elif DRV_TYPE == DRV_64
   		drvcom.Head = 0xED;
   #endif
   
   drvcom.Lenth = 0x08;
   pcombuf = (uint8_t *)&drvcom;

   checksum = 0;
   for(i = 0; i < drvcom.Lenth - 1; i++) 
   {
	  checksum ^= pcombuf[i];
   }

   drvcom.chksum = checksum;
   
   for(i = 0; i < 3; i++) 
   {
      Uart2_Write((uint8_t *)&drvcom, drvcom.Lenth);

	  //OSTimeDly(OS_TICKS_PER_SEC * 2);
	  OSTimeDly(OS_TICKS_PER_SEC / 2);

	  lenth = Uart2_Read(evbbuf,8);

      status = 0;
      checksum = 0;

	  if(lenth > 0) 
	  {		 		 
		 #if DRV_TYPE == DRV_12
		 	if(evbbuf[0] != 0xEF) 
			{
		 #elif DRV_TYPE == DRV_64
		 	if(evbbuf[0] != 0xEE) 
			{
		 #endif
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
         status = ERR_TIMEOUT;
      }

	  OSTimeDly(OS_TICKS_PER_SEC / 10);
   }

   return status;
}

/*****************************************************************************
** Function name:	DRV_Dispense	
**
** Descriptions:	��������	
**					
**
** parameters:		DRVNo:���������  chksign:������⣨1:�� 0:�أ�
** Returned value:	��ȷ��Ӧ����0�����򷵻ش�����
** 
*****************************************************************************/
uint8_t DRV_Dispense(uint8_t DRVNo, uint8_t chksign)
{
   EVBCommand drvcom;
   uint8_t  status,checksum,j,lenth,i;

   drvcom.SN = DRVSN;
   drvcom.Com = DRV_DISPENSE;
   drvcom.DevNo = DRVNo;
   drvcom.rsv1 = 0;
      
   #if DRV_TYPE == DRV_12
	   drvcom.rsv2 = chksign;
	   /*if(Maintain == 1) {
	       drvcom.rsv2 = GOODSCHK_OPEN;
	   }*/
   #elif DRV_TYPE == DRV_64
	   if(chksign > 0) 
	   {
	      drvcom.rsv2 = 1;
	   } 
	   else 
	   {
	      drvcom.rsv2 = 0;
	   }
   #endif

   status = DRV_Command(drvcom);

   #if DRV_TYPE == DRV_64
	   if(Drv_ErrJudge(status) != TRUE) 
	   {
			checksum = 0;
			
			//120824 by cq ChannelTime
			//OSTimeDly(OS_TICKS_PER_SEC*4);
			//OSTimeDly(OS_TICKS_PER_SEC*6);//4 
			OSTimeDly(OS_TICKS_PER_SEC*7);//4 

			memset(evbbuf,0,sizeof(evbbuf));
			for(lenth = 0, i = 0; i < 20 && lenth == 0; i++)
			{
				lenth = Uart2_Read(evbbuf,8);
				OSTimeDly(OS_TICKS_PER_SEC);
				Trace("\r\n RETRYGOOD");
			}
			/*
			//memset(evbbuf,0,sizeof(evbbuf));
			//sysVPMission.drvOutTimer = 600;
			//while( (evbbuf[0]==0)&&(sysVPMission.drvOutTimer > 0) )	
			while( (evbbuf[0]==0)||(lenth==0) )
			{
				lenth = Uart2_Read(evbbuf,8);
				OSTimeDly(OS_TICKS_PER_SEC / 10);//4 
			}
			*/
			Trace("\r\n Dispense:len=%d,evb=%#x,%#x,%#x,%#x,%#x,%#x,%#x,%#x",lenth,evbbuf[0],evbbuf[1],evbbuf[2],evbbuf[3],evbbuf[4],evbbuf[5],evbbuf[6],evbbuf[7]);
			
			if(lenth > 0) 
			{		 		 
				if(evbbuf[0] != 0xEE) 
				{
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
					   status = ERR_CHKSUM;
					}
					else 
					{
					   status = 0;
					}
				}	 
			} 
			else 
			{
			    status = ERR_TIMEOUT;
			}
	   }
   #endif

   return status;
}



/*****************************************************************************
** Function name:	DRV_Inquire	
**
** Descriptions:	��ѯ����״��	
**					
**
** parameters:		DRVNo:���������  chksign:������⣨1:�� 0:�أ�
** Returned value:	��ȷ��Ӧ����0�����򷵻ش�����
** 
*****************************************************************************/
uint8_t DRV_Inquire(uint8_t DRVNo, uint8_t chksign)
{
   EVBCommand drvcom;
   uint8_t  status;
      
   drvcom.SN = DRVSN;
   drvcom.Com = DRV_INQUIRE;
   drvcom.DevNo = DRVNo;
   drvcom.rsv1 = 0;

   #if DRV_TYPE == DRV_12
   		drvcom.rsv2 = 0;
   #elif DRV_TYPE == DRV_64
	   if(chksign > 0) 
	   {
	      drvcom.rsv2 = 1;
	   }
	   else 
	   {
	      drvcom.rsv2 = 0;
	   }
   #endif

   status = DRV_Command(drvcom);

   return status;
}

#if DRV_TYPE == DRV_12
/*****************************************************************************
** Function name:	DRV_GetStatus	
**
** Descriptions:	��ȡͨ�����޻�״̬	
**					
**
** parameters:		DRVNo:���������  chksign:������⣨1:�� 0:�أ�
** Returned value:	��ȷ��Ӧ����0�����򷵻ش�����
** 
*****************************************************************************/
uint8_t DRV_GetStatus(uint8_t DRVNo, uint8_t chksign)
{
   EVBCommand drvcom;
   uint8_t  status;

   drvcom.SN = DRVSN;
   drvcom.Com = DRV_STATUSCHK;
   drvcom.DevNo = DRVNo;
   drvcom.rsv1 = 0;
   drvcom.rsv2 = 0;

   status = DRV_Command(drvcom);

   return status;
}
#endif

/*****************************************************************************
** Function name:	DRV_ClearSN	
**
** Descriptions:	��SN��	
**					
**
** parameters:		DRVNo:���������  chksign:������⣨1:�� 0:�أ�
** Returned value:	��ȷ��Ӧ����0�����򷵻ش�����
** 
*****************************************************************************/
uint8_t DRV_ClearSN(uint8_t DRVNo, uint8_t chksign)
{
   EVBCommand drvcom;
   uint8_t   status;

   drvcom.SN = 0;

   #if DRV_TYPE == DRV_12
   		drvcom.Com = DRV_CLEARSN;
   #elif DRV_TYPE == DRV_64
   		drvcom.Com = DRV64_CLEARSN;
   #endif

   drvcom.DevNo = DRVNo;
   drvcom.rsv1 = 0;

   #if DRV_TYPE == DRV_12
   		drvcom.rsv2 = 0;
   #elif DRV_TYPE == DRV_64
	   if(chksign > 0) 
	   {
	      drvcom.rsv2 = 1;
	   }
	   else 
	   {
	      drvcom.rsv2 = 0;
	   }
   #endif

   status = DRV_Command(drvcom);

   return status;
}

#if DRV_TYPE == DRV_64
/*****************************************************************************
** Function name:	DRV_Test	
**
** Descriptions:	��������	
**					
**
** parameters:		DRVNo:���������  chksign:������⣨1:�� 0:�أ�
** Returned value:	��ȷ��Ӧ����0�����򷵻ش�����
** 
*****************************************************************************/
uint8_t DRV_Test(uint8_t DRVNo, uint8_t chksign)
{
   EVBCommand drvcom;
   uint8_t  status;

   drvcom.SN = 0;
   drvcom.Com = DRV64_TEST;
   drvcom.DevNo = DRVNo;
   drvcom.rsv1 = 0;

   if(chksign > 0) 
   {
      drvcom.rsv2 = 1;
   }
   else 
   {
      drvcom.rsv2 = 0;
   }

   status = DRV_Command(drvcom);

   return status;
}

#endif

/*****************************************************************************
** Function name:	GetDrvStatus	
**
** Descriptions:	�õ���ǰ������������������ֵ	
**					
**
** parameters:		
** Returned value:	
** 
*****************************************************************************/
uint8_t GetDrvStatus(void)
{	 
#if DRV_TYPE == DRV_12
		return evbbuf[1];
#elif DRV_TYPE == DRV_64
		//return evbbuf[5];
		if(SYSPara.GOCCtr == 0)//120920 by cq DebugModify	 
		{
			return evbbuf[5]&0x7f;
		}
		else
		{
			return evbbuf[5];
		}
#endif
}



/*****************************************************************************
** Function name:	Drv_ErrJudge	
**
** Descriptions:	�ж�Drv����״̬
**						
**
** parameters:		x:Drv����ص�״ֵ̬
** Returned value:	������TRUE�����򷵻�FALSE	
** 
*****************************************************************************/
uint8_t Drv_ErrJudge(uint8_t x)
{
  if(x > 0) 
  {
     return TRUE;
  }
  return FALSE;
} 

/*****************************************************************************
** Function name:	DRV_ChnChk	
**
** Descriptions:	��ȡʵ�ʻ�����ź��к�	
**					
**
** parameters:	channelno:�ͻ�����Ļ�����	channelx:ʵ�ʲ�� channely:ʵ���к�
** Returned value:	������ȷ����TRUE�����򷵻�FALSE
** 
*****************************************************************************/
uint8_t DRV_ChnChk(uint8_t channelno,uint8_t *channelx, uint8_t *channely)
{
    #if CHNINPUT_MODE == TWO_Bit_MODE
		uint8_t x,y;
		//uint8_t i;

		x = channelno/10;
		y = channelno%10;

		//121105 by cq TenChannels
		if((x >= 1) && (y == 0)) 
			y += 10;
		
		if((x >= 1) && (x <= MAXLAYER) && (y >= 1) && (y <= MAXCHANNEL)) 
		{
		   x -= 1;
		   y -= 1;

		   x = ChnMapPara.LAYTODRV[x];
		   if(x > 0) 
		   {
		      x -= 1;
			  y = ChnMapPara.CHTODRV[x][y];
		      if (y > 0) 
			  {	     		  
			     y -= 1;
			     *channelx = x;
		         *channely = y;
			     return TRUE;		  
		      } 
			  else 
			  {
		         return FALSE;
		      }
		   }
		   else 
		   {
		      return FALSE;
		   }
		/*   for(i = 0; (i<=x)&&(i<MAXLAYER); i++) {
		      if(DrvSet[i] == 0) {
			     x++;
			  }
		   }
		   if(x < CHN_ROW) {
		      for(i = 0; (i<=y)&&(i<MAXCHANNEL); i++) {
		         if(!(DrvSet[x] & (1 << i))) {
			        y++;
			     }
		      }
		      if(y < CHN_COL) {
		         *channelx = x;
		         *channely = y;
		         return 0;
		      } else {
		         return 1;
		      }
		   } else {
		      return 1;
		   } */
		}
		else 
		{
		   return FALSE;
		}
	#elif CHNINPUT_MODE == ONE_Bit_MODE
	if((channelno > 0) && (channelno <= MAXCHANNEL)) 
	{
	  // *channelx = channelno/8;
	  // *channelx = channelno%8;
	   *channelx = (channelno-1)/8;
	   *channelx = (channelno-1)%8;
	   return TRUE;
	} 
	else 
	{
	   return FALSE;
	}
	#endif
}









/*������л���״̬*/
/*���� mode 0:������л��� 1:����⵽���û������˳�*/
/*����ֵ ����� 0:���� �������쳣*/
uint8_t ChannelCheck(void)	 
{
    uint8_t status,i,j;

	status =  DRV_HARDERR_BIT|DRV_NOGOODS_BIT|DRV_ALLCHNDIS_BIT;
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
		      status &= ~DRV_HARDERR_BIT;		  
			  if(Channels[i][j].GoodsNum > 0) 
			  {
		          status &= ~DRV_NOGOODS_BIT;
				  status &= ~DRV_ALLCHNDIS_BIT;

				  return status;
		      }	
			  else 
			  {
			      Channels[i][j].ChannelStat = (DRV_CHNSET_BIT|CHANNELOVER);
			  }		  							
		  }
		  if(Channels[i][j].ChannelStat != (DRV_CHNSET_BIT|CHANNELOVER)) 
		  {
			  status &= ~DRV_NOGOODS_BIT;				 
		  }
		  if(Channels[i][j].ChannelStat != (DRV_CHNSET_BIT|CHANNELHARDERR)) 
		  {
			  status &= ~DRV_HARDERR_BIT;			 	 
		  }
	   }
	}
	return status;
}

/*�������л���״̬���ϣ��޻������ǲ�����*/
void CheckChannelStat(void)
{
    uint8_t DrvStat;
	
	DrvStat = ChannelCheck();

	if(DrvStat > 0) 
	{
	   if(DrvStat & DRV_HARDERR_BIT) 
	   {
	       SetDevStatus(DEV_ERR_BIT_CHNALL);						 //����ȫ����
	   } else if(DrvStat & DRV_NOGOODS_BIT) 
	   {
	       SetDevStatus(DEV_ERR_BIT_CHNOUT);						 //����ȫ�޻�
	   } 
	   else 
	   {
	       SetDevStatus(DEV_ERR_BIT_CHNDIST);				         //�޿��û���
	   }
	}
}

/*��������ͨѶ״̬���������ģ��״̬*/
void CheckDriverStat(void)
{   
	#if DRVDEVICE
		uint8_t pStatus;

		DRVSN = 0;
		#if DRV_TYPE == DRV_12
			DRV_ClearSN(1,GOODSCHK_CLOSE);
			OSTimeDly(OS_TICKS_PER_SEC / 10);
			pStatus	= DRV_GetStatus(1,GOODSCHK_CLOSE);
		#elif DRV_TYPE == DRV_64
			pStatus = DRV_ClearSN(0,SYSPara.GOCCtr);
		#endif

		if(Drv_ErrJudge(pStatus) == TRUE) 
		{		     //��������	
		     //���������������
		     SetDevStatus(DEV_ERR_BIT_DRVCOMM);
		} 
		else 
		{
			 pStatus = GetDrvStatus();

			 #if DRV_TYPE == DRV_64
				  //121108 by cq GOCErrorSevice
				 //if((SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT)) 
				  //if((SYSPara.GOCErrorSevice == 0) && (SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT)) 
				 if(isGOCErrorSevice() && SYSPara.GOCErrorSevice == 1)
				 {
					 SYSPara1.GOCStat = 0;
					 ClrDevStatus(DEV_ERR_BIT_GOODSCHK);
				 }
				 else if((SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT)) 
				 {
				    SYSPara1.GOCStat = 1;
					SetDevStatus(DEV_ERR_BIT_GOODSCHK);
				 } 
				 else 
				 {
				    SYSPara1.GOCStat = 0;
					ClrDevStatus(DEV_ERR_BIT_GOODSCHK);
				 }
			 #endif
		}

		CheckChannelStat();
				
		if(SYSPara.GOCCtr > 0) 
		{
			OSTimeDly(OS_TICKS_PER_SEC / 10);
			pStatus = DRV_ClearSN(0,GOODSCHK_CLOSE);
		}			
	#else
		uint8_t i,j;

		SetDevStatus(DEV_ERR_BIT_DRVCOMM);
		
		for(i = 0; i < MAXLAYER; i++) 
		{
		   for(j = 0; j < MAXCHANNEL; j++) 
		   {
		      Channels[i][j].ChannelStat &= DRV_CHNSET_BIT;
			  Channels[i][j].ChannelStat |= CHANNELDISABLE;
		   }  
		}	 		
	#endif 
}

/*������ѯ����*/
/*���� channel:�ͻ�����Ļ������*/
void DrvCheckCommand(uint8_t channel)
{
      uint8_t     pStatus;
	  uint8_t     ChannelNum,ChannelX,ChannelY;
	  
	  if(DRV_ChnChk(channel,&ChannelX,&ChannelY) == TRUE) 
	  {
		  //ChannelNum = GetChannelNo(ChannelX,ChannelY);
		  //�Ƿ�ʹ��ʮ�����Ļ���;by gzz 20130226	
		  if(SYSPara2.TenColumn==1)
		  {
		  	ChannelNum = GetChannelNo10(ChannelX,ChannelY);
		  }
		  else
		  {
		  	ChannelNum = GetChannelNo8(ChannelX,ChannelY);
		  }
		  
		  #if DRV_TYPE == DRV_64
			  //DRVSN = 0;
			  pStatus = DRV_Inquire(ChannelNum,SYSPara.GOCCtr);
			  if(Drv_ErrJudge(pStatus) != TRUE) 
			  {
			      ClrDevStatus(DEV_ERR_BIT_DRVCOMM);
				  pStatus = GetDrvStatus();
				  
				   //121108 by cq GOCErrorSevice
				  //if((SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT)) 
				   //if((SYSPara.GOCErrorSevice == 0) && (SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT)) 
				   if(isGOCErrorSevice() && SYSPara.GOCErrorSevice == 1)
				   {
					   SYSPara1.GOCStat = 0;
					   ClrDevStatus(DEV_ERR_BIT_GOODSCHK);
				   }
				   else if((SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT)) 
				  {
				     SYSPara1.GOCStat = 1;
				 	 SetDevStatus(DEV_ERR_BIT_GOODSCHK);
				  } 
				  else 
				  {
				     SYSPara1.GOCStat = 0;
					 ClrDevStatus(DEV_ERR_BIT_GOODSCHK);
				  }
				  MsgBack.pBackMsg = pStatus;					 
				  OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);

				  if(SYSPara.GOCCtr > 0) 
				  {
				      OSTimeDly(OS_TICKS_PER_SEC / 10);
					  pStatus = DRV_Inquire(ChannelNum,GOODSCHK_CLOSE);
				  }
		      }	
			  else 
			  {
			      SetDevStatus(DEV_ERR_BIT_DRVCOMM);
			  }
		  #elif DRV_TYPE == DRV_12
			  pStatus = DRV_GetStatus(ChannelNum,GOODSCHK_CLOSE);

			  if(Drv_ErrJudge(pStatus) != TRUE) 
			  {
		         ClrDevStatus(DEV_ERR_BIT_DRVCOMM);
				 pStatus = GetDrvStatus();

				 if(pStatus == DRV_NOGOOGS) 
				 {
					 //121108 by cq DontReduceNum
					 if(!isDontReduceNum())
					 {
						 Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
						 Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOVER;
						 Channels[ChannelX][ChannelY].GoodsNum = 0;
					 }

					CheckChannelStat();
				 }
				 MsgBack.pBackMsg = pStatus;					 
				 OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);
			  } 
			  else 
			  {
				 SetDevStatus(DEV_ERR_BIT_DRVCOMM);		         //ͨѶ����
			  }
		  #endif
	  }
}

/*��������*/
/*���� channel:�ͻ�������߼��������*/
void DrvOutCommand(uint8_t channel)
{
	  uint8_t	  pStatus;
	  uint8_t	  ChannelNum,ChannelX,ChannelY;
	  uint32_t	  PcValue = 0;
	  uint8_t	  Pcchannel,PcChannelX,PcChannelY,x,y;
	  uint8_t	  i=0;
		
	  if(DRV_ChnChk(channel,&ChannelX,&ChannelY) == TRUE) 
	  {
		  if(BeSaleStat() && ( SYSPara.PCEnable == 1 ) &&(sysVPMission.vendCmd == 0)) 
		  {
			 //�õ���pc�ϱ��Ļ������
			 for(x = 0; x<MAXLAYER;x++)   
			 {			
				for(y=0; y<MAXCHANNEL;y++) 
				{
					Pcchannel = x*10+y+11;
					if(DRV_ChnChk(Pcchannel,&PcChannelX,&PcChannelY) == TRUE) 
					{
						if(Pcchannel != channel)
						{
							i++;
						}
						else
						{
							sysVPMission.vendColumn = i;	
						}
					}				
				}
			 }
			 
			 if(SYSPara.Decimal==1)
			 {
				PcValue = g_Amount * 10;
			 }
			 else if(SYSPara.Decimal==2)
			 {
				PcValue = g_Amount; 
			 }				 
			 if(VPMission_Vendout_REQ(sysVPMission.vendColumn, PcValue))
			 {
				return;
			 }
		  }

		  //ChannelNum = GetChannelNo(ChannelX,ChannelY);	
		  //�Ƿ�ʹ��ʮ�����Ļ���;by gzz 20130226	
		  if(SYSPara2.TenColumn==1)
		  {
		  	ChannelNum = GetChannelNo10(ChannelX,ChannelY);
		  }
		  else
		  {
		  	ChannelNum = GetChannelNo8(ChannelX,ChannelY);
		  }
		  //Trace("\r\n +2:%d,%d,%d,%d",channel,ChannelX,ChannelY,ChannelNum);
		  ChangeSN(DRVSN);
		 
	  #if DRV_TYPE == DRV_12
			  pStatus = DRV_Dispense(ChannelNum, GOODSCHK_CLOSE);
	  #elif DRV_TYPE == DRV_64
			  pStatus = DRV_Dispense(ChannelNum, SYSPara.GOCCtr);
			  /*OSTimeDly(OS_TICKS_PER_SEC);
			  TimerDly.TimeDly = 1000;
			  while(TimerDly.TimeDly > 0) { 					 //��ѯ�������
				 pStatus = DRV_Inquire(0);
				 if(Drv_ErrJudge(pStatus) != TRUE) {
					if((evbbuf[2] == DRVSN) && (evbbuf[3] == DRV_INQUIRE)) {
					   break;
					}
				 }
				 OSTimeDly(OS_TICKS_PER_SEC/10); 
			  }*/
	  #endif
		  //Trace("\r\n Drvout:status=%#x",pStatus);

		  if(Drv_ErrJudge(pStatus) != TRUE) 
		  {
			 if(sysVPMission.vendCmd == 0)			 
			 {
				sysVPMission.vendType = 0;
			 }
			 
			 pStatus = GetDrvStatus();												   
			 //����жϷ���״̬ 
			 Trace("\r\n ***outGood=%#x",pStatus);


			/*********GOC�򿪵������********************/
			if(SYSPara.GOCCtr > 0)
			{				 
				 //1.�ж�GOC�Ƿ����bit7:
				 if(pStatus & DRV_GOCERR_BIT) 
				 {
				 	Trace("\r\n ++GOCErr");
				 	//GOC����->��Ǯ��Ȼ��goc������
					SYSPara1.GOCStat = 1;
					SetDevStatus(DEV_ERR_BIT_GOODSCHK);

					if(BeSaleStat())
					{
						//�м�⵽->��Ǯ  
						/*************************************************************************/ 
						//����ͨ����¼							  
						 if(SYSPara2.AutoColumn==0)
						 {
							 //����ͨ����¼ 						  
							 if(Channels[ChannelX][ChannelY].GoodsNum > 0) 
							 {
								 //121108 by cq DontReduceNum
								 if(!isDontReduceNum())
									 Channels[ChannelX][ChannelY].GoodsNum--;
							 }
						 }
						 if(Channels[ChannelX][ChannelY].GoodsNum == 0) 
						 {
							if(!isDontReduceNum())
							{
								//Trace("\r\n 2");
								Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
								Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOVER;
								//Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOK;
							}
						 }
						/*************************************************************************/ 

						/*************************************************************************/
						//���½��׼�¼	 
						 TranData.Money +=	Channels[ChannelX][ChannelY].GoodsPrice;
						 (TranData.Goods[ChannelX][ChannelY])++;
						  // TranData[CurrentPage].  Time =
						 TranTotal.Money +=  Channels[ChannelX][ChannelY].GoodsPrice;
						 (TranTotal.Goods[ChannelX][ChannelY])++;
						 TranTotal.TotalTrans +=  Channels[ChannelX][ChannelY].GoodsPrice;

						 //���ڼ��Ƚ�����;by gzz 20121009
						 TranTotal.TotalTransJidu +=  Channels[ChannelX][ChannelY].GoodsPrice;
						/*************************************************************************/
						
						//���pc�п������ϱ�pc
						if( SYSPara.PCEnable == 1 )
						{
							sysVPMission.vendSta = 2; 
						}
					}
				 } 
				 else 
				 {
				 	//GOC��Ϊ����
					SYSPara1.GOCStat = 0;
					ClrDevStatus(DEV_ERR_BIT_GOODSCHK);

					//2.���ж�GOC�Ƿ��⵽bit5				
                    if((pStatus & GOODS_NOTPASS_BIT) == 0) 
                    {
                    	Trace("\r\n ++GOCOK");
                    	Channels[ChannelX][ChannelY].ChannelStat	&= DRV_CHNSET_BIT;
						Channels[ChannelX][ChannelY].ChannelStat 	|= CHANNELOK;	
						//2.���ж�GOC�Ƿ��⵽bit5�������ڽ���״̬:					
	                    if(BeSaleStat() && ((pStatus & GOODS_NOTPASS_BIT) == 0)) 
					   	{
								//�м�⵽->��Ǯ  
								/*************************************************************************/ 
								//����ͨ����¼							  
								 if(SYSPara2.AutoColumn==0)
				 				 {
									 //����ͨ����¼							  
									 if(Channels[ChannelX][ChannelY].GoodsNum > 0) 
									 {
										 //121108 by cq DontReduceNum
										 if(!isDontReduceNum())
											 Channels[ChannelX][ChannelY].GoodsNum--;
									 }
				 				 }
								 if(Channels[ChannelX][ChannelY].GoodsNum == 0) 
								 {
								 	if(!isDontReduceNum())
								 	{
										//Trace("\r\n 2");
										Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
										Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOVER;
										//Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOK;
								 	}
								 }
								/*************************************************************************/ 

								/*************************************************************************/
								//���½��׼�¼	 
								 TranData.Money +=	Channels[ChannelX][ChannelY].GoodsPrice;
								 (TranData.Goods[ChannelX][ChannelY])++;
								  // TranData[CurrentPage].  Time =
								 TranTotal.Money +=  Channels[ChannelX][ChannelY].GoodsPrice;
								 (TranTotal.Goods[ChannelX][ChannelY])++;
								 TranTotal.TotalTrans +=  Channels[ChannelX][ChannelY].GoodsPrice;

								 //���ڼ��Ƚ�����;by gzz 20121009
								 TranTotal.TotalTransJidu +=  Channels[ChannelX][ChannelY].GoodsPrice;
								/*************************************************************************/

								
								//���pc�п������ϱ�pc
								if( SYSPara.PCEnable == 1 )
								{
									sysVPMission.vendSta = 0; 
								}
								
						}		
                    }
		            else
		            { 
		            		//Trace("\r\n errcolu=pstatus=%x",pStatus);
		                   //û��⵽->����Ǯ
		                   //3.���жϵ����
		                   //ûת��λ������״��bit1,bit2,bit3,bit4->�����ù���  
		                   if( pStatus & (GOODS_SOLDOUT_BIT|MOTO_MISPLACE_BIT|MOTO_NOTMOVE_BIT|MOTO_NOTRETURN_BIT) ) 
		                   {
								Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
								Channels[ChannelX][ChannelY].ChannelStat |= CHANNELHARDERR; 
								Trace("\r\n errcolu");
						   }
						   else
						   {
						   	Channels[ChannelX][ChannelY].ChannelStat	&= DRV_CHNSET_BIT;
							Channels[ChannelX][ChannelY].ChannelStat 	|= CHANNELOK;
							Trace("\r\n coluok");
						   }
						   //���pc�п������ϱ�pc
						   if( SYSPara.PCEnable == 1 )
						   {
								sysVPMission.vendSta = 2; 
						   }
		            }
					
				 }
			}
			/*********GOC�رյ������********************/
			else
			{
				//1�ܽ���״̬Ϊ0
				if(pStatus == 0) 
		        {
					Channels[ChannelX][ChannelY].ChannelStat	&= DRV_CHNSET_BIT;
					Channels[ChannelX][ChannelY].ChannelStat 	|= CHANNELOK;	
					//1�ܽ���״̬Ϊ0�������ڽ���״̬ 
					if( BeSaleStat() && (pStatus == 0) )
			        {
						//��Ǯ  
						
						/*************************************************************************/ 
						//����ͨ����¼	
						 if(SYSPara2.AutoColumn==0)
		 				 {
							 //����ͨ����¼							  
							 if(Channels[ChannelX][ChannelY].GoodsNum > 0) 
							 {
								 //121108 by cq DontReduceNum
								 if(!isDontReduceNum())
									 Channels[ChannelX][ChannelY].GoodsNum--;
							 }
		 				 }					 
						 if(Channels[ChannelX][ChannelY].GoodsNum == 0) 
						 {
							if(!isDontReduceNum())
							{
								//Trace("\r\n 2");
								Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
								Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOVER;
								//Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOK;
							}
						 }
						/*************************************************************************/ 

						/*************************************************************************/
						//���½��׼�¼	 
						 TranData.Money +=	Channels[ChannelX][ChannelY].GoodsPrice;
						 (TranData.Goods[ChannelX][ChannelY])++;
						  // TranData[CurrentPage].  Time =
						 TranTotal.Money +=  Channels[ChannelX][ChannelY].GoodsPrice;
						 (TranTotal.Goods[ChannelX][ChannelY])++;
						 TranTotal.TotalTrans +=  Channels[ChannelX][ChannelY].GoodsPrice;

						 //���ڼ��Ƚ�����;by gzz 20121009
						 TranTotal.TotalTransJidu +=  Channels[ChannelX][ChannelY].GoodsPrice;
						/*************************************************************************/
						

						
						//���pc�п������ϱ�pc
						if( SYSPara.PCEnable == 1 )
						{
							sysVPMission.vendSta = 0; 
						}
							
					}
				}
		        else
		        {
		           	   //2.���жϵ����
	                   //ûת��λ������״��bit1,bit2,bit3,bit4->�����ù���  
	                   if( pStatus & (GOODS_SOLDOUT_BIT|MOTO_MISPLACE_BIT|MOTO_NOTMOVE_BIT|MOTO_NOTRETURN_BIT)) 
	                   {
							Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
							Channels[ChannelX][ChannelY].ChannelStat |= CHANNELHARDERR; 								
					   }
					   else
					   {
						   	Channels[ChannelX][ChannelY].ChannelStat	&= DRV_CHNSET_BIT;
							Channels[ChannelX][ChannelY].ChannelStat 	|= CHANNELOK;	
					   }
					   //���pc�п������ϱ�pc
					   if( SYSPara.PCEnable == 1 )
					   {
							sysVPMission.vendSta = 2; 
					   }
		          
		        } 
			}

			CheckChannelStat(); 
			 /*
			 if(BeSaleStat() && ((pStatus & GOODS_SOLDOUT_BIT) == 0)) 
			 {
		     #if DRV_TYPE == DRV_64
				 //120920 by cq DebugModify
				 //((*pComStatus & MOTO_NOTRETURN_BIT) == 0)
				 
					 //goc��:�������(δת,δת��λ)����0x11,������������0x00;
					 //goc��:�������(δת,δת��λ)����0x11,���������ת�����ǳ���ȷ��û��⵽����0x21,������������0x00;
					 //goc���ϣ�����0x80
					 if((pStatus == 0) 
						 || ((SYSPara.GOCCtr == 0) && ((pStatus & MOTO_NOTRETURN_BIT) == 0))
						 || ((SYSPara.GOCCtr > 0) && ((pStatus & (DRV_GOCERR_BIT|GOODS_NOTPASS_BIT)) == 0)&&((pStatus & MOTO_NOTRETURN_BIT) == 0))
						 || ((SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT) && ((pStatus & MOTO_NOTRETURN_BIT) == 0))) 
					{
			 #elif DRV_TYPE == DRV_12
					if((pStatus == 0) || (pStatus & MOTO_NOTRETURN_BIT)) 
					{
			 #endif
							/************************************************************************* / 
			 				if(SYSPara2.AutoColumn==0)
			 				{
								 //����ͨ����¼							  
								 if(Channels[ChannelX][ChannelY].GoodsNum > 0) 
								 {
									 //121108 by cq DontReduceNum
									 if(!isDontReduceNum())
										 Channels[ChannelX][ChannelY].GoodsNum--;
								 }
			 				}
							/************************************************************************* / 

							/************************************************************************* /
							//���½��׼�¼	 
							 TranData.Money +=	Channels[ChannelX][ChannelY].GoodsPrice;
							 (TranData.Goods[ChannelX][ChannelY])++;
							  // TranData[CurrentPage].  Time =
							 TranTotal.Money +=  Channels[ChannelX][ChannelY].GoodsPrice;
							 (TranTotal.Goods[ChannelX][ChannelY])++;
							 TranTotal.TotalTrans +=  Channels[ChannelX][ChannelY].GoodsPrice;

							 //���ڼ��Ƚ�����;by gzz 20121009
							 TranTotal.TotalTransJidu +=  Channels[ChannelX][ChannelY].GoodsPrice;
							/************************************************************************* /

							
							//���pc�п������ϱ�pc
							if( SYSPara.PCEnable == 1 )
							{
								sysVPMission.vendSta = 0; 
							}
							
					}
					else 
					{
					}
			 }
			 else 
			 {
			 }

	 #if DRV_TYPE == DRV_64 
			 if((pStatus & (DRV_ERR_MASK|GOODS_SOLDOUT_BIT|GOODS_NOTPASS_BIT)) 
				|| (Channels[ChannelX][ChannelY].GoodsNum == 0)) 
			 {
	 #elif DRV_TYPE == DRV_12
			 if((pStatus & (DRV_ERR_MASK|GOODS_SOLDOUT_BIT)) 
				|| (Channels[ChannelX][ChannelY].GoodsNum == 0)) 
			 {
	 #endif 						    
					if(pStatus & GOODS_SOLDOUT_BIT) 
					{
						//Trace("\r\n 1");
						//121108 by cq DontReduceNum
						if(!isDontReduceNum())
						{
							Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
							Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOVER;
							Channels[ChannelX][ChannelY].GoodsNum = 0;
						}
					}
					if(Channels[ChannelX][ChannelY].GoodsNum == 0) 
					{
						//Trace("\r\n 2");
						Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
						Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOVER;
						//Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOK;
					}

				#if DRV_TYPE == DRV_64
					if( (pStatus & GOODS_NOTPASS_BIT) && (!BeSaleStat()) ) 
					{
						//Trace("\r\n 3");
						
						//121108 by cq DontReduceNum
						if(!isDontReduceNum())
						{
							Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
							Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOVER;						
						}
					}
				#endif

					//if(pStatus & DRV_ERR_MASK) 
					if(pStatus & MOTO_NOTRETURN_BIT)//120920 by cq DebugModify							
					{
						Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
						Channels[ChannelX][ChannelY].ChannelStat |= CHANNELHARDERR; 					
					}

					//���pc�п������ϱ�pc
					if( SYSPara.PCEnable == 1 )
					{
						sysVPMission.vendSta = 2; 
					}

					CheckChannelStat(); 						
			 }
			 else 
			 {
				Channels[ChannelX][ChannelY].ChannelStat &= DRV_CHNSET_BIT;
				Channels[ChannelX][ChannelY].ChannelStat |= CHANNELOK;

				//���pc�п������ϱ�pc
				if( SYSPara.PCEnable == 1 )
				{
					sysVPMission.vendSta = 0; 
				}
			 }

	 #if DRV_TYPE == DRV_64
			 //121108 by cq GOCErrorSevice
			 //if((SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT)) 
			  //if((SYSPara.GOCErrorSevice == 0) && (SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT)) 
			 if(isGOCErrorSevice() && SYSPara.GOCErrorSevice == 1)
			 {
				 SYSPara1.GOCStat = 0;
				 ClrDevStatus(DEV_ERR_BIT_GOODSCHK);
			 }
			 else if((SYSPara.GOCCtr > 0) && (pStatus & DRV_GOCERR_BIT))  
			 {
				SYSPara1.GOCStat = 1;
				SetDevStatus(DEV_ERR_BIT_GOODSCHK);
			 } 
			 else 
			 {
				SYSPara1.GOCStat = 0;
				ClrDevStatus(DEV_ERR_BIT_GOODSCHK);
			 }
	 #endif
			*/
			 MsgBack.pBackMsg = pStatus;					 
			 //OSMboxPost(g_CommBackMsg,(uint32_t *)&pStatus);
			 OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);
		/*
		 #if DRV_TYPE == DRV_64
				 if(SYSPara.GOCCtr > 0)
				 {
					 OSTimeDly(OS_TICKS_PER_SEC / 10);
					 pStatus = DRV_Inquire(ChannelNum,GOODSCHK_CLOSE);
				 }
		 #endif
		*/	 

			 if(BeSaleStat() && ( SYSPara.PCEnable == 1 )) 
			 {
				 //�õ���pc�ϱ��Ļ������
				 i=0;
				 for(x = 0; x<MAXLAYER;x++)   
				 {			
					for(y=0; y<MAXCHANNEL;y++) 
					{
						Pcchannel = x*10+y+11;
						if(DRV_ChnChk(Pcchannel,&PcChannelX,&PcChannelY) == TRUE) 
						{
							if(Pcchannel != channel)
							{
								i++;
							}
							else
							{
								sysVPMission.vendColumn = i;	
							}
						}				
					}
				 }
				 
				 if(sysVPMission.vendCmd == 0)			 
				 {
					sysVPMission.vendType = 0;
				 }	
				 if(sysVPMission.vendCmd == 1)	
				 {
					PcValue = sysVPMission.vendCost;
				 }
				 else
				 {
					 if(SYSPara.Decimal==1)
					 {
						PcValue = Channels[ChannelX][ChannelY].GoodsPrice * 10;
					 }
					 else if(SYSPara.Decimal==2)
					 {
						PcValue = Channels[ChannelX][ChannelY].GoodsPrice; 
					 }	
				 }				 
				 VPMission_Vendout_RPT( sysVPMission.vendSta, sysVPMission.vendColumn, sysVPMission.vendType, PcValue);
			 }	

		  }
		  else 
		  { 			 
			SetDevStatus(DEV_ERR_BIT_DRVCOMM);
		  }
	  }
}


  
/******************************************************************************
**                            End Of File
******************************************************************************/
