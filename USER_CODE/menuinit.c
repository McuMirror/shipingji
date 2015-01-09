/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Menuinit.c
** Last modified Date:  2012-03-01
** Last Version:         
** Descriptions:        ��ά��ģ���и��˵�ҳ���У������������������ʾ����ֵ
**                      
**------------------------------------------------------------------------------------------------------
** Created by:           
** Created date:        2012-03-01
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

//Last Modify Time:03/11/07 01:22
//ReadMe
//����:112
//����:64

//#include <intrins.h>
#include <absacc.h>
#include "..\driver\lpc_types.h"
#include "global.h"
#include "function.h"
#include "gbahr1.h"
#include "hopper.h"
#include "ITL.h"
#include "lcd.h"
#include "menu.h"
#include "drv.h"
#include "dispmenu.h"
#include "language.h"
//		   



char *  MenuInit0(void)
{
return NULL;	
}
char *  MenuInitCHIN(void)		   //����������
{
	Cursor_On(LCDUP);
	InputMode = TRUE;
	FDot =  FALSE;
	DOT = FALSE;			//С������	
	PASSWORD = FALSE;
	InputNum = 0;
	offset = 0;
	InputCol = 2;
	InputDone = FALSE ;
	return NULL;	
}
char *  MenuInitLAYIN(void)		   //���������
{
	Cursor_On(LCDUP);
	InputMode = TRUE;
	FDot =  FALSE;
	DOT = FALSE;			//С������	
	PASSWORD = FALSE;
	InputNum = 0;
	offset = 0;
	InputCol = 1;
	InputDone = FALSE ;
	return NULL;	
}


//����	 ��������
char *  MenuInitPWIN(void)		   
{
	Cursor_On(LCDUP);
	InputMode = TRUE;
	FDot =  FALSE;
	DOT = FALSE;			//С������
	PASSWORD = TRUE;
	InputNum = 0;
	offset = 0;
	
	return NULL;	
}

char * MenuInitCHNO(void)			//������
{

sprintf( StrInit,"%d", 	NowChannel );
//NowCHNO = InputNum;
return  StrInit;	
}

char * MenuInitCHPR(void)		   //�����۸�
{
	uint32_t temp = 0;
//	uint8_t chx,chy;

   // if(DRV_ChnChk(NowCHNO,&chx,&chy) == FALSE) {
   //    strcpy( StrInit,"err");
   // } else {   
	   temp = Channels[NowLayerNo][NowCHNO].GoodsPrice;
	//   sprintf( StrInit,"%d.%S", temp/100,DecimalPoint(temp));
	//}
	return DecimalPoint(temp);		
}


char * MenuInitCHST(void)			//����״̬
{
	sprintf( StrInit,"%d", (Channels[NowLayerNo][NowCHNO].ChannelStat & 0x03) );
	return StrInit;		
}
char * MenuInitCHLF(void)			//�������
{

	//sprintf( StrInit,"%d", Channels[ChnMapPara.LAYTODRV[NowLayerNo - 1]][ChnMapPara.CHTODRV[ChnMapPara.LAYTODRV[NowLayerNo-1]][NowCHNO-1]].GoodsNum  );

	sprintf( StrInit,"%d", Channels[NowLayerNo][NowCHNO].GoodsNum  );
	return StrInit;		
}

char * MenuInitCHGOODS(void)			//��Ʒ���
{
	sprintf( StrInit,"%d", (Channels[NowLayerNo][NowCHNO].GoodsCode) );
	return StrInit;		
}


char * MenuInitAddGoods(void)			//���ȫ������
{
	ClearScreen();
	if(	InputNum == 9)	
	{
		sprintf( StrInit,Language[ADDFULLLAY][SYSPara.Language] );
	}
	else
	{
		sprintf( StrInit,Language[ADDLAYNO][SYSPara.Language], InputNum );
	}
	return StrInit;		
}

char * MenuInitCHSU(void)		   //  �����ɹ����״���
{
	sprintf( StrInit,"%d", Channels[NowLayerNo][NowCHNO].SuccessNum  );
	return StrInit;		
}

