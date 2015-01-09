/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           keypad.c
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
#include "..\driver\lpc_types.h"
#include "..\config.h"
#include "global.h"
#include "keypad.h"

uint8_t newkey,oldkey;					//��ֵ
uint8_t KeyDownStat = FALSE;
/*****************************************************************************
** Function name:	JudgeKey	
**
** Descriptions:	ͨ����õ�ʵ��IO�ڵ�ֵ��ת���õ���ֵ����ֵ	
**					
**
** parameters:		keyvalue:ʵ�ʶ�����IO��ֵ
** Returned value:	����ΰ������кŻ��к�
** 
*****************************************************************************/
uint8_t JudgeKey(uint8_t keyvalue)
{
   	uint8_t key;
	
	switch(keyvalue) 
	{
	   case 0x01: 
	   		key = 0; break;
	   case 0x02: 
	   		key = 1; break;
	   case 0x04: 
	   		key = 2; break;
	   case 0x08: 
	   		key = 3; break;
	   case 0x10: 
	   		key = 4; break;
	   case 0x20: 
	   		key = 5; break;
	   case 0x40: 
	   		key = 6; break;
	   case 0x80: 
	   		key = 7; break;
	   case 0x00: 
	   		key = 0x10; break;
	   default:   
	   		key = 0x20; break;
	}
	return key;
}

/*****************************************************************************
** Function name:	GetKeyValue	
**
** Descriptions:	��ȡ����״̬	
**					
**
** parameters:		��
** Returned value:	����״̬����ֵ���ް�����
** 
*****************************************************************************/
uint8_t GetKeyValue(void)
{
	uint8_t  keyx, keyy, key_x, key_y, delay;
	uint8_t  keyvalue;

	KeyX_SetInput();//������Ϊ����״̬
    KeyY_Set0();//�����0
	delay = 24;
	while(--delay);
    keyx = KeyX_Get();//��ȡ��ֵ

    KeyY_SetInput();//������Ϊ����״̬
    KeyX_Set0();//�����0
	delay = 24;
	while(--delay);
    keyy = KeyY_Get();//��ȡ��ֵ

    #if KEY_MODE == KEY_4X6
		key_x = JudgeKey(~keyx & 0x0F);
		key_y = JudgeKey(~keyy & 0x3F);
	#elif  KEY_MODE == KEY_2X8
		key_x = JudgeKey(~keyx & 0x03);
		key_y = JudgeKey(~keyy);
	#endif

	if((key_x == 0x10) && (key_y == 0x10)) 
	{
	   	keyvalue = KEY_NULL;
	} 
	else if((key_x == 0x10) || (key_y == 0x10)) 
	{
	   	keyvalue = KEY_ERR;
	} 
	else if((key_x == 0x20) || (key_y == 0x20)) 
	{
	   	keyvalue = KEY_MUTI;
	} 
	else 
	{
	    #if KEY_MODE == KEY_4X6
        	keyvalue = key_x * 6 + key_y;
	    #elif KEY_MODE == KEY_2X8
	    	keyvalue = key_x * 8 + key_y;
	    #endif
	}

	 KeyX_SetInput();
	 KeyY_Set0();
	 delay = 24;		  //?????
     while(--delay);
	 	
	 return keyvalue;
}

