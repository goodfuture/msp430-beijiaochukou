#include  <msp430xG46x.h>
#include <string.h>
#include "define.h"
#include "test.h"
#include "zimo.h"

//14
INT8U index1[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 117, 118, 13, '\0' }; //欢迎		监控11 12
const INT8U index4[16] = { 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
		49, 49, '\0' }; //欢迎
const INT8U index2[3] = { 17, 85, '\0' }; //日期
const INT8U index3[3] = { 18, 62, '\0' }; //时间
const INT8U index5[6] = { 94, 29, 44, 30, 31, '\0' }; //请输入密码
const INT8U index7[5] = { 42, 43, 23, 24, '\0' }; //参数设置
const INT8U index8[5] = { 27, 28, 25, 26, '\0' }; //状态查看
const INT8U index9[3] = { 27, 28, '\0' }; //状态
INT8U index10[4] = { 22, 20, 0, '\0' }; //AD
INT8U index11[5] = { 111, 112, 23, 24, '\0' }; //系统设置
INT8U index29[4] = { 21, 19, 0, '\0' }; //DO
const INT8U index30[5] = { 36, 37, 38, 39, '\0' }; //菜单选项
const INT8U index31[4] = { 21, 20, 0, '\0' }; //DI
const INT8U index32[7] = { 94, 29, 44, 48, 30, 31, 0 };	//请输入新密码
const INT8U index33[2] = { 87, 88 }; //关开
const INT8U index34[5] = { 103, 104, 105, 106, 0 };	//成功
const INT8U index35[5] = { 23, 24, 107, 108, 0 };		//失败
const INT8U index36[7] = { 94, 34, 35, 48, 30, 31, 0 };	//请确认新密码
const INT8U index37[15] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 26, 17, 16, '\0' }; //数字'0~9' 'S,P,B'废气用
const INT8U index38[4] = { 18, 24, 25, '\0' };	//Pfk
const INT8U index39[3] = { 109, 110, '\0' };	//测试
const INT8U index40[3][9] = { { 1, 16, 14, 2, 1, 16, '\0' },       //0V-10V
		{ 1, 16, 14, 6, 16, '\0' },         //0V-5V
		{ 5, 23, 22, 14, 3, 1, 23, 22, '\0' }  //4mA-20mA
};
const INT8U index42[5] = { 90, 93, 95, 96, '\0' }; //仪器个数
const INT8U index45[3][4] = { { 19, 26, 26, '\0' },       //off
		{ 2, 3, 1, '\0' },         //30
		{ 3, 5, 1, '\0' }  //60
};
const INT8U index48[5][7] = { { 10, 7, 1, 1, '\0' },         //9600
		{ 6, 8, 7, 1, 1, '\0' },  //57600
		{ 2, 2, 6, 3, 1, 1, '\0' }, //115200
		{ 5, 9, 1, 1, '\0' },       //4800
		{ 2, 3, 1, 1, '\0' }       //1200
};
const INT8U index49[3][4] = { { 19, 26, 26, '\0' },       //OFF
		{ 29, 19, 21, '\0' },       //COD
		};

const INT8U index50[3] = { 68, 116, '\0' };       //通道

const INT8U index52[17] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 26, 17, 23, 24,
		16, '\0' };  //数字'0~9' 'S,P,B'废气用

const INT8U index53[5] = { 16, PROGTYPE + 1, VERSION + 1, SUBVERSION + 1, '\0' }; //版本信息
//const INT8U index53[5]={33,22,32,33,'\0'};//版本信息
const INT8U P1_index[5][5] = { { 111, 112, 30, 31, '\0' },  //系统密码
		{ 111, 112, 46, 47, '\0' },  //系统标识
		{ 111, 112, 18, 62, '\0' },  //系统时间
		{ 55, 56, 57, 43, '\0' },  //重发次数
		{ 111, 112, 65, 66, '\0' }  //系统编号
};

const INT8U P2_index[5][7] = { { 54, 18, 18, 62, '\0' },  //超时时间
		{ 61, 72, 18, 62, '\0' },  //报警时间
		{ 43, 64, 59, 61, 62, 63, '\0' },  //数据上报间隔
		{ 58, 18, 59, 61, 62, 63, '\0' },  //实时上报间隔
		{ 86, 87, 91, 92, '\0' }, //背光时间
		};

const INT8U P3_index[3][6] = {

{ 13, 21, 23, 24, '\0' }, //仪表设置
		{ 81, 82, 83, 84, '\0' }, //协议类型
		{ 68, 100, 69, 70, '\0' }, //通信速率
		};

const INT8U AI_index[6][6] = { { 100, 101, 73, 80, 14, '\0' }, //信号量范围
		{ 75, 76, 77, 65, 66, '\0' }, //污染物编号
		{ 73, 74, 59, 79, '\0' }, //量程上限
		{ 73, 74, 60, 79, '\0' }, //量程下限
		{ 61, 72, 59, 79, '\0' }, //报警上线
		{ 61, 72, 60, 79, '\0' }, //报警下限
		};

//const INT8U index54[8]={3,4,3,28,5,9,6,'\0'};//232/485
const INT8U index54[2][4] = { { 19, 26, 26, '\0' }, //off
		{ 32, 19, 21, '\0' } //cod
};
const INT8U index55[3] = { 23, 22, '\0' }; //设备
const INT8U index56[3] = { 119, 120, '\0' }; //串口
const INT8U index57[5] = { 27, 22, 31, 21, '\0' }; //BAUD
const INT8U index58[4] = { 127, 73, '\0' }; //流量
const INT8U index59[4] = { 36, 33, 4, '\0' }; //NH3

//INT8U LCD_EQU;
float MODBUS_EQU[6];
extern float B01datastore;
extern float NHdatastore;
//-----------------------------------------

/*
 INT8U Revers(INT8U data1)`
 {
 INT8U data2;
 data2=(((data1&0x01)<<7)+((data1&0x02)<<5)+((data1&0x04)<<3)+((data1&0x08)<<1)+((data1&0x10)>>1)+((data1&0x20)>>3)+((data1&0x40)>>5)+((data1&0x80)>>7));
 return(data2);
 }
 */
#define DB_WR(X)  P10OUT  =X
#define DB_RD(X)  P10DIR  &=0X00; RD_DB;X =P10IN;WR_DB;P10DIR |=0XFF
/*
 void DB_WR(INT8U data)
 {
 P9OUT  &= 0x03;
 P10OUT &= 0xFC;

 P9OUT |= ((data&0x04)<<5)+((data&0x08)<<3)+((data&0x10)<<1)+((data&0x20)>>1)+((data&0x40)>>3)+((data&0x80)>>5);
 P10OUT |= ((data&0x01)<<1)+((data&0x02)>>1);
 }
 */
/*
 INT8U DB_RD()
 {
 INT8U indata = 0;
 INT8U p9in,p10in;


 P9DIR  &= 0x03;
 P10DIR &= 0xFC;
 RD_DB;

 p9in = P9IN;
 p10in = P10IN;
 //indata = IOOUTPUTs[p8in];
 //indata = Revers(p8in);
 indata = ((p9in&0x04)<<5)+((p9in&0x08)<<3)+((p9in&0x10)<<1)+((p9in&0x20)>>1)+((p9in&0x40)>>3)+((p9in&0x80)>>5)+((p10in&0x01)<<1)+((p10in&0x02)>>1);


 P9DIR |= 0xFC;
 P10DIR |= 0x03;
 WR_DB;


 return(indata);
 }*/

void Delay_10_uS(void)
{
	char i = 20;
	while (i--)
		;
}

void delay11(unsigned int ms)
{
	unsigned int i, j;
	for (i = 0; i < ms; i++)
		for (j = 0; j < 500; j++)
			;
	//////WDTCN     = 0xA5;	//喂狗;
}

void wr_od(INT8U dat, INT8U comm)       //写一个数据和一个命令
{
	wr_data(dat);
	wr_comm(comm);
}

void wr_td(INT8U datl, INT8U dath, INT8U comm)  //写两个数据和一个命令
{
	wr_data(datl);
	wr_data(dath);
	wr_comm(comm);
}

void wr_xd(INT16U dat, INT8U comm)       //写一个16进制数据和一个命令
{
	INT8U datl, dath;
	datl = dat;
	dath = dat >> 8;
	wr_data(datl);
	wr_data(dath);
	wr_comm(comm);
}

void wr_auto(INT8U dat)               //自动写数据
{
	chk_busy(1);
	CD_0;               //cd=0;
	RD_1;               //rd=1;
	//data_ora=dat;
	DB_WR(dat);
	//P8OUT = Revers(dat);
	//P8OUT = IOOUTPUTs[dat];
	WR_0;  //wr=0;
	//Delay_10_uS();
	WR_1;  // wr=1;
}

void wr_comm(INT8U comm)       //写命令
{
	chk_busy(0);
	CD_1;       //cd=1;
	RD_0;       //rd=0;
	//data_ora=comm;
	//P8OUT = Revers(comm);
	DB_WR(comm);
	//P8OUT = IOOUTPUTs[comm];
	WR_0;  //wr=0;
	//Delay_10_uS();
	WR_1;  // wr=1;
}

void wr_data(INT8U dat)       //写数据
{
	chk_busy(0);
	CD_0;       //cd=0;
	RD_1;       //rd=1;
	//data_ora=dat;
	DB_WR(dat);
	//P8OUT = Revers(dat);
	//P8OUT = IOOUTPUTs[dat];
	WR_0;  //wr=0;
	//Delay_10_uS();
	WR_1;  //wr=1;
}

void chk_busy(INT8U autowr)    //测状态
{
	INT8U inbuf;
	//data_ora=0xff;
	DB_WR(0xff);
	//P8OUT = Revers(0xff);
	//P8OUT = IOOUTPUTs[0xff];
	CD_1;  //cd=1;
	WR_1;  //wr=1;
	RD_0;  //rd=0;
	DB_RD(inbuf);
	if (autowr) {
		//SFRPAGE = 0xf;
		while ((inbuf & 0x08) == 0)
			;
	} else {
		//SFRPAGE = 0xf;
		while (((inbuf & 0x01) == 0) || ((inbuf & 0x02) == 0))
			;
	}
	//Delay_10_uS();
	RD_1;  //rd=1;
}

void init_lcd(void)
{
	RST_0;  //rst=0;
	Delay_10_uS();
	RST_1;  //rst=1;
	//fs=0;
	CE_0;  //ce=0;
	WR_1;  //wr=1;
	RD_1;  //rd=1;
	wr_xd(addr_w, 0x40);                   //文本显示区首地址
	wr_xd(addr_t, 0x42);                   //图形显示区首地址
	wr_td(width, 0x00, 0x41);               //文本显示区宽度
	wr_td(width, 0x00, 0x43);               //图形显示区宽度
	wr_comm(0x81);                        //逻辑"异或"
	wr_td(0x02, 0x00, 0x22);                //CGRAM偏置地址设置
	//wr_comm(0x9c);                        //启用文本显示,启用图形显示
	wr_comm(0x98);
}

void clrram(void)
{
	INT8U i, j;
	INT8U inbuf;
	wr_xd(addr_t, 0x24);
//------------------------------------
	//SFRPAGE = 0xf;
	//data_ora=0xff;
	DB_WR(0xff);
	//P8OUT = Revers(0xff);
	//P8OUT = IOOUTPUTs[0xff];
	CD_1;    //cd=1;
	WR_1;    //wr=1;
	RD_0;    //rd=0;
	DB_RD(inbuf);
	while (1) {
		// SFRPAGE = 0xf;
		if ((inbuf & 0x03) == 0x03) {
			wr_comm(0xb0);
			break;
		}
	}
	//Delay_10_uS();
	RD_1;    // rd=1;
	//------------------------------------
	//wr_comm(0xb0);
	for (j = 0; j < 128; j++) {
		for (i = 0; i < width; i++)
			wr_auto(0x00);
	}

	//SFRPAGE = 0xf;
	//data_ora=0xff;
	DB_WR(0xff);
	//P8OUT = Revers(0xff);
	//P8OUT = IOOUTPUTs[0xff];
	CD_1;          //cd=1;
	WR_1;          //wr=1;
	RD_0;          //rd=0;
	DB_RD(inbuf);
	while (1) {
		//SFRPAGE = 0xf;
		if ((inbuf & 0x08) == 0x08) {
			wr_comm(0xb2);
			break;
		}
	}
	//Delay_10_uS();
	RD_1;          //rd=1;
}

void clrramBlock(INT8U X0, INT8U Y0, INT8U nbyte)
{
	INT8U j, k;
	INT16U addr;
	for (k = 0; k < nbyte; k++) {
		addr = addr_t + X0 + Y0 * 30 + k;
		for (j = 0; j < 16; j++) {

			wr_xd(addr + j * width, 0x24);
			wr_od(0x00, 0xc0);
		}
	}
}

void disp_chn1616_1(INT8U X0, INT8U Y0, INT8U index, INT8U PoN)
{
	INT8U i, j;
	INT16U addr;

	addr = addr_t + X0 + Y0 * 30;
	for (j = 0; j < 16; j++) {

		for (i = 0; i < 2; i++) {
			wr_xd(addr + j * width + i, 0x24);

			if (PoN)
				wr_od(zimo1616[index][i + 2 * j], 0xc0);
			else
				wr_od(~zimo1616[index][i + 2 * j], 0xc0);

		}

	}

}

void disp_chn1616(INT8U X0, INT8U Y0, const INT8U *index, INT8U PoN)
{
	INT8U i, j, k, m;
	INT16U addr;
	m = strlen(index);
	for (k = 0; k < m; k++) {
		addr = addr_t + X0 + Y0 * 30 + k * 2;
		for (j = 0; j < 16; j++) {
			for (i = 0; i < 2; i++) {
				wr_xd(addr + j * width + i, 0x24);

				if (PoN)
					wr_od(zimo1616[*index - 1][i + 2 * j], 0xc0);
				else
					wr_od(~zimo1616[*index - 1][i + 2 * j], 0xc0);

			}

		}
		index++;
	}
}

void disp_img(INT16U addr, INT8U xl, INT8U yl, const INT8U *img)
{
	INT8U i, j;
	for (j = 0; j < yl; j++) {
		for (i = 0; i < xl; i++) {
			wr_xd(addr + j * width + i, 0x24);
			wr_od(img[j * xl + i], 0xc0);

		}
	}
}

void disp_chn816_1(INT8U X0, INT8U Y0, INT8U index, INT8U PoN) //显示一个字符
{
	INT8U j;
	INT16U addr;
	addr = addr_t + X0 + Y0 * 30;
	for (j = 0; j < 16; j++) {

		wr_xd(addr + j * width, 0x24);

		if (PoN)
			wr_od(zimo816[index][j], 0xc0);
		else
			wr_od(~zimo816[index][j], 0xc0);
	}

}
/*----------------------显示一串字符--------------------------------------------*/
void disp_chn816(INT8U X0, INT8U Y0, const INT8U *index, INT8U PoN) //显示一串字符
{
	INT8U j, k, m;
	INT16U addr;
	m = strlen(index);
	for (k = 0; k < m; k++) {
		addr = addr_t + X0 + Y0 * 30 + k;
		for (j = 0; j < 16; j++) {

			wr_xd(addr + j * width, 0x24);

			if (PoN)
				wr_od(zimo816[*index - 1][j], 0xc0);
			else
				wr_od(~zimo816[*index - 1][j], 0xc0);

		}
		index++;
	}
}

void disp_yline(INT8U X0, INT8U Y0)
{
	INT8U a = 0x10, i;
	INT16U addr;
	addr = addr_t + X0;
	for (i = Y0; i < 128; i++) {
		wr_xd(addr + i * width, 0x24);
		wr_od(a, 0xc0);
	}
}

void disp_xline(INT8U Y0)
{
	INT8U a = 0xff, i;
	INT16U addr;
	addr = addr_t + Y0 * 30;
	for (i = 0; i < 30; i++) {
		wr_xd(addr + i, 0x24);
		wr_od(a, 0xc0);
	}
}

void LCD_indexs(INT8U *Dnum, INT8U lenth, INT8U *L_ind)
{
	INT8U i;
	for (i = 0; (i < lenth) && (*Dnum != 0); i++) {
		(*L_ind) = ((*Dnum) & 0x0f) + 1;
		L_ind++;
		Dnum++;
	}
	(*L_ind) = 0;

}

void disp10(void) //欢迎

{
	INT8U indexp[5];
	INT8U k;
	if (Symbol.LCD_deal) {
		Symbol.LCD_deal = 0;

		if (Symbol.LCD_Page_Change) {
			clrram();
			disp_chn1616(2, 35, index1, 1);
			disp_xline(52);
			disp_xline(54);
			disp_chn816(26, 55, index53, 1);

			disp_chn1616(8, 80, index2, 1);
			disp_chn1616(8, 98, index3, 1);
			disp_chn816_1(18, 80, 13, 1);
			disp_chn816_1(21, 80, 13, 1);
			disp_chn816_1(16, 98, 14, 1);
			disp_chn816_1(19, 98, 14, 1);
			//v_Get1302();
			Symbol.LCD_Page_Change = 0;
		} else if ((Symbol.LCD_T == 1) && (Symbol.LCD_Page_Change == 0)) {
			Symbol.LCD_T = 0;
			clrramBlock(14, 80, 4);
			clrramBlock(19, 80, 2);
			clrramBlock(22, 80, 2);
			clrramBlock(14, 98, 2);
			clrramBlock(17, 98, 2);
			clrramBlock(20, 98, 2);
		}
		for (k = 0; k < 4; k++)
			indexp[k] = (System_Time[k] & 0x0f) + 1;
		indexp[4] = 0;
		disp_chn816(14, 80, indexp, 1);

		for (k = 0; k < 2; k++)
			indexp[k] = (System_Time[k + 4] & 0x0f) + 1;
		indexp[2] = 0;
		disp_chn816(19, 80, indexp, 1);

		for (k = 0; k < 2; k++)
			indexp[k] = (System_Time[k + 6] & 0x0f) + 1;
		indexp[2] = 0;
		disp_chn816(22, 80, indexp, 1);

		for (k = 0; k < 2; k++)
			indexp[k] = (System_Time[k + 8] & 0x0f) + 1;
		indexp[2] = 0;
		disp_chn816(14, 98, indexp, 1);

		for (k = 0; k < 2; k++)
			indexp[k] = (System_Time[k + 10] & 0x0f) + 1;
		indexp[2] = 0;
		disp_chn816(17, 98, indexp, 1);

		for (k = 0; k < 2; k++)
			indexp[k] = (System_Time[k + 12] & 0x0f) + 1;
		indexp[2] = 0;
		disp_chn816(20, 98, indexp, 1);

	}
	switch (KeyV) {
	case 1:			//enter 进入参数设置
		LCD_page = 30;	//disp51_1();
		Symbol.LCD_deal = 1;
		break;
	case 2:			//enter 进入参数设置
		LCD_page = 30;	//disp51_1();
		Symbol.LCD_deal = 1;
		break;
	case 3:			//down 进入状态查看
		LCD_page = 30;			//disp3(1);
		Symbol.LCD_deal = 1;
		break;
	case 4:			//up
		LCD_page = 30;	//disp3(1);
		Symbol.LCD_deal = 1;
		break;
	case 5:
		LCD_page = 30;
		Symbol.LCD_deal = 1;
		break;
	case 6:
		LCD_page = 30;
		Symbol.LCD_deal = 1;
		break;
	default:
		break;
	}

}

