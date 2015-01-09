#ifndef __MENU_H 
#define __MENU_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

void menu(void);
#define		 KEYTEST 1
#define		 KEYLOOP 2





	//�洢��־
//
#define S_S   	0x80//��      =1000,0000=0x80,
#define S_X   	0x40//��      =0100,0000=0x40,
#define S_Z  	0x20//��      =0010,0000=0x20,
#define S_Y  	0x10//��      =0001,0000=0x10,
#define S_ZS  	0xa0//����    =1010,0000=0xa0,
#define S_ZX  	0x60//����    =0110,0000=0x60,
#define S_YS  	0x90//����    =1001,0000=0x90,
#define S_YX  	0x50//����    =0101,0000=0x50,
#define S_SXZY  0xf0//��������=1111,0000=0xf0
  








//




									//
									//************************************************************************
									//* Menu Struct:                                                         *
									//************************************************************************
#define  MENU_PASSWORD			0	//* First Bmp--------------------->(MenuID=0)                            *
									//*  ---+                                                                *
#define  MENU_CHANNEL			1	//*     |��������----------------->(MenuID=1)                            *
									//*     +---+                                                            *
#define  MENU_INPUTNUM			2	//*     |   |��������----------->(MenuID=2)                            *
									//*     |   +--------------                                              *
#define  MENU_CHANNELNO			3	//*     |   	|������----------------->(MenuID=3)                      *
									//*     |   +--------------                                              *
#define  MENU_PRICE				4	//*     |   	|����------------------->(MenuID=4)                      *
									//*     |   +--------------                                              *
#define  MENU_CHANNELLEFT		5	//*     |   	|�������--------------->(MenuID=5)                      *
									//*     |   +--------------                                              *									
#define  MENU_CHANNELSTAT		6	//*     |   	|����״̬--------------->(MenuID=6)                      *
									//*     |   +--------------                                              *
#define  MENU_CHANNELGOODS		7	//*     |   	|��Ʒ���--------------->(MenuID=7)                      *
									//*     |   +--------------                                              *									
#define  MENU_ADDGOODS 			8   //*		|���--------------------->(MenuID=7)                            *
									//*     +---+                                                            *
#define  MENU_ADDINPUTLAY		9	//*     |   |��������----------->(MenuID=8)                        *
									//*     |   +--------------                                              *
#define  MENU_INPUTADDGOODS		10	//*     |   	|��ȷ��Ҫ�����----------->(MenuID=8)                        *
									//*     |   	+--------------                                              *
#define  MENU_DRIVER			11	//*     |�豸����----------------->(MenuID=9)                            *
									//*     +---+                                                            *
#define  MENU_NOTESTAT			12	//*     |   |ֽ����״̬------------->(MenuID=10)                         *
									//*     |   +--------------                                              *
#define  MENU_COINSSTAT			13	//*     |   |Ӳ����״̬------------->(MenuID=11)                         *
									//*     |   +--------------                                              *
#define  MENU_HOPPERSTAT1		14	//*     |   |#1������״̬----------->(MenuID=12)                         *
									//*     |   +--------------                                              *
#define  MENU_HOPPERSTAT2		15	//*     |   |#2������״̬----------->(MenuID=13)                         *
									//*     |   +--------------                                              *
#define  MENU_HOPPERSTAT3		16	//*     |   |#3������״̬----------->(MenuID=14)                         *
									//*     |   +--------------                                              *
#define  MENU_GPRSTEST			17	//*     |   |�ֻ�ģ��״̬����------->(MenuID=20)                         *
									//*     |   +--------------                                              *
#define  MENU_SMSTEST			18	//*     |   |����Ϣ���------------->(MenuID=21)                         *
									//*     |   +--------------                                              *
#define  MENU_KEYTEST			19	//*     |   |��ť���--------------->(MenuID=15)                         *
									//*     |   +--------------                                              *
#define  MENU_DOKEYTEST			20	//*     |   |	|��ť��⶯��--------->(MenuID=16)                       *
									//*     |   +--------------                                              *
#define  MENU_ALLCHANNELSTAT 	21	//*     |   |����״̬--------------->(MenuID=17)                         *
									//*     |   +--------------                                              *
#define  MENU_CHANNELTEST		22	//*     |   |�������--------------->(MenuID=18)                         *
									//*     |   +--------------                                              *
#define  MENU_DRINPUTNUM		23  //*     |   	|��������----------->(MenuID=19)                       *
									//*     |   +--------------                                              *
#define  MENU_CHTESTRESULT		24	//*     |   |�������Խ��------->(MenuID=20)                         *
									//*     |   +--------------                                              *
//#define  MENU_TRANSINPUTNUM		56	//*     |	|   |��������---------->(MenuID=48)                    *
									//*     |	|   +--------------                                      *
//#define  MENU_TRANSCHANNELNO 	57	//*     |   | 		|�������-------->(MenuID=49)          		     *
									//*     |   |   |	+--------------                                  *
//#define  MENU_TRANSSUCCESS		58	//*     |   |   | 	|������������---->(MenuID=50)                    *
									//*     |   |   |	+--------------                                  *
//#define  MENU_TRANSDOUBT		59	//*     |   |   | 	|�������ϴ���---->(MenuID=51)                    *
									//*     |   |   |	+--------------                                  *
//#define  MENU_TRANSDOUBT		59	//*     |   |   | 	|�����޻�����---->(MenuID=51)                    *
									//*     |   |   |	+--------------                                  *
#define  MENU_IRTEST			25	//*     |   |����ȷ�ϲ���------->(MenuID=20)                         *
									//*     |   +--------------                                              *
#define  MENU_LCDTEST			26	//*     |   |LCD����------->(MenuID=20)                         *
                                    //*     |   +--------------                                              *
#define  MENU_DOLCDTEST			27	//*     |       |LCD���Բ���------->(MenuID=20)                         *
									//* 	|	+--------------
#define  MENU_TEMPRATURETEST	28	//*     |   |�¿�������------->(MenuID=20)                         *
									//* 	|	+--------------									
#define  MENU_DOTEMPTEST		29	//*     |       |�¿������Բ���------->(MenuID=20)                         *
									//* 	|	+--------------	
#define  MENU_SELECTKEYTEST		30	//*     |   |ѡ����������------->(MenuID=20)                         *
									//* 	|	+--------------									
#define  MENU_DOSELECTKEYTEST	31	//*     |       |ѡ���������Բ���------->(MenuID=20)                         *									
									//*     |   +--------------                                              *	
#define  MENU_TEMPSTEST			32	//*     |   |ѹ��������------->(MenuID=20)                         *//���ѹ��������;by gzz 20121224
                                    //*     |   +--------------                                              *//���ѹ��������;by gzz 20121224
