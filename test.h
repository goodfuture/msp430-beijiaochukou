#ifndef TEST_H
#define TEST_H

#include "cpu.h"

#ifndef MAINFILE
#define EXTERN  extern
#else
#define EXTERN
#endif

typedef char INT8U;
typedef unsigned int INT16U;
typedef unsigned long INT32U;

extern const INT16U MaskTbl[];
#define COM1  0x00
#define COM2  0x01
#define COM3  0x02
#define COM4  0x03
#define COM5  0x04

#define IS752_1   0x01
#define IS752_2   0x02

#define BAUDRATE_1200      (INT16U)0x0300
#define BAUDRATE_4800      (INT16U)0x00C0
#define BAUDRATE_9600      (INT16U)0x0060
#define BAUDRATE_57600     (INT16U)0x0010
#define BAUDRATE_115200    (INT16U)0x0008

#define REG_IIR_A       0x90      /*interrupt identification register channel A*/
#define REG_IIR_B       0x92      /*interrupt identification register channel B*/
#define REG_RXLVL_A     0xc8      /*Receiver FIFO level register channel A*/
#define REG_RXLVL_B     0xca      /*Receiver FIFO level register channel B*/
#define REG_REFIFO_A    0x80
#define REG_REFIFO_B    0x82

#define FLASHBUFFER1       0X00
#define FLASHBUFFER2       0X01
/*
 typedef struct _SYMBOL{
 unsigned COM2orCOM3:1;
 unsigned COM4orCOM5:1;
 }SYMBOL;
 EXTERN SYMBOL Symbol;
 */
extern INT8U stop_watch_devstatus;
typedef union _symb {
	struct {
		unsigned modre :1;		//modbus receive
		unsigned Mod_complete :1;		//mod check totally complete
		unsigned Mod_ontime :1;	//enable the first mod check
		unsigned Mod_checkover :2;	//interval state per check
		unsigned Hour_data :1;	//type of check data
		unsigned Day_data :1;	//type of check data
		unsigned Pass_id :1;		//ADC channel change ping-pong mode
		unsigned ccc :1;

		unsigned isover :1;		//
		unsigned rd_change :1;	//realdata upload time has been changed
		unsigned stop_watch :1;	//stop uploading the realdata
		unsigned NDO56 :1;
		unsigned DO5_DI15 :1;
		unsigned DO6_DI16 :1;
		unsigned LCD_deal :1;	//LCD deal symbol
		unsigned LCD_para_set :1;	//use LCD to set the parametre

		unsigned LCD_DO :1;
		unsigned LCD_DI :1;
		unsigned LCD_AD :1;
		unsigned LCD_Control :1;
		unsigned ADP_change :1;
		unsigned dealcommand :1;
		unsigned Mod_Device_Check :1;
		unsigned ADcalculate :1;

		unsigned LCD_T :1;
		unsigned LCD_key :1;
		unsigned LCD_Page_Change :1;
		unsigned COM2orCOM3 :1;
		unsigned COM4orCOM5 :1;
		unsigned POdata_deal :1;
		unsigned Mod_symbol :1;
	};
	long SymAll;
} SYMBOL;
EXTERN SYMBOL Symbol;

