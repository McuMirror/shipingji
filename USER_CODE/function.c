/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               
** Latest modified Date:    2010-04-23
** Latest Version:          1.00
** Descriptions:            ͨ��flash����Ķ�ȡ���׼�¼�Ȳ������û���д�Ļ����ӿں���,��������Ȩģʽ����
**                          ע��:ͨ����ͨ��ҳ��д�ģ��������ҳ����оƬ�Լ������,ͨ��spi���߶�д             
**
**--------------------------------------------------------------------------------------------------------
** Created by:              yqh
** Created date:            
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
 
#include "global.h"
//#include "..\mid\AT45DB.h"
#include "..\driver\AT45DB.h"//120401 by cq change structor
#include "function.h"
#include "Menu.h"
#include "dispmenu.h"

/**************************AT45DB161DоƬ���ܼ�ʵ��Ӧ��˵��**********************************************/
/*
һ��AT45DB161DоƬ����
	1.1 AT45DB161DΪSPI�ӿڵ�Nor��Flash
	1.2 4096ҳ��ÿҳ512/528�ֽڣ�������Ϊ2M�ֽ�
	1.3 �ɰ��������졢ҳ����
����ʵ��Ӧ��
	2.1 �豸����  ��7ҳ
	2.2 �ܵĽ��׽���¼	 ��8ҳ
	2.3 ϵͳ����  ��9ҳ
    2.4 ��������  10--20ҳ
    2.5 �������������� ��21ҳ
    2.6 �µ�ϵͳ���� ��70ҳ
    2.7 �û��˵��ɼ� ��50ҳ
	2.8 ���׼�¼  ��500ҳ-4000	
*/
/**************************************End Of File*******************************************************/

//����Ͷ�ȡ��������		10--20ҳ
 void XChannels(uint8_t mode)
{	
//	uint8_t *tp1,*tp2;
    uint8_t *tp2;
	uint16_t	i = 0;
	int16_t	temp,Pages;
	
//	tp1 = sSysData;
	tp2 = (uint8_t *) &Channels[0];
	temp = (sizeof(GoodsChannel))* MAXCHANNEL*MAXLAYER;
	 /*  for( i= 0; i<temp;i++)	{
	   		if (mode == READ)
	   			*tp2 = *tp1;
	   		else
	   			*tp1 = *tp2;
	   		tp1++;
	   		tp2++;
	   	}
	*/
	
	Pages = (temp / PAGESIZE)	+1;

	
	if (mode == WRITE)	
	{
		 for(i = 0;i<Pages ;i++)
		 {
		 	AT45DB_WritePage(10+i, tp2);//ÿҳÿҳ��д����
		 	tp2+=PAGESIZE;
		 }
	}	    		
	else
	{
		while( temp>0)
		{
			if(temp >  PAGESIZE)
				AT45DB_ReadByte(10+i, 0, PAGESIZE, tp2);//ÿҳÿҳ�Ķ�����
			else
				AT45DB_ReadByte(10+i, 0, temp, tp2);
			
			i++;
			temp -=  PAGESIZE;
			tp2 +=	PAGESIZE;
		}
 	}					  

	 
}

//����Ͷ�ȡϵͳ����,���ϵͳ�����ڽ��׹����в���ı�	   ��9ҳ
void XSystemPara(uint8_t mode)
{
 	uint8_t *tp1;
//	uint16_t	i = 0;
	int16_t	temp,Pages;
	
	Pages = Pages;

	tp1 = (uint8_t *) &SYSPara;
	temp = (sizeof(SystemPara));
	
	Pages = (temp / PAGESIZE)	+1;
	
	if (mode == WRITE)	
	{
	 	AT45DB_WritePage(9, tp1);
	}	    		
	else
	{
		AT45DB_ReadByte(9, 0, temp, tp1);
	}					


}

//����Ͷ�ȡϵͳ����,���ϵͳ�����ڽ��׹����в���ı�	   ��9ҳ
void XSystemPara2(uint8_t mode)
{
 	uint8_t *tp1;
//	uint16_t	i = 0;
	int16_t	temp,Pages;
	
	Pages = Pages;

	//��70ҳ//����µ�ϵͳ����;by gzz 20121219
	tp1 = (uint8_t *) &SYSPara2;
	temp = (sizeof(SystemPara2));
	
	Pages = (temp / PAGESIZE)	+1;
	
	if (mode == WRITE)	
	{
	 	AT45DB_WritePage(70, tp1);
	}	    		
	else
	{
		AT45DB_ReadByte(70, 0, temp, tp1);
	}	

}


