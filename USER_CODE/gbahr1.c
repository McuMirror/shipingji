/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           gbahr.c
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        GBAֽ������������
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
#include "gbahr1.h"
//#include "gbahr1App.h"//120401 by cq change structor
#include "BillAcceptor.h"




uint8_t GbaAck;		  //ACK�ź�
uint8_t gbabuf[12];	  //GBA����


/*****************************************************************************
** Function name:	Gbahr1_PackAnalysis	
**
** Descriptions:	��POLL��ѯ֮��GBAֽ�������յ�״̬���ݰ�����
**						
**
** parameters:		buf:״̬���ݻ��棬len:״̬���ݳ���
** Returned value:	��	
** 
*****************************************************************************/
void Gbahr1_PackAnalysis(uint8_t *buf, uint8_t len)
{
	 uint16_t status = HR_LCBPRESENT_BIT;
	 uint8_t moneych;

	 moneych = (buf[5] >> 3) & 0x0F;
	 if(buf[3] & HR_ESCROWED_BIT) //ֽ���ݴ�״̬	 escrowed	
	 {		            
		 if(moneych == 0)
		 {
		 	BillAcceptor_SetInValid();
		 } 
		 else 
		 {
		 	moneych -= 1;
		 }
		 BillAcceptor_UpdateAcpt(BILLACCEPTOR_ESCROWED, moneych);
	 } 
	 else if(buf[3] & HR_STACKED_BIT) 	     //�յ�ֽ��״̬	 stacked	
	 {
		 BillAcceptor_ClrInValid();
		 moneych -= 1;
		 BillAcceptor_UpdateAcpt(BILLACCEPTOR_STACKED, moneych);	
	 } 
	 else if(buf[3] & HR_RETURNED_BIT) 	     //�˱�״̬	 returned	
	 {
		 BillAcceptor_ClrInValid();
		 moneych -= 1;
		 BillAcceptor_UpdateAcpt(BILLACCEPTOR_RETURNED, moneych);
	 } 
	
	 if(buf[4] & HR_ERR_MASK1) 
	 {			    
		status |= buf[4] & HR_ERR_MASK1;	        				
	 }
	
	 if(!(buf[4] & HR_LCBPRESENT_BIT))           //LCB unpresent
	 {
	    status &= ~HR_LCBPRESENT_BIT;
	 }
	
	 if(buf[5] & HR_ERR_MASK2) 			         //failure(sensor err)
	 {
	    status |= ((buf[5] & HR_ERR_MASK2) << 8);
	 }
	 
	 //if(status != HR_LCBPRESENT_BIT) {
		BillAcceptor_UpDateStat(status);
	 //}	      	  
}

