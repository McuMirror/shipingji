/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           RealTime.c
** Last modified Date:  2011-12-02
** Last Version:         
** Descriptions:        ʵʱʱ����������
**                      
**------------------------------------------------------------------------------------------------------
** Created by:           
** Created date:        2011-12-02
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
#include "..\driver\lpc17xx_rtc.h"
#include "..\config.h"
#include "global.h"
#include "pcf8563t.h"
#include "RealTime.h"

/*****************************************************************************
** Function name:		RTCn_Init
**
** Descriptions:		��ʼ��ʵʱʱ��
**
** parameters:			��
** Returned value:		��
**				
** 
*****************************************************************************/
void RTCn_Init(void) 
{
    #if RTC_TYPE == PCF8563T_CFG
		PCF8563T_Init();
		PCF8563T_Start();
	#else
		/* RTC Block section ------------------------------------------------------ */
		// Init RTC module
		RTC_Init(LPC_RTC);

		/* Enable rtc (starts increase the tick counter and second counter register) */
		RTC_ResetClockTickCounter(LPC_RTC);
		RTC_Cmd(LPC_RTC, ENABLE);
		RTC_CalibCounterCmd(LPC_RTC, ENABLE);
		RTC_CalibConfig(LPC_RTC, 10612, RTC_CALIB_DIR_FORWARD);
		
		SYSPara1.RTCStat = 0;
	#endif
}

/*****************************************************************************
** Function name:		RTCn_SetTime
**
** Descriptions:		ʱ������
**
** parameters:			Timetype: 
**						RTCN_YEAR����
**						RTCN_MONTH����
**						...
**						TimeValue������ֵ
** Returned value:		��
**				
** 
*****************************************************************************/
void RTCn_SetTime(uint32_t Timetype, uint32_t TimeValue)
{
    #if RTC_TYPE == PCF8563T_CFG
		PCF8563T_SetTime(Timetype, TimeValue);
	#else
		RTC_SetTime(LPC_RTC, Timetype, TimeValue);
	#endif
}

/*****************************************************************************
** Function name:		RTCn_SetFullTime
**
** Descriptions:		����ʱ�䣬�����ꡢ�¡��ա����ڡ����ڡ�ʱ���֡���
**
** parameters:			pFullTime��RTC_TIME_Type*�ṹ��ʽʱ��
** Returned value:		��
**				
** 
*****************************************************************************/
void RTCn_SetFullTime(RTC_TIME_Type *pFullTime) 
{
    #if RTC_TYPE == PCF8563T_CFG
		PCF8563T_SetFullTime(pFullTime);
	#else
		RTC_SetFullTime(LPC_RTC, pFullTime);
	#endif
}

/*****************************************************************************
** Function name:		RTCn_GetTime
**
** Descriptions:		��ȡʱ��
**
** parameters:			Timetype: 
**						RTCN_YEAR����
**						RTCN_MONTH����
**						...
** Returned value:		ʱ��ֵ
**				
** 
*****************************************************************************/
uint32_t RTCn_GetTime (uint32_t Timetype)
{
    #if RTC_TYPE == PCF8563T_CFG
		return PCF8563T_GetTime(Timetype);
	#else
		return RTC_GetTime(LPC_RTC, Timetype);
	#endif
}

 /*****************************************************************************
** Function name:		RTCn_GetFullTime
**
** Descriptions:		��ȡʱ�䣬�����ꡢ�¡��ա����ڡ����ڡ�ʱ���֡���
**
** parameters:			pFullTime��RTC_TIME_Type*�ṹ��ʽʱ��
** Returned value:		��
**				
** 
*****************************************************************************/
void RTCn_GetFullTime(RTC_TIME_Type *pFullTime) 
{
    #if RTC_TYPE == PCF8563T_CFG
		PCF8563T_GetFullTime(pFullTime);
	#else
		RTC_GetFullTime(LPC_RTC, pFullTime);
	#endif
}