//������������;by gzz 20121120
//����Ͷ�ȡ��������������,���ϵͳ�����ڽ��׹����в���ı�	   ��21ҳ
void XColSystemPara(uint8_t mode)
{
 	uint8_t *tp1;
//	uint16_t	i = 0;
	int16_t	temp,Pages;
	
	Pages = Pages;

	tp1 = (uint8_t *) &colSystemPara;
	temp = (sizeof(ColSystemPara));
	
	Pages = (temp / PAGESIZE)	+1;
	
	if (mode == WRITE)	
	{
	 	AT45DB_WritePage(21, tp1);
	}	    		
	else
	{
		AT45DB_ReadByte(21, 0, temp, tp1);
	}					  

}


//����Ͷ�ȡϵͳ����,���ϵͳ�����ڽ��׹����л�ı�	   ��7ҳ
void XSystemPara1(uint8_t mode)
{
 	uint8_t *tp1;
//	uint16_t	i = 0;
	int16_t	temp,Pages;
	
	Pages = Pages;		

	tp1 = (uint8_t *) &SYSPara1;
	temp = (sizeof(SystemPara1));
	
	Pages = (temp / PAGESIZE)	+1;
	
	if (mode == WRITE)	
	{
	 	AT45DB_WritePage(7, tp1);
	}	    		
	else
	{
		AT45DB_ReadByte(7, 0, temp, tp1);
	}					  

}

//�����û��˵��ɼ�;by gzz 20121204
//�����û��˵��ɼ�,���ϵͳ�����ڽ��׹����в���ı�	   ��50ҳ
void XKeySystemVisible(uint8_t mode)
{
 	uint8_t *tp1;
//	uint16_t	i = 0;
	int16_t	temp,Pages;
	
	Pages = Pages;

	tp1 = (uint8_t *) &keyVisible;
	temp = (sizeof(KeySystemVisible));
	
	Pages = (temp / PAGESIZE)	+1;
	
	if (mode == WRITE)	
	{
	 	AT45DB_WritePage(50, tp1);
	}	    		
	else
	{
		AT45DB_ReadByte(50, 0, temp, tp1);
	}					  

}

//Ŀǰ�Ѿ�ʹ�õ���71ҳ��
//����Ͷ�ȡ���׼�¼  ��500ҳ��		 ����Ͷ�ȡ�ܽ��׽���¼  ��8ҳ
void XTransaction(uint8_t mode)
{
 	uint8_t *tp1;
//	uint16_t	i = 0;
	int16_t	temp;
	

	tp1 = (uint8_t *) &TranData;//�������ݼ�¼
	temp = (sizeof(Transaction  ));
	
	
	//���׼�¼��500��ʼ��4000Ϊֹ��ÿ����һ�Σ���ȥһҳ����
	if (mode == WRITE)	
	{
	 	AT45DB_WritePage(TranTotal.TranPages, tp1);
	}	    		
	else
	{
		AT45DB_ReadByte(TranTotal.TranPages, 0, temp, tp1);
	}					  
	if(TranTotal.TranPages++ > MAXTRANPAGE)
		TranTotal.TranPages = 500;
	
	//�����ܵĽ��׽���¼	 ��8ҳ
	tp1 = (uint8_t *) &TranTotal;
	temp = (sizeof(TransactionTotal));
	   
	if (mode == WRITE)	
	{
	 	AT45DB_WritePage(8, tp1);
	}	    		
	else
	{
		AT45DB_ReadByte(8, 0, temp, tp1);
	}					  
}


