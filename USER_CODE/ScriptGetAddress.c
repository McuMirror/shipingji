#include "ScriptGetAddress.h"
#include "uart.h"
#include "global.h"
#include "pcf8563t.h"
#include "SaleTaskFun.h"
#include "UCSGBK.h"
#include "lcd.h"

extern uint32_t DispTimer;
extern uint8_t KeyNumC;

/*****************************************************************************
** Function name:	Draw_RECT	
**
** Descriptions:	ͼ����ʾ���� 	
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void nDraw_RECT(uint8_t Yaddr,uint8_t Xaddr,const uint8_t * dp)  
{ 
    uint8_t j; 
    uint8_t k=0; 
        
    lcd_send(0x34,LCD_CMD);			 //ʹ����չָ�
	for(j = 0; j < 8; j++) { 
        lcd_send(Yaddr++,LCD_CMD);   //Y��ַ 
        lcd_send(Xaddr,LCD_CMD);     //X��ַ 
        lcd_send(dp[k++],LCD_DAT);
		lcd_send(dp[k++],LCD_DAT);
    }
	lcd_send(0x36,LCD_CMD);			 //�򿪻�ͼ��ʾ 
	lcd_send(0x30,LCD_CMD);          //�ص�����ָ�ģʽ  
} 

/*****************************************************************************
** Function name:	LCD_WhiteBlock	
**
** Descriptions:	LCD������ʾ�׿麯�� 	
**					
**
** parameters:		flag:1ȫ���ɰ׿飬0ȫ���
** Returned value:	��
** 
*****************************************************************************/
void nLCD_WhiteBlock(uint8_t *nPtr)
{
    uint8_t command_data,i,j,data;

	/*if(flag == 1)
	{
		data = 0xff;
	}
	else
	{
		data = 0x00;
	}*/
	uint8_t Yaddr,Xaddr,k;
	Yaddr = 5;
	Xaddr = 5;	
	k = 0;
   
	command_data=0x36; 
	lcd_send(command_data,LCD_CMD);
	command_data=0x36; 
	lcd_send(command_data,LCD_CMD);
	command_data=0x01; 
	lcd_send(command_data,LCD_CMD);
	//lcd_send(0x80 + i,LCD_CMD);
	lcd_send(0x80,LCD_CMD);
	//for(j = 0;j < 4;j++)
	{
		lcd_send(5,LCD_CMD);   //Y��ַ 
        lcd_send(5,LCD_CMD);     //X��ַ 
        lcd_send(nPtr[0],LCD_DAT);
		lcd_send(nPtr[1],LCD_DAT);
		lcd_send(6,LCD_CMD);   //Y��ַ 
        lcd_send(5,LCD_CMD);     //X��ַ 
        lcd_send(nPtr[2],LCD_DAT);
		lcd_send(nPtr[3],LCD_DAT);
		lcd_send(7,LCD_CMD);   //Y��ַ 
        lcd_send(5,LCD_CMD);     //X��ַ 
        lcd_send(nPtr[4],LCD_DAT);
		lcd_send(nPtr[5],LCD_DAT);
		lcd_send(8,LCD_CMD);   //Y��ַ 
        lcd_send(5,LCD_CMD);     //X��ַ 
        lcd_send(nPtr[7],LCD_DAT);
		lcd_send(nPtr[8],LCD_DAT);
		//lcd_send(*nPtr++,LCD_DAT);
	}
	/*for(i = 0;i < 32;i++)
	{
		lcd_send(0x80 + i,LCD_CMD);
		lcd_send(0x80,LCD_CMD);
		for(j = 0;j < 16;j++)
		{
			lcd_send(*nPtr++,LCD_DAT);
		}
	}
	for(i = 0;i < 32;i++)
	{
		lcd_send(0x80 + i,LCD_CMD);
		lcd_send(0x88,LCD_CMD);
		for(j = 0;j < 16;j++)
		{
			lcd_send(*nPtr++,LCD_DAT);
		}
	}
	command_data=0x20; 
  	lcd_send(command_data,LCD_CMD);

	*/	
    /*if(SYSPara.LCDSel==1)
    {
   		//Trace("\r\n start block");
   		command_data=0x36; 
		lcd_send_up(command_data,LCD_CMD);
		command_data=0x36; 
		lcd_send_up(command_data,LCD_CMD);
		command_data=0x01; 
		lcd_send_up(command_data,LCD_CMD);
		for(i = 0;i < 32;i++)
		{
			lcd_send_up(0x80 + i,LCD_CMD);
			lcd_send_up(0x80,LCD_CMD);
			for(j = 0;j < 16;j++)
			{
				lcd_send_up(*nPtr++,LCD_DAT);
			}
		}
		for(i = 0;i < 32;i++)
		{
			lcd_send_up(0x80 + i,LCD_CMD);
			lcd_send_up(0x88,LCD_CMD);
			for(j = 0;j < 16;j++)
			{
				lcd_send_up(*nPtr++,LCD_DAT);
			}
		}
		command_data=0x20; 
	  	lcd_send(command_data,LCD_CMD);
		//Trace("\r\n block over"); 
		
    } 
	*/   
}