#define ParaNum 388
typedef struct S1 {
	char pw[6];  //密码
	char mn[14]; //系统标识
	char st[2];  //系统编码
	char sim[9];  //SIM卡号
	char rd_interval[3]; //实时数据上报间隔
	char overtime[5];  //超时时间
	char warntime[5];    //报警时间
	char resendtime[2];  //重发次数
	char reporttime[4];  //上报时间
	char alarmtarge[20];  //上位机地址
	unsigned char PO_Type[6];
	unsigned char PO_SerialNum[6][16];
	unsigned char LCD_Baud; //_at_ 0x206;	//开机默认9600
	unsigned char LCD_Backtime;	//开机默认120秒
	unsigned char Serial_Baud[6];
} SP1;
typedef union S3 {
	INT8U a[4];
	float b;
} ADSUB1;
typedef struct S2 {
	INT8U po_id[4];  //污染物编号
	INT8U AI_Type;  //AI转换种类0－5V，0－10V，4－20mA
	ADSUB1 ADUV, ADLV, rate, U_Alarmlimt, L_Alarmlimt; //上位值,下位值,转换精度,报警上门限,报警下门限
} ADP1;
typedef union Sys {
	struct {
		SP1 sys_parameter;
		ADP1 AD_i[8];
	};
	char sys_setting[ParaNum];
} PARAMETER;
EXTERN PARAMETER parameter;
#define	SPARA parameter.sys_parameter
#define ADPARA(X) parameter.AD_i[X]

#define DATA_LEN 300

typedef struct u1rdata			//	串行通讯协议数据结构
{
	char package_head[2];			//包头固定为“##”,长度为2
	char data_length[4];			//数据长度,长度为
	char data_segme[DATA_LEN];			//数据包中的数据段
	char CRC[5];					//校验码
	char package_tail[2];			//包尾
} DATA_SEGMENT;
EXTERN DATA_SEGMENT ReData;

typedef union RDA {
	struct S5 {
		char time[16];
		union {
			char AD[32];
			float ADF[8];
		} FF;
		char DA[4];
		char DI[2];
		char DO;
	} R_D;
	char RD[55];
} RData;
EXTERN RData RealData;			//_at_ 0x1ECB;  //实时数据

typedef struct _COMBAG {
	INT8U cbag_head[2];
	INT8U cbag_length[4];
	INT8U cbag_ST[6];
	INT8U cbag_CN[8];
	INT8U cbag_PW[10];
	INT8U cbag_MN[18];
	INT8U cbag_dynamic[960];
	INT8U cbag_crc_tail[6];
} COMBAG;

struct _Devctr {
	unsigned calibrate :1;
	unsigned sample :1;
	unsigned operate :1;
	unsigned settimes :1;
	unsigned null :12;
};
EXTERN struct _Devctr Devctr;

extern COMBAG CBAG;
EXTERN INT8U OldDO;
EXTERN INT8U LCD_page;
EXTERN INT16U LCD_light;
EXTERN INT8U KeyV;
EXTERN INT8U Screen_RST;
EXTERN INT8U LCD_RSTime;
EXTERN INT8U LCD_RST;
EXTERN INT16U Receive_Data_length;						//接收数据总长度
EXTERN INT16U Receive_Data_len;							//接收数据总长度
EXTERN INT16U Receive_Package_length;
EXTERN INT16U ADValue[8];
#define MAX_LENGTH_EXTERN   10
EXTERN INT8U COM2_Buffer[MAX_LENGTH_EXTERN];
EXTERN INT8U COM3_Buffer[29];
EXTERN INT8U COM3_Bufferbuf[31];
EXTERN INT8U COM4_Buffer[MAX_LENGTH_EXTERN];
EXTERN INT8U COM5_Buffer[MAX_LENGTH_EXTERN];
struct _COMSYMBOL {
	unsigned COM1DataReady :1;
	unsigned COM2DataReady :1;
	unsigned COM3DataReady :1;
	unsigned COM4DataReady :1;
	unsigned COM5DataReady :1;
};
EXTERN struct _COMSYMBOL COMSymbol;

typedef struct _hisdata {
	INT16U year;
	INT8U month;
	INT8U flag[31][3];
	INT16U page;
} HISDATAFLAGS;

typedef struct _hisdataD {
	INT16U year;
	INT8U month;
	INT8U flag[31];
	INT16U page;
} HISDATAFLAGS_D;

typedef struct _hisdataR {
	INT8U day;
	INT16U flag[24];
	INT16U page;
} HISDATAFLAGS_R;