/*****************************************************************************
** Function name:  Gbahr1_Command		
**
** Descriptions:   ��������		
**					
**
** parameters:	   gbacom:����	
** Returned value: ��ȷ��Ӧ����0�������������	
** 
*****************************************************************************/
static uint8_t Gbahr1_Command(GBACommand gbacom)
{
   uint8_t *pcombuf;
   uint8_t checksum, i, j;
   uint8_t  status, lenth;

   Uart3_ClrBuf();
   
   gbacom.Stx = 0x02;
   gbacom.Lenth = 0x08;
   gbacom.Msgtype = 0x10;
   gbacom.Etx = 0x03;

   pcombuf = (uint8_t *)&gbacom;

   checksum = 0;

   for(i = 1; i < gbacom.Lenth - 2; i++) 
   {
	  checksum ^= pcombuf[i];
   }

   gbacom.chksum = checksum;
   
   for(i = 0; i < 6; i++) 
   {
      Uart3_Write((uint8_t *)&gbacom,gbacom.Lenth);

      OSTimeDly(OS_TICKS_PER_SEC / 10);

	  lenth = Uart3_Read(gbabuf,11);

	  if(lenth == 11) 
	  {
		  status = 0;
	      checksum = 0;
	  		 		 
		 if(gbabuf[0] != 0x02) 
		 {
		    status = ERR_STX;
		 }
		 else if(gbabuf[9] != 0x03) 
		 {
		    status = ERR_ETX;
		 }
		 else 
		 {
			for(j = 1; j < lenth - 2; j++) 
			{
		       checksum ^= gbabuf[j];
		    }

			if(checksum != gbabuf[lenth - 1]) 
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

   return status? status : 11;
}

/*****************************************************************************
** Function name:		
**
** Descriptions:   ʹ��Ͷ��ͨ��		
**						
**
** parameters:	   billtype:ʹ��Ͷ��ͨ����λģʽ����nλ��1���nͨ��ʹ��		
** Returned value: ��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����		
**						
**						
** 
*****************************************************************************/
uint8_t Gbahr1_Enable(uint16_t billtype)
{
   GBACommand gbacom;
   uint8_t  len;

   gbacom.Ack = GbaAck;
   gbacom.Data0 = billtype;
   gbacom.Data1 = 0x14;
   gbacom.Data2 = billtype >> 7;

   len = Gbahr1_Command(gbacom);

   return len;
}

/*****************************************************************************
** Function name:	GBA_HR_Poll	
**
** Descriptions:	��ѯ	
**						
**
** parameters:		billtype:ʹ��Ͷ��ͨ����λģʽ����nλ��1���nͨ��ʹ��		
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
**						
**						
** 
*****************************************************************************/
uint8_t Gbahr1_Poll(uint16_t billtype)
{
   GBACommand gbacom;
   uint8_t  len;

   gbacom.Ack = GbaAck;
   gbacom.Data0 = billtype;
   gbacom.Data1 = 0x11;		 //0x14
   gbacom.Data2 = billtype >> 7;

   len = Gbahr1_Command(gbacom);

   return len;
}

/*****************************************************************************
** Function name:	GBA_HR_Stack	
**
** Descriptions:	ѹ��	
**						
**
** parameters:		billtype:ʹ��Ͷ��ͨ����λģʽ����nλ��1���nͨ��ʹ��		
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
**						
**						
** 
*****************************************************************************/
uint8_t Gbahr1_Stack(uint16_t billtype)
{
   GBACommand gbacom;
   uint8_t  len;

   gbacom.Ack = GbaAck;
   gbacom.Data0 = billtype;
   gbacom.Data1 = 0x31;	   //0x34
   gbacom.Data2 = billtype >> 7;

   len = Gbahr1_Command(gbacom);

   return len;
}

/*****************************************************************************
** Function name:	GBA_HR_Return	
**
** Descriptions:	�˳�	
**						
**
** parameters:		billtype:ʹ��Ͷ��ͨ����λģʽ����nλ��1���nͨ��ʹ��	
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
**						
**						
** 
*****************************************************************************/
uint8_t Gbahr1_Return(uint16_t billtype)
{
   GBACommand gbacom;
   uint8_t  len;

   gbacom.Ack = GbaAck;
   gbacom.Data0 = billtype;
   gbacom.Data1 = 0x51;	   //0x54
   gbacom.Data2 = billtype >> 7;

   len = Gbahr1_Command(gbacom);

   return len;
}

/*****************************************************************************
** Function name:	Gbahr1_ReadBuf	
**
** Descriptions:	��ȡGBA HR1ֽ������������
**						
**
** parameters:		buf:���ݻ��棬len:���ݳ���
** Returned value:	��	
** 
*****************************************************************************/
void Gbahr1_ReadBuf(uint8_t *buf, uint8_t len)
{
	uint8_t i;

	if(len > 11) 
	{
		len = 11;
	}

	for(i = 0; i < len; i++) 
	{
		buf[i] = gbabuf[i];
	}
} 

/*****************************************************************************
** Function name:	Gbahr1_ErrJudge	
**
** Descriptions:	�ж�GBA HR1ͨѶ�Ƿ�����
**						
**
** parameters:		x: GBA HR1����״̬
** Returned value:	TRUE���쳣 FALSE��������	
** 
*****************************************************************************/
uint8_t Gbahr1_ErrJudge(uint8_t x)
{
	if(x != 11) 
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}




/*���GBA����ֽ����*/
void Gbahr1_InitProc(void)
{
    uint8_t len;

	#if GBAHRDEVICE
		GbaAck = 0;	
		len = Gbahr1_Enable(0);			
		if(Gbahr1_ErrJudge(len) == TRUE) 
		{				  //��ȡHRֽ����ͨѶ״̬
		   //GBAHR����	   
		   BillAcceptor_SetCommErr();
		} 																					   		
	#endif
}

/*���³���״̬*/
void Gbahr1_UpDateStackerStat(void)
{

}