char * MenuInitCHMONEY(void)		   //  �������׽��
{
	return DecimalPoint(Channels[NowLayerNo][NowCHNO].SuccessNum * Channels[NowLayerNo][NowCHNO].GoodsPrice);
}

//���ڼ��Ƚ�����;by gzz 20121009
char * MenuInitCHSUJIDU(void)		   //  �����ɹ����״���
{
	sprintf( StrInit,"%d", Channels[NowLayerNo][NowCHNO].SuccessNumJidu  );
	return StrInit;		
}

char * MenuInitCHMONEYJIDU(void)		   //  �������׽��
{
	return DecimalPoint(Channels[NowLayerNo][NowCHNO].SuccessNumJidu * Channels[NowLayerNo][NowCHNO].GoodsPrice);
}


char * MenuInitCHDO(void)		   //�������ʽ��״���
{
	sprintf( StrInit,"%d", Channels[NowLayerNo][NowCHNO].DoubtNum  );
	return StrInit;		
}

char * MenuInitNOST(void)		  //ֽ����״̬��ʾ
{
	if(((SYSPara.GBAEnable == MDB_NOTE_EN) && (SYSPara1.NoteStat == MBV_STAT_OK))
	   || ((SYSPara.GBAEnable == HR_NOTE_EN) && (SYSPara1.NoteStat == HR_STAT_OK))
	   || ((SYSPara.GBAEnable == ITL_NOTE_EN) && (SYSPara1.NoteStat == ITL_STAT_OK))) 
	{
		sprintf( StrInit,"%s",  Language[SNORMAL][SYSPara.Language] );
	}
	else 
	{
	 	sprintf( StrInit,"%s%02x",  Language[SFAULT][SYSPara.Language] ,SYSPara1.NoteStat );
	}
	return StrInit;		
}

char * MenuInitCOST(void)		   //Ӳ����״̬��ʾ
{
	if (SYSPara1.CoinsStat == 0)
		sprintf( StrInit,"%s",  Language[SNORMAL][SYSPara.Language] );
	else
	 	sprintf( StrInit,"%s%02x",   Language[SFAULT][SYSPara.Language] ,SYSPara1.CoinsStat);
	return StrInit;		
}
char * MenuInitHOST1(void)			//������#1״̬��ʾ
{	
	//120716 by cq HoppeyUse
	if(SYSPara.ChangerEnable == MDB_CHANGER_EN) 
		sprintf( StrInit,"%s",	 Language[SNORMAL][SYSPara.Language]  );//120622 by cq HopperTest
	else if ((SYSPara1.HopperStat[0] & HOPPER_ERR_MASK) == 0)
		sprintf( StrInit,"%s",   Language[SNORMAL][SYSPara.Language]  );
	else
	 	sprintf( StrInit,"%s%02x",  Language[SFAULT][SYSPara.Language] ,SYSPara1.HopperStat[0]);
		
	return StrInit;		
}
char * MenuInitHOST2(void)		   //������#2״̬��ʾ
{
	//120716 by cq HoppeyUse
	if(SYSPara.ChangerEnable == MDB_CHANGER_EN) 
		sprintf( StrInit,"%s",	 Language[SNORMAL][SYSPara.Language]  );//120622 by cq HopperTest
	else if ((SYSPara1.HopperStat[1] & HOPPER_ERR_MASK) == 0)
		sprintf( StrInit,"%s",  Language[SNORMAL][SYSPara.Language] );
	else
	 	sprintf( StrInit,"%s%02x", Language[SFAULT][SYSPara.Language],SYSPara1.HopperStat[1]);
		
	return StrInit;		
}
char * MenuInitHOST3(void)			//������#3״̬��ʾ
{
	//120716 by cq HoppeyUse
	if(SYSPara.ChangerEnable == MDB_CHANGER_EN) 
		sprintf( StrInit,"%s",	 Language[SNORMAL][SYSPara.Language]  );//120622 by cq HopperTest
	else if ((SYSPara1.HopperStat[2] & HOPPER_ERR_MASK) == 0)
		sprintf( StrInit,"%s",  Language[SNORMAL][SYSPara.Language]  );
	else
	 	sprintf( StrInit,"%s%02x", Language[SFAULT][SYSPara.Language] ,SYSPara1.HopperStat[2]);
		
	return StrInit;		
}

