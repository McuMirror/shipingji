/*******************************************************************


 ������Ҫ����һЩȫ�ֱ��� 

 ����Ԥ���巽ʽ,���������ļ�����ʱ�ظ���������� 

********************************************************************/
#ifndef GLOBAL
#define GLOBAL

#ifdef __cplusplus
    extern "C" {
#endif
#include "..\config.h"
#include "..\driver\LPC17xx.h"
#include "..\driver\lpc17xx_gpio.h"
#include "..\driver\lpc17xx_rtc.h"
#include "..\driver\lpc17xx_pinsel.h"
#include "keypad.h"
#include "timer.h"
#include "MdbNote.h"
#include "Mdbcoin.h"
#include "gbahr1.h"
#include "uart.h"
#include "uart1.h"
#include "i2c.h"

//120914 by cq Cashless
#include "reader.h"
#include "task.h"

//#define MDBDEBUG        1		     	//MDB����
#define EVBDEBUG        0			 	//EVB����
#define GBADEBUG        0			 	//232ֽ��������
#define BEEPDEBUG       0			 	//Ͷ��ʱ��������

#define SOFTVERSION	    0x1300			//����汾xx.yy  xx�����ȱʡ����
#define HAEDWAREVERDION	0x1700			//Ӳ���汾

/*��������*/
#define  KEY_4X6   0			 		//4*6����
#define  KEY_2X8   1			 		//2*8����
#define  KEY_MODE    KEY_2X8

/*��ʾ��ʽ����*/
#define LCD_DISPLAY  0	                //LCD��ʾģʽ
//#define LED_DISPLAY  1	                //LED��ʾģʽ
#define DISP_MODE	 LCD_DISPLAY

/*���������뷽ʽ����*/
#define ONE_Bit_MODE	 0	            //1λ����������뷽ʽ
#define TWO_Bit_MODE	 1	            //2λ����������뷽ʽ
#define CHNINPUT_MODE	 TWO_Bit_MODE

/*��������������*/
#define DRV_12 	  0						//12������
#define DRV_64 	  1						//64������
#define DRV_TYPE 	  DRV_64

/*FLASH����*/
#define AT45DB081D   0					//AT45DB081D
#define AT45DB161D   1  				//AT45DB161D
#define FLASH_TYPE   AT45DB161D

/*ʱ������*/
#define PCF8563T_CFG 0					//PCF8563T
#define LPC_RTC_CFG  1  				//LPC_RTC
#define RTC_TYPE     PCF8563T_CFG

#define SALETIME    30000				//Ͷ�ҳ�ʱʱ��(SALETIME/100)s
#define SALETIME2   500				    //3000-500��������ʱ��(SALETIME2/100)s
#define SALETIME3   3000				//(SALETIME3/100)s

/*����Ϊ1������Ӧ�豸��Ϊ0������Ӧ�豸*/
#define GBAHRDEVICE    1				//GBA HR1
#define MBVDEVICE      1				//MDBֽ����
#define COINDEVICE     1				//MDBӲ����
#define PULSEDEVICE    1				//���������豸
#define HOPPERDEVICE   1				//Hopper
#define DRVDEVICE      1				//����������

/*ֽ�������Ͷ���*/
#define	NOTE_CLOSE	   	0
#define	NOTE_MEI		1
#define	NOTE_GBA		2
#define	NOTE_ITL		3

//�������˵�;by gzz 20121120
//����������
#define	READEDR_CLOSE	   	0
#define	READEDR_MDB			1


#if  FLASH_TYPE == AT45DB081D
#define PAGESIZE 264		//08
#elif  FLASH_TYPE == AT45DB161D
#define PAGESIZE 528		//16
#endif	

#if KEY_MODE == KEY_4X6
#elif KEY_MODE == KEY_2X8
#define KEY_1      0x0C			 //���� 1
#define KEY_2      0x0D
#define KEY_3      0x0E
#define KEY_4      0x09
#define KEY_5      0x08
#define KEY_6      0x0F
#define KEY_7      0x0B
#define KEY_8      0x0A
#define KEY_9      0x04
#define KEY_0      0x06
#define KEY_DOT    0x05			//���� .
#define KEY_SET    0x03
#define KEY_CLR    0x03
#define KEY_UP     0x07
#define KEY_DOWN   0x00
#define KEY_CANCEL 0x01
#define KEY_ENTER  0x02			//���� ENTER
#endif

/****************************************************************************************/
#define MVC_BEGIN    	  0							//��ʼ״̬
#define MVC_SALE 	      1							//����״̬
#define MVC_XUANHUO    	  2							//ѡ��
#define MVC_WUHUO    	  3							//�޻�
#define MVC_CHUHUO  	  4							//����
#define MVC_LESSMONEY 	  5							//Ǯ����
#define MVC_ADDMONEY 	  6							//��Ǯ
#define MVC_RETRANS  	  7							//��������
#define MVC_PAYOUT 	      8							//����
#define MVC_OVERVALUE	  9							//��ֵ̫��
#define MVC_INPUT	      10							//�����������״̬
#define MVC_INPUTERR	  11						//�����������
#define MVC_CHAXUN	      12							//������ѯ״̬
#define MVC_SAVEDAT		  13                         //��Ҫ���潻�׼�¼
#define MVC_CHAOSHI		  14                        //������ʱ״̬
#define MVC_VMCRST		0xF0
#define MVC_IDLE        0xFF
/*******************************************************************************************/

#define MAXLAYER 		8	 					//������� 8
#define MAXLAYER_6 		6	 					//������� 8


//121105 by cq TenChannels
#if 0//����10��������;by gzz 20121226
#define MAXCHANNEL 		8	 					//�������� 8
#else
#define MAXCHANNEL 		10	 					//�������� 8
#endif

#define HOPPERNUM 		3	 					//hopper��

#define	MAXGOODS		26						//������������
#define	MAXINCOME		32						//����ձ�ͨ����
#define	MAXOUTCOME		32						//����ұ�ͨ����
#define	MAXTRANPAGE		4000					//���洢����ҳ����

#define WRITE			1
#define READ			0

//�豸״̬
#define DEVICE_OK   		   0x00		  		//�豸����
#define DEV_ERR_NOTE           0xF1		  		//ֽ��������
#define DEV_ERR_COIN           0xF2		  		//Ӳ��������
#define DEV_ERR_CHANGER        0xF3		  		//������������
#define DEV_ERR_COINLOW        0xF4		  		//������Ӳ�Ҳ���
#define DEV_ERR_CHNOUT         0xF5		  		//����ͨ���޻�
#define DEV_ERR_CHNALL         0xF6		  		//����ͨ������
#define DEV_ERR_DRVCOMM        0xF7		  		//�������������
#define DEV_ERR_CHNDIS         0xF8		  		//���л���������
#define DEV_ERR_PARASET        0xF9		  		//�������ó���
#define DEV_ERR_LCDCOMM        0xFA		  		//LCD����
#define DEV_ERR_PRICESET       0xFB		  		//�۸����ó������ó�0��
#define DEV_ERR_GOODSCHK       0xFC		  	//����ȷ��ģ�����
#define DEV_ERR_FLASH          0xFD		  		//Flash����
#define DEV_ERR_RTC            0xFE		  		//ʵʱʱ�ӳ���
#define DEV_ERR_READER         0xC4       //120914 by cq Cashless

#define DEV_ERR_BIT_NOTE       (1 << 0)		  		//ֽ��������
#define DEV_ERR_BIT_COIN       (1 << 1)		  		//Ӳ��������
#define DEV_ERR_BIT_CHANGER    (1 << 2)		  		//������������
#define DEV_ERR_BIT_COINLOW    (1 << 3)		  		//������Ӳ�Ҳ���
#define DEV_ERR_BIT_CHNOUT     (1 << 4)		  		//����ͨ���޻�
#define DEV_ERR_BIT_CHNALL     (1 << 5)		  		//����ͨ������
#define DEV_ERR_BIT_DRVCOMM    (1 << 6)		  		//�������������
#define DEV_ERR_BIT_CHNDIST    (1 << 7)		  		//���л���������
#define DEV_ERR_BIT_PARASET    (1 << 8)		  		//�������ó���
#define DEV_ERR_BIT_LCDCOMM    (1 << 9)		  		//LCD����
#define DEV_ERR_BIT_PRICESET   (1 << 10)		  		//�۸����ó������ó�0��
#define DEV_ERR_BIT_GOODSCHK   (1 << 11)		  		//����ȷ��ģ�����
#define DEV_ERR_BIT_FLASH      (1 << 12)		  		//Flash����
#define DEV_ERR_BIT_RTC        (1 << 13)		  		//ʵʱʱ�ӳ���
#define DEV_ERR_BIT_READER	   (1 << 14)	//120914 by cq Cashless

//����ͨ��
#define BILLCHMAX			8			   		//ֽ�������ͨ����
#define COINCHMAX			8			   		//Ӳ�������ͨ����
#define HOPPERCHMAX			HOPPERNUM	   		//���������ͨ���� = 3

#define DEV_IN1_BASE       	0	 			 	//Ͷ���豸1��IncomeValue[MAXINCOME]�е���ʼλ��
#define DEV_IN1_NUM			8	  				//Ͷ���豸1ͨ���� <= 8
#define DEV_IN2_BASE        16
#define DEV_IN2_NUM			8		
#define DEV_OUT1_BASE       0	 				//�����豸1��OutcomeValue[MAXINCOME]�е���ʼλ��
#define DEV_OUT1_NUM		8	 				//�����豸1ͨ���� <= 8
#define DEV_OUT2_BASE       16
#define DEV_OUT2_NUM		8
/*ע����Ҫ�ص�*/

#define CHANGE_HOPPER_BASE		DEV_OUT2_BASE	      //Hopper����ͨ����ʼֵ   
#define CHANGE_HOPPER_NUM       HOPPERNUM             //Hopper����ͨ����
#define COIN_PULSE_BASE			DEV_IN1_BASE		  //PULSEͶ��ͨ����ʼֵ
#define COIN_PULSE_NUM  		DEV_IN1_NUM			  //PULSEͶ��ͨ����
#define COIN_MDB_BASE		    DEV_IN1_BASE		  //MDBӲ����Ͷ��ͨ����ʼֵ
#define COIN_MDB_NUM  		    DEV_IN1_NUM			  //MDBӲ����Ͷ��ͨ����
#define CHANGE_COIN_BASE		DEV_OUT1_BASE	      //MDBӲ��������ͨ����ʼֵ
#define CHANGE_COIN_NUM  		DEV_OUT1_NUM		  //MDBӲ��������ͨ����
#define NOTE_MDB_BASE			DEV_IN2_BASE		  //MDBֽ����Ͷ��ͨ����ʼֵ
#define NOTE_MDB_NUM  		    DEV_IN2_NUM			  //MDBֽ����Ͷ��ͨ����
#define NOTE_GBA_BASE			DEV_IN2_BASE		  //GBAֽ����Ͷ��ͨ����ʼֵ
#define NOTE_GBA_NUM  		    DEV_IN2_NUM			  //GBAֽ����Ͷ��ͨ����
#define NOTE_ITL_BASE			DEV_IN2_BASE		  //GBAֽ����Ͷ��ͨ����ʼֵ
#define NOTE_ITL_NUM  		    DEV_IN2_NUM			  //GBAֽ����Ͷ��ͨ����

/*ע��COIN_MDB_BASE��CHANGE_COIN_BASEΪͬһ�豸��������һ����ֵ */

#define CMD_TYPE_EVB			0x80				 //EVB����
#define CMD_TYPE_MDB			0x00				 //MDB����

/*EVB���� >= 0x80*/
#define CMD_GOODS_CHECK      0x80				//���������޻�����
#define CMD_GOODS_OUT        0x81				//��������
#define CMD_HOPPER_CHANGE    0x82				//HOPPER��������
#define CMD_ACDC        	 0x85				//ACDC�豸//���ѹ��������;by gzz 20121224


/*MDB���������� < 0x80*/
#define CMD_COIN_CHANGE      0x00				//MDBӲ������������
#define CMD_ALL_DIS          0x01				//����Ͷ���豸��������
#define CMD_ALL_EN           0x02				//����Ͷ���豸ʹ������
#define CMD_NOTE_DIS         0x03				//ֽ������������
#define CMD_NOTE_EN          0x04				//ֽ����ʹ������
#define CMD_COIN_DIS         0x05				//Ӳ������������
#define CMD_COIN_EN          0x06   			//Ӳ����ʹ������
#define CMD_NOTE_STACK       0x07				//ѹ������
#define CMD_NOTE_RETURN      0x08				//�˳�����

#define COIN_DEV_OK           0					//Ӳ����״̬ ����
#define COIN_DEV_ER           (1 << 0)			//Ӳ����״̬ ����
#define COIN_DEV_DIS          (1 << 1)			//Ӳ����״̬ ����
#define COIN_DEV_PERR         (1 << 2)			//Ӳ����״̬ ������
#define COIN_DEV_NONE         (1 << 3)			//Ӳ����״̬ ��

#define NOTE_DEV_OK           0					//ֽ����״̬ ����
#define NOTE_DEV_ER           (1 << 0)			//ֽ����״̬ ����
#define NOTE_DEV_DIS          (1 << 1)			//ֽ����״̬ ����
#define NOTE_DEV_PERR         (1 << 2)			//ֽ����״̬ ������
#define NOTE_DEV_NONE         (1 << 3)			//ֽ����״̬ ��

#define CHANGER_OK            0					//������״̬ ����
#define CHANGER_ER            (1 << 0)			//������״̬ ����
//#define CHANGER_DIS           (1 << 1)				//������״̬ ����
#define CHANGER_LOW           (1 << 2)			//������״̬ ȱ��
#define CHANGER_NONE          (1 << 3)			//������״̬ ��

#define HR_NOTE_EN	          NOTE_GBA			//ʹ��GBAֽ����
#define MDB_NOTE_EN	          NOTE_MEI			//ʹ��MDBֽ����
#define ITL_NOTE_EN	          NOTE_ITL			//ʹ��ITLֽ����


#define PULSE_COIN_EN 	      1					//ʹ������Ӳ����
#define MDB_COIN_EN 	      2					//ʹ��MDBӲ����
#define HOPPER_CHANGER_EN 	  1					//ʹ��HOPPER������
#define MDB_CHANGER_EN 	      2					//ʹ��MDB������

#define MDB_COINNUMMIN        10			    //MDB������	����Ӳ��������

//����״̬
#define CHANNELDISABLE		  0	                //��������
#define CHANNELOK			  1	                //��������
#define CHANNELHARDERR		  2	                //��������
#define CHANNELOVER			  3					//����ȱ��
//#define CHANNELCOMMERR		4

#define  OVER_VALUE_INDEX	   0x01	            //��ֵ̫��
#define  RETURN_MONEY_INDEX	   0x02	            //�˱�

#define  COIN_TEST_BIT         0x01	            //ά��״̬�£�Ӳ��Ͷ�Ҳ���ʹ��λ
#define  NOTE_TEST_BIT         0x02	            //ά��״̬�£�ֽ��Ͷ�Ҳ���ʹ��λ
					 			
//#define GetChannelNo(x,y)    (x) * MAXCHANNEL + (y) + 1;	
//#define GetChannelNo(x,y)    (MAXLAYER - (x) - 1) * MAXCHANNEL + (MAXCHANNEL - (y) - 1) + 1;
//#define GetChannelNo(x,y)      (MAXLAYER - (x) - 1) * MAXCHANNEL + (y) + 1;	 //��ȡʵ�ʻ�����
#define GetChannelNo8(x,y)      (MAXLAYER - (x) - 1) * 8 + (y) + 1;	 //��ȡ8����ʵ�ʻ�����
#define GetChannelNo10(x,y)      (MAXLAYER - (x) - 1) * 10 + (y) + 1;	 //��ȡ10����ʵ�ʻ�����


#define SetHaveSaleFlag()  	   g_pvmcFlag.HaveSale = 1			//�ѽ��й���������
#define RstHaveSaleFlag()  	   g_pvmcFlag.HaveSale = 0			//��λ�ѽ��й����ױ�־
#define IsHaveSaled()      	   (g_pvmcFlag.HaveSale == 1)			//�ж��Ƿ��ѽ��й�����

#define SetDoubtTrans()    	   g_pvmcFlag.DoubtTrans = 1			//���ʽ�������
#define RstDoubtTrans()        g_pvmcFlag.DoubtTrans = 0			//��λ���ʽ�������
#define IsDoubtTrans()         (g_pvmcFlag.DoubtTrans == 1)		//�ж��Ƿ������ʽ���

#define EnableMoneyIn()        g_pvmcFlag.MoneyInEN = 1			//ʹ��Ͷ��������
#define DisableMoneyIn()       g_pvmcFlag.MoneyInEN = 0			//����Ͷ��������
#define IsMoneyInEN()          (g_pvmcFlag.MoneyInEN == 1)		//�ж��Ƿ���ʹ��Ͷ����״̬

#define EnterMaintainStat()    g_pvmcFlag.Maintain = 1			//ά��״̬
#define ReturnSaleStat()   	   g_pvmcFlag.Maintain = 0			//����״̬
#define SetReInitStat()        g_pvmcFlag.Maintain = 0xFF			//��ά��״̬�˻ؽ���״̬
#define BeSaleStat()          (g_pvmcFlag.Maintain == 0)			//�ж��Ƿ��ǽ���״̬
#define IsMaintainStat()      (g_pvmcFlag.Maintain == 1)			//�ж��Ƿ���ά��״̬
#define IsReInitStat()        (g_pvmcFlag.Maintain == 0xFF)		//�ж��Ƿ��Ǵ�ά��״̬�˻ؽ���״̬

#define SetDevStatus(bit)      g_pvmcFlag.DevStatus |= (bit)		//�����豸����Ϊ
#define ClrDevStatus(bit)      g_pvmcFlag.DevStatus &= ~(bit)		//����豸����λ
#define GetDevStatus()         g_pvmcFlag.DevStatus				//��ȡ�豸����״̬
#define RstDevStatus()         g_pvmcFlag.DevStatus = DEVICE_OK	//��λ�豸����״̬
#define IsDeviceOK()           (g_pvmcFlag.DevStatus == DEVICE_OK)//�ж��豸����״̬

#define NoteEscrowSet()        g_pvmcFlag.BillEscrowed = 1	    //��ֽ�Ҵ�ѹ��
#define NoteEscrowHold()       g_pvmcFlag.BillEscrowed = 2	    //ֽ���ݴ�״̬
#define NoteEscrowClr()        g_pvmcFlag.BillEscrowed = 0		//���ֽ���ݴ�״̬
#define IsEscrowSta()          (g_pvmcFlag.BillEscrowed == 1)		//�ж��Ƿ��д�ѹ����ֽ��
#define IsEscrowHold()         (g_pvmcFlag.BillEscrowed == 2)		//�ж��Ƿ����ݴ�״̬

#define SetCoinTest()          g_pvmcFlag.TouBiTest |= COIN_TEST_BIT	  //��ʼ����Ӳ����
#define SetNoteTest()          g_pvmcFlag.TouBiTest |= NOTE_TEST_BIT	  //��ʼ����ֽ����
#define RstTouBiTest()         g_pvmcFlag.TouBiTest = 0				  //��λͶ�Ҳ��Ա�־
#define RstCoinTest()          g_pvmcFlag.TouBiTest &= ~COIN_TEST_BIT	  //��������Ӳ����
#define RstNoteTest()          g_pvmcFlag.TouBiTest &= ~NOTE_TEST_BIT	  //��������ֽ����
#define IsCoinTest()           (g_pvmcFlag.TouBiTest & COIN_TEST_BIT)	  //���ڲ���Ӳ����
#define IsNoteTest()           (g_pvmcFlag.TouBiTest & NOTE_TEST_BIT)	  //���ڲ���ֽ����

/*���ڽ���ѡ��*/
#define RstInputNum()          g_KeyStat.InputNum = 0; g_KeyStat.InputCnt = 0  //InputNum��ָ�������������ֵ�����ø�λ���ְ���
#define CalcInputNum(key)      g_KeyStat.InputNum * 10 + key		           //��������ֵ
#define RstInputMode()	       g_KeyStat.InputMode = 0			           //��ֹ�������ְ���
#define SetInputMode()	       g_KeyStat.InputMode = 1			           //�����������ְ���

//���Ʒ;��Ļ�ļ���;by gzz 20121025
#define IsLargeLCD() 		 ( (SYSPara.LCDSel==1)||(SYSPara.LCDSel==2) )

/*------------------------- GLOBAL CONSTANTS ------------------------ */
//	#define TRUE            1       /* boolean TRUE value */
//	#define FALSE           0       /* boolean FALSE value */
//	#define BUFFERSIZE      240      /* size of character input buffer */
//	#define FIXED           0       /* fixed tune */
//	#define boolean         int     /* make a boolean data type */
//	#define ESC             27      /* ESCAPE character */
//	#define OK              1       /* successful function execution */
//	#define ERROR           0       /* unsuccessful function execution */
//	#define SPACE           0x20    /* hex representation for a space */
//	#define LF              0x0A    /* Line Feed */
//	#define CR              0x0D    /* carriage return*/
//	#define BS              0x08    // back space
//	#define EOB             0x07    // end of block (bell)
																									   
typedef struct 
{
//uint8_t		ChannelCode;			   //��������
uint16_t	GoodsCode;	   					//��Ʒ����
uint32_t	GoodsPrice;	   					//��Ʒ�۸�
uint8_t		ChannelStat;	 				//����״̬;���������һ����0δ���ԣ�1������2���ϣ�3ȱ��	
/*
//����״̬
bit7�����������ÿ��� ��λΪ�� ����Ϊ��
#define CHANNELDISABLE		  0	                //��������
#define CHANNELOK			  1	                //��������
#define CHANNELHARDERR		  2	                //��������
#define CHANNELOVER			  3					//����ȱ��
//#define CHANNELCOMMERR		4
*/     
uint8_t		GoodsNum;		 				//��Ʒ����
uint32_t	SuccessNum;					 	//�������ɹ����״���
uint32_t	DoubtNum;					 	//���������ʽ��״���
uint8_t		TestNum;						//���Թ��ϴ���

//���ڼ��Ƚ�����;by gzz 20121009
uint32_t	SuccessNumJidu;					 	//�������ɹ����״���


}GoodsChannel ;		 					//��������	total 16 word

typedef struct	
{
	uint8_t		ColMaxGoods[MAXLAYER][MAXCHANNEL];	//ÿ��������������
}ColSystemPara;//������������;by gzz 20121120

typedef struct	
{
	uint8_t		visible[245];	//ÿ���˵��ɼ�
}KeySystemVisible;//�����û��˵��ɼ�;by gzz 20121204

typedef struct	
{
uint16_t	SoftwareVersion;				//����汾
uint16_t	HardwareVersion;				//Ӳ���汾	
uint32_t	Password;

uint8_t     Language;						//����ѡ��

uint32_t	ChangeValue[HOPPERCHMAX];	//��������ֵ
uint32_t	MoneyMaxin;		   			//���Ͷ��ֵ
uint32_t	MoneyMinLeft;	   			//������
char		SerialNo[10];
char		GSMNO[16];
uint32_t    CoinsValue[COINCHMAX];	  	//Ӳ����ֵ
uint32_t    BillValue[BILLCHMAX];	 	//ֽ����ֵ


uint8_t		LayEnable[8];				//������ÿ���
uint8_t		LayMaxGoods[8];				//ÿ����������





uint8_t		ChangeServer;		   		//������Ƿ����
uint8_t		GPRSOnOff;
uint8_t     TransMultiMode;				//�����ν���
uint8_t     TransEscape;				//���������˱�

uint8_t		POSEnable;					//POS������
uint8_t     PCEnable;		   			//ʹ��PC��
uint8_t     LCDSel;                     //ʹ�ô���
uint8_t     KeySel;                     //ʹ��ѡ������//ѡ������;by gzz 20121025
uint8_t     LogoSel;                    //ƴͼ��Ļ��ʽ;by gzz 20121106
uint8_t     GBAEnable;		   			//ʹ��ֽ����
uint8_t     CoinEnable;		   			//ʹ��Ӳ����

uint8_t     ChangerEnable;		   		//ʹ��������
uint8_t		Decimal;		   			//С��λ��
uint8_t     GOCCtr;			   			//����ȷ��

uint8_t     GOCErrorSevice;			   	//121108 by cq GOCErrorSevice

uint8_t     NoteEscrow;					//�ݴ�״̬����
uint8_t     NoteEscrowType[BILLCHMAX];	//ֽ���ݴ�״̬

uint32_t	Password2;//120729 by cq RecordPassword /**/
uint32_t	Password3;//���ڼ��Ƚ�����;by gzz 20121009

uint8_t     ReaderEnable;				//120914 by cq Cashless
uint8_t     ReaderCost;					//120926 by cq Cashless

}SystemPara;							//ϵͳ����

//���ѹ��������;by gzz 20121224
typedef struct	
{
uint8_t DeviceOn;
uint8_t HourOn;
uint8_t	MinOn;
uint8_t HourOff;
uint8_t	MinOff;
}ACDC_TIME;

typedef struct	
{
uint8_t 	BillEnable; 				//ֽ��ʹ��λ//�������ò���ֽ��;by gzz 20121219
ACDC_TIME	CompressorTime;		  		//ѹ��������ʱ��
ACDC_TIME	LEDTime;		  			//չʾ�ƿ���ʱ��
uint8_t     AutoColumn;					//�����ֹ���������;by gzz 20130122
uint8_t     TenColumn;					//�Ƿ�ʹ��ʮ�����Ļ���;by gzz 20130226
}SystemPara2;							//ϵͳ����//����µ�ϵͳ����;by gzz 20121219


/*״ֵ̬Ϊ��Ӧ�豸��״ֵ̬��������豸�ֲ�*/
typedef struct	
{
uint16_t    NoteStat;			   			//ֽ����״̬
uint16_t	CoinsStat;		   				//Ӳ����״̬
uint16_t    HopperStat[HOPPERCHMAX]; 		//������״̬
uint8_t	    CHTestNO;						//�������Դ���
uint8_t     GOCStat;			   			//����ȷ��ģ��״̬
uint8_t     FlashStat;					    //Flash״̬
uint8_t     RTCStat;					    //RTC״̬
uint8_t     AdminStat;					    //����Աģʽ״̬//�û�ģʽ�˵�;by gzz 20121130
uint8_t     VisibleStat;				    //�˵�����״̬//�����û��˵��ɼ�;by gzz 20121204
}SystemPara1;							    //ϵͳ����1	

typedef struct	
{
	 uint8_t	IncomeCH[MAXINCOME];		  	//�ձ�ͨ����¼
	 uint8_t	Goods[MAXLAYER][MAXCHANNEL]; 	//��������
	 uint32_t	Money;							//���׽��
	 uint8_t	OutcomeCH[MAXOUTCOME];		  	//�����¼
	 RTC_TIME_Type	Time;		  				//����ʱ��
	 uint16_t	Check;							//
} Transaction;

typedef struct	
{
	uint16_t	IncomeCH[MAXINCOME];		  	//�ձ�ͨ����¼//����ձ�ͨ����32
	uint16_t	Goods[MAXLAYER][MAXCHANNEL]; 	//��������	   64
	uint32_t	Money;							//�ܽ��
	uint16_t	OutcomeCH[MAXOUTCOME];		  	//�����¼ 32
	RTC_TIME_Type	Time;		  				//����ʱ��	  
	 
	uint16_t	TranPages;	  					//���׼�¼����ҳ���	
	uint32_t	Income;		  					//���ձ�ֵ
	uint32_t	NoteIncome;	  					//ֽ�����ձ�ֵ
	uint32_t	CoinsIncome;  					//Ӳ�����ձ�ֵ
	uint32_t	TotalTrans;	  					//�����ܽ��
	uint32_t	TotalChange;  					//�����ܽ��
	uint32_t	CoinsChange[HOPPERCHMAX];	 	//������������
	uint32_t	SuccessNum;	  					//�ɹ������ܴ���
	uint32_t	DoubtNum;	  					//���ʽ����ܴ���
	uint32_t		Iou;	  					//Ƿ���ܶ�
	uint32_t	DoubtMoney;	  					//���ʽ��
	//���ڼ��Ƚ�����;by gzz 20121009
	uint32_t	IncomeJidu;		  					//���ձ�ֵ
	uint32_t	NoteIncomeJidu;	  					//ֽ�����ձ�ֵ
	uint32_t	CoinsIncomeJidu;  					//Ӳ�����ձ�ֵ
	uint32_t	TotalTransJidu;	  					//�����ܽ��
	uint32_t	TotalChangeJidu;  					//�����ܽ��
	uint32_t	CoinsChangeJidu[HOPPERCHMAX];	 	//������������

	uint16_t	Check;
}TransactionTotal;	   						//�洢����С��256����

typedef struct
{
	/*Bit is set to indicate a coin type is enable or full*/
	uint16_t CoinTypeEN,BillTypeEN;		    //CoinTypeEN,BillTypeEN�����õ�ʹ��λ
	uint16_t BillType,CoinType;				//BillType,CoinType����ǰ��ʹ��λ
	uint16_t CoinFullBit;					//CoinFullBit��MDBӲ������ͨ������־λ
} CashTypeEnBitStruct;						//�ֽ��豸ͨ��ʹ��λ

typedef struct
{
	uint8_t  CHTODRV[MAXLAYER][MAXCHANNEL];	//��������λӳ�����
    uint8_t	 DRVTOCH[MAXLAYER][MAXCHANNEL];	//��������λӳ�����
    uint8_t	 LAYTODRV[MAXLAYER];			//������λӳ��
    uint8_t	 DRVTOLAY[MAXLAYER];			//������λӳ��
} ChannelMapPara;							/*����ʵ�ʱ���������ŵ�ӳ���ϵ����*/

typedef struct
{
	/*Ӳ����ֽ�������������������״̬*/		
    uint8_t   CoinState;
	uint8_t   NoteState;
	uint8_t   ChangerState;	 //
} CashStatStruct;							//�豸״̬

typedef struct
{
    uint32_t  CmdType,pBackMsg;				//�������ͣ�����ֵ
	uint32_t   keyback;						//������Ϣ����ֵ//120622 by cq NewLayer
    uint32_t  moneyback;					//Ͷ����Ϣ����ֵ
    uint32_t  coinPlusback;					//Ͷ����Ϣ����ֵ
    uint32_t  CmdPCType;       				//PC�������ͣ�TASKC�������TASKB
    uint32_t  CmdPCCMDMSG;       			//PC�������ͣ�TASKB�������TASKC
    uint32_t  CmdPCCMDMSGBack;    			//PC�������ͣ�TASKC����ֵTASKB    

	//120914 by cq Cashless
	uint32_t msgRTV;
	uint32_t msgVTR;
} MessageBack;								//�����ֵ

typedef struct
{
	/*��ʱTimeDly*10ms*/
	uint16_t  TimeDly;					   //�ȴ�����/���ҽ���
	uint16_t  OperateDly;				   //�ȴ��ͻ�����
	uint16_t  CheckDly;  	     		   //��ʱ����豸״̬
} TimerDelay;							   //��ʱ

typedef struct  
{
    uint8_t   Channel;						//������ͨ��
	uint32_t  Value;						//������ͨ����Ӧ��ֵ
}  ChangerPara;								//����hopper����ֵ��С����

/*���彻��ѡ��ʱ������״̬�����ڳ������жϽ���״̬��ת*/
typedef struct  
{
    uint8_t   InputMode:4;					//��������ģʽ�������������֣�InputMode = 1���ͽ�ֹ��������ģʽ
	uint8_t   InputCnt:4;					//��������λ������λ��һλ
	uint8_t   InputNum;						//��������ֵ 
}  KEYSTAT;									//����ѡ��ʱ��������

/*����������õ��ĸ��ֱ�־��һͬ�ŵ��ýṹ����*/
typedef struct  
{   
	uint8_t HaveSale:1;						//�Ƿ��ѽ��й����ױ�־
	uint8_t DoubtTrans:1;					//���ʽ��ױ�־
	uint8_t MoneyInEN:1;					//Ͷ����״̬��־
	uint8_t TouBiTest:3;					//Ͷ�Ҳ��Ա�־
	uint8_t BillEscrowed:2;					//ֽ�Ҵ���״̬��־
	uint8_t Maintain;						//ά��״̬��־
	uint16_t DevStatus;						//�豸����״̬
}  PVMCFLAG;

//---------------------------------------------
//XMT�¿�;by gzz 20110105
#define XMT_CTR_DEVADDR     0x01//�豸��ַ
#define XMT_CTR_ADDR        (0x80+XMT_CTR_DEVADDR)//�豸ͷ
#define XMT_CTR_READTEMP    0x52//���������
#define XMT_CTR_SETTEMP     0x43//д�������
#define XMT_CTR_CMDSETTMP   0x00//������������:��д�¶�
#define XMT_CTR_CMDSETHY    0x05//������������:��д�¶ȿ���ƫ�ƾ���
#define XMT_CTR_GETTEMPOPT  1//���¶�
#define XMT_CTR_SETTEMPOPT  0//�趨�¶�
#define XMT_GET_TEMPTIME    1000
#define XMT_TIME_GETTEMPERATURE 10//����¶�





typedef struct 
{ 
    uint8_t Addr;//�豸��ַ
    uint8_t cmd;//���������:52H��д����:43H
    uint8_t cmdSet;//������������
    uint8_t cmdPar[2];//�趨��ֵ
    uint8_t crcEnd;//crcУ��ֵ
    uint8_t recPV[2];
    uint8_t recSV[2];
	uint8_t recHY[2];
    uint16_t  recPVTemp;//������������
	uint16_t  recSVTemp;//�����趨���¶�
	uint16_t  recHYTemp;//�����趨���¶ȿ���ƫ�ƾ���
	uint16_t  temperaTimer;//�����趨���¶�
	uint8_t recBuf[30];	
	uint8_t rectemp;
	uint8_t GetTempeTime;//����¶�
}	XMT_Mission;
//=============================================

 

#ifdef	MAINDEF
#define MAIN_EXTERN 
#else
#define MAIN_EXTERN    extern
#endif

MAIN_EXTERN		GoodsChannel		Channels[MAXLAYER][MAXCHANNEL];	//����������
MAIN_EXTERN		uint16_t			IncomeValue[MAXINCOME];			//Ͷ��ͨ����Ӧ��ֵ
MAIN_EXTERN		uint16_t			OutcomeValue[MAXOUTCOME];		//����ͨ����Ӧ��ֵ
MAIN_EXTERN   	SystemPara			SYSPara;						//ϵͳ������
MAIN_EXTERN   	SystemPara1			SYSPara1;						//ϵͳ������1
MAIN_EXTERN   	SystemPara2			SYSPara2;						//ϵͳ������2//����µ�ϵͳ����;by gzz 20121219
MAIN_EXTERN  	Transaction			TranData;						//�������ݼ�¼
MAIN_EXTERN  	TransactionTotal	TranTotal;						//�ܽ��׼�¼
MAIN_EXTERN  	XMT_Mission         sysXMTMission;                  //�¶ȿ���
MAIN_EXTERN  	ColSystemPara		colSystemPara;					//������������;by gzz 20121120
MAIN_EXTERN  	KeySystemVisible	keyVisible;					    //�����û��˵��ɼ�;by gzz 20121204




/*��С��ֵ������ͨ��*/
MAIN_EXTERN  uint8_t g_ChangeMinCh,g_EscrowMinCh;
/*��ǰֽ����*/				     								
MAIN_EXTERN  uint16_t g_BillNum;				        
/*��ǰ��ͨ�������� ��СӲ����ֵ*/
MAIN_EXTERN  uint16_t g_CoinTypeNum[COINCHMAX],g_CoinMinValue;		 
/*Ͷ���豸ʹ��λ�ṹ�嶨��*/
MAIN_EXTERN  CashTypeEnBitStruct CashTypeEnBit;
/*���ڼ���hopper��ֵ��С����*/
MAIN_EXTERN  ChangerPara HopperPara[HOPPERCHMAX];
/*ѡ��ʱ����״̬*/
MAIN_EXTERN  KEYSTAT	    g_KeyStat;
/*�������õ��ĸ��ֱ�־*/
MAIN_EXTERN  PVMCFLAG		g_pvmcFlag;
/*����ʵ�ʱ���������ŵ�ӳ���ϵ����*/
MAIN_EXTERN  ChannelMapPara		ChnMapPara;
/*Ӳ����ֽ�������������������״̬*/		
MAIN_EXTERN  CashStatStruct CashState;	  //
/*��Ϣ�����ֵ*/
MAIN_EXTERN  MessageBack  MsgBack;
/*��ǰͶ���ܶ� ��ǰʣ�������,��ǰʣ��5��(��#1ͨ��)��Ӳ��ֵ,,��ǰʣ��1Ԫ(��#2ͨ��)��Ӳ������,�豸��������ʾ��ǰʣ����ʵ��ҽ��,*/
MAIN_EXTERN  uint32_t     g_Amount,g_CoinLeft,g_coin1Num,g_coin2Num,g_CoinRealLeft;
/*��ʱ�����ṹ��*/
MAIN_EXTERN  TimerDelay   TimerDly;


//120621 by cq KeySlowly
/*�������д�С*/
#define 	    KEYQUEUE       2 
#define 	    COINPLUSQUEUE       20 
MAIN_EXTERN  	void        *KeyMsgArray[KEYQUEUE]; // ������������
MAIN_EXTERN  	void        *CoinPlusArray[COINPLUSQUEUE]; // ����Ӳ�Ҷ�������


MAIN_EXTERN 	OS_EVENT	*g_InitSem;		// �ź�������,����֪ͨϵͳ��ʼ�����
MAIN_EXTERN 	OS_EVENT	*g_PCSem;		// �ź�������,����֪ͨϵͳPC�˳�ʼ�����
MAIN_EXTERN  	OS_EVENT	*g_CommBackMsg;	// �����ź�������,����֪ͨϵͳ������ɺ����ķ�������(�������еĳ����������һ���ǳɹ�)������Ҳһ��,�Լ�����������ض�����
MAIN_EXTERN 	OS_EVENT	*g_GPRSMsg;		// �ź�������,����֪ͨGPRS�������
MAIN_EXTERN    	OS_EVENT 	*g_CommMsg;		// �����ź�������,����֪ͨϵͳ�г��������,����������,�Լ�����������Ͷ�����
MAIN_EXTERN 	OS_EVENT 	*g_KeyMsg;		// �����ź�������,����֪ͨϵͳ�а�������
MAIN_EXTERN 	OS_EVENT 	*g_MoneyMsg;	// �����ź�������,����֪ͨϵͳ��Ͷ�������//120621 by cq KeySlowly
MAIN_EXTERN 	OS_EVENT 	*g_CoinPlusMsg;	// �����ź�������,����֪ͨϵͳ������Ӳ��Ͷ�������
MAIN_EXTERN 	OS_EVENT 	*g_PCCMDMsg;	// �����ź�������,TASKC����ѯʱ��������PC����ͣ��ͷ��͸�TASKB����
MAIN_EXTERN    	OS_EVENT 	*g_PCCommMsg;	// �����ź�������,TASKB����pc����ʱ�����͸�TASKCҪ����
MAIN_EXTERN  	OS_EVENT	*g_PCCommBackMsg;// �����ź�������,TASKC�������֮�󣬷���TASKB
//120914 by cq Cashless
MAIN_EXTERN		OS_EVENT	*mbVmcToCashless;// �����ź�������,vmc���������·���ָ��
MAIN_EXTERN		OS_EVENT	*mbCashlessToVmc;// �����ź�������,��������vmc���ص�״̬

/*
����:����������������
TASKB��
DoChuhuoMsg()��
//�������루32λ�������λ��1����EVB�������ֽ�Ϊ������룬����Ϊͨ����
MsgBack.CmdType = ch + ((uint32_t)CMD_GOODS_OUT << 24); 
OSMboxPost(g_CommMsg,&MsgBack.CmdType);//֪ͨϵͳ�г��������

TASKC�У�
PCmdMsg = OSMboxPend(g_CommMsg,OS_TICKS_PER_SEC / 10,&err);//����������Ϣ�������õ�������Ҫ����ʲô�豸

TASKC��
DrvOutCommand()��
MsgBack.pBackMsg = pStatus;					 
//OSMboxPost(g_CommBackMsg,(uint32_t *)&pStatus);
OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);


TASKB��
DoChuhuoMsg()��
//�������루32λ�������λ��1����EVB�������ֽ�Ϊ������룬����Ϊͨ����
OSMboxAccept(g_CommBackMsg);
pComStatus = OSMboxPend(g_CommBackMsg,OS_TICKS_PER_SEC * 20,&err);//֪ͨϵͳ������ɺ����ķ�������(�������еĳ����������һ���ǳɹ�)

*/




#ifdef __cplusplus
    }
#endif



#endif