void disp30() //菜单
{
	if (Symbol.LCD_deal) {
		Symbol.LCD_deal = 0;
		Menu_Select = 0;
		clrram();
		disp_chn1616(11, 30, index30, 1);
		disp_chn1616(11, 60, index8, 0);
		disp_chn1616(11, 80, index7, 1);
	}
	switch (KeyV) {
	case 1:
		if (Menu_Select == 0)
			LCD_page = 41;	//实时数据查看
		else
			LCD_page = 20;	//参数设置密码

		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;

		break;
	case 3:
		if (Menu_Select == 0) {
			clrramBlock(11, 60, 8);
			clrramBlock(11, 80, 8);
			disp_chn1616(11, 60, index8, 1);
			disp_chn1616(11, 80, index7, 0);

			Menu_Select = 1;
		} else {
			clrramBlock(11, 60, 8);
			clrramBlock(11, 80, 8);
			disp_chn1616(11, 60, index8, 0);
			disp_chn1616(11, 80, index7, 1);

			Menu_Select = 0;
		}

		break;
	case 4:
		if (Menu_Select == 0) {
			clrramBlock(11, 60, 8);
			clrramBlock(11, 80, 8);
			disp_chn1616(11, 60, index8, 1);
			disp_chn1616(11, 80, index7, 0);

			Menu_Select = 1;
		} else {
			clrramBlock(11, 60, 8);
			clrramBlock(11, 80, 8);
			disp_chn1616(11, 60, index8, 0);
			disp_chn1616(11, 80, index7, 1);

			Menu_Select = 0;
		}
		break;
	case 5:
		LCD_page = 10;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		break;
	default:
		break;

	}

}

void disp20()	//用户密码
{
	INT8U i;
	if (LCDSymbol.LCD_set == 0) {
		Symbol.LCD_deal = 0;
		clrram();
		disp_chn1616(10, 40, index5, 1);
		//disp_chn816_1(10,64,66,0);
		disp_chn816_1(10, 64, 12, 0);
		LCD_NumPos = 0;
		LCD_NoPt = 0;
		LCDSymbol.LCD_set = 1;
	}
	switch (KeyV) {
	case 1:			//enter 进入参数设置
		LCD_Temp[LCD_NumPos + 1] = 0;
		LCD_Temp[LCD_NumPos] = LCD_NoPt;
		for (i = 0; i < 6; i++)
			LCD_Temp[i] |= 0x30;
		if (strcmp(LCD_Temp, LCD_user_pw) == 0) {
			LCD_page = 50;
			Symbol.LCD_deal = 1;
			LCDSymbol.LCD_set = 0;
			Symbol.LCD_Page_Change = 1;
			Y_Pos = 0;
		} else {
			LCD_page = 20;
			Symbol.LCD_deal = 1;
			LCDSymbol.LCD_set = 0;
		}
		break;
	case 2:
		if (LCD_NumPos == 0)
			;
		else {
			clrramBlock(10 + LCD_NumPos, 64, 1);
			LCD_Temp[LCD_NumPos] = 11;
			//disp_chn816_1(10+LCD_NumPos,64,66,1);
			LCD_NumPos--;
			//LCD_Temp[LCD_NumPos]=LCD_NoPt;
			//LCD_NoPt=0;
			LCD_NoPt = LCD_Temp[LCD_NumPos];
			clrramBlock(10 + LCD_NumPos, 64, 1);
			disp_chn816_1(10 + LCD_NumPos, 64, LCD_NoPt, 0);
		}
		break;
	case 3:			//down 进入状态查看

		if (LCD_NoPt == 9)
			LCD_NoPt = 0;
		else
			LCD_NoPt++;
		clrramBlock(10 + LCD_NumPos, 64, 1);
		disp_chn816_1(10 + LCD_NumPos, 64, LCD_NoPt, 0);
		break;
	case 4:			//up
		if (LCD_NoPt == 0)
			LCD_NoPt = 9;
		else
			LCD_NoPt--;
		clrramBlock(10 + LCD_NumPos, 64, 1);
		disp_chn816_1(10 + LCD_NumPos, 64, LCD_NoPt, 0);
		break;
	case 5:
		LCD_page = 30;
		Symbol.LCD_deal = 1;
		LCDSymbol.LCD_set = 0;
		break;
	case 6:
		if (LCD_NumPos == 5)
			;
		else {
			clrramBlock(10 + LCD_NumPos, 64, 1);
			//disp_chn816_1(10+LCD_NumPos,64,66,1);
			disp_chn816_1(10 + LCD_NumPos, 64, 12, 1);
			LCD_Temp[LCD_NumPos] = LCD_NoPt;
			LCD_NumPos++;
			LCD_NoPt = 0;
			clrramBlock(10 + LCD_NumPos, 64, 1);
			disp_chn816_1(10 + LCD_NumPos, 64, 0, 0);
		}

		break;
	default:
		break;
	}
	//Symbol.LCD_deal=1;

}

void disp41()			//状态查看1DO
{
	INT8U i, j;
	if (Symbol.LCD_deal) {
		Symbol.LCD_deal = 0;
		if ((Symbol.LCD_DO == 0) || (Symbol.LCD_Page_Change)) {
			clrram();

			disp_yline(4, 0);

			disp_chn816_1(1, 15, 20, 0);   //DO
			disp_chn816_1(2, 15, 18, 0);

			disp_chn816_1(1, 35, 20, 1);   //DI
			disp_chn816_1(2, 35, 19, 1);

			disp_chn816_1(1, 55, 21, 1);   //AI
			disp_chn816_1(2, 55, 19, 1);

			disp_chn816_1(1, 75, 28, 1);   //EQU
			disp_chn816_1(2, 75, 29, 1);
			disp_chn816_1(3, 75, 30, 1);

			disp_chn816_1(1, 95, 33, 1);  //LOG
			disp_chn816_1(2, 95, 18, 1);
			disp_chn816_1(3, 95, 34, 1);
			//disp_chn816_1(3,60,1,1);

			//disp_chn816_1(1,80,21,1);
			//disp_chn816_1(2,80,19,1);
			//disp_chn816_1(3,80,2,1);
			//disp_chn1616(3,50,index9,1);
			disp_chn816(12, 3, index29, 1);
			disp_chn1616(14, 3, index9, 1);

			disp_chn816_1(6, 35, 1, 1);
			disp_chn816_1(12, 35, 2, 1);
			disp_chn816_1(18, 35, 3, 1);
			disp_chn816_1(24, 35, 4, 1);

			disp_chn816_1(6, 85, 5, 1);
			disp_chn816_1(12, 85, 6, 1);
			disp_chn816_1(18, 85, 7, 1);
			disp_chn816_1(24, 85, 8, 1);
			Symbol.LCD_Page_Change = 0;
		} else {
			for (i = 0; i < 4; i++) {
				clrramBlock(6 + 6 * i, 55, 2);
				clrramBlock(6 + 6 * i, 105, 2);
			}
			Symbol.LCD_DO = 0;
		}
		for (i = 0; i < 4; i++) {
			j = (RealData.R_D.DO >> i) & 0x01;
			if (j == 0)
				disp_chn1616_1(6 + 6 * i, 55, 87, 1);
			else
				disp_chn1616_1(6 + 6 * i, 55, 88, 1);
		}
		for (i = 0; i < 4; i++) {
			j = (RealData.R_D.DO >> (i + 4)) & 0x01;
			if (j == 0)
				disp_chn1616_1(6 + 6 * i, 105, 87, 1);
			else
				disp_chn1616_1(6 + 6 * i, 105, 88, 1);
		}
	}
	switch (KeyV) {
	case 3:			//down 进入DI状态查看
		LCD_page = 42;			//disp42();
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		break;
	case 4:        //up AD
		LCD_page = 45;        //disp42();
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		break;
	case 5:			//cancel 推出到菜单
		LCD_page = 30;
		Symbol.LCD_deal = 1;
		break;
	default:
		break;
	}

}

void disp42()			//状态查看2DI
{
	INT8U i, j, m;
	if (Symbol.LCD_deal) {
		Symbol.LCD_deal = 0;
		if ((Symbol.LCD_DI == 0) || (Symbol.LCD_Page_Change)) {
			clrram();
			disp_yline(4, 0);

			disp_chn816(12, 1, index31, 1);
			disp_chn1616(14, 1, index9, 1);

			disp_chn816_1(1, 15, 20, 1);   //DO
			disp_chn816_1(2, 15, 18, 1);

			disp_chn816_1(1, 35, 20, 0);   //DI
			disp_chn816_1(2, 35, 19, 0);

			disp_chn816_1(1, 55, 21, 1);   //AI
			disp_chn816_1(2, 55, 19, 1);

			disp_chn816_1(1, 75, 28, 1);   //EQU
			disp_chn816_1(2, 75, 29, 1);
			disp_chn816_1(3, 75, 30, 1);

			disp_chn816_1(1, 95, 33, 1);  //LOG
			disp_chn816_1(2, 95, 18, 1);
			disp_chn816_1(3, 95, 34, 1);
			//disp_chn816_1(3,60,1,1);

			//disp_chn816_1(1,80,21,1);
			//disp_chn816_1(2,80,19,1);
			//disp_chn816_1(3,80,2,1);
			// disp_chn1616(3,10,index9,0);
			disp_chn816_1(6, 20, 1, 1);
			disp_chn816_1(12, 20, 2, 1);
			disp_chn816_1(18, 20, 3, 1);
			disp_chn816_1(24, 20, 4, 1);

			disp_chn816_1(6, 46, 5, 1);
			disp_chn816_1(12, 46, 6, 1);
			disp_chn816_1(18, 46, 7, 1);
			disp_chn816_1(24, 46, 8, 1);

			disp_chn816_1(6, 72, 9, 1);
			disp_chn816_1(12, 72, 1, 1);
			disp_chn816_1(13, 72, 0, 1);
			disp_chn816_1(18, 72, 1, 1);
			disp_chn816_1(19, 72, 1, 1);
			disp_chn816_1(24, 72, 1, 1);
			disp_chn816_1(25, 72, 2, 1);

			disp_chn816_1(6, 98, 1, 1);
			disp_chn816_1(7, 98, 3, 1);
			disp_chn816_1(12, 98, 1, 1);
			disp_chn816_1(13, 98, 4, 1);
			disp_chn816_1(18, 98, 1, 1);
			disp_chn816_1(19, 98, 5, 1);
			disp_chn816_1(24, 98, 1, 1);
			disp_chn816_1(25, 98, 6, 1);

			Symbol.LCD_Page_Change = 0;
		} else {
			for (j = 0; j < 4; j++) {
				for (i = 0; i < 4; i++)
					clrramBlock(8 + 6 * i, 20 + j * 26, 2);
			}
			Symbol.LCD_DI = 0;
		}
		//disp_chn1616(3,30,index9,1);
		for (j = 0; j < 4; j++) {
			for (i = 0; i < 4; i++) {
				m = (RealData.R_D.DI[(3 - j) / 2] >> (i + (j % 2) * 4)) & 0x01;
				if (m == 0)
					disp_chn1616_1(8 + 6 * i, 20 + j * 26, 87, 1);
				else
					disp_chn1616_1(8 + 6 * i, 20 + j * 26, 88, 1);
			}
		}
	}
	switch (KeyV) {
	case 3:			//down AD
		LCD_page = 43;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		break;
	case 4:			//up DO
		LCD_page = 41;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		break;
	case 5:			//cancel 推出到菜单
		LCD_page = 30;
		Symbol.LCD_deal = 1;
		break;
	default:
		break;
	}

	//disp_chn1616(3,50,index9,1);
}

void disp43()			//状态查看3AD
{
	INT8U i, j;
	INT8U ftstring[18];
	//uchar ad[18];
	INT8U indexad[18];
	if ((Symbol.LCD_deal) || (Symbol.LCD_Page_Change)) {
		Symbol.LCD_deal = 0;
		if (Symbol.LCD_AD == 0) {
			Symbol.LCD_Page_Change = 0;
			clrram();
			disp_yline(4, 0);

			disp_chn816_1(1, 15, 20, 1);   //DO
			disp_chn816_1(2, 15, 18, 1);

			disp_chn816_1(1, 35, 20, 1);   //DI
			disp_chn816_1(2, 35, 19, 1);

			disp_chn816_1(1, 55, 21, 0);   //AI
			disp_chn816_1(2, 55, 19, 0);

			disp_chn816_1(1, 75, 28, 1);   //EQU
			disp_chn816_1(2, 75, 29, 1);
			disp_chn816_1(3, 75, 30, 1);

			disp_chn816_1(1, 95, 33, 1);  //LOG
			disp_chn816_1(2, 95, 18, 1);
			disp_chn816_1(3, 95, 34, 1);
			//disp_chn816_1(3,60,1,0);

			//disp_chn816_1(1,80,21,1);
			//disp_chn816_1(2,80,19,1);
			//	disp_chn816_1(3,80,2,1);

			for (i = 0; i < 8; i++) {
				index10[2] = i + 2;
				disp_chn816(5, 0 + i * 16, index10, 1);
				float_to_string(RealData.R_D.FF.ADF[i], ftstring);

				for (j = 0; j < 18; j++) {
					if (ftstring[j] == 0x2e)		//点
							{
						indexad[j] = 11;
					} else if (ftstring[j] == '\0') {
						indexad[j] = 0;
						break;
					} else
						indexad[j] = (ftstring[j] & 0x0f) + 1;
				}
				//disp_chn816(16,10+i*16,indexad,1);
				disp_chn816(10, 16 * i, indexad, 1);
			}
		} else {
			Symbol.LCD_AD = 0;
			for (i = 0; i < 8; i++) {
				clrramBlock(10, 16 * i, 13);
				float_to_string(RealData.R_D.FF.ADF[i], ftstring);

				for (j = 0; j < 18; j++) {
					if (ftstring[j] == 0x2e)		//点
							{
						indexad[j] = 11;
					} else if (ftstring[j] == '\0') {
						indexad[j] = 0;
						break;
					} else
						indexad[j] = (ftstring[j] & 0x0f) + 1;
				}
				//disp_chn816(16,10+i*16,indexad,1);
				disp_chn816(10, 16 * i, indexad, 1);
			}
		}

	}
	switch (KeyV) {
	case 3:			//down DO
		LCD_page = 44;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		break;
	case 4:			//up DI
		LCD_page = 42;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		break;
	case 5:			//cancel 推出到菜单
		LCD_page = 30;
		Symbol.LCD_deal = 1;
		break;
	default:
		break;
	}

	//disp_chn1616(3,50,index9,1);
}

void disp44()		//仪器仪表实时数据

{
	uchar j;
	unsigned char NP = 0;
	uchar indexad[18];
	INT8U ftstring[18];
	union {
		char a[4];
		float b;
	} Mod_D;

	if ((Symbol.LCD_deal) || (Symbol.LCD_Page_Change)) {
		Symbol.LCD_deal = 0;
		if (LCDSymbol.LCD_EQU == 0) {
			Symbol.LCD_Page_Change = 0;
			clrram();
			disp_yline(4, 0);

			disp_chn816_1(1, 15, 20, 1);   //DO
			disp_chn816_1(2, 15, 18, 1);

			disp_chn816_1(1, 35, 20, 1);   //DI
			disp_chn816_1(2, 35, 19, 1);

			disp_chn816_1(1, 55, 21, 1);   //AI
			disp_chn816_1(2, 55, 19, 1);

			disp_chn816_1(1, 75, 28, 0);   //EQU
			disp_chn816_1(2, 75, 29, 0);
			disp_chn816_1(3, 75, 30, 0);

			disp_chn816_1(1, 95, 33, 1);  //LOG
			disp_chn816_1(2, 95, 18, 1);
			disp_chn816_1(3, 95, 34, 1);

			//for(i=0;i<6;i++)
			{
				disp_chn816(6, 20, index54[1], 1);
				disp_chn816(6, 40, index59, 1);
				disp_chn1616(5, 60, index58, 1);
				//	disp_chn816_1(9,i*20,i+1,1);
			}

			//for(i=0;i<6;i++)
			{
				//index12[3]=i+2;
				//disp_chn816(5,0+i*16,index12,1);
				Mod_D.b = MODBUS_EQU[0];
				if ((Mod_D.a[3] & 0x80) == 0x80) {
					Mod_D.a[3] &= 0x7f;
					NP = 1;
				}
				float_to_string(Mod_D.b, ftstring);
				if (NP == 1) {
					indexad[0] = 14;
					NP = 0;
				} else
					indexad[0] = 12;

				for (j = 0; j < 18; j++) {
					if (ftstring[j] == 0x2e)				//点
							{
						indexad[j + 1] = 11;
					} else if (ftstring[j] == '\0') {
						indexad[j + 1] = 0;
						break;
					} else
						indexad[j + 1] = (ftstring[j] & 0x0f) + 1;
				}
				//disp_chn816(16,10+i*16,indexad,1);
				disp_chn816(12, 20, indexad, 1);

				Mod_D.b = NHdatastore;
				if ((Mod_D.a[3] & 0x80) == 0x80) {
					Mod_D.a[3] &= 0x7f;
					NP = 1;
				}
				float_to_string(Mod_D.b, ftstring);
				if (NP == 1) {
					indexad[0] = 14;
					NP = 0;
				} else
					indexad[0] = 12;

				for (j = 0; j < 18; j++) {
					if (ftstring[j] == 0x2e)				//点
							{
						indexad[j + 1] = 11;
					} else if (ftstring[j] == '\0') {
						indexad[j + 1] = 0;
						break;
					} else
						indexad[j + 1] = (ftstring[j] & 0x0f) + 1;
				}
				//disp_chn816(16,10+i*16,indexad,1);
				disp_chn816(12, 40, indexad, 1);

				Mod_D.b = B01datastore;
				if ((Mod_D.a[3] & 0x80) == 0x80) {
					Mod_D.a[3] &= 0x7f;
					NP = 1;
				}
				float_to_string(Mod_D.b, ftstring);
				if (NP == 1) {
					indexad[0] = 14;
					NP = 0;
				} else
					indexad[0] = 12;

				for (j = 0; j < 18; j++) {
					if (ftstring[j] == 0x2e)				//点
							{
						indexad[j + 1] = 11;
					} else if (ftstring[j] == '\0') {
						indexad[j + 1] = 0;
						break;
					} else
						indexad[j + 1] = (ftstring[j] & 0x0f) + 1;
				}
				//disp_chn816(16,10+i*16,indexad,1);
				disp_chn816(12, 60, indexad, 1);
			}

		} else {
			LCDSymbol.LCD_EQU = 0;

			// for(i=0;i<6;i++)
			{
				clrramBlock(12, 20, 13);
				clrramBlock(12, 40, 13);
				clrramBlock(12, 60, 13);
				Mod_D.b = MODBUS_EQU[0];
				if ((Mod_D.a[3] & 0x80) == 0x80) {
					Mod_D.a[3] &= 0x7f;
					NP = 1;
				}
				float_to_string(Mod_D.b, ftstring);
				if (NP == 1) {
					NP = 0;
					indexad[0] = 14;
				} else
					indexad[0] = 12;

				for (j = 0; j < 18; j++) {
					if (ftstring[j] == 0x2e)				//点
							{
						indexad[j + 1] = 11;
					} else if (ftstring[j] == '\0') {
						indexad[j + 1] = 0;
						break;
					} else
						indexad[j + 1] = (ftstring[j] & 0x0f) + 1;
				}
				//disp_chn816(16,10+i*16,indexad,1);
				disp_chn816(12, 20, indexad, 1);
			}
			Mod_D.b = NHdatastore;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP == 1) {
				indexad[0] = 14;
				NP = 0;
			} else
				indexad[0] = 12;

			for (j = 0; j < 18; j++) {
				if (ftstring[j] == 0x2e)				//点
						{
					indexad[j + 1] = 11;
				} else if (ftstring[j] == '\0') {
					indexad[j + 1] = 0;
					break;
				} else
					indexad[j + 1] = (ftstring[j] & 0x0f) + 1;
			}
			//disp_chn816(16,10+i*16,indexad,1);
			disp_chn816(12, 40, indexad, 1);

			Mod_D.b = B01datastore;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP == 1) {
				indexad[0] = 14;
				NP = 0;
			} else
				indexad[0] = 12;

			for (j = 0; j < 18; j++) {
				if (ftstring[j] == 0x2e)				//点
						{
					indexad[j + 1] = 11;
				} else if (ftstring[j] == '\0') {
					indexad[j + 1] = 0;
					break;
				} else
					indexad[j + 1] = (ftstring[j] & 0x0f) + 1;
			}
			//disp_chn816(16,10+i*16,indexad,1);
			disp_chn816(12, 60, indexad, 1);

		}

	}
	switch (KeyV) {
	case 3:			//down DO
		LCD_page = 45;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		//for(i=0;i<6;i++)
		//MODBUS_EQU[i]=0;
		break;
	case 4:			//up DI
		LCD_page = 43;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		//for(i=0;i<6;i++)
		//MODBUS_EQU[i]=0;
		break;
	case 5:			//cancel 推出到菜单
		LCD_page = 30;
		Symbol.LCD_deal = 1;
		//for(i=0;i<6;i++)
		//MODBUS_EQU[i]=0;
		break;
	default:
		break;
	}

}

