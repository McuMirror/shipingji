/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           GBA.c
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        MDBֽ������������
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
#include "BillAcceptor.h"
#include "MdbNote.h"
#include "mdb.h"



/*****************************************************************************
** Function name:	MdbNote_PackAnalysis	
**
** Descriptions:	��POLL��ѯ֮��MDBֽ�������յ�״̬���ݰ�����
**						
**
** parameters:		buf:״̬���ݻ��棬len:״̬���ݳ���
** Returned value:	��	
** 
*****************************************************************************/
void MdbNote_PackAnalysis(uint8_t *buf,uint8_t len)
{     		   	  	
	uint8_t i,nstat = 0;
	
	for(i = 0; i < len; i++) 
	{	                     //report validator activity
	    if(buf[i] & 0x80) 
		{	                         //bill accepted
	        switch(buf[i] & 0x70) 
			{		   		   
	            case 0x00:			                 //bill stacked	   		 			   		   		                         			   
			        BillAcceptor_UpdateAcpt(BILLACCEPTOR_STACKED, (buf[i] & 0x0F));
		            break;
	
	            case 0x10:			                 //escrow position	   			  
					BillAcceptor_UpdateAcpt(BILLACCEPTOR_ESCROWED, (buf[i] & 0x0F));
		            break;
	
	            case 0x20:			                 //bill returned
					BillAcceptor_UpdateAcpt(BILLACCEPTOR_RETURNED, (buf[i] & 0x0F));
		            break;
	
	            case 0x40:			                 //disable bill rejected
	            	break;
	
	            default:				             //others
			        BillAcceptor_UpDateStat(buf[i]);
		            break;
	        }		
	    } 
		else if((buf[i] & 0xF0) == 0) 
		{            //validator status
		    switch(buf[i]) 
			{
	            case 0x01:			                 //defective motor    				   
			        BillAcceptor_UpDateStat(MBV_DEFMOTOERR);
			        break;
		
		        case 0x02:			                 //sensor problem
				    BillAcceptor_UpDateStat(MBV_SENSORERR);
			        break;
		
		        case 0x03:			                 //validator busy
		        	break;
		
		        case 0x04:			                 //rom chksum err
			    BillAcceptor_UpDateStat(MBV_ROMCHKERR);
		        break;
		
		        case 0x05:			                 //validator jammed
				    BillAcceptor_UpDateStat(MBV_VALIDATORJAM);				       
			        break;
		
		        case 0x06:			                 //validator was reset
					BillAcceptor_SetRstStat();	
			        break;
			 
		        case 0x07:			                 //bill removed					   
		        	break;
		 
		        case 0x08:			                 //cash box out of position
				    BillAcceptor_UpDateStat(MBV_CASHBOXERR);
			        break;
		
		        case 0x09:			                 //validator disabled
			        nstat = 1;
					break;
		
		        case 0x0A:			                 //invalid escrow request
		       		break;
		
		        case 0x0B:			                 //bill rejected
		        	break;
		
		        case 0x0C:			                 //possible credited bill removal
				    BillAcceptor_UpDateStat(MBV_BILLREMOVAL);
			        break;
		
		        default:
				    BillAcceptor_UpDateStat(buf[i]);
			        break;
	         }
	    }
		else if((buf[i] & 0xE0) == 0x40) 
		{	 //bill num input while validator is disable
	    }
		else
		{					//others(bill recycler)
	        BillAcceptor_UpDateStat(buf[i]);
	    }			 
	}
	
	if(nstat == 0) {
		BillAcceptor_UpDateStat(0);
	} 
}

/*****************************************************************************
** Function name:	MdbNote_Reset	
**
** Descriptions:	��λ
**						
**
** parameters:		
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
** 
*****************************************************************************/
uint8_t MdbNote_Reset(void)
{
  return Mdb_Session(MBV_RESET,NULL,0); 
}

/*****************************************************************************
** Function name:	MdbNote_Setup	
**
** Descriptions:	��ȡ������Ϣ
**						
**
** parameters:		
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����		
** 
*****************************************************************************/
uint8_t MdbNote_Setup(void)
{
  return Mdb_Session(MBV_SETUP,NULL,0); 
}

