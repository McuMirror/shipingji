/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           mdb.c
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        mdbЭ����������
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
#include "..\driver\lpc17xx_uart.h"
#include "..\driver\lpc17xx_clkpwr.h"
#include "..\driver\lpc_types.h"
#include "..\driver\UartDev.h"
#include "..\config.h"
#include "global.h"
#include "uart.h"
#include "mdb.h"

uint8_t MdbBuf[MAX_BLOCK_SIZE];		 //MDB���ݻ���
/*****************************************************************************
** Function name:	Mdb_TransmitByte	
**
** Descriptions:	MDB�����ֽ�	
**					
**
** parameters:		dat:���͵����� mode:ģʽ��MDB_ADD:��ַ��MDB_DAT:���ݣ�
** Returned value:	��
** 
*****************************************************************************/
void Mdb_TransmitByte(uint8_t dat,uint8_t mode)
{
	Trace_R(" %02x",dat);//120914 by cq Cashless
	switch(mode) 
	{
		case MDB_DAT:
		Uart2_SetParity(PARITY_F_0);
		Uart2_SendByte(dat);
		break;

		default:
		Uart2_SetParity(PARITY_F_1);
		Uart2_SendByte(dat);
		break;
	}

	Uart2_TransmitWait();
}

/*****************************************************************************
** Function name:	Mdb_Session	
**
** Descriptions:	�Ự�����������������Ӧ	
**					
**
** parameters:		add:MDB���� dat[]:���� count:���ݳ���
** Returned value:	��ȷ��Ӧ���ؽ������ݳ��ȣ����򷵻ش�����
** 
*****************************************************************************/
uint8_t Mdb_Session(uint8_t add,uint8_t dat[],uint8_t count)
{
   uint8_t check,len,i, j, err; 

   #if MDBDEBUG
   int sizeTx;
   extern UartDev_IOB *pUart;
   #endif

   Uart2_ClrBuf();
   Uart2_SetMdbMode();
  
   for(j = 0; j < 8; j++) 
   {    	   
	  #if MDBDEBUG
	  sizeTx = 1;
	  //pUart->BufTx ((void *)&add, &sizeTx, UartDev_FLAG_NONBLOCKING);
	
	  sizeTx = count;
	  //pUart->BufTx ((void *)dat, &sizeTx, UartDev_FLAG_NONBLOCKING);
	  #endif  

      err = 0;
	  check = 0;
      Mdb_TransmitByte(add,MDB_ADD);
      check += add; 
      for(i = 0; i < count; i++) 
	  { 
         Mdb_TransmitByte(dat[i],MDB_DAT);
	     check += dat[i];
      }
      Mdb_TransmitByte(check,MDB_DAT);

	  #if MDBDEBUG
	  sizeTx = 1;
	  //pUart->BufTx ((void *)&check, &sizeTx, UartDev_FLAG_NONBLOCKING);
	  #endif
     
      OSTimeDly(OS_TICKS_PER_SEC / 5);
	  
	  len = Uart2_Read(MdbBuf,MAX_BLOCK_SIZE);
	  
	  //120914 by cq Cashless
	  Trace_R("\r\nR = %02x - ",len); 
	  for(i = 0; i < len; i++)
		  Trace_R(" %02x",MdbBuf[i]);
	  
	  err = Uart2_ReadMdbStat();
	  Trace_R(" 	err = %02x",err);//120914 by cq Cashless
  
	  if(err == MDB_RCV_OK) 
	  {
	    #if MDBDEBUG
		sizeTx = len;
		//pUart->BufTx ((void *)MdbBuf, &sizeTx, UartDev_FLAG_NONBLOCKING);
		#endif
		break;
      }//if(err == MDB_RCV_OK)

      OSTimeDly(OS_TICKS_PER_SEC / 10);
   }//for j

   return (err != MDB_RCV_OK)? err : (len-1);
}

/*****************************************************************************
** Function name:	Mdb_ReadBuf	
**
** Descriptions:	��ȡMDB����
**						
**
** parameters:		buf�����ݻ��� len�����ݳ���
** Returned value:	��	
** 
*****************************************************************************/
void Mdb_ReadBuf(uint8_t *buf, uint8_t len)
{
	uint8_t i;

	if(len > MAX_BLOCK_SIZE) 
	{
		len = MAX_BLOCK_SIZE;
	}

	for(i = 0; i < len; i++) 
	{
		buf[i] = MdbBuf[i];
	}
} 

/*****************************************************************************
** Function name:	MDB_ErrJudge	
**
** Descriptions:	�ж�MDB��ǰ�������ݵ�״̬����û�д���
**						
**
** parameters:		x:MDB����ص�״ֵ̬
** Returned value:	������TRUE�����򷵻�FALSE	
** 
*****************************************************************************/
uint8_t Mdb_ErrJudge(uint8_t x)
{
  if(x > MAX_BLOCK_SIZE) 
  {
     return TRUE;
  }
  return FALSE;
} 