void disp45()
{
	uchar indextmp[18], j;
	uchar indextmp1[5] = { 121, 122, 18, 62, 0 };
	uchar indextmp2[5] = { 123, 124, 18, 62, 0 };
	uchar indextmp3[5] = { 125, 126, 18, 62, 0 };
	uchar ftstring[18];
	if ((Symbol.LCD_deal) || (Symbol.LCD_Page_Change)) {
		Symbol.LCD_deal = 0;
		if (LCDSymbol.LCD_LOG == 0) {
			Symbol.LCD_Page_Change = 0;
			clrram();
			disp_yline(4, 0);

			disp_chn816_1(1, 15, 20, 1);   //DO
			disp_chn816_1(2, 15, 18, 1);

			disp_chn816_1(1, 35, 20, 1);   //DI
			disp_chn816_1(2, 35, 19, 1);

			disp_chn816_1(1, 55, 21, 1);   //AI
			disp_chn816_1(2, 55, 19, 1);

			disp_chn816_1(1, 75, 28, 1);   //EQU
			disp_chn816_1(2, 75, 29, 1);
			disp_chn816_1(3, 75, 30, 1);

			disp_chn816_1(1, 95, 33, 0);  //LOG
			disp_chn816_1(2, 95, 18, 0);
			disp_chn816_1(3, 95, 34, 0);

			//disp_chn816(5,20,index54,1);
			disp_chn1616(5, 15, indextmp1, 1);
			disp_chn1616(5, 35, indextmp2, 1);
			disp_chn1616(5, 55, indextmp3, 1);

			for (j = 0; j < 14; j++)
				indextmp[j] = (RunLog.OFFtime[j] & 0x0f) + 1;
			indextmp[14] = 0;
			disp_chn816(14, 15, indextmp, 1);

			for (j = 0; j < 14; j++)
				indextmp[j] = (RunLog.ONtime[j] & 0x0f) + 1;
			indextmp[14] = 0;
			disp_chn816(14, 35, indextmp, 1);

			float_to_string(RunLog.acctime, ftstring);
			for (j = 0; j < 18; j++) {
				if (ftstring[j] == 0x2e)  //点
						{
					indextmp[j] = 11;
				} else if (ftstring[j] == '\0') {
					indextmp[j] = 0;
					break;
				} else
					indextmp[j] = (ftstring[j] & 0x0f) + 1;
			}
			disp_chn816(14, 55, indextmp, 1);

		} else {
			LCDSymbol.LCD_LOG = 0;
			clrramBlock(14, 55, 14);
			float_to_string(RunLog.acctime, ftstring);
			for (j = 0; j < 18; j++) {
				if (ftstring[j] == 0x2e)  //点
						{
					indextmp[j] = 11;
				} else if (ftstring[j] == '\0') {
					indextmp[j] = 0;
					break;
				} else
					indextmp[j] = (ftstring[j] & 0x0f) + 1;
			}
			disp_chn816(14, 55, indextmp, 1);
		}
	}
	switch (KeyV) {
	case 3:			//down DO
		LCD_page = 41;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		break;
	case 4:			//up DI
		LCD_page = 44;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		break;
	case 5:			//cancel 推出到菜单
		LCD_page = 30;
		Symbol.LCD_deal = 1;
		break;
	default:
		break;
	}
}

void disp_SetNum_5x(INT8U Numlenth)
{
	INT8U j;
	//i=LCD_page%10;	
	switch (KeyV) {
	case 1:
		LCDSymbol.LCD_set = 0;
		Symbol.LCD_para_set = 1;
		Par_Select = 1;
		LCD_Temp[LCD_NumPos] = LCD_NoPt;
		LCD_Temp[Numlenth] = 0;

		//k=LCD_page/10;
		//Symbol.LCD_para_set=1;
		switch (Y_Pos) {
		case 0:
			;
			/*
			 for(j=0;j<6;j++)
			 {
			 LCD_user_pw[j]=LCD_Temp[j]|0x30;
			 parameter.sys_parameter.pw[j]=LCD_user_pw[j];
			 }*/
			break;
		case 1:
			for (j = 0; j < 14; j++)
				parameter.sys_parameter.mn[j] = (LCD_Temp[j] | 0x30);
			break;
		case 2:
			for (j = 0; j < 14; j++)
				System_Time1[j] = (LCD_Temp[j] | 0x30);
			v_Set1302();
			break;
		case 3:
			for (j = 0; j < 2; j++)
				parameter.sys_parameter.resendtime[j] = (LCD_Temp[j] | 0x30);
			break;
		case 4:
			for (j = 0; j < 2; j++)
				parameter.sys_parameter.st[j] = (LCD_Temp[j] | 0x30);
			break;
		default:
			break;
		}
		for (j = 0; j < Numlenth; j++) {
			LCD_Temp[j] += 1;
			LCD_index1[Y_Pos][j] = LCD_Temp[j];
		}
		disp_chn816(15, 29 + Y_Pos * 18, LCD_Temp, 1);
		break;
	case 2:
		LCD_Temp[LCD_NumPos] = LCD_NoPt;
		clrramBlock(15 + LCD_NumPos, 29 + Y_Pos * 18, 1);
		disp_chn816_1(15 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 1);
		if (LCD_NumPos == 0)
			LCD_NumPos = Numlenth - 1;
		else
			LCD_NumPos--;
		clrramBlock(15 + LCD_NumPos, 29 + Y_Pos * 18, 1);
		LCD_NoPt = LCD_Temp[LCD_NumPos];
		disp_chn816_1(15 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 0);
		break;
	case 3:
		//LCD_Temp[LCD_NumPos]=(LCD_NoPt|0x30);
		clrramBlock(15 + LCD_NumPos, 29 + Y_Pos * 18, 1);
		if (LCD_NoPt == 9)
			LCD_NoPt = 0;
		else
			LCD_NoPt++;
		disp_chn816_1(15 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 0);
		break;
	case 4:
		//LCD_Temp[LCD_NumPos]=(LCD_NoPt|0x30);
		if (LCD_NoPt == 0)
			LCD_NoPt = 9;
		else
			LCD_NoPt--;
		clrramBlock(15 + LCD_NumPos, 29 + Y_Pos * 18, 1);
		disp_chn816_1(15 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 0);
		break;
	case 5:
		disp_chn816(15, 29 + Y_Pos * 18, LCD_index1[Y_Pos], 1);
		LCD_NoPt = 0;
		LCD_NumPos = 0;
		LCDSymbol.LCD_set = 0;
		Par_Select = 1;
		break;
	case 6:
		LCD_Temp[LCD_NumPos] = LCD_NoPt;
		clrramBlock(15 + LCD_NumPos, 29 + Y_Pos * 18, 1);
		disp_chn816_1(15 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 1);

		if (LCD_NumPos == (Numlenth - 1))
			LCD_NumPos = 0;
		else
			LCD_NumPos++;
		LCD_NoPt = LCD_Temp[LCD_NumPos];
		clrramBlock(15 + LCD_NumPos, 29 + Y_Pos * 18, 1);
		disp_chn816_1(15 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 0);
		break;
	default:
		break;
	}
}

void disp50()
{

	INT8U *p;
	INT8U i;

	if (Symbol.LCD_deal) {
		clrram();
		Symbol.LCD_deal = 0;

		disp_xline(27);
		disp_yline(3, 28);

		disp_chn816_1(0, 29, 1, 0);			//1页
		disp_chn1616_1(1, 29, 101, 0);
		disp_chn816_1(0, 47, 2, 1);			//2页
		disp_chn1616_1(1, 47, 101, 1);
		disp_chn816_1(0, 65, 3, 1);			//2页
		disp_chn1616_1(1, 65, 101, 1);

		p = index11 + 2;
		disp_chn816_1(21, 7, 20, 1); //DO
		disp_chn816_1(22, 7, 18, 1);
		disp_chn1616(23, 7, index39, 1);

		disp_chn816(3, 7, index10, 1); //AD
		disp_chn1616(5, 7, p, 1);

		disp_chn1616(11, 7, index11, 0); //系统设置

		disp_chn1616(4, 29, P1_index[0], 1);
		disp_chn1616(4, 47, P1_index[1], 1);
		disp_chn1616(4, 65, P1_index[2], 1);
		disp_chn1616(4, 83, P1_index[3], 1);
		disp_chn1616(4, 101, P1_index[4], 1);
		//LCD_indexs(System_Time,14,LCD_index1[2]);					//系统时间值 14位

		for (i = 0; i < 6; i++)
			disp_chn816_1(15 + i, 29, 12, 1);

		disp_chn816(15, 47, LCD_index1[1], 1);

		LCD_indexs(System_Time, 14, LCD_index1[2]);
		disp_chn816(15, 65, LCD_index1[2], 1);

		//LCD_indexs(parameter.sys_parameter.resendtime,2,LCD_index1[3]);	//重发次数 2位
		disp_chn816(15, 83, LCD_index1[3], 1);

		disp_chn816(15, 101, LCD_index1[4], 1);

	}

	if (LCDSymbol.LCD_set) {
		//LCD_set=0;
		if (Y_Pos == 1)
			Numlenth = 14;
		else if (Y_Pos == 2)
			Numlenth = 14;
		else if (Y_Pos == 3)
			Numlenth = 2;
		else if (Y_Pos == 4)
			Numlenth = 2;

		disp_SetNum_5x(Numlenth);
	} else if (Par_Select) {
		//Par_Select=0;

		switch (KeyV) {
		case 1:
			Par_Select = 0;
			if (Y_Pos == 0) {
				LCD_page = 56;	//密码设置
				Symbol.LCD_deal = 1;
			} else {
				LCDSymbol.LCD_set = 1;
				LCD_NoPt = LCD_index1[Y_Pos][0] - 1;
				for (i = 0; i < 14; i++)
					LCD_Temp[i] = LCD_index1[Y_Pos][i] - 1;
				LCD_NumPos = 0;
				clrramBlock(15, 29 + Y_Pos * 18, 1);
				disp_chn816_1(15, 29 + Y_Pos * 18, LCD_NoPt, 0);
			}
			break;
		case 3:
			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 4)
				Y_Pos = 0;
			else
				Y_Pos++;

			clrramBlock(4, 29 + pre_Y_Pos * 18, 8);
			disp_chn1616(4, 29 + pre_Y_Pos * 18, P1_index[pre_Y_Pos], 1);

			clrramBlock(4, 29 + Y_Pos * 18, 8);
			disp_chn1616(4, 29 + Y_Pos * 18, P1_index[Y_Pos], 0);

			break;
		case 4:
			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 0)
				Y_Pos = 4;
			else
				Y_Pos--;

			clrramBlock(4, 29 + pre_Y_Pos * 18, 8);
			disp_chn1616(4, 29 + pre_Y_Pos * 18, P1_index[pre_Y_Pos], 1);

			clrramBlock(4, 29 + Y_Pos * 18, 8);
			disp_chn1616(4, 29 + Y_Pos * 18, P1_index[Y_Pos], 0);
			break;
		case 5:
			clrramBlock(4, 29 + Y_Pos * 18, 8);
			disp_chn1616(4, 29 + Y_Pos * 18, P1_index[Y_Pos], 1);
			Y_Pos = 0;
			Par_Select = 0;
			break;
		default:
			break;
		}
	} else {
		switch (KeyV) {
		case 1:
			Par_Select = 1;
			Y_Pos = 0;
			clrramBlock(4, 29, 8);
			disp_chn1616(4, 29, P1_index[0], 0);
			break;
		case 2:
			LCD_page = 70;	//Do设置
			Symbol.LCD_deal = 1;
			break;
		case 3:
			LCD_page = 60;	//设置2页
			Symbol.LCD_deal = 1;
			Y_Pos = 0;
			break;
		case 4:
			LCD_page = 100;	//设置3页
			Symbol.LCD_deal = 1;
			Y_Pos = 0;
			break;
		case 5:
			LCD_page = 30;	//回菜单
			Symbol.LCD_deal = 1;
			break;
		case 6:				//AD设置
			LCD_page = 90;
			LCD_NumPos = 0;
			LCD_DOP = 0;
			Symbol.LCD_deal = 1;
			Y_Pos = 0;
			break;
		default:
			break;
		}
	}

}

void disp56()	//密码修改
{
	INT8U i;
	if (Symbol.LCD_deal) {
		Symbol.LCD_deal = 0;
		clrram();
		disp_chn1616(10, 40, index32, 1);
		//disp_chn816_1(10,64,66,0);
		disp_chn816_1(10, 64, 12, 0);
		LCD_NumPos = 0;
		LCD_NoPt = 0;
		LCDSymbol.LCD_set = 1;
	}
	switch (KeyV) {
	case 1:			//enter 进入参数设置
		LCD_Temp[LCD_NumPos + 1] = 0;
		LCD_Temp[LCD_NumPos] = LCD_NoPt;
		for (i = 0; i < 6; i++)
			LCD_Temp[i] |= 0x30;
		LCD_page = 57;
		Symbol.LCD_deal = 1;
		break;
	case 2:
		if (LCD_NumPos == 0)
			;
		else {
			clrramBlock(10 + LCD_NumPos, 64, 1);
			LCD_Temp[LCD_NumPos] = 11;
			//disp_chn816_1(10+LCD_NumPos,64,66,1);
			LCD_NumPos--;
			//LCD_Temp[LCD_NumPos]=LCD_NoPt;
			//LCD_NoPt=0;
			LCD_NoPt = LCD_Temp[LCD_NumPos];
			clrramBlock(10 + LCD_NumPos, 64, 1);
			disp_chn816_1(10 + LCD_NumPos, 64, LCD_NoPt, 0);
		}
		break;
	case 3:			//down 进入状态查看

		if (LCD_NoPt == 9)
			LCD_NoPt = 0;
		else
			LCD_NoPt++;
		clrramBlock(10 + LCD_NumPos, 64, 1);
		disp_chn816_1(10 + LCD_NumPos, 64, LCD_NoPt, 0);
		break;
	case 4:			//up
		if (LCD_NoPt == 0)
			LCD_NoPt = 9;
		else
			LCD_NoPt--;
		clrramBlock(10 + LCD_NumPos, 64, 1);
		disp_chn816_1(10 + LCD_NumPos, 64, LCD_NoPt, 0);
		break;
	case 5:
		LCD_page = 50;
		Symbol.LCD_deal = 1;
		LCDSymbol.LCD_set = 0;
		Symbol.LCD_Page_Change = 1;
		Y_Pos = 0;
		break;
	case 6:
		if (LCD_NumPos == 5)
			;
		else {
			clrramBlock(10 + LCD_NumPos, 64, 1);
			//disp_chn816_1(10+LCD_NumPos,64,66,1);
			disp_chn816_1(10 + LCD_NumPos, 64, 12, 1);
			LCD_Temp[LCD_NumPos] = LCD_NoPt;
			LCD_NumPos++;
			LCD_NoPt = 0;
			clrramBlock(10 + LCD_NumPos, 64, 1);
			disp_chn816_1(10 + LCD_NumPos, 64, 0, 0);
		}
		break;
	default:
		break;
	}

}