void ChangeCharBit(uint8_t *ptr,uint8_t *qtr)
{
	char i,j,m,n,k;
/*
#ifdef DIANZHENG12X12
	m = 0;
	n = 0;
	k = 0;
	for(j=0;j<8;j++)
	{
		k = 0;
		while(k<2)
		{
			for(i=0;i<8;i++)
			{
				if((i+n+2)<14)
					qtr[m] |= ((ptr[i+n+2]&(0x01<<j))>>j)<<(7-i);
				else
					qtr[m] |= ((0x00&(0x01<<j))>>j)<<(7-i);
			}
			if(n==8)
				n = 0;
			else
				n = 8;
			m++;
			k++;
		}
	}
	//m = 0;
	n = 0;
	//k = 0;
	for(j=0;j<8;j++)
	{
		k = 0;
		while(k<2)
		{
			for(i=0;i<8;i++)
			{
				if((i+n+14)<26)
					qtr[m] |= ((ptr[i+14+n]&(0x01<<j))>>j)<<(7-i);
				else
					qtr[m] |= ((0x00&(0x01<<j))>>j)<<(7-i);
			}
			if(n==8)
				n = 0;
			else
				n = 8;
			k++;
			m++;
		}
	}
	return;
#endif
*/
#ifdef	ZILEIXING_8X16 
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)
		{	
			*(qtr+j) |= (((*(ptr+i))&(0x01<<j))>>j)<<(7-i);
		}
	}
	m=0;
	for(j=8;j<16;j++)
	{
		for(i=0;i<8;i++)
		{
			*(qtr+j) |= (((*(ptr+i+8))&(0x01<<m))>>m)<<(7-i);
		}
		m++;
	}
	return;
#else
	m = 0;
	n = 0;
	k = 0;
	for(j=0;j<8;j++)
	{
		k = 0;
		while(k<2)
		{
			for(i=0;i<8;i++)
			{
				qtr[m] |= ((ptr[i+n+2]&(0x01<<j))>>j)<<(7-i);
			}
			if(n==8)
				n = 0;
			else
				n = 8;
			m++;
			k++;
		}
	}
	//m = 0;
	n = 0;
	//k = 0;
	for(j=0;j<8;j++)
	{
		k = 0;
		while(k<2)
		{
			for(i=0;i<8;i++)
			{
				qtr[m] |= ((ptr[i+18+n]&(0x01<<j))>>j)<<(7-i);
			}
			if(n==8)
				n = 0;
			else
				n = 8;
			k++;
			m++;
		}
	}
	return;
#endif

}

//����ַ���Unicode��
//***************************************************************************************
//�� �� ����GetScriptUnicode
//�������ܣ����ַ���ͨ����ͼ�ķ�ʽ������ʾ��LCD����
//��    ����DispRow:1����һ�У�2���ڶ���
//			DispLCDFlag:1���ϰ�����2���°���
//			str:��Ҫ��ʾ�ַ���
//			strlen����Ҫ��ʾ�ַ����ĳ���
//			ChangeWhite:1:���ף�0��������
//�� �� ֵ��0
//***************************************************************************************
uint8_t GetScriptUnicode(uint8_t DispRow,uint8_t DispLCDFlag,const char *str,uint8_t strLen,uint8_t ChangeWhite)
{
	uint8_t nUniCode[48]={0},i,j;
	uint8_t mUniCode[24]={0};
	uint32_t UnicodeLen = 0,UnicodeLen1=0;
	uint32_t ScriptAdd[48]={0};
	uint32_t ScriptAdd1[10]={0};
	uint8_t OneScriptUnicd[20]={0};
	uint8_t nStr[24]={0};

#ifdef ZILEIXING_8X16
	uint8_t ptr[16]={0},qtr[16]={0};
#else
	uint8_t ptr[34]={0},qtr[34]={0};
#endif
	uint8_t keyStr[4]={0};
	//���unicode��
	UnicodeLen = gsmEncodeUcs2(str,nUniCode,strlen(str));
	OS_ENTER_CRITICAL(); 	 //   ucosii add//change by gzz 20121013
	//ͨ��unicode�롣���ݹ�ʽ����ֵĵ����ַ
	Script_GetAddress(nUniCode,ScriptAdd,UnicodeLen/2);
	OS_EXIT_CRITICAL();	//   ucosii add
	//�������ַ����оƬ������������У�������
	DispStrZiFu(DispRow,DispLCDFlag,ScriptAdd,UnicodeLen/2,ChangeWhite);
	return 0;
}

