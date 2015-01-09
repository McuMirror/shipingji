/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Dispmenu.c
** Last modified Date:  2012-03-01
** Last Version:         
** Descriptions:        ��ʾά��ģ���и��˵�ҳ��
**                      
**------------------------------------------------------------------------------------------------------
** Created by:           
** Created date:        2012-03-01
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


//Last Modify Time:03/11/07 01:22
//ReadMe
//����:112
//����:64

//#include <intrins.h>
#include <absacc.h>
#include "..\driver\lpc_types.h"
#include "global.h"
#include "pcf8563t.h"
#include "RealTime.h"
#include "function.h"
#include "gbahr1.h"
#include "hopper.h"
#include "lcd.h"
#include "menu.h"
#include "drv.h"
#include "dispmenu.h"
#include "DebugTrace.h"		   




  
const char *     Menu_Password[LANGUAGENO][1]=
{
 	{
 		"���������룺" 
	},
	{
 		"Input password��"
 	},
	//change by liya 2012-10-16
	{
		"���ӧ֧էڧ�� ��ѧ��ݧ�:"
	},
	//��������;by gzz 20121115
	{
		"\xf1\x5eifreyi girin:"
	}
};
const unsigned int  Menu_PasswordID[1]=
{
    MENU_PASSWORD 
};
//����˹��;by gzz 20121012
const char *     Menu_Language[2][LANGUAGENO]=
{
 	{
 		"ENGLISH" ,
		"���� ",
		"RUSSIAN",
		"Turkish"//��������;by gzz 20121115
	},
	{
 		"ENGLISH" ,
		"���� ",
		"RUSSIAN",
		"Turkish"//��������;by gzz 20121115
 	}
};

const unsigned int  Menu_LanguageID[LANGUAGENO]=
{
   MENU_ENGLISH ,
   MENU_CHINESE ,
   MENU_RUSSIAN,//����˹��;by gzz 20121012
   MENU_SYSTURKEY	//��������;by gzz 20121115
};
const  unsigned int  Menu_SysLanguageID[LANGUAGENO]=
 {
	MENU_SYSENGLISH ,
	MENU_SYSCHINESE ,
	MENU_SYSRUSSIAN,//����˹��;by gzz 20121012
	MENU_SYSTURKEY	//��������;by gzz 20121115
 };


 //

const char *     Menu_Root[LANGUAGENO][ROOTNO]=
 {
	 {
	 "1 ��������",
	 "2 ����ȫ������",
	 "3 �豸����",
	 "4 ҵ�����",
	 "5 ���׼�¼",
	 "6 ϵͳ����",
	 "7 ��������",
	 "8 ����Ĭ������"	 
	 //"9.ȫϵͳͬ��",
	 //"10. ��Ӳ�����",
	 //"11. ȡֽ�����"
	 },
	 {
	 "1.Column",
	 "2.Add full goods",
	 "3.Device",
	 "4.Parameter",
	 "5.Record inquiry",
	 "6.System",
	 "7.Tray",
	 "8.Default"	 
	 //"9.Goods-Column",
	 //"10.Add coin",
	 //"11.Add Cash"
	 },
	 //change by liya 20121013
	 {
	 "1.����ݧ�ߧܧ�",
	 "2.����ҧѧӧڧ�� ���ݧߧ�� �֧է�",
	 "3.�������ۧ��ӧ�",
	 "4.���ѧ�ѧާ֧�֧�",
	 "5.���ѧ�ڧ�� �٧ѧ�����",
	 "6.���ڧ��֧ާ�",
	 "7.�������",
	 "8.���ާ�ݧ�ѧߧڧ�"
	 //"9.����ݧ�ߧܧ� �֧է�",
	 //"10.���ѧԧ��٧ܧ� �ާ�ߧ֧�",
	 //"11.���ѧԧ��٧ܧ� �ߧѧݧڧ�ߧ��",
	 //"12.����� �ߧ� �է�����֧�",
	 //"13.����� �ߧ� �է�����֧�"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.Sutun parametre",
	 "2.\xf0\xdcr\xf0\xfcn girin",	
	 "3.Cihazlar",
	 "4.Cihaz parametreleri",
	 "5.Kay\xf1\x31t sorgulama",
	 "6.Sistem parametreleri",
	 "7.Tepsi",
	 "8.Varsay\xf1\x31lan ayar"
	 }
 };
const unsigned int  Menu_RootID[ROOTNO]=
{
	 MENU_CHANNEL,
	 MENU_ADDGOODS,
	 MENU_DRIVER,
	 MENU_BUSINESS,
	 MENU_TRANSACTIONS,
	 MENU_SYSTEM,
	 MENU_SETCHANNEL,
	 MENU_DEFAULTSET
	 //MENU_SYNGOODSCOL,
	 //MENU_ADDCOIN,
	 //MENU_ADDBILL
};

const char *     Menu_InputChannelNo[LANGUAGENO][1]=
{
	 {
	  "��������: "
	 },
	 {
	  "Input column code:"
	 },
	 //change by liya 2012-10-16
	 {
	 	"���ӧ�� �ܧ�է� ����ݧҧ��: "
	 },
	 //��������;by gzz 20121115
	 {
	 	"S\xf0\xfctun kodunu girin:"
	 }
};

const unsigned int  Menu_InputChannelNoID[1]=
{
  	MENU_INPUTNUM
};
//

const char *     Menu_Channel[LANGUAGENO][CHANNELNO]=
{
	 {
	 "1.�������: ",
	 "2.����:     ",
	 "3.��Ʒ����: ",
	 "4.����״̬: ",
	 "5.��Ʒ���: "	 
	 },
	 {
	 "1.Column code:",
	 "2.Price:",
	 "3.Goods remain:",
	 "4.Column status:",
	 "5.Goods NO:"
	 },
	 //change by liya 2012-10-16
	 {
	 "1.����� �ܧ�ݧ�ߧܧ�: ",
	 "2.���֧ߧ�: ",
	 "3.�����ѧ�ܧ� �֧է�: ",
	 "4.����ѧ��� �ܧ�ݧ�ߧܧ�: ",
	 "5. ����ާ֧� �֧է�: "
	 },
	 //��������;by gzz 20121115
	 {
	 	"1 S\xf0\xfctun kodu:",
		"2.Fiyat:",
		"3.Kalan \xf0\xfcr\xf0\xfcn:",
		"4 S\xf0\xfctun  durumu:",
		"5.\xf0\xdcr\xf0\xfcn numaras\xf1\x31:"
	 }
};
const unsigned int  Menu_ChannelID[CHANNELNO]=
{
	 MENU_CHANNELNO,
	 MENU_PRICE,
	 MENU_CHANNELLEFT,
	 MENU_CHANNELSTAT,
	 MENU_CHANNELGOODS
};
//

const char *     Menu_AddInputLayerNum[LANGUAGENO][1]=
{
	 {
	 "��������: "
	 },
	 {
	  "Input tray code:"
	 },
	 //change by liya 2012-10-16
	 {
	  "���ӧ֧էڧ�� �ܧ�� �ݧ��ܧ�:"
	 },
	 //��������;by gzz 20121115
	 {
	 "Katman numaras\xf1\x31n\xf1\x31 girin"
	 }
};

const unsigned int  Menu_AddInputLayerNumID[1]=
{
	  MENU_ADDINPUTLAY
};


const  char *     Menu_InputAddGoods[LANGUAGENO][2]=
{
	 {
	 "" ,
	 "ȷ��ENTER ����CANCEL"
	 },
	 {
	 "",
	 "ENTER or CANCEL"
	 },
	 //change by liya 2012-10-16
	 {
	 "",
	 "���ӧ��   �ڧݧ�   �������"
	 },
	 //��������;by gzz 20121115
	 {
	 "",
	 "Giri\xf1\x5f yada iptal"
	 }
};
const unsigned int  Menu_InputAddGoodsID[2]=
{
	  MENU_INPUTADDGOODS,
	  MENU_NULL
};


const char *    Menu_Driver[LANGUAGENO][DRIVERNO]=
{
	 {
	 "1.ֽ����״̬: ",
	 "2.Ӳ����״̬: ",
	 "3.#1������: ",
	 "4.#2������: ",
	 "5.#3������: ",
	 "6.�ֻ�ģ��״̬����",
	 "7.����Ϣ���  ",
	 "8.��ť���  ",
	 "9.����״̬  ",
	 "10. �������  ",
	 "11. ���������",
	 "12. ����ȷ�ϼ��",
	 "13. ��ʾ�����",
	 "14. �¿������",
	 "15. ѡ���������",
	 "16. ѹ�������",//���ѹ��������;by gzz 20121224
	 "17. չʾ�Ƽ��",//���չʾ�ƿ���;by gzz 20121229
	 "18. �洢ʣ��ռ�"
	 },
	 {
	 "1.BillAcceptor:",
	 "2.CoinAcceptor:",
	 "3.ChangeUnit#1:",
	 "4.ChangeUnit#2:",
	 "5.ChangeUnit#3:",
	 "6.GSM status test",
	 "7.SMS test  ",
	 "8.Key test  ",
	 "9.Column status",
	 "10. Column test",
	 "11. ColTest result",
	 "12. GOC test  ",
	 "13. LCD test  ",
	 "14. Temperature test",
	 "15. Choose test",
	 "16. Compressor test",
	 "17. LED test",
	 "18. Flash left"
	 },
	 //change by liya 2012-10-16
	 {
	 "1.����ڧ֧ާߧ� �ܧ����: ",
	 "2.����ڧ֧ާߧڧ� �ާ�ߧ֧�: ",
	 "3.���٧ާ֧ߧ֧ߧڧ� 1UINT: ",
	 "4.���٧ާ֧ߧ֧ߧڧ� 2UINT: ",
	 "5.���٧ާ֧ߧ֧ߧڧ� 3UINT: ",
	 "6.���֧�� ���ѧ���� GSM",
	 "7.���֧�� SMS",
	 "8.���֧�� �ܧߧ����",
	 "9.����ѧ��� �ܧ�ݧ�ߧܧ�",
	 "10.���֧�� �ܧ�ݧ�ߧܧ�",
	 "11.���֧٧�ݧ��ѧ� ��֧��� �ܧ�ݧ�ߧܧ�",
	 "12.���֧�� SMS",
	 "13.���֧�� LCD",
	 "14.���֧�� ��֧ާ�֧�ѧ����",
	 "15.���֧�� ���٧�� �ܧݧ���",
	 "16.����ާ��֧���� ��֧��",
	 "17.LED ��֧��",
	 "18.�����ѧ��� Flash ��ѧާ���"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.Ka\xf1\x1f\xf1\x31t para al\xf1\x31\c\xf1\x31: ",
	 "2.Bozuk para al\xf1\x31\c\xf1\x31: ",
	 "3.De\xf1\x1fi\xf1\x5fim #1: ",
	 "4.De\xf1\x1fi\xf1\x5fim #2: ",
	 "5.De\xf1\x1fi\xf1\x5fim #3: ",
	 "6.Tele test durumu",
	 "7.SMS testi  ",
	 "8.Klavye testi",
	 "9.S\xf0\xfctun Durumu  ",
	 "10.S\xf0\xfctun testi",
	 "11.S\xf0\xfctun test sonuc",
	 "12.Ba\xf1\x5f\ar\xf1\x31l\xf1\x31 i\xf1\x5flem adet testi",
	 "13.LCD testi",
	 "14.Termostat testi",
	 "15.D\xf0\xfc\xf1\x1fmesi Toplama testi",
	 "16.Kompres\xf0\xF6r testi",
	 "17.LED testi",
	 "18.Depolama alan\xf1\x31"
	 }
};
const unsigned int  Menu_DriverID[DRIVERNO]=
{
	 MENU_NOTESTAT,
	 MENU_COINSSTAT,
	 MENU_HOPPERSTAT1,
	 MENU_HOPPERSTAT2,
	 MENU_HOPPERSTAT3,
	 MENU_GPRSTEST,
	 MENU_SMSTEST,
	 MENU_KEYTEST,
	 MENU_ALLCHANNELSTAT,
	 MENU_CHANNELTEST,
	 MENU_CHTESTRESULT,
	 MENU_IRTEST,
	 MENU_LCDTEST,
	 MENU_TEMPRATURETEST,
	 MENU_SELECTKEYTEST,
	 MENU_TEMPSTEST,//���ѹ��������;by gzz 20121224
	 MENU_LEDTEST,//���չʾ�ƿ���;by gzz 20121229
	 MENU_FLASHLEFT
};
const char *     Menu_KeyTest[LANGUAGENO][1]=
{
	 {
	 "�밴�����"
	 },
	 {
	 "Pls press any key"
	 },
	 //change by liya 2012-10-16
	 {
	 "���ӧ֧էڧ�� �ܧ�� ����ݧҧ��:"
	 },
	 //��������;by gzz 20121115
	 {
	 "D\xf0\xfc\xf1\x1fme giriniz"
	 }
};
const  char *     Menu_NoteTestConfirm[LANGUAGENO][2]=
{
	 {
	 "ֽ����������" ,
	 "��ȷENTER ����CANCEL"
	 },
	 {
	 "Bill acceptor OK?",
	 "ENTER or CANCEL"
	 },
	 //change by liya 2012-10-16
	 {
	 "����ڧ֧ާߧڧ� �ܧ���� �ӧ����էܧ�?",
	 "���ӧ��   �ڧݧ�   �������"
	 },
	 //��������;by gzz 20121115
	 {
	 "Ka\xf1\x1f\xf1\x31t para ok?" ,
	 "Giri\xf1\x5f yada iptal"
	 }
};
const unsigned int  Menu_NoteTestConfirmID[2]=
{
	  MENU_NOTETESTCONFIRM,
	  MENU_NULL
};
const char *     Menu_CoinsTestConfirm[LANGUAGENO ][2]=
{
	 {
	 "Ӳ����������" ,
	 "��ȷENTER ����CANCEL"
	 },
	 {
	 "Coin acceptor OK?",
	 "ENTER or CANCEL"
	 },
	 //change by liya 2012-10-16
	 {
	 "����ڧ֧ާߧڧ� �ާ�ߧ֧� �ӧ����էܧ�?",
	 "���ӧ�� �ڧݧ� �������"
	 },
	 //��������;by gzz 20121115
	 {
	 "Bozuk para ok?" ,
	 "Giri\xf1\x5f yada iptal"
	 }
};
const unsigned int  Menu_CoinsTestConfirmID[2]=
{
	  MENU_COINSTESTCONFIRM,
	  MENU_NULL
};
const char *     Menu_DriverInputNum[LANGUAGENO][1]=
{
	 {
	 "��������: "
	 },
	 {
	  "Input column code:"
	 },
	 //change by liya 2012-10-16
	 {
	 "���ӧ֧էڧ�� �ܧ�� �ܧ�ݧ�ߧܧ�: "
	 },
	 //��������;by gzz 20121115
	 {
	 "S\xf0\xfctun xx Hata num.:"
	 }
};

const unsigned int  Menu_DriverInputNumID[1]=
{
	  MENU_DRINPUTNUM
};
//
const unsigned int  Menu_KeyTestID[1]=
{
   	MENU_DOKEYTEST
};
 //

 const char * 	Menu_Business[LANGUAGENO][BUSINESSNO]=
 {
	  {
	  "1.Ӳ������ֵ  ",
	  "2.ֽ������ֵ  ",
	  "3.��������ֵ  ",
	  "4.����Ӳ����: ",
	  "5.ֽ��������: ",
	  "6.����������: ",
	  "7.����������:",
	  "8.��������Ǯ:",
	  "9.������Ƿ����: ",
	  "10. �����ι���: ",
	  "11. ������˱�: ",
	  "12. �������: ",
	  "13. �ձ�����: ",
	  "14. Ƿ����  ",
	  "15. ���ʽ��: ",
	  "16. С����λ��: ",
	  "17. ��������ȷ��: ", 
	  "18. ����POS ��: ",
	  "19. ����PCͨѶ:",
	  "20. ��Ļ����:",//ƴͼ��Ļ��ʽ;by gzz 20121106
	  "21. ʹ��ѡ��������:",
	  "22. ʹ��logo:",
	  "23. �Զ����:",
	  "24. ʮ����:",
	  "25. �Ƿ����ݴ棺",
	  "26. ֽ�� 5Ԫ�ݴ�: ",
	  "27. ֽ��10Ԫ�ݴ�: "//,
	  //"20. ֽ��20Ԫ�ݴ�: "
	  },
	  {
	  "1.Coins type ", 
	  "2.Note type ", 
	  "3.Change type ", 
	  "4.Coin on: ", 
	  "5.Bill on: ", 
	  "6.Change on: ",
	  "7.Reader Type:",
	  "8.Reader Cost:",
	  "9.Nochange SVR:",
	  "10.Multi-verd:",
	  "11.Refund:",
	  "12.ChangeValue:",
	  "13.BanknoteMax:",
	  "14. IOU:",
	  "15.Doubtful Amt:",
	  "16.Decimal num:",
	  "17.GOC_dev on:", 
	  "18. POS on:",
	  "19. PC on:",
	  "20. LCDType:",
	  "21. SelectKey:",
	  "22. Logo:",
	  "23. AutoAdd:",
	  "24. TenColumn:",
	  "25. Hold note:",
	  "26.HoldNote5$: ",
	  "27.HoldNote10$:"//,
	  //"20.HoldNote10$:" 
	 },
	 //change by liya 2012-10-16
	 {
	 "1.���ڧ� �ڧ�ߧ֧�",
	 "2.���ڧ� �ܧ����",
	 "3.���ڧ� ��ѧ٧ާ֧ߧߧڧܧ�",
	 "4.����ߧ֧�� �ӧܧ�.:",
	 "5.�������� �ӧܧ�.:",
	 "6.���ѧ٧ާ֧ߧߧڧ� �ӧܧ�.:",
	 "7.���ڧ�ѧ�֧ݧ� ��ڧ��:",
	 "8.���ڧ�ѧ�֧ݧ�, �٧� �ӧ��֧��� �է֧ߧ֧�:",
	 "9.���֧� ��ѧ٧ާ֧ߧ� ��ҧ�ݧ�اڧӧѧߧڧ�:",
	 "10.����ݧ�� ��֧�֧ߧڧ�:",
	 "11.��֧�֧���֧է֧ݧ֧ߧڧ�:",
	 "12.���ߧѧ�֧ߧڧ� ��ѧ٧ާ֧ߧ�:",
	 "13.���ѧܧ�. ���ѧԧ��٧ܧ�:",
	 "14.IOU:",
	 "15.����ާߧڧ�֧ݧ�ߧ�� Amt:",
	 "16.���֧���ڧ�ߧ�� �ާ�ާ֧�:",
	 "17.GOC-������ۧ��ӧ� �ӧܧ�.:",
	 "18.POS �ӧܧ�.:",
	 "19.PC �ӧܧ�.:",
	 "20.������ߧ�� ��ܧ�ѧ�:",
	 "21.���٧�� �ܧݧ���:",
	 "22. Logo:",
	 "23.�ѧӧ��ާѧ�ڧ�֧�ܧ� �է�ҧѧӧݧ�����:",
	 "24.�է֧����",
	 "25.����ܧݧ��֧ߧڧ� �ܧ����:",
	 "26.����ܧݧ��ڧ�� �ܧ����� 5$:",
	 "27.����ܧݧ��ڧ�� �ܧ����� 10$:"
	 },
	 //��������;by gzz 20121115
	 {
	  "1.Bozuk paran\xf1\x31n de\xf1\x1f\eri",
	  "2.Ka\xf1\x1f\xf1\x31t paran\xf1\x31n de\xf1\x1f\eri",
	  "3.Homing cihaz\xf1\x31n nominal de\xf1\x1feri",
	  "4.P.alici acik:",
	  "5.Ka\xf1\x1f\xf1\x31t para:",
	  "6.De\xf1\x1fi\xf1\x5fiklik t\xf0\xfcr\xf0\xfcne tutun: ",
	  "7.Okuyucu tipi:",
	  "8.Para d\xf0\xfc\xf1\x5f\xf0\xfclmesi Okuyucu,:",
	  "9.No degisim Modu:",
	  "10.\xf0\xc7oklu al\xf1\x31m:",
	  "11.Geri \xf0\xF6deme:",
	  "12.Bozuk p:",
	  "13.Banknot max.de\xf1\x1f\er:",
	  "14.Kalan bakiye:",
	  "15.\xf1\x5e\xf0\xfcpheli bakiye:",
	  "16.Ondal\xf1\x31k say\xf1\x31:",
	  "17.GOC acik:", 
	  "18.POS acik:",
	  "19.PC acik:",
	  "20.Ekran T\xf0\xfcr\xf0\xfc:",//ƴͼ��Ļ��ʽ;by gzz 20121106
	  "21.Anahtar kurulu Toplama:",
	  "22.kullanmak logo:",
	  "23.otomatik eklendi:",
	  "24.on:",
	  "25.Ge\xf0\xe7ici a\xf0\xe7mak i\xf0\xe7in olsun:",
	  "26.5Ge\xf0\xe7ici: ",
	  "27.10Ge\xf0\xe7ici:"//,
	  //"20. ֽ��20Ԫ�ݴ�: "
	  }
 };

const unsigned int  Menu_BusinessID[BUSINESSNO]=
{
	 MENU_COINVALUE,
	 MENU_NOTEVALUE,
	 MENU_CHANGEVALUE,
	 MENU_OPENCOIN, 
	 MENU_OPENNOTE,
	 MENU_OPENCHANGE,
	 MENU_OPENREADER,
	 MENU_READERCOST,
	 MENU_CHANGESERVER,
	 MENU_NOLIMITEDBUY,
	 MENU_RETURNCOINS,
	 MENU_BALANCEMIN,
	 MENU_MONEYMAXIN,
	 MENU_IOU	,
	 MENU_DOUBTMONEY,
	 MENU_DECPOINTNUM,
	 MENU_SALECONFIRM,
	 MENU_POSENABLE,
	 MENU_VMCPC,
	 MENU_LARGELCD,
	 MENU_SELECTKEY,
	 MENU_LOGOSEL,
	 MENU_ADDCOLUMN,
	 MENU_TENCOLUMN,
	 MENU_HOLDNOTE,
	 MENU_HOLDNOTE5,
	 MENU_HOLDNOTE10//,
	 //MENU_HOLDNOTE20
};
//

const char *     Menu_ChangeValue[LANGUAGENO][CHANGEVALUENO]=
{
	 {
	 "1.#1������: ",
	 "2.#2������: ",
	 "3.#3������: "
	 },
	 {
	 "1.#1Change: ",
	 "2.#2Change: ",
	 "3.#3Change: "
	 },
	 //change by liya 2012-10-16
	 {
	 "1.���ѧ٧ާ֧� 1: ",
	 "2.���ѧ٧ާ֧� 2: ",
	 "3.���ѧ٧ާ֧� 3: "
	 },
	 //��������;by gzz 20121115
	 {
	 "De\xf1\x1fi\xf1\x5fim #1:",
	 "De\xf1\x1fi\xf1\x5fim #2:",
	 "De\xf1\x1fi\xf1\x5fim #3:"
	 }
};
const unsigned int  Menu_ChangeValueID[CHANGEVALUENO]=
{
	 MENU_CHANGEVALUE1,
	 MENU_CHANGEVALUE2,
	 MENU_CHANGEVALUE3
};


