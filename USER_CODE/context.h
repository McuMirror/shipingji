/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           context.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        ������ʾ�˵�����
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
#ifndef __CONTEXT_H
#define __CONTEXT_H

#if DISP_MODE == LCD_DISPLAY



const char  *Disp_Init[4][1] =	 
{
   {
      "�豸��ʼ����.."
   },
   {
      "Initializing.."
   },
   //change by liya 2012-10-16
   {
   	  "���ߧڧ�ڧѧݧڧ٧ѧ�ڧ�..."
   },
   //��������;by gzz 20121115
   {
   	  "Cihaz ba\xf1\x5flatma"
   }
};

const char  *Disp_Fault[4][20] =
{
   {
	  "��Ǹ��������ͣ����",   
	  "������:	",
	  "��Ʒ������",
	  "����������",
	  "ֽ��������",
	  "Ӳ��������",
	  "�ұ���ȱ��",
	  "���л����޻�",
	  "���л�������",
	  "���������",
	  "����������",
	  "ϵͳ��������",
	  "LCD ����",
	  "���������쳣",
	  "����ȷ�Ϲ���",
	  "Flash����",
	  "ʱ�ӹ���",
	  "ȡ����������",
	  "������û��",
	  "��Ǹ"
	  
   },
   {	
	  "Out of Service!",
	  "Err Code: ",
	  "Channel err",
	  "Hopper is wrong",
	  "bill err",
	  "coin err",
	  "hopper empty",
	  "column empty",
	  "column err",
	  "column err",
	  "column err",
	  "system err",
	  "LCD err",
	  "price err",
	  "GOC err",
	  "Flash err",
	  "RTC err",
	  "FGP err",
	  "Door Open",
	  "Sorry"
   },
   //change by liya 2012-10-16
   {
	  "���� ��ѧҧ��ѧ֧�",
	  "����� ���ڧҧܧ�:",
	  "����ڧҧܧ� �ܧѧߧѧݧ�",
	  "������֧� ",
	  "���ڧݧ� ",
	  "����ߧ֧��",
	  "���������ӧڧ� �ӧѧݧ���",
	  "����էѧߧߧ��",
	  "�ߧ֧ڧ���ѧӧߧ����",
	  "�ߧ֧ڧ���ѧӧߧ����",
	  "�ߧ֧ڧ���ѧӧߧ����",
	  "��ѧ�ѧާ֧��� ��ڧ��֧ާ�",
	  "LCD",
	  "���֧ߧ� �ߧ֧��ѧӧڧݧ�ߧ�",
	  "GOC",
	  "Flash",
	  "RTC",
	  "FGP",
	  "�էӧ֧�� �ܧ�ߧ�֧ۧߧ֧��",
	  "�ڧ٧ӧڧߧڧ��"
   },
   //��������;by gzz 20121115
   {
	  "Servis d\xf1\x31\xf1\x5f\xf1\x31",   
	  "Hata kodu:  ",
	  "\xf0\xdcr\xf0\xfcn sat\xf1\x31ld\xf1\x31",
	  "De\xf1\x1fi\xf1\x5fikli\xf1\x1fi hatas\xf1\x31 tutun",
	  "Bill yetmezli\xf1\x1fi",
	  "Coin hatas\xf1\x31",
	  "Paralar eksik sikke bul",
	  "T\xf0\xfcm g\xf0\xF6nderiler hi\xf0\xe7bir mal road",
	  "T\xf0\xfcm Kargo Karayolu fay",
	  "Kargo Karayolu kart\xf1\x31 ar\xf1\x31zas\xf1\x31",
	  "Kargo Karayolu kullan\xf1\x31lam\xf1\x31yor",
	  "Sistem parametreleri ar\xf1\x31zas\xf1\x31",
	  "LCD ar\xf1\x31za",
	  "Fiyat anormal",
	  "GOC ar\xf1\x31za",
	  "Flash ar\xf1\x31za",
	  "RTC ar\xf1\x31za",
	  "FGP ar\xf1\x31za",
	  "Kap\xf1\x31 kapal\xf1\x31 de\xf1\x1fil Pick",
	  "\xf0\xfczg\xf0\xfcn\xf0\xfcm"
   }
};


