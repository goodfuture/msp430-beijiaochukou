#include <msp430xG46x.h>
#include "test.h"

#define DELAYNUM 2
void v_RTInputByte(INT8U ucDa);         //向实时时钟DS1302输入一个字节子程序
void v_W1302(INT8U ucAddr, INT8U ucDa);         //向实时时钟DS1302某寄存器写一个字节
INT8U uc_RTOutputByte(void);         //从实时时钟DS1302读取一个字节子程序
INT8U uc_R1302(INT8U ucAddr); //从实时时钟DS1302指定地址读取一个字节子程序
void v_Set1302(void); //设置实时时钟DS1302
void v_Get1302(void); //从实时时钟DS1302中读取时间
void delays(INT16U m);  //延时程序
/**********************************************************************************************************
 实时时钟时钟控制信号线定义
 **********************************************************************************************************/
/*————控制信号线定义————————*/
#ifdef MAINBOARD
#define RST10320  P2OUT&=~BIT5
#define RST10321  P2OUT|=BIT5
#define IO1032W   P2OUT&=~BIT4
#define IO1032R   P2OUT|=BIT4
#define CLK10320  P2OUT&=~BIT6
#define CLK10321  P2OUT|=BIT6

#define IO_IN     P2DIR&=~BIT4
#define IO_OUT    P2DIR|=BIT4

#define T_IO      P2IN&BIT4
#else
#define RST10320  P3OUT&=~BIT5
#define RST10321  P3OUT|=BIT5
#define IO1032W   P3OUT&=~BIT7
#define IO1032R   P3OUT|=BIT7
#define CLK10320  P3OUT&=~BIT6
#define CLK10321  P3OUT|=BIT6

#define IO_IN     P3DIR&=~BIT7
#define IO_OUT    P3DIR|=BIT7

#define T_IO      P3IN&BIT7
#endif
/*————变量定义————————*/
INT8U current_year; /*	年		*/
INT8U current_moth; /*	月		*/
INT8U current_date; /*	日		*/
INT8U current_hour; /*	小时	*/
INT8U current_minute; /*	分钟	*/
INT8U yestoday;
volatile INT8U current_second; /*	秒	*/
INT8U old_minute;
INT8U System_Time[15];
INT8U System_Time1[15] = "20080101000000\0";

void delays(INT16U m)
{
	INT16U n;
	n = 0;
	while (n < m) {
		n++;
	}
	return;
}
/*
 *********************************************************************************************************
 *                           实时时钟DS1302函数
 *	说 明：	实时时钟DS1302函数
 *参数说明：
 *		数据顺序：秒 分 时 日 月 星期 年
 *
 *********************************************************************************************************
 */