extern INT8U System_Time[15];
extern INT8U System_Time1[15];
extern INT8U semicolon[2];
extern INT8U comma[2];
extern INT8U ml_mn[15]; /*本机存储系统唯一标识*/
extern INT8U ml_st[3];
extern INT8U ml_cn[5];
extern INT8U e_result[4];
extern INT8U Channel_Num[6];
extern INT8U LCD_user_pw[7];

extern INT8U LCD_index1[5][15];
extern INT8U LCD_index2[4][6];

extern INT8U current_year; /*	年		*/
extern INT8U current_moth; /*	月		*/
extern INT8U current_date; /*	日		*/
extern INT8U current_hour; /*	小时	*/
extern INT8U current_minute; /*	分钟	*/
extern volatile INT8U current_second; /*	秒	*/
extern INT8U yestoday;
extern INT8U POdata_Type;							//污染物数据类型  Rtd Rtp等
extern INT16U POdata_Receive;	//污染物数据接收标志位 Rtd Rtp等
extern INT8U PO_Retime;  //超时重发次数计数器
extern const unsigned char IOOUTPUTs[];
extern INT8U LCD_indexAD[8][5][14];
extern INT8U Pre_LCD_Dot[4];

extern float Modbustore;
#define Mod_RealD 1		//提取数据类型标志
#define Mod_MinD 2
#define Mod_HourD 3
#define Mod_DayD 4
EXTERN INT8U Mod_method;
EXTERN INT8U devcpoID[5]; //仪表反控 污染物代码
EXTERN INT8U devctime[24];
EXTERN INT16U devctnum;
extern unsigned char symbol1;
extern unsigned char symbol2;

struct _SMB {
	unsigned sdminutedata :1;
	unsigned sddaydata :1;
	unsigned sdhourdata :1;
};
EXTERN struct _SMB Rpthisdata;  //历史数据上报标志位

typedef struct _MAX_MIN {
	float max;
	float min;
	float avg;
	float sum;
	float cou;
	int num;
} MAX_MIN;
EXTERN MAX_MIN local_mma_M[8];  //本地最大最小平均值 分钟
EXTERN MAX_MIN local_mma_H[8];  //本地最大最小平均值 小时
EXTERN MAX_MIN local_mma_D[8];  //本地最大最小平均值  日
EXTERN MAX_MIN dev_mma_M[2];   //仪表最大最小平均值 分钟
EXTERN MAX_MIN dev_mma_H[2];   //仪表最大最小平均值 小时
EXTERN MAX_MIN dev_mma_D[2];   //仪表最大最小平均值  日
//B01
EXTERN MAX_MIN B01_dev_mma_M[2];   //仪表最大最小平均值 分钟
EXTERN MAX_MIN B01_dev_mma_H[2];   //仪表最大最小平均值 小时
EXTERN MAX_MIN B01_dev_mma_D[2];   //仪表最大最小平均值  日
//NH3
EXTERN MAX_MIN NH_dev_mma_M[2];   //仪表最大最小平均值 分钟
EXTERN MAX_MIN NH_dev_mma_H[2];   //仪表最大最小平均值 小时
EXTERN MAX_MIN NH_dev_mma_D[2];   //仪表最大最小平均值  日

typedef struct _RUNRECORD {
	INT8U OFFtime[14];      //掉电时间
	INT8U ONtime[14];       //开启时间
	INT8U Rtstime[14];      //当前实时数据时间
	float acctime;         //累计运行时间 （小时）
} RUNRECORD;
EXTERN RUNRECORD RunLog;