void disp57()
{
	INT8U i;
	if (Symbol.LCD_deal) {
		Symbol.LCD_deal = 0;
		clrram();
		disp_chn1616(10, 40, index36, 1);
		//disp_chn816_1(10,64,66,0);
		disp_chn816_1(10, 64, 12, 0);
		LCD_NumPos = 0;
		LCD_NoPt = 0;
		LCDSymbol.LCD_set = 1;
	}
	switch (KeyV) {
	case 1:			//enter 进入参数设置
		LCD_comfirm[LCD_NumPos + 1] = 0;
		LCD_comfirm[LCD_NumPos] = LCD_NoPt;
		for (i = 0; i < 6; i++)
			LCD_comfirm[i] |= 0x30;
		if (strcmp(LCD_comfirm, LCD_Temp) == 0) {
			LCD_page = 58;
			Symbol.LCD_deal = 1;
			LCDSymbol.LCD_set = 1;

		} else {
			LCD_page = 58;
			Symbol.LCD_deal = 1;
			LCDSymbol.LCD_set = 0;
		}
		break;
	case 2:
		if (LCD_NumPos == 0)
			;
		else {
			clrramBlock(10 + LCD_NumPos, 64, 1);
			LCD_comfirm[LCD_NumPos] = 11;
			//disp_chn816_1(10+LCD_NumPos,64,66,1);
			LCD_NumPos--;
			//LCD_Temp[LCD_NumPos]=LCD_NoPt;
			//LCD_NoPt=0;
			LCD_NoPt = LCD_comfirm[LCD_NumPos];
			clrramBlock(10 + LCD_NumPos, 64, 1);
			disp_chn816_1(10 + LCD_NumPos, 64, LCD_NoPt, 0);
		}
		break;
	case 3:			//down 进入状态查看

		if (LCD_NoPt == 9)
			LCD_NoPt = 0;
		else
			LCD_NoPt++;
		clrramBlock(10 + LCD_NumPos, 64, 1);
		disp_chn816_1(10 + LCD_NumPos, 64, LCD_NoPt, 0);
		break;
	case 4:			//up
		if (LCD_NoPt == 0)
			LCD_NoPt = 9;
		else
			LCD_NoPt--;
		clrramBlock(10 + LCD_NumPos, 64, 1);
		disp_chn816_1(10 + LCD_NumPos, 64, LCD_NoPt, 0);
		break;
	case 5:
		LCD_page = 50;
		Symbol.LCD_deal = 1;
		LCDSymbol.LCD_set = 0;
		Symbol.LCD_Page_Change = 1;
		Y_Pos = 0;
		break;
	case 6:
		if (LCD_NumPos == 5)
			;
		else {
			clrramBlock(10 + LCD_NumPos, 64, 1);
			//disp_chn816_1(10+LCD_NumPos,64,66,1);
			disp_chn816_1(10 + LCD_NumPos, 64, 12, 1);
			LCD_comfirm[LCD_NumPos] = LCD_NoPt;
			LCD_NumPos++;
			LCD_NoPt = 0;
			clrramBlock(10 + LCD_NumPos, 64, 1);
			disp_chn816_1(10 + LCD_NumPos, 64, 0, 0);
		}

		break;
	default:
		break;
	}
}

void disp58()	//密码状态
{
	INT8U i;
	clrram();
	if (LCDSymbol.LCD_set) {
		LCDSymbol.LCD_set = 0;
		disp_chn1616(10, 56, index34, 1);
		for (i = 0; i < 6; i++) {
			LCD_user_pw[i] = LCD_comfirm[i];
			parameter.sys_parameter.pw[i] = LCD_user_pw[i];
		}

		LCD_page = 50;
		Symbol.LCD_para_set = 1;
		Symbol.LCD_Page_Change = 1;
		Y_Pos = 0;
	} else {
		disp_chn1616(10, 56, index35, 1);
		LCD_page = 56;
	}
	delay11(400);
	Symbol.LCD_deal = 1;
}

void disp_SetNum_6x(INT8U Numlenth)
{
	INT8U j;
	//i=LCD_page%10;
	switch (KeyV) {
	case 1:
		LCDSymbol.LCD_set = 0;
		LCD_Temp[LCD_NumPos] = index37[LCD_NoPt];

		LCD_Temp[Numlenth] = 0;

		//k=LCD_page/10;
		Par_Select = 1;
		Symbol.LCD_para_set = 1;
		switch (Y_Pos) {
		case 0:
			for (j = 0; j < 5; j++)
				parameter.sys_parameter.overtime[j] = (LCD_Temp[j] | 0x30);
			break;
		case 1:
			for (j = 0; j < 5; j++)
				parameter.sys_parameter.warntime[j] = (LCD_Temp[j] | 0x30);
			break;

		case 2:
			for (j = 0; j < 4; j++)
				parameter.sys_parameter.reporttime[j] = (LCD_Temp[j] | 0x30);
			break;
		case 3:
			for (j = 0; j < 3; j++)
				parameter.sys_parameter.rd_interval[j] = (LCD_Temp[j] | 0x30);
			Symbol.rd_change = 1;
			break;
		case 4:
			//parameter.sys_parameter.PO_Type=LCD_NoPt;
			parameter.sys_parameter.LCD_Backtime = LCD_NoPt;
			break;
		default:
			break;
		}
		if (Y_Pos != 4) {
			for (j = 0; j < Numlenth; j++) {
				LCD_Temp[j] += 1;
				LCD_index2[Y_Pos][j] = LCD_Temp[j];
			}
			disp_chn816(18, 29 + Y_Pos * 18, LCD_Temp, 1);
		} else {
			//clrramBlock(18,101,5);
			//disp_chn1616(18,101,index49[parameter.sys_parameter.PO_Type],1);

			clrramBlock(18, 101, 4);
			disp_chn816(18, 101, index45[LCD_NoPt], 1);
			//LCD_page=200;	//通道设置
			//Symbol.LCD_deal=1;

		}

		break;
	case 2:
		if (Y_Pos == 4) {

			;
		} else {
			LCD_Temp[LCD_NumPos] = LCD_NoPt;
			clrramBlock(18 + LCD_NumPos, 29 + Y_Pos * 18, 1);
			disp_chn816_1(18 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 1);
			if (LCD_NumPos == 0)
				;              //LCD_NumPos=Numlenth-1;
			else
				LCD_NumPos--;
			clrramBlock(18 + LCD_NumPos, 29 + Y_Pos * 18, 1);
			LCD_NoPt = LCD_Temp[LCD_NumPos];
			disp_chn816_1(18 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 0);
		}
		break;
	case 3:
		//LCD_Temp[LCD_NumPos]=(LCD_NoPt|0x30);
		if (Y_Pos == 4) {

			clrramBlock(18, 101, 4);
			if (LCD_NoPt == 2)
				LCD_NoPt = 0;
			else
				LCD_NoPt++;
			disp_chn816(18, 101, index45[LCD_NoPt], 0);

		} else {
			clrramBlock(18 + LCD_NumPos, 29 + Y_Pos * 18, 1);
			if (LCD_NoPt == 9)
				LCD_NoPt = 0;
			else
				LCD_NoPt++;
			disp_chn816_1(18 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 0);
		}
		break;
	case 4:
		//LCD_Temp[LCD_NumPos]=(LCD_NoPt|0x30);
		if (Y_Pos == 4) {
			clrramBlock(18, 101, 4);
			if (LCD_NoPt == 0)
				LCD_NoPt = 2;
			else
				LCD_NoPt--;
			disp_chn816(18, 101, index45[LCD_NoPt], 0);
		} else {
			if (LCD_NoPt == 0)
				LCD_NoPt = 9;
			else
				LCD_NoPt--;
			clrramBlock(18 + LCD_NumPos, 29 + Y_Pos * 18, 1);
			disp_chn816_1(18 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 0);
		}
		break;
	case 5:
		//LCD_page=Pre_LCD_page;
		if (Y_Pos != 4) {
			disp_chn816(18, 29 + Y_Pos * 18, LCD_index2[Y_Pos], 1);
			LCD_NoPt = 0;
			LCD_NumPos = 0;
			//LCD_set=0;
			//LCD_back=1;
			//Symbol.LCD_deal=1;
		} else
			disp_chn816(18, 101, index45[parameter.sys_parameter.LCD_Backtime],
					1);

		LCDSymbol.LCD_set = 0;
		Par_Select = 1;

		break;
	case 6:
		if (Y_Pos == 4) {
			;

		} else {
			LCD_Temp[LCD_NumPos] = LCD_NoPt;
			clrramBlock(18 + LCD_NumPos, 29 + Y_Pos * 18, 1);
			disp_chn816_1(18 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 1);

			if (LCD_NumPos == (Numlenth - 1))
				LCD_NumPos = 0;
			else
				LCD_NumPos++;
			LCD_NoPt = LCD_Temp[LCD_NumPos];
			clrramBlock(18 + LCD_NumPos, 29 + Y_Pos * 18, 1);
			disp_chn816_1(18 + LCD_NumPos, 29 + Y_Pos * 18, LCD_NoPt, 0);
		}
		break;
	default:
		break;
	}
}

void disp60()
{
	INT8U *p;
	INT8U i;
	if (Symbol.LCD_deal) {
		clrram();
		Symbol.LCD_deal = 0;
		disp_xline(27);
		disp_yline(3, 28);

		disp_chn816_1(0, 29, 1, 1);          //1页
		disp_chn1616_1(1, 29, 101, 1);
		disp_chn816_1(0, 47, 2, 0);          //2页
		disp_chn1616_1(1, 47, 101, 0);
		disp_chn816_1(0, 65, 3, 1);          //2页
		disp_chn1616_1(1, 65, 101, 1);

		p = index11 + 2;
		disp_chn816_1(21, 7, 20, 1); //DO
		disp_chn816_1(22, 7, 18, 1);

		disp_chn1616(23, 7, index39, 1);

		disp_chn816(3, 7, index10, 1); //AD
		disp_chn1616(5, 7, p, 1);

		disp_chn1616(11, 7, index11, 0); //系统设置

		disp_chn1616(4, 29, P2_index[0], 1);
		disp_chn1616(4, 47, P2_index[1], 1);
		disp_chn1616(4, 65, P2_index[2], 1);
		disp_chn1616(4, 83, P2_index[3], 1);
		disp_chn1616(4, 101, P2_index[4], 1);

		disp_chn816(18, 29, LCD_index2[0], 1); //超时时间

		disp_chn816(18, 47, LCD_index2[1], 1); //报警时间

		disp_chn816(18, 65, LCD_index2[2], 1);	//数据上报时间

		disp_chn816(18, 83, LCD_index2[3], 1); //实时上报时间

		disp_chn816(18, 101, index45[parameter.sys_parameter.LCD_Backtime], 1);

	}
	if (LCDSymbol.LCD_set) {
		//LCD_set=0;
		if (Y_Pos == 0)
			Numlenth = 5;
		else if (Y_Pos == 1)
			Numlenth = 5;
		else if (Y_Pos == 2)
			Numlenth = 4;
		else if (Y_Pos == 3)
			Numlenth = 3;
		else if (Y_Pos == 4)
			Numlenth = 1;

		disp_SetNum_6x(Numlenth);

	} else if (Par_Select) {

		switch (KeyV) {
		case 1:
			Par_Select = 0;
			if (Y_Pos == 4) {
				LCDSymbol.LCD_set = 1;
				LCD_NoPt = parameter.sys_parameter.LCD_Backtime;
				clrramBlock(18, 101, 4);
				disp_chn816(18, 101, index45[LCD_NoPt], 0);
			} else {
				LCDSymbol.LCD_set = 1;
				LCD_NoPt = LCD_index2[Y_Pos][0] - 1;
				for (i = 0; i < 5; i++)
					LCD_Temp[i] = LCD_index2[Y_Pos][i] - 1;
				LCD_NumPos = 0;
				clrramBlock(18, 29 + Y_Pos * 18, 1);
				disp_chn816_1(18, 29 + Y_Pos * 18, LCD_NoPt, 0);
			}
			break;
		case 3:
			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 4)
				Y_Pos = 0;
			else
				Y_Pos++;

			clrramBlock(4, 29 + pre_Y_Pos * 18, 8);
			disp_chn1616(4, 29 + pre_Y_Pos * 18, P2_index[pre_Y_Pos], 1);

			clrramBlock(4, 29 + Y_Pos * 18, 8);
			disp_chn1616(4, 29 + Y_Pos * 18, P2_index[Y_Pos], 0);

			break;
		case 4:
			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 0)
				Y_Pos = 4;
			else
				Y_Pos--;

			clrramBlock(4, 29 + pre_Y_Pos * 18, 8);
			disp_chn1616(4, 29 + pre_Y_Pos * 18, P2_index[pre_Y_Pos], 1);

			clrramBlock(4, 29 + Y_Pos * 18, 8);
			disp_chn1616(4, 29 + Y_Pos * 18, P2_index[Y_Pos], 0);
			break;
		case 5:
			clrramBlock(4, 29 + Y_Pos * 18, 8);
			disp_chn1616(4, 29 + Y_Pos * 18, P2_index[Y_Pos], 1);
			Y_Pos = 0;
			Par_Select = 0;
			break;
		default:
			break;
		}
	} else {
		switch (KeyV) {
		case 1:
			Par_Select = 1;
			Y_Pos = 0;
			clrramBlock(4, 29, 8);
			disp_chn1616(4, 29, P2_index[0], 0);
			break;
		case 2:
			LCD_page = 70;	//AD设置
			Symbol.LCD_deal = 1;
			Y_Pos = 0;
			break;
		case 3:
			LCD_page = 100;	//设置1页
			Symbol.LCD_deal = 1;
			Y_Pos = 0;
			break;
		case 4:
			LCD_page = 50;	//设置1页
			Symbol.LCD_deal = 1;
			Symbol.LCD_Page_Change = 1;
			Y_Pos = 0;
			break;
		case 5:
			LCD_page = 30;	//回菜单
			Symbol.LCD_deal = 1;
			break;

		case 6:				//DO设置
			LCD_page = 90;
			LCD_NumPos = 0;
			LCD_DOP = 0;
			Symbol.LCD_deal = 1;
			break;
		default:
			break;
		}
	}

}

void disp_SetNum_10x(INT8U Numlenth)
{
	//uchar i;
	switch (KeyV) {
	case 1:
		LCDSymbol.LCD_set = 0;
		//Symbol.LCD_deal=1;
		Par_Select = 1;
		switch (Y_Pos) {
		case 0:
			Symbol.LCD_para_set = 1;
			parameter.sys_parameter.PO_Type[0] = LCD_NoPt;
			if (LCD_NoPt == 1) //cod
				Channel_Num[0] = 1;
			else
				//off
				Channel_Num[0] = 0;
			break;
		case 1:
			if (LCD_NoPt)
				Device_Protocol = 1;
			else
				Device_Protocol = 0;
			break;
		case 2:
			break;
		default:
			break;
		}
		switch (Y_Pos) {
		case 0:
			//100504
			clrramBlock(18, 29 + Y_Pos * 18, 5);
			disp_chn816(18, 29 + Y_Pos * 18, index54[LCD_NoPt], 1);
			//100504
			break;
		case 1:
			clrramBlock(18, 29 + Y_Pos * 18, 1);
			disp_chn816_1(18, 29 + Y_Pos * 18, LCD_NoPt, 1);
			break;
		case 2:
			clrramBlock(18, 29 + Y_Pos * 18, 7);
			disp_chn816(18, 29 + Y_Pos * 18, index48[LCD_NoPt], 1);
			break;
		default:
			break;
		}
		break;
	case 3:
		if (Y_Pos == 0) {
			/*;*/
			clrramBlock(18, 29, 5);
			if (LCD_NoPt == 1)
				LCD_NoPt = 0;
			else
				LCD_NoPt++;
			//disp_chn1616(18,65,index45[LCD_NoPt],0);
			disp_chn816(18, 29, index54[LCD_NoPt], 0);
		} else if (Y_Pos == 2) {
			/*
			 clrramBlock(18,65,7);
			 if(LCD_NoPt==Numlenth)
			 LCD_NoPt=0;
			 else
			 LCD_NoPt++;
			 disp_chn816(18,65,index48[LCD_NoPt],0);
			 */
		} else {
			clrramBlock(18, 29 + Y_Pos * 18, 1);
			if (LCD_NoPt == Numlenth)
				LCD_NoPt = 0;
			else
				LCD_NoPt++;
			disp_chn816_1(18, 29 + Y_Pos * 18, LCD_NoPt, 0);
		}
		break;
	case 4:
		if (Y_Pos == 0) {/*;*/
			clrramBlock(18, 29, 5);
			if (LCD_NoPt == 0)
				LCD_NoPt = 1;
			else
				LCD_NoPt--;
			//disp_chn1616(18,65,index45[LCD_NoPt],0);
			disp_chn816(18, 29, index54[LCD_NoPt], 0);
		} else if (Y_Pos == 2) {
			/*
			 clrramBlock(18,65,7);
			 if(LCD_NoPt==0)
			 LCD_NoPt=Numlenth;
			 else
			 LCD_NoPt--;
			 disp_chn816(18,65,index48[LCD_NoPt],0);
			 */
		}

		else {
			clrramBlock(18, 29 + Y_Pos * 18, 1);
			if (LCD_NoPt == 0)
				LCD_NoPt = Numlenth;
			else
				LCD_NoPt--;
			disp_chn816_1(18, 29 + Y_Pos * 18, LCD_NoPt, 0);
		}
		break;
	case 5:
		switch (Y_Pos) {

		case 0:
			;
			//clrramBlock(18,29,4);
			//disp_chn816(18,29,index54[Equ_Type],1);
			break;
		case 1:
			clrramBlock(18, 47, 1);
			if (Device_Protocol)
				LCD_NoPt = 1;
			else
				LCD_NoPt = 0;
			disp_chn816_1(18, 47, LCD_NoPt, 1);
			break;
		case 2:
			//clrramBlock(18,65,7);
			//disp_chn816(18,65,index48[parameter.sys_parameter.LCD_Baud],1);
			break;
		default:
			break;
		}
		LCD_NoPt = 0;
		LCDSymbol.LCD_set = 0;
		Par_Select = 1;
		break;

	default:
		break;
	}
}