#define  MENU_DOTEMPSTEST		33	//*     |       |ѹ�������Բ���------->(MenuID=20)                         *
									//* 	|	+--------------
#define  MENU_LEDTEST			34	//*     |   |չʾ�Ʋ���------->(MenuID=20)                         *//���չʾ�ƿ���;by gzz 20121229
                                    //*     |   +--------------                                              *//���չʾ�ƿ���;by gzz 20121229
#define  MENU_DOLEDTEST			35	//*     |       |չʾ�Ʋ��Բ���------->(MenuID=20)                         *									
									//*     |   +--------------                                              *									
#define  MENU_FLASHLEFT			36	//*     |   |FLASH�洢ʣ��ռ�------------->(MenuID=52)                           *
									//*     |   +---+                                                        *
#define  MENU_BUSINESS			37	//*     |ҵ�����----------------->(MenuID=22)                           *
									//*     +---+                                                            *
#define  MENU_COINVALUE			38	//*     |   |Ӳ������ֵ��--------------->(MenuID=23)                   *
									//*     |   +--------------                                              *
#define  MENU_NOTEVALUE			39	//*     |   |ֽ������ֵ��--------------->(MenuID=24)                   *
									//*     |   +--------------                                              *
#define  MENU_CHANGEVALUE		40	//*     |   |��������ֵ��--------------->(MenuID=25)                   *
									//*     |   +--------------                                              *
#define  MENU_OPENCOIN			41	//*		|	|����Ӳ������----------------->(MenuID=28)                   *
									//*     |   +--------------                                              *
#define  MENU_OPENNOTE			42	//*		|	|ֽ�������ͣ�----------------->(MenuID=28)                   *
									//*     |   +--------------                                              *
#define  MENU_OPENCHANGE		43	//*		|	|������������----------------->(MenuID=28)                   *
									//*     |   +--------------                                              *
#define  MENU_OPENREADER		44	//*		|	|���������ͣ�----------------->(MenuID=28)                   *
									//*     |   +--------------                                              *
#define  MENU_READEROFF			45	//*     |       |�رն�����------->(MenuID=20)                         *									
									//*     |   +--------------    
#define  MENU_READERMDB			46	//*     |       |MDB������------->(MenuID=20)                         *									
									//*     |   +--------------  
#define  MENU_READERCOST		47	//*		|	|�������Ƿ������ۿ�----------------->(MenuID=28)                   *
									//*     |   +-------------- 									
#define  MENU_CHANGESERVER		48	//*		|	|������Ƿ����------------->(MenuID=33)                   *	
									//*     |   +--------------   											 *
#define  MENU_NOLIMITEDBUY		49	//*     |   |�����ι���----------------->(MenuID=26)                   *
									//*     |   +--------------                                              *
#define  MENU_RETURNCOINS		50	//*		|	|������˱ң�----------------->(MenuID=27)                   *
									//*     |   +--------------                                              *
#define  MENU_BALANCEMIN		51	//*     |   |�������--------------------->(MenuID=29)                   *
									//*     |   +--------------   											 *
#define  MENU_MONEYMAXIN		52	//*     |   |�ձ�����--------------------->(MenuID=30)                   *
									//*     |   +--------------   											 *
#define  MENU_IOU				53	//*     |   |Ƿ����----------------------->(MenuID=32)                   *
									//*     |   +--------------                                              *
#define  MENU_DOUBTMONEY		54	//*     |   |���ʽ��--------------------->(MenuID=31)                   *
									//*     |   +--------------                                              *
#define  MENU_DECPOINTNUM		55	//*		|	|С����λ����------------->(MenuID=33)                   *
									//*     |   +--------------                                              *
#define  MENU_SALECONFIRM		56	//*		|	|�ջ�ȷ�ϣ�------------->(MenuID=33)                   *
									//*     |   +--------------                                              *
#define  MENU_POSENABLE			57	//*		|	|����POS����------------->(MenuID=33)                   *
									//*     |   +--------------                                              *
#define  MENU_VMCPC             58  //*     |	ʹ��pcͨѶ--------------->(MenuID=)                         *
                                    //*     |   +--------------                                              *
#define  MENU_LARGELCD          59  //*     |	��Ļ���� --------------->(MenuID=)                         *	
                                    //*     |   +--------------                                              *
#define  MENU_SELECTKEY         60  //*     |	ʹ��ѡ������ģʽ--------------->(MenuID=)                         *	
                                    //*     |   +--------------                                              *   
#define  MENU_LOGOSEL           61  //*     |	ʹ��Logo--------����------->(MenuID=)                         *	//ƴͼ��Ļ��ʽ;by gzz 20121106
                                    //*     |   +--------------                                              *  
#define  MENU_ADDCOLUMN         62  //*     |	�Զ�����--------����------->(MenuID=)                         *	//�����ֹ���������;by gzz 20130122
                                    //*     |   +--------------                                              *   
#define  MENU_TENCOLUMN         63  //*     |	�Ƿ�ʹ��ʮ�����Ļ���--------����------->(MenuID=)              *	//�Ƿ�ʹ��ʮ�����Ļ���;by gzz 20130226
                                    //*     |   +--------------                                              *                                     
#define  MENU_HOLDNOTE			64	//*		|	|�Ƿ����ݴ棺------------->(MenuID=33)                   *
									//*     |   +--------------                                              *
#define  MENU_HOLDNOTE5 		65	//*     |	5Ԫֽ���ݴ�--------------->(MenuID=17)                         *
									//*     |   +--------------                                              *
#define  MENU_HOLDNOTE10 		66	//*     |	10Ԫֽ���ݴ�--------------->(MenuID=17)                         *
									//*     |   +--------------                                              *
#define  MENU_HOLDNOTE20 		67	//*     |	20Ԫֽ���ݴ�--------------->(MenuID=17)                         *
                                    //*     |	+--------------                                              *
									//*     |   +--------------                                              *
#define  MENU_TRANSACTIONS		68	//*     |���׼�¼----------------->(MenuID=34)                           *
									//*     +---+                                                            *
#define  MENU_PAYMENTS			69	//*     |   |�ճ�������֧------------->(MenuID=35)                           *
									//*     |   +---+                                                        *
#define  MENU_INCOME			70	//*     |   |   |����������--------->(MenuID=36)                         *
									//*     |   |   +--------------                                          *
#define  MENU_NOTEINCOME		71	//*     |   |   |ֽ������----------->(MenuID=37)                         *
									//*     |   |   +--------------                                          *
#define  MENU_COINSINCOME		72	//*     |   |   |Ӳ������----------->(MenuID=38)                         *
									//*     |   |   +--------------                                          *
#define  MENU_TOTALTRANS		73	//*     |   |   |�����ܽ��--------->(MenuID=39)                         *
									//*     |   |   +--------------                                          *
