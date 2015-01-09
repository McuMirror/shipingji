/****************************************Copyright (c)****************************************************
**                            POWERORIGIN electronics Co.,LTD.
**
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.c
** Last modified Date:  2011-05-01
** Last Version:        V1.00
** Descriptions:        The main() function example template
**
**--------------------------------------------------------------------------------------------------------
** Created by:         
** Created date:       
** Version:           
** Descriptions:       
**
** Rechecked by:
*********************************************************************************************************/
#define	MAINDEF
#include "..\config.h"

#include "..\driver\LPC17xx.h"

#include "..\driver\lpc17xx_nvic.h"
#include "..\driver\lpc17xx_wdt.h"
#include "..\driver\lpc17xx_rtc.h"
#include "..\driver\UartDev.h"
//#include "..\mid\AT45DB.h"
#include "..\driver\AT45DB.h"//120401 by cq change structor
//#include "..\mid\spi.h"
#include "..\driver\spi.h"//120401 by cq change structor
#include "global.h"
#include "function.h"
#include "mdb.h"
#include "MdbNote.h"
#include "lcd.h"
#include "menu.h"
#include "pcf8563t.h"
#include "timer.h"
#include "evb.h"
#include "drv.h"
#include "gprs.h"
#include "DevTaskFun.h"
#include "SaleTaskFun.h"
#include "MdbCoin.h"//120401 by cq change structor
//#include "MdbCoinApp.h"//120401 by cq change structor
#include "Hopper.h"//120401 by cq change structor
//#include "HopperApp.h"//120401 by cq change structor
#include "PulseCoin.h"//120401 by cq change structor
//#include "PulseCoinApp.h"//120401 by cq change structor
//#include "DrvApp.h"//120401 by cq change structor
#include "BillAcceptor.h"
#include "CoinAcceptor.h"
#include "Changer.h"
#include "pcf8563t.h"
#include "RealTime.h"
#include "DebugTrace.h"
#include "ITL.h"
#include "VMC_PC.h"
#include "Acdc.h"


#define  YREGCH				   0	   //RTC�Ĵ�����

//Watchodog time out in 20 seconds
#define WDT_TIMEOUT 	20000000
/*********************************************************************************************************
  �йغ���ȫ�ֱ����Ķ���
*********************************************************************************************************/
/*********************************************************************************************************
  TASK0 ����ID�����ȼ�����ջ���ü���������                                
*********************************************************************************************************/
#define TASK0_ID                          6                             /* �����ID                     */
#define TASK0_PRIO                        TASK0_ID                      /* �������ȼ�                   */
#define TASK0_STACK_SIZE                  256                           /* �����û���ջ����             */
OS_STK  TASK0_STACK[TASK0_STACK_SIZE];                                  /* ��������0��ջ                */
extern void    TASK0(void *pdata);                                      /* ��������0                    */
/*********************************************************************************************************
  TASKB  ����ID�����ȼ�����ջ���ü���������                                
*********************************************************************************************************/
#define TASKB_ID                          7                             /* ����ID                       */
#define TASKB_PRIO                        TASKB_ID                      /* �������ȼ�                   */
#define TASKB_STACK_SIZE                  512                           /* �����û���ջ����             */
OS_STK  TASKB_STACK[TASKB_STACK_SIZE];                                  /* ��������B��ջ                */
extern void    TASKB(void *pdata);                                      /* ��������B                    */
/*********************************************************************************************************
  TASKC ����ID�����ȼ�����ջ���ü���������                                
*********************************************************************************************************/   
#define TASKC_ID                          5                             /* ����ID                       */
#define TASKC_PRIO                        TASKC_ID                      /* �������ȼ�                   */
#define TASKC_STACK_SIZE                  512                           /* �����û���ջ����             */
OS_STK  TASKC_STACK[TASKC_STACK_SIZE];                                  /* ��������C ��ջ               */
extern void    TASKC(void *pdata);                                      /* ��������C                    */
/*********************************************************************************************************
  Task_Server ����ID�����ȼ�����ջ���ü���������                                
*********************************************************************************************************/
#define Task_DEXServer_ID                    8                             /* ����ID                       */
#define Task_DEXServer_PRIO                  Task_DEXServer_ID                /* �������ȼ�                   */
#define Task_DEXServer_STACK_SIZE            512                           /* �����û���ջ����             */
OS_STK  Task_DEXServer_STACK[Task_DEXServer_STACK_SIZE];                      /* ��������Task_Server ��ջ     */
extern void    Task_DEXServer(void *pdata);                                /* ��������Task_Server          */
/*********************************************************************************************************
  Task_CoinPlus ����ID�����ȼ�����ջ���ü���������                                
*********************************************************************************************************/
#define Task_CoinPlus_ID                    9                             /* ����ID                       */
#define Task_CoinPlus_PRIO                  Task_CoinPlus_ID                /* �������ȼ�                   */
#define Task_CoinPlus_STACK_SIZE            512                           /* �����û���ջ����             */
OS_STK  Task_CoinPlus_STACK[Task_CoinPlus_STACK_SIZE];                      /* ��������Task_CoinPlus ��ջ     */
extern void    Task_CoinPlus(void *pdata);                                /* ��������Task_CoinPlus          */


char bufTx[20];				  //���ڷ��ͻ���
char bufRx[20];				  //���ڽ��ջ���

int  retCode;				  //���ڷ��ش���
/*----------------------------------------------------------------------------
  Interface to UartDev
 *----------------------------------------------------------------------------*/
extern UartDev_IOB  uart0;
       UartDev_IOB *pUart;

uint32_t DispMsgFlag = 0,DispMsgFlag1 = 0;
//uint16_t DispModeTimer = VP_DSP_TIME2;



void CreateMbox(void)    
{
	g_InitSem = OSSemCreate(0);
	g_PCSem = OSSemCreate(0);
	g_GPRSMsg = OSMboxCreate(NULL);			// ����GPRSͨѶ��Ϣ����
	//120621 by cq KeySlowly
	//g_KeyMsg  = OSMboxCreate(NULL);			// ��������������Ϣ����
	g_KeyMsg  = OSQCreate(&KeyMsgArray[0],KEYQUEUE);// ��������������Ϣ��Ϣ����	
	g_MoneyMsg  = OSMboxCreate(NULL);		// ��������������Ϣ����//120621 by cq KeySlowly
	g_CoinPlusMsg  = OSQCreate(&CoinPlusArray[0],COINPLUSQUEUE);// ��������������Ϣ��Ϣ����
	g_PCCMDMsg  = OSMboxCreate(NULL);		// ����PC������Ϣ����
	g_CommMsg = OSMboxCreate(NULL);			// �����豸��������
	g_CommBackMsg = OSMboxCreate(NULL);		// �������������
	g_PCCommMsg = OSMboxCreate(NULL);			// ����PC�豸��������
	g_PCCommBackMsg = OSMboxCreate(NULL);		// ����PC���������
	//120914 by cq Cashless
	mbVmcToCashless = OSMboxCreate(NULL);
	mbCashlessToVmc = OSMboxCreate(NULL);
}


//����ϵͳ��������������ӳ���ϵ
void systeminit(void)
{
	 uint16_t	i,j,temp;
	 uint8_t	LayNum =0,ChannelNum =0;

	 XSystemPara(READ);											  //��ȡϵͳ����
	 XSystemPara1(READ);
	 //XColSystemPara(READ);//������������;by gzz 20121120
	 //XKeySystemVisible(READ);//�����û��˵��ɼ�;by gzz 20121204
	 temp = SOFTVERSION;
	 if((SYSPara.SoftwareVersion & 0xff00) != (temp & 0xff00))	
	 { //ϵͳ���£���ʼ������			  				
			RstSystemPara();
				
			XChannels(WRITE);						 //����ϵͳ����
			XSystemPara(WRITE);
			XSystemPara1(WRITE);
			//XColSystemPara(WRITE);//������������;by gzz 20121120
			//XKeySystemVisible(WRITE);//�����û��˵��ɼ�;by gzz 20121204
			XTransaction(WRITE);
			RTC_WriteGPREG(LPC_RTC,YREGCH,0);
	}
	
	XChannels(READ);								  //��ȡϵͳ����
	XSystemPara(READ);
	XSystemPara1(READ);
	XSystemPara2(READ);
	XColSystemPara(READ);//������������;by gzz 20121120
	XKeySystemVisible(READ);//�����û��˵��ɼ�;by gzz 20121204
	XTransaction(READ);

	for(i = 0;i < MAXLAYER;i++)	
	{					    //�����������ӳ���ϵ
		ChnMapPara.LAYTODRV[i] = 0;   //����
		ChnMapPara.DRVTOLAY[i] = 0;
		if( SYSPara.LayEnable[i] == 0x01 )  
		{
			ChnMapPara.LAYTODRV[LayNum++] = i+1;
			ChnMapPara.DRVTOLAY[i] = LayNum;
		}

		ChannelNum = 0;
		for(j = 0; j < MAXCHANNEL; j++)	
		{
			ChnMapPara.CHTODRV[i][j] = 0;		//��������
			ChnMapPara.DRVTOCH[i][j] = 0;
			if( (Channels[i][j].ChannelStat & 0x80) == 0x80 ) 
			{
				
				ChnMapPara.CHTODRV[i][ChannelNum++] = j+1;
				ChnMapPara.DRVTOCH[i][j] = ChannelNum;
			}
		
		}
	}
}

/*----------------------------------------------------------------------------
  SendChar
  Write character to Serial Port.
 *----------------------------------------------------------------------------*/
int SendChar (int ch)  {
  int size = 1;

  //retCode =  pUart->BufTx ((void *)&ch, &size, UartDev_FLAG_BLOCKING);
  return (ch);
}


/*----------------------------------------------------------------------------
  SendString
  Write a const string to Serial Port.
 *----------------------------------------------------------------------------*/
void SendString (const char *str)
{
	while (*str)
	{
		SendChar((int)*str++);
	}
}

/*----------------------------------------------------------------------------
  GetKey
  Read character to Serial Port.
 *----------------------------------------------------------------------------*/
int GetKey (void)  {
  int ch;
  int size = 1;


  retCode =  pUart->BufRx ((void *)&ch, &size, UartDev_FLAG_BLOCKING);
  if (size == 0)
    ch = -1;

  return (ch);
}

//return 1��Ҫ���豸��0����Ҫ���豸
uint8_t IsInTime(uint16_t nowTime,uint16_t beginTime,uint16_t endTime)
{  	
	//Trace("begintime=%d,endtime=%d\n",sysVPMission.saleTime[i],sysVPMission.saleTime[i+1]);
	if( (nowTime>=beginTime)&&(nowTime<=endTime) )			
		return 1;
	else
		return 0;
}

