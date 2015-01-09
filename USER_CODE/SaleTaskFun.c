/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           SaleTaskFun.c
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        ����������õ���س���,��Ÿ�����״̬���Լ���ʾ�������������ҳ�棬����ʾͶ�ҽ����йصĸ�ҳ��
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
#include "lcd.h"
#include "context.h"
#include "drv.h"
#include "hopper.h"
#include "SaleTaskFun.h"
#include "VMC_PC.h"
#include "DebugTrace.h"
#include "Function.h"




uint32_t ChgAmount;	  //��ǰ����ֵ

/*�����������������Ƿ���Ͷ�ң��Լ������ϸ���״̬��������һ����״̬*/
/*���� state:��ǰ����״̬*/
/*���� key:����ֵ*/
/*����ֵ ����״̬*/
uint8_t KeyProcess(uint8_t state,uint16_t key,uint8_t *ChannelNum)//ѡ������;by gzz 20121025
{
	unsigned char x = 0;
	unsigned char y = 0;
	uint8_t   channel,ChannelX,ChannelY;

	//ѡ������;by gzz 20121025
	if(SYSPara.KeySel == 1 )
	{
		Trace("\r\n taskb key=%d",key);
		for(x = 0; x<MAXLAYER;x++)	  
		{					
			for(y=0; y<MAXCHANNEL;y++) 
			{  
				channel = x*10+y+11;
				if(DRV_ChnChk(channel,&ChannelX,&ChannelY) == TRUE) 
				{
					if( (Channels[ChannelX][ChannelY].GoodsCode == key)&&(Channels[ChannelX][ChannelY].GoodsNum > 0)&&((Channels[ChannelX][ChannelY].ChannelStat & 0x03)==1) )
					{
						*ChannelNum = channel;
						if(g_Amount > 0) 
						{					    
							state = MVC_XUANHUO;
						}
						else
						{
							state = MVC_CHAXUN;
						}
						Trace("\r\n taskb1 channel=%d,state=%d",*ChannelNum,state);
						return state;
					}  
					if(Channels[ChannelX][ChannelY].GoodsCode == key)
					{
						*ChannelNum = channel;
						if(g_Amount > 0) 
						{					    
							state = MVC_XUANHUO;
						}
						else
						{
							state = MVC_CHAXUN;
						}
						Trace("\r\n taskb2 channel=%d,state=%d",*ChannelNum,state);
					}  	
				} 
			}  		
		}	
	}
	else
	{
		switch(key) 
		{			    
			case KEY_0:	
				#if CHNINPUT_MODE == TWO_Bit_MODE	
				//��������������֣����һ�û������λ����ʱ���������֣����Ҹ���Ϊ�����š���״̬��Ϊ�������״̬
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(0);
					g_KeyStat.InputCnt++;
					state = MVC_INPUT;    
				}
				#endif
				break;
		
			case KEY_1:
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(1);
					g_KeyStat.InputCnt++;
					state = MVC_INPUT;    
				}
				#elif CHNINPUT_MODE == ONE_Bit_MODE
				g_KeyStat.InputNum = 1;
				if(g_KeyStat.InputMode > 0) 
				{
					if(g_Amount > 0)
					{
					    state = MVC_XUANHUO;
					} 
					else 
					{
					    state = MVC_CHAXUN;
					}
				}
				#endif
				break;
		
			case KEY_2:
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(2);
					g_KeyStat.InputCnt++;  
					state = MVC_INPUT;   
				}
				#elif CHNINPUT_MODE == ONE_Bit_MODE
				g_KeyStat.InputNum = 2;
				if(g_KeyStat.InputMode > 0) 
				{
					if(g_Amount > 0) 
					{
					    state = MVC_XUANHUO;
					}
					else 
					{
					    state = MVC_CHAXUN;
					}
				}
				#endif
				break;
		
			case KEY_3:
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(3);
					g_KeyStat.InputCnt++;   
					state = MVC_INPUT;  
				}
				#elif CHNINPUT_MODE == ONE_Bit_MODE
				g_KeyStat.InputNum = 3;
				if(g_KeyStat.InputMode > 0) 
				{
					if(g_Amount > 0) 
					{
					    state = MVC_XUANHUO;
					}
					else 
					{
					    state = MVC_CHAXUN;
					}
				}
				#endif
				break;
		
			case KEY_4:
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(4);
					g_KeyStat.InputCnt++; 
					state = MVC_INPUT;    
				}
				#elif CHNINPUT_MODE == ONE_Bit_MODE
				g_KeyStat.InputNum = 4;
				if(g_KeyStat.InputMode > 0) 
				{
					if(g_Amount > 0) 
					{
					    state = MVC_XUANHUO;
					} 
					else 
					{
					    state = MVC_CHAXUN;
					}
				}
				#endif
				break;
		
			case KEY_5:
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(5);
					g_KeyStat.InputCnt++;  
					state = MVC_INPUT;   
				}
				#elif CHNINPUT_MODE == ONE_Bit_MODE
				g_KeyStat.InputNum = 5;
				if(g_KeyStat.InputMode > 0) 
				{
					if(g_Amount > 0) 
					{
					    state = MVC_XUANHUO;
					}
					else 
					{
					    state = MVC_CHAXUN;
					}
				}
				#endif
				break;
		
			case KEY_6:
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(6);
					g_KeyStat.InputCnt++; 
					state = MVC_INPUT;    
				}
				#elif CHNINPUT_MODE == ONE_Bit_MODE
				g_KeyStat.InputNum = 6;
				if(g_KeyStat.InputMode > 0) 
				{
					if(g_Amount > 0) 
					{
					    state = MVC_XUANHUO;
					}
					else
					{
					    state = MVC_CHAXUN;
					}
				}
				#endif
				break;
		
			case KEY_7:
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(7);
					g_KeyStat.InputCnt++;  
					state = MVC_INPUT;   
				}
				#elif CHNINPUT_MODE == ONE_Bit_MODE
				g_KeyStat.InputNum = 7;
				if(g_KeyStat.InputMode > 0) 
				{
					if(g_Amount > 0) 
					{
					    state = MVC_XUANHUO;
					}
					else
					{
					    state = MVC_CHAXUN;
					}
				}
				#endif
				break;
		
			case KEY_8:
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(8);
					g_KeyStat.InputCnt++; 
					state = MVC_INPUT;    
				}
				#elif CHNINPUT_MODE == ONE_Bit_MODE
				g_KeyStat.InputNum = 8;
				if(g_KeyStat.InputMode > 0)
				{
					if(g_Amount > 0)
					{
					    state = MVC_XUANHUO;
					}
					else 
					{
					    state = MVC_CHAXUN;
					}
				}
				#endif
				break;
		
			case KEY_9:
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if((g_KeyStat.InputMode > 0) && (g_KeyStat.InputCnt < 2)) 
				{
				    g_KeyStat.InputNum = CalcInputNum(9);
					g_KeyStat.InputCnt++; 
					state = MVC_INPUT;    
				}
				#elif CHNINPUT_MODE == ONE_Bit_MODE
				g_KeyStat.InputNum = 9;
				if(g_KeyStat.InputMode > 0)
				{
					if(g_Amount > 0) 
					{
					    state = MVC_XUANHUO;
					} 
					else 
					{
					    state = MVC_CHAXUN;
					}
				}
				#endif
				break;

			case KEY_CLR:
				//��clr�����һ���������֡���״̬��Ϊ�������״̬
				#if CHNINPUT_MODE == TWO_Bit_MODE
				if(g_KeyStat.InputCnt > 0) 
				{
				    g_KeyStat.InputNum = g_KeyStat.InputNum/10;
					g_KeyStat.InputCnt--; 
					state = MVC_INPUT;    
				}
				#endif
				break;
		
			case KEY_ENTER:
				//����enter���󣬸����Ƿ���Ͷ�ң�״̬��Ϊ��ѯ����״̬������ѡ��״̬�����Ҹ����ϸ���״̬��������һ����״̬������������ף����߼�Ǯ
				switch(state) 
				{
				    case MVC_INPUT:
						#if CHNINPUT_MODE == TWO_Bit_MODE
						if((g_Amount > 0) && (g_KeyStat.InputCnt >= 2)) 
						{					    
							state = MVC_XUANHUO;
						}
						#endif
						break;
			
					case MVC_RETRANS:
						state = MVC_SALE;
						break;
			
					case MVC_LESSMONEY:
						state = MVC_ADDMONEY;
						break;
			
					default:
						break;
				}
				break;
		
			case KEY_CANCEL:
				switch(state) 
				{
				    //�����ǰ�����������ְ�����״̬������Ѿ�������һ�������ˣ�ִ�� RstInputNum();����ֱ�ӽ�����������
				    //���û�У�������Ƿ���Ͷ�ң�״̬����Ϊ����״̬�����ǳ�ʼ����״̬
				    case MVC_INPUT:
						#if CHNINPUT_MODE == TWO_Bit_MODE
						if(g_KeyStat.InputCnt == 0) 
						{
						    if(g_Amount > 0) 
							{					    
							    state = MVC_SALE;
								#if DISP_MODE == LCD_DISPLAY
							    Cursor_Off(LCDUP);
							    #endif
							} 
							else 
							{
							   	RstInputNum();
								sysVPMission.dspTimer2 = 0;//�ӿ���ʾ���н���;by gzz 20121106
								state = MVC_BEGIN;
							}
					    } 
						else 
						{
						    RstInputNum();
						}
						#endif
						break;
					//�����ǰ�ǽ���״̬���Ǯ״̬������cancel������Ƿ��׹�һ�κ󣬻���������˱ң���������״̬
					case MVC_SALE:
					case MVC_ADDMONEY:
						//����н��׹�������������˱ң����˱�
						if((g_Amount > 0) && (IsHaveSaled() || (SYSPara.TransEscape > 0)) 
							//������û�������ߵ�ǰ������ûǮ
							&& ((SYSPara.ReaderEnable==0)||(Reader_GetFundsMultiplyUnit()==0))) 
						{
						    state = MVC_PAYOUT;
					    }
						break;
			        //�����ǰ�Ǽ�������״̬������Ϊ����״̬
					case MVC_RETRANS:
						state = MVC_PAYOUT;
						break;
			        //�����ǰ��Ǯ����״̬������Ϊ����״̬
					case MVC_LESSMONEY:
						state = MVC_SALE;
						break;
			
					default:
						break;
				}				
				break;
		
			default:
				break;
		}
	}
	
	return state;
}

/*������ʱʱ�������ϸ���״̬���л�����״̬����*/
/*���� state:��ǰ����״̬*/
/*����ֵ ����״̬*/
uint8_t SaleTimeoutProc(uint8_t state)
{
     switch(state) 
	 {
	     case MVC_INPUT:
			 RstInputNum();
		
			 #if DISP_MODE == LCD_DISPLAY
		     Cursor_Off(LCDUP);
		     #endif
		
			 if(g_Amount > 0) 
			 {			 
				 state = MVC_SALE;
			 } 
			 else 
			 {
			     state = MVC_BEGIN;
			 }
			 break;
			 /*
			 case SALE:
			 case ADDMONEY:
			 TranTotal.Iou = g_Amount;	  	//
			 XSystemPara(WRITE);
			 state = CHAOSHI;
			 break;
			 */
		 case MVC_LESSMONEY:
			 state = MVC_SALE;
			 break;
	
		 case MVC_RETRANS:
			 state = MVC_PAYOUT;
			 break;
	
		 default:
		 	break;
	 }
	 return state;
}