char * MenuInitHOST2_ReaderCost(void)		   //������#2״̬��ʾ
{
	//120926 by cq Cashless
	if(SYSPara.ReaderCost)//��
	{
		if(SYSPara.Language)//Ӣ��
		{
			strcpy( StrInit,"ON");
		}
		else
		{
			strcpy( StrInit,"��");
		}
	}
	else
	{
		if(SYSPara.Language)//Ӣ��
		{
			strcpy( StrInit,"OFF");
		}
		else
		{
			strcpy( StrInit,"��");
		}
	}
	
	/*
	if ((SYSPara1.HopperStat[1] & HOPPER_ERR_MASK) == 0)
		sprintf( StrInit,"%s",  Language[SNORMAL][SYSPara.Language] );
	else
	 	sprintf( StrInit,"%s%02x", Language[SFAULT][SYSPara.Language],SYSPara1.HopperStat[1]);
		
	sprintf( StrInit,"%s",	 Language[SNORMAL][SYSPara.Language]  );//120622 by cq HopperTest
	*/

	return StrInit;		
}

char * MenuInitHOST3_ReaderEnable(void)			//������#3״̬��ʾ
{	
	//120921 by cq Cashless
	if(SYSPara.ReaderEnable)//��
	{
		if(SYSPara.Language)//Ӣ��
		{
			strcpy( StrInit,"ON");
		}
		else
		{
			strcpy( StrInit,"��");
		}
	}
	else
	{
		if(SYSPara.Language)//Ӣ��
		{
			strcpy( StrInit,"OFF");
		}
		else
		{
			strcpy( StrInit,"��");
		}
	}
		
		
	/*
	if ((SYSPara1.HopperStat[2] & HOPPER_ERR_MASK) == 0)
		sprintf( StrInit,"%s",  Language[SNORMAL][SYSPara.Language]  );
	else
	 	sprintf( StrInit,"%s%02x", Language[SFAULT][SYSPara.Language] ,SYSPara1.HopperStat[2]);
		
	sprintf( StrInit,"%s",	 Language[SNORMAL][SYSPara.Language]  );//120622 by cq HopperTest
	*/

	return StrInit;		
}