void DispStrZiFu(uint8_t DispRow,uint8_t DispLCDFlag,uint32_t *ZiAddress,uint8_t DispCount,uint8_t ChangeWhite)
{
	uint8_t i,j,h;
#ifdef ZILEIXING_8X16
	uint8_t ptr[16]={0},qtr[16]={0};
	uint8_t ptr1[16]={0},qtr1[16]={0};
#else
	uint8_t ptr[34]={0},qtr[34]={0};
#endif
	uint8_t str[24][17]={0};
	uint8_t str1[24][17]={0}; 

	//��������ֵĵ������У������浽��ά������
	for(i=0;i<DispCount;i++)
	{
	 	//�����ַ��õ�������
#ifdef ZILEIXING_8X16
		GT20L24F6Y_ReadZiku(16,str[i],ZiAddress[i]);
#else
		GT20L24F6Y_ReadZiku(34,ptr,ZiAddress[i]);
#endif
		//����ת
		ChangeCharBit(str[i],str1[i]);
	}
	if(DispLCDFlag == 2)
	{
		//��ʾ����
		lcd_send(0x34,LCD_CMD);			 			//ʹ����չָ�
		lcd_send(0x08,LCD_CMD);
	}
	else
	if(DispLCDFlag == 1)
	{
		//��ʾ����
		lcd_send_up(0x34,LCD_CMD);			 			//ʹ����չָ�
		lcd_send_up(0x08,LCD_CMD);	
	}
	//	
	for(j=0;j<17;j++)
	{
		if(DispRow == 1)
		{
			if(DispLCDFlag == 2)
			{
				lcd_send(0x80+j,LCD_CMD);
				lcd_send(0x80,LCD_CMD);   	//X��ַ 
			}
			else
			if(DispLCDFlag == 1)
			{
				lcd_send_up(0x80+j,LCD_CMD);
				lcd_send_up(0x80,LCD_CMD);   	//X��ַ 
			}
			 
		}  			//Y��ַ 
		else
		if(DispRow == 2)
		{
			//Y��ַ
			if(DispLCDFlag == 2)
			{
				lcd_send(0x80+j+15,LCD_CMD);
				lcd_send(0x80,LCD_CMD);   	//X��ַ 
			}
			else
			if(DispLCDFlag == 1)
			{
				lcd_send_up(0x80+j+15,LCD_CMD);
				lcd_send_up(0x80,LCD_CMD);   	//X��ַ 
			}
		}
		/*if(ChangeWhite==1)
		{
			if(strlen(str1)<24)
			{
				for(sl=0;sl<(24-strlen(str1));sl++)
				{
					str1[strlen(str1)] = 0xff;
				}
			}
			//DispCount = strlen(str1);
		} */
		//lcd_send(0x80,LCD_CMD);   	//X��ַ 
		for(i=0;i<24;i++)
		{
			//��ͬһ����ʾ�����ݵ���λͬ�·��ͳ�ȥ
			//lcd_send(str1[i][j],LCD_DAT);
			//Y��ַ
			if(DispLCDFlag == 2)
			{
				if(ChangeWhite==1)
					lcd_send(0xff&(~str1[i][j]),LCD_DAT);
				else
					lcd_send(str1[i][j],LCD_DAT);
			}
			else
			if(DispLCDFlag == 1)
			{
				if(ChangeWhite==1)
				{
					lcd_send_up(0xff&(~str1[i][j]),LCD_DAT);
				}
				else
					lcd_send_up(str1[i][j],LCD_DAT);
			}
		} 
	}
	if(DispLCDFlag == 2)
	{
		lcd_send(0x0c,LCD_CMD);
		lcd_send(0x36,LCD_CMD);			 //ʹ����չָ�
		lcd_send(0x30,LCD_CMD);          //�ص�����ָ�ģʽ  	 
	}
	else
	if(DispLCDFlag == 1)
	{
		lcd_send_up(0x0c,LCD_CMD);
		lcd_send_up(0x36,LCD_CMD);			 //ʹ����չָ�
		lcd_send_up(0x30,LCD_CMD);          //�ص�����ָ�ģʽ  		
	}
}