/*����С��λ�������ĺ���*/
/*����   dispnum:Ͷ�ҽ��Է�Ϊ��λ dec:С��λ*/
/*����ֵ ��ʾ�ַ���*/
char strnum[10];
char *SprintDec(uint32_t dispnum, uint8_t dec)
{  
   switch(dec) 
   {
      case 0:
	  sprintf(strnum,"%d",dispnum);
	  break;

	  case 1:
	  sprintf(strnum,"%d.%d",dispnum/10,dispnum%10);
	  break;
	  
	  default:
	  sprintf(strnum,"%02d.%02d",dispnum/100,dispnum%100);
	  break;
   }
   return strnum;
}

/*��ʾ��ͣ���񣬺ʹ������*/
void DispErrText(void)
{
	#if DISP_MODE == LCD_DISPLAY
    char    str2[48],strtemp[20];
    #endif	

	uint8_t  i;
	uint16_t status;
	uint8_t len = 0;	
	uint8_t str[48];

	status = GetDevStatus();

	if(status > 0) 
	{
		for(i = 16; i > 0; i--) 
		{
		    if(status & (1 << i)) 
			{
			    break;
			}
		}
	
		switch(1 << i) 
		{
		    case DEV_ERR_BIT_NOTE:
				status = DEV_ERR_NOTE;
				break;
	
			case DEV_ERR_BIT_COIN:
				status = DEV_ERR_COIN;
				break;
	
			case DEV_ERR_BIT_CHANGER:
				status = DEV_ERR_CHANGER;
				break;
	
			case DEV_ERR_BIT_COINLOW:
				status = DEV_ERR_COINLOW;
				break;
	
			case DEV_ERR_BIT_CHNOUT:
				status = DEV_ERR_CHNOUT;
				break;
	
			case DEV_ERR_BIT_CHNALL:
				status = DEV_ERR_CHNALL;
				break;
	
			case DEV_ERR_BIT_DRVCOMM:
				status = DEV_ERR_DRVCOMM;
				break;
	
			case DEV_ERR_BIT_CHNDIST:
				status = DEV_ERR_CHNDIS;
				break;
	
			case DEV_ERR_BIT_PARASET:
				status = DEV_ERR_PARASET;
				break;
	
			case DEV_ERR_BIT_LCDCOMM:
				status = DEV_ERR_LCDCOMM;
				break;
	
			case DEV_ERR_BIT_PRICESET:
				status = DEV_ERR_PRICESET;
				break;
	
			case DEV_ERR_BIT_GOODSCHK:
				status = DEV_ERR_GOODSCHK;
				break;
	
			case DEV_ERR_BIT_FLASH:
				status = DEV_ERR_FLASH;
				break;

			case DEV_ERR_BIT_RTC:
				status = DEV_ERR_RTC;
				break;
	
			default:
				RstDevStatus();
				break;
	
		}
   	
		#if DISP_MODE == LCD_DISPLAY	
		//sprintf(strtemp, "%02x",status);
		//strcpy(str2, Disp_Fault[SYSPara.Language][1]);
		//strcat(str2, strtemp);
				 
		//WriteFull_LCD(LINE0,Disp_Fault[SYSPara.Language][0],strlen(Disp_Fault[SYSPara.Language][0]));
		sprintf(strtemp, "(%02x)",status);
		//strcpy(str2, Disp_Fault[SYSPara.Language][1]);
		//strcat(str2, strtemp);
		strcpy(str2, strtemp);
		switch(status)
		{
			case DEV_ERR_NOTE:
				strcat(str2, Disp_Fault[SYSPara.Language][4]);	
				break;
			case DEV_ERR_COIN:
				strcat(str2, Disp_Fault[SYSPara.Language][5]);	
				break;	
			case DEV_ERR_CHANGER:
				strcat(str2, Disp_Fault[SYSPara.Language][3]);	
				break;	
			case DEV_ERR_COINLOW:
				strcat(str2, Disp_Fault[SYSPara.Language][6]);	
				break;	
			case DEV_ERR_CHNOUT:
				strcat(str2, Disp_Fault[SYSPara.Language][7]);	
				break;	
			case DEV_ERR_CHNALL:
				strcat(str2, Disp_Fault[SYSPara.Language][8]);	
				break;	
			case DEV_ERR_DRVCOMM:
				strcat(str2, Disp_Fault[SYSPara.Language][9]);	
				break;		
			case DEV_ERR_CHNDIS:
				strcat(str2, Disp_Fault[SYSPara.Language][10]);	
				break;	
			case DEV_ERR_PARASET:
				strcat(str2, Disp_Fault[SYSPara.Language][11]);	
				break;	
			case DEV_ERR_LCDCOMM:
				strcat(str2, Disp_Fault[SYSPara.Language][12]);	
				break;	
			case DEV_ERR_PRICESET:
				strcat(str2, Disp_Fault[SYSPara.Language][13]);	
				break;	
			case DEV_ERR_GOODSCHK:
				strcat(str2, Disp_Fault[SYSPara.Language][14]);	
				break;	
			case DEV_ERR_FLASH:
				strcat(str2, Disp_Fault[SYSPara.Language][15]);	
				break;	
			case DEV_ERR_RTC:
				strcat(str2, Disp_Fault[SYSPara.Language][16]);	
				break;	
			//case DEV_ERR_USERDOOR:
			//	strcat(str2, Disp_Fault[SYSPara.Language][17]);	
			//	break;	
			//case DEV_ERR_MAINDOOR:
			//	strcat(str2, Disp_Fault[SYSPara.Language][18]);	
			//	break;		
		}
		if(sysVPMission.dspErrTimer == 0)	
		{
			sysVPMission.dspErrTimer = VP_DSP_TIME4*3;	
			if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
			{			
				ClearScreen();
				RTCn_GetFullTime ((RTC_TIME_Type *)&TranData.Time);//��ȡrtcʱ��
				OSTimeDly(2);
				//1������ʾ
				Pitu_LCDPrintf(LINE01,0,"��",strlen("��"),0,3);
				Pitu_LCDPrintf(LINE01,40,Disp_Fault[1][19],strlen(Disp_Fault[1][19]),0,1);
				Pitu_LCDPrintf(LINE03,40,Disp_Fault[1][0],strlen(Disp_Fault[1][0]),0,0);
				strcpy(str2, Disp_Fault[SYSPara.Language][0]);
				strcat(str2, strtemp);
				Pitu_LCDPrintf(LINE11,40,str2,strlen(str2),0,0);
				//Pitu_LCDPrintf(LINE13,40,str2,strlen(str2),0,0);
				//2����
				Pitu_LCDClearLine(LINE22,1,0);
				//3ʱ������
				len = sprintf( str, "%04d", TranData.Time.YEAR);
				Pitu_LCDPrintf(LINE23,40,str,len,0,1);
				len = sprintf( str, "%02d-%02d",TranData.Time.MONTH,TranData.Time.DOM);
				Pitu_LCDPrintf(LINE31,40,str,len,0,1);
				len = sprintf( str, "%02d:%02d", TranData.Time.HOUR, TranData.Time.MIN);
				Pitu_LCDPrintf(LINE23,96,str,len,0,3);	
				OSTimeDly(OS_TICKS_PER_SEC / 10);
			}
			else
			{
				WriteFull_LCD(LINE0,Disp_Fault[SYSPara.Language][0],strlen(Disp_Fault[SYSPara.Language][0]));
				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{			
					WriteFull_LCD(LINE1,"",0);
					WriteFull_LCD(LINE2,str2,strlen(str2));
					WriteFull_LCD(LINE3,"",0);//120920 by cq DebugModify
				}
				else
				{
					WriteFull_LCD(LINE1,str2,strlen(str2));
				}
			}
		}
		
		
	    #endif
	}
}

/*��ʾ���ڳ�ʼ��*/
void DispInitText(void)
{
#if DISP_MODE == LCD_DISPLAY
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		Pitu_LCDClearLine(LINE1, 0,0);
		Pitu_LCDPutLOGOBmp(LINE1,20,SYSPara.LogoSel);
		//OSTimeDly(200*3);
		//Pitu_LCDPutLOGOBmp(LINE13,20,2);
		//OSTimeDly(200*3);
		WriteFull_LCD(LINE3,Disp_Init[SYSPara.Language][0],strlen(Disp_Init[SYSPara.Language][0]));
		WriteFull_LCD(LINE32,Disp_Wait[SYSPara.Language][0],strlen(Disp_Wait[SYSPara.Language][0]));
	}
	else
	{
		WriteFull_LCD(LINE0,Disp_Init[SYSPara.Language][0],strlen(Disp_Init[SYSPara.Language][0]));
		WriteFull_LCD(LINE1,Disp_Wait[SYSPara.Language][0],strlen(Disp_Wait[SYSPara.Language][0]));
		//���Ʒ;��Ļ�ļ���;by gzz 20121025
		if(IsLargeLCD())
		{
			WriteFull_LCD(LINE2,"",0);
			WriteFull_LCD(LINE3,"",0);//120920 by cq DebugModify
		}
	}
#endif
}


//120704 by cq DispVersion
/*��ʾ����汾��*/
void DispVersionText(void)
{
	uint16_t	tempVersion;
	char  		VerInit[48];
	uint8_t	    Verlen;
	#if DISP_MODE == LCD_DISPLAY
	//120704 by cq DispVersion
	//tempVersion = SOFTVERSION;
	tempVersion = 143;
	tempVersion = (tempVersion & 0x00ff);
	Verlen=sprintf( VerInit,"    Version%d.%02d",tempVersion/100, tempVersion%100);
	//Verlen=sprintf( VerInit,"    7636  V%d.%d",tempVersion/100, tempVersion%100);
	//���Ʒ;��Ļ�ļ���;by gzz 20121025
	if(IsLargeLCD())
	{
		WriteFull_LCD(LINE1,VerInit,Verlen);
		WriteFull_LCD(LINE2,"",0);
		WriteFull_LCD(LINE3,"",0);//120920 by cq DebugModify
	}
	else
	{
		WriteFull_LCD(LINE0,VerInit,Verlen);
		WriteFull_LCD(LINE1,"",0);
	}
	OSTimeDly(OS_TICKS_PER_SEC);
	#endif
}