const char *     Menu_SetNote[LANGUAGENO][SETNOTE]=
{
	 {
	 "1. MDB",
	 "2. GBA ",
	 "3. SSP ",
	 "4. OFF "
	 },
	 {
	 "1. MDB",
	 "2. GBA ",
	 "3. SSP ",
	 "4. OFF "
	 },
	 //change by liya 2012-10-16
	 {
	 "1. MDB",
	 "2. GBA ",
	 "3. SSP ",
	 "4. OFF "
	 },
	 //��������;by gzz 20121115
	 {
	 "1. MDB",
	 "2. GBA ",
	 "3. SSP ",
	 "4. OFF "
	 }
};
const unsigned int  Menu_SetNoteID[SETNOTE]=
{
	 MENU_SELECTMEI,
	 MENU_SELECTGBA,
	 MENU_SELECTITL,
	 MENU_SELECTCLOSE
};

//�������˵�;by gzz 20121120
const char * 	Menu_SetReader[LANGUAGENO][SETREADER]=
{
	  {
	  "1. OFF",
	  "2. MDB "
	  },
	  {
	  "1. OFF",
	  "2. MDB "
	  },
	  //change by liya 2012-10-16
	  {
	  "1. OFF",
	  "2. MDB "
	  },
	  //��������;by gzz 20121115
	  {
	  "1. OFF",
	  "2. MDB "
	  }
};
//�������˵�;by gzz 20121120
const unsigned int  Menu_SetReaderID[SETREADER]=
{
	  MENU_READEROFF,
	  MENU_READERMDB
};

  
 //

const char *     Menu_NoteValue[LANGUAGENO][NOTEVALUENO]=
{
	 {
	 "1.#1ֽ��: ",
	 "2.#2ֽ��: ",
	 "3.#3ֽ��: ",
	 "4.#4ֽ��: ",
	 "5.#5ֽ��: ",
	 "6.#6ֽ��: ",
	 "7.#7ֽ��: ",
	 "8.#8ֽ��: "
	 },
	 {
	 "1.#1 Note: ",
	 "2.#2 Note: ",
	 "3.#3 Note: ",
	 "4.#4 Note: ",
	 "5.#5 Note: ",
	 "6.#6 Note: ",
	 "7.#7 Note: ",
	 "8.#8 Note: "
	 },
	 //change by liya 2012-10-16
	 {
	 "1.�������� ��1:",
	 "2.�������� ��2:",
	 "3.�������� ��3:",
	 "4.�������� ��4:",
	 "5.�������� ��5:",
	 "6.�������� ��6:",
	 "7.�������� ��7:",
	 "8.�������� ��8:"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.#1 dikkat: ",
	 "2.#2 dikkat: ",
	 "3.#3 dikkat: ",
	 "4.#4 dikkat: ",
	 "5.#5 dikkat: ",
	 "6.#6 dikkat: ",
	 "7.#7 dikkat: ",
	 "8.#8 dikkat: "
	 }
};
const unsigned int  Menu_NoteValueID[NOTEVALUENO]=
{
	 MENU_NOTEVALUE1,
	 MENU_NOTEVALUE2,
	 MENU_NOTEVALUE3,
	 MENU_NOTEVALUE4,
	 MENU_NOTEVALUE5,
	 MENU_NOTEVALUE6,
	 MENU_NOTEVALUE7,
	 MENU_NOTEVALUE8
};
 
 
 //

const char *     Menu_CoinValue[LANGUAGENO][COINVALUENO]=
{
	 {
	 "1.#1Ӳ��: ",
	 "2.#2Ӳ��: ",
	 "3.#3Ӳ��: ",
	 "4.#4Ӳ��: ",
	 "5.#5Ӳ��: ",
	 "6.#6Ӳ��: ",
	 "7.#7Ӳ��: ",
	 "8.#8Ӳ��: "
	 },
	 {
	 "1.#1 Coin: ",
	 "2.#2 Coin: ",
	 "3.#3 Coin: ",
	 "4.#4 Coin: ",
	 "5.#5 Coin: ",
	 "6.#6 Coin: ",
	 "7.#7 Coin: ",
	 "8.#8 Coin: "
	 },
	 //change by liya 2012-10-16
	 {
	 "1.����ߧ֧�� ��1:",
	 "2.����ߧ֧�� ��2:",
	 "3.����ߧ֧�� ��3:",
	 "4.����ߧ֧�� ��4:",
	 "5.����ߧ֧�� ��5:",
	 "6.����ߧ֧�� ��6:",
	 "7.����ߧ֧�� ��7:",
	 "8.����ߧ֧�� ��8:"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.#1 sikke: ",
	 "2.#2 sikke: ",
	 "3.#3 sikke: ",
	 "4.#4 sikke: ",
	 "5.#5 sikke: ",
	 "6.#6 sikke: ",
	 "7.#7 sikke: ",
	 "8.#8 sikke: "
	 }
}; 
 
const unsigned int  Menu_CoinValueID[COINVALUENO]=
{
	 MENU_COINVALUE1,
	 MENU_COINVALUE2,
	 MENU_COINVALUE3,
	 MENU_COINVALUE4,
	 MENU_COINVALUE5,
	 MENU_COINVALUE6,
	 MENU_COINVALUE7,
	 MENU_COINVALUE8
};
   
 //

const char *     Menu_HoldNote[LANGUAGENO][HOLDNOTENO]=
{
	 {
	 "1.ֽ�� 5Ԫ�ݴ�: ",
	 "2.ֽ��10Ԫ�ݴ�: "
	 },
	 {
	 "1.HoldNote5$: ",
	 "2.HoldNote10$: "
	 },
	 //change by liya 2012-10-16
	 {
	 "1.����ܧݧ��ڧ�� �ܧ����� 5$: ",
	 "2.����ܧݧ��ڧ�� �ܧ����� 10$: "
	 },
	 //��������;by gzz 20121115
	 {
	 "1.5$ Ge\xf0\xe7ici: ",
	 "2.10$ Ge\xf0\xe7ici: "
	 }
};
const unsigned int  Menu_HoldNoteID[COINVALUENO]=
{
	 MENU_HOLDNOTE5,
	 MENU_HOLDNOTE10
};
  
 
 

const  char *     Menu_Transactions[LANGUAGENO][TRANSACTIONSNO]=
{
	 {
	 "1 �ճ�������֧    ",
	 "2 �ճ���Ʒ��¼        ",
	 "3 ����ճ���¼    ",
	 "4 ���Ȼ�����֧    ",
	 "5 ������Ʒ��¼        ",
	 "6 ������ȼ�¼    "
	 },
	 {
	 "1.Payments    ",
	 "2.Goods       ",
	 "3.Clear record",
	 "4.quarter Payments    ",
	 "5.quarter Goods       ",
	 "6.Clear quarter record"
	 },
	 //change by liya 2012-10-16
	 {
	 "1.���ݧѧ�֧ا�",
	 "2.���է�",
	 "3.����ڧ��ڧ�� �٧ѧ�ڧ��",
	 "4.�ܧӧѧ��ѧ� ���ݧѧ�֧ا�",
	 "5.�ܧӧѧ��ѧ� ���է�",
	 "6.�ܧӧѧ��ѧ� ����ڧ��ڧ��٧ѧ�ڧ��"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.\xf0\xD6\demeler g\xf0\xfcng\xf0\xfcn para bakiyesi",
	 "2.G\xf0\xfcnl\xf0\xfck mallar\xf1\x31n kay\xf1\x31tlar\xf1\x31",
	 "3.G\xf0\xfcnl\xf0\xfck kay\xf1\x31t Temizle",
	 "4.\xf0\xc7eyrek parasal \xf0\xF6demeler",
	 "5.Ayl\xf1\x31k emtia kay\xf1\x31tlar\xf1\x31",
	 "6.Temizle ayl\xf1\x31k rekor"
	 }
};
const unsigned int  Menu_TransactionsID[TRANSACTIONSNO]=
{
	 MENU_PAYMENTS,
	 MENU_GOODS,
	 MENU_CLEARTRANS,
	 MENU_PAYMENTSJIDU,
	 MENU_GOODSJIDU,
	 MENU_CLEARTRANSJIDU
};
//



const  char *     Menu_Payments[LANGUAGENO][PAYMENTSNO]=
{
	 {
	 "1.����������:",
	 "2.ֽ������  :",
	 "3.Ӳ������  :",
	 "4.�����ܽ��:",
	 "5.�����ܽ��:",
	 "6.#1����ö��:",
	 "7.#2����ö��:",
	 "8.#3����ö��:"
	 },
	 {
	 "1.TotalIncome:",
	 "2.Note income:",
	 "3.CoinsIncome:",
	 "4.Total trans:",
	 "5.TotalChange:",
	 "6.#1Coins num:",
	 "7.#2Coins num:",
	 "8.#3Coins num:"
	 },
	 //change by liya 2012-10-16
	 {
	 "1.����ާާѧ�ߧѧ� �ӧ����ܧ�:",
	 "2.����ڧߧ��� �ܧ����:",
	 "3.����ڧߧ��� �ާ�ߧ֧�:",
	 "4.����֧ԧ� ���ѧߧ٧ѧܧ�ڧ�:",
	 "5.����֧ԧ� ��ѧ٧ާ֧ߧ��:",
	 "6.���ڧ�ݧ� �ާ�ߧ֧� ��1:",
	 "7.���ڧ�ݧ� �ާ�ߧ֧� ��2:",
	 "8.���ڧ�ݧ� �ާ�ߧ֧� ��3:"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.Toplam:",
	 "2.Ka\xf1\x1f\xf1\x31t para:",
	 "3.Madeni para:",
	 "4.Sat\xf1\x31ld\xf1\x31:",
	 "5.Toplam tutar\xf1\x31 i\xf0\xe7in de\xf1\x1fi\xf1\x5ftirme:",
	 "6.#1Sikke alt\xf1\x31n:",
	 "7.#2Sikke alt\xf1\x31n:",
	 "8.#3Sikke alt\xf1\x31n:"
	 }
};
const unsigned int  Menu_PaymentsID[PAYMENTSNO]=
{
	 MENU_INCOME,
	 MENU_NOTEINCOME,
	 MENU_COINSINCOME,
	 MENU_TOTALTRANS,
	 MENU_TOTALCHANGE,
	 MENU_COINSCHANGE1,
	 MENU_COINSCHANGE2,
	 MENU_COINSCHANGE3
};

//���ڼ��Ƚ�����;by gzz 20121009
const unsigned int  Menu_PaymentsIDJidu[PAYMENTSNO]=
{
	  MENU_INCOMEJIDU,
	  MENU_NOTEINCOMEJIDU,
	  MENU_COINSINCOMEJIDU,
	  MENU_TOTALTRANSJIDU,
	  MENU_TOTALCHANGEJIDU,
	  MENU_COINSCHANGE1JIDU,
	  MENU_COINSCHANGE2JIDU,
	  MENU_COINSCHANGE3JIDU
};

const  char *     Menu_Goods[LANGUAGENO][3]=
{
	 {
	 "1.�ɹ����״���:",
	 "2.���ʽ��״���:",
	 "3.����������ͳ��"
	 },
	 {
	 "1.Success num:",
	 "2.Doubt num  :",
	 "3.Column tran "
	 },
	 //change by liya 2012-10-16
	 {
	 "1.�����-�ӧ� ��էѧ�:",
	 "2.�����-�ӧ� ���ާߧ֧ߧڧ�:",
	 "3.�����ݧҧ֧� ���ѧߧ٧ѧܧ�ڧ�:"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.I\xf1\x5flem say\xf1\x31s\xf1\x31:",
	 "2.\xf1\x5e\xf0\xfcphe bu i\xf1\x5flem say\xf1\x31s\xf1\x31:",
	 "3.Tek koridorlu i\xf1\x5flemleri istatistikleri"
	 }
};

//���ڼ��Ƚ�����;by gzz 20121009
const char *     Menu_GoodsJidu[LANGUAGENO][1]=
{
	 {	
	 "1.����������ͳ��"
	 },
	 {	
	 "1.Column tran "
	 },
	 //change by liya 2012-10-16
	 {
	 "1.�����ݧҧ֧� ���ѧߧ٧ѧܧ�ڧ�:"
	 },
	 //��������;by gzz 20121115
	 {	
	 "1.Tek koridorlu i\xf1\x5flemleri istatistikleri"
	 }
}; 
const unsigned int  Menu_GoodsID[3]=
{
	 MENU_SUCCESSNUM,
	 MENU_DOUBTNUM,
	 MENU_CHANNELTRANS
};

//���ڼ��Ƚ�����;by gzz 20121009
const unsigned int  Menu_GoodsIDJidu[1]=
{	
	 MENU_CHANNELTRANSJIDU
};


const char *     Menu_TransInputChannelNo[LANGUAGENO][1]=
{
	 {
	 "��������: "
	 },
	 {
	 "Input column code:"
	 },
	 //change by liya 2012-10-16
	 {
	 "���ӧ�� �ܧ�� �ܧ�ݧ�ߧܧ�:"
	 },
	 //��������;by gzz 20121115
	 {
	 	"S\xf0\xfctun kodunu girin:"
	 }
};
const unsigned int  Menu_TransInputChannelNoID[1]=
{
	MENU_TRANSINPUTNUM
};

 //���ڼ��Ƚ�����;by gzz 20121009
const  unsigned int  Menu_TransInputChannelNoIDJIDU[1]=
 {
	 MENU_TRANSINPUTNUMJIDU
 };


const  char *     Menu_TransChannel[LANGUAGENO][4]=
{
	 {
	 "1.�������:     ",
	 "2.�ɹ�����ͳ��: ",
	 "3.��Ʒ���ͳ��: ",
	 "4.���ʽ���ͳ��: "
	 },
	 {
	 "1.Column No.:",
	 "2.Success num:",
	 "3.Success money:",
	 "4.Doubt num:"
	 },
	 //change by liya 2012-10-16
	 {
	 "1.����ݧ�ߧܧ� �ߧ�ާ֧�:",
	 "2.�ܧ��-�ӧ� ��էѧ�:",
	 "3.���֧ߧ�ԧ� ���ѧ�ڧ��ڧܧ�:",
	 "4.�ܧ��-�ӧ� ���ާߧ֧ߧڧ�:"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.Kargo Road No:     ",
	 "2.Ba\xf1\x5far\xf1\x31l\xf1\x31 bir i\xf1\x5flem say\xf1\x31s\xf1\x31: ",
	 "3.Mal istatistik miktar\xf1\x31: ",
	 "4.\xf1\x5e\xf0\xfcphe bu i\xf1\x5flem say\xf1\x31s\xf1\x31: "
	 }
};

 //���ڼ��Ƚ�����;by gzz 20121009
const   char *     Menu_TransChannelJidu[LANGUAGENO][3]=
{
	 {
	 "1.�������:     ",
	 "2.�ɹ�����ͳ��: ",
	 "3.��Ʒ���ͳ��: "
	 },
	 {
	 "1.Column NO:",
	 "2.Success NUM:",
	 "3.Success Money:"	 
	 },
	 //change by liya 2012-10-16
	 {
	 "1.����ݧ�ߧܧ� �ߧ�ާ֧�:",
	 "2.�ܧ��-�ӧ� ��էѧ�:",
	 "3.�ܧ��-�ӧ� ���ާߧ֧ߧڧ�:"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.Kargo Road No:     ",
	 "2.Ba\xf1\x5far\xf1\x31l\xf1\x31 bir i\xf1\x5flem say\xf1\x31s\xf1\x31: ",
	 "3.Mal istatistik miktar\xf1\x31: "
	 }
};
 
const  unsigned int  Menu_TransChannelID[4]=
{
	 MENU_TRANSCHANNELNO,
	 MENU_TRANSSUCCESS,
	 MENU_TRANMONEY,
	 MENU_TRANSDOUBT
};

//���ڼ��Ƚ�����;by gzz 20121009
const unsigned int  Menu_TransChannelIDJIDU[3]=
{
	 MENU_TRANSCHANNELNOJIDU,
	 MENU_TRANSSUCCESSJIDU,
	 MENU_TRANMONEYJIDU
}; 
 

const char *     Menu_System[LANGUAGENO][SYSTEMNO]=
{
	 {
	 "1 ʱ������    ",
	// "��������    ",
	 "2 �����ֻ�ģ��: ",
	 "3 �������: ",
	 "4 GSM No",
	 "5 �����¶��趨:",
	 "6 ����ѡ��",
	 "7 �¿�������",//���ѹ��������;by gzz 20121224
	 "8 չʾ�ƿ���"//���չʾ�ƿ���;by gzz 20121229
	 },
	 {
	 "1.Set time",
	 //"CHANGEPASSWORD",
	 "2.GSM on:",
	 "3.VM ID:",
	 "4.GSM No",
	 "5.Temperature:",
	 "6.language",
	 "7.Temperature control",
	 "8.LED control"
	 },
	 //change by liya 2012-10-16
	 {
	 "1.����ѧߧ�ӧܧ� �ӧ�֧ާ֧ߧ�",
	 "2.���ܧݧ��ڧ�� GSM:",
	 "3.VM ID:",
	 "4.����ާ֧� GSM:",
	 "5.���֧ާ�֧�ѧ����:",
	 "6.��٧��",
	 "7.��֧ԧ�ݧڧ��ӧѧߧڧ� ��֧ާ�֧�ѧ����",
	 "8.LED ��֧ާ�֧�ѧ����"
	 },
	 //��������;by gzz 20121115
	 {
	 "1.Zaman ayar\xf1\x31",
	 "2.Mobil:",
	 "3.VM Ki:",
	 "4.GSM mum",
	 "5.S\xf1\x31.cakl\xf1\x31k ayar\xf1\x31:",
	 "6.Dil",
	 "7.S\xf1\x31\cakl\xf1\x31k kontrol\xf0\xfc",
	 "8.LED kontrol\xf0\xfc"
	 }
};
const  unsigned int  Menu_SystemID[SYSTEMNO]=
{
	 MENU_TIMESET,
	// MENU_CGPASSWORD,
	 MENU_GPRSONOFF,
	 MENU_SERIALNO,
	 MENU_GSMNO,
	 MENU_TEMPERATURE,
	 MENU_SYSLANGUAGE,
	 MENU_TEMPSET,//���ѹ��������;by gzz 20121224
	 MENU_LEDSET//���չʾ�ƿ���;by gzz 20121229
};
 
const char *    Menu_TimeSet[LANGUAGENO][5]=
{
	 {
	 "1.��:         ",
	 "2.��:         ",
	 "3.��:         ",
	 "4.ʱ:         ",
	 "5.��:         "
	 },
	 {
	 "1.YEAR:       ",
	 "2.MONTH:      ",
	 "3.DATE:       ",
	 "4.HOUR:       ",
	 "5.MINUTE:     "
	 },
	 //change by liya
	 {
	 "1.�����:        ",
	 "2.���֧���:      ",
	 "3.���֧ߧ�:       ",
	 "4.���ѧ��:       ",
	 "5.���ڧߧ���:     "
	 },
	 //��������;by gzz 20121115
	 {
	 "1.Y\xf1\x31l:         ",
	 "2.ay:         ",
	 "3.g\xf0\xfcn:         ",
	 "4.zaman:         ",
	 "5.dakika:         "
	 }
};
const  unsigned int  Menu_TimeSetID[5]=
{
	 MENU_SETYEAR,
	 MENU_SETMONTH,
	 MENU_SETDATE,
	 MENU_SETHOUR,
	 MENU_SETMINUTE
};

//���ѹ��������;by gzz 20121224
const char *    Menu_TempSet[LANGUAGENO][5]=
{
	 {
	 "1.ѹ��������: ",	
	 "2.ѹ��������ʱ: ",
	 "3.ѹ����������: ",
	 "4.ѹ�����ر�ʱ: ",
	 "5.ѹ�����رշ�: "
	 },
	 {
	 "1.Temp Set:",
	 "2.TempStartHour:",
	 "3.TempStartMinute:",
	 "4.TempEndHour:",
	 "5.TempEndMinute:"
	 },
	 //change by liya 2012-10-16
	 {
	 "1.��֧ԧ�ݧڧ��ӧѧߧڧ� ��֧ާ�֧�ѧ����:",
	 "2.���ѧ�ѧ�� ��ѧ���:",
	 "3.���ѧ�ѧݧ� �ާڧߧ��:",
	 "4.���ѧܧ���� ��ѧ�:",
	 "5.���ѧܧ���� �ާڧߧ���:"
	 },
	 {
	 "1.S\xf1\x31\cakl\xf1\x31k kontrol\xf0\xfc:",
	 "2.Saat ba\xf1\x5flay\xf1\x31n:",
	 "3.Dakikada ba\xf1\x5flay\xf1\x31n:",
	 "4.Kapat saat:",
	 "5.Kapat dakika:"
	 }
};

//���ѹ��������;by gzz 20121224
const unsigned int  Menu_TempSetID[5]=
{
	 MENU_TEMPON,
	 MENU_TEMPHOURSTR,
	 MENU_TEMPMINUTESTR,
	 MENU_TEMPHOUREND,
	 MENU_TEMPMINUTEEND
}; 

//���չʾ�ƿ���;by gzz 20121229
const char *    Menu_LEDSet[LANGUAGENO][5]=
{
	 {
	 "1.չʾ������: ",	
	 "2.չʾ������ʱ: ",
	 "3.չʾ��������: ",
	 "4.չʾ�ƹر�ʱ: ",
	 "5.չʾ�ƹرշ�: "
	 },
	 {
	 "1.LED Set:",
	 "2.LEDStartHour:",
	 "3.LEDStartMinute:",
	 "4.LEDEndHour:",
	 "5.LEDEndMinute:"
	 },
	 //change by liya 2012-10-16
	 {
	 "1.LED ��֧ާ�֧�ѧ����:",
	 "2.���ѧ�ѧ�� ��ѧ���:",
	 "3.���ѧ�ѧݧ� �ާڧߧ��:",
	 "4.���ѧܧ���� ��ѧ�:",
	 "5.���ѧܧ���� �ާڧߧ���:"
	 },
	 {
	 "1.LED kontrol\xf0\xfc:",
	 "2.Saat ba\xf1\x5flay\xf1\x31n:",
	 "3.Dakikada ba\xf1\x5flay\xf1\x31n:",
	 "4.Kapat saat:",
	 "5.Kapat dakika:"
	 }
};