void disp100()
{
	INT8U *p;

	if (Symbol.LCD_deal) {
		clrram();
		Symbol.LCD_deal = 0;
		disp_xline(27);
		disp_yline(3, 28);

		disp_chn816_1(0, 29, 1, 1);      //1页
		disp_chn1616_1(1, 29, 101, 1);
		disp_chn816_1(0, 47, 2, 1);      //2页
		disp_chn1616_1(1, 47, 101, 1);
		disp_chn816_1(0, 65, 3, 0);      //2页
		disp_chn1616_1(1, 65, 101, 0);

		p = index11 + 2;
		disp_chn816_1(21, 7, 20, 1); //DO
		disp_chn816_1(22, 7, 18, 1);
		disp_chn1616(23, 7, index39, 1);

		disp_chn816(3, 7, index10, 1); //AD
		disp_chn1616(5, 7, p, 1);

		disp_chn1616(11, 7, index11, 0); //系统设置

		disp_chn1616(4, 29, P3_index[0], 1);
		disp_chn1616(4, 47, P3_index[1], 1);
		disp_chn1616(4, 65, P3_index[2], 1);
		//disp_chn1616(4,65,index44,1);

		//disp_chn816(18,29,index45[parameter.sys_parameter.LCD_Backtime],1);
		//disp_chn1616(18,29,index49[parameter.sys_parameter.PO_Type[0]],1);//Equ_Type
		disp_chn816(18, 29, index54[parameter.sys_parameter.PO_Type[0]], 1);
		//disp_chn816(18,29,index54,1);
		disp_chn816_1(18, 47, (char) Device_Protocol, 1);
		//disp_chn816(18,65,index48[parameter.sys_parameter.LCD_Baud],1);
		disp_chn816(18, 65, index57, 1);
		//disp_chn816(18,65,LCD_index3[2],1);
	}

	if (LCDSymbol.LCD_set) {
		//	LCD_set=0;
		if (Y_Pos == 0)
			Numlenth = 1;  //1
		else if (Y_Pos == 1)
			Numlenth = 1;
		else if (Y_Pos == 2)
			Numlenth = 4;

		disp_SetNum_10x(Numlenth);
	} else if (Par_Select) {
		switch (KeyV) {
		case 1: //100504
			Par_Select = 0;
			LCDSymbol.LCD_set = 1;
			if (Y_Pos == 0) {

				//LCD_page=101; //100504
				//Symbol.LCD_deal=1;
				//LCDSymbol.LCD_set=0;
				if (parameter.sys_parameter.PO_Type[0] == 0)
					LCD_NoPt = 0;
				else
					LCD_NoPt = 1;
				clrramBlock(18, 29, 4);
				disp_chn816(18, 29, index54[LCD_NoPt], 0);
				//disp_chn816(18,29,index54,0);
			} else if (Y_Pos == 1) {
				LCD_NoPt = parameter.sys_parameter.LCD_Backtime;
				if (Device_Protocol)
					LCD_NoPt = 1;
				else
					LCD_NoPt = 0;
				clrramBlock(18, 47, 4);
				disp_chn816_1(18, 47, LCD_NoPt, 0);
			} else {
				LCD_page = 102;
				Symbol.LCD_deal = 1;
				LCDSymbol.LCD_set = 0;

			}
			break;  //100504

		case 3:
			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 2)
				Y_Pos = 0;
			else
				Y_Pos++;

			clrramBlock(4, 29 + pre_Y_Pos * 18, 10);
			disp_chn1616(4, 29 + pre_Y_Pos * 18, P3_index[pre_Y_Pos], 1);

			clrramBlock(4, 29 + Y_Pos * 18, 10);
			disp_chn1616(4, 29 + Y_Pos * 18, P3_index[Y_Pos], 0);

			break;
		case 4:
			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 0)
				Y_Pos = 2;
			else
				Y_Pos--;

			clrramBlock(4, 29 + pre_Y_Pos * 18, 10);
			disp_chn1616(4, 29 + pre_Y_Pos * 18, P3_index[pre_Y_Pos], 1);

			clrramBlock(4, 29 + Y_Pos * 18, 10);
			disp_chn1616(4, 29 + Y_Pos * 18, P3_index[Y_Pos], 0);
			break;
		case 5:
			clrramBlock(4, 29 + Y_Pos * 18, 10);
			disp_chn1616(4, 29 + Y_Pos * 18, P3_index[Y_Pos], 1);
			Y_Pos = 0;
			Par_Select = 0;
			break;
		default:
			break;
		}
	} else {
		switch (KeyV) {
		case 1:
			Par_Select = 1;
			Y_Pos = 0;
			clrramBlock(4, 29, 10);
			disp_chn1616(4, 29, P3_index[0], 0);
			break;
		case 2:
			LCD_page = 70;	//Do设置
			Symbol.LCD_deal = 1;
			break;
		case 3:
			LCD_page = 50;	//设置1页
			Symbol.LCD_deal = 1;
			Symbol.LCD_Page_Change = 1;
			Y_Pos = 0;
			break;
		case 4:
			LCD_page = 60;	//设置2页
			Symbol.LCD_deal = 1;
			Y_Pos = 0;
			break;
		case 5:
			LCD_page = 30;	//回菜单
			Symbol.LCD_deal = 1;
			break;
		case 6:				//AD设置
			LCD_page = 90;
			LCD_NumPos = 0;
			LCD_DOP = 0;
			Symbol.LCD_deal = 1;
			break;
		default:
			break;
		}
	}
}

