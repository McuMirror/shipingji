/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           mdb.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        MDBЭ����غ�������
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
#ifndef __MDB_H 
#define __MDB_H

#define MAX_BLOCK_SIZE 36 		    //������ݿ�
#define MDB_ACK 0x00				//Ӧ��
#define MDB_RET 0xAA				//����
#define MDB_NAK 0xFF				//��Ӧ��

#define  MDB_RCV_OK       0x00		//MDB���ݽ�����ȷ
#define  MDB_RCV_INIT     0x80		//��ʼ����MDB����
#define  MDB_RCV_DATA     0x81		//���ڽ���MDB����
#define  MDB_OUT_RANGE    0x82		//MDB���ݽ��ճ���
#define  MDB_CHKSUM_ERR   0x83		//MDB���ݽ���У�����

#define  MDB_ADD          1			//MDB��ַ
#define  MDB_DAT          0			//MDB����

void Mdb_TransmitByte(uint8_t dat,uint8_t mode);
uint8_t Mdb_Session(uint8_t add,uint8_t dat[],uint8_t count);
uint8_t Mdb_ErrJudge(uint8_t x);
void Mdb_ReadBuf(uint8_t *buf, uint8_t len);

#endif /* end __MDB_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