//���չʾ�ƿ���;by gzz 20121229
const unsigned int  Menu_LEDSetID[5]=
{
	 MENU_LEDON,
	 MENU_LEDHOURSTR,
	 MENU_LEDMINUTESTR,
	 MENU_LEDHOUREND,
	 MENU_LEDMINUTEEND
}; 


//
const char *     Menu_InputLayerNum[LANGUAGENO][1]=
{
	 {
	 "��������: "
	 },
	 {
	  "Input tray code:"
	 },
	 //change by liya 2012-10-16
	 {
	 "���ӧ֧էڧ�� �ܧ�� �ݧ��ܧ�:"
	 },
	 //��������;by gzz 20121115
	 {
	 "Katman numaras\xf1\x31n\xf1\x31 girin: "
	 }
};



const unsigned int  Menu_InputLayerNumID[1]=
{
	  MENU_INPUTLAYER
};
 

const char *     Menu_SetChannel[LANGUAGENO][SETCHANNELNO]=
{
	 {
	 "1.��ܱ��:   ",
	 "2.�Ƿ�����:   ",
	 "3.���������: ",
	 "4.��һ����:   ",
	 "5.��һ��������: ",
	 "6.�ڶ�����:   ",
	 "7.�ڶ���������: ",
	 "8.��������:   ",
	 "9.������������: ",
	 "10. ���Ļ���:   ",
	 "11. ���Ļ�������: ",
	 "12. �������:   ",
	 "13. �����������: ",
	 "14. ��������:   ",
	 "15. ������������: ",
	 "16. ���߻���: ",
	 "17. ���߻�������: ",
	 "18. �ڰ˻���: ",
	 "19. �ڰ˻�������: ",
	 "20. �ھŻ���: ",
	 "21. �ھŻ�������: ",
	 "22. �������: ",
	 "23. �����������: "
	 },
	 {
	 "1.Tray code:",
	 "2.Enabled:  ",
	 "3.Goods Max:",
	 "4.Column 1: ",
	 "5.Column 1Num: ",
	 "6.Column 2: ",
	 "7.Column 2Num: ",
	 "8.Column 3: ",
	 "9.Column 3Num: ",
	 "10.Column 4: ",
	 "11.Column 4Num: ",
	 "12.Column 5: ",
	 "13.Column 5Num: ",
	 "14.Column 6: ",
	 "15.Column 6Num: ",
	 "16.Column 7:",
	 "17.Column 7Num: ",
	 "18.Column 8:",
	 "19.Column 8Num: ",
	 "20.Column 9:",
	 "21.Column 9Num: ",
	 "22.Column 0:",
	 "23.Column 0Num: "
	 },
	 //change by liya 2012-10-16
	 {
	 "1.����� �ݧ��ܧ�:",
	 "2.���ܧݧ��֧�:  ",
	 "3.���ѧܧ�. �����ڧ�:",
	 "4.����ݧ�ߧܧ� 1: ",
	 "5.����ݧ�ߧܧ� 1�ܧ�ݧڧ�֧��ӧ�: ",
	 "6.����ݧ�ߧܧ� 2: ",
	 "7.����ݧ�ߧܧ� 2�ܧ�ݧڧ�֧��ӧ�: ",
	 "8.����ݧ�ߧܧ� 3: ",
	 "9.����ݧ�ߧܧ� 3�ܧ�ݧڧ�֧��ӧ�: ",
	 "10.����ݧ�ߧܧ� 4: ",
	 "11.����ݧ�ߧܧ� 4�ܧ�ݧڧ�֧��ӧ�: ",
	 "12.����ݧ�ߧܧ� 5: ",
	 "13.����ݧ�ߧܧ� 5�ܧ�ݧڧ�֧��ӧ�: ",
	 "14.����ݧ�ߧܧ� 6: ",
	 "15.����ݧ�ߧܧ� 6�ܧ�ݧڧ�֧��ӧ�: ",
	 "16.����ݧ�ߧܧ� 7:",
	 "17.����ݧ�ߧܧ� 7�ܧ�ݧڧ�֧��ӧ�: ",
	 "18.����ݧ�ߧܧ� 8:",
	 "19.����ݧ�ߧܧ� 8�ܧ�ݧڧ�֧��ӧ�: ",
	 "20.����ݧ�ߧܧ� 9:",
	 "21.����ݧ�ߧܧ� 9�ܧ�ݧڧ�֧��ӧ�: ",
	 "22.����ݧ�ߧܧ� 0:",
	 "23.����ݧ�ߧܧ� 0�ܧ�ݧڧ�֧��ӧ�: "
	 },
	 //��������;by gzz 20121115
	 {
	 "1.Tepsi kodu:   ",
	 "2.Etkin:   ",
	 "3.Max \xf0\xfcr\xf0\xfcn: ",
	 "4.S\xf0\xfctun  1:",
	 "5.S\xf0\xfctun  1miktar:",
	 "6.S\xf0\xfctun  2:",
	 "7.S\xf0\xfctun  2miktar:",
	 "8.S\xf0\xfctun  3:",
	 "9.S\xf0\xfctun  3miktar:",
	 "10.S\xf0\xfctun  4:",
	 "11.S\xf0\xfctun  4miktar:",
	 "12.S\xf0\xfctun  5:",
	 "13.S\xf0\xfctun  5miktar:",
	 "14.S\xf0\xfctun  6:",
	 "15.S\xf0\xfctun  6miktar:",
	 "16.S\xf0\xfctun  7:",
	 "17.S\xf0\xfctun  7miktar:",
	 "18.S\xf0\xfctun  8:",
	 "19.S\xf0\xfctun  8miktar:",
	 "20.S\xf0\xfctun  9:",
	 "21.S\xf0\xfctun  9miktar:",
	 "22.S\xf0\xfctun  0:",
	 "23.S\xf0\xfctun  0miktar:"
	 }
};
const  unsigned int  Menu_SetChannelID[SETCHANNELNO]=
{
	 MENU_LAYERNO,
	 MENU_LAYENABLE,
	 MENU_MAXGOODS,
	 MENU_CHANNEL1,
	 MENU_CHANNELNUM1,//������������;by gzz 20121120
	 MENU_CHANNEL2,
	 MENU_CHANNELNUM2,
	 MENU_CHANNEL3,
	 MENU_CHANNELNUM3,
	 MENU_CHANNEL4,
	 MENU_CHANNELNUM4,
	 MENU_CHANNEL5,
	 MENU_CHANNELNUM5,
	 MENU_CHANNEL6,
	 MENU_CHANNELNUM6,
	 MENU_CHANNEL7,
	 MENU_CHANNELNUM7,
	 MENU_CHANNEL8,
	 MENU_CHANNELNUM8,
	 MENU_CHANNEL9,
	 MENU_CHANNELNUM9,
	 MENU_CHANNEL0,
	 MENU_CHANNELNUM0
};
 
const char *     Menu_NewPassword[LANGUAGENO][2]=
{
	 {
	 "����������",
	 "�ٴ�����  "
	 },
	 {
	 "NEW PW    ",
	 "REPEAT    "
	 },
	 //change by liya 2012-10-16
	 {
	 "����ӧ�� PW",
	 "����ӧ���ڧ��"
	 },
	 //��������;by gzz 20121115
	 {
	 "Yeni \xf1\x5fifreyi girin",
	 "yeniden girin  "
	 }
};
const  unsigned int  Menu_NewPasswordID[2]=
{
	 MENU_NEWPW,
	 MENU_NEWPWREPEAT
};
 
const  char *     Menu_Confirmation[LANGUAGENO][2]=
{
	 {
	 "��ȷ����" ,
	 "ȷ��ENTER ����CANCEL"
	 },
	 {
	 "Are you sure?",
	 "ENTER or CANCEL"
	 },
	 //change by liya 2012-10-16
	 {
	 "���� ��ӧ֧�֧ߧߧ�?",
	 "���ӧ��   �ڧݧ�   �������"
	 },
	 //��������;by gzz 20121115
	 {
	 "Emin misiniz?",
	 "Giri\xf1\x5f yada iptal"
	 }
};
const unsigned int  Menu_ConfirmationID[2]=
{
	MENU_CONFIRMATION ,
	MENU_NULL
};

//���ڼ��Ƚ�����;by gzz 20121009
const unsigned int  Menu_ConfirmationIDJidu[2]=
{
	MENU_CONFIRMATIONJIDU ,
	MENU_NULL
};


const char *     Menu_SetConfirmation[LANGUAGENO][2]=
{
	 {
	 "��ȷ����" ,
	 "ȷ��ENTER ����CANCEL"
	 },
	 {
	 "Are you sure?",
	 "ENTER or CANCEL"
	 },
	 //change by liya 2012-10-16
	 {
	 "���� ��ӧ֧�֧ߧߧ�?",
	 "���ӧ��   �ڧݧ�   �������"
	 },
	 //��������;by gzz 20121115
	 {
	 "Emin misiniz?",
	 "Giri\xf1\x5f yada iptal"
	 }
};




const unsigned int  Menu_SetConfirmationID[2]=
{
	MENU_CONFIRMSET ,
	MENU_NULL
};


//�û�ģʽ�˵�;by gzz 20121130
const unsigned int  Menu_SetAdminID[2]=
{
	MENU_CONFIRMSET ,
	MENU_NULL
};


//
const char  MenuNULL[]={"              "};
//



/*********************************************************
���飬������ת����ҳ��

//CurMenuID=���˵�ID
//MaxMenuItem=ͬ���˵��������
//OkMenuID=�Ӳ˵�������Ӧ�Ĳ˵�ID,ID=999Ϊ�˵��Ѿ�������
//EscMenuID=���˵�������Ӧ�Ĳ˵�ID,ID=999Ϊ�˵��Ѿ�������
//DownMenuID=�ܲ˵�������Ӧ�Ĳ˵�ID,ID=999Ϊ�˵��Ƕ�����
//UpMenuID=�ֲ˵�������Ӧ�Ĳ˵�ID,ID=999Ϊ�˵��Ƕ�����
//CurFunction=���˵�����Ӧ�Ĳ˵�����ָ��
typedef struct
 {
 	unsigned short int KeyTab_MenuIndex;  		//��ǰ״̬������
 	unsigned short int KeyTab_MaxItems;  		//�����˵������Ŀ��
    unsigned short int KeyTab_PressOk;   	 	//����"�س�"��ʱת���״̬������
    unsigned short int KeyTab_PressEsc;  		//����"����"��ʱת���״̬������
    unsigned short int KeyTab_PressDown;  		//����"����"��ʱת���״̬������
    unsigned short int KeyTab_PressUp;    		//����"����"��ʱת���״̬������
 	uint8_t    	(*CurrentOperate)(void);   		//��ǰѡ��Ӧ��ִ�еĹ��ܲ���
	char * 		(*InitKeyTab)(void);			//��ǰѡ������Ĳ���
 }KeyTabStruct;									//�˵���ṹ

***********************************************************/