//�����ֹ���������;by gzz 20130122
void AutoAddColumn()
{	
	uint8_t i,j;
	
	for(j = 0; j< MAXLAYER; j++)	
	{
		//Trace("\r\n +");
		for(i = 0; i < MAXCHANNEL;i++)
		{
		    //ֻ�л���״̬Ϊ1����3�Ĳſ������
			//121108 by cq DontReduceNum
			//if(((Channels[j][i].ChannelStat& 0x03)==CHANNELOK)||((Channels[j][i].ChannelStat& 0x03)==CHANNELOVER) )
			if((isDontReduceNum())||((Channels[j][i].ChannelStat& 0x03)==CHANNELOK)||((Channels[j][i].ChannelStat& 0x03)==CHANNELOVER))
			{
				//Channels[j][i].GoodsNum = SYSPara.LayMaxGoods[j];
				//Channels[j][i].GoodsNum = colSystemPara.ColMaxGoods[j][i];//������������;by gzz 20121120
				Channels[j][i].GoodsNum = 5;
				//Trace("%d, ",colSystemPara.ColMaxGoods[j][i]);
                //���Ļ���״̬
				if((Channels[j][i].ChannelStat& 0x03)==CHANNELOVER)
				{
					Channels[j][i].ChannelStat	&= DRV_CHNSET_BIT;
					Channels[j][i].ChannelStat 	|= CHANNELOK;					
				}	
			}					
		}
	}
}

//����ϵͳ������������Ӧ��ϵ�����׼�¼
void TurkeySystemSet(void)
{
    uint16_t i,j;
	//uint8_t  *tp;
	//SystemPara tempSysPara;

	/*			
	//1.��ҵ�����
	SYSPara.MoneyMaxin = 2000;
	SYSPara.MoneyMinLeft = 100;
	SYSPara.ChangeServer = 0;
	SYSPara.Decimal = 2;
	SYSPara.TransMultiMode = 0;
	SYSPara.TransEscape = 0;	
	SYSPara.POSEnable = 0; 
	SYSPara.PCEnable = 0; 
	SYSPara.LCDSel = 2;
	SYSPara.KeySel = 0;//ѡ������;by gzz 20121025
	SYSPara.LogoSel = 3;//ƴͼ��Ļ��ʽ;by gzz 20121106
	SYSPara.ReaderEnable = 0;//�������˵�;by gzz 20121120 
	SYSPara.ReaderCost = 0;

	//121108 by cq GOCErrorSevice
	SYSPara.GOCCtr = 1;
	SYSPara.GOCErrorSevice = 0; 

	
	SYSPara2.AutoColumn = 1;
	SYSPara2.TenColumn = 1;
	SYSPara.NoteEscrow = 0;
	SYSPara.NoteEscrowType[1]=0;
	SYSPara.NoteEscrowType[2]=0;

	//2.���������
	ColumnFunction(0,0,0);
	ColumnFunction(2,0,0);
	ColumnFunction(4,0,0);
	LayerFunction(0,6);
	LayerFunction(0,7);

	//3.��ϵͳѹ����,չʾ�Ʋ���
	SYSPara2.CompressorTime.DeviceOn = 2;
	SYSPara2.CompressorTime.HourOn   = 0;
	SYSPara2.CompressorTime.MinOn    = 0;
	SYSPara2.CompressorTime.HourOff  = 23;
	SYSPara2.CompressorTime.MinOff   = 59;
	SYSPara2.LEDTime.DeviceOn = 2;
	SYSPara2.LEDTime.HourOn   = 0;
	SYSPara2.LEDTime.MinOn    = 0;
	SYSPara2.LEDTime.HourOff  = 23;
	SYSPara2.LEDTime.MinOff   = 59;
	*/
	//SYSPara.GBAEnable = MDB_NOTE_EN;
	//SYSPara.CoinEnable = MDB_COIN_EN;
	//SYSPara.ChangerEnable = MDB_CHANGER_EN;
	//SYSPara.ReaderEnable = 1;//�������˵�
	//SYSPara.ReaderCost = 1;  //��������Ǯ	
	
	SYSPara.ReaderCost = 1;  //��������Ǯ
	
}


void StartCoinplusTask()
{
	OSTaskCreateExt(Task_CoinPlus,
	                    (void *)0,
	                    &Task_CoinPlus_STACK[Task_CoinPlus_STACK_SIZE-1],
	                    Task_CoinPlus_PRIO,
	                    Task_CoinPlus_ID,
	                    &Task_CoinPlus_STACK[0],
	                    Task_CoinPlus_STACK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);  
}


/*********************************************************************************************************
** Function name:       TASK0
** Descriptions:        ������
** input parameters:    pvData: û��ʹ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void TASK0(void *pvData)
{
	uint32_t delay;
	
	pvData = pvData;  
	
	WDT_Init(WDT_CLKSRC_IRC, WDT_MODE_RESET);
	
	// Start watchdog with timeout given
	WDT_Start(WDT_TIMEOUT);			
		   	
	AT45DB_Init();//�����flash�洢����ͨ��spi���߶�д
	
	delay = SystemCoreClock / 10;
	while(--delay);
	
	AT45DB_WaitOK();
	AT45DB_GetFlashPara();
	//AT45DB_Test();		
	
	RTCn_Init();
	
	WDT_Feed(); 
	if(SYSPara1.FlashStat == 0) 
	{
	    systeminit();		   //ϵͳ��ʼ��
	}
	WDT_Feed(); 
	CreateMbox() ; 
	while(1) 
	{
		OSTaskCreateExt(TASKB,
	                    (void *)200,
	                    &TASKB_STACK[TASKB_STACK_SIZE-1],
	                    TASKB_PRIO,
	                    TASKB_ID,
	                    &TASKB_STACK[0],
	                    TASKB_STACK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);  
	    WDT_Feed(); 
		OSTaskCreateExt(TASKC,
	                    (void *)0,
	                    &TASKC_STACK[TASKC_STACK_SIZE-1],
	                    TASKC_PRIO,
	                    TASKC_ID,
	                    &TASKC_STACK[0],
	                    TASKC_STACK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR); 
	  
	   // ZlgipInitial(GucMcuIp,GucMcuGateWay,GucMcuMark);
	   WDT_Feed(); 
	   //ʹ�������mdbӲ��;by gzz 20130105
	   OSTaskCreateExt(Task_CoinPlus,
	                    (void *)0,
	                    &Task_CoinPlus_STACK[Task_CoinPlus_STACK_SIZE-1],
	                    Task_CoinPlus_PRIO,
	                    Task_CoinPlus_ID,
	                    &Task_CoinPlus_STACK[0],
	                    Task_CoinPlus_STACK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
	   WDT_Feed(); 
	   OSTaskCreateExt(Task_DEXServer,
	                    (void *)0,
	                    &Task_DEXServer_STACK[Task_DEXServer_STACK_SIZE-1],
	                    Task_DEXServer_PRIO,
	                    Task_DEXServer_ID,
	                    &Task_DEXServer_STACK[0],
	                    Task_DEXServer_STACK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);  		   	
	
	   	while (1) 
		{
			WDT_Feed(); 
			if(IsReInitStat()) 
			{
			    OSTaskDel(TASKB_PRIO);
				OSTaskDel(TASKC_PRIO);
				OSTaskDel(Task_DEXServer_PRIO);
				OSTaskDel(Task_CoinPlus_PRIO);

				RstDevStatus();
				ReturnSaleStat();							
				break;
			}
			
			OSTimeDly(OS_TICKS_PER_SEC);
	    }
	} 
}

/*********************************************************************************************************
** Function name:       main
** Descriptions:        �û�������ں���
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int main(void)
{	
	targetInit();                                                       /* ��ʼ��Ŀ��壬����ɾ��       */
    pinInit();                                                          /* ���ų�ʼ��                   */                                                                     
	VCC_POWERON();

	EVB_PWRON();//120426 by cq temperature control

    OSInit();                                                                                                       
  //  OSTaskCreate(TASK0, (void *)0, &stkMainTask[sizeof(stkMainTask) / 4 - 1], TASK0_PRIO);
    OSTaskCreate(TASK0, (void *)0, &TASK0_STACK[TASK0_STACK_SIZE-1], TASK0_PRIO);
    OSStart();
}
 
/*********************************************************************************************************
** Function name:       TASKB
** Descriptions:        ά�����ݴ�������������������
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void  TASKB (void *pdata)
{	
	extern uint32_t ChgAmount;
  
    uint8_t 	DispMode,i,j,err;
	/*��ǰ����״̬��ȷʵҪ��ʼ���ײ���ʱ������ʱ����״̬��ֵ�������� �ϴν���״̬�������������һ�ν���״̬���ͽ��������ָ�ʹ�ã� ��ʱ����״̬������*/
	uint8_t		CurrentStat,LastStat,SaleStat,cSta;
	/*ʵ������������ ʵ�ʻ����к� ʵ�ʻ����к�*/
	uint8_t     ChannelNum,ChannelX,ChannelY;
	/*���հ�����Ͷ����Ϣָ��*/
	uint16_t 	*PKeyInput;
	/*���հ�����Ͷ����Ϣ*/
	uint16_t	KeyInput;
	/*��ǰ�յ���Ͷ��ֵ*/														   		
	uint16_t	Money;	
	/*��ǰ���ʽ��*/
	uint32_t    DoubtMoney;	
	uint8_t 	InputSys=0;
	uint32_t    DebtMoney=0;	
	uint8_t     state,cMsg,cCashlessKeyInputFlag = 0;

	//120821 by cq ReturnCoinKey
	uint8_t		ReturnCoinKey=0;
	uint32_t	DisintOutput;
	uint16_t	nowTime,beginTime,endTime;
	uint8_t		CompressDev=0,LEDDev=0,DevSet=0;
	
	//RTC_TIME_Type CurrentTime;			

	pdata = pdata;
	//change by liya 20121013
	if(SYSPara.Language == 2)
	{
		LCD_WhiteBlock(0);
		ClearScreen();
	}
	//���Ʒ;��Ļ�ļ���;by gzz 20121025
	else
	{
		ClearScreen();
	}

    //*********************
    //1����ʼ����ϵͳ����ֵ
    //*********************
	ReturnSaleStat();//���뽻��״̬
	SetInputMode();//�����������ְ���
	RstInputNum();//�������ְ���
	RstHaveSaleFlag();//��λ�ѽ��й����ױ�־

	LastStat = MVC_VMCRST;//�������һ�ν���״̬