/*�ڿ���״̬�£�������ʾ�ֽ����ѣ������ֽ�һ�Ӳ��*/
/*���� mode:��ʾ��ʽ*/
void DispBeginText(uint8_t mode)
{
	uint8_t pNum,DispLine0,DispLine1;
	uint8_t len = 0;	
	uint8_t str[48];
	static uint8_t timeFLag1 = 0,timeFLag2 = 0;

#if DISP_MODE == LCD_DISPLAY
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
		RTCn_GetFullTime ((RTC_TIME_Type *)&TranData.Time);//��ȡrtcʱ��
		OSTimeDly(2);
		
		Pitu_LCDPutLOGOBmp(LINE0,75,SYSPara.LogoSel);
		len = sprintf( str, "%04d-%02d-%02d",  TranData.Time.YEAR,TranData.Time.MONTH,TranData.Time.DOM);
		//Trace("\r\n %04d-%02d-%02d, %02d:%02d",TranData.Time.YEAR,TranData.Time.MONTH,TranData.Time.DOM,TranData.Time.HOUR, TranData.Time.MIN);
		if( ((TranData.Time.MONTH>=13)||(TranData.Time.DOM>=32))&&(timeFLag1<3) )
		{
			timeFLag1++;
		}
		else
		{
			timeFLag1 = 0;
			Pitu_LCDPrintf(LINE12,66,str,len,0,1);
		}
		
		len = sprintf( str, "%02d:%02d", TranData.Time.HOUR, TranData.Time.MIN);
		if( ((TranData.Time.HOUR>=25)||(TranData.Time.MIN>=62))&&(timeFLag2<3) )
		{
			timeFLag2++;
		}
		else
		{
			timeFLag2 = 0;
			Pitu_LCDPrintf(LINE2,51,str,len,0,2);
		}
	}
	else
	{
		//���Ʒ;��Ļ�ļ���;by gzz 20121025
		if(IsLargeLCD())
		{
			DispLine0 = LINE0;
			DispLine1 = LINE2;
			//WriteFull_LCD(LINE1,"",0);//120621 by cq LCDswitch


			//120621 by cq LCDswitch
			RTCn_GetFullTime ((RTC_TIME_Type *)&TranData.Time);//��ȡrtcʱ��
			OSTimeDly(2);
			/*
			if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
			{
				ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
				len = sprintf( str, "		  %d-%d-%d", TranData.Time.YEAR,TranData.Time.MONTH,TranData.Time.DOM);
				Pitu_LCDPrintf(LINE03,0,str,len,0,1);
				len = sprintf( str, "  %02d:%02d", TranData.Time.HOUR, TranData.Time.MIN);
				Pitu_LCDPrintf(LINE11,0,str,len,0,2);
				Pitu_LCDClearLine(LINE32,0,0);
			}
			else
			*/
			{
				len = sprintf( str, "  %d/%d/%d %02d:%02d", TranData.Time.YEAR,TranData.Time.MONTH,TranData.Time.DOM,TranData.Time.HOUR, TranData.Time.MIN);
			
				WriteFull_LCD(LINE1,str,len);
				//Trace("%s",str);
				//WriteFull_LCD(LINE3," O(*^_^*)O \\(*^o^*)/",strlen(" O(*^_^*)O \\(*^o^*)/"));
				//WriteFull_LCD(LINE3,Disp_Input[SYSPara.Language][6],strlen(Disp_Input[SYSPara.Language][6]));
				//WriteFull_LCD(LINE3,"						 ",24);//120920 by cq DebugModify
				WriteFull_LCD(LINE3,Disp_Input[SYSPara.Language][6],strlen(Disp_Input[SYSPara.Language][6]));
			}
		}
		else
		{
			DispLine0 = LINE0;
			DispLine1 = LINE1;
		}
		
		if(mode == 0) 
		{
			/*
			if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
			{
				Pitu_LCDPrintf(LINE0,0,Disp_Main[SYSPara.Language][0],strlen(Disp_Main[SYSPara.Language][0]),0,0);
				Pitu_LCDPrintf(LINE3,0,Disp_Main[SYSPara.Language][1],strlen(Disp_Main[SYSPara.Language][1]),0,0);
			}
			else
				*/
			{
				WriteFull_LCD(DispLine0,Disp_Main[SYSPara.Language][0],strlen(Disp_Main[SYSPara.Language][0]));
				WriteFull_LCD(DispLine1,Disp_Main[SYSPara.Language][1],strlen(Disp_Main[SYSPara.Language][1]));
			}
		} 
		//120914 by cq Cashless
		else if(SYSPara.ReaderEnable)
		{
			WriteFull_LCD(DispLine0,Disp_Main_2[SYSPara.Language][0],strlen(Disp_Main_2[SYSPara.Language][0]));
			WriteFull_LCD(DispLine1,Disp_Main_2[SYSPara.Language][1],strlen(Disp_Main_2[SYSPara.Language][1]));
		}
		else 
		{
			if(CashState.ChangerState != CHANGER_OK) 
			{
				pNum = 4;
			} 
			else if(CashState.NoteState != NOTE_DEV_OK) 
			{
				pNum = 3;
			} 
			else if(CashState.CoinState != COIN_DEV_OK) 
			{
				pNum = 2;
			} else 
			{
				pNum = 1;
			}

			
			
			if(sysXMTMission.recSVTemp>0)
			{
				if((sysXMTMission.recSVTemp/10)<10)
				{
					len = sprintf( str, "����%d.%dC  �趨%d.%dC", sysXMTMission.recPVTemp/10, sysXMTMission.recPVTemp%10,sysXMTMission.recSVTemp/10, sysXMTMission.recSVTemp%10 );
				}
				else
				{
					len = sprintf( str, "����%d.%dC �趨%d.%dC", sysXMTMission.recPVTemp/10, sysXMTMission.recPVTemp%10,sysXMTMission.recSVTemp/10, sysXMTMission.recSVTemp%10 );
				}
				/*
				if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
				{
					Pitu_LCDPrintf(LINE0,0,str,len,0,0);
				}
				else*/
				{
					WriteFull_LCD(DispLine0,str,len);
				}
			}
			else
			{
				if(pNum == 4) 
				{
					/*
					if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
					{
						Pitu_LCDPrintf(LINE0,0,Disp_Input[SYSPara.Language][5],strlen(Disp_Input[SYSPara.Language][5]),0,0);
					}
					else*/
					{
						WriteFull_LCD(DispLine0,Disp_Input[SYSPara.Language][5],strlen(Disp_Input[SYSPara.Language][5]));
					}
				} 
				else 
				{
					/*
					if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
					{
						Pitu_LCDPrintf(LINE0,0,Disp_Input[SYSPara.Language][0],strlen(Disp_Input[SYSPara.Language][0]),0,0);
					}
					else*/
					{
						WriteFull_LCD(DispLine0,Disp_Input[SYSPara.Language][0],strlen(Disp_Input[SYSPara.Language][0]));
					}
				}
			}	
			/*
			if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
			{
				Pitu_LCDPrintf(LINE3,0,Disp_Input[SYSPara.Language][pNum],strlen(Disp_Input[SYSPara.Language][pNum]),0,0);
			}
			else*/
			{
				WriteFull_LCD(DispLine1,Disp_Input[SYSPara.Language][pNum],strlen(Disp_Input[SYSPara.Language][pNum])); 
			}

		}
	}
#endif
}


/*����״̬�£���ʾ��ѯ���,��ȱ�������ϣ����ǽ��ܣ���������ʾ���*/
/*���� x:������� y:�����к�*/
void DispChaxunText(uint8_t x,uint8_t y,uint8_t  KeyInput)//ѡ������;by gzz 20121025
{			 
	 #if DISP_MODE == LCD_DISPLAY
	 char	str1[48];
  	 char	str2[48];
	 char    strtemp[20];
	 char    *pstr;
	 #endif
	 			    
	 #if DISP_MODE == LCD_DISPLAY	 
	 //ѡ������;by gzz 20121025
	 if(SYSPara.KeySel == 1 )
	 {
	 	sprintf(strtemp,"%2d",KeyInput);
	 }
	 else
	 {
	 	sprintf(strtemp,"%2d",g_KeyStat.InputNum);
	 }	 
	 strcpy(str1, Disp_ChInput[SYSPara.Language][0]);
	 strcat(str1, strtemp);
											    
	 strcpy(str2, Disp_ChnPara[SYSPara.Language][0]);
	 strcat(str2, strtemp);
	 if((Channels[x][y].ChannelStat & DRV_STAT_MASK) == CHANNELHARDERR)
	 {
		 strcat(str2, Disp_ChnState[SYSPara.Language][2]);
	 } 
	 else if((Channels[x][y].ChannelStat & DRV_STAT_MASK) == CHANNELDISABLE)
	 {
		 strcat(str2, Disp_ChnState[SYSPara.Language][0]);
	 } 
	 else if((Channels[x][y].ChannelStat & DRV_STAT_MASK) == CHANNELOVER)
	 {
		 strcat(str2, Disp_ChnState[SYSPara.Language][3]);
	 }
	 else 
	 {
		 pstr = SprintDec(Channels[x][y].GoodsPrice,SYSPara.Decimal);
	     strcpy(str2, Disp_ChnPara[SYSPara.Language][1]);	
	     strcat(str2, pstr);	
	 }

	 if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	 {
		//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
		//����
		Pitu_LCDClearLine(LINE22,1,0);
		Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
		Pitu_LCDPrintf(LINE23,40,str1,strlen(str1),0,0);
		Pitu_LCDPrintf(LINE31,40,str2,strlen(str2),0,0);
		OSTimeDly(OS_TICKS_PER_SEC*2);
	 }
	 else
	 {
		 WriteFull_LCD((uint8_t)LINE0,str1,strlen(str1));
		 WriteFull_LCD((uint8_t)LINE1,str2,strlen(str2));
	 }
	 //change by liya 2012-10-16
	 WriteFull_LCD((uint8_t)LINE2,"",0);
	 #endif					 
}

/*��ʾ������ʱ*/
void DispChaoshiText(void)
{
    #if DISP_MODE == LCD_DISPLAY
	WriteFull_LCD((uint8_t)LINE0,Disp_Timeout[SYSPara.Language][0],strlen(Disp_Timeout[SYSPara.Language][0]));
	WriteFull_LCD((uint8_t)LINE1,Disp_Blank,strlen(Disp_Blank));
	#endif
}