/*****************************************************************************
** Function name:	ReadKey	
**
** Descriptions:	��ȡ����ֵ	
**					
**
** parameters:		��
** Returned value:	��ֵ
** 
*****************************************************************************/	 
void ReadKey(void)
{
	static uint8_t rdkey;
	int i,j;	
	uint8_t returnkey;//120621 by cq KeySlowly

	if(KeyDownStat == TRUE) 
	{
		if((newkey = GetKeyValue()) == KEY_NULL) 
		{ 	   
		   if((oldkey != KEY_NULL) || (rdkey > 0)) 
		   {
		      BEEPOFF();
		   }
		   rdkey = 0;
		   oldkey = KEY_NULL; 
		   newkey = KEY_NULL;
		   KeyDownStat = FALSE;
		   //NVIC_EnableIRQ(EINT2_IRQn);
		   LPC_PINCON -> PINSEL4 &= ~(3ul << 24);
		   LPC_PINCON -> PINSEL4 |= (1ul << 24);	   //������������жϷ�ʽ
		} 
		else if(oldkey == newkey) 
		{
		   if((newkey != KEY_MUTI) && (newkey != KEY_ERR) && (rdkey == 0)) 
		   {
			   rdkey = 1;				//ȷ�ϼ�ֵ
			   //120621 by cq KeySlowly
			   //KeySlowly Begin
			   MsgBack.keyback = oldkey;			   
			   returnkey=OSQPost(g_KeyMsg,&MsgBack.keyback);
			   for (j = 100; j > 0; j--) 
				{
    				for (i = 0; i < 9000; i++);
						{BEEPON();}
					for (i = 0; i < 9000; i++);
						{BEEPOFF();}
				}	//�������� chen
			   //MsgBack.keyback = oldkey;
			   //OSMboxPost(g_KeyMsg,&MsgBack.keyback);
			   //KeySlowly End
		   } 
		   else 
		   {
		       if((rdkey > 0) && (rdkey < 255)) 
			   {
			       rdkey++;
			   } 
			   else 
			   {
			       rdkey = 0;
			   }
			   if(rdkey == 5) 
			   {
			       BEEPOFF();
			   }
		   }

		}
		else 
		{	 	   
		   //rdkey = 0;
		}
		oldkey = newkey;
	}
}
 
/*****************************************************************************
** Function name:		EINT2_Handler
**
** Descriptions:		�жϷ������external INT handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void EINT2_IRQHandler (void) 
{   
	OS_ENTER_CRITICAL(); 	 //   ucosii add
	OSIntEnter();

	LPC_PINCON -> PINSEL4 &= ~(3ul << 24);		   //�������GPIO����ֹ�ж�
	
	//NVIC_DisableIRQ(EINT2_IRQn);	
	/*
	newkey = GetKeyValue();
	
	if(newkey != KEY_NULL)  {
	    MsgBack.keyback = newkey;
	    OSMboxPost(g_KeyMsg,&MsgBack.keyback);
	}
	*/
	KeyDownStat = TRUE;
	LPC_SC -> EXTINT = 0x04;		/* clear interrupt */
	//NVIC_EnableIRQ(EINT2_IRQn);  

	OSIntExit();
	OS_EXIT_CRITICAL();
}

/*****************************************************************************
** Function name:		EINT2_Init
**
** Descriptions:		Initialize external interrupt pin and
**						install interrupt handler
**
** parameters:			None
** Returned value:		true or false, return false if the interrupt
**						handler can't be installed to the VIC table.
** 
*****************************************************************************/
void EINT2_Init(void)
{

	LPC_PINCON -> PINSEL4 &= ~(3ul << 24);
	LPC_PINCON -> PINSEL4 |= (1ul << 24);	   //��������жϷ�ʽ
	
	LPC_SC -> EXTMODE |= 0x04;	/* INT2 edge trigger */
	LPC_SC -> EXTPOLAR = 0;			/* INT2 is falling edge by default */
	
	zyIsrSet((EINT2_IRQn +16), (unsigned long)EINT2_IRQHandler, PRIO_SEVEN );	
	
	//	NVIC_EnableIRQ(EINT2_IRQn);
	zyIrqEnable();

}

/*****************************************************************************
** Function name:	InitKey	
**
** Descriptions:	���̳�ʼ��ֵ	
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void InitKey(void)
{
	uint8_t delay;
	
	KeyX_SetInput();	//�����ó�����
    KeyY_Set0();		//�����0

	delay = 24;		    //?????
    while(--delay);

	EINT2_Init();		//�жϳ�ʼ��
}

