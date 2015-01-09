#ifndef __KEY_H 
#define __KEY_H

//#include <lpc17xx.h>
//#include "..\driver\LPC17xx.h"
//#include "global.h"

#define KEY_NULL 0xFF		//�޼�ֵ
#define KEY_ERR  0xFE		//��ֵ����
#define KEY_MUTI 0xFD		//�����

uint8_t JudgeKey(uint8_t keyvalue);
uint8_t GetKeyValue(void);
void ReadKey(void);
void InitKey(void);
void EINT2_IRQHandler(void);
void EINT2_Init(void);

#endif /* end __KEY_H */

/****************************************************************************
**                            End Of File
*****************************************************************************/