//
KeyTabStruct  KeyTab[MAX_KEYTABSTRUCT_NUM]=
	{		  
		//CurMenuID,	  MaxMenuItem,			OkMenuID,			EscMenuID,			DownMenuID,				UpMenuID,			IsVisible				CurFunction				  		InitKeyTab
		{MENU_PASSWORD,			1,			MENU_INPUTLAYER,		MENU_SETCHANNEL,	0,						999,				MENU_VISIBLE_TRUE,		*MenuFunctionPW,				*MenuInitPWIN	},//0
		{MENU_CHANNEL,			ROOTNO,		MENU_INPUTNUM,			999,				MENU_ADDGOODS,			MENU_DEFAULTSET,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,				*MenuInit0	},       
		{MENU_INPUTNUM,			1,			MENU_CHANNELNO,			MENU_CHANNEL,		999,					999,				MENU_VISIBLE_TRUE,		*MenuFunctionCHIN,				*MenuInitCHIN	},
		{MENU_CHANNELNO,		CHANNELNO,			999,			MENU_INPUTNUM,		MENU_PRICE,				MENU_CHANNELGOODS,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,				*MenuInitCHNO	},
		{MENU_PRICE,			CHANNELNO,			999,			MENU_INPUTNUM,		MENU_CHANNELLEFT,		MENU_CHANNELNO,		MENU_VISIBLE_TRUE,		*MenuFunctionCHPR,				*MenuInitCHPR	},
		{MENU_CHANNELLEFT,		CHANNELNO,			999,			MENU_INPUTNUM,		MENU_CHANNELSTAT,		MENU_PRICE,     	MENU_VISIBLE_TRUE,		*MenuFunctionCHLF,				*MenuInitCHLF	},//5
		{MENU_CHANNELSTAT,		CHANNELNO,			999,			MENU_INPUTNUM,		MENU_CHANNELGOODS,	    MENU_CHANNELLEFT,	MENU_VISIBLE_TRUE,		*MenuFunctionCHST,				*MenuInitCHST	},	
		{MENU_CHANNELGOODS,		CHANNELNO,			999,			MENU_INPUTNUM,		MENU_CHANNELNO,		    MENU_CHANNELSTAT,	MENU_VISIBLE_TRUE,		*MenuFunctionCHGOODS,			*MenuInitCHGOODS},		
		{MENU_ADDGOODS,			ROOTNO,		MENU_ADDINPUTLAY,		999,				MENU_DRIVER,			MENU_CHANNEL,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo1, 			*MenuInit0	},
		{MENU_ADDINPUTLAY,		1,			MENU_INPUTADDGOODS,		MENU_ADDGOODS,		999,					999,				MENU_VISIBLE_TRUE,		*MenuFunctionADDLAYIN, 			*MenuInitLAYIN	},
		{MENU_INPUTADDGOODS,	2,			MENU_ADDINPUTLAY,		MENU_ADDINPUTLAY,	999,					999,				MENU_VISIBLE_TRUE,		*MenuFunctionAddGoods, 			*MenuInitAddGoods	},
		{MENU_DRIVER,			ROOTNO,		MENU_NOTESTAT,			999,				MENU_BUSINESS,			MENU_ADDGOODS,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo6,				*MenuInit0	},   //10
		{MENU_NOTESTAT, 		DRIVERNO,	MENU_NOTETESTCONFIRM,	MENU_DRIVER,		MENU_COINSSTAT,         MENU_FLASHLEFT,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo7,				*MenuInitNOST	},
		{MENU_COINSSTAT,      	DRIVERNO,	MENU_COINSTESTCONFIRM,	MENU_DRIVER,		MENU_HOPPERSTAT1, 		MENU_NOTESTAT,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo8,				*MenuInitCOST	},
		{MENU_HOPPERSTAT1,      DRIVERNO,	MENU_HOPPERSTAT1,		MENU_DRIVER,		MENU_HOPPERSTAT2,    	MENU_COINSSTAT,		MENU_VISIBLE_TRUE,		*Hopper1Test,					*MenuInitHOST1	},
		{MENU_HOPPERSTAT2,      DRIVERNO,	MENU_HOPPERSTAT2,		MENU_DRIVER,		MENU_HOPPERSTAT3,    	MENU_HOPPERSTAT1,	MENU_VISIBLE_TRUE,		*Hopper2Test,					*MenuInitHOST2	},
		{MENU_HOPPERSTAT3,      DRIVERNO,	MENU_HOPPERSTAT3,		MENU_DRIVER,		MENU_GPRSTEST,    		MENU_HOPPERSTAT2,	MENU_VISIBLE_TRUE,		*Hopper3Test,					*MenuInitHOST3	},
		{MENU_GPRSTEST,         DRIVERNO,			999,			MENU_DRIVER,		MENU_SMSTEST,			MENU_HOPPERSTAT3, 	MENU_VISIBLE_TRUE,		*MenuFunctionDemo12,			*MenuInit0	},
		{MENU_SMSTEST,			DRIVERNO,			999,			MENU_DRIVER,		MENU_KEYTEST,     		MENU_GPRSTEST, 		MENU_VISIBLE_TRUE,		*MenuFunctionDemo13,			*MenuInit0	},
		{MENU_KEYTEST,          DRIVERNO,	MENU_DOKEYTEST,			MENU_DRIVER,		MENU_ALLCHANNELSTAT,	MENU_SMSTEST,		MENU_VISIBLE_TRUE,		*MenuFunctionKeyTest,			*MenuInit0	},
		{MENU_DOKEYTEST,        1,					999,			MENU_KEYTEST,		999, 					999,				MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,				*MenuInit0	},
		{MENU_ALLCHANNELSTAT,   DRIVERNO,	MENU_SUBALLCHANNELSTAT,	MENU_DRIVER,		MENU_CHANNELTEST,		MENU_KEYTEST,  		MENU_VISIBLE_TRUE,		*MenuFunctionAllChannelStat,	*MenuInit0	},//20
		{MENU_CHANNELTEST,      DRIVERNO,	MENU_DRINPUTNUM,		MENU_DRIVER,		MENU_CHTESTRESULT,		MENU_ALLCHANNELSTAT,MENU_VISIBLE_TRUE,		*MenuFunctionChannelTest,		*MenuInit0	},
		{MENU_DRINPUTNUM,       1,			MENU_DRINPUTNUM,		MENU_CHANNELTEST,	999,					999,  				MENU_VISIBLE_TRUE,		*MenuFunctionTESTCHIN,			*MenuInitCHIN	},
		{MENU_CHTESTRESULT, 	DRIVERNO,	MENU_SUBCHTESTRESULT,	MENU_DRIVER,		MENU_IRTEST,			MENU_CHANNELTEST,  	MENU_VISIBLE_TRUE,		*MenuFunctionAllCHResult,		*MenuInit0	},
		{MENU_IRTEST,		   	DRIVERNO,	MENU_IRTEST,			MENU_DRIVER,		MENU_LCDTEST,			MENU_CHTESTRESULT,  MENU_VISIBLE_TRUE,		*MenuFunctionIRTest,			*MenuInit0	},
        {MENU_LCDTEST,		   	DRIVERNO,	MENU_DOLCDTEST,			MENU_DRIVER,		MENU_TEMPRATURETEST,	MENU_IRTEST,        MENU_VISIBLE_TRUE,		*MenuFunctionLCDTest,			*MenuInit0	},
        {MENU_DOLCDTEST,		1,      			999,			MENU_LCDTEST,		999,					999,                MENU_VISIBLE_TRUE,		*MenuFunctionDOLCDTest,			*MenuInit0	},
		{MENU_TEMPRATURETEST,	DRIVERNO,	MENU_DOTEMPTEST,		MENU_DRIVER,		MENU_SELECTKEYTEST,		MENU_LCDTEST,       MENU_VISIBLE_TRUE,		*MenuFunctionTemperatureTest,	*MenuInit0	},
		{MENU_DOTEMPTEST,		1,      			999,			MENU_TEMPRATURETEST,		999,			999,      			MENU_VISIBLE_TRUE,		*MenuFunctionDoTempeTest,		*MenuInit0	},
		{MENU_SELECTKEYTEST,	DRIVERNO,	MENU_DOSELECTKEYTEST,	MENU_DRIVER,		MENU_TEMPSTEST,			MENU_TEMPRATURETEST,MENU_VISIBLE_TRUE,		*MenuFunctionXuanhuoTest,		*MenuInit0	},
		{MENU_DOSELECTKEYTEST,	1,      			999,			MENU_SELECTKEYTEST,			999,			999,      			MENU_VISIBLE_TRUE,		*MenuFunctionDoXuanhuoTest,		*MenuInit0	},
		{MENU_TEMPSTEST,	   	DRIVERNO,	MENU_DOTEMPSTEST,		MENU_DRIVER,		MENU_LEDTEST,			MENU_SELECTKEYTEST, MENU_VISIBLE_TRUE,		*MenuFunctionTempTest,			*MenuInit0	},//���ѹ��������;by gzz 20121224
        {MENU_DOTEMPSTEST,		1,      			999,			MENU_TEMPSTEST,		999,					999,                MENU_VISIBLE_TRUE,		*MenuFunctionDoTempsTest,		*MenuInit0	},//���ѹ��������;by gzz 20121224
		{MENU_LEDTEST,	   		DRIVERNO,	MENU_DOLEDTEST,			MENU_DRIVER,		MENU_FLASHLEFT,			MENU_TEMPSTEST, 	MENU_VISIBLE_TRUE,		*MenuFunctionLEDTest,			*MenuInit0	},//���ѹ��������;by gzz 20121224
        {MENU_DOLEDTEST,		1,      			999,			MENU_LEDTEST,		999,					999,                MENU_VISIBLE_TRUE,		*MenuFunctionDoLEDTest,			*MenuInit0	},//���ѹ��������;by gzz 20121224
		{MENU_FLASHLEFT,		DRIVERNO,			999,			MENU_DRIVER,		MENU_NOTESTAT,			MENU_LEDTEST, 		MENU_VISIBLE_TRUE,		*MenuFunctionDemo38,			*MenuInitFLASH	},
		//CurMenuID,	  MaxMenuItem,			OkMenuID,			EscMenuID,			DownMenuID,				UpMenuID,			IsVisible				CurFunction			
		{MENU_BUSINESS,       	ROOTNO,		MENU_COINVALUE,			999,				MENU_TRANSACTIONS,		MENU_DRIVER,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo14,			*MenuInit0	},
		{MENU_COINVALUE,		BUSINESSNO,	MENU_COINVALUE1,		MENU_BUSINESS,		MENU_NOTEVALUE,     	MENU_HOLDNOTE10,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo14,			*MenuInit0	},
		{MENU_NOTEVALUE,		BUSINESSNO,	MENU_NOTEVALUE1,		MENU_BUSINESS,		MENU_CHANGEVALUE,      	MENU_COINVALUE,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo14,			*MenuInit0	},
		{MENU_CHANGEVALUE,		BUSINESSNO,	MENU_CHANGEVALUE1,		MENU_BUSINESS,		MENU_OPENCOIN,      	MENU_NOTEVALUE,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo14,			*MenuInit0	},
		{MENU_OPENCOIN,   		BUSINESSNO,			999,			MENU_BUSINESS,		MENU_OPENNOTE,			MENU_CHANGEVALUE,	MENU_VISIBLE_TRUE,		*MenuFunctionOCOIN,				*MenuInitOCOIN	},//30
		{MENU_OPENNOTE,   		BUSINESSNO,	MENU_SELECTMEI,			MENU_BUSINESS,		MENU_OPENCHANGE,		MENU_OPENCOIN,		MENU_VISIBLE_TRUE,		*MenuFunctionONOTE,				*MenuInitONOTE	},
		{MENU_OPENCHANGE,   	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_OPENREADER,		MENU_OPENNOTE,		MENU_VISIBLE_TRUE,		*MenuFunctionOCHANGE,			*MenuInitOCHANGE	},
		{MENU_OPENREADER,   	BUSINESSNO,	MENU_READEROFF,			MENU_BUSINESS,		MENU_READERCOST,		MENU_OPENCHANGE,	MENU_VISIBLE_TRUE,		*MenuFunctionONREADER,			*MenuInitONREADER	},
		{MENU_READEROFF,		SETREADER,	MENU_OPENREADER,		MENU_OPENREADER,	MENU_READERMDB,			MENU_READERMDB,		MENU_VISIBLE_TRUE,		*MenuFunctionREADERSetOFF,		*MenuInit0	},
		{MENU_READERMDB,		SETREADER,	MENU_OPENREADER,		MENU_OPENREADER,	MENU_READEROFF,	    	MENU_READEROFF,		MENU_VISIBLE_TRUE,		*MenuFunctionREADERSetMDB,		*MenuInit0	},
		{MENU_READERCOST,   	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_CHANGESERVER,		MENU_OPENREADER,	MENU_VISIBLE_TRUE,		*MenuFunctionONREADERCOST,		*MenuInitOREADERCOST},
		{MENU_CHANGESERVER,   	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_NOLIMITEDBUY,		MENU_READERCOST,	MENU_VISIBLE_TRUE,		*MenuFunctionCGSV,				*MenuInitCGSV	},
		{MENU_NOLIMITEDBUY,   	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_RETURNCOINS,		MENU_CHANGESERVER,	MENU_VISIBLE_TRUE,		*MenuFunctionNBUY,				*MenuInitNBUY	},
		{MENU_RETURNCOINS,   	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_BALANCEMIN,		MENU_NOLIMITEDBUY,	MENU_VISIBLE_TRUE,		*MenuFunctionRCOIN,				*MenuInitRCOIN	},
		{MENU_BALANCEMIN,		BUSINESSNO,			999,			MENU_BUSINESS,		MENU_MONEYMAXIN,		MENU_RETURNCOINS, 	MENU_VISIBLE_TRUE,		*MenuFunctionBMIN,				*MenuInitBMIN	},
		{MENU_MONEYMAXIN,		BUSINESSNO,			999,			MENU_BUSINESS,		MENU_IOU,				MENU_BALANCEMIN, 	MENU_VISIBLE_TRUE,		*MenuFunctionMMAX,				*MenuInitMMAX	},
		{MENU_IOU,				BUSINESSNO,			999,			MENU_BUSINESS,		MENU_DOUBTMONEY,		MENU_MONEYMAXIN,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo15,			*MenuInitIOU	},
		{MENU_DOUBTMONEY, 		BUSINESSNO,			999,			MENU_BUSINESS,		MENU_DECPOINTNUM,		MENU_IOU,			MENU_VISIBLE_TRUE,		*MenuFunctionDBMN,				*MenuInitDBMN	},
		{MENU_DECPOINTNUM,   	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_SALECONFIRM,		MENU_DOUBTMONEY,	MENU_VISIBLE_TRUE,		*MenuFunctionPONO,				*MenuInitPONO	},//40
		{MENU_SALECONFIRM,   	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_POSENABLE,			MENU_DECPOINTNUM,	MENU_VISIBLE_TRUE,		*MenuFunctionSACON,				*MenuInitSACON	},
		{MENU_POSENABLE, 	  	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_VMCPC,			    MENU_SALECONFIRM,	MENU_VISIBLE_TRUE,		*MenuFunctionPOSEN,				*MenuInitPOSEN	},
		{MENU_VMCPC, 	  	    BUSINESSNO,			999,			MENU_BUSINESS,		MENU_LARGELCD,			MENU_POSENABLE,		MENU_VISIBLE_TRUE,		*MenuFunctionPCEN,	    		*MenuInitPCEN	}, 
        {MENU_LARGELCD, 	  	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_SELECTKEY,			MENU_VMCPC,		    MENU_VISIBLE_TRUE,		*MenuFunctionLCDSEL,	    	*MenuInitLCDSEL	}, 
        {MENU_SELECTKEY, 	  	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_LOGOSEL,			MENU_LARGELCD,	    MENU_VISIBLE_TRUE,		*MenuFunctionKeySel,	    	*MenuInitKeySel	}, 
		{MENU_LOGOSEL, 	  		BUSINESSNO,			999,			MENU_BUSINESS,		MENU_ADDCOLUMN,			MENU_SELECTKEY,	    MENU_VISIBLE_TRUE,		*MenuFunctionLogoSel,	    	*MenuInitLogoSel	}, 
		{MENU_ADDCOLUMN,  		BUSINESSNO,			999,			MENU_BUSINESS,		MENU_TENCOLUMN,			MENU_LOGOSEL,	    MENU_VISIBLE_TRUE,		*MenuFunctionAutoColumn,    	*MenuInitAutoColumn	}, 
		{MENU_TENCOLUMN,  		BUSINESSNO,			999,			MENU_BUSINESS,		MENU_HOLDNOTE,			MENU_ADDCOLUMN,	    MENU_VISIBLE_TRUE,		*MenuFunctionTenColumn,    		*MenuInitTenColumn	}, 
		{MENU_HOLDNOTE, 	  	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_HOLDNOTE5,			MENU_TENCOLUMN,		MENU_VISIBLE_TRUE,		*MenuFunctionHOLDNOTE,			*MenuInitHOLDNOTE	},
		{MENU_HOLDNOTE5, 	  	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_HOLDNOTE10,		MENU_HOLDNOTE,		MENU_VISIBLE_TRUE,		*MenuFunctionHOLDNOTE5,			*MenuInitHOLDNOTE5	},
		{MENU_HOLDNOTE10, 	  	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_COINVALUE,			MENU_HOLDNOTE5,		MENU_VISIBLE_TRUE,		*MenuFunctionHOLDNOTE10,		*MenuInitHOLDNOTE10	},
		{MENU_HOLDNOTE20, 	  	BUSINESSNO,			999,			MENU_BUSINESS,		MENU_COINVALUE,			MENU_HOLDNOTE10,	MENU_VISIBLE_TRUE,		*MenuFunctionHOLDNOTE10,		*MenuInitHOLDNOTE10	},
		
		 //CurMenuID,	  		MaxMenuItem,		OkMenuID,			EscMenuID,			DownMenuID,				UpMenuID,			CurFunction				  InitKeyTab
		
		{MENU_TRANSACTIONS,		ROOTNO,			MENU_PAYMENTS,		999,				MENU_SYSTEM,			MENU_BUSINESS,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo23,			*MenuInit0	},
		{MENU_PAYMENTS,			TRANSACTIONSNO,	MENU_INCOME,		MENU_TRANSACTIONS,	MENU_GOODS,				MENU_CLEARTRANSJIDU,MENU_VISIBLE_TRUE,		*MenuFunctionDemo24,			*MenuInit0	},
		{MENU_INCOME,			PAYMENTSNO,			999,			MENU_PAYMENTS,		MENU_NOTEINCOME,		MENU_COINSCHANGE3,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo25,			*MenuInitINCOME	},
		{MENU_NOTEINCOME,		PAYMENTSNO,			999,			MENU_PAYMENTS,		MENU_COINSINCOME,		MENU_INCOME,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo26,			*MenuInitNOIN	},//50
		{MENU_COINSINCOME,		PAYMENTSNO,			999,			MENU_PAYMENTS,		MENU_TOTALTRANS,		MENU_NOTEINCOME,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo27,			*MenuInitCOIN	},
		{MENU_TOTALTRANS,		PAYMENTSNO,			999,			MENU_PAYMENTS,		MENU_TOTALCHANGE,		MENU_COINSINCOME,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo28,			*MenuInitTOTR	},
		{MENU_TOTALCHANGE,		PAYMENTSNO,			999,			MENU_PAYMENTS,		MENU_COINSCHANGE1,		MENU_TOTALTRANS,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo29,			*MenuInitTOCH	},
		{MENU_COINSCHANGE1,		PAYMENTSNO,			999,			MENU_PAYMENTS,		MENU_COINSCHANGE2,		MENU_TOTALCHANGE,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo30,			*MenuInitCOVA1	},
		{MENU_COINSCHANGE2,		PAYMENTSNO,			999,			MENU_PAYMENTS,		MENU_COINSCHANGE3,		MENU_COINSCHANGE1,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo30,			*MenuInitCOVA2	},
		{MENU_COINSCHANGE3,		PAYMENTSNO,			999,			MENU_PAYMENTS,		MENU_INCOME,			MENU_COINSCHANGE2,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo30,			*MenuInitCOVA3	},
		{MENU_GOODS,			TRANSACTIONSNO,	MENU_SUCCESSNUM,	MENU_TRANSACTIONS,	MENU_CLEARTRANS,		MENU_PAYMENTS,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo31,			*MenuInit0	},
		{MENU_SUCCESSNUM,		3,					999,			MENU_GOODS,			MENU_DOUBTNUM,			MENU_CHANNELTRANS,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo32,			*MenuInitSUNUM	},
		{MENU_DOUBTNUM,			3,					999,			MENU_GOODS,			MENU_CHANNELTRANS,		MENU_SUCCESSNUM,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo33,			*MenuInitDBNUM	},
		{MENU_CHANNELTRANS,		3,			MENU_TRANSINPUTNUM,		MENU_GOODS,			MENU_SUCCESSNUM,		MENU_DOUBTNUM,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo34,			*MenuInit0	},    //60
		{MENU_TRANSINPUTNUM,	1,			MENU_TRANSCHANNELNO,	MENU_CHANNELTRANS,	999,					999,				MENU_VISIBLE_TRUE,		*MenuFunctionCHIN,				*MenuInitCHIN	},
		{MENU_TRANSCHANNELNO,	4,					999,			MENU_CHANNELTRANS,	MENU_TRANSSUCCESS,		MENU_TRANSDOUBT,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo36,			*MenuInitCHNO	},
		{MENU_TRANSSUCCESS,		4,					999,			MENU_CHANNELTRANS,	MENU_TRANMONEY,			MENU_TRANSCHANNELNO,MENU_VISIBLE_TRUE,		*MenuFunctionDemo37,			*MenuInitCHSU	},
		{MENU_TRANMONEY,		4,					999,			MENU_CHANNELTRANS,	MENU_TRANSDOUBT,		MENU_TRANSSUCCESS,  MENU_VISIBLE_TRUE,		*MenuFunctionDemo37,			*MenuInitCHMONEY},
		{MENU_TRANSDOUBT,		4,	 				999,			MENU_CHANNELTRANS,	MENU_TRANSCHANNELNO,	MENU_TRANMONEY,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo38,			*MenuInitCHDO	},

		//120724 by cq RecordPassword /**/
		//{MENU_CLEARTRANS,		TRANSACTIONSNO,	MENU_CONFIRMATION,	MENU_TRANSACTIONS,	MENU_PAYMENTS,			MENU_GOODS,			*MenuFunctionDemo38,			*MenuInit0	},
		{MENU_CLEARTRANS,		TRANSACTIONSNO,	MENU_PASSWORD_2,	MENU_TRANSACTIONS,	MENU_PAYMENTSJIDU,		MENU_GOODS,			MENU_VISIBLE_TRUE,		*MenuFunctionDemo38,			*MenuInit0	},

		//{MENU_PASSWORD_2,		1,				MENU_CONFIRMATION,	MENU_CLEARTRANS,	0,						999,				*MenuFunctionPW,				*MenuInitPWIN	},//0

		//{MENU_CONFIRMATION,		2,				MENU_CLEARTRANS,	MENU_CLEARTRANS,	999,					999,				*MenuFunctionCONF,				*MenuInit0	},
		{MENU_CONFIRMATION, 	2,				MENU_CLEARTRANS,	MENU_CLEARTRANS,	999,					999,				MENU_VISIBLE_TRUE,		*MenuFunctionCONF,				*MenuInit0	},


		//{MENU_CLEARTRANS,		TRANSACTIONSNO,	MENU_CONFIRMATION,	MENU_TRANSACTIONS,	MENU_PAYMENTS,			MENU_GOODS,			*MenuFunctionDemo38,			*MenuInit0	},
		//{MENU_CONFIRMATION,		2,				MENU_CLEARTRANS,	MENU_CLEARTRANS,	999,					999,				*MenuFunctionCONF,				*MenuInit0	},

		
		{MENU_PAYMENTSJIDU, 	TRANSACTIONSNO, MENU_INCOMEJIDU,		MENU_TRANSACTIONS,		MENU_GOODSJIDU, 			MENU_CLEARTRANS,			MENU_VISIBLE_TRUE,		*MenuFunctionDemo24,			*MenuInit0	},
		{MENU_INCOMEJIDU,			PAYMENTSNO, 		999,			MENU_PAYMENTSJIDU,		MENU_NOTEINCOMEJIDU,		MENU_COINSCHANGE3JIDU,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo25,			*MenuInitINCOMEJIDU },
		{MENU_NOTEINCOMEJIDU,		PAYMENTSNO, 		999,			MENU_PAYMENTSJIDU,		MENU_COINSINCOMEJIDU,		MENU_INCOMEJIDU,			MENU_VISIBLE_TRUE,		*MenuFunctionDemo26,			*MenuInitNOINJIDU	},//50
		{MENU_COINSINCOMEJIDU,		PAYMENTSNO, 		999,			MENU_PAYMENTSJIDU,		MENU_TOTALTRANSJIDU,		MENU_NOTEINCOMEJIDU,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo27,			*MenuInitCOINJIDU	},
		{MENU_TOTALTRANSJIDU,		PAYMENTSNO, 		999,			MENU_PAYMENTSJIDU,		MENU_TOTALCHANGEJIDU,		MENU_COINSINCOMEJIDU,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo28,			*MenuInitTOTRJIDU	},
		{MENU_TOTALCHANGEJIDU,		PAYMENTSNO, 		999,			MENU_PAYMENTSJIDU,		MENU_COINSCHANGE1JIDU,		MENU_TOTALTRANSJIDU,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo29,			*MenuInitTOCHJIDU	},
		{MENU_COINSCHANGE1JIDU, 	PAYMENTSNO, 		999,			MENU_PAYMENTSJIDU,		MENU_COINSCHANGE2JIDU,		MENU_TOTALCHANGEJIDU,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo30,			*MenuInitCOVA1JIDU	},
		{MENU_COINSCHANGE2JIDU, 	PAYMENTSNO, 		999,			MENU_PAYMENTSJIDU,		MENU_COINSCHANGE3JIDU,		MENU_COINSCHANGE1JIDU,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo30,			*MenuInitCOVA2JIDU	},
		{MENU_COINSCHANGE3JIDU, 	PAYMENTSNO, 		999,			MENU_PAYMENTSJIDU,		MENU_INCOMEJIDU,			MENU_COINSCHANGE2JIDU,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo30,			*MenuInitCOVA3JIDU	},
		{MENU_GOODSJIDU,	    	TRANSACTIONSNO, MENU_CHANNELTRANSJIDU,	MENU_TRANSACTIONS,	MENU_CLEARTRANSJIDU,	    MENU_PAYMENTSJIDU,			MENU_VISIBLE_TRUE,		*MenuFunctionDemo31,			*MenuInit0	},
		{MENU_CHANNELTRANSJIDU, 	1,			MENU_TRANSINPUTNUMJIDU, 	MENU_GOODSJIDU, 		999,					999,						MENU_VISIBLE_TRUE,		*MenuFunctionDemo34,			*MenuInit0	},	  //60
		{MENU_TRANSINPUTNUMJIDU,	1,			MENU_TRANSCHANNELNOJIDU,	MENU_CHANNELTRANSJIDU,	999,					999,						MENU_VISIBLE_TRUE,		*MenuFunctionCHIN,				*MenuInitCHIN	},
		{MENU_TRANSCHANNELNOJIDU,	3,					999,			MENU_CHANNELTRANSJIDU,	MENU_TRANSSUCCESSJIDU,		MENU_TRANMONEYJIDU,			MENU_VISIBLE_TRUE,		*MenuFunctionDemo36,			*MenuInitCHNO	},
		{MENU_TRANSSUCCESSJIDU, 	3,					999,			MENU_CHANNELTRANSJIDU,	MENU_TRANMONEYJIDU, 		MENU_TRANSCHANNELNOJIDU,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo37,			*MenuInitCHSUJIDU	},
		{MENU_TRANMONEYJIDU,		3,					999,			MENU_CHANNELTRANSJIDU,	MENU_TRANSCHANNELNOJIDU,	MENU_TRANSSUCCESSJIDU,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo37,			*MenuInitCHMONEYJIDU},
		
		//120724 by cq RecordPassword /**/
		//{MENU_CLEARTRANS, 	TRANSACTIONSNO, MENU_CONFIRMATION,	MENU_TRANSACTIONS,	MENU_PAYMENTS,			MENU_GOODS, 		*MenuFunctionDemo38,			*MenuInit0	},
		{MENU_CLEARTRANSJIDU,	TRANSACTIONSNO, MENU_PASSWORD_3,	MENU_TRANSACTIONS,	MENU_PAYMENTS,			MENU_GOODSJIDU,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo38,			*MenuInit0	},

		//{MENU_PASSWORD_2, 	1,				MENU_CONFIRMATION,	MENU_CLEARTRANS,	0,						999,				*MenuFunctionPW,				*MenuInitPWIN	},//0

		//{MENU_CONFIRMATION,		2,				MENU_CLEARTRANS,	MENU_CLEARTRANS,	999,					999,				*MenuFunctionCONF,				*MenuInit0	},
		{MENU_CONFIRMATIONJIDU, 	2,				MENU_CLEARTRANSJIDU,MENU_CLEARTRANSJIDU,999,					999,			MENU_VISIBLE_TRUE,		*MenuFunctionCONFJIDU,			*MenuInit0	},

		//CurMenuID,	  		MaxMenuItem,		OkMenuID,			EscMenuID,			DownMenuID,				UpMenuID,			CurFunction				  InitKeyTab
		
		{MENU_LANGUAGE,			1,				MENU_ENGLISH,		999,				MENU_CHANNEL,			MENU_TRANSACTIONS,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,				*MenuInit0	},
	    {MENU_ENGLISH,			3,				MENU_CHANNEL,		999,				MENU_CHINESE,			MENU_RUSSIAN,		MENU_VISIBLE_TRUE,		*MenuFunctionENG,				*MenuInit0	},
		{MENU_CHINESE,			3,				MENU_CHANNEL,		999,				MENU_RUSSIAN,			MENU_ENGLISH,		MENU_VISIBLE_TRUE,		*MenuFunctionCHN,				*MenuInit0	},
		{MENU_RUSSIAN,			3,				MENU_CHANNEL,		999,				MENU_ENGLISH,			MENU_CHINESE,		MENU_VISIBLE_TRUE,		*MenuFunctionRussian,			*MenuInit0	},//����˹��;by gzz 20121012
		{MENU_SYSTEM,			ROOTNO,			MENU_TIMESET,		999,				MENU_SETCHANNEL,		MENU_TRANSACTIONS,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,				*MenuInit0	},   //70
	    {MENU_TIMESET,			SYSTEMNO,		MENU_SETYEAR,		MENU_SYSTEM,		MENU_GPRSONOFF,			MENU_LEDSET,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,				*MenuInit0	},
	    {MENU_SETYEAR,			5,					999,			MENU_TIMESET,		MENU_SETMONTH,			MENU_SETMINUTE,		MENU_VISIBLE_TRUE,		*MenuFunctionYear,				*MenuInitYear	},
		{MENU_SETMONTH,			5,					999,			MENU_TIMESET,		MENU_SETDATE,			MENU_SETYEAR,		MENU_VISIBLE_TRUE,		*MenuFunctionMonth,				*MenuInitMonth	},
	   
	   //CurMenuID,	  		MaxMenuItem,		OkMenuID,			EscMenuID,			DownMenuID,				UpMenuID,			CurFunction				 		 InitKeyTab
		{MENU_SETDATE,			5,					999,			MENU_TIMESET,		MENU_SETHOUR,			MENU_SETMONTH,		MENU_VISIBLE_TRUE,		*MenuFunctionDate,				*MenuInitDate	},
		{MENU_SETHOUR,			5,					999,			MENU_TIMESET,		MENU_SETMINUTE,			MENU_SETDATE,		MENU_VISIBLE_TRUE,		*MenuFunctionHour,				*MenuInitHour	},
		{MENU_SETMINUTE,		5,					999,			MENU_TIMESET,		MENU_SETYEAR,			MENU_SETHOUR,		MENU_VISIBLE_TRUE,		*MenuFunctionMinute,			*MenuInitMinute	},
		{MENU_CGPASSWORD,		SYSTEMNO,			999,			MENU_SYSTEM,		MENU_GPRSONOFF,			MENU_TIMESET,		MENU_VISIBLE_FAUSE,		*MenuFunctionDemo1,				*MenuInit0	},
//		{MENU_CGPASSWORD,		SYSTEMNO,		MENU_NEWPW,			MENU_SYSTEM,		MENU_GPRSONOFF,			MENU_TIMESET,		*MenuFunctionDemo1,				*MenuInit0	},
		{MENU_NEWPW,			2,					999,			MENU_CGPASSWORD,	MENU_NEWPWREPEAT,		MENU_NEWPW,			MENU_VISIBLE_FAUSE,		*MenuFunctionNEWPW,				*MenuInit0	},
		{MENU_NEWPWREPEAT,		2,					999,			MENU_CGPASSWORD,	MENU_NEWPW,				MENU_NEWPWREPEAT,	MENU_VISIBLE_FAUSE,		*MenuFunctionNEWPW2,			*MenuInit0	},
		{MENU_GPRSONOFF,		SYSTEMNO,			999,			MENU_SYSTEM,		MENU_SERIALNO,			MENU_TIMESET,		MENU_VISIBLE_FAUSE,		*MenuFunctionGPRS,				*MenuInitGPRS	},//80
		{MENU_SERIALNO,			SYSTEMNO,			999,			MENU_SYSTEM,		MENU_GSMNO,				MENU_GPRSONOFF,		MENU_VISIBLE_FAUSE,		*MenuFunctionSENO,				*MenuInitSENO	},
		{MENU_GSMNO,			SYSTEMNO,			999,			MENU_SYSTEM,		MENU_TEMPERATURE,		MENU_SERIALNO,		MENU_VISIBLE_FAUSE,		*MenuFunctionGSMNO,				*MenuInitGSMNO	},
        {MENU_TEMPERATURE,		SYSTEMNO,			999,			MENU_SYSTEM,		MENU_SYSLANGUAGE,		MENU_GSMNO,			MENU_VISIBLE_FAUSE,		*MenuFunctionTemprature,		*MenuInitTemerature	},
		{MENU_SYSLANGUAGE,		SYSTEMNO,		MENU_SYSENGLISH,		MENU_SYSTEM,		MENU_TEMPSET,			MENU_TEMPERATURE,			MENU_VISIBLE_FAUSE,		*MenuFunctionDemo1,				*MenuInit0	},
	    {MENU_SYSENGLISH,		LANGUAGENO,		MENU_SYSLANGUAGE,		MENU_SYSLANGUAGE,	MENU_SYSCHINESE,		MENU_SYSTURKEY,				MENU_VISIBLE_FAUSE,		*MenuFunctionENG,				*MenuInit0	},
		{MENU_SYSCHINESE,		LANGUAGENO,		MENU_SYSLANGUAGE,		MENU_SYSLANGUAGE,	MENU_SYSRUSSIAN,		MENU_SYSENGLISH,			MENU_VISIBLE_FAUSE,		*MenuFunctionCHN,				*MenuInit0	},
		{MENU_SYSRUSSIAN,		LANGUAGENO,		MENU_SYSLANGUAGE,		MENU_SYSLANGUAGE,	MENU_SYSTURKEY,			MENU_SYSCHINESE,			MENU_VISIBLE_FAUSE,		*MenuFunctionRussian,			*MenuInit0	},//����˹��;by gzz 20121012
		{MENU_SYSTURKEY	,		LANGUAGENO,		MENU_SYSLANGUAGE,		MENU_SYSLANGUAGE,	MENU_SYSENGLISH,		MENU_SYSRUSSIAN,			MENU_VISIBLE_FAUSE,		*MenuFunctionTurkey,			*MenuInit0	},//����˹��;by gzz 20121012
		{MENU_TEMPSET,			SYSTEMNO,		MENU_TEMPON,			MENU_SYSTEM,		MENU_LEDSET,			MENU_SYSLANGUAGE,			MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,				*MenuInit0	},//���ѹ��������;by gzz 20121224
		{MENU_TEMPON,				5,					999,			MENU_TEMPSET,		MENU_TEMPHOURSTR,		MENU_TEMPMINUTEEND,			MENU_VISIBLE_TRUE,		*MenuFunctionCompressOn,		*MenuInitCompressOn	},
		{MENU_TEMPHOURSTR,			5,					999,			MENU_TEMPSET,		MENU_TEMPMINUTESTR,		MENU_TEMPON,				MENU_VISIBLE_TRUE,		*MenuFunctionCompressHourOn,	*MenuInitCompressHourOn	},
		{MENU_TEMPMINUTESTR,		5,					999,			MENU_TEMPSET,		MENU_TEMPHOUREND,		MENU_TEMPHOURSTR,			MENU_VISIBLE_TRUE,		*MenuFunctionCompressMinuteOn,	*MenuInitCompressMinuteOn	},
		{MENU_TEMPHOUREND,			5,					999,			MENU_TEMPSET,		MENU_TEMPMINUTEEND,		MENU_TEMPMINUTESTR,			MENU_VISIBLE_TRUE,		*MenuFunctionCompressHourOff,	*MenuInitCompressHourOff	},
		{MENU_TEMPMINUTEEND,		5,					999,			MENU_TEMPSET,		MENU_TEMPON,			MENU_TEMPHOUREND,			MENU_VISIBLE_TRUE,		*MenuFunctionCompressMinuteOff,	*MenuInitCompressMinuteOff	},
		{MENU_LEDSET,			SYSTEMNO,		MENU_LEDON,				MENU_SYSTEM,		MENU_TIMESET,			MENU_TEMPSET,				MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,				*MenuInit0	},//���չʾ�ƿ���;by gzz 20121229
		{MENU_LEDON,				5,					999,			MENU_LEDSET,		MENU_LEDHOURSTR,		MENU_LEDMINUTEEND,			MENU_VISIBLE_TRUE,		*MenuFunctionLEDOn,				*MenuInitLEDOn	},
		{MENU_LEDHOURSTR,			5,					999,			MENU_LEDSET,		MENU_LEDMINUTESTR,		MENU_LEDON,					MENU_VISIBLE_TRUE,		*MenuFunctionLEDHourOn,			*MenuInitLEDHourOn	},
		{MENU_LEDMINUTESTR,			5,					999,			MENU_LEDSET,		MENU_LEDHOUREND,		MENU_LEDHOURSTR,			MENU_VISIBLE_TRUE,		*MenuFunctionLEDMinuteOn,		*MenuInitLEDMinuteOn	},
		{MENU_LEDHOUREND,			5,					999,			MENU_LEDSET,		MENU_LEDMINUTEEND,		MENU_LEDMINUTESTR,			MENU_VISIBLE_TRUE,		*MenuFunctionLEDHourOff,		*MenuInitLEDHourOff	},
		{MENU_LEDMINUTEEND,			5,					999,			MENU_LEDSET,		MENU_LEDON,				MENU_LEDHOUREND,			MENU_VISIBLE_TRUE,		*MenuFunctionLEDMinuteOff,		*MenuInitLEDMinuteOff	},
		{MENU_SETCHANNEL,		ROOTNO,			MENU_PASSWORD,		999,				MENU_DEFAULTSET,		MENU_SYSTEM,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo23,			*MenuInit0	},
		{MENU_INPUTLAYER,		1,				MENU_LAYERNO,		MENU_SETCHANNEL,	999,					999,				MENU_VISIBLE_TRUE,		*MenuFunctionLAYIN,				*MenuInitLAYIN	},

		//121105 by cq TenChannels
		//{MENU_LAYERNO,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_LAYENABLE,			MENU_CHANNEL8,		*MenuFunctionDemo1,				*MenuInitLAYNO	},
		//CurMenuID,	  		MaxMenuItem,		OkMenuID,			EscMenuID,			DownMenuID,				UpMenuID,			CurFunction				 		 InitKeyTab
		{MENU_LAYERNO,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_LAYENABLE, 		MENU_CHANNELNUM0,		MENU_VISIBLE_TRUE,		*MenuFunctionDemo1, 			*MenuInitLAYNO	},
		{MENU_LAYENABLE,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_MAXGOODS,			MENU_LAYERNO,			MENU_VISIBLE_TRUE,		*MenuFunctionLAYENABLE,			*MenuInitLAYENABLE	},
		{MENU_MAXGOODS,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL1,			MENU_LAYENABLE,			MENU_VISIBLE_TRUE,		*MenuFunctionMAXGOODS,			*MenuInitMAXGOODS	},
		{MENU_CHANNEL1,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM1,		MENU_MAXGOODS,			MENU_VISIBLE_TRUE,		*MenuFunctionCH1,				*MenuInitCH1	},
		{MENU_CHANNELNUM1,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL2,			MENU_CHANNEL1,			MENU_VISIBLE_TRUE,		*MenuFunctionCH1Num,			*MenuInitCH1Num	},
		{MENU_CHANNEL2,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM2,		MENU_CHANNELNUM1,		MENU_VISIBLE_TRUE,		*MenuFunctionCH2,				*MenuInitCH2	},
		{MENU_CHANNELNUM2,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL3,			MENU_CHANNEL2,			MENU_VISIBLE_TRUE,		*MenuFunctionCH2Num,			*MenuInitCH2Num	},
		{MENU_CHANNEL3,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM3,		MENU_CHANNELNUM2,		MENU_VISIBLE_TRUE,		*MenuFunctionCH3,				*MenuInitCH3	},//90
		{MENU_CHANNELNUM3,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL4,			MENU_CHANNEL3,			MENU_VISIBLE_TRUE,		*MenuFunctionCH3Num,			*MenuInitCH3Num	},
		{MENU_CHANNEL4,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM4,		MENU_CHANNELNUM3,		MENU_VISIBLE_TRUE,		*MenuFunctionCH4,				*MenuInitCH4	},
		{MENU_CHANNELNUM4,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL5,			MENU_CHANNEL4,			MENU_VISIBLE_TRUE,		*MenuFunctionCH4Num,			*MenuInitCH4Num	},
		{MENU_CHANNEL5,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM5,		MENU_CHANNELNUM4,		MENU_VISIBLE_TRUE,		*MenuFunctionCH5,				*MenuInitCH5	},
		{MENU_CHANNELNUM5,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL6,			MENU_CHANNEL5,			MENU_VISIBLE_TRUE,		*MenuFunctionCH5Num,			*MenuInitCH5Num	},
		{MENU_CHANNEL6,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM6,		MENU_CHANNELNUM5,		MENU_VISIBLE_TRUE,		*MenuFunctionCH6,				*MenuInitCH6	},
		{MENU_CHANNELNUM6,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL7,			MENU_CHANNEL6,			MENU_VISIBLE_TRUE,		*MenuFunctionCH6Num,			*MenuInitCH6Num	},
		{MENU_CHANNEL7,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM7,		MENU_CHANNELNUM6,		MENU_VISIBLE_TRUE,		*MenuFunctionCH7,				*MenuInitCH7	},
		{MENU_CHANNELNUM7,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL8,			MENU_CHANNEL7,			MENU_VISIBLE_TRUE,		*MenuFunctionCH7Num,			*MenuInitCH7Num	},
		//{MENU_CHANNEL8,		SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_LAYERNO,			MENU_CHANNEL7,		*MenuFunctionCH8,				*MenuInitCH8	},
		{MENU_CHANNEL8, 	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM8,		MENU_CHANNELNUM7,		MENU_VISIBLE_TRUE,		*MenuFunctionCH8,				*MenuInitCH8	},
		{MENU_CHANNELNUM8,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL9,			MENU_CHANNEL8,			MENU_VISIBLE_TRUE,		*MenuFunctionCH8Num,			*MenuInitCH8Num	},	
		{MENU_CHANNEL9, 	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM9,		MENU_CHANNELNUM8,		MENU_VISIBLE_TRUE,		*MenuFunctionCH9,				*MenuInitCH9	},
		{MENU_CHANNELNUM9,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNEL0,			MENU_CHANNEL9,			MENU_VISIBLE_TRUE,		*MenuFunctionCH9Num,			*MenuInitCH9Num	},
		{MENU_CHANNEL0, 	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_CHANNELNUM0,		MENU_CHANNELNUM9,		MENU_VISIBLE_TRUE,		*MenuFunctionCH0,				*MenuInitCH0	},
		{MENU_CHANNELNUM0,	SETCHANNELNO,			999,			MENU_INPUTLAYER,	MENU_LAYERNO,			MENU_CHANNEL0,			MENU_VISIBLE_TRUE,		*MenuFunctionCH0Num,			*MenuInitCH0Num	},
		
		{MENU_NOTEVALUE1,		NOTEVALUENO,		999,			MENU_NOTEVALUE,		MENU_NOTEVALUE2,     	MENU_NOTEVALUE8,	MENU_VISIBLE_TRUE,		*MenuFunctionNOCH1,				*MenuInitNOCH1	},
		{MENU_NOTEVALUE2,		NOTEVALUENO,		999,			MENU_NOTEVALUE,		MENU_NOTEVALUE3,     	MENU_NOTEVALUE1,	MENU_VISIBLE_TRUE,		*MenuFunctionNOCH2,				*MenuInitNOCH2	},
		{MENU_NOTEVALUE3,		NOTEVALUENO,		999,			MENU_NOTEVALUE,		MENU_NOTEVALUE4,     	MENU_NOTEVALUE2,	MENU_VISIBLE_TRUE,		*MenuFunctionNOCH3,				*MenuInitNOCH3	},
		{MENU_NOTEVALUE4,		NOTEVALUENO,		999,			MENU_NOTEVALUE,		MENU_NOTEVALUE5,     	MENU_NOTEVALUE3,	MENU_VISIBLE_TRUE,		*MenuFunctionNOCH4,				*MenuInitNOCH4	},
		{MENU_NOTEVALUE5,		NOTEVALUENO,		999,			MENU_NOTEVALUE,		MENU_NOTEVALUE6,     	MENU_NOTEVALUE4,	MENU_VISIBLE_TRUE,		*MenuFunctionNOCH5,				*MenuInitNOCH5	},//100
		{MENU_NOTEVALUE6,		NOTEVALUENO,		999,			MENU_NOTEVALUE,		MENU_NOTEVALUE7,     	MENU_NOTEVALUE5,	MENU_VISIBLE_TRUE,		*MenuFunctionNOCH6,				*MenuInitNOCH6	},
		{MENU_NOTEVALUE7,		NOTEVALUENO,		999,			MENU_NOTEVALUE,		MENU_NOTEVALUE8,     	MENU_NOTEVALUE6,	MENU_VISIBLE_TRUE,		*MenuFunctionNOCH7,				*MenuInitNOCH7	},
		{MENU_NOTEVALUE8,		NOTEVALUENO,		999,			MENU_NOTEVALUE,		MENU_NOTEVALUE1,     	MENU_NOTEVALUE7,	MENU_VISIBLE_TRUE,		*MenuFunctionNOCH8,				*MenuInitNOCH8	},
		{MENU_COINVALUE1,		COINVALUENO,		999,			MENU_COINVALUE,		MENU_COINVALUE2,     	MENU_COINVALUE8,	MENU_VISIBLE_TRUE,		*MenuFunctionCOCH1,				*MenuInitCOCH1	},
		{MENU_COINVALUE2,		COINVALUENO,		999,			MENU_COINVALUE,		MENU_COINVALUE3,     	MENU_COINVALUE1,	MENU_VISIBLE_TRUE,		*MenuFunctionCOCH2,				*MenuInitCOCH2	},
		{MENU_COINVALUE3,		COINVALUENO,		999,			MENU_COINVALUE,		MENU_COINVALUE4,     	MENU_COINVALUE2,	MENU_VISIBLE_TRUE,		*MenuFunctionCOCH3,				*MenuInitCOCH3	},
		{MENU_COINVALUE4,		COINVALUENO,		999,			MENU_COINVALUE,		MENU_COINVALUE5,     	MENU_COINVALUE3,	MENU_VISIBLE_TRUE,		*MenuFunctionCOCH4,				*MenuInitCOCH4	},
		{MENU_COINVALUE5,		COINVALUENO,		999,			MENU_COINVALUE,		MENU_COINVALUE6,     	MENU_COINVALUE4,	MENU_VISIBLE_TRUE,		*MenuFunctionCOCH5,				*MenuInitCOCH5	},
		{MENU_COINVALUE6,		COINVALUENO,		999,			MENU_COINVALUE,		MENU_COINVALUE7,     	MENU_COINVALUE5,	MENU_VISIBLE_TRUE,		*MenuFunctionCOCH6,				*MenuInitCOCH6	},
		{MENU_COINVALUE7,		COINVALUENO,		999,			MENU_COINVALUE,		MENU_COINVALUE8,     	MENU_COINVALUE6,	MENU_VISIBLE_TRUE,		*MenuFunctionCOCH7,				*MenuInitCOCH7	},//110
		{MENU_COINVALUE8,		COINVALUENO,		999,			MENU_COINVALUE,		MENU_COINVALUE1,     	MENU_COINVALUE7,	MENU_VISIBLE_TRUE,		*MenuFunctionCOCH8,				*MenuInitCOCH8	},
		{MENU_CHANGEVALUE1,		CHANGEVALUENO,		999,			MENU_CHANGEVALUE,	MENU_CHANGEVALUE2,    	MENU_CHANGEVALUE3,	MENU_VISIBLE_TRUE,		*MenuFunctionCGVA1,				*MenuInitCGVA1	},
 	    {MENU_CHANGEVALUE2,		CHANGEVALUENO,		999,			MENU_CHANGEVALUE,	MENU_CHANGEVALUE3,    	MENU_CHANGEVALUE1,	MENU_VISIBLE_TRUE,		*MenuFunctionCGVA2,				*MenuInitCGVA2	},
 	    {MENU_CHANGEVALUE3,		CHANGEVALUENO,		999,			MENU_CHANGEVALUE,	MENU_CHANGEVALUE1,   	MENU_CHANGEVALUE2,	MENU_VISIBLE_TRUE,		*MenuFunctionCGVA3,				*MenuInitCGVA3	},
 		{MENU_DEFAULTSET,		ROOTNO,			MENU_CONFIRMSET,		999,			MENU_CHANNEL,			MENU_SETCHANNEL,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo23,			*MenuInit0	},
		{MENU_CONFIRMSET,		2,				MENU_DEFAULTSET,	MENU_DEFAULTSET,		999,					999,			MENU_VISIBLE_TRUE,		*MenuFunctionCONFSET,			*MenuInit0	},
		//{MENU_SYNGOODSCOL,		ROOTNO,			    999,			999,				MENU_ADDCOIN,			MENU_DEFAULTSET,	*MenuFunctionSynGoodsCol,		*MenuInit0	},
		//{MENU_ADDCOIN,		    ROOTNO,				999,			999,				MENU_ADDBILL,			MENU_SYNGOODSCOL,	*MenuFunctionAddCoinChanges,	*MenuInit0	},
		//{MENU_ADDBILL,		    ROOTNO,				999,			999,				MENU_CHANNEL,			MENU_ADDCOIN,	    *MenuFunctionAddBillChanges,	*MenuInit0	},
		
 	   //CurMenuID,	  			MaxMenuItem,		OkMenuID,			EscMenuID,			DownMenuID,				UpMenuID,			CurFunction				 	 InitKeyTab

		{MENU_NOTETESTCONFIRM,		2,			MENU_NOTESTAT,		MENU_NOTESTAT,			999,						999,		MENU_VISIBLE_TRUE,		*MenuFunctionNOTETEST,			*MenuInit0	},
		{MENU_COINSTESTCONFIRM,		2,			MENU_COINSSTAT,		MENU_COINSSTAT,			999,						999,		MENU_VISIBLE_TRUE,		*MenuFunctionCOINSTEST,			*MenuInit0	},
		{MENU_SUBALLCHANNELSTAT,	2,				999,			MENU_ALLCHANNELSTAT,MENU_SUBALLCHANNELSTAT,	MENU_SUBALLCHANNELSTAT,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,			*MenuInit0	},
		{MENU_SUBCHTESTRESULT,		2,				999,			MENU_CHTESTRESULT,	MENU_SUBCHTESTRESULT,	MENU_SUBCHTESTRESULT,	MENU_VISIBLE_TRUE,		*MenuFunctionDemo1,			*MenuInit0	},//120
		{MENU_SELECTMEI,		SETNOTE,		MENU_OPENNOTE,		MENU_OPENNOTE,		MENU_SELECTGBA,			MENU_SELECTCLOSE,	MENU_VISIBLE_TRUE,		*MenuFunctionSetMEI,				*MenuInit0	},
		{MENU_SELECTGBA,		SETNOTE,		MENU_OPENNOTE,		MENU_OPENNOTE,		MENU_SELECTITL,	    	MENU_SELECTMEI,		MENU_VISIBLE_TRUE,		*MenuFunctionSetGBA,				*MenuInit0	},
		{MENU_SELECTITL,        SETNOTE,		MENU_OPENNOTE,		MENU_OPENNOTE,		MENU_SELECTCLOSE,		MENU_SELECTGBA,		MENU_VISIBLE_TRUE,		*MenuFunctionSetITL,				*MenuInit0	},
		{MENU_SELECTCLOSE,		SETNOTE,		MENU_OPENNOTE,		MENU_OPENNOTE,		MENU_SELECTMEI,			MENU_SELECTITL,		MENU_VISIBLE_TRUE,		*MenuFunctionSetClose,				*MenuInit0	},
	//	{MENU_HOLDNOTE5,		HOLDNOTENO,		MENU_OPENNOTE,		MENU_OPENNOTE,		MENU_SELECTMEI,			MENU_SELECTGBA,		*MenuFunctionSetClose,				*MenuInit0	},
	//	{MENU_HOLDNOTE10,		HOLDNOTENO,		MENU_OPENNOTE,		MENU_OPENNOTE,		MENU_SELECTMEI,			MENU_SELECTGBA,		*MenuFunctionSetClose,				*MenuInit0	}
	

		//120724 by cq RecordPassword /**/
		//120729 by cq RecordPassword /**/
		{MENU_PASSWORD_2,		1,				MENU_CONFIRMATION,	MENU_CLEARTRANS,		0,						999,				MENU_VISIBLE_TRUE,		*MenuFunctionPW2,				*MenuInitPWIN	},//0
		{MENU_PASSWORD_3,		1,			MENU_CONFIRMATIONJIDU,	MENU_CLEARTRANSJIDU,	0,						999,				MENU_VISIBLE_TRUE,		*MenuFunctionPW3,				*MenuInitPWIN	},//0
		{MENU_PASSWORD_ADMIN,		1,		MENU_CONFIRMATIONJIDU,	MENU_CLEARTRANSJIDU,				0,						999,				MENU_VISIBLE_TRUE,		*MenuFunctionPWAdmin,			*MenuInitPWIN	},//0
};


 