void runlogreport(void);
void run_log_init(RUNRECORD *runlog);
void run_log_record(RUNRECORD *runlog);
void Delay_N_mS(unsigned int n_milisecond);
int CPU_init(void);
void AT24C64_W(void *src, INT16U des, INT16U len);
void AT24C64_R(void *des, INT16U src, INT16U len);
void AT24C64_RS(void *des, INT16U src, INT16U len);
void FlashMemoryWrite(INT8U *addr, void *array, INT16U len, INT8U buff);
void FlashMemoryRead(INT8U *addr, void *array, INT16U len);
void FlashBufferRead(INT8U *addr, void *array, INT16U len, INT8U buff);
void FlashBufferWrite(INT8U *addr, void *array, INT16U len, INT8U buff);
void FlashBuffertoMemory(INT8U *addr, INT8U buff);
void FlashMemorytoBuffer(INT8U *addr, INT8U buff);
void FlashClearMemory(INT8U *addr, INT16U len, INT8U buff);

void Task_ReDataFrom752_1(void /*pdata*/);
void Task_ReDataFrom752_2(void /*pdata*/);

void IS752_initial_1(INT8U baudA, INT8U baudB);
void IS752_initial_2(INT8U baudA, INT8U baudB);
void Chang752Baud(INT8U baudnum, INT8U com);
void SendData(INT8U *src, INT16U len, INT8U com);

void v_Get1302(void);
void v_Set1302(void);
void v_charge1302(void);

INT16U DIInput(void);
void DOOutput(INT8U dout);

void insert(INT8U *des, const void *src, INT16U pos);
void separation(INT8U *strinput);
void command_store(INT8U *dat1, INT8U *key);
void Response(INT8U type);
void add_send();
//void Add_Send();
void cp_analyze();
void dealdata_wjj();
long mod10n(INT8U n);
void float_to_string(float tempf, INT8U *ftstring);
float string_to_float(INT8U *tempstr);
void collect_realdata(INT8U hoursave, INT8U daysave);
void ReportDaydata(INT8U smonth, INT8U sdate, INT8U emonth, INT8U edate);
void UploadHourdata(INT8U smonth, INT8U sdate, INT8U shour, INT8U emonth,
		INT8U edate, INT8U ehour);
void MemoryClear(void *pdes, INT16U size);
void MemoryCopy(INT8U *src, INT8U *des, INT16U len);
//void Save_Data(void);
void CRC_Calculation(INT8U *src, INT16U len, INT8U *des);
INT8U StrToASCII(INT8U *src, INT8U *des, INT16U len);
void AD_READ(void);
void ADCalculation(void);
void Delay_10_uS(void);

void ModataUpload(INT8U ModM);
void Mod_dealdata(INT8U *receive);
void Mod_Command(INT8U method);

void NH3_ModataUpload(INT8U ModM);
void dataparse_zhonglv(INT8U *buf);
void dataget_zhonglv(void);
void B01_ModataUpload(INT8U ModM);
void dataparse_jiubo(INT8U *buf);
void dataget_jiubo(void);

INT8U getkey(void);
void LCD_disp(void);
void init_lcd(void);
void delay11(unsigned int ms);
void disp_img(INT16U addr, INT8U xl, INT8U yl, const INT8U *img);
void clrram(void);
void index_initial(void);
void disp10(void);

void Progupdatemain(void);
extern void ClearFlashSection(void);
extern void WriteFlashSection(void);
extern void ChangeINTVector(void);
//extern void START(void);
extern void LCD_indexs(INT8U *Dnum, INT8U lenth, INT8U *L_ind);

void ReportAlarm(void);
void ReportAlarmRecord(INT8U *start, INT8U *end);
void Device_Status(void);

void dev_calibrate_sample(INT8U type);
//void dev_sample(void);
void dev_operate(void);
void dev_settimes(void);
void Reporthisdata_M(void);
void Reporthisdata_H(void);
void Reporthisdata_D(void);
void DevCalculation(void);
void UploadRealdata(INT8U sday, INT8U shour);
void CRC_Calculation_B(INT8U *src, INT16U len, INT8U *des);
void ADsimulate(void);
void AnalogDataStatistic(void);
#define Add_Send()  add_send();\
                    MemoryClear(CBAG.cbag_dynamic,sizeof(CBAG.cbag_dynamic))
#endif