/*����״̬�ºͿ���״̬�£���ʾ���������ҳ��*/
/*����ֵ ����״̬*/
uint8_t DispInputText(void)
{
#if DISP_MODE == LCD_DISPLAY
	char	str1[48];
	char	strtemp[20];
#endif
	
	uint8_t state = MVC_INPUT;

	
	if(g_KeyStat.InputCnt > 0) //�Ѿ�����һλ����
	{
	#if DISP_MODE == LCD_DISPLAY	   		 		  
		strcpy(str1,Disp_ChInput[SYSPara.Language][0]);
		if(g_KeyStat.InputCnt >= 2) 
		{
			sprintf(strtemp,"%02d",g_KeyStat.InputNum);
		}
		else 
		{
			sprintf(strtemp,"%d",g_KeyStat.InputNum);
		}
		strcat(str1,strtemp);	  
		if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
		{
			//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
			//����
			Pitu_LCDClearLine(LINE22,1,0);
			Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
			Pitu_LCDPrintf(LINE23,40,str1,strlen(str1),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE31,40,Disp_ChInput[1][0],strlen(Disp_ChInput[1][0]),0,0);
			//OSTimeDly(OS_TICKS_PER_SEC);
		}
		else
		{
			WriteFull_LCD(LINE0,str1,strlen(str1)); 
			if(g_Amount == 0) 
			{
				WriteFull_LCD(LINE1,Disp_Blank,strlen(Disp_Blank));
				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{
					WriteFull_LCD(LINE2,Disp_Blank,strlen(Disp_Blank));
					WriteFull_LCD(LINE3,Disp_Blank,strlen(Disp_Blank));
				}
			}
			else 
			{	   
				/*
				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())//�޸����������������Ϣ;by gzz 20121016
				{
					WriteFull_LCD(LINE1,Disp_Confirm[SYSPara.Language][2],strlen(Disp_Confirm[SYSPara.Language][2]));
					WriteFull_LCD(LINE2,Disp_Confirm[SYSPara.Language][3],strlen(Disp_Confirm[SYSPara.Language][3]));
				}
				else
				{
					WriteFull_LCD(LINE1,Disp_Confirm[SYSPara.Language][0],strlen(Disp_Confirm[SYSPara.Language][0]));
				}	
				*/
				WriteFull_LCD(LINE1,"",0);
				WriteFull_LCD(LINE2,"",0);
				WriteFull_LCD(LINE3,"",0);
			}	   
			SetCursorPost(LINE0+(strlen(Disp_ChInput[SYSPara.Language][0])+1)/2);					
			if(g_KeyStat.InputCnt < 2)
			{
				Cursor_On(LCDUP);
			}
			else
			{
				Cursor_Off(LCDUP);
			}	   
		}
    #endif
	
		if((g_Amount == 0) && (g_KeyStat.InputCnt >= 2)) 
		{
			state = MVC_CHAXUN; 		
		}
		//���ð�enterֱ�ӳ���;by gzz 20121114
		else if((g_Amount > 0) && (g_KeyStat.InputCnt >= 2)) 
		{		
			//Trace("\r\n try to xuanhuo,readksale=%d",sysVPMission.readySale);
			OSTimeDly(OS_TICKS_PER_SEC / 5);
			state = MVC_XUANHUO;			
		}
	}
	else //��δ���밴��
	{
	#if DISP_MODE == LCD_DISPLAY
		if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
		{
			//ClearScreen();
			Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
			Pitu_LCDPrintf(LINE23,40,Disp_ChInput[SYSPara.Language][0],strlen(Disp_ChInput[SYSPara.Language][0]),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE31,40,Disp_ChInput[1][0],strlen(Disp_ChInput[1][0]),0,0);
		}
		else
		{
			WriteFull_LCD(LINE0,Disp_ChInput[SYSPara.Language][0],strlen(Disp_ChInput[SYSPara.Language][0]));
			if(g_Amount == 0)
			{
				WriteFull_LCD(LINE1,Disp_Blank,strlen(Disp_Blank));
			} 
			
			else 
			{
				//
				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())//�޸����������������Ϣ;by gzz 20121016
				{
					//WriteFull_LCD(LINE1,Disp_Confirm[SYSPara.Language][2],strlen(Disp_Confirm[SYSPara.Language][2]));
					//WriteFull_LCD(LINE2,Disp_Confirm[SYSPara.Language][3],strlen(Disp_Confirm[SYSPara.Language][3]));
					WriteFull_LCD(LINE1,Disp_Blank,strlen(Disp_Blank));
					WriteFull_LCD(LINE2,Disp_Blank,strlen(Disp_Blank));
				}
				else
				{
					//WriteFull_LCD(LINE1,Disp_Confirm[SYSPara.Language][0],strlen(Disp_Confirm[SYSPara.Language][0]));
					WriteFull_LCD(LINE1,Disp_Blank,strlen(Disp_Blank));
				}	 
			}
			SetCursorPost(LINE0+(strlen(Disp_ChInput[SYSPara.Language][0])+1)/2);
			Cursor_On(LCDUP);
		}
	#endif
	}
	
	return state;
}


/*��ʾ�����������*/
void DispInputErrText(void)
{
	#if DISP_MODE == LCD_DISPLAY
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
		//����
		Pitu_LCDClearLine(LINE22,1,0);
		Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
		Pitu_LCDPrintf(LINE23,40,Disp_ChInput[SYSPara.Language][1],strlen(Disp_ChInput[SYSPara.Language][1]),0,0);
		if(SYSPara.Language != 1)
			Pitu_LCDPrintf(LINE31,40,Disp_ChInput[1][1],strlen(Disp_ChInput[1][1]),0,0);
		//OSTimeDly(OS_TICKS_PER_SEC);
	}
	else
	{
		WriteFull_LCD(LINE0,Disp_ChInput[SYSPara.Language][1],strlen(Disp_ChInput[SYSPara.Language][1]));
	    WriteFull_LCD(LINE1,Disp_ChInput[SYSPara.Language][2],strlen(Disp_ChInput[SYSPara.Language][2]));
		//���Ʒ;��Ļ�ļ���;by gzz 20121025
		if(IsLargeLCD())//�޸����������������Ϣ;by gzz 20121016
		{
			WriteFull_LCD(LINE2,"",0);//120920 by cq DebugModify
			WriteFull_LCD(LINE3,"",0);//120920 by cq DebugModify
		}
	}
	#endif
}

/*��ʾ�ȴ�Ͷ�ҵ�ҳ��*/
void DispSaleText(void)
{
#if DISP_MODE == LCD_DISPLAY
	char	str1[48];
	char	*pstr;
#endif
	
#if DISP_MODE == LCD_DISPLAY
	pstr = SprintDec(g_Amount,SYSPara.Decimal);
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		ClearScreen();
		//������ʾ
		if(SYSPara.Language != 1)
		{
			if(IsHaveSaled())
			{
				sprintf(str1,"      %s/%s",Disp_Deal[SYSPara.Language][0],Disp_Deal[1][0]);
			}
			else
			{
				sprintf(str1,"         %s/%s",Disp_Deal[SYSPara.Language][9],Disp_Deal[1][9]);
			}
		}
		else
		{
			if(IsHaveSaled())
			{
				sprintf(str1,"      %s",Disp_Deal[1][0]);
			}
			else
			{
				sprintf(str1,"         %s",Disp_Deal[1][9]);
			}
		}
		Pitu_LCDPrintf(LINE02,0,str1,strlen(str1),0,0);
		//���
		strcpy(str1, Disp_Deal[SYSPara.Language][8]);
		Pitu_LCDPrintf(LINE11,20,str1,strlen(str1),0,0);
		strcpy(str1, pstr);
		Pitu_LCDPrintf(LINE1,51,str1,strlen(str1),0,2);
		//����
		Pitu_LCDClearLine(LINE22,1,0);
		//������ʾ
		if(IsHaveSaled())
		{
			Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
			Pitu_LCDPrintf(LINE23,40,Disp_Deal[SYSPara.Language][11],strlen(Disp_Deal[SYSPara.Language][11]),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE31,40,Disp_Deal[1][11],strlen(Disp_Deal[1][11]),0,0);

			Pitu_LCDPrintf(LINE23,112,"��",strlen("��"),0,3);
			Pitu_LCDPrintf(LINE23,152,Disp_Deal[SYSPara.Language][12],strlen(Disp_Deal[SYSPara.Language][12]),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE31,152,Disp_Deal[1][12],strlen(Disp_Deal[1][12]),0,0);
		}
		else
		{
			Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
			Pitu_LCDPrintf(LINE23,40,Disp_Deal[SYSPara.Language][10],strlen(Disp_Deal[SYSPara.Language][10]),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE31,40,Disp_Deal[1][10],strlen(Disp_Deal[1][10]),0,0);
		}
	}
	else
	{
		if(IsHaveSaled())
		{
			strcpy(str1, Disp_Deal[SYSPara.Language][0]);
		}
		else
		{
			strcpy(str1, Disp_Deal[SYSPara.Language][9]);
		}		
		strcat(str1, pstr);

		WriteFull_LCD(LINE0,str1,strlen(str1));
		WriteFull_LCD(LINE1,Disp_ChInput[SYSPara.Language][0],strlen(Disp_ChInput[SYSPara.Language][0]));
		
		//���Ʒ;��Ļ�ļ���;by gzz 20121025
		if(IsLargeLCD())//�޸Ľ�����ʾ;by gzz 20121009
		{	
			/*
			WriteFull_LCD(LINE2,Disp_Deal[SYSPara.Language][6],strlen(Disp_Deal[SYSPara.Language][6])); 
			if(IsHaveSaled())
			{
				WriteFull_LCD(LINE3,Disp_Deal[SYSPara.Language][7],strlen(Disp_Deal[SYSPara.Language][7])); 
			}
			else
			{
				WriteFull_LCD(LINE3,"",0);//120920 by cq DebugModify
			}	
			*/
			WriteFull_LCD(LINE2,"",0);
			WriteFull_LCD(LINE3,"",0);
		}
		
	}
#endif
}



/*��ʾֽ�ҳ�������*/
void DispOverText(void)
{
#if DISP_MODE == LCD_DISPLAY	
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		//ClearScreen();
		Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
		Pitu_LCDPrintf(LINE23,40,Disp_Deal[SYSPara.Language][4],strlen(Disp_Deal[SYSPara.Language][4]),0,0);
		if(SYSPara.Language != 1)
			Pitu_LCDPrintf(LINE31,40,Disp_Deal[1][4],strlen(Disp_Deal[1][4]),0,0);
	}
	else
	{
	
		WriteFull_LCD((uint8_t)LINE0,Disp_Deal[SYSPara.Language][4],strlen(Disp_Deal[SYSPara.Language][4]));
		WriteFull_LCD((uint8_t)LINE1,Disp_Blank,strlen(Disp_Blank));
		//���Ʒ;��Ļ�ļ���;by gzz 20121025
		if(IsLargeLCD())//�޸����������������Ϣ;by gzz 20121016
		{
			WriteFull_LCD(LINE2,"",0);//120920 by cq DebugModify
			WriteFull_LCD(LINE3,"",0);//120920 by cq DebugModify
		}
	}
#endif
}


/*��ʾ�޻�*/
void DispWuhuoText(uint8_t x,uint8_t y)
{	
	#if DISP_MODE == LCD_DISPLAY
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		//ClearScreen();
		Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
		Pitu_LCDPrintf(LINE23,40,Disp_Deal[SYSPara.Language][3],strlen(Disp_Deal[SYSPara.Language][3]),0,0);
		if(SYSPara.Language != 1)
			Pitu_LCDPrintf(LINE31,40,Disp_Deal[1][3],strlen(Disp_Deal[1][3]),0,0);
	}
	else
	{
		//   ClearScreen();			 
		WriteFull_LCD(LINE0,Disp_Deal[SYSPara.Language][3],strlen(Disp_Deal[SYSPara.Language][3]));
		WriteFull_LCD(LINE1,Disp_ChInput[SYSPara.Language][2],strlen(Disp_ChInput[SYSPara.Language][2]));
		//���Ʒ;��Ļ�ļ���;by gzz 20121025
		if(IsLargeLCD())//�޸����������������Ϣ;by gzz 20121016
		{
			WriteFull_LCD(LINE2,"",0);//120920 by cq DebugModify
			WriteFull_LCD(LINE3,"",0);//120920 by cq DebugModify
		}
	}
	#endif
}

