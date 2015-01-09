/*****************************************************************************
 *   pcf8563t.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __PCF8563T_H 
#define __PCF8563T_H

#define PCF_CENCUTY_BASE	 19				   //��С����ֵ
#define PCF_CUR_CENCUTY		 20				   //��ǰ����ֵ
#define PCF_CENCUTY_BIT	     (1 << 7)		   //�¼Ĵ���������ֵ��־λ

#define PCF_MONTH_MASK		 0x1F			   //��ֵ����
#define PCF_WEEK_MASK		 0x07			   //����ֵ����
#define PCF_DATE_MASK		 0x3F			   //����ֵ����
#define PCF_HOUR_MASK		 0x3F			   //ʱֵ����
#define PCF_MIN_MASK		 0x7F			   //��ֵ����
#define PCF_SEC_MASK		 0x7F			   //��ֵ����

/* For more info, read Philips's PCF8563T datasheet */
#define PCF8563T_ADDR		 0xA2			   //������ַ
#define PCF8563T_CS1		 0x00			   //����״̬�Ĵ���1
#define PCF8563T_CS2		 0x01			   //����״̬�Ĵ���2
#define PCF8563T_SEC		 0x02			   //��Ĵ���
#define PCF8563T_MIN		 0x03			   //�ּĴ���
#define PCF8563T_HOUR		 0x04			   //ʱ�Ĵ���
#define PCF8563T_DATE		 0x05			   //���ڼĴ���
#define PCF8563T_WEEK		 0x06			   //���ڼĴ���
#define PCF8563T_MONTH		 0x07			   //�¼Ĵ���
#define PCF8563T_YEAR		 0x08			   //��Ĵ���
#define PCF8563T_ALARM_MIN	 0x09			   //ALARM�ּĴ���
#define PCF8563T_ALARM_HOUR	 0x0A			   //ALARMʱ�Ĵ���
#define PCF8563T_ALARM_DAY	 0x0B			   //ALARM���ڼĴ���
#define PCF8563T_ALARM_WEEK  0x0C			   //ALARM���ڼĴ���
#define PCF8563T_CLKOUT_FRQ	 0x0D			   //ʱ������Ĵ���
#define PCF8563T_TIMER_CTRL	 0x0E			   //���ƼĴ���
#define PCF8563T_TIMER_VAL   0x0F			   //countdown�Ĵ���

void PCF8563T_Init(void);
void PCF8563T_Start(void);
void PCF8563T_Stop(void);
void PCF8563T_SetTime (uint32_t Timetype, uint32_t TimeValue);
void PCF8563T_SetFullTime(RTC_TIME_Type * pFullTime);
uint32_t PCF8563T_GetTime(uint32_t Timetype);
void PCF8563T_GetFullTime(RTC_TIME_Type * pFullTime);
#endif /* end __PCF8563T_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/