//	strcpy(SYSPara.GSMNO,"13706966847");
	DoubtMoney = TranTotal.DoubtMoney;//�����ʽ��
	EnableMoneyIn();//ʹ��Ͷ��������
	
	/*�鿴�ͻָ�����Amount���ݣ��õ�����ǰ��Ͷ�ҽ����䱣�浽���׼�¼��*/
	g_Amount = RTC_ReadGPREG(LPC_RTC,YREGCH);
	if((g_Amount > 0) && (g_Amount < SYSPara.MoneyMaxin*2)) 
	{
	    TranTotal.Iou = g_Amount;	  	//Ƿ���ܶ�
		XTransaction(WRITE);
		RTC_WriteGPREG(LPC_RTC,YREGCH,0);
	}

	g_Amount = 0;
	SaleStat = MVC_BEGIN;//�轻��״̬
	LastStat = MVC_BEGIN;//���ϴν���״̬

	//--------------------------
	//��ʼ������
	SYSPara.LCDSel=2;//ƴͼ��Ļ��ʽ;by gzz 20121106
	SYSPara2.TenColumn = 1;//ʮ����
	//ר��Ϊ���������õĳ���
	TurkeySystemSet();
	//==========================

	
	SYSPara2.AutoColumn = 1;//�����Զ�����
	
		
	#if DISP_MODE == LCD_DISPLAY 
	LCD_Init();	
	SCLK_BL_SET();//���ߣ��Ա�����Ļ��˸;by gzz 20130121 	
	#endif
	
	init_timer(0, TIME_INTERVAL); 	  //��ʼ����ʱ��0  Xms
    enable_timer(0);				  //ʹ�ܶ�ʱ��0
	InitKey();	                      //���̳�ʼ��

//	Draw_FullBmp(Disp_Bmp);

	//120821 by cq ReturnCoinKey
	ReturnCoinKey_SetInput();


	OSTimeDly(OS_TICKS_PER_SEC/10);	

	//*****************************************************************************
    //2���ȴ����豸�ĳ�ʼ����ɣ���ʼ��������TASKC��������ɺ󣬻ᷢ������g_InitSem
    //*****************************************************************************
    DispVersionText();//120704 by cq DispVersion
	DispInitText();	//��ʾ"�豸��ʼ���У����Ժ�"

	OSSemPend(g_InitSem,OS_TICKS_PER_SEC * 20,&err);	//�ȴ��豸��ʼ�����

	//if(SYSPara.CoinEnable==PULSE_COIN_EN )
	//{
	//	StartCoinplusTask();
	//}
    //ѡ������;by gzz 20121025
	if(SYSPara.KeySel == 1 )
	{	
		UpdateSelectionLed();//���µƵ���ʾ
	}

	//�����ֹ���������;by gzz 20130122
	if(SYSPara2.AutoColumn != 0)
	{
		AutoAddColumn();
	}
	
   	CurrentStat = MVC_BEGIN;//�赱ǰ����״̬
	TimerDly.CheckDly = SALETIME3;//��һ��ʱ�䣬����ʱ����豸״̬
	//120621 by cq KeySlowly
	//OSMboxAccept(g_KeyMsg);//����Ƿ��а�������
	OSQAccept(g_KeyMsg);//����Ƿ��а�������
	DispMode = 1;	
	if(DevSet==0)
	{
		DevSet = 1;
		//if( (SYSPara2.LEDTime.DeviceOn>0)||(SYSPara2.CompressorTime.DeviceOn>0) )
		
		CompressDev = sysVPMission.ACDCCompressorCtr;
		LEDDev = sysVPMission.ACDCLedCtr;
		if(SYSPara2.CompressorTime.DeviceOn>0) 
		{
			CompressDev = 1;
		}
		if(SYSPara2.LEDTime.DeviceOn>0)
		{
			LEDDev = 1;
		}
		
		//acdc�豸������ֽ�Ϊ������룬����Ϊ�豸����
		DisintOutput =	((uint32_t)CMD_ACDC << 24) + ((uint32_t)LEDDev<<1)+CompressDev;
		MsgBack.CmdType = DisintOutput;
		OSMboxAccept(g_CommBackMsg);
		OSMboxPost(g_CommMsg,&MsgBack.CmdType); 
		//Write_LCD(LINE0,Menu_ACDC[SYSPara.Language][5],strlen(Menu_ACDC[SYSPara.Language][5]));
		OSTimeDly(OS_TICKS_PER_SEC / 2);
		Trace("\r\n 1.LEDDev=%d,CompressDev=%d",LEDDev,CompressDev);
		
	}
	while(1) 
	{
		while(1) 
		{	
			//Trace("\r\n+++begin sys");
		    //*********************
		    //3����������ά��ģʽ
		    //*********************
		    //�������ʱ���ͼ�⵽����ά��״̬	    
			if(!MAINTEN_SWITCH()) 
			{				   
	           OSTimeDly(2);
			   if(!MAINTEN_SWITCH()) //����
			   {
			   	   //Trace("\r\n+++EnterMain");	
				   EnterMaintainStat();//ģʽ��Ϊά��״̬
				   			   
			       if(IsMoneyInEN()) //���Ͷ����״̬��ʾ��ʹ�ܵģ����Խ���
				   {
					   SetTouBiStat(CMD_ALL_DIS);  //����Ͷ��  
					   DisableMoneyIn();//���Ͷ����״̬��ʾ��Ϊ����
				   }	
                   //Trace("\r\n+++1");	
				   //���pc�п������ϱ�pc
				   if( SYSPara.PCEnable == 1 )
				   {
					   OSMboxAccept(g_PCCommMsg);
					   MsgBack.CmdPCCMDMSG = ((uint32_t)VP_ADMIN_ENTER_MENU << 24); 
					   OSMboxPost(g_PCCommMsg,&MsgBack.CmdPCCMDMSG);//֪ͨϵͳ����ά��ģʽ�������
				   }
				   
				   //Trace("\r\n+++2");	
	
				   #if DISP_MODE == LCD_DISPLAY
				       //Trace("\r\n+++Menu");
					   Cursor_Off(LCDUP);
			           menu();//����ά���˵�
		           #endif
			   }				   
            } 
			else 
			{		
			    //*****************************************************************************
			    //4����ά���˵��˻ؽ���ģʽ�󣬼�ⷢ������g_pvmcFlag.Maintain״̬����ά��״̬
			    //��Ϊ0xFF,Ȼ��һֱ�ȴ����ȴ�TASK0���������״̬�󣬽�TASKB,TASKC,TASK_DEXSserver����
			    //ɾ������������
			    //*****************************************************************************
				if(IsMaintainStat()) 
				{
					/*����ReInitStat�󣬵ȴ���������*/
					SetReInitStat();			    //�˳�ά��״̬

					//Trace("\r\n+++QuitMain");

					//���pc�п������ϱ�pc
					if( SYSPara.PCEnable == 1 )
					{
					   OSMboxAccept(g_PCCommMsg);
					   MsgBack.CmdPCCMDMSG = ((uint32_t)VP_ADMIN_QUIT_MENU << 24); 
					   OSMboxPost(g_PCCommMsg,&MsgBack.CmdPCCMDMSG);//֪ͨϵͳ����ά��ģʽ�������
				    }	
					
					
					while(1) 
					{
					    OSTimeDly(OS_TICKS_PER_SEC * 5);
					}
				}

                //*******************************************
				//5�������pcͨѶ��ֱ��ͨѶ�ɹ��Ž��뽻��״̬
				//*******************************************
				if(( SYSPara.PCEnable == 1 )&&(InputSys == 0))
				{					
					OSSemPend(g_PCSem,0,&err);	//һֱ�ȴ���ֱ���豸��ʼ�����
					InputSys = 1;
				}

				//*********************
			    //6����ʼ����ģʽ
			    //*********************
				ReturnSaleStat();

				//Trace("\r\nReady opt");
				
				if(IsDeviceOK()) //����豸������״̬	
				{	     
				    
					//*********************************
				    //7�����豸�����£������������ĸ���
				    //*********************************
				    
				    //�ڿ���״̬�£�������ʾ�ֽ����ѣ������ֽ�һ�Ӳ��
					if(SaleStat == MVC_BEGIN) //�����ǰ״̬�ǳ�ʼ����״̬
					{
					//120621 by cq LCDswitch
						
					/*
						if(DispMode == 0) 
						{
							DispMode = 1;
						}
						else 
						{
							DispMode = 0;
						}
					
						if(DispModeTimer < VP_DSP_TIME1) 
						{
							DispMode = 1;
						}
						else 
						{
							DispMode = 0;
						}
						
						if(DispModeTimer == 0)
							DispModeTimer = VP_DSP_TIME2;
							*/
							
						
						if(DispMode == 1)
							DispMode = 0;
						else
							DispMode = 1;
						/*if(DispMsgFlag>=300)
						{
							DispBeginText(DispMode);
							DispMsgFlag = 0;
						}
						else
							DispMsgFlag++;	*/
						if(sysVPMission.dspTimer2==0)
						{
							sysVPMission.dspTimer2=VP_DSP_TIME4;
							DispBeginText(DispMode);
						}
					}			

					if(SYSPara.ReaderEnable)
					{
						PKeyInput = OSMboxPend(mbCashlessToVmc,1,&err);
						
						if (err == OS_NO_ERR)
						{
							cMsg = (uint8_t)*PKeyInput;
							cSta = Vmc_HandleReaderMsg(cMsg);
							if(cSta != MVC_IDLE)
								SaleStat = cSta;
							cCashlessKeyInputFlag = 1;							
							break;
						}
					}
					//PKeyInput = Vmc_PendFromReader(&SaleStat,SaleStat,1);//120914 by cq Cashless

					//�ȴ�������Ͷ���źŵȣ����������°�����Ϣ��
					//120621 by cq KeySlowly
					//KeySlowly Begin
					//PKeyInput = OSMboxPend(g_KeyMsg,OS_TICKS_PER_SEC * 2,&err);

					//120821 by cq ReturnCoinKey
					//if(ReturnCoinKey_Get())
					if(ReturnCoinKey_Get()&&(g_Amount > 0)&&(SYSPara.CoinEnable!=MDB_COIN_EN) && ((IsHaveSaled()) || (SYSPara.TransEscape > 0)) ) //����н��׹�������������˱ң����˱�
					{
						//Trace("\r\nReturnCoinKey_Get ((LPC_GPIO0->FIOPIN >> 22) & 0x01) == 0"); 
						Trace("\r\nReturKey=%d,g_Amount=%d,havesale=%d,trans=%d",ReturnCoinKey_Get(),g_Amount,IsHaveSaled(),SYSPara.TransEscape);
						ReturnCoinKey = 1;
						//SaleStat = MVC_PAYOUT;
						break;
					}
					else
					{
						//Trace("\r\nReturnCoinKey_Get == 1");
					}
					


					//�ȴ������ź�					
					PKeyInput = OSQPend(g_KeyMsg,1,&err);
					KeyInput = *PKeyInput;		    
					if(err == OS_NO_ERR) 
					{		
						//Trace("\r\n TASKB,PendKeyMsg=%d,%d",KeyInput);
	#if DISP_MODE == LCD_DISPLAY
					    Cursor_Off(LCDUP);						
						OSTimeDly(OS_TICKS_PER_SEC / 10);
	#endif
						//Trace("\r\n++presskey,pkey=%x,key=%x",*PKeyInput,KeyInput);
						break;
					}	
					//Trace("\r\n +%d,%d",i,sysVPMission.dspTimer1);
					//i++;
					//�ȴ�Ͷ���źŵȣ����������°�����Ϣ��
					PKeyInput = OSMboxPend(g_MoneyMsg,1,&err);
					//KeySlowly End
					
					KeyInput = *PKeyInput;		    
					if(err == OS_NO_ERR) 
					{		
						//Trace("\r\n TASKB,PendMoneyMsg=%d",KeyInput);
						#if DISP_MODE == LCD_DISPLAY
					    Cursor_Off(LCDUP);
					    #endif
						break;
					}				

					//������ʱ�������л��µĽ���״̬ 
					if(TimerDly.OperateDly == 0) 
					{			
						SaleStat = SaleTimeoutProc(SaleStat);//������ʱ�л�����״̬����

						if(SaleStat != MVC_BEGIN) 
						{
						    KeyInput = KEY_NULL;//��հ���ֵ
							break;
						}
					}

					//��ʱ����豸״̬
					if(TimerDly.CheckDly == 0)
					{			
					    TimerDly.CheckDly = SALETIME3;
					    DoDingshiMsg(); 					    
					}

					//���û��Ͷ�ҽ�����ʹ��Ͷ���豸
					//121106 by cq BillSingleWork
					/*
					if((g_Amount == 0)
					   && IsMoneyInEN() 
					   && (CashState.ChangerState == CHANGER_OK) 
					   && (CashState.NoteState & NOTE_DEV_DIS)) 
					*/
					if((g_Amount == 0)
					   && IsMoneyInEN() 
					   && ((isBillSingleWork())||(CashState.ChangerState == CHANGER_OK) )
					   && (CashState.NoteState & NOTE_DEV_DIS)) 
					{
					    SetTouBiStat(CMD_NOTE_EN); 	         //ʹ��ֽ��Ͷ��
					}

					
					//����pc���͵�ָ��	
					//120621 by cq PCcommunication
					/*
					state = VP_CMD_Opt();
					if(state != 0xEE)
					{						
						SaleStat = state;
						//Trace("\r\n two salestat=%d",SaleStat);						
						break;
					}*/

					if( SYSPara.PCEnable == 2 )
					{
						  state = VP_CMD_Opt();						  
						  if(state != 0xEE)
						  {
								SaleStat = state;		
								
								break;
						  }
						  OSTimeDly(OS_TICKS_PER_SEC/10);
					}
					//ѡ������;by gzz 20121025
					if(SYSPara.KeySel == 1 )
					{	
						UpdateSelectionLed();//���µƵ���ʾ
					}

					/*
					//���չʾ�ƿ���;by gzz 20121229
					if( (SYSPara2.LEDTime.DeviceOn==1)||(SYSPara2.CompressorTime.DeviceOn==1) )
					{
						Trace("\r\n Begin ledcomp");
						CompressDev = sysVPMission.ACDCCompressorCtr;
						LEDDev = sysVPMission.ACDCLedCtr;
						RTCn_GetFullTime ((RTC_TIME_Type *)&TranData.Time);//��ȡrtcʱ��
						OSTimeDly(2);						
						nowTime = (TranData.Time.HOUR * 100) + TranData.Time.MIN;
						if( nowTime <= 2500 )
						{
							if(SYSPara2.LEDTime.DeviceOn==1)
							{
								//����״̬�¼�⣬�Ƿ���չʾ��
								beginTime = (SYSPara2.LEDTime.HourOn * 100) + SYSPara2.LEDTime.MinOn;
								endTime = (SYSPara2.LEDTime.HourOff * 100) + SYSPara2.LEDTime.MinOff;
								if((IsInTime(nowTime,beginTime,endTime))&&(sysVPMission.ACDCLedCtr == 0))
								{
									LEDDev = 1;
									DevSet = 1;
								}
								else if((!(IsInTime(nowTime,beginTime,endTime)))&&(sysVPMission.ACDCLedCtr == 1))
								{
									LEDDev = 0;
									DevSet = 1;
								}
								Trace("\r\n now=%d,begin=%d,end=%d,LEDDev=%d,DevSet=%d",nowTime,beginTime,endTime,LEDDev,DevSet);
							}

							if(SYSPara2.CompressorTime.DeviceOn==1)
							{
								//����״̬�¼�⣬�Ƿ���ѹ����
								beginTime = (SYSPara2.CompressorTime.HourOn * 100) + SYSPara2.CompressorTime.MinOn;
								endTime = (SYSPara2.CompressorTime.HourOff * 100) + SYSPara2.CompressorTime.MinOff;
								if((IsInTime(nowTime,beginTime,endTime))&&(sysVPMission.ACDCCompressorCtr == 0))
								{
									CompressDev = 1;
									DevSet = 1;
								}
								else if((!(IsInTime(nowTime,beginTime,endTime)))&&(sysVPMission.ACDCCompressorCtr == 1))
								{
									CompressDev = 0;
									DevSet = 1;
								}
								Trace("\r\n now=%d,begin=%d,end=%d,CompressDev=%d,DevSet=%d",nowTime,beginTime,endTime,CompressDev,DevSet);
							}

							if(DevSet == 1)
							{
								DevSet = 0;
								//Trace("\r\n LEDDev=%d,CompressDev=%d",LEDDev,CompressDev);
								//acdc�豸������ֽ�Ϊ������룬����Ϊ�豸����
								DisintOutput =	((uint32_t)CMD_ACDC << 24) + ((uint32_t)LEDDev<<1)+CompressDev;
								MsgBack.CmdType = DisintOutput;
								OSMboxAccept(g_CommBackMsg);
								OSMboxPost(g_CommMsg,&MsgBack.CmdType); 
								//Write_LCD(LINE0,Menu_ACDC[SYSPara.Language][5],strlen(Menu_ACDC[SYSPara.Language][5]));
								OSTimeDly(OS_TICKS_PER_SEC / 2);
							}
						}
						
					}*/					
				} 
				//***************************************************************************************
			    //8�����豸�����£���Ͷ�ҽ�����㲢������ʾ��ͣ���񣬺ʹ�������У�Ȼ���Լ죬ֱ�����ϻָ�
			    //***************************************************************************************
				else 
				{			                
				    //�����Ͷ�ҽ�����״̬��Ϊ���㣬ֱ������
					if(g_Amount > 0) 
					{
					    KeyInput = KEY_NULL;		//
						RstInputMode();
						SaleStat = MVC_PAYOUT;
						break;
					}

	                //���Ͷ������ʹ�ܵģ���������
					if(IsMoneyInEN()) 
					{
						DisableMoneyIn();						
						SetTouBiStat(CMD_ALL_DIS);  //����Ͷ��
					}
	
					/*���������TranTotal.DoubtMoney = DoubtMoney��
					 *������ֽ����ʶ��escrowed state��ִ��stack�����ȴû�г���stacked stateʱ��
					 *TranTotal.DoubtMoney > DoubtMoney�����ڵĲ��ּ��ղų�����escrowed state��ֽ�����
					 */
					 //����ֽ����ѹ������������ϵͳ���ϣ���δѹ�ɹ��Ľ�����ϵͳ���ʽ����
					if(TranTotal.DoubtMoney > DoubtMoney) 
					{
					    TranTotal.DoubtMoney -= DoubtMoney;
					    DoubtMoney = TranTotal.DoubtMoney;
						XTransaction(WRITE);
					}						   	  				   	   		               
					
					#if DISP_MODE == LCD_DISPLAY
				    Cursor_Off(LCDUP);
				    #endif										
					
					//������ʾ��ͣ���񣬺ʹ�������У�Ȼ���Լ죬ֱ�����ϻָ�
					TimerDly.CheckDly = SALETIME3;
					while(1) 
					{			  
						  DispErrText();//��ʾ��ͣ���񣬺ʹ������
						  //�������ά��״̬	
						  if(!MAINTEN_SWITCH()) 
						  {	    
						      SaleStat = MVC_BEGIN;
							  SetInputMode();//�������ְ���
							  RstInputNum();//��ʼ������
						      break;
						  }
						  //�豸�Լ죬���»ָ���������������������ģʽ
						  else if(IsDeviceOK()) 
						  {
						      SaleStat = MVC_BEGIN;			
							  SetInputMode();
							  RstInputNum();
							  EnableMoneyIn();//ʹ��Ͷ����״̬
							  SetTouBiStat(CMD_ALL_EN);//ʹ��Ͷ���� 
								//120621 by cq KeySlowly
							  //OSMboxAccept(g_KeyMsg);							  
							  OSQAccept(g_KeyMsg);
							  sysVPMission.dspTimer2 = 0;//�ӿ���ʾ���н���;by gzz 20121106	
							  break;					//��������������ģʽ
						  }	
						  //���ǹ���
						  else 
						  {			
						      //ʱ�䵽�󣬶�ʱ���¼��һ��
						      if(TimerDly.CheckDly == 0) 
							  {		
							      TimerDly.CheckDly = SALETIME3;
								  DoDingshiMsg(); 
							  }
						  }
						  
						  //11������pc���͵�ָ��
						  //120621 by cq PCcommunication
						  /*
						  state = VP_CMD_Opt();						  
						  if(state != 0xEE)
						  {
								SaleStat = state;								
						  }
						  OSTimeDly(OS_TICKS_PER_SEC/10);
						  */

						  if( SYSPara.PCEnable == 2 )
						  {
							  state = VP_CMD_Opt();						  
							  if(state != 0xEE)
							  {
									SaleStat = state;								
							  }
							  OSTimeDly(OS_TICKS_PER_SEC/10);
						  }						  
					}
			    }
		    }

			
		}

		
		//*******************************************************************************************************
	    //9�������Ͷ�ң����ۼӵ�Ͷ�ҽ���У����жϣ��������Ͷ�ҽ���������׽���ʣ����ң���Ͷ��������
	    //*******************************************************************************************************
        //���λΪ1,��˵������Ϊ�ͻ�Ͷ����

		//120914 by cq Cashless
		/*
		if(cCashlessKeyInputFlag == 1)
		{
			cCashlessKeyInputFlag = 0;
		}
		else 
		*/	
		if (KeyInput & 0x8000) 
		{  					
			RstInputNum();
			Money = KeyInput & 0x7FFF;//�õ�����Ͷ�ҽ��,����ֽ�Һ�Ӳ��
			KeyInput = KEY_NULL;
		//  if((Money % 100) == 0) 		 		//Ͷ����ֵΪ100�ı���
		//  { 
				g_Amount += Money;	//�ۼ�Ͷ�ҽ��								

                //����Ǵ�����߽������ޣ����ߴ��ڿ��������ޣ���������Ӧ�豸����
				if(IsMoneyInEN()) 
				{
					if(g_Amount >= SYSPara.MoneyMaxin) 
					{
						DisableMoneyIn();
						SetTouBiStat(CMD_ALL_DIS);      //����Ͷ��
					} 
					//121106 by cq BillSingleWork
					else if(isBillSingleWork())
					{
						//dosen't dis_note
					}		
					/*
					else if(g_Amount >= g_CoinLeft) 
					{
					    SetTouBiStat(CMD_NOTE_DIS);      //����Ͷ��
					}
					*/
				}		
				
				if( (SaleStat != MVC_ADDMONEY) && (g_Amount > 0) )
				{	  
				   SaleStat = MVC_SALE;					//��������״̬ ������ADDMONEY
				}		 
		//  } 
	
			RTC_WriteGPREG(LPC_RTC,YREGCH,g_Amount);	//�ݴ浱ǰ���
		}
		else if((KeyInput >> 8) > 0) 
		{			//����
		    switch(KeyInput >> 8) 
			{
			    case OVER_VALUE_INDEX:
					SaleStat = MVC_OVERVALUE;
					break;

				case RETURN_MONEY_INDEX://�˱�����
				    //Trace("\r\n 1.%d,%d,%d,%d,%d",g_Amount,IsHaveSaled(),(SYSPara.TransEscape > 0),(SYSPara.ReaderEnable==0),(Reader_GetFundsMultiplyUnit()==0));
				                          //����н��׹�������������˱ң����˱�
					if((g_Amount > 0) && (IsHaveSaled() || (SYSPara.TransEscape > 0)) 
						//������û�������ߵ�ǰ������ûǮ
						&& ((SYSPara.ReaderEnable==0)||(Reader_GetFundsMultiplyUnit()==0))) 
					{
						//Trace("\r\n 2.");
					    SaleStat = MVC_PAYOUT;
					}
					break;

				default:
					break;
			}									    
		} 		
		//*********************************************************************
	    //10�������������������Ƿ���Ͷ�ң��Լ������ϸ���״̬��������һ����״̬
	    //*********************************************************************
		//˵������Ϊ������,�����Ƿ���Ͷ�ң�״̬��Ϊ��ѯ����״̬������ѡ��״̬
		else 
		{									//����
		    /*��������*/
			SaleStat = KeyProcess(SaleStat,KeyInput,&ChannelNum);//ѡ������;by gzz 20121025		
		}

		//120821 by cq ReturnCoinKey
		if(ReturnCoinKey == 1)
		{
			ReturnCoinKey = 0;
			SaleStat = MVC_PAYOUT;
		}



		
		//*******************************************
	    //11�����ݵ�ǰ�����Ľ���״̬��������Ӧ�Ĳ���
	    //*******************************************
		while(1) 
		{
			//Trace("\r\n now salestat=%d",SaleStat);
			CurrentStat = SaleStat;//�������Ľ���״̬���浽CurrentStat��
			switch(SaleStat) 
			{
				case MVC_CHAXUN:						//��ѯ״̬
					RstInputMode();
					//ѡ������;by gzz 20121025
					if(SYSPara.KeySel == 0 )
					{
						ChannelNum = g_KeyStat.InputNum;	//�õ�����״̬				 
					}
					if(DRV_ChnChk(ChannelNum,&ChannelX,&ChannelY) == TRUE) 
					{
					    DispChaxunText(ChannelX,ChannelY,KeyInput);//��ʾ��ѯ���//ѡ������;by gzz 20121025
						
						//OSTimeDly(OS_TICKS_PER_SEC * 2);
						OSTimeDly(OS_TICKS_PER_SEC / 2);
			 
						SaleStat = MVC_BEGIN;//�ص���ʼ����״̬
						OSQFlush(g_KeyMsg);//120621 by cq KeySlowly
						SetInputMode();//�������ְ���
					} 
					else 
					{
					    SaleStat = MVC_INPUTERR;//�����������
					}
					RstInputNum();
					sysVPMission.dspTimer2 = 0;//�ӿ���ʾ���н���;by gzz 20121106
					break;
												    //������ʱ
				case MVC_CHAOSHI:
					RstInputMode();
					DispChaoshiText();//��ʾ������ʱ
					OSTimeDly(OS_TICKS_PER_SEC * 2);
					SaleStat = MVC_SAVEDAT;//��Ҫ���潻�׼�¼
					break;

				case MVC_INPUT:						    //�����������״̬
					SetInputMode();
					TimerDly.OperateDly = SALETIME2;   
					SaleStat = DispInputText();		  //��ʾ���������ҳ��		
					break;

				case MVC_INPUTERR:					    //�����������
					RstInputMode();
					DispInputErrText();//��ʾ�����������

					OSTimeDly(OS_TICKS_PER_SEC * 2);

					RstInputNum();

					#if CHNINPUT_MODE == TWO_Bit_MODE				
					SaleStat = MVC_INPUT;
					#elif CHNINPUT_MODE == ONE_Bit_MODE
					if(g_Amount > 0) 
					{
					    SaleStat = MVC_SALE;
					} 
					else 
					{
						SaleStat = MVC_BEGIN;
						sysVPMission.dspTimer2 = 0;//�ӿ���ʾ���н���;by gzz 20121106
						SetInputMode();
					}
					#endif
					
					OSQFlush(g_KeyMsg);//120621 by cq KeySlowly
					break;
			
				case MVC_SALE:						    //����״̬���ȴ�Ͷ��
				    //Trace("\r\n three salestat=%d,g_Amount=%d",SaleStat,g_Amount);
				    //Trace("\r\n input saletime");
					SetInputMode();
					TimerDly.OperateDly = SALETIME;   
					DispSaleText();    //��ʾ�ȴ�Ͷ�ҵ�ҳ��
					
					if( (!IsMoneyInEN()) 
						//������û�������ߵ�ǰ������ûǮ
						&& ((SYSPara.ReaderEnable==0)||(Reader_GetFundsMultiplyUnit()==0)))
					{
						if(g_Amount < g_CoinLeft) 
						{
							EnableMoneyIn();
							SetTouBiStat(CMD_ALL_EN);       //ʹ��Ͷ��
						}
						else if(g_Amount < SYSPara.MoneyMaxin)
						{
						    EnableMoneyIn();
							SetTouBiStat(CMD_COIN_EN);      //ʹ��Ͷ��
						}
					}
					//ѡ������;by gzz 20121025
					if(SYSPara.KeySel == 1 )
					{	
						UpdateSelectionLed();//���µƵ���ʾ
					}
					if((SYSPara.ReaderEnable==1)&&(Reader_GetFundsMultiplyUnit()==0)) 
					{
						Vmc_PostToReader(VTR_READER_DISABLE);
					}
					break;

				case MVC_OVERVALUE:					    //Ͷ�ҳ���
					RstInputMode();
					DispOverText();//��ʾֽ�ҳ�������
					
					OSTimeDly(OS_TICKS_PER_SEC * 2);
					//SaleStat = LastStat;
					SetInputMode();
					TimerDly.OperateDly = SALETIME;   
					if(g_Amount > 0) //���㲻��	
					{
						DispSaleText();    //��ʾ�ȴ�Ͷ�ҵ�ҳ��
					}
					
					if( (!IsMoneyInEN()) 
						//������û�������ߵ�ǰ������ûǮ
						&& ((SYSPara.ReaderEnable==0)||(Reader_GetFundsMultiplyUnit()==0)))
					{
						if(g_Amount < g_CoinLeft) 
						{
							EnableMoneyIn();
							SetTouBiStat(CMD_ALL_EN);		//ʹ��Ͷ��
						}
						else if(g_Amount < SYSPara.MoneyMaxin)
						{
							EnableMoneyIn();
							SetTouBiStat(CMD_COIN_EN);		//ʹ��Ͷ��
						}
					}
					
					SaleStat = LastStat;
					break;

				case MVC_XUANHUO:						//ѡ��
					RstInputMode();
					//ѡ������;by gzz 20121025
					if(SYSPara.KeySel == 0 )
					{
						ChannelNum = g_KeyStat.InputNum;
					}
					RstInputNum();	

					

					//���pc�п������ϱ�pcѡ��
					if( SYSPara.PCEnable == 1 )
					{
					   DRV_ChnChk(ChannelNum,&ChannelX,&ChannelY);						   	
					   OSMboxAccept(g_PCCommMsg);
					   MsgBack.CmdPCCMDMSG = (((uint32_t)VP_BUTTON_RPT << 24) + (VP_BUT_GOODS<<16) + (Channels[ChannelX][ChannelY].GoodsCode)); 
					   OSMboxPost(g_PCCommMsg,&MsgBack.CmdPCCMDMSG);//֪ͨϵͳ����ά��ģʽ�������
					   //Trace("\r\nbutton=%d,msg=%x",Channels[ChannelX][ChannelY].GoodsCode,MsgBack.CmdPCCMDMSG);
				    }		

					OSQFlush(g_KeyMsg);//120621 by cq KeySlowly
					
					if(DRV_ChnChk(ChannelNum,&ChannelX,&ChannelY) == TRUE)
					{
					    //ChannelNum = GetChannelNo(ChannelX,ChannelY);						
						if((Channels[ChannelX][ChannelY].ChannelStat & DRV_STAT_MASK) != CHANNELOK)//��ȱ��������ѡ	
						{	
							SetHaveSaleFlag();//�ѽ��й���������
							//Trace("\r\n goto wuhuo");
						    SaleStat = MVC_WUHUO;		
					    } 
						else if(g_Amount >= Channels[ChannelX][ChannelY].GoodsPrice) //�����ڵ��ۣ������	
						{						 		   
							//120914 by cq Cashless
						    //SaleStat = MVC_CHUHUO;
						    SetHaveSaleFlag();//�ѽ��й���������

							if( (SYSPara.ReaderEnable)&&(Reader_GetFundsMultiplyUnit()>0) )
							{
								//really set the cost money
								//120926 by cq Cashless
								//Reader_SetItemValue(Channels[ChannelX][ChannelY].GoodsPrice);
								if(SYSPara.ReaderCost)
								{
									Reader_SetItemValue(Channels[ChannelX][ChannelY].GoodsPrice);
								}
								else
								{
									Reader_SetItemValue(0);
								}
								Vmc_PostToReader(VTR_VEND_REQUEST); 

								Vmc_PendFromReader(&SaleStat,MVC_SALE,OS_TICKS_PER_SEC * 10);//120914 by cq Cashless
																
							}
							else
								SaleStat = MVC_CHUHUO;
							
						} 
						else 
						{	
						    SaleStat = MVC_LESSMONEY;	//Ǯ����			   	
					    }
				    } 
					else 
					{
					     SaleStat = MVC_INPUTERR;//�����������
					}
					break;
			
				case MVC_WUHUO:						    //�޻�
					//Trace("\r\n input wuhuo");
					RstInputMode();
					DispWuhuoText(ChannelX,ChannelY);//��ʾ�޻�
					
					OSTimeDly(OS_TICKS_PER_SEC * 2);
					SetInputMode();
					TimerDly.OperateDly = SALETIME;   
					DispSaleText();    //��ʾ�ȴ�Ͷ�ҵ�ҳ��
					
					if( (!IsMoneyInEN()) 
						//������û�������ߵ�ǰ������ûǮ
						&& ((SYSPara.ReaderEnable==0)||(Reader_GetFundsMultiplyUnit()==0)))
					{
						if(g_Amount < g_CoinLeft) 
						{
							EnableMoneyIn();
							SetTouBiStat(CMD_ALL_EN);       //ʹ��Ͷ��
						}
						else if(g_Amount < SYSPara.MoneyMaxin)
						{
						    EnableMoneyIn();
							SetTouBiStat(CMD_COIN_EN);      //ʹ��Ͷ��
						}
					}					

					//Trace("\r\n goto saletime");
					OSQFlush(g_KeyMsg);//120621 by cq KeySlowly
					SaleStat = MVC_SALE;
					break;
												    
				case MVC_CHUHUO:						//����
					RstInputMode();
					DispChuhuoText();//��ʾ���ڳ���

				    if(IsMoneyInEN()) //���Ͷ������ʹ�ܵģ���������
					{
						DisableMoneyIn();
						SetTouBiStat(CMD_ALL_DIS);      //����Ͷ��
					}
					
					if(IsEscrowHold()) //�ж��Ƿ���ֽ���ݴ�
					{			   
					    DoNoteStackMsg();//ѹ��
					}				
					
					SaleStat = DoChuhuoMsg(ChannelNum,ChannelX,ChannelY);//���ͳ�������
					RTC_WriteGPREG(LPC_RTC,YREGCH,g_Amount);

					if(!IsDoubtTrans()) //��¼���ʽ���
					{				
						Channels[ChannelX][ChannelY].SuccessNum++;
						TranTotal.SuccessNum++;

						//���ڼ��Ƚ�����;by gzz 20121009
						Channels[ChannelX][ChannelY].SuccessNumJidu++;
					} 
					else 
					{
						Channels[ChannelX][ChannelY].DoubtNum++;
						TranTotal.DoubtNum++;
						RstDoubtTrans();
					}
					//ѡ������;by gzz 20121025
					if(SYSPara.KeySel == 1 )
					{	
						UpdateSelectionLed();//���µƵ���ʾ
					}
					OSQFlush(g_KeyMsg);//120621 by cq KeySlowly
					break;
				
				case MVC_RETRANS:					    //��������
					//RstInputMode();
					//TimerDly.OperateDly = SALETIME2;
					//DispRetransText();//��ʾ�Ƿ��������
					//break;	
					SetInputMode();
					TimerDly.OperateDly = SALETIME;   
					DispSaleText();    //��ʾ�ȴ�Ͷ�ҵ�ҳ��
					
					if( (!IsMoneyInEN()) 
						//������û�������ߵ�ǰ������ûǮ
						&& ((SYSPara.ReaderEnable==0)||(Reader_GetFundsMultiplyUnit()==0)))
					{
						if(g_Amount < g_CoinLeft) 
						{
							EnableMoneyIn();
							SetTouBiStat(CMD_ALL_EN);       //ʹ��Ͷ��
						}
						else if(g_Amount < SYSPara.MoneyMaxin)
						{
						    EnableMoneyIn();
							SetTouBiStat(CMD_COIN_EN);      //ʹ��Ͷ��
						}
					}					

					//Trace("\r\n goto saletime");
					SaleStat = MVC_SALE;
					break;	
				
				case MVC_LESSMONEY:						//����
					RstInputMode();	
					//TimerDly.OperateDly = SALETIME2;   			   					   
					DispLessText(Channels[ChannelX][ChannelY].GoodsPrice);		//��ʾǮ����			   						   
					/**/
					OSTimeDly(OS_TICKS_PER_SEC * 2);	   
					SetInputMode();
					TimerDly.OperateDly = SALETIME;   
					DispSaleText();    //��ʾ�ȴ�Ͷ�ҵ�ҳ��
					
					if( (!IsMoneyInEN()) 
						//������û�������ߵ�ǰ������ûǮ
						&& ((SYSPara.ReaderEnable==0)||(Reader_GetFundsMultiplyUnit()==0)))
					{
						if(g_Amount < g_CoinLeft) 
						{
							EnableMoneyIn();
							SetTouBiStat(CMD_ALL_EN);       //ʹ��Ͷ��
						}
						else if(g_Amount < SYSPara.MoneyMaxin)
						{
						    EnableMoneyIn();
							SetTouBiStat(CMD_COIN_EN);      //ʹ��Ͷ��
						}
					}					

					//Trace("\r\n goto saletime");
					OSQFlush(g_KeyMsg);//120621 by cq KeySlowly
					SaleStat = MVC_SALE;
					break;
			
				case MVC_ADDMONEY:						//��Ǯ������ѡ��Ʒ
					SetInputMode();
					TimerDly.OperateDly = SALETIME;   
					SaleStat = DispAddMoneyText(ChannelX,ChannelY);//��ʾ��Ǯ״̬���
					break;
			
				case MVC_PAYOUT:						//����
					//Ӳ�������Բ���;by gzz 20130128
					if(SYSPara.CoinEnable > 0) 
					{
						RstInputMode();
						ChgAmount = 0;
					    DispPayoutText();//��ʾ��������
						   
					    if(IsEscrowHold()) //ֽ�����ݴ棬���˳�
						{
						    DoNoteReturnMsg();
						}
						
						if(IsMoneyInEN()) //Ͷ������ʹ�ܣ��ͽ���
						{
							DisableMoneyIn();
							SetTouBiStat(CMD_ALL_DIS);      //����Ͷ��
						}

						//���� 
						/*										 
						DoCoinOutMsg();
						RTC_WriteGPREG(LPC_RTC,YREGCH,g_Amount);	

					 	HopStat = DoHopperOutMsg();	*/
						DoPayOutMsg();		 //������������
						RTC_WriteGPREG(LPC_RTC,YREGCH,g_Amount);
					
						if(g_Amount > 0) //���㲻��	
						{			  							            
							TranTotal.Iou = g_Amount;	  	    //	
							if( SYSPara.PCEnable == 1 )						
							{
								if(SYSPara.Decimal==1)
								{
								  	DebtMoney = TranTotal.Iou * 10;
								}
								else if(SYSPara.Decimal==2)
								{
								  	DebtMoney = TranTotal.Iou; 
								}	
								
							    OSMboxAccept(g_PCCommMsg);						   
							    MsgBack.CmdPCCMDMSG = ((uint32_t)VP_DEBT_RPT << 24) + DebtMoney;
							    OSMboxPost(g_PCCommMsg,&MsgBack.CmdPCCMDMSG);//֪ͨϵͳ����ά��ģʽ�������		
							    //Trace("\r\n==B debt=%x",MsgBack.CmdPCCMDMSG);
							}
							DispIOUText();	//��ʾǷ��																             										 						        					 							
						} 
						else 
						{
						    if(ChgAmount > 0) //������ֵ����0
							{				
								DispChangeText();//��ʾȡ��Ǯ
							}					
						}
						/*
						if(HopStat > 0) {				    //Hopper�������
							SetDoubtTrans();
						}
						*/
						if(!IsDoubtTrans()) //�ж��Ƿ������ʽ���
						{
							//TranTotal.SuccessNum++;
						} 
						else 
						{
							//TranTotal.DoubtNum++;
							RstDoubtTrans();//��λ���ʽ�������
						}
					}
					
					RTCn_GetFullTime ((RTC_TIME_Type *)&TranData.Time);//��ȡrtcʱ��

					OSTimeDly(OS_TICKS_PER_SEC);

					SaleStat = MVC_SAVEDAT;				
					break;

                //*******************************************
			    //12�����׽����󣬽��и�λ�ͱ����¼�Ĳ���
			    //*******************************************
				case MVC_SAVEDAT:					    //���潻�׼�¼
					RstInputMode();
					/*���������TranTotal.DoubtMoney = DoubtMoney��
					 *������ֽ����ʶ��escrowed state��ִ��stack�����ȴû�г���stacked stateʱ��
					 *TranTotal.DoubtMoney > DoubtMoney�����ڵĲ��ּ��ղų�����escrowed state��ֽ�����
					 */
					 //����ֽ����ѹ������������ϵͳ���ϣ���δѹ�ɹ��Ľ�����ϵͳ���ʽ����
					if(TranTotal.DoubtMoney > DoubtMoney) 
					{
						TranTotal.DoubtMoney -= DoubtMoney;
						DoubtMoney = TranTotal.DoubtMoney;
					}
					/*************************************************************/
					//���潻�׼�¼
					XTransaction(WRITE);
					
					/*************************************************************/		 	
					//���׽�������λ��������
					g_Amount = 0;
					for(i = 0;i<MAXINCOME; i++) 
					{
						TranData.IncomeCH[i] = 0;
					}
					for(i = 0;i<MAXOUTCOME; i++) 
					{
						TranData.OutcomeCH[i] = 0;
					}
					for(i = 0;i<MAXLAYER; i++)
					{
						for(j = 0;j<MAXCHANNEL; j++)
						{
						    TranData.Goods[i][j] = 0;
						}
					}
					TranData.Money = 0;			
										
					//����ͨ����¼
					XChannels(WRITE);				
					/*************************************************************/			                 								

					DispEndText();//��ʾ���׽���

					OSTimeDly(OS_TICKS_PER_SEC);
					
					SaleStat = MVC_BEGIN;//����״̬
					sysVPMission.dspTimer2 = 0;//�ӿ���ʾ���н���;by gzz 20121106
					SetInputMode();
					RstHaveSaleFlag();//��λ�ѽ��й����ױ�־
				    RTC_WriteGPREG(LPC_RTC,YREGCH,0);

                    /*************************************************************/		
					//���׽��������¸�λʹ�ܣ�����豸�����⣬�ͽ���
					if(!IsMoneyInEN()) 
					{
						SetTouBiStat(CMD_ALL_EN);            //ʹ��Ͷ�� 					
						EnableMoneyIn();
					} 
					//121106 by cq BillSingleWork
					//else if((CashState.ChangerState == CHANGER_OK) 
					          //&& (CashState.NoteState & NOTE_DEV_DIS)) 
					else if(((isBillSingleWork()) || (CashState.ChangerState == CHANGER_OK) )
								  && (CashState.NoteState & NOTE_DEV_DIS)) 
					{
					    SetTouBiStat(CMD_NOTE_EN); 	         //ʹ��ֽ��Ͷ��
					} 
					else 
					{
						if((CashState.ChangerState != CHANGER_OK) 
						   && ((CashState.NoteState & NOTE_DEV_DIS) == 0)) 
						{
						   	SetTouBiStat(CMD_NOTE_DIS); 	 //����ֽ��Ͷ��  						
						}
					}				
					if((SYSPara.ReaderEnable==1)&&(Reader_GetFundsMultiplyUnit()==0)) 
					{
						Vmc_PostToReader(VTR_READER_ENABLE);
					}
					break;
			
				default:
					SetInputMode();
					break;
			}

			//****************************
		    //13�����׽����󣬱��潻�ײ���
		    //****************************
			LastStat = CurrentStat;//����ǰ����״̬���浽�����״̬��
			if(SaleStat == MVC_BEGIN) 
			{
			   LastStat = MVC_BEGIN;
			}
			if(SaleStat == MVC_SALE) 
			{
			   break;
			}
			if((CurrentStat == SaleStat) || (SaleStat == MVC_BEGIN)) 
			{
				//OSMboxAccept(g_KeyMsg);//120621 by cq KeySlowly
				break;
			}
		}							
    }		  	   
}