void disp101()
{
	INT8U i, j, k;

	if (Symbol.LCD_deal) {
		clrram();
		Symbol.LCD_deal = 0;

		disp_chn816_1(2, 6, 4, 1);
		disp_chn816_1(3, 6, 8, 1);
		disp_chn816_1(4, 6, 5, 1);

		disp_chn816_1(2, 86, 2, 1);
		disp_chn816_1(3, 86, 3, 1);
		disp_chn816_1(4, 86, 2, 1);

		for (i = 0; i < 6; i++) {
			disp_chn1616(9, 6 + i * 20, index55, 1);
			disp_chn816_1(13, 6 + i * 20, i + 1, 1);
		}

		for (i = 0; i < 6; i++) {
			disp_chn1616(18, 6 + i * 20,
					index49[parameter.sys_parameter.PO_Type[i]], 1);
		}

		clrramBlock(9, 6 + AD_Y_Pos * 20, 4);
		disp_chn1616(9, 6 + AD_Y_Pos * 20, index55, 0);
		clrramBlock(13, 6 + AD_Y_Pos * 20, 1);
		disp_chn816_1(13, 6 + AD_Y_Pos * 20, AD_Y_Pos + 1, 0);

	}
	if (LCDSymbol.LCD_set) {
		switch (KeyV) {
		case 1:
			LCDSymbol.LCD_set = 0;
			Symbol.LCD_para_set = 1;

			if (parameter.sys_parameter.PO_Type[AD_Y_Pos] != LCD_NoPt)
				PO_Change = 1;
			else
				PO_Change = 0;

			parameter.sys_parameter.PO_Type[AD_Y_Pos] = LCD_NoPt;

			clrramBlock(18, 6 + AD_Y_Pos * 20, 4);
			disp_chn1616(18, 6 + AD_Y_Pos * 20,
					index49[parameter.sys_parameter.PO_Type[AD_Y_Pos]], 1);

			if (parameter.sys_parameter.PO_Type[AD_Y_Pos] == 0) {
				for (k = 0; k < 16; k++) {
					parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][k] = 0xff;

				}
				Channel_Num[AD_Y_Pos] = 0;

			} else {
				for (i = 0; i < 16; i++) {
					switch (parameter.sys_parameter.PO_Type[AD_Y_Pos]) {
					case 1:
						for (j = 0; j < 3; j++) {
							if (parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]
									== 0xff) {

								LCD_Channel_index[i][0] = 1;
								LCD_Channel_index[i][1] = 1;
								LCD_Channel_index[i][2] = 1;
								break;
							} else {
								if (MOD_Water[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'S')
									LCD_Channel_index[i][j] = 17;
								else if (MOD_Water[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'P')
									LCD_Channel_index[i][j] = 18;
								else if (MOD_Water[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'f')
									LCD_Channel_index[i][j] = 24;
								else if (MOD_Water[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'k')
									LCD_Channel_index[i][j] = 25;
								else if (MOD_Water[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'B')
									LCD_Channel_index[i][j] = 27;
								else if (MOD_Water[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 0) {
									LCD_Channel_index[i][j] = 12;
									break;
								} else
									LCD_Channel_index[i][j] =
											(MOD_Water[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
													& 0x0f) + 1;
							}
						}
						break;
					case 2:
						for (j = 0; j < 3; j++) {
							if (parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]
									== 0xff) {

								LCD_Channel_index[i][0] = 1;
								LCD_Channel_index[i][1] = 1;
								LCD_Channel_index[i][2] = 1;
								break;
								//	//LCD_Channel_index[i][3]='\0';
							} else {
								if (MOD_Gas[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'S')
									LCD_Channel_index[i][j] = 17;
								else if (MOD_Gas[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'P')
									LCD_Channel_index[i][j] = 18;
								else if (MOD_Gas[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'f')
									LCD_Channel_index[i][j] = 24;
								else if (MOD_Gas[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'k')
									LCD_Channel_index[i][j] = 25;
								else if (MOD_Gas[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 'B')
									LCD_Channel_index[i][j] = 27;
								else if (MOD_Gas[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
										== 0) {
									LCD_Channel_index[i][j] = 12;
									break;
								} else
									LCD_Channel_index[i][j] =
											(MOD_Gas[parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i]].PO_code[j]
													& 0x0f) + 1;
							}
						}
						break;
					default:
						break;
					}
					LCD_Channel_index[i][3] = 0;
					//	}

				}

				if (PO_Change) {
					PO_Change = 0;
					for (k = 0; k < 16; k++) {
						parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][k] =
								0xff;
						LCD_Channel_index[k][0] = 1;
						LCD_Channel_index[k][1] = 1;
						LCD_Channel_index[k][2] = 1;
						LCD_Channel_index[k][3] = 0;

					}
					Channel_Num[AD_Y_Pos] = 0;

					LCD_page = 200;	//通道设置
					Symbol.LCD_deal = 1;

				} else {
					LCD_page = 200;	//通道设置
					Symbol.LCD_deal = 1;
				}
			}

			break;
		case 3:
			clrramBlock(18, 6 + AD_Y_Pos * 20, 4);
			if (LCD_NoPt == 2)
				LCD_NoPt = 0;
			else
				LCD_NoPt++;
			disp_chn1616(18, 6 + AD_Y_Pos * 20, index49[LCD_NoPt], 0);
			break;
		case 4:
			clrramBlock(18, 6 + AD_Y_Pos * 20, 4);
			if (LCD_NoPt == 0)
				LCD_NoPt = 2;
			else
				LCD_NoPt--;
			disp_chn1616(18, 6 + AD_Y_Pos * 20, index49[LCD_NoPt], 0);
			break;
		case 5:
			disp_chn1616(18, 6 + AD_Y_Pos * 20,
					index49[parameter.sys_parameter.PO_Type[AD_Y_Pos]], 1);
			LCDSymbol.LCD_set = 0;
			break;
		default:
			break;
		}
	} else {
		switch (KeyV) {
		case 1:
			LCDSymbol.LCD_set = 1;
			LCD_NoPt = parameter.sys_parameter.PO_Type[AD_Y_Pos];
			clrramBlock(18, 6 + AD_Y_Pos * 20, 4);
			disp_chn1616(18, 6 + AD_Y_Pos * 20,
					index49[parameter.sys_parameter.PO_Type[AD_Y_Pos]], 0);

			break;

		case 3:
			AD_pre_Y_Pos = AD_Y_Pos;
			if (AD_Y_Pos == 5)
				AD_Y_Pos = 0;
			else
				AD_Y_Pos++;

			clrramBlock(9, 6 + AD_pre_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_pre_Y_Pos * 20, index55, 1);
			clrramBlock(13, 6 + AD_pre_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_pre_Y_Pos * 20, AD_pre_Y_Pos + 1, 1);

			clrramBlock(9, 6 + AD_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_Y_Pos * 20, index55, 0);
			clrramBlock(13, 6 + AD_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_Y_Pos * 20, AD_Y_Pos + 1, 0);

			break;
		case 4:
			AD_pre_Y_Pos = AD_Y_Pos;

			if (AD_Y_Pos == 0)
				AD_Y_Pos = 5;
			else
				AD_Y_Pos--;

			clrramBlock(9, 6 + AD_pre_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_pre_Y_Pos * 20, index55, 1);
			clrramBlock(13, 6 + AD_pre_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_pre_Y_Pos * 20, AD_pre_Y_Pos + 1, 1);

			clrramBlock(9, 6 + AD_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_Y_Pos * 20, index55, 0);
			clrramBlock(13, 6 + AD_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_Y_Pos * 20, AD_Y_Pos + 1, 0);

			break;
		case 5:
			clrramBlock(9, 6 + AD_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_Y_Pos * 20, index55, 1);
			clrramBlock(13, 6 + AD_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_Y_Pos * 20, AD_Y_Pos + 1, 1);
			AD_Y_Pos = 0;

			LCD_page = 100;
			Symbol.LCD_deal = 1;
			//Par_Select=0;
			break;

		default:
			break;
		}
	}

}

void disp102()
{
	INT8U i;

	if (Symbol.LCD_deal) {
		clrram();
		Symbol.LCD_deal = 0;

		for (i = 0; i < 6; i++) {
			disp_chn1616(9, 6 + i * 20, index56, 1);
			disp_chn816_1(13, 6 + i * 20, i + 1, 1);
		}

		for (i = 0; i < 6; i++) {
			disp_chn816(18, 6 + i * 20, index48[SPARA.Serial_Baud[i]], 1);
		}

		clrramBlock(9, 6 + AD_Y_Pos * 20, 4);
		disp_chn1616(9, 6 + AD_Y_Pos * 20, index56, 0);
		clrramBlock(13, 6 + AD_Y_Pos * 20, 1);
		disp_chn816_1(13, 6 + AD_Y_Pos * 20, AD_Y_Pos + 1, 0);

	}
	if (LCDSymbol.LCD_set) {
		switch (KeyV) {
		case 1:
			LCDSymbol.LCD_set = 0;
			Symbol.LCD_para_set = 1;
			SPARA.Serial_Baud[AD_Y_Pos] = LCD_NoPt;

			clrramBlock(18, 6 + AD_Y_Pos * 20, 8);
			disp_chn816(18, 6 + AD_Y_Pos * 20,
					index48[SPARA.Serial_Baud[AD_Y_Pos]], 1);
			_BIC_SR(GIE);
			Chang752Baud(SPARA.Serial_Baud[AD_Y_Pos], AD_Y_Pos);
			_BIS_SR(GIE);
			break;
		case 3:
			clrramBlock(18, 6 + AD_Y_Pos * 20, 8);
			if (LCD_NoPt == 4)
				LCD_NoPt = 0;
			else
				LCD_NoPt++;
			disp_chn816(18, 6 + AD_Y_Pos * 20, index48[LCD_NoPt], 0);
			break;
		case 4:
			clrramBlock(18, 6 + AD_Y_Pos * 20, 8);
			if (LCD_NoPt == 0)
				LCD_NoPt = 4;
			else
				LCD_NoPt--;
			disp_chn816(18, 6 + AD_Y_Pos * 20, index48[LCD_NoPt], 0);
			break;
		case 5:
			clrramBlock(18, 6 + AD_Y_Pos * 20, 8);
			disp_chn816(18, 6 + AD_Y_Pos * 20,
					index48[SPARA.Serial_Baud[AD_Y_Pos]], 1);
			LCDSymbol.LCD_set = 0;
			break;
		default:
			break;
		}
	} else {
		switch (KeyV) {
		case 1:
			LCDSymbol.LCD_set = 1;
			LCD_NoPt = SPARA.Serial_Baud[AD_Y_Pos];
			clrramBlock(18, 6 + AD_Y_Pos * 20, 8);
			disp_chn816(18, 6 + AD_Y_Pos * 20,
					index48[SPARA.Serial_Baud[AD_Y_Pos]], 0);

			break;

		case 3:
			AD_pre_Y_Pos = AD_Y_Pos;
			if (AD_Y_Pos == 5)
				AD_Y_Pos = 0;
			else
				AD_Y_Pos++;

			clrramBlock(9, 6 + AD_pre_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_pre_Y_Pos * 20, index56, 1);
			clrramBlock(13, 6 + AD_pre_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_pre_Y_Pos * 20, AD_pre_Y_Pos + 1, 1);

			clrramBlock(9, 6 + AD_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_Y_Pos * 20, index56, 0);
			clrramBlock(13, 6 + AD_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_Y_Pos * 20, AD_Y_Pos + 1, 0);

			break;
		case 4:
			AD_pre_Y_Pos = AD_Y_Pos;

			if (AD_Y_Pos == 0)
				AD_Y_Pos = 5;
			else
				AD_Y_Pos--;

			clrramBlock(9, 6 + AD_pre_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_pre_Y_Pos * 20, index56, 1);
			clrramBlock(13, 6 + AD_pre_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_pre_Y_Pos * 20, AD_pre_Y_Pos + 1, 1);

			clrramBlock(9, 6 + AD_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_Y_Pos * 20, index56, 0);
			clrramBlock(13, 6 + AD_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_Y_Pos * 20, AD_Y_Pos + 1, 0);

			break;
		case 5:
			clrramBlock(9, 6 + AD_Y_Pos * 20, 4);
			disp_chn1616(9, 6 + AD_Y_Pos * 20, index56, 1);
			clrramBlock(13, 6 + AD_Y_Pos * 20, 1);
			disp_chn816_1(13, 6 + AD_Y_Pos * 20, AD_Y_Pos + 1, 1);
			AD_Y_Pos = 0;

			LCD_page = 100;
			Symbol.LCD_deal = 1;
			//Par_Select=0;
			break;

		default:
			break;
		}
	}

}
INT8U posselect(INT8U Pos_X, INT8U Pos_Y)
{

	if ((Pos_X == 0) && (Pos_Y == 0))
		return 0;
	else if ((Pos_X == 1) && (Pos_Y == 0))
		return 1;
	else if ((Pos_X == 0) && (Pos_Y == 1))
		return 2;
	else if ((Pos_X == 1) && (Pos_Y == 1))
		return 3;
	else if ((Pos_X == 0) && (Pos_Y == 2))
		return 4;
	else if ((Pos_X == 1) && (Pos_Y == 2))
		return 5;
	else if ((Pos_X == 0) && (Pos_Y == 3))
		return 6;
	else if ((Pos_X == 1) && (Pos_Y == 3))
		return 7;
	else if ((Pos_X == 0) && (Pos_Y == 4))
		return 8;
	else if ((Pos_X == 1) && (Pos_Y == 4))
		return 9;
	else if ((Pos_X == 0) && (Pos_Y == 5))
		return 10;
	else if ((Pos_X == 1) && (Pos_Y == 5))
		return 11;
	else if ((Pos_X == 0) && (Pos_Y == 6))
		return 12;
	else if ((Pos_X == 1) && (Pos_Y == 6))
		return 13;
	else if ((Pos_X == 0) && (Pos_Y == 7))
		return 14;
	else
		return 15;

}

INT8U LCD_PO_C = 0;

void disp200()
{

	INT8U i, j, k;
	INT8U numberlen, addnum;
	INT8U check[4] = "000\0";
	//INT16U  b=1;

	if (parameter.sys_parameter.PO_Type[AD_Y_Pos] == 1) {
		numberlen = 12;
		addnum = 35;
	} else if (parameter.sys_parameter.PO_Type[AD_Y_Pos] == 2) {
		numberlen = 13;
		addnum = 48;
	}

	if (Symbol.LCD_deal) {
		clrram();
		Symbol.LCD_deal = 0;

		for (i = 0; i < 8; i++) {
			disp_chn1616(3, 0 + i * 16, index50, 1);
			disp_chn1616(18, 0 + i * 16, index50, 1);
		}
		for (i = 0; i < 5; i++) {
			disp_chn816_1(7, 0 + i * 16, 2 * i + 1, 1);
			disp_chn816_1(22, 0 + i * 16, 2 * i + 2, 1);
		}
		disp_chn816_1(22, 64, 1, 1);
		disp_chn816_1(23, 64, 0, 1);

		for (i = 0; i < 3; i++) {
			disp_chn816_1(7, 80 + i * 16, 1, 1);
			disp_chn816_1(22, 80 + i * 16, 1, 1);
			disp_chn816_1(8, 80 + i * 16, 2 * i + 1, 1);
			disp_chn816_1(23, 80 + i * 16, 2 * i + 2, 1);
		}
		//LCD_Channel_index[16][4];
		for (i = 0; i < 8; i++) {
			disp_chn816(10, 0 + i * 16, LCD_Channel_index[2 * i], 1);
			disp_chn816(25, 0 + i * 16, LCD_Channel_index[2 * i + 1], 1);
		}
		clrramBlock(10, 0, 4);
		disp_chn816(10, 0, LCD_Channel_index[0], 0);

	}
	if (LCDSymbol.LCD_set == 1) {
		switch (KeyV) {
		case 1:
			LCDSymbol.LCD_set = 0;
			Symbol.LCD_para_set = 1;

			LCD_Temp[LCD_NumPos] = index37[LCD_NoPt];
			//	LCD_Temp[3]=0;

			for (j = 0; j < 3; j++) {
				if (LCD_Temp[j] == 16)
					LCD_Temp[j] = 'S';
				else if (LCD_Temp[j] == 17) {
					LCD_Temp[j] = 'P';
					break;
				} else if (LCD_Temp[j] == 11) {
					LCD_Temp[j] = 0;
					break;
				} else if (LCD_Temp[j] == 26)
					LCD_Temp[j] = 'B';
				else
					LCD_Temp[j] = (LCD_Temp[j] | 0x30);
			}
			LCD_Temp[3] = 0;

			if (LCD_Temp[0] == 'P') {
				LCD_Temp[1] = 'f';
				LCD_Temp[2] = 'k';
			}

			//----------------------------------------------------------------------

			if (strcmp(LCD_Temp, check) != 0) {
				//if(LCD_PO_C==Channel_Num[AD_Y_Pos]) Channel_Num[AD_Y_Pos]++;
				//NZ=1;

				for (j = 0; j < addnum; j++) {
					if (parameter.sys_parameter.PO_Type[AD_Y_Pos] == 1) {
						if (strcmp(LCD_Temp, MOD_Water[j].PO_code) == 0) {
							parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][LCD_PO_C] =
									j;
							if (LCD_PO_C == Channel_Num[AD_Y_Pos])
								Channel_Num[AD_Y_Pos]++;
							NZ = 1;
							break;
						}

					} else if (parameter.sys_parameter.PO_Type[AD_Y_Pos] == 2) {
						if (strcmp(LCD_Temp, MOD_Gas[j].PO_code) == 0) {
							parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][LCD_PO_C] =
									j;
							if (LCD_PO_C == Channel_Num[AD_Y_Pos])
								Channel_Num[AD_Y_Pos]++;
							NZ = 1;
							break;
						}

					}
				}
				if ((j == addnum) && (NZ == 0)) {
					LCD_Temp[0] = 0x30;
					LCD_Temp[1] = 0x30;
					LCD_Temp[2] = 0x30;
					LCD_Temp[3] = 0;

					clrramBlock(10 + 15 * X_Pos, Y_Pos * 16, 4);
					disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
							LCD_Channel_index[LCD_PO_C], 0);

				}

			} else {
				Channel_Num[AD_Y_Pos] = LCD_PO_C;

				for (i = LCD_PO_C; i < 16; i++) {
					parameter.sys_parameter.PO_SerialNum[AD_Y_Pos][i] = 0xff;
					LCD_Channel_index[i][0] = 1;
					LCD_Channel_index[i][1] = 1;
					LCD_Channel_index[i][2] = 1;
					LCD_Channel_index[i][3] = '\0';

				}
				for (k = 0; k < 8; k++) {
					clrramBlock(10, 0 + k * 16, 4);

					clrramBlock(25, 0 + k * 16, 4);

					disp_chn816(10, 0 + k * 16, LCD_Channel_index[2 * k], 1);

					disp_chn816(25, 0 + k * 16, LCD_Channel_index[k * 2 + 1],
							1);
				}

				clrramBlock(10 + 15 * X_Pos, Y_Pos * 16, 4);
				disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 0);

			}
			//----------------------------------------------------------------------
			for (j = 0; j < 3; j++) {
				if (LCD_Temp[j] == 0) {
					LCD_Temp[j] = 10;
					break;
				} else if (LCD_Temp[j] == 'S')
					LCD_Temp[j] = 13;
				else if (LCD_Temp[j] == 'P') {
					LCD_Temp[j] = 12;
					break;
				} else if (LCD_Temp[j] == 'B')
					LCD_Temp[j] = 11;

				else
					LCD_Temp[j] &= 0x0f;
				LCD_Channel_index[LCD_PO_C][j] = index37[LCD_Temp[j]] + 1;

			}
			LCD_Channel_index[LCD_PO_C][j] = index37[LCD_Temp[j]] + 1;
			LCD_Channel_index[LCD_PO_C][3] = 0;
			if (j == 0) {
				LCD_Channel_index[LCD_PO_C][0] = 18;					//P
				LCD_Channel_index[LCD_PO_C][1] = 24;					//f
				LCD_Channel_index[LCD_PO_C][2] = 25;					//k
				//disp_chn816(18,29+(i-1)*18,LCD_index2[i-1],1);
			}
			if (j == 1) {
				LCD_Channel_index[LCD_PO_C][2] = 12;
			}
			//disp_chn816(18,29+(i-1)*18,LCD_index2[i-1],1);
			if (NZ) {
				NZ = 0;
				disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 1);
				if (X_Pos == 0)
					X_Pos++;
				else {
					X_Pos = 0;
					if (Y_Pos == 7)
						Y_Pos = 0;
					else
						Y_Pos++;
				}
				if (LCD_PO_C == 15)
					LCD_PO_C = 0;
				else
					LCD_PO_C++;
				disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 0);

			}

			break;
		case 2:
			if ((LCD_NumPos == 0) && (LCD_NoPt == 12)) {
				LCD_Temp[0] = 17;
				LCD_Temp[1] = 23;
				LCD_Temp[2] = 24;
			} else {
				LCD_Temp[LCD_NumPos] = index37[LCD_NoPt];
				clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 1);
				disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
						index37[LCD_NoPt], 1);
				if (LCD_NumPos == 0)
					;					//LCD_NumPos=Numlenth-1;
				else
					LCD_NumPos--;
				clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 1);
				if (LCD_Temp[LCD_NumPos] == 16)
					LCD_NoPt = 13;
				else if (LCD_Temp[LCD_NumPos] == 26)
					LCD_NoPt = 11;
				else
					LCD_NoPt = LCD_Temp[LCD_NumPos];
				if ((LCD_NoPt < 0) || (LCD_NoPt > 13))
					LCD_NoPt = 0;
				disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
						index37[LCD_NoPt], 0);
			}

			break;
		case 3:
			clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 1);
			if (LCD_NumPos != 0) {
				if (LCD_NoPt == 10)
					LCD_NoPt = 0;
				else
					LCD_NoPt++;
				disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
						index37[LCD_NoPt], 0);
			} else {
				//if(LCD_NoPt==13)
				if (LCD_NoPt == numberlen)
					LCD_NoPt = 0;
				else
					LCD_NoPt++;
				if (index37[LCD_NoPt] == 17) {
					clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 3);
					//LCD_Temp[0]=17;
					disp_chn816(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
							index38, 0);

				} else {
					clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 3);
					disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
							index37[LCD_NoPt], 0);
					disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos + 1, Y_Pos * 16,
							11, 1);
					disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos + 2, Y_Pos * 16,
							11, 1);
					LCD_Temp[1] = 11;
					LCD_Temp[2] = 11;
				}
			}

			break;
		case 4:
			clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 1);
			if (LCD_NumPos != 0) {
				if (LCD_NoPt == 0)
					LCD_NoPt = 10;
				else
					LCD_NoPt--;
				disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
						index37[LCD_NoPt], 0);
			} else {
				if (LCD_NoPt == 0)
					LCD_NoPt = numberlen;
				else
					LCD_NoPt--;
				if (index37[LCD_NoPt] == 17) {
					clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 3);
					disp_chn816(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
							index38, 0);
					//LCD_Temp[0]=17;
				} else {
					clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 3);
					disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
							index37[LCD_NoPt], 0);
					disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos + 1, Y_Pos * 16,
							11, 1);
					disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos + 2, Y_Pos * 16,
							11, 1);
					LCD_Temp[1] = 11;
					LCD_Temp[2] = 11;
				}
			}

			break;
		case 5:

			disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
					LCD_Channel_index[LCD_PO_C], 0);
			LCD_NoPt = 0;
			LCD_NumPos = 0;
			LCDSymbol.LCD_set = 0;

			break;
		case 6:
			if ((LCD_NumPos == 0) && (LCD_NoPt == 12)) {
				LCD_Temp[0] = 17;
				LCD_Temp[1] = 23;
				LCD_Temp[2] = 24;
			} else {
				LCD_Temp[LCD_NumPos] = index37[LCD_NoPt];
				clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 1);
				disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
						index37[LCD_NoPt], 1);

				if (LCD_NumPos == 2)
					;					//LCD_NumPos=0;
				else
					LCD_NumPos++;
				if (LCD_Temp[LCD_NumPos] == 16)
					LCD_NoPt = 13;
				else if (LCD_Temp[LCD_NumPos] == 26)
					LCD_NoPt = 11;
				else
					LCD_NoPt = LCD_Temp[LCD_NumPos];
				if ((LCD_NoPt < 0) || (LCD_NoPt > 10))
					LCD_NoPt = 0;
				clrramBlock(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16, 1);
				disp_chn816_1(10 + 15 * X_Pos + LCD_NumPos, Y_Pos * 16,
						index37[LCD_NoPt], 0);
			}

			break;
		default:
			break;
		}
	} else
		switch (KeyV) {
		case 1:
			LCDSymbol.LCD_set = 1;

			pre_X_Pos = X_Pos;
			pre_Y_Pos = Y_Pos;

			LCD_PO_C = posselect(X_Pos, Y_Pos);

			if (LCD_Channel_index[LCD_PO_C][0] == 17) {
				LCD_NoPt = 13;

			} else if (LCD_Channel_index[LCD_PO_C][0] == 18) {
				LCD_NoPt = 12;
				disp_chn816(10 + 15 * X_Pos, Y_Pos * 16, index38, 0);
			} else if (LCD_Channel_index[LCD_PO_C][0] == 12)
				LCD_NoPt = 10;

			else if (LCD_Channel_index[LCD_PO_C][0] == 27)
				LCD_NoPt = 11;
			else
				LCD_NoPt = LCD_Channel_index[LCD_PO_C][0] - 1;
			for (i = 0; i < 3; i++)
				LCD_Temp[i] = LCD_Channel_index[LCD_PO_C][i] - 1;
			LCD_NumPos = 0;

			clrramBlock(10 + 15 * X_Pos, Y_Pos * 16, 4);
			disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
					LCD_Channel_index[LCD_PO_C], 1);
			clrramBlock(10 + 15 * X_Pos, Y_Pos * 16, 1);
			disp_chn816_1(10 + 15 * X_Pos, Y_Pos * 16, index37[LCD_NoPt], 0);

			break;
		case 2:
			pre_X_Pos = X_Pos;
			pre_Y_Pos = Y_Pos;

			if (X_Pos == 0) {
				X_Pos = 1;
				if (Y_Pos == 0)
					Y_Pos = 7;
				else
					Y_Pos--;
			} else
				X_Pos = 0;

			LCD_PO_C = posselect(X_Pos, Y_Pos);

			if (LCD_PO_C <= Channel_Num[AD_Y_Pos]) {

				//	a=posselect(X_Pos,Y_Pos);
				clrramBlock(10 + 15 * X_Pos, Y_Pos * 16, 4);
				disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 0);

				LCD_PO_C = posselect(pre_X_Pos, pre_Y_Pos);
				clrramBlock(10 + 15 * pre_X_Pos, pre_Y_Pos * 16, 4);
				disp_chn816(10 + 15 * pre_X_Pos, pre_Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 1);

			} else {
				X_Pos = pre_X_Pos;
				Y_Pos = pre_Y_Pos;
			}
			break;
		case 3:
			pre_X_Pos = X_Pos;
			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 7)
				Y_Pos = 0;
			else
				Y_Pos++;

			LCD_PO_C = posselect(X_Pos, Y_Pos);

			if (LCD_PO_C <= Channel_Num[AD_Y_Pos]) {
				clrramBlock(10 + 15 * X_Pos, Y_Pos * 16, 4);
				disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 0);

				LCD_PO_C = posselect(pre_X_Pos, pre_Y_Pos);
				clrramBlock(10 + 15 * pre_X_Pos, pre_Y_Pos * 16, 4);
				disp_chn816(10 + 15 * pre_X_Pos, pre_Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 1);
			} else {
				X_Pos = pre_X_Pos;
				Y_Pos = pre_Y_Pos;
			}

			break;
		case 4:
			pre_X_Pos = X_Pos;
			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 0)
				Y_Pos = 7;
			else
				Y_Pos--;

			LCD_PO_C = posselect(X_Pos, Y_Pos);
			if (LCD_PO_C <= Channel_Num[AD_Y_Pos]) {
				clrramBlock(10 + 15 * X_Pos, Y_Pos * 16, 4);
				disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 0);

				LCD_PO_C = posselect(pre_X_Pos, pre_Y_Pos);
				clrramBlock(10 + 15 * pre_X_Pos, pre_Y_Pos * 16, 4);
				disp_chn816(10 + 15 * pre_X_Pos, pre_Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 1);

			} else {
				X_Pos = pre_X_Pos;
				Y_Pos = pre_Y_Pos;
			}

			break;
		case 5:
			LCD_page = 101;	//
			Symbol.LCD_deal = 1;
			//Symbol.LCD_Page_Change=1;
			X_Pos = 0;
			Y_Pos = 0;
			//Par_Select=0;
			break;
		case 6:
			pre_X_Pos = X_Pos;
			pre_Y_Pos = Y_Pos;

			if (X_Pos == 1) {
				X_Pos = 0;
				if (Y_Pos == 7)
					Y_Pos = 0;
				else
					Y_Pos++;
			} else
				X_Pos = 1;	//

			LCD_PO_C = posselect(X_Pos, Y_Pos);
			if (LCD_PO_C <= Channel_Num[AD_Y_Pos]) {
				clrramBlock(10 + 15 * X_Pos, Y_Pos * 16, 4);
				disp_chn816(10 + 15 * X_Pos, Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 0);

				LCD_PO_C = posselect(pre_X_Pos, pre_Y_Pos);
				clrramBlock(10 + 15 * pre_X_Pos, pre_Y_Pos * 16, 4);
				disp_chn816(10 + 15 * pre_X_Pos, pre_Y_Pos * 16,
						LCD_Channel_index[LCD_PO_C], 1);
			} else {
				X_Pos = pre_X_Pos;
				Y_Pos = pre_Y_Pos;
			}
			break;
		default:
			break;
		}

}