/*****************************************************************************
** Function name:	DispTextLine	
**
** Descriptions:	��ʾ�˵���Ϣ
**					
**
** parameters:		Row�У�MenuText��ʾ��Ϣ,DispAttribû��
** Returned value:	��
** 
*****************************************************************************/
//change by liya 20121013
void DispTextLine(unsigned char Row, const char * 	MenuText,unsigned char DispAttrib)
{
//
//uint8_t  temp[16];
//change by liya 20121013
	/*
   if(SYSPara.Language == 3)//change by liya 20121013
   {
		 if (Row == 1)
		 {
			if(DispAttrib==1)
				GetScriptUnicode(1,1,MenuText,strlen(MenuText),1);
			else
				GetScriptUnicode(1,1,MenuText,strlen(MenuText),0);
		 }
		 if (Row == 2)
		 {
			if(DispAttrib==1)
				GetScriptUnicode(2,1,MenuText,strlen(MenuText),1);
			else
				GetScriptUnicode(2,1,MenuText,strlen(MenuText),0);
		 }
		 if(SYSPara.LCDSel==1)
		 {
			 if (Row == 3)
			 {
				if(DispAttrib==1)
					GetScriptUnicode(1,2,MenuText,strlen(MenuText),1);
				else
					GetScriptUnicode(1,2,MenuText,strlen(MenuText),0);
			 }
			 if (Row == 4)
			 {
				if(DispAttrib==1)
					GetScriptUnicode(2,2,MenuText,strlen(MenuText),1);
				else
					GetScriptUnicode(2,2,MenuText,strlen(MenuText),0);
			}
		 }
		 //else
		 //{
		//	GetScriptUnicode(1,2,"					   ",strlen("					  "),0);
		//	GetScriptUnicode(2,2,"					   ",strlen("					  "),0);
		 //}/
   }
   */
	//else
	//{
		 if (Row == 1)
		 {
			Write_LCD(LINE0,MenuText,strlen(MenuText));
			//���Ʒ;��Ļ�ļ���;by gzz 20121025
			if(SYSPara.LCDSel==2)
			{
				 Pitu_LCDPrintf(LINE0,0,MenuText,strlen(MenuText),1,0);//ƴͼ��Ļ��ʽ;by gzz 20121106
			}
			else
			{
				if(SYSPara.Language == 2)
				{
					if(SYSPara.LCDSel==1)
						GetScriptUnicode(1,1,MenuText,strlen(MenuText),1);
					else
						GetScriptUnicode(1,2,MenuText,strlen(MenuText),1);
				}
			}
		 }
		 if (Row == 2)
			Write_LCD(LINE1,MenuText,strlen(MenuText));
		 //���Ʒ;��Ļ�ļ���;by gzz 20121025
		 if(IsLargeLCD())
		 {
			 if (Row == 3)
				Write_LCD(LINE2,MenuText,strlen(MenuText));
			 if (Row == 4)
				Write_LCD(LINE3,MenuText,strlen(MenuText));
		 }
	//}
}