/*------------------------------------------------------
�������ƣ�
			Script_GetAddress
�������ܣ�
			��ȡ�ַ��ĵ����ѯ��ַ
����������
			ScriptType�����ַ�����:SCRIPT_ACSII����ACSII��SCRIPT_OTHER������ACSII
			ScriptStr����unicode��ֵ
��������ֵ��
			���ظ��ַ���GT20L�ϵĴ洢��ַ
--------------------------------------------------------*/
uint32_t Script_GetAddress(uint8_t *ScriptStr,uint32_t *GetAddress,uint8_t ziCount)
{
	uint32_t ScriptAddress=0;
	uint32_t MyUnicode1[20] = {0};
	uint32_t MyUnicode2[20] = {0};
	uint8_t ScriptType = 0,i,j;

	j = 0;
	for(i=0;i<ziCount*2;)
	{
		//ASCII���ַ	
		if(ScriptStr[i]==0x00)
		{
			MyUnicode2[j] = (uint32_t)ScriptStr[i+1];
			ScriptType = LADING8X16;
		}
		//������������unicode��ַ
		else
		{
			MyUnicode2[j] = (uint32_t)(ScriptStr[i]<<8)+(uint32_t)ScriptStr[i+1];
#ifdef	ZILEIXING_8X16
			ScriptType = LADING8X16;
#else
			ScriptType = DIANZHENBUDENGKUANG16;
#endif	  
			
		}
		i+=2;
		j++;
	}
	//�ҵ���Ӧ�ĵ������й��򣬲���õ�ַ
	for(i=0;i<ziCount;i++)
	{
		switch(ScriptType)
		{
			//5X7��ASCII�ַ�
			case ASCII5X7:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)(MyUnicode1[i]*8);
				break;
			//7X8��ASCII�ַ�
			case ASCII7X8:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)(MyUnicode1[i]*8+768);
				break;
			//6X12��ASCII�ַ�
			case ASCII6X12:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)((MyUnicode1[i]-0x20)*12+1536);
				break;
			//8X16��ASCII�ַ�
			case ASCII8X16:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)((MyUnicode1[i]-0x20)*16+3072);
				break;
			//8X16�����ASCII�ַ�
			case ASCII8X16CU:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)((MyUnicode1[i]-0x20)*16+5120);
				break;
			//12���󲻵ȿ�ASCII��ͷ(Arial)�ַ�
			case ASCII12_FANGTOU:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)((MyUnicode1[i]-0x20)*26+6656);
				break;
			//12���󲻵ȿ�ASCII����(Times)�ַ�
			case ASCII12_BAIZHENG:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)((MyUnicode1[i]-0x20)*26+9152);
				break;
			//16���󲻵ȿ�ASCII��ͷ(Arial)�ַ�
			case ASCII16_FANGTOU:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)((MyUnicode1[i]-0x20)*34+11648);
				break;
			//16���󲻵ȿ�ASCII����(Times)�ַ�
			case ASCII16_BAIZHENG:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)((MyUnicode1[i]-0x20)*34+14912);
				break;
			//24���󲻵ȿ�ASCII��ͷ(Arial)�ַ�
			case ASCII24_FANGTOU:
				if(MyUnicode1[i]>=0x00&&MyUnicode1[i]<=0xff)
					ScriptAddress = (uint32_t)((MyUnicode1[i]-0x20)*74+18176);
				break;
			//8x16��������ϵ�ַ�
			case LADING8X16:
				if(MyUnicode2[i]>=0x0020&&MyUnicode2[i]<=0x007F)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x0020)*16+25280);
				else
				if(MyUnicode2[i]>=0x00A0&&MyUnicode2[i]<=0x017F)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x0040)*16+25280);
				else
				if(MyUnicode2[i]>=0x01A0&&MyUnicode2[i]<=0x01CF)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x01A0+320)*16+25280);
				else
				if(MyUnicode2[i]>=0x01F0&&MyUnicode2[i]<=0x01FF)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x01F0+368)*16+25280);
				else
				if(MyUnicode2[i]>=0x0210&&MyUnicode2[i]<=0x021F)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x0210+384)*16+25280);
				else
				if(MyUnicode2[i]>=0x1EA0&&MyUnicode2[i]<=0x1EFF)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x1EA0+400)*16+25280);	
			//8X16��ϣ����ϵ�ַ�
				if(MyUnicode2[i]>=0x0370&&MyUnicode2[i]<=0x03CF)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x0370)*16+33216);
			//8X16��������ϵ�ַ�
				if(MyUnicode2[i]>=0x0400&&MyUnicode2[i]<=0x045F)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x0400)*16+34752);
				else
				if(MyUnicode2[i]>=0x0490&&MyUnicode2[i]<=0x04FF)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x0490+96)*16+34752);
			//8x16ϣ������ϵ�ַ�
				if(MyUnicode2[i]>=0x0590&&MyUnicode2[i]<=0x05FF)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x0590)*16+38080);
			//8x16̩���ַ�
				if(MyUnicode2[i]>=0x0E00&&MyUnicode2[i]<=0x0E5F)
					ScriptAddress = (uint32_t)((MyUnicode2[i]-0x0E00)*16+39872);
				break;
			case DIANZHENBUDENGKUANG16:
				//���ȿ�������
				if( MyUnicode2[i] >= 0x0600 && MyUnicode2[i] <= 0x06FF )//alb 1 
				    ScriptAddress = (uint32_t)(34*(MyUnicode2[i]-0x0600)+ 80320); 
				else 
				if( MyUnicode2[i] >= 0xfb50 && MyUnicode2[i] <= 0xfbff )//alb 2 
				    ScriptAddress = (uint32_t)(34*(16*16+MyUnicode2[i]-0xfb50)+ 80320); 
				else 
				if( MyUnicode2[i] >= 0xfe70 && MyUnicode2[i] <= 0xfeff )//alb 3 
				    ScriptAddress = (uint32_t)(34*(16*11+16*16+MyUnicode2[i]-0xfe70)+ 80320);
				//���ȿ�������
				else
				if(MyUnicode2[i] >= 0x0020 && MyUnicode2[i]<=0x007f)
					ScriptAddress = (uint32_t)((MyUnicode2[i] - 0x0020)*34+99904);
				else 
				if (MyUnicode2[i]>=0x00A0 && MyUnicode2[i]<=0x017F) 
	        		ScriptAddress = (uint32_t)((MyUnicode2[i]-0x00A0+96) * 34 +99904); 
				else 
				if (MyUnicode2[i]>=0x01A0 && MyUnicode2[i]<=0x01CF) 
				    ScriptAddress = (uint32_t)((MyUnicode2[i]-0x01A0+320) * 34 +99904); 
				else 
				if (MyUnicode2[i]>=0x01F0 && MyUnicode2[i]<=0x01FF) 
				    ScriptAddress = (uint32_t)((MyUnicode2[i]-0x01F0+368) * 34 +99904); 
				else 
				if (MyUnicode2[i]>=0x0210 && MyUnicode2[i]<=0x021F) 
				    ScriptAddress = (uint32_t)((MyUnicode2[i]-0x0210+384) * 34 +99904); 
				else 
				if (MyUnicode2[i]>=0x1EA0 && MyUnicode2[i]<=0x1EFF) 
				    ScriptAddress = ((uint32_t)((MyUnicode2[i]-0x1EA0+400) * 34 +99904));
				//���ȿ�ϣ����
				if (MyUnicode2[i]>=0x0370 && MyUnicode2[i]<=0x03CF) 
	    			ScriptAddress=(uint32_t)((MyUnicode2[i]-0x0370) * 34 +116768);
				//���ȿ�������
				if (MyUnicode2[i]>=0x0400 && MyUnicode2[i]<=0x045F) 
				    ScriptAddress=(uint32_t)((MyUnicode2[i]-0x0400) * 34 +120032); 
				else 
				if (MyUnicode2[i]>=0x0490 && MyUnicode2[i]<=0x04FF) 
				    ScriptAddress=(uint32_t)((MyUnicode2[i]-0x0490+96) * 34 +120032);
				break;
		}
		//�����ַ
		*(GetAddress++) = ScriptAddress;
	}
	
	return ScriptAddress;
}