#define  MENU_TOTALCHANGE		74  //*     |   |   |�����ܽ��--------->(MenuID=40)                         *
									//*     |   |   +--------------                                          *
#define  MENU_COINSCHANGE1		75	//*     |   |   |#1����ö��--------->(MenuID=41)                         *
									//*     |   |   +--------------                                          *
#define  MENU_COINSCHANGE2		76	//*     |   |   |#2����ö��--------->(MenuID=42)                         *
									//*     |   |   +--------------                                          *
#define  MENU_COINSCHANGE3		77	//*     |   |   |#3����ö��--------->(MenuID=43)                         *
									//*     |   |   +--------------                                          *
#define  MENU_GOODS				78	//*     |   |�ճ���Ʒ��¼----------------->(MenuID=44)                           *
									//*     |   +---+                                                        *
#define  MENU_SUCCESSNUM		79	//*     |   |   |�ɹ����״���----->(MenuID=45)                           *
									//*     |   |   +--------------                                          *
#define  MENU_DOUBTNUM			80	//*     |   |   |���ʽ��״���----->(MenuID=46)                           *
									//*     |   |   +--------------                                          *
#define  MENU_CHANNELTRANS		81	//*     |   |   |����������ͳ��--->(MenuID=47)                           *
									//*     |   |   +--------------                                          *
#define  MENU_TRANSINPUTNUM		82	//*     |	|   	|��������---------->(MenuID=48)                    *
									//*     |	|   	+--------------                                      *
#define  MENU_TRANSCHANNELNO 	83	//*     |   | 			|�������-------->(MenuID=49)          		     *
									//*     |   |   |		+--------------                                  *
#define  MENU_TRANSSUCCESS		84	//*     |   |   | 		|�ɹ�����ͳ��---->(MenuID=50)                    *
									//*     |   |   |		+--------------                                  *
#define  MENU_TRANMONEY			85	//*     |   |   | 		|��Ʒ���ͳ��---->(MenuID=50)                    *
									//*     |   |   |		+--------------                                  *									
#define  MENU_TRANSDOUBT		86	//*     |   |   | 		|���ʽ���ͳ��---->(MenuID=51)                    *
									//*     |   |   |		+--------------                                  *
#define  MENU_CLEARTRANS		87	//*     |   |����ճ���¼------------->(MenuID=52)                           *
									//*     |   +---+                                                        *
#define  MENU_CONFIRMATION		88	//*     |   |   |��ȷ����------->(MenuID=53)                           *
									//*     |   |   +--------------                                          *
#define  MENU_PAYMENTSJIDU		89	//*     |   |���Ȼ�����֧------------->(MenuID=35)                           *
									//*     |   +---+                                                        *
#define  MENU_INCOMEJIDU		90	//*     |   |   |����������--------->(MenuID=36)                         *
									//*     |   |   +--------------                                          *
#define  MENU_NOTEINCOMEJIDU	91	//*     |   |   |ֽ������----------->(MenuID=37)                         *
									//*     |   |   +--------------                                          *
#define  MENU_COINSINCOMEJIDU	92	//*     |   |   |Ӳ������----------->(MenuID=38)                         *
									//*     |   |   +--------------                                          *
#define  MENU_TOTALTRANSJIDU	93	//*     |   |   |�����ܽ��--------->(MenuID=39)                         *
									//*     |   |   +--------------                                          *
#define  MENU_TOTALCHANGEJIDU	94  //*     |   |   |�����ܽ��--------->(MenuID=40)                         *
									//*     |   |   +--------------                                          *
#define  MENU_COINSCHANGE1JIDU	95	//*     |   |   |#1����ö��--------->(MenuID=41)                         *
									//*     |   |   +--------------                                          *
#define  MENU_COINSCHANGE2JIDU	96	//*     |   |   |#2����ö��--------->(MenuID=42)                         *
									//*     |   |   +--------------                                          *
#define  MENU_COINSCHANGE3JIDU	97	//*     |   |   |#3����ö��--------->(MenuID=43)                         *
									//*     |   |   +--------------                                          *
#define  MENU_GOODSJIDU			98	//*     |   |������Ʒ��¼----------------->(MenuID=44)                           *
									//*     |   |   +--------------                                          *
#define  MENU_CHANNELTRANSJIDU	99	//*     |   |   |����������ͳ��--->(MenuID=47)                           *
									//*     |   |   +--------------                                          *
#define  MENU_TRANSINPUTNUMJIDU	100	//*     |	|   	|��������---------->(MenuID=48)                    *
									//*     |	|   	+--------------                                      *
#define  MENU_TRANSCHANNELNOJIDU 101//*     |   | 			|�������-------->(MenuID=49)          		     *
									//*     |   |   |		+--------------                                  *
#define  MENU_TRANSSUCCESSJIDU	102	//*     |   |   | 		|�ɹ�����ͳ��---->(MenuID=50)                    *
									//*     |   |   |		+--------------                                  *
#define  MENU_TRANMONEYJIDU		103	//*     |   |   | 		|��Ʒ���ͳ��---->(MenuID=50)                    *
									//*     |   |   |		+--------------                                  *	
#define  MENU_CLEARTRANSJIDU	104	//*     |   |������ȼ�¼------------->(MenuID=52)                           *
									//*     |   +---+                                                        *
#define  MENU_CONFIRMATIONJIDU	105	//*     |   |   |��ȷ����------->(MenuID=53)                           *
									//*     |   |   +--------------                                          *									
#define  MENU_LANGUAGE			106	//* 	Language------------------>(MenuID=54)                           *
									//* 	---+                                                             *
#define  MENU_ENGLISH			107	//* 		|Ӣ��----------------->(MenuID=55)                           *
									//*   		+---+                                                        *
#define  MENU_CHINESE			108	//*   		|����----------------->(MenuID=56)                           *
									//*   		+---+                                                        *
#define  MENU_RUSSIAN			109	//*   		|����˹��----------------->(MenuID=56)                       *//����˹��;by gzz 20121012
									//*   		+---+                                                        *														
#define  MENU_SYSTEM			110	//*     |ϵͳ����----------------->(MenuID=57)                           *
									//*     +---+                                                            *
#define  MENU_TIMESET			111	//* 		ʱ������----------------->(MenuID=58)                        *
									//* 		---+                                                         *
#define  MENU_SETYEAR			112	//* 			|��--------------------->(MenuID=59)                     *
									//*   			+---+                                                    *
#define  MENU_SETMONTH			113	//*   			|������----------------->(MenuID=60)                     *
									//*   			+---+                                                    *
#define  MENU_SETDATE			114	//* 			|��--------------------->(MenuID=61)                     *
									//*   			+---+                                                    *
#define  MENU_SETHOUR			115	//*   			|ʱ����----------------->(MenuID=62)                     *
									//*   			+---+                                                    *