const char  *Disp_Main[4][2] =	 
{
   {
      "        �ֽ�����",
	  "  Ͷ��->ѡ��->ȡ��"
   },
   {
      "     Cash trade",
	  " Money->Sel->Goods"
   },
   //change by liya	2012-10-16
   {
   	  "����ԧ�ӧݧ� �٧� �ߧѧݧڧ�ߧ��",
	  "���֧ߧ�ԧ�->�����էѧا�->���է�"
   },
   //��������;by gzz 20121115
   {
   		"Nakitsiz al\xf1\x31m",
		"Para->\xf0\xfcr\xf0\xfcn sec ->Al"
   }
};	

//120914 by cq Cashless
const char  *Disp_Main_2[4][2] =	 
{
   {
      "      �忨����",
	  "  �忨->ѡ��->ȡ��"
   },
   {
      "   Cashless trade",
	  "  Card->Sel->Goods"
  },
  //change by liya 2012-10-16
  {
	 "����ԧ�ӧݧ� �٧� �ߧѧݧڧ�ߧ��",
	 "���֧ߧ�ԧ�->�����էѧا�->���է�"
  },
  //��������;by gzz 20121115
  {
      "      Kart t\xf0\xfcketimi",
	  "kart->\xf0\xfcr\xf0\xfcn sec ->Al"
   } 
};	


const char  *Disp_Input[4][7] =
{
   {
      "        ��ӭ����",
	  "  Ͷ��->ѡ��->ȡ��",
	  "  Ͷ��->ѡ��->ȡ��",
	  "  Ͷ��->ѡ��->ȡ��",
	  //"�����㣬������ͶӲ��",//121106 by cq BillSingleWork
	  "  Ͷ��->ѡ��->ȡ��",//121106 by cq BillSingleWork
	  //"		 Ӳ�Ҳ���",
	  "  Ͷ��->ѡ��->ȡ��",//121106 by cq BillSingleWork
	  "������Ʒ���ȷ�Ϲ���"
   },
   {
      "      Welcome",
	  " Money->Sel->Goods",
	  " Money->Sel->Goods",
	  " Money->Sel->Goods",
	  " Money->Sel->Goods",
	  " Money->Sel->Goods",
	  "Input Column No."
   },
   //change by liya	2012-10-16
   {
   	  "����ҧ�� ���اѧݧ�ӧѧ��",
	  "�����ѧӧ��:�ܧ�����/�ާ�ߧ֧��",
	  "�����ѧӧ��:�ܧ�����",
	  "�����ѧӧ��:�ާ�ߧ֧��",
	  "���� �էѧӧѧ�� �ڧ٧ާ֧ߧ֧ߧڧ�,�����ѧӧ�֧ާ�ߧ֧��",
	  "���էѧ�� �ߧ֧է���ѧ���ߧ����",
	  "���ӧ֧էڧ�� �ߧ�ާ֧� ����է�ܧ��"
   },
   //��������;by gzz 20121115
   {
      "        kar\xf1\x5f\xf1\x31lama",
	  "  Notlar veya paralar: giri\xf1\x5fL\xf0\xfctfen",
	  "    Kagit para gir",
	  "    Madeni para gir",
	  //"�����㣬������ͶӲ��",//121106 by cq BillSingleWork
	  "De\xf1\x1fi\xf1\x5fim gerekebilir",//121106 by cq BillSingleWork
	  //"		 Ӳ�Ҳ���",
	  "S\xf1\x31f\xf1\x31r paralar ya da ba\xf1\x5far\xf1\x31s\xf1\x31zl\xf1\x31k i\xf0\xe7in de\xf1\x1fi\xf1\x5fiklik",//121106 by cq BillSingleWork
	  "\xf0\xdcr\xf0\xfcn Kodu sat\xf1\x31n onaylay\xf1\x31n Gir"
   }
};