/*��ʾ���ڳ���*/
void DispChuhuoText(void)
{
	#if DISP_MODE == LCD_DISPLAY	
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
		Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
		Pitu_LCDPrintf(LINE23,40,Disp_GoodsOut[SYSPara.Language][0],strlen(Disp_GoodsOut[SYSPara.Language][0]),0,0);
		if(SYSPara.Language != 1)
			Pitu_LCDPrintf(LINE31,40,Disp_GoodsOut[1][0],strlen(Disp_GoodsOut[1][0]),0,0);
	}
	else
	{	    
	    WriteFull_LCD(LINE0,Disp_Wait[SYSPara.Language][0],strlen(Disp_Wait[SYSPara.Language][0]));
		WriteFull_LCD(LINE1,Disp_GoodsOut[SYSPara.Language][0],strlen(Disp_GoodsOut[SYSPara.Language][0]));
		//���Ʒ;��Ļ�ļ���;by gzz 20121025
		if(IsLargeLCD())//�޸����������������Ϣ;by gzz 20121016
		{
			WriteFull_LCD(LINE2,"",0);//120920 by cq DebugModify
			WriteFull_LCD(LINE3,"",0);//120920 by cq DebugModify
		}
	}
    #endif 
}

/*���ͽ��ճ�����Ϣ������������*/
/*���� ch:�ͻ�����Ļ������*/
/*���� x:������� y:�����к�*/
/*����ֵ ����״̬*/
uint8_t DoChuhuoMsg(uint8_t ch,uint8_t x,uint8_t y)
{
	uint8_t state,err,statusDisp=0;
	uint32_t  *pComStatus;

	//121019 by cq Cashless
	uint8_t cVendSuccessFlag = 0;
	
#if DRVDEVICE
	//�������루32λ�������λ��1����EVB�������ֽ�Ϊ������룬����Ϊͨ����
	OSMboxAccept(g_CommBackMsg);
	MsgBack.CmdType = ch + ((uint32_t)CMD_GOODS_OUT << 24); 
	OSMboxPost(g_CommMsg,&MsgBack.CmdType);//֪ͨϵͳ�г��������

	pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC * 20,&err);//֪ͨϵͳ������ɺ����ķ�������(�������еĳ����������һ���ǳɹ�)
	//�ȴ���������
	if(err == OS_NO_ERR) 
	{				//�������	

	    /*********GOC�򿪵������********************/
		if(SYSPara.GOCCtr > 0)
		{
			 //1.�ж�GOC�Ƿ����bit7:
			 if( BeSaleStat() &&(*pComStatus & DRV_GOCERR_BIT) )
			 {
			 	//GOC����->��Ǯ��Ȼ��goc������
				statusDisp=1;
			 } 
			 else 
			 {
			 	//GOC��Ϊ����
				
				//2.���ж�GOC�Ƿ��⵽bit5�������ڽ���״̬:					
                if(BeSaleStat() && ((*pComStatus & GOODS_NOTPASS_BIT) == 0)) 
			   	{
					statusDisp = 1;
						
				}		            
	            else
	            { 
	                   statusDisp = 0;
	            }
				
			 }
		}
		/*********GOC�رյ������********************/
		else
		{
			//1�ܽ���״̬Ϊ0�������ڽ���״̬ 
			if( BeSaleStat() && (*pComStatus == 0) )
	        {
				//��Ǯ  
				statusDisp = 1;
					
			}	
	        else
	        {
	           	   statusDisp = 0;
	          
	        } 
		}
		if(statusDisp == 0)
		{
			 //��ʾ��������
	       #if DISP_MODE == LCD_DISPLAY
		   	   if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
			   {
					//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
					Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
					Pitu_LCDPrintf(LINE23,40,Disp_Fault[SYSPara.Language][2],strlen(Disp_Fault[SYSPara.Language][2]),0,0);
					if(SYSPara.Language != 1)
						Pitu_LCDPrintf(LINE31,40,Disp_Fault[1][2],strlen(Disp_Fault[1][2]),0,0);
					OSTimeDly(OS_TICKS_PER_SEC * 2);
			   }
			   else
			   {	
			   		WriteFull_LCD(LINE0,Disp_Fault[SYSPara.Language][2],strlen(Disp_Fault[SYSPara.Language][2]));
			   		WriteFull_LCD(LINE1,Disp_Blank,strlen(Disp_Blank));	
			   }
		   #endif
		   //���ñ��ν���Ϊ���ʽ���
		   if(*pComStatus & DRV_ERR_MASK) 
		   {
			   SetDoubtTrans();
		   }
		}
		else
		{   

		   Trace("\r\n SYSPara.GOCCtr = %x, *pComStatus & MOTO_NOTRETURN_BIT = %x",SYSPara.GOCCtr,(*pComStatus & MOTO_NOTRETURN_BIT));
		   Trace("\r\n (*pComStatus & GOODS_NOTPASS_BIT) == 0 = %x",((*pComStatus & GOODS_NOTPASS_BIT) == 0));
	   
		   g_Amount -= Channels[x][y].GoodsPrice;					  
	  #if DISP_MODE == LCD_DISPLAY		
	  	  if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
		  {
			//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
			Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
			Pitu_LCDPrintf(LINE23,40,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE31,40,Disp_GoodsOut[1][1],strlen(Disp_GoodsOut[1][1]),0,0);
		  }
		  else
		  {
		 	 WriteFull_LCD(LINE1,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]));
		  }
      #endif 	  

		  //120914 by cq Cashless
		  if( (SYSPara.ReaderEnable)&&(Reader_GetFundsMultiplyUnit()>0) )
		  {
			   cVendSuccessFlag = 1;//121019 by cq Cashless
			  Vmc_PostToReader(VTR_VEND_SUCCESS); 
			  //121013 by cq Cashless
			  state = MVC_RETRANS;//121019 by cq Cashless
			  return state;
		  }  
	    }	
	   /*	
	   //����Ϊ��
	   if(*pComStatus & GOODS_SOLDOUT_BIT) 
	   {
		   state = MVC_WUHUO;
	   } 
	   //��Ʒ��������
	   else if(*pComStatus > 0) 
	   {
		   //��ʾ��������
       #if DISP_MODE == LCD_DISPLAY
	   	   if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
		   {
				//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
				Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
				Pitu_LCDPrintf(LINE23,40,Disp_Fault[SYSPara.Language][2],strlen(Disp_Fault[SYSPara.Language][2]),0,0);
				if(SYSPara.Language != 1)
					Pitu_LCDPrintf(LINE31,40,Disp_Fault[1][2],strlen(Disp_Fault[1][2]),0,0);
				OSTimeDly(OS_TICKS_PER_SEC * 2);
		   }
		   else
		   {	
		   		WriteFull_LCD(LINE0,Disp_Fault[SYSPara.Language][2],strlen(Disp_Fault[SYSPara.Language][2]));
		   		WriteFull_LCD(LINE1,Disp_Blank,strlen(Disp_Blank));	
		   }
	   #endif


		   //���ݹ��ϵķ����������Щ���ϻ��ǻ��Ǯ��
	   #if DRV_TYPE == DRV_64
		   //120920 by cq DebugModify
		   
		   if(((SYSPara.GOCCtr == 0) && ((*pComStatus & MOTO_NOTRETURN_BIT) == 0)) 
			  || ((SYSPara.GOCCtr > 0) && ((*pComStatus & GOODS_NOTPASS_BIT) == 0)&& ((*pComStatus & MOTO_NOTRETURN_BIT) == 0)))
		   {
	   #elif DRV_TYPE == DRV_12
		   if(*pComStatus & MOTO_NOTRETURN_BIT) 
		   {
	   #endif

			   Trace("\r\n SYSPara.GOCCtr = %x, *pComStatus & MOTO_NOTRETURN_BIT = %x",SYSPara.GOCCtr,(*pComStatus & MOTO_NOTRETURN_BIT));
			   Trace("\r\n (*pComStatus & GOODS_NOTPASS_BIT) == 0 = %x",((*pComStatus & GOODS_NOTPASS_BIT) == 0));
		   
			   g_Amount -= Channels[x][y].GoodsPrice;
		   #if DISP_MODE == LCD_DISPLAY		
		   		if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
				{
					//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
					Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
					Pitu_LCDPrintf(LINE23,40,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]),0,0);
					if(SYSPara.Language != 1)
						Pitu_LCDPrintf(LINE31,40,Disp_GoodsOut[1][1],strlen(Disp_GoodsOut[1][1]),0,0);
				}
				else
				{
			   		WriteFull_LCD(LINE1,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]));		
				}
           #endif 	

			   //120914 by cq Cashless
			   if( (SYSPara.ReaderEnable)&&(Reader_GetFundsMultiplyUnit()>0) )
			   {
					cVendSuccessFlag = 1;//121019 by cq Cashless
				   Vmc_PostToReader(VTR_VEND_SUCCESS); 
				   //121013 by cq Cashless
				   state = MVC_RETRANS;//121019 by cq Cashless
				   return state;
			   }
		   }

		   //���ñ��ν���Ϊ���ʽ���
		   if(*pComStatus & DRV_ERR_MASK) 
		   {
			   SetDoubtTrans();
		   }
	   } 
	   //�����ɹ�	
	   else 
	   {														
		  //		
		  g_Amount -= Channels[x][y].GoodsPrice;					  
	  #if DISP_MODE == LCD_DISPLAY		
	  	  if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
		  {
			//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
			Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
			Pitu_LCDPrintf(LINE23,40,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE31,40,Disp_GoodsOut[1][1],strlen(Disp_GoodsOut[1][1]),0,0);
		  }
		  else
		  {
		 	 WriteFull_LCD(LINE1,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]));
		  }
      #endif 	  

		  //120914 by cq Cashless
		  if( (SYSPara.ReaderEnable)&&(Reader_GetFundsMultiplyUnit()>0) )
		  {
			   cVendSuccessFlag = 1;//121019 by cq Cashless
			  Vmc_PostToReader(VTR_VEND_SUCCESS); 
			  //121013 by cq Cashless
			  state = MVC_RETRANS;//121019 by cq Cashless
			  return state;
		  }
	   }		  
	   */	
	   //120622 by cq WaitOutGoods
	   //OSTimeDly(OS_TICKS_PER_SEC * 2);				   
	   OSTimeDly(OS_TICKS_PER_SEC);


	   //���������󣬸��ݱ��ε�״̬���Լ�����һЩ�������л�����һ��״̬
	   if(*pComStatus & GOODS_SOLDOUT_BIT) 
	   {
		   state = MVC_WUHUO;
	   } 
	   else if((g_Amount == 0) || (g_Amount < SYSPara.MoneyMinLeft) || (SYSPara.TransMultiMode == 0)) 
	   {
		   state = MVC_PAYOUT;
	   }
	   else 
	   {
		   state = MVC_RETRANS;
	   }
	}
	//��ʱ��˵��û�г����ɹ�   
	else 
	{
	   SetDoubtTrans(); //��ʱ��˵��û�г����ɹ������ó����ʽ���  
	   state = MVC_PAYOUT;
	}  //�������
	

	//�������ȷ�ϰ��й��ϣ����еĲ���
	if((GetDevStatus() & DEV_ERR_BIT_DRVCOMM) == 0) 
	{	
/**************************************************************/																								
	#if DRV_TYPE == DRV_12
		//�������루32λ�������λ��1����EVB�������ֽ�Ϊ������룬����Ϊͨ����
		OSMboxAccept(g_CommBackMsg);
		MsgBack.CmdType = ch + ((uint32_t)CMD_GOODS_CHECK << 24);			
		OSMboxPost(g_CommMsg,&MsgBack.CmdType); 			//��ѯ����״̬
		
		pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC * 2,&err);
	#endif
