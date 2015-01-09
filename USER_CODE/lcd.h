/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           lcd.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        LCD����������غ�������
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
#ifndef __LCD_H 
#define __LCD_H

//#include <lpc17xx.h>
#include "..\driver\LPC17xx.h"
/*
#define CS_SET()     {GPIO1->FIODIR |= (1 << 24); GPIO1->FIOSET |= (1 << 24);}
#define CS_CLR()     {GPIO1->FIODIR |= (1 << 24); GPIO1->FIOCLR |= (1 << 24);}
#define SID_SET()    {GPIO1->FIODIR |= (1 << 25); GPIO1->FIOSET |= (1 << 25);} 
#define SID_CLR()    {GPIO1->FIODIR |= (1 << 25); GPIO1->FIOCLR |= (1 << 25);} 
#define SCLK_SET()   {GPIO1->FIODIR |= (1 << 26); GPIO1->FIOSET |= (1 << 26);}  
#define SCLK_CLR()   {GPIO1->FIODIR |= (1 << 26); GPIO1->FIOCLR |= (1 << 26);}
#define POWER_ON()   {GPIO1->FIODIR |= (1 << 28); GPIO1->FIOCLR |= (1 << 28);}
#define POWER_OFF()  {GPIO1->FIODIR |= (1 << 28); GPIO1->FIOSET |= (1 << 28);}
#define BUZZER_SET() {GPIO1->FIODIR |= (1 << 31); GPIO1->FIOSET |= (1 << 31);}
#define BUZZER_CLR() {GPIO1->FIODIR |= (1 << 31); GPIO1->FIOCLR |= (1 << 31);}

#define CS_GET()     (GPIO1->FIOPIN & (1 << 24))
#define SID_GET()    (GPIO1->FIOPIN & (1 << 25))
#define SCLK_GET()   (GPIO1->FIOPIN & (1 << 26))
*/
#define LCD_CMD 0		//����
#define LCD_DAT 1		//����

#define LINE0  0x80		//��һ����ʼ��ַ
#define LINE01 0x81		//��1.1����ʼ��ַ
#define LINE02 0x82		//��1.2����ʼ��ַ
#define LINE03 0x83		//��1.3����ʼ��ַ
#define LINE1  0x90		//�ڶ�����ʼ��ַ
#define LINE11 0x91		//��2.1����ʼ��ַ
#define LINE12 0x92		//��2.2����ʼ��ַ
#define LINE13 0x93		//��2.3����ʼ��ַ
#define LINE2  0xE0		//��������ʼ��ַ
#define LINE21 0xE1		//��3.1����ʼ��ַ
#define LINE22 0xE2		//��3.2����ʼ��ַ
#define LINE23 0xE3		//��3.3����ʼ��ַ
#define LINE3  0xF0		//��������ʼ��ַ
#define LINE31 0xF1		//��4.1����ʼ��ַ
#define LINE32 0xF2		//��4.2����ʼ��ַ
#define LINE33 0xF3		//��4.3����ʼ��ַ


#define LCDUP   0x01    //�ϰ���
#define LCDDOWN 0x02    //�°���



#define CHAR_PER_LINE  20	//��������ַ���


//void delay_nus(uint8_t t);
void delay_nms(uint8_t t);
void delay_ns(uint8_t t);
void lcd_send(uint8_t command_data,uint8_t mode);
void LCD_Init(void);
void ClearScreen(void);
void Write_LCD(uint8_t position,const char *dat,uint8_t lenth);
void WriteFull_LCD(uint8_t position,const char *dat,uint8_t lenth);
void Line_Reverse(uint8_t line);
void LCD_WhiteBlock(uint8_t flag);
void Cursor_On(uint8_t chipsel);
void Cursor_Off(uint8_t chipsel);
void SetCursorPost(uint8_t position);
void Draw_ClrGDRam(void);
void Draw_FullBmp(const uint8_t * dp);
void Draw_RECT(uint8_t Yaddr,uint8_t Xaddr,const uint8_t * dp);


//���Ʒ;��Ļ�ļ���;by gzz 20121025
//==================
//==����Ʒ;��Ļ�豸
//==================
void Pitu_LCDInit(void);
void Pitu_LCDSetCursor(unsigned char x,unsigned char y);
void Pitu_LCDDisplaySquare(unsigned char *squ_tab);
void Pitu_LCDPutBmp(const uint8_t *data);
void Pitu_one_word(unsigned char x,unsigned char y,unsigned char *Lib,unsigned char ch_num,unsigned char widthw);
void Pitu_LCDPutCmd(unsigned char cmd);
void Pitu_LCDPutData(unsigned char data);
void Pitu_LCDPutByte(unsigned char data);
void Pitu_LCDClrScreen(void);
void Pitu_LCDClearLine(unsigned char position, uint8_t lineMode,uint8_t ziti);
void Pitu_LCDPrintf(unsigned char position,unsigned char positiony,const char *libstr,uint8_t lenth,uint8_t reverse,uint8_t ziti);//ƴͼ��Ļ��ʽ;by gzz 20121106
void Pitu_LCDPutLOGOBmp(unsigned char position,unsigned char y,unsigned char mode);//ƴͼ��Ļ��ʽ;by gzz 20121106
void Pitu_LCDPutPicBmp(unsigned char mode);



#endif