/*********************************************************************************************************
** Function name:       TASKC
** Descriptions:        MDB���ݴ���
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/

void  TASKC (void *pdata)
{	
	uint8_t     err;
	uint32_t    *PCmdMsg;
	uint8_t     msg1,msg2,cMsg;
	uint8_t key;
	
	pdata = pdata;
	VCC_POWERON();
	
	Trace("\r\n==1");
												    
	OSTimeDly(OS_TICKS_PER_SEC*3);			 //�ȴ������ʼ��


    //****************
    //1����ʼ�����豸
    //****************
	Uart2_Init();                                //��ʼ������
	Uart3_Init();
	Uart0_Init();
	Uart1_Init();//ѡ������;by gzz 20121025
	
	Trace("\r\n==2");

	RstDevStatus();			                      //��λ�豸����״̬
	NoteEscrowClr();							  //���Escrow״̬	
	RstTouBiTest();								  //��λͶ�Ҳ���״̬��ά���˵�ʱ����Ͷ��ʹ��

	g_CoinLeft = SYSPara.MoneyMaxin;				  //���ֵ

	InitMoneyDevStat();							  /*��ʼ����MDBͶ�������豸״̬*/
	
	CheckPricePara();							  /*���۸������Ƿ���0ֵ*/

	Trace("\r\n==3");
	
	EVB_MODE_SET();					 	          //��ΪEVBģʽ
	OSTimeDly(2);		
	CheckDriverStat();							  /*��������ͨѶ״̬���������ģ��״̬*/	
				
	Trace("\r\n==4");

	GetNoteEnBit();								  /*��ȡֽ��ʹ��ͨ��*/
	GetCoinEnBit();								  /*��ȡӲ��ʹ��ͨ��*/
	GetEscrowMinCh();							  /*��ȡֽ����������ݴ�ͨ��*/

	Trace("\r\n==5");

	CheckNotePara();							  /*����Ƿ��ֶ���ֽ�����쳣*/
	CheckCoinPara();							  /*����Ƿ��ֶ���Ӳ�����쳣*/	

	RTCn_Init();                                  /*����ʵʱʱ��*/	

	CheckVMCStat();                               //����豸״̬ 

	Trace("\r\n==6");
	
	MDB_MODE_SET();					              //��ΪMDBģʽ	
	OSTimeDly(2);	
	Changer_Init();								  //��������ʼ��	
	OSTimeDly(OS_TICKS_PER_SEC / 10);
	CoinAcceptor_Init();						  //Ӳ������ʼ��

	Trace("\r\n==7");
	
	EnableMoneyType();							 /*ȷ��ʹ�ܵ�ֽ��Ӳ��Ͷ��ͨ��*/
	BillAcceptor_Init();						  //ֽ������ʼ��

    OSSemPost(g_InitSem);
	Trace("\r\npc init");	
	//pc����ʼ��
	if( SYSPara.PCEnable == 1 )
	{
		VPMission_Init();
		OSSemPost(g_PCSem);
	}
	Trace("\r\nInitOK");
	//ѡ������;by gzz 20121025
	if(SYSPara.KeySel == 1 )
	{		
		SelectKey_InitProc();//120816 by cq SelectKey
	}

	//120914 by cq Cashless
	Reader_InitPara();

	//121113 by cq Cashless
	//SYSPara.ReaderCost = 0;
	//SYSPara.ReaderEnable = 0;
	
	while(1) 
	{  	
		OSTimeDly(OS_TICKS_PER_SEC / 100);
		//120914 by cq Cashless
		if(SYSPara.ReaderEnable)
		{
			PCmdMsg = OSMboxPend(mbVmcToCashless,OS_TICKS_PER_SEC / 10,&err);
			
			if (err == OS_NO_ERR)  
				cMsg = (uint8_t)*PCmdMsg;
			else
				cMsg = 0;
			
			Reader_MainProc(cMsg);	  
			
			if(Reader_IsComErr())
				SetDevStatus(DEV_ERR_BIT_READER);
			else
				ClrDevStatus(DEV_ERR_BIT_READER);
			  
		}

	
		  //ѡ������;by gzz 20121025
		  if(SYSPara.KeySel == 1 )
		  {
		  	  key = GetSelectKey(sysVPMission.selectMode);//ѡ����������ʱʹ�������;by gzz 20121121
			  if(key != KEY_NULL)
			  {				
					MsgBack.keyback = key;
					OSQPost(g_KeyMsg,&MsgBack.keyback);		
					OSTimeDly(OS_TICKS_PER_SEC / 5);
			  }
		  }
		  CheckVMCStat();

		  if((CoinAcceptor_Available() == TRUE) || IsCoinTest())//����ڽ����У�Ӳ����ͨѶ�豸�������ģ�������ά���˵��У����ڲ���Ӳ�������Ͳ���������ѯ
		  { 
		      CoinAcceptor_PollProc();				 //Ӳ������ѯ
		  }

		  OSTimeDly(OS_TICKS_PER_SEC / 10);

		  if((BillAcceptor_Available() == TRUE) || IsNoteTest())//����ڽ����У�ֽ����ͨѶ�豸�������ģ�������ά���˵��У����ڲ���ֽ�������Ͳ���������ѯ
		  { 
		      BillAcceptor_PollProc();				 //ֽ������ѯ
		  }					  		

		  //120620 by cq PCcommunication
		  if((BeSaleStat())&&( SYSPara.PCEnable == 2 ))  //pc����ѯ
		  //if(BeSaleStat())
		  {
		  	  VPMission_Poll();
			  /*
			  if(  sysVPMission.comErrNum >= VP_TIME_OUNT_NUM )
			  {
			  	OSMboxAccept(g_PCCMDMsg);
				MsgBack.CmdPCType = VP_RESET_IND;
				OSMboxPost(g_PCCMDMsg,&MsgBack.CmdPCType);	
			  }
			  */
		  }

		  CheckVMCStat();
		  
		  if(IsEscrowSta())	//���Ŀǰֽ���ݴ��ţ��ȴ�ѹ�����Ͳ����κ���
		  {						 
		      OSTimeDly(OS_TICKS_PER_SEC / 10);
			  continue;
		  }


          //*******************************
	      //2�����ݽ���������Ϣ�����豸����
	      //*******************************
		  PCmdMsg = OSMboxPend(g_CommMsg,OS_TICKS_PER_SEC / 10,&err);//����������Ϣ�������õ�������Ҫ����ʲô�豸
			  
		  if (err ==OS_NO_ERR)	
		  {
		      //����ǲ���EVB�豸������
			  if ((*PCmdMsg >> 24) >= CMD_TYPE_EVB)	
			  {	                 
				   //EVB������ָ��			   
				   EVB_MODE_SET();	                                 //ת��EVBģʽ
				   OSTimeDly(2);
				   
				   switch(*PCmdMsg >> 24) 
				   {		  
					  case CMD_GOODS_CHECK:		                     //��ѯ����״̬
					      DrvCheckCommand(*PCmdMsg & 0xFF);				 /*������ѯ����*/
						  break;			 
					  
					  case CMD_GOODS_OUT:	                         //����
							Trace("\r\nCMD_GOODS_OUT");
						  NoteEscrowClr();								 /*����һ������ʹֽ�һ������ݴ棬Ҳ���״̬����ͬ*/
						  DrvOutCommand(*PCmdMsg & 0xFF); 				 /*��������*/
						  break;
					  
					  case CMD_HOPPER_CHANGE:	                     //����
							EVB1_MODE_SET();//120821 by cq HoppeyUse							
							OSTimeDly(2);//120821 by cq HoppeyUse
						  NoteEscrowClr();
						  HopperPayoutCmd(*PCmdMsg & 0xFFFFF,(*PCmdMsg >> 20) & 0x0F);				  				  
						  break;										 /*Hopper��������*/
					  //���ѹ��������;by gzz 20121224	  
					  case CMD_ACDC:			          //����acdc�豸
							Trace("\r\nACDC,%#x,led=%d,dist=%d",*PCmdMsg&0xff,((uint32_t)(*PCmdMsg)>>1) & 0x01,*PCmdMsg & 0x01);
							sysVPMission.ACDCLedCtr = ((uint32_t)(*PCmdMsg)>>1) & 0x01;
							sysVPMission.ACDCCompressorCtr = *PCmdMsg & 0x01;
							ACDCModuleQuery(sysVPMission.ACDCLedCtr,sysVPMission.ACDCCompressorCtr);			   /*ACDC����*/
							break;		
					  default:
					  	  break;
			       }
				   	  	
				   MDB_MODE_SET();	                                 //ת��MDBģʽ	
				   OSTimeDly(2);		   	
			  }
			  //����ǲ���������EVB�豸���������MDB����GBA�� 
			  else 
			  {
			     switch(*PCmdMsg >> 24)	
				 {   
			         case CMD_COIN_CHANGE:                           //MDB����ָ��
						Trace("\r\nCMD_COIN_CHANGE");
						 NoteEscrowClr();
						 //CoinPayoutCmd(*PCmdMsg);						 /*MDBӲ�����ұ�����*/
						 Changer_Payout(*PCmdMsg);										 
						 break;

					 case CMD_NOTE_STACK:                            //ѹ������
					     BillAcceptor_Stack(CashTypeEnBit.BillType);;	 /*ѹ��*/
						 break;

					 case CMD_NOTE_RETURN:                           //�˳�����
					     BillAcceptor_Return(CashTypeEnBit.BillType);	 /*�˳�*/
						 break;

					 case CMD_ALL_DIS:		                         //����Ͷ���豸
					 case CMD_COIN_DIS:                              //����Ӳ����
						 DisCoinDevCmd();								 /*����Ӳ��������*/

						 if((*PCmdMsg >> 24) == CMD_COIN_DIS) 
						 {
						     MsgBack.pBackMsg = 0;					 
						     OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);

						     if(IsMaintainStat())                        //�����ά��״̬
							 {
							     RstCoinTest();							 //�˳�Ӳ�Ҳ���
							 }
							 
							 OSTimeDly(OS_TICKS_PER_SEC / 10);

							 break;
						 }

					 case CMD_NOTE_DIS:				 					 
						 DisNoteDevCmd();								 /*����ֽ��������*/

						 MsgBack.pBackMsg = 0;					 
						 OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);

						 if(IsMaintainStat() && ((*PCmdMsg >> 24) == CMD_NOTE_DIS)) //�����ά��״̬
						 {
						     RstNoteTest();
						 }												//�˳�ֽ�Ҳ���

						 OSTimeDly(OS_TICKS_PER_SEC / 10);
						 break;

					 case CMD_ALL_EN:			                     //ʹ��Ͷ���豸				 
					 case CMD_COIN_EN:                               //ʹ��Ӳ����
				         EnCoinDevCmd();								 /*ʹ��Ӳ��������*/

						 if((*PCmdMsg >> 24) == CMD_COIN_EN) 
						 {
						     MsgBack.pBackMsg = 0;					 
						     OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);

						     if(IsMaintainStat())                        //�����ά��״̬
							 {
							     SetCoinTest();							 //ʹ��Ӳ�Ҳ���
							 }
							 
							 OSTimeDly(OS_TICKS_PER_SEC / 10);

							 break;
						 }

					 case CMD_NOTE_EN:				 
						 EnNoteDevCmd();								 /*ʹ��ֽ��������*/

						 MsgBack.pBackMsg = 0;					 
						 OSMboxPost(g_CommBackMsg,&MsgBack.pBackMsg);

						 if(IsMaintainStat() && ((*PCmdMsg >> 24) == CMD_NOTE_EN)) //�����ά��״̬
						 {
						     SetNoteTest();								//ʹ��ֽ�Ҳ���
						 }												

						 OSTimeDly(OS_TICKS_PER_SEC / 10);
						 break;
					 
					 default:
					 	break;		      
			     }			    	  
		      }
	      }	 //if (err ==OS_NO_ERR)	  

		  //*******************************************
	      //3������������Ϣ���õ�������Ҫ����ʲôPC����
	      //*******************************************
		  if( SYSPara.PCEnable == 1 )
		  {
			  OSTimeDly(OS_TICKS_PER_SEC / 10);		
			  PCmdMsg = OSMboxPend(g_PCCommMsg,OS_TICKS_PER_SEC / 10,&err);//����������Ϣ�������õ�������Ҫ����ʲôPC����
			  if (err ==OS_NO_ERR)	
			  {
			  		//Trace("\r\n==C debt=%x",*PCmdMsg);
			  		switch(*PCmdMsg >> 24)
			  		{
						case VP_ADMIN_ENTER_MENU:
							VPMission_Admin_RPT( VP_ADMIN_ENTER_MENU, 0, 0 );
							break;
						case VP_ADMIN_QUIT_MENU:
					    	VPMission_Admin_RPT( VP_ADMIN_QUIT_MENU, 0, 0 );
					        break;
						case VP_DEBT_RPT:							
							*PCmdMsg &= (~((uint32_t)0xff << 24));
							//Trace("\r\n==C debt,PCmdMsg=%d",*PCmdMsg);
							VPMission_Debt_RPT(0,0,*PCmdMsg);					    	
					        break;	
						case VP_COST_RPT:
							*PCmdMsg &= (~((uint32_t)0xff << 24));
							VPMission_Cost_RPT(0, *PCmdMsg);					    	
					        break;	
						case VP_RESET_IND:
							//pc����ʼ��
							VPMission_Init();
							OSSemPost(g_PCSem);							
							break;
						case VP_BUTTON_RPT:
							//*PCmdMsg &= (~((uint32_t)0xff << 24));
							msg1 = (*PCmdMsg & ((uint32_t)0xff << 16))>>16;
							msg2 = *PCmdMsg & 0xff;
							//Trace("\r\nbuttonmail=%x,one=%d,two=%d",*PCmdMsg,msg1,msg2);	
							VPMission_Button_RPT( msg1, msg2 );					    	
					        break;		
						default:
							break;
					}		
			  }
		  }
		  
    } 
}