/*************************************************************/
	}
#endif

	//120914 by cq Cashless
	if( (SYSPara.ReaderEnable)&&(Reader_GetFundsMultiplyUnit()>0) )
	{		
		//121019 by cq Cashless
		//if(state != MVC_SALE)
		if(cVendSuccessFlag == 0)
		{
			Vmc_PostToReader(VTR_VEND_FAILURE);
			//121019 by cq Cashless
			state = MVC_RETRANS;
			return state;
		}
	}

	return state;
}


/*��ʾ�Ƿ��������*/
void DispRetransText(void)
{ 
	#if DISP_MODE == LCD_DISPLAY
	WriteFull_LCD(LINE0,Disp_Deal[SYSPara.Language][2],strlen(Disp_Deal[SYSPara.Language][2]));
	WriteFull_LCD(LINE1,Disp_Confirm[SYSPara.Language][0],strlen(Disp_Confirm[SYSPara.Language][0]));
	#endif
}

/*��ʾǮ����*/
void DispLessText(uint32_t	GoodsPrice)
{	   
	char    *pstr;
	char	str2[48];
	
	#if DISP_MODE == LCD_DISPLAY
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		pstr = SprintDec(GoodsPrice,SYSPara.Decimal);	    	
	    strcpy(str2, Disp_Deal[SYSPara.Language][1]);
		strcat(str2, Disp_ChnPara[SYSPara.Language][1]);
		strcat(str2, pstr);
		//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
		Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
		Pitu_LCDPrintf(LINE23,40,str2,strlen(str2),0,0);
		if(SYSPara.Language != 1)
			Pitu_LCDPrintf(LINE31,40,Disp_Deal[1][1],strlen(Disp_Deal[1][1]),0,0);
		OSTimeDly(OS_TICKS_PER_SEC*2);
	}
	else
	{
		WriteFull_LCD(LINE0,Disp_Deal[SYSPara.Language][1],strlen(Disp_Deal[SYSPara.Language][1]));
		//WriteFull_LCD(LINE1,Disp_Confirm[SYSPara.Language][0],strlen(Disp_Confirm[SYSPara.Language][0]));
	}
	#endif	
}

/*�ڽ���״̬�£���ʾ��Ǯ״̬��ҳ��*/
/*���� x:������� y:�����к�*/
/*����ֵ ����״̬*/
uint8_t DispAddMoneyText(uint8_t x,uint8_t y)
{
    #if DISP_MODE == LCD_DISPLAY
	char	str1[48];
	char    *pstr;
	#endif

	uint8_t state = MVC_ADDMONEY;;

	#if DISP_MODE == LCD_DISPLAY
	pstr = SprintDec(g_Amount,SYSPara.Decimal);
	strcpy(str1, Disp_Deal[SYSPara.Language][0]);
	strcat(str1, pstr);

	WriteFull_LCD(LINE0,str1,strlen(str1));
	WriteFull_LCD(LINE1,Disp_ChInput[SYSPara.Language][0],strlen(Disp_ChInput[SYSPara.Language][0]));
	#endif
	
	if(g_Amount >= Channels[x][y].GoodsPrice) 
	{		
	    //state = CHUHUO;	
		state = MVC_INPUT;									    	
	}
	return state;
}

/*��ʾ��������*/
void DispPayoutText(void)
{
#if DISP_MODE == LCD_DISPLAY
	char	str2[48];
	char	*pstr;
#endif
	
	if(g_Amount > 0) 
	{					
    #if DISP_MODE == LCD_DISPLAY
		pstr = SprintDec(g_Amount,SYSPara.Decimal);
		strcpy(str2, Disp_Change[SYSPara.Language][1]);
		strcat(str2, pstr);

		if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
		{
			Pitu_LCDClearLine(LINE1,0,2);
			Pitu_LCDPrintf(LINE11,20,Disp_Deal[SYSPara.Language][8],strlen(Disp_Deal[SYSPara.Language][8]),0,0);
			pstr = SprintDec(0,SYSPara.Decimal);
			Pitu_LCDPrintf(LINE1,51,pstr,strlen(pstr),0,2);
			//ClearScreen();
			Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
			Pitu_LCDPrintf(LINE23,40,Disp_Change[SYSPara.Language][1],strlen(Disp_Change[SYSPara.Language][1]),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE31,40,Disp_Change[1][1],strlen(Disp_Change[1][1]),0,0);					
		}
		else
		{
			WriteFull_LCD(LINE0,Disp_Blank,strlen(Disp_Blank));
			WriteFull_LCD(LINE1,str2,strlen(str2)); 
			//���Ʒ;��Ļ�ļ���;by gzz 20121025
			if(IsLargeLCD())
			{			
				WriteFull_LCD(LINE2,"",0);
				WriteFull_LCD(LINE3,"",0);//120920 by cq DebugModify
			}
		}
		#endif
	}	
}


/*���ͽ���Coin������Ϣ����MDB�������*/
void DoCoinOutMsg(void)
{
    uint8_t err;
	uint32_t  *pComStatus;
	
	#if COINDEVICE	  
	if((SYSPara.CoinEnable == MDB_COIN_EN) && (g_Amount > 0)
	   && ((SYSPara1.CoinsStat & (~COIN_FULL_BIT)) == COIN_STAT_OK))
	{
		OSMboxAccept(g_CommBackMsg);
		MsgBack.CmdType = ((uint32_t)CMD_COIN_CHANGE << 24) + g_Amount;
		OSMboxPost(g_CommMsg,&MsgBack.CmdType);	   //����ָ��						
		
		pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC*(g_Amount/g_CoinMinValue/2+35),&err);//����������
		//�ȴ��������//MDBӲ��������
		if(err == OS_NO_ERR) 
		{	 								     		 						    	 							
		
		   if(SYSPara1.CoinsStat != COIN_STAT_OK) //Ӳ�������ϣ���Ϊ���ʽ���
		   {
			  SetDoubtTrans();
		   }
		   if(g_Amount >= *pComStatus) 
		   {
		      g_Amount -= *pComStatus;						  	
		   } 
		   else if(*pComStatus > g_Amount)
		   {
		      g_Amount = 0;
		   }
		   ChgAmount += *pComStatus;		   				       						
		} 
		//��ʱ��˵��û�г��ҳɹ�   
		else 
		{
		   SetDoubtTrans();//��ʱ��˵��û�г��ҳɹ�����Ϊ���ʽ���  
		}									//MDBӲ��������						
	}
	#endif 
}

/*����ѹ��������Ϣ*/
void DoNoteStackMsg(void)
{
    uint8_t err;
	
	OSMboxAccept(g_CommBackMsg);
	MsgBack.CmdType =  ((uint32_t)CMD_NOTE_STACK << 24);
	OSMboxPost(g_CommMsg,&MsgBack.CmdType);//����ѹ������
	OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC*15,&err);//�ȴ�ѹ�����
}

/*�����ݴ�ֽ���˳�������Ϣ*/
void DoNoteReturnMsg(void)  
{
    uint8_t err,moneych;
	uint32_t  *pComStatus;
	
	OSMboxAccept(g_CommBackMsg);
	MsgBack.CmdType =  ((uint32_t)CMD_NOTE_RETURN << 24);//�����˳�����
	OSMboxPost(g_CommMsg,&MsgBack.CmdType);
	pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC*15,&err);//�ȴ��˱ҽ��
	if(err == OS_NO_ERR) 
	{
	    moneych = *pComStatus;	    
		if(g_Amount >= SYSPara.BillValue[moneych])	
		{
		    ChgAmount += SYSPara.BillValue[moneych];
			g_Amount -= SYSPara.BillValue[moneych];
		} 
		else 
		{
		    ChgAmount += g_Amount;
			g_Amount = 0;
		}
	}
}

/*��������������Ϣ*/
void DoPayOutMsg(void)  
{
    uint8_t err;
	uint32_t  *pComStatus;
	
	if(g_Amount > 0) 
	{
		OSMboxAccept(g_CommBackMsg);
		MsgBack.CmdType = ((uint32_t)CMD_COIN_CHANGE << 24) + g_Amount;
		OSMboxPost(g_CommMsg,&MsgBack.CmdType);	   //����ָ��						
		
		pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC*(g_Amount/g_CoinMinValue/2+60),&err);
		//�ȴ��������
		if(err == OS_NO_ERR) 
		{	 			//MDBӲ��������					     		 						    	 							
		   if(g_Amount >= *pComStatus) 
		   {
		      g_Amount -= *pComStatus;						  	
		   } 
		   else if(*pComStatus > g_Amount) 
		   {
		      g_Amount = 0;
		   }
		   ChgAmount += *pComStatus;		   				       						
		}
	}
}

/*���ͽ���Hopper����������Ϣ,��hopper�������*/
/*����ֵ ����״̬*/
uint8_t DoHopperOutMsg(void)
{
    uint8_t   state,i,j,pNum,err;
	uint32_t  ChangeBase;
	uint32_t  *pComStatus;
	
	#if HOPPERDEVICE  //����
	state = 0;						   				
	if(SYSPara.ChangerEnable == HOPPER_CHANGER_EN) 
	{
		for(i = HOPPERCHMAX; (g_Amount>0)&&(i>0); i--) 
		{           
			//ChangeBase = SYSPara.ChangeValue[i-1];
			//j = i-1;
			ChangeBase = HopperPara[i-1].Value;
			j = HopperPara[i-1].Channel;
			
			if((ChangeBase > 0) && ((SYSPara1.HopperStat[j] & HOPPER_ERR_MASK) == 0)) 
			{
				pNum = g_Amount / ChangeBase;
				if(pNum > 0) 
				{
					state |= 1 << j;
					//�������루32λ�������λ��1����EVB�������ֽ�Ϊ������룬������4λΪhopper�ţ�����20λΪ����ֵ
					OSMboxAccept(g_CommBackMsg);
					MsgBack.CmdType =  (pNum * ChangeBase) + ((uint32_t)CMD_HOPPER_CHANGE << 24) + ((uint32_t)j << 20);
			        OSMboxPost(g_CommMsg,&MsgBack.CmdType);	   //����ָ��				
			
			        pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC*(pNum/4+35),&err);
			
					if(err == OS_NO_ERR) 
					{	   			//Hopper����
					   //HopperͨѶ����
					   if(SYSPara1.HopperStat[j] & HOPPER_COMMERR_BIT) 
					   {
				          //�豸����
						  SetDoubtTrans();
						 //  break;
			           }
					   if(g_Amount >= *pComStatus) 
					   {
				          g_Amount -= *pComStatus;
						  if((SYSPara1.HopperStat[j] & (~HOPPER_INSUFFICIENT_BIT)) == 0) 
						  {
						      state &= ~(1 << j);
						  }
					   } 
					   else if(*pComStatus > g_Amount)
					   {
					      g_Amount = 0;
					   }
					   ChgAmount += *pComStatus;
				    }
					//��ʱ������ʧ�ܣ���Ҫ���ó����ʽ���
					else 
				    {
					   SetDoubtTrans();
					  // break;
					} //Hopper����
			    }		  
			}
		}
	}				 
	#endif
	return state;
}