const char  *Disp_ChInput[4][4] =
{
   {
      "������Ʒ��ţ�",
	  "�������",
	  "������������Ʒ���",
	  "��ѡ�������Ͷ��!"
   },
   {
      "Input Item code:",
	  "Invalid choice",
	  "Input other code",
	  "Make Selection!"
   },
   //change by liya 2012-10-16
   {
      "���ӧ֧էڧ�� �ܧ�� ���٧ڧ�ڧ�:",
	  "���֧��ѧӧڧݧ�ߧ�� �ӧ�ҧ��",
	  "���ӧ֧էڧ�� �է��ԧ�� �ܧ��",
	  "���է֧ݧѧۧ�� �ӧ�ҧ��!"	
   },
   //��������;by gzz 20121115
   {
      "\xf0\xdcr\xf0\xfcn kodunu giriniz:",
	  "Giri\xf1\x5f hatalar\xf1\x31",
	  "Farkl\xf1\x31 bir \xf0\xfcr\xf0\xfcn numaras\xf1\x31 giriniz",
	  "Mal se\xf0\xe7mek veya jeton devam edin!"
   }
};		

const char  *Disp_ChnPara[4][2] =
{
   {
      "����  ",
	  "���ۣ�"
   },
   {
      "Channel ",
	  "Price: "
   },
   //change by liya	2012-10-16
   {
   	  "���ѧߧѧ�",
	  "���֧ߧ�"
   },
   //��������;by gzz 20121115
   {
      "S\xf0\xfctun  ",
	  "Fiyat:"
   }
};

const char  *Disp_ChnState[4][4] =
{
   {
      " -- ����",
	  " -- �л�",
	  " -- ����",
	  " -- ȱ��"
   },
   {
      "-Disable",
	  "-OK",
	  "-Error",
	  "-Out"
   },
   //change by liya	2012-10-16
   {
      "-����ܧݧ��֧ߧ�",
	  "-OK",
	  "-����ڧҧܧ�",
	  "-����էѧ��"
   },
   //��������;by gzz 20121115
   {
      " -- Disable",
	  " -- OK",
	  " -- Hatal\xf1\x31",
	  " -- Bitti"
   }
};

//�޸Ľ�����ʾ;by gzz 20121009
const char  *Disp_Deal[4][13] =
{
   {
	  "���",
	  "���㣬",
	  "��Ҫ������Ʒ��",
	  "��Ʒ������",
	  "������С���ֽ��",
	  "�ͻ����",
	  "    ��ȷ��������",
	  "    �����ؼ��˱�",	  
	  " ��",
	  "���",
	  "�밴��ѡ��",
	  "����ѡ��",
	  "�����˱�"
   },
   {
	  "Balance:",
	  "Insufficient fund",
	  "Buy another one?",
	  "   Soldout",
	  "Insert a smaller one",
	  "Price paid:",
	  "Enter OutGood",
	  "Cancel Payout",	  
	  "  ��",
	  "Amount:",
	  "Please Select by Button",
	  "Continue",
	  "Coin Refund"
   },
   //change by liya 2012-10-16
   {
	  "���ѧݧѧߧ�:",
	  "���ѧۧէ֧ߧ� �ߧ֧�����.?",
	  "�����ڧ�� �֧��?",
	  "�����էѧߧ�",
	  "�����ѧӧ��� ���ާ֧ߧ���",
	  "���֧ߧ� ���ݧѧ�֧ߧ�:",
	  "ENTER   ���է���է��ӧ�",
	  "CANCEL  �ӧ�٧ӧ�ѧ�ѧ��",	  
	  "  ",
	  "���ѧݧѧߧ�:",
	  "����اѧݧ�ۧ���, �ߧѧاާڧ�� �ܧ��ڧ��",
	  "����է�ݧاѧ��",
	  "CASHOUT"	  
   },
   //��������;by gzz 20121115
   {
	  "Bakiye: ",
	  "Yetersiz fon?",
	  "Ba\xf1\x5fka bier \xf1\x5fey almak inter misiniz?",
	  "   Urun yok",
	  "Kucuk banknot girin",
	  "Bakiye:",
	  "nakliye",
	  "\xf0\xF6deme alma",	  
	  "  ",
	  "Bakiye: ",
	  "\xf0\xdcr\xf0\xfcn kodunu giriniz",
	  "Yeni \xf0\xfcr\xf0\xfcn",
	  "Para iade"
   }
};