void disp_SetNum_ADx(INT8U Numlenth)
{
	INT8U j;
	switch (KeyV) {
	case 1:
		LCDSymbol.LCD_set = 0;
		Par_Select = 1;
		Symbol.LCD_para_set = 1;
		LCD_Temp[LCD_NumPos] = LCD_NoPt;

		if (AD_Y_Pos == 0) {
			Symbol.ADP_change = 1;
			parameter.AD_i[Y_Pos].AI_Type = LCD_NoPt;
		}

		else if (AD_Y_Pos == 1) {
			LCD_Temp[LCD_NumPos] = index52[LCD_NoPt];

			for (j = 0; j < 3; j++) {
				if (LCD_Temp[j] == 16)
					LCD_Temp[j] = 'S';
				else if (LCD_Temp[j] == 17) {
					LCD_Temp[j] = 'P';
				} else if (LCD_Temp[j] == 11) {
					LCD_Temp[j] = 0;
					break;
				} else if (LCD_Temp[j] == 26)
					LCD_Temp[j] = 'B';
				else if (LCD_Temp[j] == 23)
					LCD_Temp[j] = 'f';
				else if (LCD_Temp[j] == 24)
					LCD_Temp[j] = 'k';

				else
					LCD_Temp[j] = (LCD_Temp[j] | 0x30);
			}
			LCD_Temp[3] = 0;

			for (j = 0; j < 4; j++)
				ADPARA(Y_Pos).po_id[j]=LCD_Temp[j];

			for (j = 0; j < 3; j++) {
				if (LCD_Temp[j] == 0) {
					LCD_Temp[j] = 10;
					break;
				} else if (LCD_Temp[j] == 'S')
					LCD_Temp[j] = 15;
				else if (LCD_Temp[j] == 'P') {
					LCD_Temp[j] = 12;

				} else if (LCD_Temp[j] == 'f') {
					LCD_Temp[j] = 13;

				} else if (LCD_Temp[j] == 'k') {
					LCD_Temp[j] = 14;

				} else if (LCD_Temp[j] == 'B')
					LCD_Temp[j] = 11;

				else
					LCD_Temp[j] &= 0x0f;
				LCD_indexAD[Y_Pos][AD_Y_Pos - 1][j] = index52[LCD_Temp[j]] + 1;
				//LCD_indexAD[k-1].LCD_poid[j]=index52[LCD_Temp[j]]+1;

			}
			LCD_indexAD[Y_Pos][AD_Y_Pos - 1][j] = index52[LCD_Temp[j]] + 1;
			LCD_indexAD[Y_Pos][AD_Y_Pos - 1][3] = 0;
			if (j == 1) {
				LCD_indexAD[Y_Pos][AD_Y_Pos - 1][2] = 12;
			}
			//disp_chn816(18,29+(i-1)*18,LCD_index2[i-1],1);
			disp_chn816(17, 6 + AD_Y_Pos * 20, LCD_indexAD[Y_Pos][AD_Y_Pos - 1],
					1);

		}

		else {
			for (j = 0; j < 13; j++) {
				if (LCD_Temp[j] == 10)
					LCD_Temp[j] = 0x2e;
				else if (LCD_Temp[j] == 11) {
					LCD_Temp[j] = 0;
					break;
				} else
					LCD_Temp[j] = (LCD_Temp[j] | 0x30);
			}
			LCD_Temp[Numlenth] = 0;
			switch (AD_Y_Pos) {
			case 2:
				ADPARA(Y_Pos).ADUV.b=string_to_float(LCD_Temp);
				break;
				case 3:
				ADPARA(Y_Pos).ADLV.b=string_to_float(LCD_Temp);
				break;
				case 4:
				ADPARA(Y_Pos).U_Alarmlimt.b=string_to_float(LCD_Temp);
				break;
				case 5:
				ADPARA(Y_Pos).L_Alarmlimt.b=string_to_float(LCD_Temp);
				break;
				default:
				break;

			}
			//AD_parameter.AD_i[k-1].ADUV.b=string_to_float(LCD_Temp);
			Symbol.ADP_change = 1;
			if (LCDSymbol.LCD_Dot)
				Pre_LCD_Dot[AD_Y_Pos - 2] |=
						((char) LCDSymbol.LCD_Dot << Y_Pos);
			else
				Pre_LCD_Dot[AD_Y_Pos - 2] &=
						((char) LCDSymbol.LCD_Dot << Y_Pos);
		}

		//------------------------------------------
		for (j = 0; j < Numlenth; j++) {
			if (LCD_Temp[j] == 0x2e)
				LCD_Temp[j] = 11;
			else if (LCD_Temp[j] == 0) {
				if (AD_Y_Pos == 1)
					LCD_Temp[j] = 13;
				else
					LCD_Temp[j] = 0;
				break;
			} else if (LCD_Temp[j] == 'S')
				LCD_Temp[j] = 11;
			else {
				LCD_Temp[j] &= 0x0f;
				if (AD_Y_Pos != 1)
					LCD_Temp[j] += 1;
			}

			if (AD_Y_Pos >= 2)
				LCD_indexAD[Y_Pos][AD_Y_Pos - 1][j] = LCD_Temp[j];
		}

		//-----------------------------------------

		if (AD_Y_Pos >= 2)
			LCD_indexAD[Y_Pos][AD_Y_Pos - 1][j] = 0;
		if (AD_Y_Pos != 1) {
			if (AD_Y_Pos == 0)
				disp_chn816(17, 6, index40[LCD_NoPt], 1);
			//disp_chn816(17,20,LCD_indexAD[k-1].LCD_poid,1);
			else {
				clrramBlock(17, 6 + AD_Y_Pos * 20, 13);
				disp_chn816(17, 6 + AD_Y_Pos * 20, LCD_Temp, 1);
			}
		}

		//}
		break;
	case 2:
		if (AD_Y_Pos == 0)
			;
		else if (AD_Y_Pos == 1) {

			{
				LCD_Temp[LCD_NumPos] = index52[LCD_NoPt];
				clrramBlock(17 + LCD_NumPos, 26, 1);
				disp_chn816_1(17 + LCD_NumPos, 26, index52[LCD_NoPt], 1);
				if (LCD_NumPos == 0)
					;	//LCD_NumPos=Numlenth-1;
				else
					LCD_NumPos--;
				clrramBlock(17 + LCD_NumPos, 26, 1);
				if (LCD_Temp[LCD_NumPos] == 16)
					LCD_NoPt = 12;
				else if (LCD_Temp[LCD_NumPos] == 17)
					LCD_NoPt = 15;
				else if (LCD_Temp[LCD_NumPos] == 26)
					LCD_NoPt = 11;
				else if (LCD_Temp[LCD_NumPos] == 23)
					LCD_NoPt = 13;
				else if (LCD_Temp[LCD_NumPos] == 24)
					LCD_NoPt = 14;
				else
					LCD_NoPt = LCD_Temp[LCD_NumPos];
				if ((LCD_NoPt < 0) || (LCD_NoPt > 15))
					LCD_NoPt = 0;
				disp_chn816_1(17 + LCD_NumPos, 26, index52[LCD_NoPt], 0);
			}
		} else {
			if (LCD_NoPt == 10)
				LCDSymbol.LCD_Dot = 1;

			LCD_Temp[LCD_NumPos] = LCD_NoPt;
			clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 1);
			disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, LCD_NoPt, 1);
			if (LCD_NumPos == 0)
				;
			//LCD_NumPos=Numlenth-1;
			else
				LCD_NumPos--;
			clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 1);
			LCD_NoPt = LCD_Temp[LCD_NumPos];
			if ((LCD_NoPt < 0) || (LCD_NoPt > 10))
				LCD_NoPt = 0;
			disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, LCD_NoPt, 0);
			if (LCD_NoPt == 10)
				LCDSymbol.LCD_Dot = 0;
		}
		break;
	case 3:
		if (AD_Y_Pos == 0) {
			clrramBlock(17, 6 + AD_Y_Pos * 20, 13);
			if (LCD_NoPt == 2)
				LCD_NoPt = 0;
			else
				LCD_NoPt++;
			disp_chn816(17, 6 + AD_Y_Pos * 20, index40[LCD_NoPt], 0);
		} else if (AD_Y_Pos == 1) {
			clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 1);
			if (LCD_NumPos != 0) {
				if (LCD_NoPt == 15)
					LCD_NoPt = 0;
				else
					LCD_NoPt++;
				disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20,
						index52[LCD_NoPt], 0);
			} else {
				//if(LCD_NoPt==13)
				if (LCD_NoPt == 15)
					LCD_NoPt = 0;
				else
					LCD_NoPt++;

				clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 3);
				disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20,
						index52[LCD_NoPt], 0);
				disp_chn816_1(17 + LCD_NumPos + 1, 6 + AD_Y_Pos * 20, 11, 1);
				disp_chn816_1(17 + LCD_NumPos + 2, 6 + AD_Y_Pos * 20, 11, 1);
				LCD_Temp[1] = 11;
				LCD_Temp[2] = 11;

			}
		} else {
			clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 1);
			if (LCDSymbol.LCD_Dot) {
				if (LCD_NoPt == 9)
					LCD_NoPt = 0;
				else
					LCD_NoPt++;
			} else {
				if (LCD_NumPos == 0) {
					if (LCD_NoPt == 9)
						LCD_NoPt = 0;
					else
						LCD_NoPt++;
				} else {
					if (LCD_NoPt == 11)
						LCD_NoPt = 0;
					else
						LCD_NoPt++;
				}
			}
			//if(i==1)
			//	disp_chn816_1(17+LCD_NumPos,20+(i-1)*20,index37[LCD_NoPt],0);
			//else
			disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, LCD_NoPt, 0);
		}
		break;
	case 4:
		if (AD_Y_Pos == 0) {
			clrramBlock(17, 6 + AD_Y_Pos * 20, 13);
			if (LCD_NoPt == 0)
				LCD_NoPt = 2;
			else
				LCD_NoPt--;
			disp_chn816(17, 6 + AD_Y_Pos * 20, index40[LCD_NoPt], 0);
		} else if (AD_Y_Pos == 1) {
			clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 1);
			if (LCD_NumPos != 0) {
				if (LCD_NoPt == 0)
					LCD_NoPt = 15;
				else
					LCD_NoPt--;
				disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20,
						index52[LCD_NoPt], 0);
			} else {
				if (LCD_NoPt == 0)
					LCD_NoPt = 15;
				else
					LCD_NoPt--;

				clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 3);
				disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20,
						index52[LCD_NoPt], 0);
				disp_chn816_1(17 + LCD_NumPos + 1, 6 + AD_Y_Pos * 20, 11, 1);
				disp_chn816_1(17 + LCD_NumPos + 2, 6 + AD_Y_Pos * 20, 11, 1);
				LCD_Temp[1] = 11;
				LCD_Temp[2] = 11;

			}

		} else {
			if (LCDSymbol.LCD_Dot) {
				if (LCD_NoPt == 0)
					LCD_NoPt = 9;
				else
					LCD_NoPt--;
			} else {
				if (LCD_NumPos == 0) {
					if (LCD_NoPt == 0)
						LCD_NoPt = 9;
					else
						LCD_NoPt--;
				} else {
					if (LCD_NoPt == 0)
						LCD_NoPt = 11;
					else
						LCD_NoPt--;
				}
			}
			clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 1);
			//if(i==1)
			//	disp_chn816_1(17+LCD_NumPos,6+AD_Y_Pos*20,index37[LCD_NoPt],0);
			//	else
			disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, LCD_NoPt, 0);
		}
		break;
	case 5:
		if (AD_Y_Pos == 0) {
			clrramBlock(17, 6, 9);
			disp_chn816(17, 6, index40[parameter.AD_i[Y_Pos].AI_Type], 1);
		} else {
			clrramBlock(17, 6 + AD_Y_Pos * 20, 14);

			disp_chn816(17, 6 + AD_Y_Pos * 20, LCD_indexAD[Y_Pos][AD_Y_Pos - 1],
					1);
		}
		LCD_NoPt = 0;
		LCD_NumPos = 0;
		LCDSymbol.LCD_set = 0;
		Par_Select = 1;

		break;
	case 6:
		if (AD_Y_Pos == 0)
			;
		else if (AD_Y_Pos == 1) {

			{
				LCD_Temp[LCD_NumPos] = index52[LCD_NoPt];
				clrramBlock(17 + LCD_NumPos, 26, 1);
				disp_chn816_1(17 + LCD_NumPos, 26, index52[LCD_NoPt], 1);
				if (LCD_NumPos == 2)
					;			//LCD_NumPos=Numlenth-1;
				else
					LCD_NumPos++;
				clrramBlock(17 + LCD_NumPos, 26, 1);
				if (LCD_Temp[LCD_NumPos] == 16)
					LCD_NoPt = 12;
				else if (LCD_Temp[LCD_NumPos] == 17)
					LCD_NoPt = 15;
				else if (LCD_Temp[LCD_NumPos] == 26)
					LCD_NoPt = 11;
				else if (LCD_Temp[LCD_NumPos] == 23)
					LCD_NoPt = 13;
				else if (LCD_Temp[LCD_NumPos] == 24)
					LCD_NoPt = 14;
				else
					LCD_NoPt = LCD_Temp[LCD_NumPos];
				if ((LCD_NoPt < 0) || (LCD_NoPt > 15))
					LCD_NoPt = 0;
				disp_chn816_1(17 + LCD_NumPos, 26, index52[LCD_NoPt], 0);
			}
		} else {
			if (LCD_NoPt == 10)
				LCDSymbol.LCD_Dot = 1;
			LCD_Temp[LCD_NumPos] = LCD_NoPt;
			clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 1);
			disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, LCD_NoPt, 1);

			if (LCD_NumPos == (Numlenth - 1))
				LCD_NumPos = 0;
			else
				LCD_NumPos++;
			LCD_NoPt = LCD_Temp[LCD_NumPos];
			if ((LCD_NoPt < 0) || (LCD_NoPt > 10))
				LCD_NoPt = 0;
			clrramBlock(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, 1);
			disp_chn816_1(17 + LCD_NumPos, 6 + AD_Y_Pos * 20, LCD_NoPt, 0);
			if (LCD_NoPt == 10)
				LCDSymbol.LCD_Dot = 0;
		}
		break;
	default:
		break;
	}
}

void disp70()
{
	INT8U i, PoN;

	if (Symbol.LCD_deal) {
		clrram();
		Symbol.LCD_deal = 0;
		disp_yline(5, 0);

		for (i = 0; i < 8; i++) {
			index10[2] = i + 2;
			if (i == 0)
				PoN = 0;
			else
				PoN = 1;
			disp_chn816(1, 0 + i * 16, index10, PoN);

		}

		index10[2] = 2;
		/*disp_chn816(14,0,index10,1);
		 disp_chn1616(17,0,a,1);*/

		disp_chn1616(6, 6, AI_index[0], 1);
		disp_chn1616(6, 26, AI_index[1], 1);
		disp_chn1616(6, 46, AI_index[2], 1);
		disp_chn1616(6, 66, AI_index[3], 1);
		disp_chn1616(6, 86, AI_index[4], 1);
		disp_chn1616(6, 106, AI_index[5], 1);

		//disp_chn816(16,10+i*16,indexad,1);
		disp_chn816(17, 26, LCD_indexAD[0][0], 1); //污染物编号
		disp_chn816(17, 6, index40[parameter.AD_i[0].AI_Type], 1);    //信号量范围
		disp_chn816(17, 46, LCD_indexAD[0][1], 1); //量程上
		disp_chn816(17, 66, LCD_indexAD[0][2], 1); //量程下
		disp_chn816(17, 86, LCD_indexAD[0][3], 1); //报警上
		disp_chn816(17, 106, LCD_indexAD[0][4], 1); //报警下
	}

	if (LCDSymbol.LCD_set) {
		//LCD_set=0;
		if (AD_Y_Pos == 1)
			Numlenth = 3;
		else
			Numlenth = 13;
		disp_SetNum_ADx(Numlenth);
	}

	else if (Par_Select) {

		switch (KeyV) {
		case 1:
			LCDSymbol.LCD_set = 1;
			Par_Select = 0;
			if (AD_Y_Pos == 0) {
				LCD_NoPt = parameter.AD_i[Y_Pos].AI_Type;
				clrramBlock(17, 6, 13);
				disp_chn816(17, 6, index40[LCD_NoPt], 0);
			} else if (AD_Y_Pos == 1) {
				if (LCD_indexAD[Y_Pos][AD_Y_Pos - 1][0] == 17) {
					LCD_NoPt = 13;

				} else if (LCD_indexAD[Y_Pos][AD_Y_Pos - 1][0] == 18) {
					LCD_NoPt = 12;

				} else if (LCD_indexAD[Y_Pos][AD_Y_Pos - 1][0] == 12)
					LCD_NoPt = 10;

				else if (LCD_indexAD[Y_Pos][AD_Y_Pos - 1][0] == 27)
					LCD_NoPt = 11;
				else
					LCD_NoPt = LCD_indexAD[Y_Pos][AD_Y_Pos - 1][0] - 1;
				for (i = 0; i < 3; i++)
					LCD_Temp[i] = LCD_indexAD[Y_Pos][AD_Y_Pos - 1][i] - 1;
				LCD_NumPos = 0;
				clrramBlock(17, 26, 1);
				disp_chn816_1(17, 26, index37[LCD_NoPt], 0);
			} else {
				LCD_NoPt = LCD_indexAD[Y_Pos][AD_Y_Pos - 1][0] - 1;
				LCDSymbol.LCD_Dot = (Pre_LCD_Dot[AD_Y_Pos - 2] >> Y_Pos);
				for (i = 0; i < 13; i++) {
					if (LCD_indexAD[Y_Pos][AD_Y_Pos - 1][i] != 0)
						LCD_Temp[i] = LCD_indexAD[Y_Pos][AD_Y_Pos - 1][i] - 1;
					else {
						for (; i < 13; i++)
							LCD_Temp[i] = 11;
						break;
					}
				}
				LCD_NumPos = 0;
				clrramBlock(17, 6 + 20 * AD_Y_Pos, 1);
				disp_chn816_1(17, 6 + 20 * AD_Y_Pos, LCD_NoPt, 0);
			}

			break;
		case 3:
			AD_pre_Y_Pos = AD_Y_Pos;

			if (AD_Y_Pos == 5)
				AD_Y_Pos = 0;
			else
				AD_Y_Pos++;

			clrramBlock(6, 6 + AD_pre_Y_Pos * 20, 10);
			disp_chn1616(6, 6 + AD_pre_Y_Pos * 20, AI_index[AD_pre_Y_Pos], 1);

			clrramBlock(6, 6 + AD_Y_Pos * 20, 8);
			disp_chn1616(6, 6 + AD_Y_Pos * 20, AI_index[AD_Y_Pos], 0);

			break;
		case 4:
			AD_pre_Y_Pos = AD_Y_Pos;

			if (AD_Y_Pos == 0)
				AD_Y_Pos = 5;
			else
				AD_Y_Pos--;

			clrramBlock(6, 6 + AD_pre_Y_Pos * 20, 10);
			disp_chn1616(6, 6 + AD_pre_Y_Pos * 20, AI_index[AD_pre_Y_Pos], 1);

			clrramBlock(6, 6 + AD_Y_Pos * 20, 10);
			disp_chn1616(6, 6 + AD_Y_Pos * 20, AI_index[AD_Y_Pos], 0);
			break;
		case 5:
			clrramBlock(6, 6 + AD_Y_Pos * 20, 10);
			disp_chn1616(6, 6 + AD_Y_Pos * 20, AI_index[AD_Y_Pos], 1);
			AD_Y_Pos = 0;
			Par_Select = 0;
			break;
		default:
			break;
		}
	}

	else {
		switch (KeyV) {
		case 1:
			Par_Select = 1;
			AD_Y_Pos = 0;
			clrramBlock(6, 6, 10);
			//disp_chn1616(6,6,AI_index[0],0);
			disp_chn1616(6, 6, AI_index[0], 0);    //信号量范围
			break;
		case 3:

			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 7)
				Y_Pos = 0;
			else
				Y_Pos++;

			clrramBlock(1, pre_Y_Pos * 16, 3);
			index10[2] = pre_Y_Pos + 2;
			disp_chn816(1, pre_Y_Pos * 16, index10, 1);

			clrramBlock(17, 6, 12);
			clrramBlock(17, 26, 12);
			clrramBlock(17, 46, 12);
			clrramBlock(17, 66, 12);
			clrramBlock(17, 86, 12);
			clrramBlock(17, 106, 12);

			clrramBlock(1, Y_Pos * 16, 3);
			index10[2] = Y_Pos + 2;
			disp_chn816(1, Y_Pos * 16, index10, 0);

			disp_chn816(17, 26, LCD_indexAD[Y_Pos][0], 1); //污染物编号
			disp_chn816(17, 6, index40[parameter.AD_i[Y_Pos].AI_Type], 1); //信号量范围
			disp_chn816(17, 46, LCD_indexAD[Y_Pos][1], 1); //量程上
			disp_chn816(17, 66, LCD_indexAD[Y_Pos][2], 1); //量程下
			disp_chn816(17, 86, LCD_indexAD[Y_Pos][3], 1); //报警上
			disp_chn816(17, 106, LCD_indexAD[Y_Pos][4], 1); //报警下

			break;
		case 4:
			pre_Y_Pos = Y_Pos;

			if (Y_Pos == 0)
				Y_Pos = 7;
			else
				Y_Pos--;

			clrramBlock(1, pre_Y_Pos * 16, 3);
			index10[2] = pre_Y_Pos + 2;
			disp_chn816(1, pre_Y_Pos * 16, index10, 1);

			clrramBlock(17, 6, 12);
			clrramBlock(17, 26, 12);
			clrramBlock(17, 46, 12);
			clrramBlock(17, 66, 12);
			clrramBlock(17, 86, 12);
			clrramBlock(17, 106, 12);

			clrramBlock(1, Y_Pos * 16, 3);
			index10[2] = Y_Pos + 2;
			disp_chn816(1, Y_Pos * 16, index10, 0);

			disp_chn816(17, 26, LCD_indexAD[Y_Pos][0], 1); //污染物编号
			disp_chn816(17, 6, index40[parameter.AD_i[Y_Pos].AI_Type], 1); //信号量范围
			disp_chn816(17, 46, LCD_indexAD[Y_Pos][1], 1); //量程上
			disp_chn816(17, 66, LCD_indexAD[Y_Pos][2], 1); //量程下
			disp_chn816(17, 86, LCD_indexAD[Y_Pos][3], 1); //报警上
			disp_chn816(17, 106, LCD_indexAD[Y_Pos][4], 1); //报警下

			break;
		case 5:
			LCD_page = 50;
			Symbol.LCD_deal = 1;
			Symbol.LCD_Page_Change = 1;
			Y_Pos = 0;
			break;
		default:
			break;
		}
	}

}