char * MenuInitIOU(void)			//Ƿ��
{
	//sprintf( StrInit,"%d", SYSPara.Iou  );
	//return StrInit;
	return DecimalPoint(TranTotal.Iou);		
}
char * MenuInitCOCH1(void)			//Ӳ����ͨ��1��ֵ
{
  
 	return DecimalPoint(SYSPara.CoinsValue[0]);			
}
char * MenuInitCOCH2(void)			//Ӳ����ͨ��2��ֵ
{
	//sprintf( StrInit,"%d", SYSPara.CoinsValue[1]  );
	return DecimalPoint(SYSPara.CoinsValue[1]);		
}
char * MenuInitCOCH3(void)		  	//Ӳ����ͨ��3��ֵ
{
	return DecimalPoint(SYSPara.CoinsValue[2]);		
}
char * MenuInitCOCH4(void)		  	//Ӳ����ͨ��4��ֵ
{
	return DecimalPoint(SYSPara.CoinsValue[3]);		
}
char * MenuInitCOCH5(void)		   	//Ӳ����ͨ��5��ֵ
{
	return DecimalPoint(SYSPara.CoinsValue[4]);			
}
char * MenuInitCOCH6(void)		   	//Ӳ����ͨ��6��ֵ
{
	return DecimalPoint(SYSPara.CoinsValue[5]);		
}
char * MenuInitCOCH7(void)				//Ӳ����ͨ��7��ֵ
{
	return DecimalPoint(SYSPara.CoinsValue[6]);		
}
char * MenuInitCOCH8(void)			  	//Ӳ����ͨ��8��ֵ
{
	return DecimalPoint(SYSPara.CoinsValue[7]);			
}
char * MenuInitNOCH1(void)			  	//ֽ����ͨ��1��ֵ
{
	return DecimalPoint(SYSPara.BillValue[0]);			
}
char * MenuInitNOCH2(void)			   //ֽ����ͨ��2��ֵ
{
	return DecimalPoint(SYSPara.BillValue[1]);	
}
char * MenuInitNOCH3(void)			  //ֽ����ͨ��3��ֵ
{
	return DecimalPoint(SYSPara.BillValue[2]);		
}
char * MenuInitNOCH4(void)			  //ֽ����ͨ��4��ֵ
{
	return DecimalPoint(SYSPara.BillValue[3]);		
}
char * MenuInitNOCH5(void)			  //ֽ����ͨ��5��ֵ
{
	return DecimalPoint(SYSPara.BillValue[4]);	
}
char * MenuInitNOCH6(void)			  //ֽ����ͨ��6��ֵ
{
	return DecimalPoint(SYSPara.BillValue[5]);	
}
char * MenuInitNOCH7(void)			  //ֽ����ͨ��7��ֵ
{
	return DecimalPoint(SYSPara.BillValue[6]);			
}
char * MenuInitNOCH8(void)			  //ֽ����ͨ��8��ֵ
{
	return DecimalPoint(SYSPara.BillValue[7]);		
}

char * MenuInitCGVA1(void)			 //������#1��ֵ
{
	return DecimalPoint(SYSPara.ChangeValue[0]);		
}
char * MenuInitCGVA2(void)			  //������#2��ֵ
{
	return DecimalPoint(SYSPara.ChangeValue[1]);	
}
char * MenuInitCGVA3(void)			  //������#3��ֵ
{
	return DecimalPoint(SYSPara.ChangeValue[2]);		
}
char * MenuInitCGSV(void)			  //������Ƿ����
{
	sprintf( StrInit,"%d", SYSPara.ChangeServer  );
	return StrInit;		
}
char * MenuInitPONO(void)			  //С����λ��
{
	sprintf( StrInit,"%d", SYSPara.Decimal  );
	return StrInit;		
}
char * MenuInitSACON(void)			  // ����ȷ��
{
	//121108 by cq GOCErrorSevice
	//sprintf( StrInit,"%d", SYSPara.GOCCtr  );
	if(isGOCErrorSevice())
		sprintf( StrInit,"%d", SYSPara.GOCErrorSevice  );
	else
		sprintf( StrInit,"%d", SYSPara.GOCCtr  );
	return StrInit;		
}
char * MenuInitPOSEN(void)			  //POS��ʹ��
{
	sprintf( StrInit,"%d", SYSPara.POSEnable  );
	return StrInit;		
}

char * MenuInitPCEN(void)			  //PC��ͨѶʹ��
{
	sprintf( StrInit,"%d", SYSPara.PCEnable  );
	return StrInit;		
}

char * MenuInitLCDSEL(void)			  //ʹ��LCD����
{
	sprintf( StrInit,"%d", SYSPara.LCDSel  );
	return StrInit;		
}

//ѡ������;by gzz 20121025
char * MenuInitKeySel(void)			  //�Ƿ�ʹ��ѡ������
{
	sprintf( StrInit,"%d", SYSPara.KeySel  );
	return StrInit;		
}

//ƴͼ��Ļ��ʽ;by gzz 20121106
char * MenuInitLogoSel(void)			  //�Ƿ�ʹ��logo
{
	sprintf( StrInit,"%d", SYSPara.LogoSel  );
	return StrInit;		
}

//�����ֹ���������;by gzz 20130122
char * MenuInitAutoColumn(void)			  
{
	sprintf( StrInit,"%d", SYSPara2.AutoColumn  );
	return StrInit;		
}