/*---------------------向实时时钟DS1302输入一个字节子程序------------------------*/
void v_RTInputByte(INT8U ucDa) //reentrant
{
	INT8U i;
	INT8U AC = ucDa;

	IO_OUT;
	delays(DELAYNUM);
	CLK10320; //;//T_CLK = 0;
	for (i = 8; i > 0; i--) /*八次循环*/
	{
		if ((AC & 0x01)) /*最低位是否==1*/
		{
			IO1032R; ////P4|=0x02;//T_IO = 1;			/*最低位=1*/
		} else {
			IO1032W; //;//T_IO = 0; 			/*最低位=0*/
		}
		//delays(DELAYNUM);
		CLK10321; //;//T_CLK = 1;
		delays(DELAYNUM);
		CLK10320; //;//T_CLK = 0;
		delays(DELAYNUM);
		AC = AC >> 1; /*等于向右移一位*/
	}
	//delays(DELAYNUM);
}
/*---------------------向实时时钟DS1302某寄存器写一个字节------------------------*/
void v_W1302(INT8U ucAddr, INT8U ucDa) // reentrant
{
	RST10320; //;//T_RST = 0;
	delays(DELAYNUM);
	CLK10320; //;//T_CLK = 0;
	delays(DELAYNUM);
	RST10321; //;//T_RST = 1;
	delays(DELAYNUM);
	v_RTInputByte(ucAddr); /* 写地址，命令 */
	v_RTInputByte(ucDa); /* 写1Byte数据*/
	CLK10320; //;//T_CLK = 0;
	delays(DELAYNUM);
	RST10320; //;//T_RST =0;
	delays(DELAYNUM);
}
/*---------------------从实时时钟DS1302读取一个字节子程序------------------------*/
INT8U uc_RTOutputByte(void) //reentrant
{
	INT8U i;
	INT8U AC;

	IO_IN;
	delays(DELAYNUM);
	for (i = 8; i > 0; i--) {
		AC = AC >> 1; /*等于向右移一位*/
		//x=P4;
		if ((T_IO) == 0) // T_IO == 0)
				{
			AC = AC & 0x7f;
		} else
			AC = AC | 0x80;
		//delays(DELAYNUM);
		CLK10321; //;//T_CLK = 1;
		delays(DELAYNUM);
		CLK10320; //;//T_CLK = 0;
		delays(DELAYNUM);

	}
	return (AC);
}
/*---------------------从实时时钟DS1302指定地址读取一个字节子程序------------------------*/
INT8U uc_R1302(INT8U ucAddr) //reentrant
{
	INT8U ucDa;

	RST10320; //;//T_RST = 0;
	delays(DELAYNUM);
	CLK10320; //;//T_CLK = 0;
	delays(DELAYNUM);
	RST10321; //;//T_RST = 1;
	v_RTInputByte(ucAddr); /* 地址，命令 */
	ucDa = uc_RTOutputByte(); /* 读1Byte数据 */
	CLK10321; //;//T_CLK = 1;
	delays(DELAYNUM);
	RST10320; //;//T_RST =0;
	delays(DELAYNUM);
	return (ucDa);
}
/*---------------------设置充电模式------------------------------*/
void v_charge1302(void)
{
	//INT8U ucAddr = 0x90;    //trickle charge

	v_W1302(0x8e, 0x00); /* 控制命令,WP=0,写操作 */
	v_W1302(0x90, 0xc5); //one diode,2K register Ima=(3.3-0.7)/2K ~1.2mA
	v_W1302(0x8e, 0x80); /* 控制命令,WP=1,写保护*/
}
/*---------------------设置实时时钟DS1302------------------------*/
void v_Set1302(void)	//reentrant
{
	INT8U i;
	INT8U hour, minute, second;
	INT8U year, moth, date;
	INT8U pSecDa[7];
	INT8U ucAddr = 0x80;

	year = ((System_Time1[2] << 4) & 0xf0) | (System_Time1[3] & 0x0f);
	moth = ((System_Time1[4] << 4) & 0xf0) | (System_Time1[5] & 0x0f);
	date = ((System_Time1[6] << 4) & 0xf0) | (System_Time1[7] & 0x0f);
	hour = ((System_Time1[8] << 4) & 0xf0) | (System_Time1[9] & 0x0f);
	minute = ((System_Time1[10] << 4) & 0xf0) | (System_Time1[11] & 0x0f);
	second = ((System_Time1[12] << 4) & 0xf0) | (System_Time1[13] & 0x0f);
	//current_moth=((System_Time1[2]<<4)&0xf0) |(System_Time1[2]&0x0f));

	/*current_year=07;
	 current_moth=07;
	 current_date=03;
	 hour = ( current_hour / 10 ) * 16 + current_hour%10;
	 hour = hour & 0x3f;
	 minute = ( current_minute / 10 ) * 16 + current_minute%10;
	 minute = minute & 0x7f;
	 year=( current_year / 10 ) * 16 + current_year%10;
	 moth=( current_moth / 10 ) * 16 + current_moth%10;
	 date=( current_date / 10 ) * 16 + current_date%10;
	 */
	/*********************不写当前秒*****************************
	 second = ( current_second / 10 ) * 16 + current_second%10;
	 second = second & 0x7f;

	 ************************************************************/
	//second = uc_R1302(0x81);/*读出当前秒*/
	second = second & 0x7f;
	/*****************************************************/
	pSecDa[0] = second;
	pSecDa[1] = minute;
	pSecDa[2] = hour;
	pSecDa[3] = date;
	pSecDa[4] = moth;
	pSecDa[6] = year;
	v_W1302(0x8e, 0x00); /* 控制命令,WP=0,写操作 */
	for (i = 0; i < 6; i++) {
		v_W1302(ucAddr, pSecDa[i]); /* 秒 分 时 日 月 星期 年 */
		ucAddr += 2;
	}
	v_W1302(ucAddr, pSecDa[6]); /* 秒 分 时 日 月 星期 年 */
	v_W1302(0x8e, 0x80); /* 控制命令,WP=1,写保护*/
}
/*---------------------从实时时钟DS1302中读取时间------------------------*/
//数据顺序：秒 分 时 日 月 星期 年
void v_Get1302(void) //reentrant
{
	INT8U ucCurtime[7];
	INT8U i;
	INT8U ucAddr = 0x81;

	for (i = 0; i < 7; i++) {
		ucCurtime[i] = uc_R1302(ucAddr);/*格式为: 秒 分 时 日 月 星期 年 */
		ucAddr += 2;
	}
	if (((ucCurtime[0] & 0x0f) > 9) || ((ucCurtime[0] & 0xf0) > 0x50)) {
		for (i = 0; i < 14; i++) {
			System_Time1[i] = System_Time[i];
		}
		v_Set1302();
		return;
	}
	System_Time[0] = 0x32;							//年的千位
	System_Time[1] = 0x30;							//年的百位
	System_Time[2] = (ucCurtime[6] >> 4) & 0x0f | 0x30;		//年的十位
	System_Time[3] = ucCurtime[6] & 0x0f | 0x30;				//年的个位
	System_Time[4] = (ucCurtime[4] >> 4) & 0x0f | 0x30;		//月的十位
	System_Time[5] = ucCurtime[4] & 0x0f | 0x30;				//月的个位
	System_Time[6] = (ucCurtime[3] >> 4) & 0x0f | 0x30;		//日的十位
	System_Time[7] = ucCurtime[3] & 0x0f | 0x30;				//日的个位
	System_Time[8] = (ucCurtime[2] >> 4) & 0x0f | 0x30;		//时的十位
	System_Time[9] = ucCurtime[2] & 0x0f | 0x30;				//时的个位
	System_Time[10] = (ucCurtime[1] >> 4) & 0x0f | 0x30;		//分的十位
	System_Time[11] = ucCurtime[1] & 0x0f | 0x30;			//分的个位
	System_Time[12] = (ucCurtime[0] >> 4) & 0x0f | 0x30;		//秒的十位
	System_Time[13] = ucCurtime[0] & 0x0f | 0x30;			//秒的个位

	System_Time[14] = '\0';
	ucCurtime[0] = ucCurtime[0] & 0x7f;
	current_second = (ucCurtime[0] >> 4) * 10 + (ucCurtime[0] & 0x0f);
	current_minute = (ucCurtime[1] >> 4) * 10 + (ucCurtime[1] & 0x0f);
	current_hour = (ucCurtime[2] >> 4) * 10 + (ucCurtime[2] & 0x0f);
	current_date = (ucCurtime[3] >> 4) * 10 + (ucCurtime[3] & 0x0f);
	current_moth = (ucCurtime[4] >> 4) * 10 + (ucCurtime[4] & 0x0f);
	current_year = (ucCurtime[6] >> 4) * 10 + (ucCurtime[6] & 0x0f);
}