void disp90() //DO设置
{
	INT8U i, j;
	INT16U tempDI;
	//INT8U *p;
	if ((Symbol.LCD_deal) && (Symbol.LCD_DO == 0)) {
		Symbol.LCD_deal = 0;
		clrram();
		index29[2] = 0;
		disp_chn816(12, 6, index29, 1);
		//p=index11+2;
		//disp_chn1616(14,6,p,1);
		disp_chn1616(14, 6, index39, 1);

		index29[2] = 2;
		disp_chn816(5, 32, index29, 1);
		j = RealData.R_D.DO & 0x01;
		LCD_Temp[0] = j;
		if (j == 0) {
			LCDSymbol.LCD_DOS = 0;
			disp_chn1616_1(5, 52, 87, 0);
		} else {
			LCDSymbol.LCD_DOS = 1;
			disp_chn1616_1(5, 52, 88, 0);
		}

		for (i = 1; i < 4; i++) {
			index29[2] = i + 2;
			disp_chn816(5 + i * 6, 32, index29, 1);
			j = (RealData.R_D.DO >> i) & 0x01;
			LCD_Temp[i] = j;
			if (j == 0)
				disp_chn1616_1(5 + 6 * i, 52, 87, 1);
			else
				disp_chn1616_1(5 + 6 * i, 52, 88, 1);
		}
		for (i = 0; i < 4; i++) {
			index29[2] = i + 6;
			disp_chn816(5 + i * 6, 76, index29, 1);
			j = (RealData.R_D.DO >> (i + 4)) & 0x01;
			LCD_Temp[i + 4] = j;
			if (j == 0)
				disp_chn1616_1(5 + 6 * i, 96, 87, 1);
			else
				disp_chn1616_1(5 + 6 * i, 96, 88, 1);
		}

	}
	switch (KeyV) {
	case 1:
		if ((LCD_NumPos == 0) && (LCD_DOP == 1))	//DO5
				{
			tempDI = DIInput();
			if ((tempDI & 0xc000) == 0x8000)	//判断DI15，16是否为0，1
					{
				RealData.R_D.DO |= 0x10;	//置DO5
				//SFRPAGE =0x0f;
				DOOutput(RealData.R_D.DO);
				/*
				 DO_Disable;
				 Delay_10_uS();
				 P1OUT=RealData.R_D.DO;
				 Delay_10_uS();
				 DO_Enable;
				 Delay_10_uS();
				 DO_Disable;*/
				Symbol.DO5_DI15 = 1;
				Symbol.LCD_Control = 1;
				clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
				LCDSymbol.LCD_DOS = (~LCDSymbol.LCD_DOS);
				LCD_Temp[LCD_NumPos + LCD_DOP * 4] = LCDSymbol.LCD_DOS;
				disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
						index33[LCDSymbol.LCD_DOS], 0);
				//EXRESULT=1;
			}
		} else if ((LCD_NumPos == 1) && (LCD_DOP == 1))	//DO6
				{
			tempDI = DIInput();
			if ((tempDI & 0xc000) == 0x4000) {
				RealData.R_D.DO |= 0x20;//RealData.R_D.DO|(value[0]<<(value[1]-1));
				//SFRPAGE =0x0f;
				DOOutput(RealData.R_D.DO);
				/*
				 DO_Disable;
				 Delay_10_uS();
				 P1OUT=RealData.R_D.DO;
				 Delay_10_uS();
				 DO_Enable;
				 Delay_10_uS();
				 DO_Disable;*/
				Symbol.DO6_DI16 = 1;
				Symbol.LCD_Control = 1;
				clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
				LCDSymbol.LCD_DOS = (~LCDSymbol.LCD_DOS);
				LCD_Temp[LCD_NumPos + LCD_DOP * 4] = LCDSymbol.LCD_DOS;
				disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
						index33[LCDSymbol.LCD_DOS], 0);
			}
		} else {
			clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
			LCDSymbol.LCD_DOS = (~LCDSymbol.LCD_DOS);
			LCD_Temp[LCD_NumPos + LCD_DOP * 4] = LCDSymbol.LCD_DOS;
			if (LCDSymbol.LCD_DOS)
				RealData.R_D.DO |= (LCD_Temp[LCD_NumPos + LCD_DOP * 4]
						<< (LCD_NumPos + LCD_DOP * 4));
			else
				RealData.R_D.DO &=
						(~((LCD_Temp[LCD_NumPos + LCD_DOP * 4] | 0x01)
								<< (LCD_NumPos + LCD_DOP * 4)));

			//SFRPAGE =0x0f;
			DOOutput(RealData.R_D.DO);
			/*
			 DO_Disable;
			 Delay_10_uS();
			 P1OUT=RealData.R_D.DO;
			 Delay_10_uS();
			 DO_Enable;
			 Delay_10_uS();
			 DO_Disable;*/
			disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
					index33[LCDSymbol.LCD_DOS], 0);
		}
		break;
	case 2:
		clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
		disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
				index33[LCDSymbol.LCD_DOS], 1);
		if (LCD_NumPos == 0)
			LCD_NumPos = 3;
		else
			LCD_NumPos--;
		clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
		LCDSymbol.LCD_DOS = LCD_Temp[LCD_NumPos + LCD_DOP * 4];
		disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
				index33[LCDSymbol.LCD_DOS], 0);
		break;
	case 3:
		clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
		disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
				index33[LCDSymbol.LCD_DOS], 1);
		if (LCD_DOP == 1)
			LCD_DOP = 0;
		else
			LCD_DOP = 1;
		//LCD_DOP=(~LCD_DOP);
		clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
		LCDSymbol.LCD_DOS = LCD_Temp[LCD_NumPos + LCD_DOP * 4];
		disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
				index33[LCDSymbol.LCD_DOS], 0);
		break;
	case 4:
		clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
		disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
				index33[LCDSymbol.LCD_DOS], 1);
		if (LCD_DOP == 0)
			LCD_DOP = 1;
		else
			LCD_DOP = 0;
		//LCD_DOP=(~LCD_DOP);
		clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
		LCDSymbol.LCD_DOS = LCD_Temp[LCD_NumPos + LCD_DOP * 4];
		disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
				index33[LCDSymbol.LCD_DOS], 0);
		break;
	case 5:
		LCD_page = 50;
		Symbol.LCD_deal = 1;
		Symbol.LCD_Page_Change = 1;
		Y_Pos = 0;
		break;
	case 6:
		clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
		disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
				index33[LCDSymbol.LCD_DOS], 1);
		if (LCD_NumPos == 3)
			LCD_NumPos = 0;
		else
			LCD_NumPos++;
		clrramBlock(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44, 2);
		LCDSymbol.LCD_DOS = LCD_Temp[LCD_NumPos + LCD_DOP * 4];
		disp_chn1616_1(5 + 6 * LCD_NumPos, 52 + LCD_DOP * 44,
				index33[LCDSymbol.LCD_DOS], 0);
		break;
	default:
		break;
	}
	if (Symbol.LCD_DO) {
		Symbol.LCD_DO = 0;
		Symbol.LCD_deal = 0;
		for (i = 0; i < 2; i++) {
			clrramBlock(5 + 6 * i, 96, 2);
			j = (RealData.R_D.DO >> (i + 4)) & 0x01;
			if (j == 0) {
				if (LCD_NumPos == i)
					disp_chn1616_1(5 + 6 * i, 96, 87, 0);
				else
					disp_chn1616_1(5 + 6 * i, 96, 87, 1);

			} else {
				if (LCD_NumPos == i)
					disp_chn1616_1(5 + 6 * i, 96, 88, 0);
				else
					disp_chn1616_1(5 + 6 * i, 96, 88, 1);
			}
			LCD_Temp[LCD_NumPos + LCD_DOP * 4] = j;
			LCDSymbol.LCD_DOS = j;
		}
	}

}
/*
 INT8U KeyRead()
 {
 INT8U KeyIN=0;
 INT8U p7in,p8in;

 p7in = P7IN;
 p8in = P8IN;

 KeyIN  = (((p7in&0x80)>>3)+((p7in&0x40)>>1)+((p8in&0x08)>>3)+((p8in&0x04)>>1)+((p8in&0x02)<<1)+((p8in&0x01)<<3));
 KeyIN |= 0xC0;

 return(KeyIN);
 }
 */
INT8U getkey() //确定键值
{
	INT8U keyV1, keyV2;
	INT8U KeyValue;

	keyV1 = KEYREAD();
	Delay_10_uS();
	Delay_10_uS();
	keyV2 = KEYREAD();

	if ((keyV1 == keyV2) && (keyV1 != 0xff)) {

		if (Symbol.Pass_id == 0) {
			LCD_light_ON;
			Symbol.Pass_id = 1;
		} else
			LCD_light = 0;

		switch (keyV1) {
		case KEY_ENTER: //0xfd:		//确定

			LCDSymbol.LCD_backdoor = 0;
			LCD_RSTime = 0;
			//return(1);
			KeyValue = 1;

			break;
		case KEY_LEFT: //0xfb:		//左
			LCDSymbol.LCD_backdoor = 0;
			LCD_RSTime = 0;
			//return(2);
			KeyValue = 2;
			break;
		case KEY_DOWN: //0xf7:		//下
			LCDSymbol.LCD_backdoor = 0;
			LCD_RSTime = 0;
			//return(3);
			KeyValue = 3;
			break;
		case KEY_UP: //0xef:		//上
			LCDSymbol.LCD_backdoor = 0;
			LCD_RSTime = 0;
			//return(4);
			KeyValue = 4;
			break;
		case KEY_CANCEL: //0xdf:		//取消
			LCDSymbol.LCD_backdoor = 0;
			LCD_RSTime = 0;
			//return(5);
			KeyValue = 5;
			break;
		case KEY_RIGHT: //0xbf:		//右
			LCDSymbol.LCD_backdoor = 0;
			LCD_RSTime = 0;
			//return(6);
			KeyValue = 6;
			break;
		case KEY_RESET: //0xf9:		//复位 取消 确定 下 左同时按下保持三秒
			LCD_RSTime++;
			if (LCD_RSTime >= 8) {
				LCD_RST = 1;
				_BIC_SR(GIE);
				AT24C64_W(index1, 0x00, 1);
				//extern ?reset_vector;
				//extern __program_start;
				asm("MOV.W #0FFFEh,R4");
				asm("MOV.W @R4,PC");
				//asm("bra ");
				_BIC_SR(GIE);
			}
			LCDSymbol.LCD_backdoor = 0;
			//return(7);
			KeyValue = 7;
			break;
		case LCD_RESET:          //0xf9:		//复位 取消 确定 下 左同时按下保持三秒
			LCD_RSTime++;
			if (LCD_RSTime >= 8)
				Screen_RST = 1;
			//return(8);
			KeyValue = 8;
			break;
		case BACK_DOOR0:			//左右键同时按3秒 再按ESC
			if ((LCDSymbol.LCD_backdoor == 0) && (LCD_page == 30)) {
				LCD_RSTime++;
				if (LCD_RSTime >= 4)
					LCDSymbol.LCD_backdoor = 1;
			}
			//return(9);
			KeyValue = 9;
			break;
		case BACK_DOOR1:		//左右+ESC
			if (LCDSymbol.LCD_backdoor) {
				LCD_RSTime++;
				if (LCD_RSTime >= 8) {
					LCD_page = 50;
					Symbol.LCD_deal = 1;
					LCDSymbol.LCD_backdoor = 0;
					LCD_RSTime = 0;
					Symbol.LCD_Page_Change = 1;
					Y_Pos = 0;
				}
			}
			//return(10);
			KeyValue = 10;
			break;
		default:
			//return(0);
			KeyValue = 0;
			break;
		}
		return (KeyValue);
	} else {
		KeyValue = 0;
		return (KeyValue);
	}

}

void LCD_disp()
{
	switch (LCD_page) {
	case 10:

		disp10();
		break;
	case 20:

		disp20();
		break;
	case 30:

		disp30();
		break;

	case 41:

		disp41();
		break;
	case 42:

		disp42();
		break;
	case 43:

		disp43();
		break;
	case 44:
		disp44();
		break;
	case 45:
		disp45();
		break;
	case 50:

		disp50();
		break;

	case 56:
		disp56();
		break;
	case 57:
		disp57();
		break;
	case 58:
		disp58();
		break;
	case 60:

		disp60();
		break;

	case 70:

		disp70();
		break;

	case 90:
		disp90();
		break;
	case 100:
		disp100();
		break;
	case 101:
		disp101();
		break;
	case 102:
		disp102();
		break;
	case 200:
		disp200();
		break;
	default:
		break;
	}
	KeyV = 0;

}

void index_initial(void)
{
	INT8U i, j;
	INT8U ftstring[18];
	//测试用
	//uchar a[4];
	for (i = 0; i < 7; i++)
		LCD_index1[0][i] = LCD_user_pw[i];
	LCD_indexs(parameter.sys_parameter.mn, 14, LCD_index1[1]);  //系统标识值 14位
	LCD_indexs(System_Time, 14, LCD_index1[2]);					//系统时间值 14位
	LCD_indexs(parameter.sys_parameter.resendtime, 2, LCD_index1[3]);//重发次数 2位
	LCD_indexs(parameter.sys_parameter.st, 2, LCD_index1[4]);		//系统编号
	//////WDTCN     = 0xA5;	//喂狗
	LCD_indexs(parameter.sys_parameter.overtime, 5, LCD_index2[0]);  //超时时间 5位
	LCD_indexs(parameter.sys_parameter.warntime, 5, LCD_index2[1]);  //报警时间 5位
	LCD_indexs(parameter.sys_parameter.reporttime, 4, LCD_index2[2]); //数据上报间隔 2位
	LCD_indexs(parameter.sys_parameter.rd_interval, 3, LCD_index2[3]); //实时上报间隔 3位

	for (i = 0; i < 8; i++) {
		//污染物编号
		for (j = 0; j < 3; j++) {
			if (ADPARA(i).po_id[j]=='P')
			LCD_indexAD[i][0][j]=18;
			else if(ADPARA(i).po_id[j]=='S')
			LCD_indexAD[i][0][j]=17;
			else if(ADPARA(i).po_id[j]=='f')
			LCD_indexAD[i][0][j]=24;
			else if(ADPARA(i).po_id[j]=='k')
			LCD_indexAD[i][0][j]=25;
			else if(ADPARA(i).po_id[j]=='B')
			LCD_indexAD[i][0][j]=27;
			else if(ADPARA(i).po_id[j]==0)
			LCD_indexAD[i][0][j]=12;
			else
			LCD_indexAD[i][0][j]=(ADPARA(i).po_id[j]&0x0f)+1;
			//	a[j]=LCD_indexAD[i].LCD_poid[j];
		}
		LCD_indexAD[i][0][3]=0;
		//////WDTCN     = 0xA5;	//喂狗
		float_to_string(ADPARA(i).ADUV.b,ftstring);
		//////WDTCN     = 0xA5;	//喂狗
		for(j=0;j<13;j++)
		{
			if(ftstring[j]==0x2e)	//点
			{
				LCD_indexAD[i][1][j]=11;
				Pre_LCD_Dot[0]|=(1<<i);
			}
			else if (ftstring[j]=='\0')
			{
				LCD_indexAD[i][1][j]=0;	//12;
				break;
			}
			else LCD_indexAD[i][1][j]=(ftstring[j]&0x0f)+1;
		}
		for(;j<13;j++)
		LCD_indexAD[i][1][j]=0;
		LCD_indexAD[i][1][13]=0;
		//////WDTCN     = 0xA5;	//喂狗

		float_to_string(ADPARA(i).ADLV.b,ftstring);
		//////WDTCN     = 0xA5;	//喂狗
		for(j=0;j<13;j++)
		{
			if(ftstring[j]==0x2e)	//点
			{
				LCD_indexAD[i][2][j]=11;
				Pre_LCD_Dot[1]|=(1<<i);
			}
			else if (ftstring[j]=='\0')
			{
				LCD_indexAD[i][2][j]=0;	//12;
				break;
			}
			else LCD_indexAD[i][2][j]=(ftstring[j]&0x0f)+1;
		}
		for(;j<13;j++)
		LCD_indexAD[i][2][j]=0;
		LCD_indexAD[i][2][13]=0;

		//////WDTCN     = 0xA5;	//喂狗
		float_to_string(ADPARA(i).U_Alarmlimt.b,ftstring);
		//////WDTCN     = 0xA5;	//喂狗
		for(j=0;j<13;j++)
		{
			if(ftstring[j]==0x2e)	//点
			{
				LCD_indexAD[i][3][j]=11;
				Pre_LCD_Dot[2]|=(1<<i);
			}
			else if (ftstring[j]=='\0')
			{
				LCD_indexAD[i][3][j]=0;
				break;
			}
			else LCD_indexAD[i][3][j]=(ftstring[j]&0x0f)+1;
		}
		for(;j<13;j++)
		LCD_indexAD[i][3][j]=0;
		LCD_indexAD[i][3][13]=0;
		//////WDTCN     = 0xA5;	//喂狗
		float_to_string(ADPARA(i).L_Alarmlimt.b,ftstring);
		//////WDTCN     = 0xA5;	//喂狗
		for(j=0;j<13;j++)
		{
			if(ftstring[j]==0x2e)	//点
			{
				LCD_indexAD[i][4][j]=11;
				Pre_LCD_Dot[3]|=(1<<i);
			}
			else if (ftstring[j]=='\0')
			{
				LCD_indexAD[i][4][j]=0;	//12;
				break;
			}
			else LCD_indexAD[i][4][j]=(ftstring[j]&0x0f)+1;
		}
		for(;j<13;j++)
		LCD_indexAD[i][4][j]=0;
		LCD_indexAD[i][4][13]=0;

	}
	//-------------------------------------------------

}

//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
/*
 void main()
 {
 unsigned int x,y;

 WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
 //System_init();
 init_lcd ();
 //BackLight_1;
 //BackLight_0;
 LCD_lignt_OFF;
 while(1)
 {

 clrram();
 for(x=0;x<1000;x++)
 {
 for(y=0;y<1000;y++);
 }
 for(x=0;x<8;x++)
 {
 disp_chn1616(0,(0+16*x),index1,1);
 }
 for(x=0;x<1000;x++)
 {
 for(y=0;y<1000;y++);
 }
 }

 }
 */
//-------------------------------------------------------------
//-------------------------------------------------------------