//�Ƿ�ʹ��ʮ�����Ļ���;by gzz 20130226
char * MenuInitTenColumn(void)			  
{
	sprintf( StrInit,"%d", SYSPara2.TenColumn  );
	return StrInit;		
}


//holdnote �˵���ʼ��,��������ݴ棬����ϵͳ��������ʾ5Ԫ�ݴ棬10Ԫ�ݴ�ѡ���������
void HoldNoteInit(void)
{

	if(SYSPara.NoteEscrow ==0)
	{
		BusinessNo = BUSINESSNO-2;
	 	KeyTab[MENU_HOLDNOTE].KeyTab_PressDown	  = MENU_COINVALUE;
		KeyTab[MENU_COINVALUE].KeyTab_PressUp	  = MENU_HOLDNOTE;

	}
	else
	{
		BusinessNo = BUSINESSNO;
		KeyTab[MENU_HOLDNOTE].KeyTab_PressDown	  = MENU_HOLDNOTE5;
		KeyTab[MENU_COINVALUE].KeyTab_PressUp	  = MENU_HOLDNOTE10;
	}

}

//�����û��˵��ɼ�;by gzz 20121204
//mode=1��ʼ�����Ӳ˵�,2���±�����Ӳ˵�
void KeySystemInit(uint8_t mode)//��ʼ�����������ÿ��Ӳ˵�
{
	uint8_t i;
	if(mode == 1)
	{
		for(i = 0;i <MAX_KEYTABSTRUCT_NUM; i++)
		{
			KeyTab[i].KeyTab_Visible = keyVisible.visible[i];	
			//Trace("(%d=%d)",i,keyVisible.visible[i]);
		}
	}
	else
	{
		for(i = 0;i <MAX_KEYTABSTRUCT_NUM; i++)
		{
			 keyVisible.visible[i] = KeyTab[i].KeyTab_Visible;		
			 //Trace("[%d=%d]",KeyTab[i].KeyTab_MenuIndex,KeyTab[i].KeyTab_Visible);
		}		
	}

}

char * MenuInitHOLDNOTE(void)			  //�ݴ�ʹ��
{

	HoldNoteInit();

	sprintf( StrInit,"%d", SYSPara.NoteEscrow  );
	return StrInit;		
}
char * MenuInitHOLDNOTE5(void)			  //�ݴ�ʹ��
{
	sprintf( StrInit,"%d", SYSPara.NoteEscrowType[1]  );
	return StrInit;		
}
char * MenuInitHOLDNOTE10(void)			  //�ݴ�ʹ��
{
	sprintf( StrInit,"%d", SYSPara.NoteEscrowType[2]  );
	return StrInit;		
}
char 	*MenuInitNBUY(void)
{
	sprintf( StrInit,"%d", SYSPara.TransMultiMode  );	  	//�����ν���
	return StrInit;		
}
char 	*MenuInitRCOIN(void)
{
	sprintf( StrInit,"%d", SYSPara.TransEscape  );	  		//���������˱�
	return StrInit;		
}
char 	*MenuInitOCOIN(void)
{
	sprintf( StrInit,"%d", SYSPara.CoinEnable  );			//Ӳ����ʹ��
	return StrInit;		
}
char 	*MenuInitONOTE(void)
{
	if(SYSPara.GBAEnable == NOTE_MEI)	
	{
		sprintf( StrInit,"MDB"  );			//ֽ����ʹ��
	}
	else if(SYSPara.GBAEnable == NOTE_GBA)	
	{
		sprintf( StrInit,"GBA"  );			//ֽ����ʹ��
	}
	else if(SYSPara.GBAEnable == NOTE_ITL)	
	{
		sprintf( StrInit,"SSP"  );			//ֽ����ʹ��
	}
	else 
	   sprintf( StrInit,"OFF"  );	
	return StrInit;		
}
//�������˵�;by gzz 20121120
char 	*MenuInitONREADER(void)
{
	if(SYSPara.ReaderEnable == READEDR_CLOSE)	
	{
		sprintf( StrInit,"OFF"  );			//������ʹ��
	}
	else if(SYSPara.ReaderEnable == READEDR_MDB)	
	{
		sprintf( StrInit,"MDB"  );			//������ʹ��
	}	
	return StrInit;		
}

