/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           RealTime.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        ʵʱʱ������������غ�������
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
#ifndef   _REALTIME_H_
#define   _REALTIME_H_

#include "global.h"

#if RTC_TYPE == PCF8563T_CFG

#define RTCN_TYPE_SEC    PCF8563T_SEC				   //��
#define RTCN_TYPE_MIN    PCF8563T_MIN				   //��
#define RTCN_TYPE_HOUR   PCF8563T_HOUR				   //ʱ
#define RTCN_TYPE_DATE   PCF8563T_DATE				   //����
#define RTCN_TYPE_WEEK   PCF8563T_WEEK				   //����
#define RTCN_TYPE_DOY    							   //һ�������
#define RTCN_TYPE_MONTH  PCF8563T_MONTH		 		   //��
#define RTCN_TYPE_YEAR   PCF8563T_YEAR				   //��

#else

#define RTCN_TYPE_SEC    RTC_TIMETYPE_SECOND	
#define RTCN_TYPE_MIN    RTC_TIMETYPE_MINUTE	
#define RTCN_TYPE_HOUR   RTC_TIMETYPE_HOUR	
#define RTCN_TYPE_DATE   RTC_TIMETYPE_DAYOFMONTH	
#define RTCN_TYPE_WEEK   RTC_TIMETYPE_DAYOFWEEK	
#define RTCN_TYPE_DOY    RTC_TIMETYPE_DAYOFYEAR
#define RTCN_TYPE_MONTH  RTC_TIMETYPE_MONTH		 
#define RTCN_TYPE_YEAR   RTC_TIMETYPE_YEAR

#endif	

void RTCn_Init(void);
void RTCn_SetTime (uint32_t Timetype, uint32_t TimeValue);
void RTCn_SetFullTime(RTC_TIME_Type * pFullTime);
uint32_t RTCn_GetTime(uint32_t Timetype);
void RTCn_GetFullTime(RTC_TIME_Type * pFullTime);
#endif