#define  MENU_SETMINUTE			116	//*   			|������----------------->(MenuID=63)                     *
									//*   			+---+                                                    *																																
#define  MENU_CGPASSWORD		117	//*     |   |�������룺--------->(MenuID=64)                             *
									//*     |   +--------------                                              *
#define  MENU_NEWPW				118	//*   			|������----------------->(MenuID=65)                     *
									//*   			+---+                                                    *
#define  MENU_NEWPWREPEAT		119	//*   			|��������--------------->(MenuID=66)                     *
									//*   			+---+                                                    *			
#define  MENU_GPRSONOFF			120	//*     |   |�����ֻ�ģ�飺------->(MenuID=67)                           *
									//*     |   +--------------                                              *
#define  MENU_SERIALNO			121	//*     |   |�������------------->(MenuID=68)                           *
									//*     |   +--------------                                              *
#define  MENU_GSMNO				122	//*		|	|GSM NO��------------->(MenuID=69)                       	 *
									//*     |   +--------------                                              *
#define  MENU_TEMPERATURE		123	//*		|	|�¶��趨��------------->(MenuID=69)                       	 *
									//*     |   +--------------                                              *	
#define  MENU_SYSLANGUAGE		124	//* 	|	Language------------------>(MenuID=54)                           *
																		//* 	---+															 *
#define  MENU_SYSENGLISH		125	//* 			|Ӣ��----------------->(MenuID=55)                           *
									//*				|					//* 		+---+														 *
#define  MENU_SYSCHINESE		126	//*   			|����----------------->(MenuID=56)                           *
									//*				|					//* 		+---+														 *
#define  MENU_SYSRUSSIAN		127	//*   			|����˹��----------------->(MenuID=56)                       *//����˹��;by gzz 20121012														//* 		+---+														 *							
									//*				|					//* 		+---+								
#define  MENU_SYSTURKEY			128	//*   			|��������----------------->(MenuID=56)                           *//��������;by gzz 20121115
									//* 			|					//* 		+---+
									//*     |   +--------------                                              *
#define  MENU_TEMPSET			129	//*		|	|ѹ�������ؿ��ƣ�------------->(MenuID=69)                       	 *//���ѹ��������;by gzz 20121224
									//*     |   ---+                                              *	
#define  MENU_TEMPON			130	//*		|		|ʹ��ѹ�������أ�------------->(MenuID=69)                       	 *
									//*     |   	+---+                                               *										
#define  MENU_TEMPHOURSTR		131	//*		|		|ѹ������ʼʱ��------------->(MenuID=69)                       	 *
									//*     |   	+---+                                               *	
#define  MENU_TEMPMINUTESTR		132	//*		|		|ѹ������ʼ�֣�------------->(MenuID=69)                       	 *
                                    //*     |   	+---+ 
#define  MENU_TEMPHOUREND		133	//*		|		|ѹ��������ʱ��------------->(MenuID=69)                       	 *
									//* 	|		+---+												*	
#define  MENU_TEMPMINUTEEND		134	//*		|		|ѹ���������֣�------------->(MenuID=69)                       	 *
									//*     |   +--------------                                              *	
#define  MENU_LEDSET			135	//*		|	|չʾ�ƿ��ؿ��ƣ�------------->(MenuID=69)                       	 *//���չʾ�ƿ���;by gzz 20121229
									//*     |   ---+                                              *	
#define  MENU_LEDON			    136	//*		|		|ʹ��չʾ�ƿ��أ�------------->(MenuID=69)                       	 *
									//*     |   	+---+                                               *										
#define  MENU_LEDHOURSTR		137	//*		|		|չʾ�ƿ�ʼʱ��------------->(MenuID=69)                       	 *
									//*     |   	+---+                                               *	
#define  MENU_LEDMINUTESTR		138	//*		|		|չʾ�ƿ�ʼ�֣�------------->(MenuID=69)                       	 *
                                    //*     |   	+---+ 
#define  MENU_LEDHOUREND		139	//*		|		|չʾ�ƽ���ʱ��------------->(MenuID=69)                       	 *
									//* 	|		+---+												*	
#define  MENU_LEDMINUTEEND		140	//*		|		|չʾ�ƽ����֣�------------->(MenuID=69)                       	 *
									//*     |   +--------------                                              *										
#define  MENU_SETCHANNEL		141	//*     |��������----------------->(MenuID=70)                           *
									//*     +---+                                                            *
#define  MENU_INPUTLAYER		142  //*     |   |��������----------->(MenuID=71)                           *
									//*     |   +--------------                                              *
#define  MENU_LAYERNO			143  //*     |   	|��ܱ��----------------->(MenuID=72)                   *
									//*     |   +--------------                                              *
#define  MENU_LAYENABLE			144 //*     |   	|�Ƿ�����----------------->(MenuID=73)                   *
									//*     |   +--------------                                              *
#define  MENU_MAXGOODS			145  //*     |   	|�������--------------->(MenuID=74)                   *
									//*     |   +--------------                                              *
#define  MENU_CHANNEL1			146  //*     |   	|��һ����----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNELNUM1		147  //*     |   	|��һ��������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *									
#define  MENU_CHANNEL2			148  //*     |   	|�ڶ�����----------------->(MenuID=76)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNELNUM2		149  //*     |   	|�ڶ���������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNEL3			150  //*     |   	|��������----------------->(MenuID=77)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNELNUM3		151  //*     |   	|������������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNEL4			152  //*     |   	|���Ļ���----------------->(MenuID=78)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNELNUM4		153  //*     |   	|���Ļ�������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNEL5			154  //*     |   	|�������----------------->(MenuID=79)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNELNUM5		155  //*     |   	|�����������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNEL6			156  //*     |   	|��������----------------->(MenuID=80)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNELNUM6		157  //*     |   	|������������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNEL7			158  //*     |   	|���߻���----------------->(MenuID=81)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNELNUM7		159  //*     |   	|���߻�������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNEL8			160  //*     |   	|�ڰ˻���----------------->(MenuID=82)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNELNUM8		161  //*     |   	|�ڰ˻�������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *

//121105 by cq TenChannels
#define  MENU_CHANNEL9			162  //*     |   	|�ھŻ���----------------->(MenuID=82)                   *
									 //*     |   +-------------- 
#define  MENU_CHANNELNUM9		163  //*     |   	|�ھŻ�������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *
#define  MENU_CHANNEL0			164  //*     |   	|�������----------------->(MenuID=82)                   *
									 //*     |   +-------------- 
#define  MENU_CHANNELNUM0		165  //*     |   	|�����������----------------->(MenuID=75)                   *
									 //*     |   +--------------                                              *



#define  MENU_NOTEVALUE1		166	//*     |   			|ֽ����ͨ��1��----->(MenuID=23)                  *
									//*     |   +--------------                                              *