//�������˵�;by gzz 20121120
char 	*MenuInitOREADERCOST(void)
{
	sprintf( StrInit,"%d", SYSPara.ReaderCost  );			//��������Ǯʹ��
	return StrInit;		
}


char 	*MenuInitOCHANGE(void)
{
	sprintf( StrInit,"%d", SYSPara.ChangerEnable  );			//������ʹ��
	return StrInit;		
}
char 	*MenuInitBMIN(void)								//������
{
	return DecimalPoint( SYSPara.MoneyMinLeft);	
}					

char * MenuInitMMAX(void)								//����ձҽ��
{
	return DecimalPoint( SYSPara.MoneyMaxin);		
}
char * MenuInitGPRS(void)								//GPRSʹ��
{
	sprintf( StrInit,"%d", SYSPara.GPRSOnOff  );
	return StrInit;		
}

char * MenuInitSENO(void)							   //�������
{
	strcpy( StrInit,SYSPara.SerialNo  );
	//sprintf( StrInit,"%X", SYSPara.SerialNo  );
	return StrInit;		
}

char * MenuInitGSMNO(void)							//GSM����
{
	strcpy( StrInit,SYSPara.GSMNO  );
	//sprintf( StrInit,"%X", SYSPara.GSMNO  );
	return StrInit;		
}

char * MenuInitTemerature(void)							   //�¶�
{
	sprintf( StrInit,"%d.%d", sysXMTMission.recSVTemp/10, sysXMTMission.recSVTemp%10);
	return	StrInit;
}



char * MenuInitDBMN(void)								//���ʽ��
{
	return DecimalPoint( TranTotal.DoubtMoney);	
}

														//����������
char * MenuInitINCOME(void)
{

	return DecimalPoint( TranTotal.Income);	
	
}
														//ֽ��������
char * MenuInitNOIN(void)
{

	return DecimalPoint( TranTotal.NoteIncome);	
}
														//Ӳ��������
char	*MenuInitCOIN(void)
{
	return DecimalPoint( TranTotal.CoinsIncome);		
}

char	*MenuInitTOTR(void)
{														//�ܽ��׽��
	
	return DecimalPoint( TranTotal.TotalTrans);			
}

char	*MenuInitTOCH(void)
{
	return DecimalPoint( TranTotal.TotalChange);			//��������
}

char	*MenuInitCOVA1(void)
{
	sprintf( StrInit,"%d", TranTotal.CoinsChange[0]);		//#1������
	return StrInit;		
} 
char	*MenuInitCOVA2(void)
{
	sprintf( StrInit,"%d", TranTotal.CoinsChange[1]);		//#2������
	return StrInit;		
} 
char	*MenuInitCOVA3(void)
{
	sprintf( StrInit,"%d", TranTotal.CoinsChange[2]);		//#3������
	return StrInit;		
}  

//���ڼ��Ƚ�����;by gzz 20121009
														//����������
char * MenuInitINCOMEJIDU(void)
{

	return DecimalPoint( TranTotal.IncomeJidu);	
	
}
														//ֽ��������
char * MenuInitNOINJIDU(void)
{

	return DecimalPoint( TranTotal.NoteIncomeJidu);	
}
														//Ӳ��������
char	*MenuInitCOINJIDU(void)
{
	return DecimalPoint( TranTotal.CoinsIncomeJidu);		
}

char	*MenuInitTOTRJIDU(void)
{														//�ܽ��׽��
	
	return DecimalPoint( TranTotal.TotalTransJidu);			
}

char	*MenuInitTOCHJIDU(void)
{
	return DecimalPoint( TranTotal.TotalChangeJidu);			//��������
}