/*********************************************************************************************************
** Function name:       Task_CoinPlus
** Descriptions:        
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void  Task_CoinPlus (void *pdata)
{
	/*���հ�����Ͷ����Ϣָ��*/
	uint16_t 	*PKeyInput;
	/*���հ�����Ͷ����Ϣ*/
	uint32_t	KeyInput;
	uint8_t 	err;
	
	//if(SYSPara.CoinEnable==PULSE_COIN_EN )//ʹ�������mdbӲ��;by gzz 20130105
	{
		//Trace("\r\n enterTASKCoin");
		while(1)
		{
			//�ȴ�����Ͷ���ź�					
			PKeyInput = OSQPend(g_CoinPlusMsg,1,&err);
			//KeyInput = *PKeyInput;		    
			if(err == OS_NO_ERR) 
			{						
				MsgBack.moneyback = *PKeyInput;   //money���루16λ�������λ��1������Ϊ��ֵ	
				//Trace("\r\n TASKCoin,money=%#x,moneyback=%#x",*PKeyInput,MsgBack.moneyback);
				while( OSMboxPost(g_MoneyMsg,&MsgBack.moneyback) != OS_NO_ERR)
			    {
			    	//Trace("\r\n PostErr");
			   		OSTimeDly(OS_TICKS_PER_SEC / 100);
			    }
				//Trace("\r\n PostOK");		
				//Trace("\r\n .TASKC,money=%d",MsgBack.moneyback & 0x7FFF);
			}
			OSTimeDly(OS_TICKS_PER_SEC / 100);
		}
	}
}