#define  MENU_NOTEVALUE2		167 //*     |   			|ֽ����ͨ��2��----->(MenuID=24)                  *
									//*     |   +--------------                                              *
#define  MENU_NOTEVALUE3		168	//*     |   			|ֽ����ͨ��3��----->(MenuID=23)                  *
									//*     |   +--------------                                              *
#define  MENU_NOTEVALUE4		169	//*     |   			|ֽ����ͨ��4��----->(MenuID=24)                  *
									//*     |   +--------------                                              *
#define  MENU_NOTEVALUE5		170	//*     |   			|ֽ����ͨ��5��----->(MenuID=23)                  *
									//*     |   +--------------                                              *
#define  MENU_NOTEVALUE6		171	//*     |   			|ֽ����ͨ��6��----->(MenuID=24)                  *
									//*     |   +--------------                                              *
#define  MENU_NOTEVALUE7		172	//*     |   			|ֽ����ͨ��7��----->(MenuID=23)                  *
									//*     |   +--------------                                              *
#define  MENU_NOTEVALUE8		173	//*     |   			|ֽ����ͨ��8��----->(MenuID=24)                  *
									//*     |   +--------------                                              *
#define  MENU_COINVALUE1		174	//*     |   			|Ӳ����ͨ��1��----->(MenuID=23)                  *
									//*     |   +--------------                                              *
#define  MENU_COINVALUE2		175	//*     |   			|Ӳ����ͨ��2��----->(MenuID=24)                  *
									//*     |   +--------------                                              *
#define  MENU_COINVALUE3		176	//*     |   			|Ӳ����ͨ��3��----->(MenuID=23)                  *
									//*     |   +--------------                                              *
#define  MENU_COINVALUE4		177	//*     |   			|Ӳ����ͨ��4��----->(MenuID=24)                  *
									//*     |   +--------------                                              *
#define  MENU_COINVALUE5		178 //*     |   			|Ӳ����ͨ��5��----->(MenuID=23)                  *
									//*     |   +--------------                                              *
#define  MENU_COINVALUE6		179	//*     |   			|Ӳ����ͨ��6��----->(MenuID=24)                  *
									//*     |   +--------------                                              *
#define  MENU_COINVALUE7		180 //*     |   			|Ӳ����ͨ��7��----->(MenuID=23)                  *
									//*     |   +--------------                                              *
#define  MENU_COINVALUE8		181	//*     |   			|Ӳ����ͨ��8��----->(MenuID=24)                  *
									//*     |   +--------------                                              *
#define  MENU_CHANGEVALUE1		182	//*     |   |#1��������ֵ��--------------->(MenuID=23)                   *
									//*     |   +--------------                                              *
#define  MENU_CHANGEVALUE2		183	//*     |   |#2��������ֵ��--------------->(MenuID=24)                   *
									//*     |   +--------------                                              *
#define  MENU_CHANGEVALUE3		184	//*     |   |#3��������ֵ��--------------->(MenuID=25)                   *
									//*     |   +--------------                                              *
#define  MENU_DEFAULTSET		185	//* 	|����Ĭ������----------->(MenuID=8)                        *
									//*     |   +--------------                                              *
#define  MENU_CONFIRMSET		186	//*     |   |   |��ȷ����------->(MenuID=53)                           *
									//*     |   |   +--------------                                          *																	
//#define  MENU_SYNGOODSCOL		126	//* 	|ȫϵͳͬ��----------->(MenuID=8)                        *		
//#define  MENU_ADDCOIN   		127	//* 	|��Ӳ�����----------->(MenuID=8)                        *	
//#define  MENU_ADDBILL	    	128	//* 	|ȡֽ�����----------->(MenuID=8)                        *	



//************************************************************************************************************************//
#define  MENU_NOTETESTCONFIRM	187	//* 	|ֽ����������----------->(MenuID=8)                        *
									//*     |   +--------------                                              *
#define  MENU_COINSTESTCONFIRM	188	//* 	|Ͷ����������----------->(MenuID=8)                        *
									//*     |   +--------------                                              *
#define  MENU_SUBALLCHANNELSTAT 189	//*     |����״̬�Ӳ˵�--------------->(MenuID=17)                         *
									//*     |   +--------------                                              *
#define  MENU_SUBCHTESTRESULT 	190	//*     |�������Խ���Ӳ˵�--------------->(MenuID=17)                         *
									//*     |   +--------------                                              *
#define  MENU_SELECTMEI 		191	//*     |MEI�˵�ѡ����--------------->(MenuID=17)                         *
									//*     |   +--------------                                              *
#define  MENU_SELECTGBA 		192 //*     |MEI�˵�ѡ����--------------->(MenuID=17)                         *
                                    //*     |
#define  MENU_SELECTITL         193 //*     |MEI�˵�ѡ����--------------->(MenuID=17)                         *
                                    //*     |   +--------------                                              *
#define  MENU_SELECTCLOSE 		194	//*     |MEI�˵�ѡ����--------------->(MenuID=17)                         *
									//*     |   +--------------                                              *

#define MENU_PASSWORD_2			195 //120724 by cq RecordPassword /**/
#define MENU_PASSWORD_3			196 
#define MENU_PASSWORD_ADMIN     197


#define  MENU_NULL				225
//�û�ģʽ�˵�;by gzz 20121130
#define  MENU_VISIBLE_FAUSE		1	
#define  MENU_VISIBLE_TRUE		255

	
char * MenuInit0(void);
char * MenuInitPWIN(void);
char * MenuInitCHIN(void);
char * MenuInitLAYIN(void);
char * MenuInitAddGoods(void);
char * MenuInitCHNO(void);
char * MenuInitCHPR(void);
char * MenuInitCHST(void);
char * MenuInitCHGOODS(void);
char * MenuInitCHSU(void);
char * MenuInitCHMONEY(void);
char * MenuInitCHSUJIDU(void);
char * MenuInitCHMONEYJIDU(void);
char * MenuInitCHDO(void);
char * MenuInitCHLF(void);
char * MenuInitNOST(void);
char * MenuInitCOST(void);
char * MenuInitTOCH(void);
char * MenuInitCOCH1(void);
char * MenuInitHOST1(void);
char * MenuInitHOST2(void);
char * MenuInitHOST3(void);
//121113 by cq Cashless
char * MenuInitHOST2_ReaderCost(void);
char * MenuInitHOST3_ReaderEnable(void);
char * MenuInitIOU(void);