char	*MenuInitCOVA1JIDU(void)
{
	sprintf( StrInit,"%d", TranTotal.CoinsChangeJidu[0]);		//#1������
	return StrInit;		
} 
char	*MenuInitCOVA2JIDU(void)
{
	sprintf( StrInit,"%d", TranTotal.CoinsChangeJidu[1]);		//#2������
	return StrInit;		
} 
char	*MenuInitCOVA3JIDU(void)
{
	sprintf( StrInit,"%d", TranTotal.CoinsChangeJidu[2]);		//#3������
	return StrInit;		
}  



char	*MenuInitSUNUM(void)							   //�ɹ����״���
{
	sprintf( StrInit,"%d", TranTotal.SuccessNum );
	return StrInit;		
} 

char	*MenuInitDBNUM(void)						   //���ʽ��״���
{
	sprintf( StrInit,"%d", TranTotal.DoubtNum  );
	return StrInit;		
} 
char	*MenuInitFLASH(void)
{

	sprintf( StrInit,"%d", (MAXTRANPAGE - TranTotal.TranPages)  );
	return StrInit;	
}

char * MenuInitYear(void)				   //��
{
	sprintf( StrInit,"%d", TranData.Time.YEAR  );
	return StrInit;		
}
char * MenuInitMonth(void)				  //��
{
	sprintf( StrInit,"%d", TranData.Time.MONTH  );
	return StrInit;		
}
char * MenuInitDate(void)				  //��
{
	sprintf( StrInit,"%d", TranData.Time.DOM  );
	return StrInit;		
}
char * MenuInitHour(void)				  //ʱ
{
	sprintf( StrInit,"%d", TranData.Time.HOUR  );
	return StrInit;		
}
char * MenuInitMinute(void)				  //��
{
	sprintf( StrInit,"%d", TranData.Time.MIN  );
	return StrInit;		
}

//���ѹ��������;by gzz 20121224
char * MenuInitCompressOn(void)				  //ѹ����ʱ�����
{
	sprintf( StrInit,"%d", SYSPara2.CompressorTime.DeviceOn  );
	return StrInit;		
}

char * MenuInitCompressHourOn(void)				  //ѹ������ʱ
{
	sprintf( StrInit,"%d", SYSPara2.CompressorTime.HourOn  );
	return StrInit;		
}
char * MenuInitCompressMinuteOn(void)				  //ѹ�����򿪷�
{
	sprintf( StrInit,"%d", SYSPara2.CompressorTime.MinOn  );
	return StrInit;		
}
char * MenuInitCompressHourOff(void)				  //ѹ�����ر�ʱ
{
	sprintf( StrInit,"%d", SYSPara2.CompressorTime.HourOff  );
	return StrInit;		
}
char * MenuInitCompressMinuteOff(void)				  //ѹ�����رշ�
{
	sprintf( StrInit,"%d", SYSPara2.CompressorTime.MinOff  );
	return StrInit;		
}

//���չʾ�ƿ���;by gzz 20121229
char * MenuInitLEDOn(void)				  //չʾ��ʱ�����
{
	sprintf( StrInit,"%d", SYSPara2.LEDTime.DeviceOn  );
	return StrInit;		
}

char * MenuInitLEDHourOn(void)				  //չʾ�ƴ�ʱ
{
	sprintf( StrInit,"%d", SYSPara2.LEDTime.HourOn  );
	return StrInit;		
}
char * MenuInitLEDMinuteOn(void)				  //չʾ�ƴ򿪷�
{
	sprintf( StrInit,"%d", SYSPara2.LEDTime.MinOn  );
	return StrInit;		
}
char * MenuInitLEDHourOff(void)				  //չʾ�ƹر�ʱ
{
	sprintf( StrInit,"%d", SYSPara2.LEDTime.HourOff  );
	return StrInit;		
}
char * MenuInitLEDMinuteOff(void)				  //չʾ�ƹرշ�
{
	sprintf( StrInit,"%d", SYSPara2.LEDTime.MinOff  );
	return StrInit;		
}