const char  *Disp_GoodsOut[4][2] =
{
   {
      "���ڳ���..",
	  "ѡ���ɹ�, ��ȡ��"
   },
   {
      "Taking the goods",
	  "Please Take the Item"
   },
   //change by liya	 2012-10-16
   {
      "���ѧ�ӧѧ� �֧է�",
	  "���ѧҧ֧�ڧ�� �֧է�"
   },
   //��������;by gzz 20121115
   {
      "\xf0\xdcr\xf0\xfcn veriliyor ,bekleyiniz",
	  "\xf0\xfcr\xf0\xfcn\xf0\xfc alabilirsiniz.."
   }
};

const char  *Disp_Change[4][7] =
{
   {
      "���˱�",
	  "��������",
	  "    ��Ǯ����",
	  "Ƿ��: ",
	  "    ��������..",
	  "���µ�ͷ�����",
	  "�����˿�"
   },
   {
      "Pls Get the Change",
	  "Change",
	  "Not enough coins",
	  "IOU: ",
	  "Changing",
	  "Change failure",
	  "Refund of fare"
   },
   //change by liya	2012-10-16
   {
      "���ѧҧ�� �ާ�ߧ֧�",
	  "���ѧާ֧ߧ�:",
	  "���֧է���ѧ���ߧ� �ާ�ߧ֧�",
	  "�� �է�ݧ֧� ���ѧ�: ",
	  "���ѧާ֧ߧ�",
	  "���ѧާ֧ߧ� �ߧ� ���ݧ��ڧݧѧ��",
	  "���֧�֧���֧է֧ݧڧ�� ��ڧ��"
   },
   //��������;by gzz 20121115
   {
      "\xf0\xfcr\xf0\xfcn\xf0\xfc de\xf1\x1fi\xf1\x5ftirebilirsiniz",
	  "De\xf1\x1fi\xf1\x5fim:",
	  "s\xf1\x31k\xf1\x31nt\xf1\x31s\xf1\x31 de\xf1\x1fi\xf1\x5ftirin",
	  "Bor\xf0\xe7 makbuzu: ",
	  "de\xf1\x1fi\xf1\x5ftirebilirsiniz..",
	  "de\xf1\x1fi\xf1\x5fikli\xf1\x1fi ba\xf1\x5far\xf1\x31s\xf1\x31z tutun",
	  "de\xf1\x1fi\xf1\x5ftirebilirsiniz"
   }
};

const char  *Disp_Wait[4][1] =	 
{
   {
	  "���Ժ�.."
   },
   {
	  "Please wait.."
   },
   //change by liya	2012-10-16
   {
   	  "����اѧݧ�ۧ��� ���է�اէڧ��..."
   },
   //��������;by gzz 20121115
   {
	  "L\xf0\xfctfen bekleyin.."
   }
};

const char  *Disp_Timeout[4][1] =	 
{
   {
	  "      ������ʱ"
   },
   {
	  " Operation timeout"
   },
   //change by liya	2012-10-16
   {
   	  "����֧ާ� �ڧ��֧ܧݧ�"
   },
   //��������;by gzz 20121115
   {
	  "      Zaman A\xf1\x5f\xf1\x31m\xf1\x31"
   }
};