/*********************************************************************************************************
** Function name:       Task_Server
** Descriptions:        
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void  Task_DEXServer (void *pdata)
{
	uint8_t i;
  	int sizeRx, sizeTx;
  //  unsigned char c;

    pdata = pdata;	

/* Expansion statement ----------------------------------------------------- */
	// DeInit NVIC and SCBNVIC
//	NVIC_DeInit();
//	NVIC_SCBDeInit();

	/* Configure the NVIC Preemption Priority Bits:
	 * two (2) bits of preemption priority, six (6) bits of sub-priority.
	 * Since the Number of Bits used for Priority Levels is five (5), so the
	 * actual bit number of sub-priority is three (3)
	 */
//	NVIC_SetPriorityGrouping(0x05);
 /*
	//  Set Vector table offset value
#if (__RAM_MODE__==1)
	NVIC_SetVTOR(0x10000000);
#else
	NVIC_SetVTOR(0x00000000);
#endif
*/
	/* End of Expansion statement ------------------------------------------------ */

    
		//UART0_Init();
		pUart = &uart0;          /* Select 'uart0' as active communication interface. */
		pUart->Init();
		/*
		while(1) {
			sizeRx = UART0_Read(PCdata,50);
			if(sizeRx) {
			    UART0_Write(PCdata,sizeRx);	
				PCdata[sizeRx] = '\0';			    
				if(!strncmp(PCdata,"GPRS Test",9)) {				    
					break;
				}				
			}
			OSTimeDly(OS_TICKS_PER_SEC);
		}
			
		UART_FullModemForcePinState(LPC_UART1,UART1_MODEM_PIN_DTR,ACTIVE);
		UART_FullModemConfigMode(LPC_UART1,UART1_MODEM_MODE_AUTO_RTS,ENABLE);
		//SendString ("CMSIS Serial Device Example\r\n\r\n");
			
		GPRS_Test();
		*/	

		 while (1) 
		 {
		      //for (i = 0; i < 10000; i++);
		      sizeRx = 20;
		      retCode =  pUart->BufRx ((void *)&bufRx[0], &sizeRx, UartDev_FLAG_NONBLOCKING);
		      for (i = 0; i < sizeRx; i++) 
			  {
			  		bufTx[i] = bufRx[i];
			  }
		      sizeTx = sizeRx;
		      //retCode =  pUart->BufTx((void *)&bufTx[0], &sizeTx, UartDev_FLAG_NONBLOCKING);
		      if (sizeRx > 0) 
			  {
		      //  SendString("\r\n");
		      }
		     
			  OSTimeDly(OS_TICKS_PER_SEC / 4);
		}
		  
			
//
//		if(TRUE == UART0_ReceiveNByte(Buf_Global, 512))     // ����ܹ��ɹ��ڽ��ջ���ػ�ȡ512�ֽ�����
//        {
//            UART0_SendNByte(Buf_Global, 512);               // ��ô����512�ֽ�����ѹ�뷢�ͻ����
//        }
//        OSTimeDly(OS_TICKS_PER_SEC/30);                     
					
}

/*********************************************************************************************************
**  End Of File
*********************************************************************************************************/