char * MenuInitCGSV(void) ;
char * MenuInitPONO(void) ;
char * MenuInitSACON(void) ;
char * MenuInitPOSEN(void) ;
char * MenuInitPCEN(void) ;
char * MenuInitLCDSEL(void) ;
char * MenuInitKeySel(void)	;	//ѡ������;by gzz 20121025
char * MenuInitLogoSel(void);//ƴͼ��Ļ��ʽ;by gzz 20121106
char * MenuInitAutoColumn(void);//�����ֹ���������;by gzz 20130122
char * MenuInitTenColumn(void);//�Ƿ�ʹ��ʮ�����Ļ���;by gzz 20130226
char * MenuInitHOLDNOTE(void) ;
char * MenuInitHOLDNOTE5(void) ;
char * MenuInitHOLDNOTE10(void) ;
char * MenuInitNBUY(void);
char * MenuInitRCOIN(void);
char * MenuInitOCOIN(void);
char * MenuInitONOTE(void);
char *MenuInitONREADER(void);//�������˵�;by gzz 20121120
char *MenuInitOREADERCOST(void);//�������˵�;by gzz 20121120
char * MenuInitOCHANGE(void);
char * MenuInitBMIN(void);
char * MenuInitMMAX(void);
char * MenuInitGPRS(void);
char * MenuInitSENO(void);
char * MenuInitGSMNO(void);
char * MenuInitTemerature(void);
char * MenuInitDBMN(void);
char * MenuInitINCOME(void);
char * MenuInitNOIN(void);
char * MenuInitCOIN(void);
char * MenuInitTOTR(void);
char * MenuInitTOCH(void);
char * MenuInitCOVA1(void);
char * MenuInitCOVA2(void);
char * MenuInitCOVA3(void);
//���ڼ��Ƚ�����;by gzz 20121009
char * MenuInitINCOMEJIDU(void);
char * MenuInitNOINJIDU(void);
char * MenuInitCOINJIDU(void);
char * MenuInitTOTRJIDU(void);
char * MenuInitTOCHJIDU(void);
char * MenuInitCOVA1JIDU(void);
char * MenuInitCOVA2JIDU(void);
char * MenuInitCOVA3JIDU(void);

char * MenuInitSUNUM(void);
char * MenuInitDBNUM(void);
char * MenuInitFLASH(void);
char * MenuInitYear(void);
char * MenuInitMonth(void);
char * MenuInitDate(void);
char * MenuInitHour(void);
char * MenuInitMinute(void);
//���ѹ��������;by gzz 20121224
char * MenuInitCompressOn(void);				  //ѹ����ʱ�����
char * MenuInitCompressHourOn(void); 			  //ѹ������ʱ
char * MenuInitCompressMinuteOn(void);				  //ѹ�����򿪷�
char * MenuInitCompressHourOff(void);				  //ѹ�����ر�ʱ
char * MenuInitCompressMinuteOff(void);				  //ѹ�����رշ�
//���չʾ�ƿ���;by gzz 20121229
char * MenuInitLEDOn(void);				  //չʾ��ʱ�����
char * MenuInitLEDHourOn(void);				  //չʾ�ƴ�ʱ
char * MenuInitLEDMinuteOn(void);				  //չʾ�ƴ򿪷�
char * MenuInitLEDHourOff(void); 			  //չʾ�ƹر�ʱ
char * MenuInitLEDMinuteOff(void);				  //չʾ�ƹرշ�
char * MenuInitLAYNO(void);
char * MenuInitLAYENABLE(void);
char * MenuInitMAXGOODS(void);
char * MenuInitCH1(void);
char * MenuInitCH2(void);
char * MenuInitCH3(void);
char * MenuInitCH4(void);
char * MenuInitCH5(void);
char * MenuInitCH6(void);
char * MenuInitCH7(void);
char * MenuInitCH8(void);
//121105 by cq TenChannels
char * MenuInitCH9(void);
char * MenuInitCH0(void);

char * MenuInitCHNum(uint8_t ID);//������������;by gzz 20121120
char * MenuInitCH1Num(void);
char * MenuInitCH2Num(void);
char * MenuInitCH3Num(void);
char * MenuInitCH4Num(void);
char * MenuInitCH5Num(void);
char * MenuInitCH6Num(void);
char * MenuInitCH7Num(void);
char * MenuInitCH8Num(void);
//121105 by cq TenChannels
char * MenuInitCH9Num(void);
char * MenuInitCH0Num(void);

		
char *	MenuInitNOCH1(void);
char *	MenuInitNOCH2(void);
char *	MenuInitNOCH3(void);
char *	MenuInitNOCH4(void);
char *	MenuInitNOCH5(void);
char *	MenuInitNOCH6(void);
char *	MenuInitNOCH7(void);
char *	MenuInitNOCH8(void);
char *	MenuInitCOCH1(void);
char *	MenuInitCOCH2(void);
char *	MenuInitCOCH3(void);
char *	MenuInitCOCH4(void);
char *	MenuInitCOCH5(void);
char *	MenuInitCOCH6(void);
char *	MenuInitCOCH7(void);
char *	MenuInitCOCH8(void);
char *  MenuInitCGVA1(void);
char *  MenuInitCGVA2(void);
char *  MenuInitCGVA3(void);	
void 	HoldNoteInit(void);
void KeySystemInit(uint8_t mode);//�����û��˵��ɼ�;by gzz 20121204


uint8_t  MenuFunctionNull(void);
uint8_t  MenuFunctionPW2(void);//120729 by cq RecordPassword /**/
uint8_t  MenuFunctionPW3(void);//���ڼ��Ƚ�����;by gzz 20121009
uint8_t  MenuFunctionPWAdmin(void);//�û�ģʽ�˵�;by gzz 20121130
uint8_t  MenuFunctionPW(void);
uint8_t  MenuFunctionENG(void);
uint8_t  MenuFunctionCHN(void);
uint8_t  MenuFunctionRussian(void);	//����˹��;by gzz 20121012
uint8_t  MenuFunctionTurkey(void);//��������;by gzz 20121115
uint8_t  MenuFunctionDemo1(void);
uint8_t  MenuFunctionCHIN(void);
uint8_t  MenuFunctionCHLF(void);//
//uint8_t  MenuFunctionDemo3(void);
uint8_t  MenuFunctionCHPR(void);
uint8_t  MenuFunctionCHST(void);
uint8_t  MenuFunctionCHGOODS(void);
uint8_t  MenuFunctionAddGoods(void);
uint8_t  MenuFunctionADDLAYIN(void);	
uint8_t  MenuFunctionSynGoodsCol(void);	
uint8_t  MenuFunctionAddCoinChanges(void);
uint8_t  MenuFunctionAddBillChanges(void);
uint8_t  MenuFunctionDemo6(void);
uint8_t  MenuFunctionDemo7(void);
uint8_t  MenuFunctionDemo8(void);
uint8_t  MenuFunctionNOTETEST(void);
uint8_t  MenuFunctionCOINSTEST(void);
uint8_t  Hopper1Test(void);
uint8_t  Hopper2Test(void);
uint8_t  Hopper3Test(void);
//121113 by cq Cashless
uint8_t  Hopper2Test_ReaderCost(void);
uint8_t  Hopper3Test_ReaderEnable(void);
uint8_t  MenuFunctionKeyTest(void);
uint8_t  MenuFunctionAllChannelStat(void);
uint8_t  MenuFunctionAllCHResult(void);	//���л������Խ��
uint8_t  MenuFunctionChannelTest(void);
uint8_t  MenuFunctionTESTCHIN(void);
uint8_t  MenuFunctionIRTest(void);
uint8_t  MenuFunctionLCDTest(void);
uint8_t  MenuFunctionDOLCDTest(void);
uint8_t  MenuFunctionTemperatureTest(void);
uint8_t  MenuFunctionDoTempeTest(void);
uint8_t  MenuFunctionXuanhuoTest(void);	//ѡ����������
uint8_t  MenuFunctionDoXuanhuoTest(void);	//������ѡ����������
uint8_t  MenuFunctionTempTest(void);	//ѹ��������//���ѹ��������;by gzz 20121224
uint8_t  MenuFunctionDoTempsTest(void);	//������ѹ��������//���ѹ��������;by gzz 20121224
uint8_t  MenuFunctionLEDTest(void);	//չʾ�Ʋ���//���չʾ�ƿ���;by gzz 20121229
uint8_t  MenuFunctionDoLEDTest(void);	//������չʾ�Ʋ���
uint8_t  MenuFunctionDemo12(void);
uint8_t  MenuFunctionDemo13(void);
uint8_t  MenuFunctionDemo14(void);
uint8_t  MenuFunctionDemo15(void);
uint8_t  FunctionCGVA(uint8_t id);