/*****************************************************************************
** Function name:	DispMenu_Password	
**
** Descriptions:	��ת��������ʾ���뺯�� 	
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void DispMenu_Password(uint8_t udkey)				  
{
 //	ClearScreen();
//	KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
//	(*KeyInitPtr)();
//	DispTextLine(1,&Menu_Password[Language][0][0],0);
//	InputSite = 0x80+strlen(Menu_Password[Language][0])/2;
	//InputSite = 0x86;

	KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
	(*KeyInitPtr)();
	
	
	ClearScreen();

	Line_Reverse(0);
	

	DispTextLine(1,&Menu_Password[SYSPara.Language][0][0],0);
	//change by liya 2012-10-16
	DispTextLine(2,"                   ",20);
	InputSite = 0x80+strlen(Menu_Password[SYSPara.Language][0])/2;
	CursorLine = LINE0;
		
}


/*****************************************************************************
** Function name:	DispMenu_Language	
**
** Descriptions:	��ʾ���Բ˵�ѡ��
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void DispMenu_Language(uint8_t udkey)				 //���Բ˵�//����˹��;by gzz 20121012
{
	SYSPara.Language = 1;
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_LanguageID[cMenuTemp1])   
		{			
			//ClearScreen();
			/*
			if( cMenuTemp1	< (KeyTab[iMenuNextID].KeyTab_MaxItems -1))
			{
				Line_Reverse(0);
				DispTextLine(1,&Menu_Language[SYSPara.Language][cMenuTemp1][0],0);
				DispTextLine(2,&Menu_Language[SYSPara.Language][cMenuTemp1+1][0],1);
				CursorLine = LINE0;
			}
			else
			{
				Line_Reverse(1) ;
				DispTextLine(1,&Menu_Language[SYSPara.Language][cMenuTemp1-1][0],0);
				DispTextLine(2,&Menu_Language[SYSPara.Language][cMenuTemp1][0],1);
				CursorLine = LINE1;
			}
			*/
			/*
			Line_Reverse(0);
			DispTextLine(1,&Menu_Language[SYSPara.Language][cMenuTemp1][0],0);
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			DispTextLine(2,&Menu_Language[SYSPara.Language][cMenuTemp1+1][0],1);
			CursorLine = LINE0;
			break;
			*/
			ClearScreen();
			Line_Reverse(0);
			//strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
			//KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			//strcpy(strtemp1,(*KeyInitPtr)());
			//strcat(strtemp, strtemp1);
			//DispTextLine(1,strtemp,0);
			DispTextLine(1,&Menu_Language[SYSPara.Language][cMenuTemp1][0],0);
			//Line_Reverse(0);
			//InputSite = 0x80+strlen(Menu_Channel[SYSPara.Language][cMenuTemp1])/2;
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			
			//strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
			//KeyInitPtr=KeyTab[Menu_DriverID[cMenuTemp1]].InitKeyTab;
			//strcpy(strtemp1,(*KeyInitPtr)());
			//strcat(strtemp, strtemp1);
			//DispTextLine(2,strtemp,0);
			DispTextLine(2,&Menu_Language[SYSPara.Language][cMenuTemp1][0],0);
			CursorLine = LINE0;
				break;
		}
	}
}


/*****************************************************************************
** Function name:	DispMenu_Language	
**
** Descriptions:	��ʾ���Բ˵�ѡ��
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void DispMenu_SysLanguage(uint8_t udkey)				 //���Բ˵�//����˹��;by gzz 20121012
{
	SYSPara.Language = 1;
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_SysLanguageID[cMenuTemp1])   
		{			
			//ClearScreen();
			/*
			if( cMenuTemp1	< (KeyTab[iMenuNextID].KeyTab_MaxItems -1))
			{
				Line_Reverse(0);
				DispTextLine(1,&Menu_Language[SYSPara.Language][cMenuTemp1][0],0);
				DispTextLine(2,&Menu_Language[SYSPara.Language][cMenuTemp1+1][0],1);
				CursorLine = LINE0;
			}
			else
			{
				Line_Reverse(1) ;
				DispTextLine(1,&Menu_Language[SYSPara.Language][cMenuTemp1-1][0],0);
				DispTextLine(2,&Menu_Language[SYSPara.Language][cMenuTemp1][0],1);
				CursorLine = LINE1;
			}
			*/
			/*
			Line_Reverse(0);
			DispTextLine(1,&Menu_Language[SYSPara.Language][cMenuTemp1][0],0);
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			DispTextLine(2,&Menu_Language[SYSPara.Language][cMenuTemp1+1][0],1);
			CursorLine = LINE0;
			break;
			*/
			ClearScreen();
			Line_Reverse(0);
			//strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
			//KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			//strcpy(strtemp1,(*KeyInitPtr)());
			//strcat(strtemp, strtemp1);
			//DispTextLine(1,strtemp,0);
			DispTextLine(1,&Menu_Language[SYSPara.Language][cMenuTemp1][0],0);
			//Line_Reverse(0);
			//InputSite = 0x80+strlen(Menu_Channel[SYSPara.Language][cMenuTemp1])/2;
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			
			//strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
			//KeyInitPtr=KeyTab[Menu_DriverID[cMenuTemp1]].InitKeyTab;
			//strcpy(strtemp1,(*KeyInitPtr)());
			//strcat(strtemp, strtemp1);
			//DispTextLine(2,strtemp,0);
			DispTextLine(2,&Menu_Language[SYSPara.Language][cMenuTemp1][0],0);
			CursorLine = LINE0;
				break;
		}
	}
}



/*****************************************************************************
** Function name:	DispMenu_Root	
**
** Descriptions:	��ʾ���˵�
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
//change by liya 20121013
void DispMenu_Root(uint8_t udkey)					 //���˵�
{
	uint8_t KeyTab_TempVisible;
	char strtemp[60];
	
	
	//SYSPara.LCDSel=1;
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_RootID[cMenuTemp1])   
		{
			ClearScreen();
		//	if( cMenuTemp1	< (KeyTab[iMenuNextID].KeyTab_MaxItems -1))
		//		{
//			Line_Reverse(0);
			//�û�ģʽ�˵�;by gzz 20121130
			if(SYSPara1.AdminStat != 1)
			{
				//Trace("\r\n t1");
				//��һ��
				DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				Line_Reverse(0);
				//�ڶ���
				do
				{
					cMenuTemp1++;
					KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
				}
				while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
				if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
				{
					cMenuTemp1 = 0;
					KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
					}	
				}			
				DispTextLine(2,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
				CursorLine = LINE0;

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
						}	
					}	
					DispTextLine(3,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
						}	
					}	
					DispTextLine(4,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
					CursorLine = LINE0; 		
				}			
				break;
			}
			else
			{
				//Trace("\r\n t2");
				//��һ��
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					//Trace("\r\n t3");
					KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp,"��");
					}
					else
					{
						strcpy(strtemp,"��");
					}
					strcat(strtemp,&Menu_Root[SYSPara.Language][cMenuTemp1][0]);	
					DispTextLine(1,strtemp,1);
					//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				}
				else
				{
					DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				}
				Line_Reverse(0);
				
				//�ڶ���
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					KeyTab_TempVisible = Menu_RootID[cMenuTemp1];					
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp,"��");	
					}
					else
					{
						strcpy(strtemp,"��");	
					}					
					strcat(strtemp,&Menu_Root[SYSPara.Language][cMenuTemp1][0]);	
					DispTextLine(2,strtemp,1);
					//DispTextLine(2,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
				}
				else
				{
					DispTextLine(2,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
				}
				CursorLine = LINE0;

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{
					//������
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp,"��");	
						}
						else
						{
							strcpy(strtemp,"��");	
						}
						strcat(strtemp,&Menu_Root[SYSPara.Language][cMenuTemp1][0]);	
						DispTextLine(3,strtemp,1);
						//DispTextLine(3,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
					}
					else
					{
						DispTextLine(3,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
					}

					//������
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						  cMenuTemp1 = 0;
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_RootID[cMenuTemp1];
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp,"��");	
						}
						else
						{
							strcpy(strtemp,"��");	
						}
						strcat(strtemp,&Menu_Root[SYSPara.Language][cMenuTemp1][0]);	
						DispTextLine(4,strtemp,1);
						//DispTextLine(4,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
					}
					else
					{
						DispTextLine(4,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
					}
					CursorLine = LINE0; 		
				}			
				break;
			}
		//		}
		/*
			else
			{
//				Line_Reverse(1) ;
				DispTextLine(1,&Menu_Root[Language][cMenuTemp1][0],0);
				DispTextLine(2,&Menu_Root[Language][0][0],1);
				CursorLine = LINE1;
			}
		*/
		}
	}
}



void DispMenu_InputLayerNum(uint8_t udkey)				//������
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_InputLayerNumID[cMenuTemp1])    
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			if( cMenuTemp1	< (KeyTab[iMenuNextID].KeyTab_MaxItems ))
			{
			
				ClearScreen();
			//	Line_Reverse(0)	;
				DispTextLine(1,&Menu_InputLayerNum[SYSPara.Language][cMenuTemp1][0],0);
				InputSite = 0x80+strlen(Menu_InputLayerNum[SYSPara.Language][cMenuTemp1])/2;
				CursorLine = LINE0;
			}
		
		}
	}
}


/*****************************************************************************
** Function name:	DispMenu_InputNum	
**
** Descriptions:	�����������õĲ˵�:��ʾ�������������
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void DispMenu_Channel(uint8_t udkey)					  
{
	char strtemp[48];
	char strtemp1[48];


	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{

		if(iMenuNextID==Menu_ChannelID[cMenuTemp1])
		{
				ClearScreen();
		 

				strcpy(strtemp,&Menu_Channel[SYSPara.Language][cMenuTemp1][0]);				   //д��Ļ�ĵ�һ��
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,0);
				Line_Reverse(0);
				
				InputSite = 0x80+strlen(Menu_Channel[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_Channel[SYSPara.Language][cMenuTemp1][0]);					//д��Ļ�ĵڶ���
				KeyInitPtr=KeyTab[Menu_ChannelID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_Channel[SYSPara.Language][cMenuTemp1][0]);					//д��Ļ�ĵڶ���
					KeyInitPtr=KeyTab[Menu_ChannelID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);

					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_Channel[SYSPara.Language][cMenuTemp1][0]);					//д��Ļ�ĵڶ���
					KeyInitPtr=KeyTab[Menu_ChannelID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
				break;
		}	
		
	}



}

/*****************************************************************************
** Function name:	DispMenu_InputNum	
**
** Descriptions:	��ʾ������������
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void DispMenu_InputNum(uint8_t udkey)				 //������ֵ
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_InputChannelNoID[cMenuTemp1])   
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();									//��ʼ������
			ClearScreen();
			
			DispTextLine(1,&Menu_InputChannelNo[SYSPara.Language][cMenuTemp1][0],0);
		//	Line_Reverse(0);
			InputSite = 0x80+(strlen(Menu_InputChannelNo[SYSPara.Language][cMenuTemp1])+1)/2;
			CursorLine = LINE0;
				
		 }
	}
}



/*****************************************************************************
** Function name:	DispMenu_AddGoods	
**
** Descriptions:	����˵�:����ȫ������
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void DispMenu_AddGoods(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];


	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_InputAddGoodsID[cMenuTemp1])   
		{
			
				ClearScreen();
				strcpy(strtemp,&Menu_InputAddGoods[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				//change by liya 2012-10-16
				DispTextLine(1,strtemp,1);
			
				Line_Reverse(0);
				InputSite = 0x80+strlen(Menu_InputAddGoods[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				//change by liya 2012-10-16
				DispTextLine(2,&Menu_InputAddGoods[SYSPara.Language][cMenuTemp1][0],0);			 //д�ڶ���
				InputSite = 0x90+strlen(Menu_InputAddGoods[SYSPara.Language][cMenuTemp1])/2;
				CursorLine = LINE0;			
			   	break;
		
		}
	}
}

/*****************************************************************************
** Function name:	DispMenu_AddInputChannelNo	
**
** Descriptions:	����˵�:������ܻ���
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void DispMenu_AddInputChannelNo(uint8_t udkey)
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_AddInputLayerNumID[cMenuTemp1])    
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			if( cMenuTemp1	< (KeyTab[iMenuNextID].KeyTab_MaxItems ))
			{
			
				ClearScreen();
				//	Line_Reverse(0)	;
				DispTextLine(1,&Menu_AddInputLayerNum[SYSPara.Language][cMenuTemp1][0],1);
				//change by liya 2012-10-16
				DispTextLine(2,"                     ",0);
				InputSite = 0x80+strlen(Menu_AddInputLayerNum[SYSPara.Language][cMenuTemp1])/2;
				CursorLine = LINE0;
			}
			else
			{
				ClearScreen();
			//	Line_Reverse(1)	;
			
				DispTextLine(2,&Menu_AddInputLayerNum[SYSPara.Language][cMenuTemp1][0],0);
				CursorLine = LINE1;
			}
		}
	}
}


/*****************************************************************************
** Function name:	DispMenu_AddInputChannelNo	
**
** Descriptions:	�豸�������˵�
**					
**
** parameters:		��
** Returned value:	��
** 
*****************************************************************************/
void DispMenu_Driver(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];
	uint8_t KeyTab_TempVisible;

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_DriverID[cMenuTemp1]) 	
		{
			ClearScreen();
			//�û�ģʽ�˵�;by gzz 20121130
			if(SYSPara1.AdminStat != 1)
			{	
				//��һ��
				strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				//change by liya 2012-10-16
				DispTextLine(1,strtemp,1);
				
				Line_Reverse(0);
				InputSite = 0x80+strlen(Menu_Channel[SYSPara.Language][cMenuTemp1])/2;
				//cMenuTemp1++;
				//if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				//	 cMenuTemp1 = 0;
				//�ڶ���
				do
				{
					cMenuTemp1++;
					KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
				}
				while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
				if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
				{
					cMenuTemp1 = 0;
					KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
					}	
				}
				
				strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_DriverID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					//cMenuTemp1++;
					//if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					//	 cMenuTemp1 = 0;
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
						}	
					}
					
					strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_DriverID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);

					//cMenuTemp1++;
					//if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					//	 cMenuTemp1 = 0;
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
						}	
					}
					
					strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_DriverID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
					break;
			}
			else
			{	
				strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				//��һ��
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp1,"��");	
					}
					else
					{
						strcpy(strtemp1,"��");	
					}
					strcat(strtemp1,strtemp);	
					DispTextLine(1,strtemp1,1);
					//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				}
				else
				{
					//change by liya 2012-10-16
					DispTextLine(1,strtemp,1);
				}
				Line_Reverse(0);
				InputSite = 0x80+strlen(Menu_Channel[SYSPara.Language][cMenuTemp1])/2;

				//�ڶ���
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_DriverID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);				
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp1,"��");	
					}
					else
					{
						strcpy(strtemp1,"��");	
					}
					strcat(strtemp1,strtemp);	
					DispTextLine(2,strtemp1,1);
					//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				}
				else
				{
					DispTextLine(2,strtemp,0);
				}

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					//������
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_DriverID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp1,"��");	
						}
						else
						{
							strcpy(strtemp1,"��");	
						}
						strcat(strtemp1,strtemp);	
						DispTextLine(3,strtemp1,1);
						//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
					}
					else
					{
						DispTextLine(3,strtemp,0);
					}

					//������
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_Driver[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_DriverID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_DriverID[cMenuTemp1];
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp1,"��");	
						}
						else
						{
							strcpy(strtemp1,"��");	
						}
						strcat(strtemp1,strtemp);	
						DispTextLine(4,strtemp1,1);
						//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
					}
					else
					{
						DispTextLine(4,strtemp,0);
					}
				}
				CursorLine = LINE0;
					break;
			}	
		}
	 }
}
void DispMenu_KeyTest(uint8_t udkey)
{
 	ClearScreen();
	DispTextLine(1,&Menu_KeyTest[SYSPara.Language][0][0],0);
	//change by liya  2012-10-16
	DispTextLine(2,"                    ",0);
	InputSite = 0x90;
}
void DispMenu_DriverInputNum(uint8_t udkey)
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_DriverInputNumID[cMenuTemp1])   
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();									//��ʼ������
			ClearScreen();
			
			DispTextLine(1,&Menu_DriverInputNum[SYSPara.Language][cMenuTemp1][0],0);
		//change by liya 20121013
			DispTextLine(2,"                   ",0);
		//	Line_Reverse(0);
			//InputSite = 0x80+strlen(Menu_DriverInputNum[SYSPara.Language][cMenuTemp1])/2;
			//CursorLine = LINE0;
				
		 }
	}
}

void DispMenu_Business(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];
	uint8_t KeyTab_TempVisible;
	
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_BusinessID[cMenuTemp1])   
		{
			
			ClearScreen();
			//�û�ģʽ�˵�;by gzz 20121130
			if(SYSPara1.AdminStat != 1)
			{
				//��һ��
				strcpy(strtemp,&Menu_Business[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				//change by liya 2012-10-16
				DispTextLine(1,strtemp,1);
				Line_Reverse(0);
				InputSite = 0x80+strlen(Menu_Business[SYSPara.Language][cMenuTemp1])/2;
				//	cMenuTemp1++;
		//		if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				//if( cMenuTemp1	== (BusinessNo))
				//	 cMenuTemp1 = 0;
				//�ڶ���
				do
				{
					cMenuTemp1++;
					KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
				}
				while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
				if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
				{
					cMenuTemp1 = 0;
					KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
					}	
				}
				
				strcpy(strtemp,&Menu_Business[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_BusinessID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);
				CursorLine = LINE0;

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					//cMenuTemp1++;
			//		if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					//if( cMenuTemp1	== (BusinessNo))
					//	 cMenuTemp1 = 0;
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
						}	
					}
					strcpy(strtemp,&Menu_Business[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_BusinessID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);
					//cMenuTemp1++;
			//		if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					//if( cMenuTemp1	== (BusinessNo))
					//	 cMenuTemp1 = 0;
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
						}	
					}
					strcpy(strtemp,&Menu_Business[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_BusinessID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
					CursorLine = LINE0;					
				}
			 	break;
			}
			else
			{
				strcpy(strtemp,&Menu_Business[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				//��һ��
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp1,"��");	
					}
					else
					{
						strcpy(strtemp1,"��");	
					}
					strcat(strtemp1,strtemp);	
					DispTextLine(1,strtemp1,1);
					//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				}
				else
				{
					//change by liya 2012-10-16
					DispTextLine(1,strtemp,1);
				}
				Line_Reverse(0);
				InputSite = 0x80+strlen(Menu_Business[SYSPara.Language][cMenuTemp1])/2;

				//�ڶ���
				cMenuTemp1++;
		//		if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				if( cMenuTemp1	== (BusinessNo))
					 cMenuTemp1 = 0;
				strcpy(strtemp,&Menu_Business[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_BusinessID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp1,"��");	
					}
					else
					{
						strcpy(strtemp1,"��");	
					}
					strcat(strtemp1,strtemp);	
					DispTextLine(2,strtemp1,1);
					//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				}
				else
				{
					DispTextLine(2,strtemp,0);
				}
				CursorLine = LINE0;

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					//������
					cMenuTemp1++;
			//		if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					if( cMenuTemp1	== (BusinessNo))
						 cMenuTemp1 = 0;
					strcpy(strtemp,&Menu_Business[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_BusinessID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp1,"��");	
						}
						else
						{
							strcpy(strtemp1,"��");	
						}
						strcat(strtemp1,strtemp);	
						DispTextLine(3,strtemp1,1);
						//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
					}
					else
					{
						DispTextLine(3,strtemp,0);
					}

					//������
					cMenuTemp1++;
			//		if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					if( cMenuTemp1	== (BusinessNo))
						 cMenuTemp1 = 0;
					strcpy(strtemp,&Menu_Business[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_BusinessID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_BusinessID[cMenuTemp1];
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp1,"��");	
						}
						else
						{
							strcpy(strtemp1,"��");	
						}
						strcat(strtemp1,strtemp);	
						DispTextLine(4,strtemp1,1);
						//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
					}
					else
					{
						DispTextLine(4,strtemp,0);
					}
					CursorLine = LINE0;					
				}
			 	break;
			}
		}
	}

}


void DispMenu_Transactions(uint8_t udkey)
{
	uint8_t KeyTab_TempVisible;
	char strtemp[60];
	
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_TransactionsID[cMenuTemp1])  
		{
		
			ClearScreen();
			Line_Reverse(0)	;
			//�û�ģʽ�˵�;by gzz 20121130
			if(SYSPara1.AdminStat != 1)
			{
				//��һ��
				DispTextLine(1,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0],1);
				//	cMenuTemp1++;
				//if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				//	 cMenuTemp1 = 0;
				//�ڶ���
				do
				{
					cMenuTemp1++;
					KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
				}
				while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
				if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
				{
					cMenuTemp1 = 0;
					KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
					}	
				}	
				DispTextLine(2,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0],0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					//cMenuTemp1++;
					//if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					//	 cMenuTemp1 = 0;
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
						}	
					}	
					DispTextLine(3,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0],0);
					
					//cMenuTemp1++;
					//if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					//	 cMenuTemp1 = 0;
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
						}	
					}	
					DispTextLine(4,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0],0);
				} 
				CursorLine = LINE0;
				break;
			}
			else
			{
				//��һ��
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp,"��");	
					}
					else
					{
						strcpy(strtemp,"��");	
					}
					strcat(strtemp,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0]);	
					DispTextLine(1,strtemp,1);
					//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				}
				else
				{
					DispTextLine(1,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0],1);
				}
				
				//�ڶ���
					cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];					
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp,"��");	
					}
					else
					{
						strcpy(strtemp,"��");	
					}					
					strcat(strtemp,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0]);	
					DispTextLine(2,strtemp,1);
					//DispTextLine(2,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
				}
				else
				{
					DispTextLine(2,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0],0);
				}
				
				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					//������
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];					
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp,"��");	
						}
						else
						{
							strcpy(strtemp,"��");	
						}					
						strcat(strtemp,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0]);	
						DispTextLine(3,strtemp,1);
						//DispTextLine(2,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
					}
					else
					{
						DispTextLine(3,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0],0);
					}

					//������
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_TransactionsID[cMenuTemp1];					
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp,"��");	
						}
						else
						{
							strcpy(strtemp,"��");	
						}					
						strcat(strtemp,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0]);	
						DispTextLine(4,strtemp,1);
						//DispTextLine(2,&Menu_Root[SYSPara.Language][cMenuTemp1][0],0);
					}
					else
					{
						DispTextLine(4,&Menu_Transactions[SYSPara.Language][cMenuTemp1][0],0);
					}
				} 
				CursorLine = LINE0;
				break;
			}
		}
	 }
}