/*��ʾǷ�ѣ�������ʧ��*/
void DispIOUText(void)
{
    #if DISP_MODE == LCD_DISPLAY
  	char	str2[48];
	char    *pstr;
	#endif
	
	#if DISP_MODE == LCD_DISPLAY
	pstr = SprintDec(g_Amount,SYSPara.Decimal);						
	strcpy(str2, Disp_Change[SYSPara.Language][3]);
	strcat(str2, pstr);

	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		//ClearScreen();
		Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
		if(CashState.ChangerState & CHANGER_LOW) 
		{		    
			Pitu_LCDPrintf(LINE23,40,Disp_Change[SYSPara.Language][2],strlen(Disp_Change[SYSPara.Language][2]),0,0);
		}
		else
		{		
			strcat(str2, Disp_Change[SYSPara.Language][5]);
			Pitu_LCDPrintf(LINE23,40,str2,strlen(str2),0,0);
		}			

		if(SYSPara.Language != 1)		
			Pitu_LCDPrintf(LINE31,40,Disp_Change[1][5],strlen(Disp_Change[1][5]),0,0);	
		OSTimeDly(OS_TICKS_PER_SEC);
	}
	else
	{						
		if(CashState.ChangerState & CHANGER_LOW) 
		{
		    WriteFull_LCD(LINE0,Disp_Change[SYSPara.Language][2],strlen(Disp_Change[SYSPara.Language][2]));
		}
		else
		{
		    WriteFull_LCD(LINE0,Disp_Change[SYSPara.Language][5],strlen(Disp_Change[SYSPara.Language][5]));
		}
		WriteFull_LCD(LINE1,str2,strlen(str2));
	}
	#endif
}

/*��ʾ��ȡ��Ǯ*/
void DispChangeText(void)
{
	#if DISP_MODE == LCD_DISPLAY
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		//ClearScreen();
		Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
		Pitu_LCDPrintf(LINE23,40,Disp_Change[SYSPara.Language][0],strlen(Disp_Change[SYSPara.Language][0]),0,0);
		if(SYSPara.Language != 1)
			Pitu_LCDPrintf(LINE31,40,Disp_Change[1][0],strlen(Disp_Change[1][0]),0,0);					
	}
	else
	{
		WriteFull_LCD(LINE0,Disp_Change[SYSPara.Language][0],strlen(Disp_Change[SYSPara.Language][0]));
		OSTimeDly(OS_TICKS_PER_SEC);
	}
	#endif
}

/*��ʾ���׽���*/
void DispEndText(void)
{
    #if DISP_MODE == LCD_DISPLAY
	if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
	{
		ClearScreen();	
		/*
		//Trace("\r\n now end=%d",SYSPara.Language);
		if(SYSPara.Language==0)
		{
			//Trace("\r\n1");
			Pitu_LCDPutPicBmp(1);
		}
		else
		*/
		{
			//Trace("\r\2");
			Pitu_LCDPutLOGOBmp(LINE0,75,SYSPara.LogoSel);
			Pitu_LCDPrintf(LINE11,32,Disp_End[1][0],strlen(Disp_End[1][0]),0,3);
			//Pitu_LCDPrintf(LINE21,16,Disp_End[SYSPara.Language][1],strlen(Disp_End[SYSPara.Language][1]),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE23,32,Disp_End[SYSPara.Language][2],strlen(Disp_End[SYSPara.Language][2]),0,0);			
		}
		OSTimeDly(OS_TICKS_PER_SEC * 2);
		
	}
	else
	{
		WriteFull_LCD(LINE0,Disp_End[SYSPara.Language][0],strlen(Disp_End[SYSPara.Language][0]));
		WriteFull_LCD(LINE1,Disp_Blank,strlen(Disp_Blank));
	}
	#endif
}

/*��ʱ����������Ϣ������ѯ����豸*/
void DoDingshiMsg(void)
{
    uint8_t err;

	//��Ӳ������Ϊmdbʱ��ֻ��ȱ�Ҳ��Լ�;by gzz 20121031
	//121106 by cq BillSingleWork
	if(isBillSingleWork())
	{
		//do nothing
	}
	else if(SYSPara.ChangerEnable==MDB_CHANGER_EN)
	{
	    /*��Ҳ���ʱ����ʱ���������*/
		if(CashState.ChangerState & CHANGER_LOW) 
		{			
			OSMboxAccept(g_CommBackMsg);
			MsgBack.CmdType = ((uint32_t)CMD_COIN_CHANGE << 24);
			OSMboxPost(g_CommMsg,&MsgBack.CmdType);	   //����ָ��						
			
			OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC*10,&err);
		} 
	}
	else if(SYSPara.ChangerEnable==HOPPER_CHANGER_EN)
	{
	    //��Ҫһֱ�Լ�1Ԫ�ıҶ���û�գ�û��ʱ����1Ԫ����
		//if(CashState.ChangerState & CHANGER_LOW) 
		if(g_Amount == 0)//ֻ���ڿ���״̬���Լ�
		{			
			OSMboxAccept(g_CommBackMsg);
			MsgBack.CmdType = ((uint32_t)CMD_COIN_CHANGE << 24);
			OSMboxPost(g_CommMsg,&MsgBack.CmdType);	   //����ָ��						
			
			OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC*10,&err);
		} 
	}

	/*���������ʱ����ʱ��������*/
	#if DRV_TYPE == DRV_64
	if(GetDevStatus() & (DEV_ERR_BIT_GOODSCHK|DEV_ERR_BIT_DRVCOMM)) 
	{
	#elif DRV_TYPE == DRV_12
	if(GetDevStatus() & DEV_ERR_BIT_DRVCOMM) 
	{
	#endif
	
	#if DRVDEVICE							  
	//�������루32λ�������λ��1����EVB�������ֽ�Ϊ������룬����Ϊͨ����
	OSMboxAccept(g_CommBackMsg);
	MsgBack.CmdType = 11 + ((uint32_t)CMD_GOODS_CHECK << 24); 
	OSMboxPost(g_CommMsg,&MsgBack.CmdType);
	
	OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC * 5,&err); 
	#endif   
	}
}



/*��ʾ��PCҪ������*/
void Disp_VP_CMD_PayoutText(uint32_t CurrentChg)  
{
    #if DISP_MODE == LCD_DISPLAY
  	char	str2[48];
	char    *pstr;
	#endif
	   
	if(CurrentChg > 0) 
	{					
	    #if DISP_MODE == LCD_DISPLAY
		pstr = SprintDec(CurrentChg,SYSPara.Decimal);
		strcpy(str2, Disp_Change[SYSPara.Language][1]);
	    strcat(str2, pstr);
	
	    WriteFull_LCD(LINE0,Disp_Blank,strlen(Disp_Blank));
		WriteFull_LCD(LINE1,str2,strlen(str2));					    
		#endif
    }	
}	



/*��PCҪ��������������Ϣ*/
void Do_VP_CMD_PayoutMsg(uint32_t CurrentChg)  
{
    uint8_t err;
	uint32_t  *pComStatus;
	
	if(CurrentChg > 0) 
	{		
		OSMboxAccept(g_CommBackMsg);
		MsgBack.CmdType = ((uint32_t)CMD_COIN_CHANGE << 24) + CurrentChg;
		OSMboxPost(g_CommMsg,&MsgBack.CmdType);	   //����ָ��						
		
		pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC*(CurrentChg/g_CoinMinValue/2+60),&err);
		//�ȴ��������
		if(err == OS_NO_ERR) 
		{	 			//MDBӲ��������					     		 						    	 							
		   if(CurrentChg >= *pComStatus) 
		   {
		      CurrentChg -= *pComStatus;						  	
		   } 
		   else if(*pComStatus > sysVPMission.changeMoney) 
		   {
		      CurrentChg = 0;
		   }
		   //sysVPMission.changeMoney += *pComStatus;		   				       						
		}
		if(SYSPara.Decimal==1)
	    {			
			sysVPMission.changeMoney = CurrentChg * 10;
	    }
	    else if(SYSPara.Decimal==2)
	    {			
			sysVPMission.changeMoney = CurrentChg;
	    }	
	}	
}



/*��ʾ��PCҪ�������Ƿ�ѣ�������ʧ��*/
void Disp_VP_CMD_Payout_IOUText(void)
{
    #if DISP_MODE == LCD_DISPLAY
  	char	str2[48];
	char    *pstr;
	#endif
	
	#if DISP_MODE == LCD_DISPLAY
	pstr = SprintDec(sysVPMission.changeMoney,SYSPara.Decimal);						
	strcpy(str2, Disp_Change[SYSPara.Language][3]);
	strcat(str2, pstr);
	   						
	if(CashState.ChangerState & CHANGER_LOW) 
	{
	    WriteFull_LCD(LINE0,Disp_Change[SYSPara.Language][2],strlen(Disp_Change[SYSPara.Language][2]));
	}
	else
	{
	    WriteFull_LCD(LINE0,Disp_Change[SYSPara.Language][5],strlen(Disp_Change[SYSPara.Language][5]));
	}
	WriteFull_LCD(LINE1,str2,strlen(str2));
	#endif
}