uint8_t  MenuFunctionNBUY(void);
uint8_t  MenuFunctionRCOIN(void);
uint8_t  MenuFunctionOCOIN(void);
uint8_t  MenuFunctionONOTE(void);
uint8_t  MenuFunctionONREADER(void);//�������˵�;by gzz 20121120
uint8_t  MenuFunctionREADERSetOFF(void);//�������˵�;by gzz 20121120
uint8_t  MenuFunctionREADERSetMDB(void);//�������˵�;by gzz 20121120
uint8_t  MenuFunctionONREADERCOST(void);//�������˵�;by gzz 20121120
uint8_t  MenuFunctionSetMEI(void);
uint8_t  MenuFunctionSetGBA(void);
uint8_t  MenuFunctionSetITL(void);
uint8_t  MenuFunctionSetClose(void);
uint8_t  MenuFunctionOCHANGE(void);
uint8_t  MenuFunctionBMIN(void);
uint8_t  MenuFunctionCGSV(void);
uint8_t  MenuFunctionPONO(void);
uint8_t  MenuFunctionSACON(void);
uint8_t  MenuFunctionPOSEN(void);
uint8_t  MenuFunctionPCEN(void);
uint8_t  MenuFunctionLCDSEL(void);
uint8_t  MenuFunctionKeySel(void);//ѡ������;by gzz 20121025
uint8_t  MenuFunctionLogoSel(void);//ƴͼ��Ļ��ʽ;by gzz 20121106
uint8_t  MenuFunctionAutoColumn(void);//�����ֹ���������;by gzz 20130122
uint8_t  MenuFunctionTenColumn(void);//�Ƿ�ʹ��ʮ�����Ļ���;by gzz 20130226
uint8_t  MenuFunctionHOLDNOTE(void);
uint8_t  MenuFunctionHOLDNOTE5(void);
uint8_t  MenuFunctionHOLDNOTE10(void);

uint8_t  MenuFunctionMMAX(void);
uint8_t  MenuFunctionGPRS(void);
uint8_t  MenuFunctionGSMNO(void);
uint8_t  MenuFunctionTemprature(void);
uint8_t  MenuFunctionSENO(void);
uint8_t  MenuFunctionDBMN(void);
uint8_t  MenuFunctionDemo23(void);
uint8_t  MenuFunctionDemo24(void);
uint8_t  MenuFunctionDemo25(void);
uint8_t  MenuFunctionDemo26(void);
uint8_t  MenuFunctionDemo27(void);
uint8_t  MenuFunctionDemo28(void);
uint8_t  MenuFunctionDemo29(void);
uint8_t  MenuFunctionDemo30(void);
uint8_t  MenuFunctionDemo31(void);
uint8_t  MenuFunctionDemo32(void);
uint8_t  MenuFunctionDemo33(void);
uint8_t  MenuFunctionDemo34(void);
uint8_t  MenuFunctionDemo35(void);
uint8_t  MenuFunctionDemo36(void);
uint8_t  MenuFunctionDemo37(void);
uint8_t  MenuFunctionDemo38(void);
uint8_t  MenuFunctionCONF(void);
uint8_t  MenuFunctionCONFJIDU(void);
uint8_t  MenuFunctionYear(void);
uint8_t  MenuFunctionMonth(void);
uint8_t  MenuFunctionDate(void);
uint8_t  MenuFunctionHour(void);
uint8_t  MenuFunctionMinute(void);
uint8_t  MenuFunctionCompressOn(void);//ѹ����ʱ�����//���ѹ��������;by gzz 20121224
uint8_t  MenuFunctionCompressHourOn(void);//ѹ������ʱ//���ѹ��������;by gzz 20121224
uint8_t  MenuFunctionCompressMinuteOn(void);//ѹ�����򿪷�//���ѹ��������;by gzz 20121224
uint8_t  MenuFunctionCompressHourOff(void);//ѹ�����ر�ʱ//���ѹ��������;by gzz 20121224
uint8_t  MenuFunctionCompressMinuteOff(void);//ѹ�����رշ�//���ѹ��������;by gzz 20121224
uint8_t  MenuFunctionLEDOn(void);//չʾ��ʱ�����//���չʾ�ƿ���;by gzz 20121229
uint8_t  MenuFunctionLEDHourOn(void);//չʾ�ƴ�ʱ//���չʾ�ƿ���;by gzz 20121229
uint8_t  MenuFunctionLEDMinuteOn(void);//չʾ�ƴ򿪷�//���չʾ�ƿ���;by gzz 20121229
uint8_t  MenuFunctionLEDHourOff(void);//չʾ�ƹر�ʱ//���չʾ�ƿ���;by gzz 20121229
uint8_t  MenuFunctionLEDMinuteOff(void);//չʾ�ƹرշ�//���չʾ�ƿ���;by gzz 20121229
uint8_t  MenuFunctionNEWPW(void);
uint8_t  MenuFunctionNEWPW2(void);
uint8_t  MenuFunctionLAYIN(void);
uint8_t  MenuFunctionLAYENABLE(void);
uint8_t  MenuFunctionMAXGOODS(void);
uint8_t  MenuFunctionCH1(void);
uint8_t  MenuFunctionCH2(void);
uint8_t  MenuFunctionCH3(void);
uint8_t  MenuFunctionCH4(void);
uint8_t  MenuFunctionCH5(void);
uint8_t  MenuFunctionCH6(void);
uint8_t  MenuFunctionCH7(void);
uint8_t  MenuFunctionCH8(void);
//121105 by cq TenChannels
uint8_t  MenuFunctionCH9(void);
uint8_t  MenuFunctionCH0(void);