char * MenuInitLAYNO(void)				  //���
{

	sprintf( StrInit,"%d", NowLayerNo +1 );
	//NowLayerNo = InputNum;
	return  StrInit;	
}
char * MenuInitLAYENABLE(void)			  //�㿪��
{
	sprintf( StrInit,"%d", SYSPara.LayEnable[NowLayerNo]  );
	return StrInit;		
}

char * MenuInitMAXGOODS(void)			  //��������
{
	sprintf( StrInit,"%d", SYSPara.LayMaxGoods[NowLayerNo] );
	return StrInit;		
}

char * MenuInitCH1(void)				  //��������
{
	sprintf( StrInit,"%d", ((Channels[NowLayerNo][0].ChannelStat &0x80)>>7) );
	return StrInit;		
}

char * MenuInitCH2(void)
{
	sprintf( StrInit,"%d", ((Channels[NowLayerNo][1].ChannelStat &0x80)>>7)  );
	return StrInit;		
}

char * MenuInitCH3(void)
{
	sprintf( StrInit,"%d", ((Channels[NowLayerNo][2].ChannelStat &0x80)>>7)  );
	return StrInit;		
}

char * MenuInitCH4(void)
{
	sprintf( StrInit,"%d", ((Channels[NowLayerNo][3].ChannelStat &0x80)>>7)  );
	return StrInit;		
}

char * MenuInitCH5(void)
{
	sprintf( StrInit,"%d", ((Channels[NowLayerNo][4].ChannelStat &0x80)>>7) );
	return StrInit;		
}

char * MenuInitCH6(void)
{
	sprintf( StrInit,"%d", ((Channels[NowLayerNo][5].ChannelStat &0x80)>>7)  );
	return StrInit;		
}

char * MenuInitCH7(void)
{
	sprintf( StrInit,"%d", ((Channels[NowLayerNo][6].ChannelStat &0x80)>>7)  );
	return StrInit;		
}

char * MenuInitCH8(void)
{
	sprintf( StrInit,"%d", ((Channels[NowLayerNo][7].ChannelStat &0x80)>>7)  );
	return StrInit;		
}


//121105 by cq TenChannels
char * MenuInitCH9(void)
{
#if (MAXCHANNEL >= 9)
	sprintf( StrInit,"%d", ((Channels[NowLayerNo][8].ChannelStat &0x80)>>7)  );
#else
	sprintf( StrInit,"%d", 0  );
#endif
	return StrInit;		
}

//121105 by cq TenChannels
char * MenuInitCH0(void)
{
#if (MAXCHANNEL >= 10)
		sprintf( StrInit,"%d", ((Channels[NowLayerNo][9].ChannelStat &0x80)>>7)  );
#else
		sprintf( StrInit,"%d", 0  );
#endif
	return StrInit;		
}


//������������;by gzz 20121120
char * MenuInitCHNum(uint8_t ID)
{
	sprintf( StrInit,"%d", colSystemPara.ColMaxGoods[NowLayerNo][ID]);
	return StrInit;		
}

char * MenuInitCH1Num(void)				  //��������
{	
	 MenuInitCHNum(0);		
}

char * MenuInitCH2Num(void)
{	
	 MenuInitCHNum(1);		
}


char * MenuInitCH3Num(void)
{	
	 MenuInitCHNum(2);		
}


char * MenuInitCH4Num(void)
{	
	 MenuInitCHNum(3);		
}


char * MenuInitCH5Num(void)
{	
	 MenuInitCHNum(4);		
}


char * MenuInitCH6Num(void)
{	
	 MenuInitCHNum(5);		
}


char * MenuInitCH7Num(void)
{	
	 MenuInitCHNum(6);		
}


char * MenuInitCH8Num(void)
{	
	 MenuInitCHNum(7);		
}



//121105 by cq TenChannels
char * MenuInitCH9Num(void)
{
#if (MAXCHANNEL >= 9)
	MenuInitCHNum(8);
#endif
}


//121105 by cq TenChannels
char * MenuInitCH0Num(void)
{
#if (MAXCHANNEL >= 10)
	MenuInitCHNum(9);
#endif
}