/*���ͽ��ճ�����Ϣ������������*/
/*���� ch:�ͻ�����Ļ������*/
/*���� x:������� y:�����к�*/
/*����ֵ ����״̬*/
uint8_t Do_VP_CMD_ChuhuoMsg(uint8_t ch,uint8_t x,uint8_t y)
{
    uint8_t state,err;
	uint32_t  *pComStatus;

	
	Trace(" \r\nDo_VP_CMD_ChuhuoMsg");
	
	#if DRVDEVICE
	sysVPMission.vendCmd = 1;
	//�������루32λ�������λ��1����EVB�������ֽ�Ϊ������룬����Ϊͨ����
	OSMboxAccept(g_CommBackMsg);

	Trace("\r\nch= %u",ch);
	
	MsgBack.CmdType = ch + ((uint32_t)CMD_GOODS_OUT << 24); 
    OSMboxPost(g_CommMsg,&MsgBack.CmdType);//֪ͨϵͳ�г��������

    pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC * 20,&err);//֪ͨϵͳ������ɺ����ķ�������(�������еĳ����������һ���ǳɹ�)
    sysVPMission.vendCmd = 0;
    //�ȴ���������
    if(err == OS_NO_ERR) 
	{	 			//�������	
	   //����Ϊ��
	   if(*pComStatus & GOODS_SOLDOUT_BIT) 
	   {
	       state = MVC_WUHUO;
	   } 
	   //��Ʒ��������
	   else if(*pComStatus > 0) 
	   {
	       //��ʾ��������
	       #if DISP_MODE == LCD_DISPLAY
		   WriteFull_LCD(LINE0,Disp_Fault[SYSPara.Language][2],strlen(Disp_Fault[SYSPara.Language][2]));
		   WriteFull_LCD(LINE1,Disp_Blank,strlen(Disp_Blank));					   
		   #endif

           //���ݹ��ϵķ����������Щ���ϻ��ǻ��Ǯ��
		   #if DRV_TYPE == DRV_64
		   if(((SYSPara.GOCCtr == 0) && (*pComStatus & MOTO_NOTRETURN_BIT)) 
		      || ((SYSPara.GOCCtr > 0) && ((*pComStatus & GOODS_NOTPASS_BIT) == 0)))
		   {
		   #elif DRV_TYPE == DRV_12
		   if(*pComStatus & MOTO_NOTRETURN_BIT) 
		   {
		   #endif
			   if(SYSPara.Decimal==1)
			   {
					g_Amount -= sysVPMission.vendCost/10;
			   }
			   else if(SYSPara.Decimal==2)
			   {
					g_Amount -= sysVPMission.vendCost;
			   }			   	   	
		       #if DISP_MODE == LCD_DISPLAY	
			   if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
			  {
				//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
				Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
				Pitu_LCDPrintf(LINE23,40,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]),0,0);
				if(SYSPara.Language != 1)
					Pitu_LCDPrintf(LINE31,40,Disp_GoodsOut[1][1],strlen(Disp_GoodsOut[1][1]),0,0);
			  }
			  else
			  {
               	WriteFull_LCD(LINE1,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]));	
			  }
               #endif 	  
		   }
		   VPMsgPackSend( VP_NAK_RPT, 0, 0  );
	   } 
	   //�����ɹ�   
	   else 
	   { 			          			 					 	
 		  //	
 		  if(SYSPara.Decimal==1)
		  {
				g_Amount -= sysVPMission.vendCost/10;
		  }
		  else if(SYSPara.Decimal==2)
		  {
				g_Amount -= sysVPMission.vendCost;
		  }
          #if DISP_MODE == LCD_DISPLAY		
		  if(SYSPara.LCDSel==2)//ƴͼ��Ļ��ʽ;by gzz 20121106
		  {
			//ClearScreen();//ƴͼ��Ļ��ʽ;by gzz 20121106
			Pitu_LCDPrintf(LINE23,0,"��",strlen("��"),0,3);
			Pitu_LCDPrintf(LINE23,40,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]),0,0);
			if(SYSPara.Language != 1)
				Pitu_LCDPrintf(LINE31,40,Disp_GoodsOut[1][1],strlen(Disp_GoodsOut[1][1]),0,0);
		  }
		  else
		  {
	      	WriteFull_LCD(LINE1,Disp_GoodsOut[SYSPara.Language][1],strlen(Disp_GoodsOut[SYSPara.Language][1]));
		  }
	      #endif 	
		  VPMsgPackSend( VP_ACK_RPT, 0, 0  );
	   }	       

	   OSTimeDly(OS_TICKS_PER_SEC * 2);
	   //���������󣬸��ݱ��ε�״̬���Լ�����һЩ�������л�����һ��״̬
	   if(*pComStatus & GOODS_SOLDOUT_BIT) 
	   {
	       state = MVC_WUHUO;
	   } 
	   else if((g_Amount == 0) || (g_Amount < SYSPara.MoneyMinLeft) || (SYSPara.TransMultiMode == 0)) 
	   {
	       state = MVC_PAYOUT;
	   }
	   else 
	   {
	       state = MVC_RETRANS;
	   }

    }
	//��ʱ��˵��û�г����ɹ�   
	else 
    {
    	state = MVC_PAYOUT;
		VPMsgPackSend( VP_NAK_RPT, 0, 0  );
	}  //�������
	

    //�������ȷ�ϰ��й��ϣ����еĲ���
	if((GetDevStatus() & DEV_ERR_BIT_DRVCOMM) == 0) 
	{	
/**************************************************************/														 							 			
		#if DRV_TYPE == DRV_12
		//�������루32λ�������λ��1����EVB�������ֽ�Ϊ������룬����Ϊͨ����
		OSMboxAccept(g_CommBackMsg);
		MsgBack.CmdType = ch + ((uint32_t)CMD_GOODS_CHECK << 24);			
		OSMboxPost(g_CommMsg,&MsgBack.CmdType);				//��ѯ����״̬
		
		pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC * 2,&err);
		#endif
/*************************************************************/
    }
	#endif

	return state;
}
	

/*����PCҪ���͵�ָ��*/
uint8_t VP_CMD_Opt(void)
{
	uint8_t 	err = 0;
	uint8_t 	*PCCmd;
	uint32_t 	CurrentChg;	  //��ǰ����ֵ
	uint32_t 	CurrentCost;	  //��ǰ�۱�ֵ
	uint8_t  	ChannelX,ChannelY;
	uint8_t     state;

	if( SYSPara.PCEnable == 2 )//120620 by cq PCcommunication
	{
		state = 0xEE;
		PCCmd = OSMboxPend(g_PCCMDMsg,10,&err);		
		if (err ==OS_NO_ERR)
		{
			//Trace("\r\nReady PCCmd=%d",*PCCmd);
			switch(*PCCmd)
			{
				  //��λָ��	
				  case VP_RESET_IND:
				  {
				  		//Trace("\r\nReady VP_RESET_IND");
						//sysVPMission.resetCmd = 0;
						DispInitText();	//��ʾ"�豸��ʼ���У����Ժ�"	
						if(IsMoneyInEN()) //Ͷ������ʹ�ܣ��ͽ���
						{
							DisableMoneyIn();
							SetTouBiStat(CMD_ALL_DIS);		//����Ͷ��
						}
						
					    OSMboxAccept(g_PCCommMsg);
					    MsgBack.CmdPCCMDMSG = ((uint32_t)VP_RESET_IND << 24);
					    OSMboxPost(g_PCCommMsg,&MsgBack.CmdPCCMDMSG);//֪ͨϵͳ����ά��ģʽ�������						   
							
						OSSemPend(g_PCSem,0,&err);	//һֱ�ȴ���ֱ���豸��ʼ�����

						EnableMoneyIn(); 
						SetTouBiStat(CMD_ALL_EN);		//ʹ��Ͷ��
						
						break;
				  }
				  //����ָ��
				  case VP_PAYOUT_IND:
				  {
				  		Trace("\r\nVP_CMD_Opt VP_PAYOUT_IND");
				  	
						//sysVPMission.changeCmd = 0;
						//���� 		
						if(SYSPara.Decimal==1)
					    {
							CurrentChg = sysVPMission.changeMoney/10;
					    }
					    else if(SYSPara.Decimal==2)
					    {
							CurrentChg = sysVPMission.changeMoney;
					    }	

						RstInputMode();
						Disp_VP_CMD_PayoutText(CurrentChg);//��ʾ��������
						   
						if(IsMoneyInEN()) //Ͷ������ʹ�ܣ��ͽ���
						{
							DisableMoneyIn();
							SetTouBiStat(CMD_ALL_DIS);		//����Ͷ��
						}

						//120827 by cq PCcommunication
						//Do_VP_CMD_PayoutMsg(CurrentChg);		 //������������
						g_Amount = CurrentChg;
						DoPayOutMsg();
						sysVPMission.changeMoney = g_Amount;
						 
						//RTC_WriteGPREG(LPC_RTC,YREGCH,g_Amount);
					
						if(sysVPMission.changeMoney > 0) //���㲻�� 
						{													
							if(SYSPara.Decimal==1)
							{
							  	TranTotal.Iou = sysVPMission.changeMoney / 10;
							}
							else if(SYSPara.Decimal==2)
							{
							  	TranTotal.Iou = sysVPMission.changeMoney; 
							}	
						    OSMboxAccept(g_PCCommMsg);
						    MsgBack.CmdPCCMDMSG = ((uint32_t)VP_DEBT_RPT << 24) + sysVPMission.changeMoney;
						    OSMboxPost(g_PCCommMsg,&MsgBack.CmdPCCMDMSG);//֪ͨϵͳ����ά��ģʽ�������							   
															
							Disp_VP_CMD_Payout_IOUText();	//��ʾǷ��																																																	
						} 
						else 
						{
							if(CurrentChg > 0) //������ֵ����0
							{				
								DispChangeText();//��ʾȡ��Ǯ
							}					
						}
						/*
						if(HopStat > 0) {					//Hopper�������
							SetDoubtTrans();
						}
						*/						

						if(g_Amount == 0)  
					    {
					       state = MVC_PAYOUT;
					    }
					    else 
					    {
					       state = MVC_SALE;
					    }
						OSTimeDly(OS_TICKS_PER_SEC);

						break;
									
				  }
				  //�ۿ�ָ��
				  case VP_COST_IND:
				  {
				  		if(IsMoneyInEN()) //���Ͷ������ʹ�ܵģ���������
						{
							DisableMoneyIn();
							SetTouBiStat(CMD_ALL_DIS);      //����Ͷ��
						}
						
						if(IsEscrowHold()) //�ж��Ƿ���ֽ���ݴ�
						{			   
						    DoNoteStackMsg();//ѹ��
						}

						if(SYSPara.Decimal==1)
						{
						  	CurrentCost = sysVPMission.costMoney / 10;
						}
						else if(SYSPara.Decimal==2)
						{
						  	CurrentCost = sysVPMission.costMoney; 
						}	

						g_Amount -= CurrentCost;	
						
					    OSMboxAccept(g_PCCommMsg);
					    MsgBack.CmdPCCMDMSG = ((uint32_t)VP_COST_RPT << 24) + sysVPMission.costMoney;
					    OSMboxPost(g_PCCommMsg,&MsgBack.CmdPCCMDMSG);//֪ͨϵͳ����ά��ģʽ�������						   
							
						
						sysVPMission.costMoney = 0;
						//Trace("\r\n COST_IND g_Amount=%d",g_Amount);
						//�ۿ�����󣬸��ݱ��ε�״̬���Լ�����һЩ�������л�����һ��״̬
					    if((g_Amount == 0) || (g_Amount < SYSPara.MoneyMinLeft) || (SYSPara.TransMultiMode == 0)) 
					    {
					       //Trace("\r\n +++costind=payout");	
					       state = MVC_PAYOUT;
					    }
					    else 
					    {
					       state = MVC_SALE;
					    }
												
				  		break;
				  }	
				  //����ָ��
				  case VP_VENDOUT_IND:
				  {

						Trace("\r\n2.VP_CMD_Opt VP_VENDOUT_IND,%d",sysVPMission.vendColumn2);
						//Trace("\r\n 6t=%ld",sysVPMission.pcTeTimer);
				  		RstInputMode();
						DispChuhuoText();//��ʾ���ڳ���

						//Trace(" VP_VENDOUT_IND 3,%d",sysVPMission.vendColumn);
						/*
					    if(IsMoneyInEN()) //���Ͷ������ʹ�ܵģ���������
						{
							DisableMoneyIn();
							SetTouBiStat(CMD_ALL_DIS);      //����Ͷ��
						}

						Trace(" VP_VENDOUT_IND 4");

						if(IsEscrowHold()) //�ж��Ƿ���ֽ���ݴ�
						{			   
						    DoNoteStackMsg();//ѹ��
						}				
						*/
						state = Do_VP_CMD_ChuhuoMsg(sysVPMission.vendColumn2 ,ChannelX,ChannelY);//���ͳ�������
												
				  		break;
				  }
				  default:
				  		break;
			}			  
		 } 
	}
	return state;

}