//����ϵͳ������������Ӧ��ϵ�����׼�¼
void RstSystemPara(void)
{
    uint16_t i,j;
	uint8_t  *tp;
	SystemPara tempSysPara;

	ClearScreen();
	memcpy((uint8_t *)&tempSysPara,(uint8_t *)&SYSPara,sizeof(SYSPara));//ϵͳ������Щ�������³���Ĭ��;by gzz 20121102
	tp = (uint8_t *)&SYSPara ;
	for(i = 0; i < (sizeof(SystemPara)); i++) 
	{		 		
		*tp++ = 0x00;
	}
	//��������ʱ����ɾ��;by gzz 20121009
	/*
	tp = (uint8_t *)&TranTotal ;
	for(i = 0; i < (sizeof(TransactionTotal)); i++) 
	{		 				
		*tp++ = 0x00;
	}
	*/
	/*
	tp = (uint8_t *)&TranData ;
	for(i = 0; i< (sizeof(Transaction)); i++) {		 				
		*tp++ = 0x00;
	}
	*/
	tp = (uint8_t *)&Channels[0][0] ;

	for(i = 0; i < ((sizeof(GoodsChannel))*MAXCHANNEL*MAXLAYER); i++) 
	{		 //clear  channels data
		*tp++ = 0x00;
	}

	
	for(i = 0;i < MAXLAYER;i++)	
	{						   //���¼����������ӳ���ϵ
		SYSPara.LayEnable[i] = 0x01	;
		SYSPara.LayMaxGoods[i] = MAXGOODS;
		
		ChnMapPara.LAYTODRV[i] = i+1;
		ChnMapPara.DRVTOLAY[i] = i+1;
		
		for(j = 0; j < MAXCHANNEL; j++)	
		{
			//120703 by cq MDBCompatible
			//Channels[i][j].ChannelStat = 0x80;
			//121108 by cq DontReduceNum
			if(!isDontReduceNum())
			{
				Channels[i][j].ChannelStat = 0x83;			 
				Channels[i][j].GoodsNum = 0;
			}
			else
			{
				Channels[i][j].ChannelStat = 0x81; 
				Channels[i][j].GoodsNum = 99;
			}
			
		   Channels[i][j].GoodsPrice = 100;
		   ChnMapPara.CHTODRV[i][j] = j+1;
		   ChnMapPara.DRVTOCH[i][j] = j+1;
		}
	}

	

	SYSPara.SoftwareVersion = SOFTVERSION;
	SYSPara.HardwareVersion	 = HAEDWAREVERDION;

	//121108 by cq RecordPassword
	if(!isRecordPassword())
	{
		SYSPara.Password = 123456;		
		SYSPara.Password2 = 83718557;
		SYSPara.Password3 = 83702153;
	}
	else
	{
		SYSPara.Password = 123456;		
		SYSPara.Password2 = 123456;
		SYSPara.Password3 = 123456;
	}
	
	TranTotal.TranPages = 20;

	//121106 by cq MDBCompatible

	#if PULSEDEVICE
		SYSPara.CoinsValue[3] = 100;
	#endif
	
	#if COINDEVICE
		SYSPara.CoinsValue[0] = 0;//50;																   
		SYSPara.CoinsValue[1] = 0;//100;
		SYSPara.CoinsValue[2] = 0;
		SYSPara.CoinsValue[3] = 0;
	#endif

	#if MBVDEVICE || GBAHRDEVICE
		SYSPara.BillValue[0] = 0;//100;
		SYSPara.BillValue[1] = 0;//500;
		SYSPara.BillValue[2] = 0;//1000;		  
		SYSPara.BillValue[3] = 0;//2000;
	#endif

	//120703 by cq MDBCompatible
	SYSPara.ChangeValue[0] = 0;//50;			
	SYSPara.ChangeValue[1] = 0;//100;			

	SYSPara.MoneyMaxin = 2000;
	SYSPara.MoneyMinLeft = 100;
	SYSPara.ChangeServer = 0;
	SYSPara.Decimal = 2;
	SYSPara.TransMultiMode = 0;
	SYSPara.TransEscape = 0;
	SYSPara.GBAEnable = MDB_NOTE_EN;
	SYSPara.CoinEnable = MDB_COIN_EN;
	SYSPara.ChangerEnable = MDB_CHANGER_EN;
	SYSPara.POSEnable = 0; 
	SYSPara.PCEnable = 0; 
	SYSPara.LCDSel = tempSysPara.LCDSel;
	SYSPara.KeySel = tempSysPara.KeySel;//ѡ������;by gzz 20121025
	SYSPara.LogoSel = tempSysPara.LogoSel;//ƴͼ��Ļ��ʽ;by gzz 20121106
	SYSPara.ReaderEnable = tempSysPara.ReaderEnable;//�������˵�;by gzz 20121120 
	SYSPara.ReaderCost = tempSysPara.ReaderCost;

	//121108 by cq GOCErrorSevice
	SYSPara.GOCCtr = 1;
	SYSPara.GOCErrorSevice = 0; 

	SYSPara2.AutoColumn = 1;
	SYSPara2.TenColumn = 0;
	
}