/*****************************************************************************
** Function name:	MdbNote_Enable	
**
** Descriptions:	ʹ��Ͷ��ͨ��
**						
**
** parameters:		NoteTypeEn:ʹ��Ͷ��ͨ����λģʽ����nλ��1���nͨ��ʹ��
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
** 
*****************************************************************************/
uint8_t MdbNote_Enable(uint16_t NoteTypeEn)
{
  uint8_t data[4];

  data[0] = NoteTypeEn >> 8; 
  data[1] = NoteTypeEn;
  data[2] = NoteTypeEn >> 8;
  data[3] = NoteTypeEn;
  Trace("\r\n billenable-%x,%x,%x,%x",data[0],data[1],data[2],data[3]);
  return Mdb_Session(MBV_BILLTYPE,data,4); 
}

/*****************************************************************************
** Function name:	MdbNote_Stack	
**
** Descriptions:	ѹ��
**						
**
** parameters:		��
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
** 
*****************************************************************************/
uint8_t MdbNote_Stack(void)
{
  uint8_t status;

  status = 1;
  return Mdb_Session(MBV_ESCROW,&status,1); 
}

/*****************************************************************************
** Function name:	MdbNote_Return	
**
** Descriptions:	�˳�
**						
**
** parameters:		��
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
** 
*****************************************************************************/
uint8_t MdbNote_Return(void)
{
  uint8_t status;

  status = 0;
  return Mdb_Session(MBV_ESCROW,&status,1); 
}

/*****************************************************************************
** Function name:	MdbNote_GetStackerStat	
**
** Descriptions:	��ȡ��������
**						
**
** parameters:		
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
** 
*****************************************************************************/
uint8_t MdbNote_GetStackerStat(void)
{
  return Mdb_Session(MBV_STACKER,NULL,0); 
}

/*****************************************************************************
** Function name:	MdbNote_Poll	
**
** Descriptions:	��ѯ
**						
**
** parameters:		
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
** 
*****************************************************************************/
uint8_t MdbNote_Poll(void)
{
  return Mdb_Session(MBV_POLL,NULL,0); 
}

/*****************************************************************************
** Function name:	MdbNote_Expansion	
**
** Descriptions:	��չ�������level3�ĸ�������
**						
**
** parameters:		subcommand:������ data[]:����  count:���ݳ���
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
** 
*****************************************************************************/
uint8_t MdbNote_Expansion(uint8_t subcommand, uint8_t data[], uint8_t count)
{
  *data = subcommand;		   //���ݴ�data[1]��ʼ�洢��ʹ��ʱע��

  return  Mdb_Session(MBV_EXPANSION,data,count+1);
}

/*****************************************************************************
** Function name:	MdbNote_IDRead	
**
** Descriptions:	����level3,��ȡ�豸���ͺ�ID�ȵ�
**						
**
** parameters:		
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����	
** 
*****************************************************************************/
uint8_t MdbNote_IDRead(void)
{
  uint8_t  data;

  return MdbNote_Expansion(MBV_ID,&data,0); 
} 






/*�ϵ縴λMDBֽ����*/
void MdbNote_RstProc(void)
{
    uint8_t lenth;

	#if MBVDEVICE
	lenth = MdbNote_Reset();			              //GBAֽ������λ
	if(Mdb_ErrJudge(lenth) == TRUE)//�������ִ�н������������MDBֽ������������ 
	{		          
	 //MDB����  
		BillAcceptor_SetCommErr();					     
	} 
	#endif
}