uint8_t  MenuFunctionCHNum(uint8_t ID);//������������;by gzz 20121120
uint8_t  MenuFunctionCH1Num(void);
uint8_t  MenuFunctionCH2Num(void);
uint8_t  MenuFunctionCH3Num(void);
uint8_t  MenuFunctionCH4Num(void);
uint8_t  MenuFunctionCH5Num(void);
uint8_t  MenuFunctionCH6Num(void);
uint8_t  MenuFunctionCH7Num(void);
uint8_t  MenuFunctionCH8Num(void);
//121105 by cq TenChannels
uint8_t  MenuFunctionCH9Num(void);
uint8_t  MenuFunctionCH0Num(void);


uint8_t  MenuFunctionNOCH1(void);
uint8_t  MenuFunctionNOCH2(void);
uint8_t  MenuFunctionNOCH3(void);
uint8_t  MenuFunctionNOCH4(void);
uint8_t  MenuFunctionNOCH5(void);
uint8_t  MenuFunctionNOCH6(void);
uint8_t  MenuFunctionNOCH7(void);
uint8_t  MenuFunctionNOCH8(void);
uint8_t  MenuFunctionCOCH1(void);
uint8_t  MenuFunctionCOCH2(void);
uint8_t  MenuFunctionCOCH3(void);
uint8_t  MenuFunctionCOCH4(void);
uint8_t  MenuFunctionCOCH5(void);
uint8_t  MenuFunctionCOCH6(void);
uint8_t  MenuFunctionCOCH7(void);
uint8_t  MenuFunctionCOCH8(void);
uint8_t  MenuFunctionCGVA1(void);
uint8_t  MenuFunctionCGVA2(void);
uint8_t  MenuFunctionCGVA3(void);
uint8_t  MenuFunctionCONFSET(void);
uint8_t  MenuFunctionADMINSET(void);//�û�ģʽ�˵�;by gzz 20121130


 //
void lcd_write_d(char c1);
void lcd_write_c(char c1);
void LcdInit(void);
void MyInit(void);
//
void DispOneBoxTextChar(unsigned char Row,unsigned char Col,unsigned char c1,unsigned char DispAttrib);
void DispTwoBoxHexChar(unsigned char Row,unsigned char Col,unsigned char c1,unsigned char DispAttrib);
//void DispGraphChar(unsigned char Row,unsigned char Col,unsigned char xdata *cArray,unsigned char DispAttrib);
//void DispTextLine(unsigned char Row,unsigned char code *MenuText,unsigned char DispAttrib);
void DispTextLine(unsigned char Row, const char  *MenuText,unsigned char DispAttrib)	;
//void ReadyForKey(void);
void DelayMs(unsigned int iMs);


//
//void DispFaceBmp(void);
void DispMenu_Root(uint8_t udkey);
void DispMenu_View(uint8_t udkey);
void DispMenu_Operation(uint8_t udkey);
void DispMenu_Test(uint8_t udkey);
void DispMENU_BUSINESSSet(uint8_t udkey);
void DispMenu_Debug(void);
//
void JudgeHLight(uint8_t udkey);

char  *DecimalPoint( uint32_t money);		  //�۸�С������ʾ
unsigned char ReadTime(void);
void 		ShowDesktopTime(void);
uint8_t  	AllChannelStat(uint8_t	layno);	 //��ǰ��ŵ����л���״̬
	
extern	uint8_t    	(*KeyFuncPtr)(void);    		//��������ָ��
extern  char *  	(*KeyInitPtr)(void);    		//������ʼ��ָ��
extern  unsigned int  	iMenuID   ;
extern  unsigned int   	iMenuNextID ;
extern  unsigned char 	cMenuTemp1;
extern  uint8_t		CursorLine;	   
extern  uint8_t  	InputSite ;			//������ʾλ��

extern 	 uint8_t		BusinessNo;
extern 	 uint8_t		InLayerNO;
extern   uint8_t		InCHNO;
extern   uint8_t		NowChannel;	 	//��ǰ�������к�
extern   uint8_t		NowLayerNo;	 	//��ǰ���
extern   uint8_t		NowLayerAll;
extern   uint8_t   		NowCHNO;		//active channel
extern   uint8_t  	InputMode;
extern   uint8_t		PASSWORD;
extern   uint8_t		DOT;		//С����ʹ��
extern   uint8_t		FDot;		//С�����־λ
extern   uint8_t		FDot1;
extern   uint8_t		FDot2;
extern   uint8_t		FSave;	
extern   uint8_t  	offset;
extern   uint32_t  	InputNum;	
extern   uint8_t		InputCol;
extern   uint8_t  	InputDone;			//�ѽ�������״̬  20110823
extern   char  		StrInit[22]; 



#define		SLNOENOUGH		0	// 		"��      ����      ��" 
#define		SLFAULT			1	//		"��      ����      ��" 
#define		SLNORMAL		2 	//		"��      ����      ��" 
#define		SLTESTING		3 	//		"���ڼ�⣬��ȴ� ..."
#define		SLCHANNELOK		4 	//		"��  ������������  ��" 
#define		SLCHANNELBAD	5	//		"��  ���������쳣  ��" 
#define		SLSAVEOK 		6 	//		"��    ����ɹ�    ��" 
#define		SNORMAL			7 	//		"����" 
#define		SFAULT			8 	//		"�쳣" 
#define		SSNORMAL		9 	//		"��" 
#define		SSFAULT			10 	//		"ȱ" 
#define		SSDISABLE		11 	//		"��" 
#define		CHBAD			12 	// 		"����:%d����" ,
#define		CHOK			13 	// 	 	"����:%d����"  ,
#define		CHEMPTY			14 	// 		"����:%d�޻�"  ,
#define		INSERTCOIN		15 	// 		"��Ͷ��Ӳ��"
#define		INSERTBILL		16 	// 		"��Ͷ��ֽ��"
#define		BALANCE			17 	// 		"Ͷ�ҽ�"
#define		SSNOGOODS		18 	// 		"��"
#define		SCHKERR		    19 	// 		"����ȷ��ģ�����"
#define		SCHKOK		    20 	// 		"����ȷ��ģ������"
#define		SCHKOFF		    21 	// 		"����ȷ��ģ��ر�"
#define		ADDLAYNO	    22 	// 		"����n������"
#define		ADDFULLLAY	    23 	// 		"��ȫ��������"

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */

#endif