//���ÿ���״̬
void RstVisiblePara(void)
{
    uint16_t i;
	
	for(i = 0;i < MAX_KEYTABSTRUCT_NUM;i++)
	{
		switch(KeyTab[i].KeyTab_MenuIndex)
		{
			case MENU_ADDGOODS:
			//�豸����	
			case MENU_HOPPERSTAT3:
			case MENU_GPRSTEST:
			case MENU_SMSTEST:	
			case MENU_ALLCHANNELSTAT:
			case MENU_CHTESTRESULT:	
			case MENU_LCDTEST:
			case MENU_TEMPRATURETEST:
			case MENU_SELECTKEYTEST:
			case MENU_FLASHLEFT:
			//ҵ�����	
			case MENU_OPENCOIN:
			case MENU_OPENNOTE:
			case MENU_OPENCHANGE:	
			case MENU_OPENREADER:
			case MENU_READERCOST:
			case MENU_CHANGESERVER:	
			case MENU_BALANCEMIN:
			case MENU_DECPOINTNUM:	
			case MENU_SALECONFIRM:
			case MENU_POSENABLE:
			case MENU_VMCPC:
			case MENU_LARGELCD:
			case MENU_SELECTKEY:
			case MENU_LOGOSEL:
			case MENU_ADDCOLUMN:
			case MENU_TENCOLUMN:	
			case MENU_HOLDNOTE:
			case MENU_HOLDNOTE5:
			case MENU_HOLDNOTE10:
			case MENU_HOLDNOTE20:	
			//���׼�¼	
			case MENU_PAYMENTSJIDU:
			case MENU_GOODSJIDU:
			case MENU_CLEARTRANSJIDU:
			//ϵͳ����
			case MENU_GPRSONOFF:
			case MENU_SERIALNO:
			case MENU_GSMNO:
			case MENU_TEMPERATURE:
			case MENU_SYSLANGUAGE:
			//�������	
			case MENU_SETCHANNEL:	
			//����Ĭ������	
			case MENU_DEFAULTSET:	
				KeyTab[i].KeyTab_Visible = MENU_VISIBLE_FAUSE;
				break;
		}
	}	
}

uint8_t  ColumnFunction(uint8_t ID,uint8_t InputNum,uint8_t NowLayerNo)				  //��������
{
	uint8_t i,ChannelNum =0 ;
	//Trace("\r\n input=%d,lay=%d,id=%d",InputNum,NowLayerNo,ID);
	if (1)
	{
		if((InputNum < 2 ))
		{
			InputCol = 8;
			//InputMode = FALSE;
			if (InputNum == 0)
			{
				Channels[NowLayerNo][ID].ChannelStat &= ~(1 << 7);
				colSystemPara.ColMaxGoods[NowLayerNo][ID] = 0;//������������;by gzz 20121120
			}
			if (InputNum == 1)
				Channels[NowLayerNo][ID].ChannelStat |= (1 << 7);
			for ( i = 0; i <MAXCHANNEL; i++)
			{
				
				ChnMapPara.CHTODRV[NowLayerNo][i] = 0;		//��������
				ChnMapPara.DRVTOCH[NowLayerNo][i] = 0;
				if( (Channels[NowLayerNo][i].ChannelStat & 0x80) == 0x80 )		   
				{
					
					ChnMapPara.CHTODRV[NowLayerNo][ChannelNum++] = i+1;
					ChnMapPara.DRVTOCH[NowLayerNo][i] = ChannelNum;
				}
			}
			return TRUE;
		}
		else 
		{
			InputDone = FALSE;		  //20110823
			return FALSE;
		}
	}
	InputCol = 1;
	InputDisplay( 0x07)	 ;
	
	return TRUE;
}