/*MDBֽ������ʼ������*/
void MdbNote_InitProc(void)
{
   uint8_t buf[36],lenth,j;
   BillParaStruct bpara;
   
   MdbNote_RstProc();
   Trace("\r\n bill1");

   if(BillAcceptor_CommErr() == FALSE) 
   {
	   OSTimeDly(OS_TICKS_PER_SEC / 2);
	   lenth = MdbNote_Setup();		             //��ȡֽ��������
	   if(Mdb_ErrJudge(lenth) != TRUE) 
	   {	    
	   	  Trace("\r\n bill2");
	      //ͨ��jֽ����ֵ=BillValue[j]*BillScale/BillDecimal
	      Mdb_ReadBuf(buf,lenth);
		  bpara.Level = buf[0];

		  //120703 by cq MDBCompatible

		  /*
		  bpara.Scale = (((uint16_t)buf[3]) << 8) | buf[4];
		  bpara.Decimal = 1;
		  for(j = 0; j < buf[5]; j++) 
		  {
		     bpara.Decimal *= 10;
		  }
		  */

		  
		  bpara.Decimal = 100;
		  //121106 by cq MDBCompatible
		  //for(j = 0; j < buf[4]; j++) 
		  for(j = 0; j < buf[5]; j++) 
		  {
			 bpara.Decimal /= 10;
		  }
		  bpara.Scale = ((((uint16_t)buf[3]) << 8) | buf[4]) * bpara.Decimal;
		  
		  
	      for(j = 0; j < NOTE_MDB_NUM; j++) 
		  {
			 if(buf[11+j] == 0xFF) 
			 {
			     break;
			 }
			 IncomeValue[NOTE_MDB_BASE+j] = buf[11+j] * bpara.Scale;

			 //121106 by cq MDBCompatible
			  SYSPara.BillValue[j] = buf[11+j] * bpara.Scale;

			 /*
			 if((CashTypeEnBit.BillTypeEN & (1 << j)) && ((buf[11+j] * bpara.Scale) != SYSPara.BillValue[j])) 
			 {
			    BillAcceptor_SetValueErr();
				CashTypeEnBit.BillType = 0;
			 }
			 */
			 //�������ò���ֽ��;by gzz 20121219
			 //if(!((SYSPara2.BillEnable>>j)&0x01))  
			 //{	   
			 //	  IncomeValue[NOTE_MDB_BASE+j] = 0;
			 //     SYSPara.BillValue[j] = 0;
			 //}
		  }

		  /*
		  for(;j < NOTE_MDB_NUM; j++) 
		  {
		     if(SYSPara.BillValue[j] > 0) 
			 {
			    BillAcceptor_SetValueErr();			
				CashTypeEnBit.BillType = 0;
			 }
		  }
		  */
		  bpara.StkCapacity = ((((uint16_t)buf[6]) << 8) | buf[7]);  
		  
		  if(buf[10] == 0) 
		  {
		  	  bpara.EscrowFun = FALSE;
		  }
		  else 
		  {
		  	  //bpara.EscrowFun = TRUE;			  
			  bpara.EscrowFun = FALSE; //120814 by cq NeedNotHoldBill
		  }
		  BillAcceptor_SetBillPara(bpara);
	   }
	   
	  // OSTimeDly(OS_TICKS_PER_SEC / 10);
	  // lenth = MdbNote_IDRead();	             //��ȡֽ����ID��Ϣ
	  
	   OSTimeDly(OS_TICKS_PER_SEC / 10);
	   lenth = MdbNote_GetStackerStat();	//��ȡֽ����ֽ������
	   if(Mdb_ErrJudge(lenth) != TRUE) 
	   {	        
	      Mdb_ReadBuf(buf,lenth);
	      g_BillNum = (((uint16_t)(buf[0] & 0x7F)) << 8) | buf[1];
	
		  if((buf[0] & 0x80)/* || (g_BillNum >= BillNumMax)*/) 
		  {
		     BillAcceptor_SetStackerFull();
			 CashTypeEnBit.BillType = 0;
		  }
	   }	
	   //��ȡֽ��ʹ��ͨ��
	   for(j = 0; j < NOTE_MDB_NUM; j++)
	   {			  
		   if(SYSPara.BillValue[j] > 0) 
		   {
		        CashTypeEnBit.BillTypeEN |= (1 << j);
		   }
	   }	  
	   Trace("\r\n bill3-%d,%d,%d,%d,%d,%d,%d,%d",SYSPara.BillValue[0],SYSPara.BillValue[1],SYSPara.BillValue[2],SYSPara.BillValue[3],SYSPara.BillValue[4],SYSPara.BillValue[5],SYSPara.BillValue[6],SYSPara.BillValue[7]);
   }
}

/*���³���״̬*/
void MdbNote_UpDateStackerStat(void)
{
	uint8_t buf[2],lenth;
	
	lenth = MdbNote_GetStackerStat();	             //��ȡֽ����ֽ������
    if((Mdb_ErrJudge(lenth) != TRUE) && (lenth == 2)) {
       Mdb_ReadBuf(buf,lenth);
	   g_BillNum = (((uint16_t)(buf[0] & 0x7F)) << 8) | buf[1];

	   if((buf[0] & 0x80)/* || (g_BillNum >= BillNumMax)*/) {
	      BillAcceptor_SetStackerFull();
	   }
    }
}

  
/******************************************************************************
**                            End Of File
******************************************************************************/