const char  *Disp_End[4][3] =
{
    {
	    "        лл",
		"    Ʒζ��;���ղؼ���",
		"        лл�ݹ�!"
	},
	{
	    "Thank You",
		" Thank you",
		"    Thank you"
	},
	//change by liya  2012-10-16
	{
		"����ѧ�ڧҧ�",
		"����ѧ�ڧҧ�",
		"����ѧ�ڧҧ�"
	},
    //��������;by gzz 20121115
    {
	    "Te\xf1\x5fekk\xf0\xfcrler",
		"Te\xf1\x5fekk\xf0\xfcrler",
		"    Te\xf1\x5f\ekk\xf0\xfcrler"
	}
};



//�޸����������������Ϣ;by gzz 20121016
const char  *Disp_Confirm[4][4] =
{
    {
	    "ȷ��ENTER ����CANCEL",
		"          ����CANCEL",
		"�밴ȷ�������� ENTER",
		"�밴���ؼ��޸�CANCEL"
	},
	{
	    "  ENTER     CANCEL",
		"            CANCEL",
		"  ENTER     outgood",
		"  CANCEL    back"
	},
	//change by liya 2012-10-16
	{
	    "���ӧ֧էڧ��     �ܧѧߧѧ�",
		"          �������",
		"ENTER   ���է���է��ӧ�",
		"CANCEL  �ӧ�٧ӧ�ѧ�ѧ��"
	},
    //��������;by gzz 20121115
    {
	    "  ENTER     CANCEL",
		"            CANCEL",
		"  ENTER     nakliye",
		"  CANCEL    de\xf1\x1fi\xf1\x5ftirmek"
	}
};

const char  *Disp_Blank = "";
/*
const uint8_t Disp_Bmp[640] = 
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xC0,0x02,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0x00,0x18,0x40,0x02,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xE1,0x00,0x31,0xC0,0x02,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x81,0x00,0x2F,0x00,0x02,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x03,0x03,0x00,0x78,0x00,0x02,0x00,0x0F,0xFF,0xFF,0xE0,0x00,0x03,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x02,0x06,0x03,0xC0,0x00,0x06,0x01,0xF8,0x08,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0xBC,0xC0,0x00,0x04,0x7E,0x00,0x08,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x18,0x80,0x86,0x00,0x0F,0xC0,0x00,0x0F,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x81,0x83,0x00,0x74,0x00,0x00,0x1D,0x01,0x00,0x03,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x81,0x01,0x03,0xC4,0x70,0x00,0x32,0x0F,0x00,0x06,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x18,0x81,0x01,0xFC,0x04,0xD0,0x08,0x76,0x78,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x18,0x81,0x1E,0x80,0x0D,0x90,0x08,0x79,0xC0,0x00,0x70,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x18,0x81,0x30,0x80,0x09,0x10,0x08,0x7E,0x80,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x15,0x01,0x60,0x80,0x0B,0x10,0x18,0x79,0xC0,0x03,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x17,0x01,0xC0,0x80,0x0A,0x10,0x10,0x73,0x40,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x01,0x00,0x80,0x14,0x10,0x10,0x76,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x01,0x00,0x80,0x14,0x10,0x11,0x9C,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x00,0x00,0xF0,0x1E,0x10,0x31,0x18,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x30,0x00,0x80,0x90,0x1F,0x10,0x30,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x00,0x80,0x90,0x1D,0x90,0x30,0x17,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x00,0x80,0x80,0x34,0xD0,0x30,0x1D,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x01,0x8C,0x80,0x34,0x60,0x38,0x12,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x01,0x07,0x00,0x24,0x70,0x08,0x17,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x00,0x03,0x00,0x26,0xCC,0x00,0x30,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x00,0x06,0x00,0x23,0x82,0x00,0x20,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x60,0x00,0x06,0x00,0x20,0x01,0xD8,0x63,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x38,0x61,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};*/

#endif

#endif