uint8_t  LayerFunction(uint8_t InputNum,uint8_t NowLayerNo)			//�������
{
	uint8_t i,LayNum =0 ;
	//Trace("\r\n input=%d,lay=%d",InputNum,NowLayerNo);
	if (1)
	{
		if( (InputNum < 2 ))
		{
			InputCol = 8;
			//InputMode = FALSE;
			SYSPara.LayEnable[NowLayerNo] = InputNum;
			for ( i = 0; i <MAXLAYER; i++)
			{
				
				ChnMapPara.LAYTODRV[i] = 0;   //����
				ChnMapPara.DRVTOLAY[i] = 0;
				if( SYSPara.LayEnable[i] == 0x01 )		   
				{
					
					ChnMapPara.LAYTODRV[LayNum++] = i+1;
					ChnMapPara.DRVTOLAY[i] = LayNum;
				}
			}
			
			return TRUE;
		}
		else
		{
			InputDone = FALSE;		  //20110823
			return FALSE;
		}
	}
	InputCol = 1;
	InputDisplay( 0x07)	 ;
	
	return TRUE;
}


//����ϵͳ������������Ӧ��ϵ�����׼�¼
void RstTurkeySystemPara(void)
{
    uint16_t i,j;
	//uint8_t  *tp;
	//SystemPara tempSysPara;

	ClearScreen();
	/*
	memcpy((uint8_t *)&tempSysPara,(uint8_t *)&SYSPara,sizeof(SYSPara));//ϵͳ������Щ�������³���Ĭ��;by gzz 20121102
	tp = (uint8_t *)&SYSPara ;
	for(i = 0; i < (sizeof(SystemPara)); i++) 
	{		 		
		*tp++ = 0x00;
	}
	

	//121108 by cq RecordPassword
	if(!isRecordPassword())
	{
		SYSPara.Password = 123456;		
		SYSPara.Password2 = 83718557;
		SYSPara.Password3 = 83702153;
	}
	else
	{
		SYSPara.Password = 123456;		
		SYSPara.Password2 = 123456;
		SYSPara.Password3 = 123456;
	}
	
	TranTotal.TranPages = 20;
	*/
				
	//1.��ҵ�����
	SYSPara.MoneyMaxin = 2000;
	SYSPara.MoneyMinLeft = 100;
	SYSPara.ChangeServer = 0;
	SYSPara.Decimal = 2;
	SYSPara.TransMultiMode = 0;
	SYSPara.TransEscape = 0;
	SYSPara.GBAEnable = MDB_NOTE_EN;
	SYSPara.CoinEnable = MDB_COIN_EN;
	SYSPara.ChangerEnable = MDB_CHANGER_EN;
	SYSPara.POSEnable = 0; 
	SYSPara.PCEnable = 0; 
	SYSPara.LCDSel = 2;
	SYSPara.KeySel = 0;//ѡ������;by gzz 20121025
	SYSPara.LogoSel = 3;//ƴͼ��Ļ��ʽ;by gzz 20121106
	SYSPara.ReaderEnable = 0;//�������˵�;by gzz 20121120 
	SYSPara.ReaderCost = 1;

	//121108 by cq GOCErrorSevice
	SYSPara.GOCCtr = 1;
	SYSPara.GOCErrorSevice = 0; 

	
	SYSPara2.AutoColumn = 1;
	SYSPara2.TenColumn = 1;
	SYSPara.NoteEscrow = 0;
	SYSPara.NoteEscrowType[1]=0;
	SYSPara.NoteEscrowType[2]=0;

	//2.���������
	ColumnFunction(0,0,0);
	ColumnFunction(2,0,0);
	ColumnFunction(4,0,0);
	LayerFunction(0,6);
	LayerFunction(0,7);

	//3.��ϵͳѹ����,չʾ�Ʋ���
	SYSPara2.CompressorTime.DeviceOn = 2;
	SYSPara2.CompressorTime.HourOn   = 0;
	SYSPara2.CompressorTime.MinOn    = 0;
	SYSPara2.CompressorTime.HourOff  = 23;
	SYSPara2.CompressorTime.MinOff   = 59;
	SYSPara2.LEDTime.DeviceOn = 2;
	SYSPara2.LEDTime.HourOn   = 0;
	SYSPara2.LEDTime.MinOn    = 0;
	SYSPara2.LEDTime.HourOff  = 23;
	SYSPara2.LEDTime.MinOff   = 59;
	
}

