#ifndef __DISPMENU_H 
#define __DISPMENU_H
#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

typedef struct
 {
 	unsigned short int KeyTab_MenuIndex;  		//��ǰ״̬������
 	unsigned short int KeyTab_MaxItems;  		//�����˵������Ŀ��
    unsigned short int KeyTab_PressOk;   	 	//����"�س�"��ʱת���״̬������
    unsigned short int KeyTab_PressEsc;  		//����"����"��ʱת���״̬������
    unsigned short int KeyTab_PressDown;  		//����"����"��ʱת���״̬������
    unsigned short int KeyTab_PressUp;    		//����"����"��ʱת���״̬������
    unsigned short int KeyTab_Visible;    		//��ǰ��״̬���������û�ģʽ���Ƿ�ɼ�
 	uint8_t    	(*CurrentOperate)(void);   		//��ǰ״̬Ӧ��ִ�еĹ��ܲ���
	char * 		(*InitKeyTab)(void);			//��ǰ״̬��ʼ������
 }KeyTabStruct;									//�˵���ṹ



#define		ROOTNO			8
#define		CHANNELNO		5
#define		DRIVERNO		18
#define		BUSINESSNO		27
#define  	CHANGEVALUENO	3
#define  	SETNOTE			4
#define  	SETREADER		2//�������˵�;by gzz 20121120
#define  	NOTEVALUENO		8
#define  	COINVALUENO		8
#define  	HOLDNOTENO		2
#define  	TRANSACTIONSNO	6
#define		PAYMENTSNO		8
#define		SYSTEMNO		8
#define		LANGUAGENO		4
//121105 by cq TenChannels
//#define		SETCHANNELNO	11
#define		SETCHANNELNO	23

#define 	MAX_KEYTABSTRUCT_NUM      	198

extern  KeyTabStruct  KeyTab[MAX_KEYTABSTRUCT_NUM] ;

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */

#endif
