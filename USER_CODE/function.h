/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               function.h
** Latest modified Date:    2010-04-23
** Latest Version:          1.00
** Descriptions:            �û���д�Ļ����ӿں�������
**
**--------------------------------------------------------------------------------------------------------
** Created by:              yqh
** Created date:            
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __FUNCTION_H 
#define __FUNCTION_H


void XChannels(uint8_t mode);

void XSystemPara(uint8_t mode);

void XSystemPara2(uint8_t mode);

void XColSystemPara(uint8_t mode);//������������;by gzz 20121120

void XSystemPara1(uint8_t mode);

void XKeySystemVisible(uint8_t mode);//�����û��˵��ɼ�;by gzz 20121204

void XTransaction(uint8_t mode);

void RstSystemPara(void);

void RstVisiblePara(void);

void RstTurkeySystemPara(void);

void RstTurkeyVisiblePara(void);

void RstTurkeyVisibleParaInit(void);

void SetTouBiStat(uint8_t CommandType);

#endif