//���ÿ���״̬
void RstTurkeyVisiblePara(void)
{
    uint16_t i;
	
	for(i = 0;i < MAX_KEYTABSTRUCT_NUM;i++)
	{
		switch(KeyTab[i].KeyTab_MenuIndex)
		{
			case MENU_ADDGOODS:
			//�豸����	
			case MENU_HOPPERSTAT1:
			case MENU_HOPPERSTAT2:	
			case MENU_HOPPERSTAT3:
			case MENU_GPRSTEST:
			case MENU_SMSTEST:	
			case MENU_ALLCHANNELSTAT:
			case MENU_CHTESTRESULT:	
			case MENU_LCDTEST:
			case MENU_TEMPRATURETEST:
			case MENU_SELECTKEYTEST:
			case MENU_FLASHLEFT:
			//ҵ�����	
			case MENU_CHANGEVALUE:				
			//case MENU_OPENREADER:
			//case MENU_READERCOST:
			case MENU_CHANGESERVER:	
			case MENU_RETURNCOINS:	
			case MENU_BALANCEMIN:
			case MENU_DECPOINTNUM:	
			case MENU_SALECONFIRM:
			case MENU_POSENABLE:
			case MENU_VMCPC:
			case MENU_LARGELCD:
			case MENU_SELECTKEY:
			case MENU_LOGOSEL:
			case MENU_ADDCOLUMN:
			case MENU_TENCOLUMN:	
			case MENU_HOLDNOTE:
			case MENU_HOLDNOTE5:
			case MENU_HOLDNOTE10:
			case MENU_HOLDNOTE20:	
			//���׼�¼	
			case MENU_PAYMENTSJIDU:
			case MENU_GOODSJIDU:
			case MENU_CLEARTRANSJIDU:
			//ϵͳ����
			case MENU_GPRSONOFF:
			case MENU_SERIALNO:
			case MENU_GSMNO:
			case MENU_TEMPERATURE:
			case MENU_TEMPSET:
			case MENU_LEDSET:
			//�������	
			case MENU_SETCHANNEL:	
			//����Ĭ������	
			case MENU_DEFAULTSET:	
				KeyTab[i].KeyTab_Visible = MENU_VISIBLE_FAUSE;
				break;
		}
	}	
	for(i = 0;i < MAX_KEYTABSTRUCT_NUM;i++)
	{
		switch(KeyTab[i].KeyTab_MenuIndex)
		{			
			//ҵ�����	
			case MENU_OPENCOIN:				
			case MENU_OPENNOTE:
			case MENU_OPENCHANGE:
			case MENU_OPENREADER:
			case MENU_SYSLANGUAGE:
				KeyTab[i].KeyTab_Visible = MENU_VISIBLE_TRUE;
				break;
		}
	}	
}

//���ÿ���״̬
void RstTurkeyVisibleParaInit(void)
{
    uint16_t i;
	
	for(i = 0;i < MAX_KEYTABSTRUCT_NUM;i++)
	{
		switch(KeyTab[i].KeyTab_MenuIndex)
		{	
			//��������
			case MENU_CHANNELNO:
			case MENU_PRICE:
			case MENU_CHANNELLEFT:
			case MENU_CHANNELSTAT:
			case MENU_CHANNELGOODS:	
			//ҵ�����	
			case MENU_OPENCOIN:				
			case MENU_OPENNOTE:
			case MENU_OPENCHANGE:
			case MENU_OPENREADER:
			case MENU_SYSLANGUAGE:	
				KeyTab[i].KeyTab_Visible = MENU_VISIBLE_TRUE;
				break;
		}
	}	
}



//����Ͷ����״̬ ���� ʹ��
void SetTouBiStat(uint8_t CommandType)
{
    uint8_t err;

	
	Trace("\r\nSetTouBiStat = %u",CommandType);
	
	OSMboxAccept(g_CommBackMsg);
	MsgBack.CmdType = (uint32_t)CommandType << 24;		  
	OSMboxPost(g_CommMsg,&MsgBack.CmdType);	   						
	OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC*8,&err);
}