void DispMenu_Payments(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_PaymentsID[cMenuTemp1])   
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				strcpy(strtemp,&Menu_Payments[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
			
				InputSite = 0x80+strlen(Menu_Payments[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				strcpy(strtemp,&Menu_Payments[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_PaymentsID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					strcpy(strtemp,&Menu_Payments[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_PaymentsID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					strcpy(strtemp,&Menu_Payments[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_PaymentsID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
			 	break;
		}
	}
}
void DispMenu_PaymentsJidu(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_PaymentsIDJidu[cMenuTemp1])   
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				strcpy(strtemp,&Menu_Payments[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
			
				InputSite = 0x80+strlen(Menu_Payments[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				strcpy(strtemp,&Menu_Payments[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_PaymentsIDJidu[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					strcpy(strtemp,&Menu_Payments[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_PaymentsIDJidu[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					strcpy(strtemp,&Menu_Payments[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_PaymentsIDJidu[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
			 	break;
		}
	}
}

void DispMenu_Goods(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_GoodsID[cMenuTemp1]) 	
		{
		
				ClearScreen();
				Line_Reverse(0)	;
				strcpy(strtemp,&Menu_Goods[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
			
				InputSite = 0x80+strlen(Menu_Goods[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				strcpy(strtemp,&Menu_Goods[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_GoodsID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					strcpy(strtemp,&Menu_Goods[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_GoodsID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					strcpy(strtemp,&Menu_Goods[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_GoodsID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
			 	break;
		}
	}

}

//���ڼ��Ƚ�����;by gzz 20121009
void DispMenu_GoodsJidu(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_GoodsIDJidu[cMenuTemp1]) 	
		{
		
				ClearScreen();
				Line_Reverse(0)	;
				strcpy(strtemp,&Menu_GoodsJidu[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
			
				WriteFull_LCD(LINE1,"",0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					WriteFull_LCD(LINE2,"",0);
					WriteFull_LCD(LINE3,"",0);
				}
				CursorLine = LINE0;
			 	break;
		}
	}

}


void DispMenu_ChannelTrans(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_TransChannelID[cMenuTemp1]) 	
		{
		
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_TransChannel[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_TransChannel[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_TransChannel[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_TransChannelID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				 if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_TransChannel[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_TransChannelID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_TransChannel[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_TransChannelID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
			 	break;
		}
	}
}

//���ڼ��Ƚ�����;by gzz 20121009
void DispMenu_ChannelTransJidu(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_TransChannelIDJIDU[cMenuTemp1]) 	
		{
		
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_TransChannelJidu[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_TransChannelJidu[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_TransChannelJidu[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_TransChannelIDJIDU[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_TransChannelJidu[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_TransChannelIDJIDU[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_TransChannelJidu[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_TransChannelIDJIDU[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
			 	break;
		}
	}
}


void DispMenu_TransInputChannelNo(uint8_t udkey)
	{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_TransInputChannelNoID[cMenuTemp1])    
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			if( cMenuTemp1	< (KeyTab[iMenuNextID].KeyTab_MaxItems ))
			{
			
				ClearScreen();
				//	Line_Reverse(0)	;
				DispTextLine(1,&Menu_TransInputChannelNo[SYSPara.Language][cMenuTemp1][0],0);
				//change by liya 2012-10-16
				DispTextLine(2,"                    ",0);
				InputSite = 0x80+strlen(Menu_TransInputChannelNo[SYSPara.Language][cMenuTemp1])/2;
				CursorLine = LINE0;
			}
			else
			{
				ClearScreen();
			//	Line_Reverse(1)	;
			
				DispTextLine(2,&Menu_TransInputChannelNo[SYSPara.Language][cMenuTemp1][0],1);
				CursorLine = LINE1;
			}
		}
	}
}

//���ڼ��Ƚ�����;by gzz 20121009
void DispMenu_TransInputChannelNoJidu(uint8_t udkey)
	{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_TransInputChannelNoIDJIDU[cMenuTemp1])    
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			if( cMenuTemp1	< (KeyTab[iMenuNextID].KeyTab_MaxItems ))
			{
			
				ClearScreen();
				//	Line_Reverse(0)	;
				DispTextLine(1,&Menu_TransInputChannelNo[SYSPara.Language][cMenuTemp1][0],0);
				//change by liya 2012-10-16
				DispTextLine(2,"                    ",0);
				InputSite = 0x80+strlen(Menu_TransInputChannelNo[SYSPara.Language][cMenuTemp1])/2;
				CursorLine = LINE0;
			}
			else
			{
				ClearScreen();
			//	Line_Reverse(1)	;
			
				DispTextLine(2,&Menu_TransInputChannelNo[SYSPara.Language][cMenuTemp1][0],1);
				CursorLine = LINE1;
			}
		}
	}
}

void DispMenu_CoinsTestConfirm(uint8_t udkey)
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_CoinsTestConfirmID[cMenuTemp1])  
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			ClearScreen();
		
			DispTextLine(1,&Menu_CoinsTestConfirm[SYSPara.Language][cMenuTemp1][0],0);
	//		DispTextLine(2,&Menu_InputChannelNo[cMenuTemp1+1][0],1);
			Line_Reverse(0);
			InputSite = 0x80+strlen(Menu_CoinsTestConfirm[SYSPara.Language][cMenuTemp1])/2;
			
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			
			DispTextLine(2,&Menu_CoinsTestConfirm[SYSPara.Language][cMenuTemp1][0],1);			 //д�ڶ���
			InputSite = 0x90+strlen(Menu_CoinsTestConfirm[SYSPara.Language][cMenuTemp1])/2;
			CursorLine = LINE0;			
			break;
		}
	}
}

void DispMenu_NoteTestConfirm(uint8_t udkey)
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_NoteTestConfirmID[cMenuTemp1])   
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			ClearScreen();
		
			DispTextLine(1,&Menu_NoteTestConfirm[SYSPara.Language][cMenuTemp1][0],0);
	//		DispTextLine(2,&Menu_InputChannelNo[cMenuTemp1+1][0],1);
			Line_Reverse(0);
			InputSite = 0x80+strlen(Menu_NoteTestConfirm[SYSPara.Language][cMenuTemp1])/2;
			
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			
			DispTextLine(2,&Menu_NoteTestConfirm[SYSPara.Language][cMenuTemp1][0],1);			 //д�ڶ���
			InputSite = 0x90+strlen(Menu_NoteTestConfirm[SYSPara.Language][cMenuTemp1])/2;
			CursorLine = LINE0;			
			break;
		}
	}
}

void DispMenu_Confirmation(uint8_t udkey)
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_ConfirmationID[cMenuTemp1])   
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			ClearScreen();
		
			DispTextLine(1,&Menu_Confirmation[SYSPara.Language][cMenuTemp1][0],0);
	//		DispTextLine(2,&Menu_InputChannelNo[cMenuTemp1+1][0],1);
			Line_Reverse(0);
			InputSite = 0x80+strlen(Menu_Confirmation[SYSPara.Language][cMenuTemp1])/2;
			
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			
			DispTextLine(2,&Menu_Confirmation[SYSPara.Language][cMenuTemp1][0],1);			 //д�ڶ���
			InputSite = 0x90+strlen(Menu_Confirmation[SYSPara.Language][cMenuTemp1])/2;
			CursorLine = LINE0;			
			break;
		}
	}
}

//���ڼ��Ƚ�����;by gzz 20121009
void DispMenu_ConfirmationJidu(uint8_t udkey)
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_ConfirmationIDJidu[cMenuTemp1])   
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			ClearScreen();
		
			DispTextLine(1,&Menu_Confirmation[SYSPara.Language][cMenuTemp1][0],0);
	//		DispTextLine(2,&Menu_InputChannelNo[cMenuTemp1+1][0],1);
			Line_Reverse(0);
			InputSite = 0x80+strlen(Menu_Confirmation[SYSPara.Language][cMenuTemp1])/2;
			
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			
			DispTextLine(2,&Menu_Confirmation[SYSPara.Language][cMenuTemp1][0],1);			 //д�ڶ���
			InputSite = 0x90+strlen(Menu_Confirmation[SYSPara.Language][cMenuTemp1])/2;
			CursorLine = LINE0;			
			break;
		}
	}
}

void DispMenu_System(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];
	uint8_t KeyTab_TempVisible;

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_SystemID[cMenuTemp1]) 
		{		
			ClearScreen();
			Line_Reverse(0)	;

			//�û�ģʽ�˵�;by gzz 20121130
			if(SYSPara1.AdminStat != 1)
			{
				//��һ��
				strcpy(strtemp,&Menu_System[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_System[SYSPara.Language][cMenuTemp1])/2;
				//cMenuTemp1++;
				//if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				//	 cMenuTemp1 = 0;
				//�ڶ���
				do
				{
					cMenuTemp1++;
					KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
				}
				while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
				if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
				{
					cMenuTemp1 = 0;
					KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
					}	
				}
				
				strcpy(strtemp,&Menu_System[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_SystemID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					//cMenuTemp1++;
					//if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					//	 cMenuTemp1 = 0;
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
						}	
					}
					
					strcpy(strtemp,&Menu_System[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SystemID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);
					
					//cMenuTemp1++;
					//if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					//	 cMenuTemp1 = 0;
					//������
					do
					{
						cMenuTemp1++;
						KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
					}
					while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) );
					if( cMenuTemp1	>= (KeyTab[iMenuNextID].KeyTab_MaxItems))
					{
						cMenuTemp1 = 0;
						KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
						while( (KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)&&(KeyTab[iMenuNextID].KeyTab_PressDown!=999)&&(iMenuNextID!=999)&&(cMenuTemp1 < (KeyTab[iMenuNextID].KeyTab_MaxItems)) )
						{
							cMenuTemp1++;
							KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
						}	
					}
					
					strcpy(strtemp,&Menu_System[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SystemID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
			 	break;
			}
			else
			{
				strcpy(strtemp,&Menu_System[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				//��һ��
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp1,"��");	
					}
					else
					{
						strcpy(strtemp1,"��");	
					}
					strcat(strtemp1,strtemp);	
					DispTextLine(1,strtemp1,1);
					//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				}
				else
				{
					DispTextLine(1,strtemp,1);
				}
				
				InputSite = 0x80+strlen(Menu_System[SYSPara.Language][cMenuTemp1])/2;

				//�ڶ���
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_System[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_SystemID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				//�����û��˵��ɼ�;by gzz 20121204
				//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
				if(SYSPara1.VisibleStat == 1)
				{
					KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
					if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
					{
						strcpy(strtemp1,"��");	
					}
					else
					{
						strcpy(strtemp1,"��");	
					}
					strcat(strtemp1,strtemp);	
					DispTextLine(2,strtemp1,1);
					//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
				}
				else
				{
					DispTextLine(2,strtemp,0);
				}

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					//������
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_System[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SystemID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp1,"��");	
						}
						else
						{
							strcpy(strtemp1,"��");	
						}
						strcat(strtemp1,strtemp);	
						DispTextLine(3,strtemp1,1);
						//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
					}
					else
					{
						DispTextLine(3,strtemp,0);
					}

					//������
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_System[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SystemID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					//�����û��˵��ɼ�;by gzz 20121204
					//if( (SYSPara1.VisibleStat == 1)&&(SYSPara.LCDSel== 2) )
					if(SYSPara1.VisibleStat == 1)
					{
						KeyTab_TempVisible = Menu_SystemID[cMenuTemp1];
						if(KeyTab[KeyTab_TempVisible].KeyTab_Visible == MENU_VISIBLE_FAUSE)
						{
							strcpy(strtemp1,"��");	
						}
						else
						{
							strcpy(strtemp1,"��");	
						}
						strcat(strtemp1,strtemp);	
						DispTextLine(4,strtemp1,1);
						//DispTextLine(1,&Menu_Root[SYSPara.Language][cMenuTemp1][0],1);
					}
					else
					{
						DispTextLine(4,strtemp,0);
					}
				}
				CursorLine = LINE0;
			 	break;
			}
		}
	}
}

void DispMenu_TimeSet(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];
	RTCn_GetFullTime ((RTC_TIME_Type *)&TranData.Time);
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_TimeSetID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_TimeSet[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_TimeSet[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_TimeSet[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_TimeSetID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_TimeSet[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_TimeSetID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);

					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_TimeSet[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_TimeSetID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
			 	break;
		}
	}
}

//ѹ��������
void DispMenu_TempSet(uint8_t udkey)//���ѹ��������;by gzz 20121224
{
	char strtemp[24];
	char strtemp1[16];	
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_TempSetID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_TempSet[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,0);
				
				InputSite = 0x80+strlen(Menu_TempSet[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_TempSet[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_TempSetID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_TempSet[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_TempSetID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);

					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_TempSet[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_TempSetID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
			 	break;
		}
	}
}

//չʾ������
void DispMenu_LEDSet(uint8_t udkey)//���չʾ�ƿ���;by gzz 20121229
{
	char strtemp[24];
	char strtemp1[16];	
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_LEDSetID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_LEDSet[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,0);
				
				InputSite = 0x80+strlen(Menu_LEDSet[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_LEDSet[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_LEDSetID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_LEDSet[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_LEDSetID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);

					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_LEDSet[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_LEDSetID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
			 	break;
		}
	}
}



void DispMenu_SetChannel(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_SetChannelID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_SetChannel[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_SetChannel[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_SetChannel[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_SetChannelID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
		 		if(IsLargeLCD())
				{
					
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_SetChannel[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SetChannelID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);

					
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_SetChannel[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SetChannelID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
				break;
		}
	}
}


void DispMenu_NoteValue(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_NoteValueID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_NoteValue[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_NoteValue[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_NoteValue[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_NoteValueID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_NoteValue[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_NoteValueID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);

					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_NoteValue[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_NoteValueID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
				break;
		}
	}
}
void DispMenu_ChangeValue(uint8_t udkey)
{
char strtemp[48];
char strtemp1[48];

for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
{
	
		if(iMenuNextID==Menu_ChangeValueID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_ChangeValue[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_ChangeValue[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_ChangeValue[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_ChangeValueID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_ChangeValue[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_ChangeValueID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);

					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_ChangeValue[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_ChangeValueID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
				break;
		}
	}
}
void DispMenu_CoinValue(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_CoinValueID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_CoinValue[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_CoinValue[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_CoinValue[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_CoinValueID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_CoinValue[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_CoinValueID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);

					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_CoinValue[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_CoinValueID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
				break;
		}
	}
}
void DispMenu_SetConfirmation(uint8_t udkey)
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_SetConfirmationID[cMenuTemp1])   
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			ClearScreen();
		
			DispTextLine(1,&Menu_SetConfirmation[SYSPara.Language][cMenuTemp1][0],0);
	//		DispTextLine(2,&Menu_InputChannelNo[cMenuTemp1+1][0],1);
			Line_Reverse(0);
			InputSite = 0x80+strlen(Menu_SetConfirmation[SYSPara.Language][cMenuTemp1])/2;
			
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			
			DispTextLine(2,&Menu_SetConfirmation[SYSPara.Language][cMenuTemp1][0],1);			 //д�ڶ���
			InputSite = 0x90+strlen(Menu_SetConfirmation[SYSPara.Language][cMenuTemp1])/2;
			CursorLine = LINE0;			
			break;
		}
	}
}

//�û�ģʽ�˵�;by gzz 20121130
void DispMenu_SetAdmin(uint8_t udkey)
{
	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_SetAdminID[cMenuTemp1])   
		{
			KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
			(*KeyInitPtr)();
			ClearScreen();
		
			DispTextLine(1,&Menu_SetConfirmation[SYSPara.Language][cMenuTemp1][0],0);
	//		DispTextLine(2,&Menu_InputChannelNo[cMenuTemp1+1][0],1);
			Line_Reverse(0);
			InputSite = 0x80+strlen(Menu_SetConfirmation[SYSPara.Language][cMenuTemp1])/2;
			
			cMenuTemp1++;
			if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
				 cMenuTemp1 = 0;
			
			DispTextLine(2,&Menu_SetConfirmation[SYSPara.Language][cMenuTemp1][0],1);			 //д�ڶ���
			InputSite = 0x90+strlen(Menu_SetConfirmation[SYSPara.Language][cMenuTemp1])/2;
			CursorLine = LINE0;			
			break;
		}
	}
}

void DispMenu_SubCHStat(uint8_t udkey)
{


	
	if (udkey == KEY_ENTER)	
	{
		  AllChannelStat(InLayerNO);
	}
	if (udkey ==KEY_DOWN)
	{
			if (InLayerNO < (MAXLAYER - 1) )
			{
					if(	ChnMapPara.LAYTODRV[InLayerNO +1] != 0) 
					{
						InLayerNO ++;
						AllChannelStat(InLayerNO);
					}
			}
		
	}
	if (udkey ==KEY_UP)
	{
			if (InLayerNO >0 )
			{
				InLayerNO --;
				
				AllChannelStat(InLayerNO);
		   	}
			
	}

}
void DispMenu_SubCHResult(uint8_t udkey)
{

	char	strtemp1[48];
	uint8_t	m,n;

	//Trace("\r\ninput display testresult");	
	strtemp1[0] = 0x00;

	NowLayerNo = ChnMapPara.LAYTODRV[InLayerNO];
	if (udkey ==KEY_DOWN)
	{
			
		if((InCHNO == (MAXCHANNEL-1)))	
		{
		   	
		   	if((InLayerNO) == (MAXLAYER -1)||(ChnMapPara.LAYTODRV[(InLayerNO +1)] == 0))	
			{
		   		//  NowLayerNo = 0;
				  return;						 //������
			}
			InCHNO = 0;
			(InLayerNO++);
		}
		else
			InCHNO++;

	}
	if (udkey ==KEY_UP)
	{
		if(InCHNO == 0)
		{
			if( InLayerNO == 0)
			{
				return;		//����
			}
			else
			{
				InLayerNO--;			  //����
				InCHNO = MAXCHANNEL-1;
			}
		}
		else
		{
			InCHNO--;
		}
	}
		   	
			
			
	while(1)
	{
		
		NowLayerNo = ChnMapPara.LAYTODRV[InLayerNO];
		if (NowLayerNo == 0)
			break;
		NowLayerNo--;
		NowCHNO = ChnMapPara.CHTODRV[NowLayerNo][InCHNO];
		if (NowCHNO == 0)
			break;
		NowCHNO--;
		if((Channels[NowLayerNo][NowCHNO].TestNum  ) > 0)	
		{	
			if((InLayerNO+1)>8)
				break;
			else
			{
				ClearScreen();
				Trace("\r\n%d,%derrone[%d]", InLayerNO+1, InCHNO+1,Channels[NowLayerNo][NowCHNO].TestNum);
				//change by liya 2012-10-16
				if(SYSPara.Language==3)//��������;by gzz 20121115
					sprintf( strtemp1,"%d%dKoridorun ba\xf1\x5far\xf1\x31s\xf1\x31zl\xf1\x31klar\xf1\x31n\xf1\x31n say\xf1\x31s\xf1\x31%d", InLayerNO+1, InCHNO+1,Channels[NowLayerNo][NowCHNO].TestNum);
				else if(SYSPara.Language==2)
					sprintf( strtemp1,"%d%d����ݧڧ�֧��ӧ� ���ܧѧ٧��%d", InLayerNO+1, InCHNO+1,Channels[NowLayerNo][NowCHNO].TestNum);
				else
					sprintf( strtemp1,"%d%d�������ϴ���%d", InLayerNO+1, InCHNO+1,Channels[NowLayerNo][NowCHNO].TestNum);
				Write_LCD(LINE0,strtemp1,strlen(strtemp1));
				break;
			}		 	
		}
		(InCHNO++);
		if((InCHNO == MAXCHANNEL) || (ChnMapPara.CHTODRV[NowLayerNo][InCHNO] == 0))
		{
			InCHNO = 0;
			InLayerNO++;
			if(( InLayerNO == MAXLAYER) )
			{
				break;
			}
		}
	
	}
		
		
	m=InLayerNO ;
	n= InCHNO;	
		
	Trace("\r\nStart m,n==============");	
	while(1)
	{	
		
		(n++);
		Trace("\r\nOnem=%d,n=%d", m, n);	
		if((n >= MAXCHANNEL) || (ChnMapPara.CHTODRV[NowLayerNo][n] == 0))
		{
			n = 0;
			m++;
			if(( m >= MAXLAYER) )
			{
				Trace("\r\nNow break;");
				break;
			}
		}
		Trace("\r\nTwom=%d,n=%d", m, n);
		NowLayerNo = ChnMapPara.LAYTODRV[m];
		if (NowLayerNo == 0)
			break;
		NowLayerNo--;
		NowCHNO = ChnMapPara.CHTODRV[NowLayerNo][n];
		if (NowCHNO == 0)
			break;
		NowCHNO--;
		
		if((Channels[NowLayerNo][NowCHNO].TestNum  ) > 0)	
		{	
			if((m+1)>8)
				break;
			else
			{
				Trace("\r\n%d,%derrtwo[%d]", m+1, n+1,Channels[NowLayerNo][NowCHNO].TestNum);
				//change by liya 2012-10-16
				if(SYSPara.Language==3)//��������;by gzz 20121115
					sprintf( strtemp1,"%d%dKoridorun ba\xf1\x5far\xf1\x31s\xf1\x31zl\xf1\x31klar\xf1\x31n\xf1\x31n say\xf1\x31s\xf1\x31%d", m+1, n+1,Channels[NowLayerNo][NowCHNO].TestNum);
				else if(SYSPara.Language==2)
					sprintf( strtemp1,"%d%d����ݧڧ�֧��ӧ� ���ܧѧ٧��%d", m+1, n+1,Channels[NowLayerNo][NowCHNO].TestNum);
				else
					sprintf( strtemp1,"%d%d�������ϴ���%d", m+1, n+1,Channels[NowLayerNo][NowCHNO].TestNum);
				Write_LCD(LINE1,strtemp1,strlen(strtemp1));
				break;
			}			
		}
	}

}

void DispMenu_SubNOTE(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_SetNoteID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_SetNote[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_SetNote[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_SetNote[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_SetNoteID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_SetNote[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SetNoteID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_SetNote[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SetNoteID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
				break;
		}
	}
}


//�������˵�;by gzz 20121120
void DispMenu_SubReader(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_SetReaderID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_SetReader[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_SetReader[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_SetReader[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_SetReaderID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);

				//���Ʒ;��Ļ�ļ���;by gzz 20121025
				if(IsLargeLCD())
				{
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_SetReader[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SetReaderID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(3,strtemp,0);
					cMenuTemp1++;
					if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
						 cMenuTemp1 = 0;
					
					strcpy(strtemp,&Menu_SetReader[SYSPara.Language][cMenuTemp1][0]);
					KeyInitPtr=KeyTab[Menu_SetReaderID[cMenuTemp1]].InitKeyTab;
					strcpy(strtemp1,(*KeyInitPtr)());
					strcat(strtemp, strtemp1);
					DispTextLine(4,strtemp,0);
				}
				CursorLine = LINE0;
				break;
		}
	}
}


void DispMenu_HoldNote(uint8_t udkey)
{
	char strtemp[48];
	char strtemp1[48];

	for(cMenuTemp1=0;cMenuTemp1<KeyTab[iMenuNextID].KeyTab_MaxItems;cMenuTemp1++)
	{
	
		if(iMenuNextID==Menu_HoldNoteID[cMenuTemp1]) 	
		{
			
				ClearScreen();
				Line_Reverse(0)	;
				
				strcpy(strtemp,&Menu_HoldNote[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[iMenuNextID].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(1,strtemp,1);
				
				InputSite = 0x80+strlen(Menu_HoldNote[SYSPara.Language][cMenuTemp1])/2;
				cMenuTemp1++;
				if( cMenuTemp1	== (KeyTab[iMenuNextID].KeyTab_MaxItems))
					 cMenuTemp1 = 0;
				
				strcpy(strtemp,&Menu_HoldNote[SYSPara.Language][cMenuTemp1][0]);
				KeyInitPtr=KeyTab[Menu_HoldNoteID[cMenuTemp1]].InitKeyTab;
				strcpy(strtemp1,(*KeyInitPtr)());
				strcat(strtemp, strtemp1);
				DispTextLine(2,strtemp,0);
				CursorLine = LINE0;
				break;
		}
	}
}


void JudgeHLight(uint8_t udkey)			//ˢ�½���
{
	switch(iMenuNextID)
	{
		case	MENU_PASSWORD:			
		case	MENU_PASSWORD_2://120724 by cq RecordPassword /**/
		case	MENU_PASSWORD_3://���ڼ��Ƚ�����;by gzz 20121009
		case	MENU_PASSWORD_ADMIN://�û�ģʽ�˵�;by gzz 20121130
				DispMenu_Password(udkey);
				break;
			
		case	MENU_ENGLISH:
		case	MENU_CHINESE:
		case	MENU_RUSSIAN:	//����˹��;by gzz 20121012		
				DispMenu_Language(udkey);
				break;
									//************************************************************************
									//* First Bmp--------------------->(MenuID=0)                            *
		case	MENU_LANGUAGE:		//*  ---+                                                                *
		case  	MENU_CHANNEL	:	//*     |��������----------------->(MenuID=1)                            *
				DispMenu_Root(udkey);
				break;		
									//*     +---+                                                            *
		case  	MENU_INPUTNUM	:   //*     |   |��������----------->(MenuID=2)                            *
		   		DispMenu_InputNum(udkey);
				break;		
		case  MENU_CHANNELNO	:	//*     |   |������--------------->(MenuID=3)                            *
		case  MENU_PRICE		:	//*     |   |����----------------->(MenuID=3)                            *
		case  MENU_CHANNELLEFT	:   //*     |   |��������------------->(MenuID=4)                            *	
		case  MENU_CHANNELSTAT	:	//*     |   |����״̬------------->(MenuID=4)                            *	
		case  MENU_CHANNELGOODS	:	//*     |   |����״̬------------->(MenuID=4)                            *
			DispMenu_Channel(udkey);
			break;	

		case  MENU_ADDGOODS		:	//*		|���--------------------->(MenuID=5)                            *
		case  MENU_DRIVER		:	//*     |�豸����----------------->(MenuID=5)                            *
			DispMenu_Root(udkey);
			break;						
		case  MENU_INPUTADDGOODS:	
			DispMenu_AddGoods(udkey);	//*		|��ȷ��Ҫ�����
			break;				
		case  MENU_ADDINPUTLAY:
			DispMenu_AddInputChannelNo(udkey);
			break;		
		case  MENU_NOTESTAT		:	//*     |   |ֽ����״̬----------->(MenuID=6)                            *
		case  MENU_COINSSTAT	:	//*     |   |Ӳ����״̬----------->(MenuID=7)                            *
		case  MENU_HOPPERSTAT1	:	//*     |   |������״̬----------->(MenuID=8)                            *
		case  MENU_HOPPERSTAT2	:	//*     |   |������״̬----------->(MenuID=8)                            *
		case  MENU_HOPPERSTAT3	:	//*     |   |������״̬----------->(MenuID=8)                            *
		case  MENU_KEYTEST		:	//*     |   |��ť���------------->(MenuID=9)                            *
		case  MENU_CHANNELTEST	:	//*     |   |�������------------->(MenuID=10)                           *
		case  MENU_ALLCHANNELSTAT  :
		case  MENU_GPRSTEST		:	//*     |   |�ֻ�ģ��״̬����----->(MenuID=11)                           *
		case  MENU_SMSTEST		:	//*     |   |����Ϣ���----------->(MenuID=12)                           *
		case  MENU_CHTESTRESULT	:
		case  MENU_IRTEST		:
		case  MENU_LCDTEST		:
		case  MENU_TEMPRATURETEST:
		case  MENU_SELECTKEYTEST:	
		case  MENU_TEMPSTEST:		//���ѹ��������;by gzz 20121224
		case  MENU_LEDTEST:			//���չʾ�ƿ���;by gzz 20121229
		case  MENU_FLASHLEFT	:
			DispMenu_Driver(udkey);
			break;					
		case  MENU_DOKEYTEST	:	//*     |   +--------------                                              *
			DispMenu_KeyTest(udkey);
			break;	
		case  MENU_NOTETESTCONFIRM 	:
			DispMenu_NoteTestConfirm(udkey);	//*		|ֽ����������
			break;
		case  	MENU_COINSTESTCONFIRM	:
			DispMenu_CoinsTestConfirm(udkey);//*		|Ӳ����������
			break;
		case  MENU_DRINPUTNUM		:	//*     |   |��������----------->(MenuID=2)                            *
		   	DispMenu_DriverInputNum(udkey);
					break;		
		case  MENU_BUSINESS		:	//*     |ϵͳ����----------------->(MenuID=13)                           *
			DispMenu_Root(udkey);
			break;					
									//*     +---+                                                            *
		case  MENU_COINVALUE	:	//*     |   |������ֵ------------->(MenuID=15)                           *
		case  MENU_NOTEVALUE	:	//*     |   |������ֵ------------->(MenuID=15)                           *
		case  MENU_CHANGEVALUE	:	//*     |   |������ֵ------------->(MenuID=15)                           *
		case  MENU_NOLIMITEDBUY	:	//*     |   |�ձ�����------------->(MenuID=17)                           *
		case  MENU_RETURNCOINS	:	//*     |   |�ձ�����------------->(MenuID=17)                           *
		case  MENU_OPENCOIN	:		//*     |   |����ֽ����----------->(MenuID=17)                           *
		case  MENU_OPENNOTE	:		//*     |   |����ֽ����----------->(MenuID=17)                           *
		case  MENU_OPENCHANGE	:	//*     |   |����ֽ����----------->(MenuID=17)                           *
		case  MENU_OPENREADER	:	//*     |   |����ֽ����----------->(MenuID=17)                           *
		case  MENU_READERCOST	:	//*     |   |����ֽ����----------->(MenuID=17)                           *
		case  MENU_BALANCEMIN   :	//*     |   |�������------------->(MenuID=17)                           *
		case  MENU_MONEYMAXIN	:	//*     |   |�ձ�����------------->(MenuID=17)                           *
		case  MENU_DOUBTMONEY	:	//*     |   |���ʽ��------------->(MenuID=21)                           *
		case  MENU_IOU			:	//*     |   |Ƿ����--------------->(MenuID=14)                           *
		case  MENU_CHANGESERVER	:	//*		|	|������Ƿ����----->(MenuID=16)                           *
		case  MENU_DECPOINTNUM	:   //*		|	|С����λ����--------->(MenuID=16)                           *
		case  MENU_SALECONFIRM	:   //*		|	|�ջ�ȷ��
		case  MENU_POSENABLE	:   //*		|	|����POS����------------->(MenuID=33)                   *
		case  MENU_VMCPC        :  	//*     |   |����PCͨѶ----------->(MenuID=)                             *	
		case  MENU_LARGELCD     :  	//*     |   |��Ļ���� ----------->(MenuID=)                             *	
		case  MENU_SELECTKEY    :  	//*     |   |�Ƿ�ʹ��ѡ������ ----------->(MenuID=)                             *	
		case  MENU_LOGOSEL      :  	//*     |   |�Ƿ�ʹ��logo----------->(MenuID=)                             *
		case  MENU_ADDCOLUMN    :  	//*     |   |�Ƿ��Զ�����----------->(MenuID=)                             *
		case  MENU_TENCOLUMN    :  	//*     |   |�Ƿ�ʹ��ʮ�����Ļ���----------->(MenuID=)                             *
		case  MENU_HOLDNOTE		:   //*		|	|�ݴ�     
			DispMenu_Business(udkey);
			break;					//*     |   +--------------   											 *
		case 	MENU_READEROFF		://*     |   +--------------   											 *
		case    MENU_READERMDB      ://*     |   +--------------   											 *
			DispMenu_SubReader(udkey);
			break;
		case  MENU_TRANSACTIONS	:	//*     |���׼�¼----------------->(MenuID=22)                           *
			DispMenu_Root(udkey);
			break;					//*     +---+                                                            *
		case  MENU_PAYMENTS		:	//*         |������֧------------->(MenuID=23)                           *
			DispMenu_Transactions(udkey);
			break;					
									//*         +---+                                                        *
		case  MENU_INCOME		:	//*         |   |����������------->(MenuID=24)                           *
		case  MENU_NOTEINCOME	:	//*         |   |ֽ������--------->(MenuID=25)                           *
		case  MENU_COINSINCOME	:	//*         |   |Ӳ������--------->(MenuID=26)                           *
		case  MENU_TOTALTRANS	:	//*         |   |�����ܽ��------->(MenuID=27)                           *
		case  MENU_TOTALCHANGE  :	//*         |   |�����ܽ��------->(MenuID=28)                           *
		case  MENU_COINSCHANGE1  :	//*         |   |����ö��--------->(MenuID=29)                           *
		case  MENU_COINSCHANGE2  :	//*         |   |����ö��--------->(MenuID=29)                           *
		case  MENU_COINSCHANGE3  :	//*         |   |����ö��--------->(MenuID=29)                           *
			DispMenu_Payments(udkey);
			break;	
		case  MENU_GOODS		:	//*         |��Ʒ----------------->(MenuID=30)                           *
			DispMenu_Transactions(udkey);
			break;					//*         +---+                                                        *
		
		case  MENU_SUCCESSNUM	:	//*         |   |�ɹ����״���----->(MenuID=31)                           *
		case  MENU_DOUBTNUM		:	//*         |   |���ʽ��״���----->(MenuID=32)                           *
		case  MENU_CHANNELTRANS	:	//*         |   |����������ͳ��--->(MenuID=33)                           *
			DispMenu_Goods(udkey);
			break;				
		case  MENU_TRANSINPUTNUM:
			DispMenu_TransInputChannelNo(udkey);
			break;		
		case   MENU_TRANSCHANNELNO:	//*     	|   | 	|�������--->(MenuID=35)                   		     *
		case   MENU_TRANSSUCCESS:	//*         |   | 	|�ɹ�����ͳ��--->(MenuID=36)                         *
		case   MENU_TRANMONEY:		//*         |   | 	|��Ʒ���׽��--->(MenuID=36)                         *
		case   MENU_TRANSDOUBT	:	//*         |   | 	|���ʽ���ͳ��--->(MenuID=37)                         *
			DispMenu_ChannelTrans(udkey);
			break;										//*         |   	+--------------                                      *							//*         |   +--------------                                          *
		case  MENU_CLEARTRANS	:	//*         |�����¼------------->(MenuID=34)                           *
		
			DispMenu_Transactions(udkey);
			break;					
									//*         +---+                                                        *
		case  MENU_CONFIRMATION	 :
			DispMenu_Confirmation(udkey);
			break;	

		case  MENU_PAYMENTSJIDU		:	//*         |������֧------------->(MenuID=23)                           *
			DispMenu_Transactions(udkey);
			break;					
			
									//*         +---+                                                        *
		case  MENU_INCOMEJIDU		:	//*         |   |����������------->(MenuID=24)                           *
		case  MENU_NOTEINCOMEJIDU	:	//*         |   |ֽ������--------->(MenuID=25)                           *
		case  MENU_COINSINCOMEJIDU	:	//*         |   |Ӳ������--------->(MenuID=26)                           *
		case  MENU_TOTALTRANSJIDU	:	//*         |   |�����ܽ��------->(MenuID=27)                           *
		case  MENU_TOTALCHANGEJIDU  :	//*         |   |�����ܽ��------->(MenuID=28)                           *
		case  MENU_COINSCHANGE1JIDU  :	//*         |   |����ö��--------->(MenuID=29)                           *
		case  MENU_COINSCHANGE2JIDU  :	//*         |   |����ö��--------->(MenuID=29)                           *
		case  MENU_COINSCHANGE3JIDU  :	//*         |   |����ö��--------->(MenuID=29)                           *
			DispMenu_PaymentsJidu(udkey);
			break;	
			
		case  MENU_GOODSJIDU		:	//*         |��Ʒ----------------->(MenuID=30)                           *
			DispMenu_Transactions(udkey);
			break;					//*         +---+                                                        *
		
		case  MENU_CHANNELTRANSJIDU	:	//*         |   |����������ͳ��--->(MenuID=33)                           *
			DispMenu_GoodsJidu(udkey);
			break;				
		case  MENU_TRANSINPUTNUMJIDU:
			DispMenu_TransInputChannelNoJidu(udkey);
			break;		
		case   MENU_TRANSCHANNELNOJIDU:	//*     	|   | 	|�������--->(MenuID=35)                   		     *
		case   MENU_TRANSSUCCESSJIDU:	//*         |   | 	|�ɹ�����ͳ��--->(MenuID=36)                         *
		case   MENU_TRANMONEYJIDU:		//*         |   | 	|��Ʒ���׽��--->(MenuID=36)                         *		
			DispMenu_ChannelTransJidu(udkey);
			break;										//*         |   	+--------------                                      *							//*         |   +--------------                                          *
		
		case  MENU_CLEARTRANSJIDU	:	//*         |�����¼------------->(MenuID=34)                           *
		
			DispMenu_Transactions(udkey);
			break;					
									//*         +---+                                                        *
		case  MENU_CONFIRMATIONJIDU	 :
			DispMenu_ConfirmationJidu(udkey);
			break;	
			
		case  	MENU_SYSTEM     :	//*		ϵͳ����
			DispMenu_Root(udkey);
			break;					//*     +---+           
		case  	MENU_TIMESET     :	//*		ʱ������
			DispMenu_System(udkey);
			break;					//*     +---+           
		case  	MENU_SETYEAR	:
		case  	MENU_SETMONTH	:
		case  	MENU_SETDATE	:
		case  	MENU_SETHOUR	:
		case  	MENU_SETMINUTE	:
			DispMenu_TimeSet(udkey);
			break;					//*     +---+        
		case  MENU_CGPASSWORD	:	//*     |   |�����ֻ�ģ�飺------->(MenuID=18)                           *
		case  MENU_GPRSONOFF	:	//*     |   |�����ֻ�ģ�飺------->(MenuID=18)                           *
		case  MENU_SERIALNO		:	//*     |   |�������------------->(MenuID=19)                           *
		case  MENU_GSMNO		:	//*		|	|GSM NO��------------->(MenuID=20)                           *
		case  MENU_TEMPERATURE	:	//*		|	|�¶��趨��------------->(MenuID=20)                           *
		case  MENU_SYSLANGUAGE	:	//*		|	|���Կ��ƣ�------------->(MenuID=20)                           *
		case  MENU_TEMPSET		:	//*		|	|�¿������ƣ�------------->(MenuID=20)                           *
		case  MENU_LEDSET		:	//*		|	|չʾ�ƿ��ƣ�------------->(MenuID=20)                           *
			DispMenu_System(udkey);
			break;					//*     +---+ 
		case	MENU_SYSENGLISH:
		case	MENU_SYSCHINESE:
		case	MENU_SYSRUSSIAN:	//����˹��;by gzz 20121012	
		case	MENU_SYSTURKEY :    //��������;by gzz 20121115
				DispMenu_SysLanguage(udkey);
				break;	
		case  	MENU_TEMPON	        :	//*		|	|ѹ�������ƣ�------------->(MenuID=20)                           *//���ѹ��������;by gzz 20121224
		case  	MENU_TEMPHOURSTR	:	//*		|	|�¿�����ʼʱ��------------->(MenuID=20)                           *
		case  	MENU_TEMPMINUTESTR	:	//*		|	|�¿�����ʼ�֣�------------->(MenuID=20)                           *
		case  	MENU_TEMPHOUREND	:	//*		|	|�¿�������ʱ��------------->(MenuID=20)                           *
		case  	MENU_TEMPMINUTEEND	:	//*		|	|�¿��������֣�------------->(MenuID=20)                           *	
				DispMenu_TempSet(udkey);
				break;	
		case  	MENU_LEDON	        :	//*		|	|ѹ�������ƣ�------------->(MenuID=20)                           *//���ѹ��������;by gzz 20121224
		case  	MENU_LEDHOURSTR	:	//*		|	|�¿�����ʼʱ��------------->(MenuID=20)                           *
		case  	MENU_LEDMINUTESTR	:	//*		|	|�¿�����ʼ�֣�------------->(MenuID=20)                           *
		case  	MENU_LEDHOUREND	:	//*		|	|�¿�������ʱ��------------->(MenuID=20)                           *
		case  	MENU_LEDMINUTEEND	:	//*		|	|�¿��������֣�------------->(MenuID=20)                           *	
				DispMenu_LEDSet(udkey);
				break;			
			
		case  	MENU_SETCHANNEL :	//*		���û���
			DispMenu_Root(udkey);
			break;					//*     +---+           
		case  MENU_INPUTLAYER :
			  DispMenu_InputLayerNum(udkey);
					break;	
		case  MENU_LAYERNO		:   //*     |   	|��ܱ��----------------->(MenuID=72)                   *
		case  MENU_LAYENABLE	:	//*     |   	|�Ƿ�����----------------->(MenuID=73)                   *
		case  MENU_MAXGOODS		:   //*     |   	|�������--------------->(MenuID=74)                   *
		case  MENU_CHANNEL1		:   //*     |   	|��һ����----------------->(MenuID=75)                   *
		case  MENU_CHANNELNUM1	:	//*     |   	|��һ��������----------------->(MenuID=75)                   *//������������;by gzz 20121120
		case  MENU_CHANNEL2		:   //*     |   	|�ڶ�����----------------->(MenuID=75)                   *
		case  MENU_CHANNELNUM2	:	//*     |   	|�ڶ���������----------------->(MenuID=75)                   *
		case  MENU_CHANNEL3		:   //*     |   	|��������----------------->(MenuID=75)                   *
		case  MENU_CHANNELNUM3	:	//*     |   	|������������----------------->(MenuID=75)                   *
		case  MENU_CHANNEL4		:   //*     |   	|���Ļ���----------------->(MenuID=75)                   *
		case  MENU_CHANNELNUM4	:   //*     |   	|���Ļ�������----------------->(MenuID=75)                   *
		case  MENU_CHANNEL5		:   //*     |   	|�������----------------->(MenuID=75)                   *
		case  MENU_CHANNELNUM5	:   //*     |   	|�����������----------------->(MenuID=75)                   *
		case  MENU_CHANNEL6		:   //*     |   	|��������----------------->(MenuID=75)                   *
		case  MENU_CHANNELNUM6	:   //*     |   	|������������----------------->(MenuID=75)                   *
		case  MENU_CHANNEL7		:   //*     |   	|���߻���----------------->(MenuID=75)                   *
		case  MENU_CHANNELNUM7	:   //*     |   	|���߻�������----------------->(MenuID=75)                   *
		case  MENU_CHANNEL8		:   //*     |   	|�ڰ˻���----------------->(MenuID=75)                   *
		case  MENU_CHANNELNUM8	:   //*     |   	|�ڰ˻�������----------------->(MenuID=75)                   *
		//121105 by cq TenChannels
		case  MENU_CHANNEL9 	:	//* 	|		|�ھŻ���----------------->(MenuID=75)					 *
		case  MENU_CHANNELNUM9	:   //*     |   	|�ھŻ�������----------------->(MenuID=75)                   *
		case  MENU_CHANNEL0 	:	//* 	|		|�������----------------->(MenuID=75)					 *
		case  MENU_CHANNELNUM0	:   //*     |   	|�����������----------------->(MenuID=75)                   *
			DispMenu_SetChannel(udkey);
			break;					//*     +---+           
		case  MENU_NOTEVALUE1		:
		case  MENU_NOTEVALUE2		:
		case  MENU_NOTEVALUE3		:
		case  MENU_NOTEVALUE4		:
		case  MENU_NOTEVALUE5		:
		case  MENU_NOTEVALUE6		:
		case  MENU_NOTEVALUE7		:
		case  MENU_NOTEVALUE8		:
			 DispMenu_NoteValue(udkey);
			break;					//*     +---+           
		case  MENU_COINVALUE1		:
		case  MENU_COINVALUE2		:
		case  MENU_COINVALUE3		:
		case  MENU_COINVALUE4		:
		case  MENU_COINVALUE5		:
		case  MENU_COINVALUE6		:
		case  MENU_COINVALUE7		:
		case  MENU_COINVALUE8		:
			 DispMenu_CoinValue(udkey);
			break;					//*     +---+         
		case  MENU_CHANGEVALUE1		:
		case  MENU_CHANGEVALUE2		:
		case  MENU_CHANGEVALUE3		:
			DispMenu_ChangeValue(udkey);
			break;					//*     +---+    
		case  	MENU_DEFAULTSET :	//*		Ĭ������
			DispMenu_Root(udkey);
			break;					//*     +---+        
		case  MENU_CONFIRMSET	 :
			DispMenu_SetConfirmation(udkey);
			break;				
		//case  	MENU_SYNGOODSCOL :	//*		ȫϵͳͬ��
		//case  	MENU_ADDCOIN :	    //*		��Ӳ�����
		//case  	MENU_ADDBILL :	    //*		ȡֽ�����
		//	DispMenu_Root(udkey);
		//	break;					//*     +---+      	
		case  MENU_SUBALLCHANNELSTAT :
			DispMenu_SubCHStat(udkey);
			break;
		case  MENU_SUBCHTESTRESULT :
			DispMenu_SubCHResult(udkey);
			break;
		case 	MENU_SELECTGBA		:
		case 	MENU_SELECTMEI		:
		case    MENU_SELECTITL      :	
		case 	MENU_SELECTCLOSE	:			
			DispMenu_SubNOTE(udkey);
			break;	
		case 	MENU_HOLDNOTE5		:
		case 	MENU_HOLDNOTE10		:
		case 	MENU_HOLDNOTE20		:
			DispMenu_Business(udkey);
			//	DispMenu_HoldNote(udkey);
			break;	
		
		default:
				break;
	}

}









