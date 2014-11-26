#include <msp430xG46x.h>
#include <string.h>

#define MAINFILE 1
#include "test.h"

int IO_init(void);

INT8U stop_watch_devstatus = 0;

extern const char zimo240128[30 * 64];
INT16U ADResult[8][10];

INT8U AD_CONVERTER = 0;
INT8U ADTimes = 0;

void Hjt212_UploadStatusMsg()
{
	INT8U cnt, tmp, state;
	char buf[5];

	for (cnt = 0; cnt < 2; cnt++) {
		tmp = RealData.R_D.DI[cnt];		//Intmp[i];

		state = (tmp >> 4) & 0x0f;
		if (state < 10) {
			buf[2 * cnt] = state | 0x30;		//输入状态
		} else {
			buf[2 * cnt] = (state - 9) + 0x40;		//输入状态
		}

		state = RealData.R_D.DI[cnt] & 0x0f;
		if (state < 10) {
			buf[2 * cnt + 1] = state | 0x30;		//输入状态
		} else {
			buf[2 * cnt + 1] = (state - 9) | 0x40;	//输入状态
		}
	}

	buf[4] = '\0';
	Symbol.ccc = 1;
	Response(5);
	Symbol.ccc = 0;

	strcat(CBAG.cbag_dynamic, "DI=");
	strcat(CBAG.cbag_dynamic, buf);

	Add_Send()
	;
}

void Dio_Run()
{
	static INT8U cnt = 0;
	INT16U temp, oldDI;
	INT16U DI_Convert = 0;

	oldDI = (RealData.R_D.DI[0] << 8) | RealData.R_D.DI[1];

	//DI状态查询
	if ((cnt++ % 5) == 0) {
		temp = DIInput();
		RealData.R_D.DI[0] = (INT8U) (temp >> 8);
		RealData.R_D.DI[1] = (INT8U) temp;
	}

	//DI15,16互锁
	if (Symbol.DO5_DI15) {
		if ((temp & 0xc000) == 0x4000) {
			DI_Convert = 0;

			Symbol.DO5_DI15 = 0;
			OldDO = RealData.R_D.DO;
			//清DO5
			RealData.R_D.DO &= 0xef;
			DOOutput(RealData.R_D.DO);
			if (Symbol.LCD_Control == 0) {
				e_result[0] = '1';
				Response(2);
			} else {
				Symbol.LCD_Control = 0;
			}

			if ((LCD_page == 41) || (LCD_page == 90)) {
				Symbol.LCD_DO = 1;
				Symbol.LCD_deal = 1;
			}
		} else {
			DI_Convert++;

			if (DI_Convert >= 4500) {
				Symbol.DO5_DI15 = 0;
				DI_Convert = 0;
				if (Symbol.LCD_Control == 0) {
					e_result[0] = '2';
					Response(2);
				} else
					Symbol.LCD_Control = 0;
				OldDO = RealData.R_D.DO;
				RealData.R_D.DO &= 0xef;		//清DO5
				DOOutput(RealData.R_D.DO);
				if ((LCD_page == 41) || (LCD_page == 90)) {
					Symbol.LCD_DO = 1;
					Symbol.LCD_deal = 1;
				}
			}
		}
	}

	if (Symbol.DO6_DI16) {
		if ((temp & 0xc000) == 0x8000) {
			DI_Convert = 0;
			Symbol.DO6_DI16 = 0;
			OldDO = RealData.R_D.DO;
			RealData.R_D.DO &= 0xdf;		//清DO6
			DOOutput(RealData.R_D.DO);
			if (Symbol.LCD_Control == 0) {
				e_result[0] = '1';
				Response(2);
			} else
				Symbol.LCD_Control = 0;
			if ((LCD_page == 41) || (LCD_page == 90)) {
				Symbol.LCD_DO = 1;
				Symbol.LCD_deal = 1;
			}
			//------------------DI15,16逢变则报-------------------------
		} else {
			DI_Convert++;
			if (DI_Convert >= 4500) {
				Symbol.DO6_DI16 = 0;
				DI_Convert = 0;
				if (Symbol.LCD_Control == 0) {
					e_result[0] = '2';
					Response(2);
				} else
					Symbol.LCD_Control = 0;
				OldDO = RealData.R_D.DO;
				RealData.R_D.DO &= 0xdf;				//清DO6
				DOOutput(RealData.R_D.DO);
				if ((LCD_page == 41) || (LCD_page == 90)) {
					Symbol.LCD_DO = 1;
					Symbol.LCD_deal = 1;
				}
			}
		}
	}

	if (temp != oldDI) {
		if ((temp & 0x3fff) != (oldDI & 0x3fff)) {
			Hjt212_UploadStatusMsg();
		} else {
			if ((temp & 0xc000) != 0x0000)
				Hjt212_UploadStatusMsg();
		}
		if ((Symbol.LCD_deal == 0) && (LCD_page == 42)) {
			Symbol.LCD_DI = 1;
			Symbol.LCD_deal = 1;
		} else
			Symbol.LCD_DI = 0;
	}
}

//采集到模拟量通道的数据 进行计算
void Adc_Run()
{
	static INT16U cnt = 0;
	INT8U i;

	if (AD_CONVERTER) {
		AD_CONVERTER = 0;
		//读AD转换数据
		AD_READ();
		ADC12CTL0 |= ADC12SC;

		if ((cnt++ % 1000) == 0) {
			ADCalculation();
			//更新LCD AD数据
			if ((Symbol.LCD_deal == 0) && (LCD_page == 43)) {
				Symbol.LCD_AD = 1;
				Symbol.LCD_deal = 1;
			}
		}
	}

	if ((Symbol.ADP_change) && ((LCD_page / 10) != 7)) {
		Symbol.ADP_change = 0;
		for (i = 0; i < 8; i++) {
			if (ADPARA(i).AI_Type==2)
			ADPARA(i).rate.b=(ADPARA(i).ADUV.b-ADPARA(i).ADLV.b)/0x666;
			else
			ADPARA(i).rate.b=(ADPARA(i).ADUV.b-ADPARA(i).ADLV.b)/0x1000;
		}
	}
}

void Led_Run()
{
	static INT8U RUN = 1;

	if (RUN) {
		RUN_ON; //应该是控制状态灯闪烁
		RUN = 0;
	} else {
		RUN = 1;
		RUN_OFF;
	}
}

void Rtc_Sync()
{
	v_Get1302();
}

//---------------Modbus 数据读取与处理---------------------------
void Modbus_Run()
{
	if (Symbol.Mod_Device_Check) {
		Mod_method = Mod_RealD;
		Mod_Command(Mod_method); //读取COD的实时值
		dataget_zhonglv(); //读取氨氮的实时值
		Symbol.Mod_Device_Check = 0;
	}

	if (Symbol.COM2orCOM3) {
		Symbol.COM2orCOM3 = 0;
		Task_ReDataFrom752_1(); //232扩展端口接收数据
	}

	if (Symbol.COM4orCOM5) {
		Symbol.COM4orCOM5 = 0;
		Task_ReDataFrom752_2(); //485扩展端口接收数据
	}

	if (COMSymbol.COM5DataReady)  //判断是否接收到完整数据
	{
		Symbol.Mod_symbol = 0;
		COMSymbol.COM5DataReady = 0;
		Mod_dealdata(COM5_Buffer);
	}

	if (COMSymbol.COM4DataReady)  //判断是否接收到完整数据
	{
		Symbol.Mod_symbol = 0;
		COMSymbol.COM5DataReady = 0;
		Mod_dealdata(COM4_Buffer);
	}

	if (COMSymbol.COM2DataReady) {
		COMSymbol.COM2DataReady = 0;
		Symbol.Mod_symbol = 0;
		dataparse_jiubo(COM2_Buffer);
	}

	if (COMSymbol.COM3DataReady) {
		COMSymbol.COM3DataReady = 0;
		Symbol.Mod_symbol = 0;
		dataparse_zhonglv(COM3_Bufferbuf);
	}
}

INT16U Hjt212_GetRtdUploadInterval()
{
	INT8U count;
	INT16U second = 300;

	for (count = 0; SPARA.rd_interval[count] != '\0' && count < 3; count++)
		;

	switch (count) {
	case 1:
		second = (int) (SPARA.rd_interval[0] & 0xf);
		break;
	case 2:
		second = ((int) (SPARA.rd_interval[0] & 0xf)) * 10
				+ (int) (SPARA.rd_interval[1] & 0xf);
		break;
	case 3:
		second = ((int) (SPARA.rd_interval[0] & 0xf)) * 100
				+ ((int) (SPARA.rd_interval[1] & 0xf)) * 10
				+ (int) (SPARA.rd_interval[2] & 0xf);
		break;
	default:
		break;
	}

	return second;
}

//---------------------检测GPRS是否在线---------------------------
void Gprs_Run()
{
	static INT8U old_minute = 0;

	if (old_minute != current_minute) {
		old_minute = current_minute;

		if (current_minute % 10 == 0)
			Rpthisdata.sdminutedata = 1;
		if ((GPRS_ONLINE)) {
			GPRS_RST
			;
		}
	}
}

/*-----------------------------------------------------------------------
 IS752 INITIAL
 ------------------------------------------------------------------------*/
void Uart_Init()
{
	IS752_initial_1(SPARA.Serial_Baud[1], SPARA.Serial_Baud[2]);
	IS752_initial_2(SPARA.Serial_Baud[3], SPARA.Serial_Baud[4]);
	Delay_N_mS(20000);
}

/***************************************************************
 LCD initializing
 ***************************************************************/
void Lcd_Init()
{
	INT8U count;

	for (count = 0; count < 6; count++) {
		LCD_user_pw[count] = parameter.sys_parameter.pw[count];
	}

	index_initial();  //LCD 初始化
	Symbol.LCD_deal = 1;
	LCD_page = 10;
	Symbol.LCD_Page_Change = 1;
	Symbol.Mod_checkover = 1;
	Symbol.Pass_id = 1;
	disp10();
}

//------------LCD数据更新-----------------------------
void Lcd_Update()
{
	if ((Symbol.LCD_deal == 0) && (LCD_page == 10)) {
		Symbol.LCD_T = 1;
		Symbol.LCD_deal = 1;
	} else {
		Symbol.LCD_T = 0;
	}
}

//-----------------LCD背光控制--------------
void Lcd_Backlightcontrol()
{
	char tmp;
	if (SPARA.LCD_Backtime != 0) {
		if (Symbol.Pass_id) {
			LCD_light++;

			if (SPARA.LCD_Backtime == 1) {
				tmp = 120;
			} else {
				tmp = 240;
			}

			if (LCD_light >= tmp) {
				LCD_light = 0;
				Symbol.Pass_id = 0;
				LCD_light_OFF;
				Symbol.LCD_deal = 1;
				LCD_page = 10;
				Symbol.LCD_Page_Change = 1;
			}
		}
	}
}

void Lcd_Proc()
{
	static INT16U cnt = 0;

	//读取键盘值
	if (cnt++ % 400 == 0)
		KeyV = getkey();

	if ((KeyV != 0) || (Symbol.LCD_deal))		//LCD 处理
			{
		LCD_disp();
	}

	if (Symbol.LCD_para_set) {
		Symbol.LCD_para_set = 0;
		_BIC_SR(GIE);
		AT24C64_W(parameter.sys_setting, 0x10, ParaNum);
		_BIS_SR(GIE);
	}

	//LCD复位
	if (Screen_RST) {
		Screen_RST = 0;
		LCD_RSTime = 0;
		init_lcd();
	}
}
/***********************************************
 device initializing
 ************************************************/
void Hardware_Init()
{
	CPU_init();
	P4OUT |= BIT0;   //flash rst
	GPRS_POWERON;
	RealData.R_D.DO = 0;
	DIInput();
	DOOutput(RealData.R_D.DO);
	init_lcd();
	clrram();
	LCD_light_ON;
	disp_img(0x01e0 + 960, 30, 64, zimo240128);
	delay11(3200);

	Uart_Init();
}

/****************************************************
 system initializing
 ****************************************************/
void System_Init()
{
	INT8U count;
	INT8U checknum[7];
	char checkcode[6] = "vh11+\0";

	Symbol.SymAll = 0;
	Symbol.stop_watch = 1;  //使能上传实时数据
	Symbol.dealcommand = 0;

	Modbustore = 0;
	MemoryClear(local_mma_H, sizeof(local_mma_H));
	MemoryClear(local_mma_D, sizeof(local_mma_D));
	MemoryClear(local_mma_M, sizeof(local_mma_M));   //100504
	MemoryClear(dev_mma_D, sizeof(dev_mma_D));
	MemoryClear(dev_mma_H, sizeof(dev_mma_H));
	MemoryClear(dev_mma_M, sizeof(dev_mma_M));  //100504

	AT24C64_RS(checknum, 0x00, 6);
	Delay_N_mS(2000);
	AT24C64_RS(checknum, 0x00, 6);
	checknum[6] = 0;

	if (strcmp(checknum, checkcode) != 0) {
		v_charge1302();
		v_Set1302();

		for (count = 0; count < 6; count++)
			SPARA.pw[count] = (count + 1) | 0x30;  //初始密码123456

		for (count = 0; count < 9; count++) {
			SPARA.mn[count] = (count + 1) | 0x30;  //mn 12345678901234
			ml_mn[count] = parameter.sys_parameter.mn[count];
		}

		for (count = 0; count < 5; count++) {
			SPARA.mn[count + 9] = count | 0x30;
			ml_mn[count + 9] = parameter.sys_parameter.mn[count + 9];
		}

		SPARA.st[0] = '3';             //st 32
		SPARA.st[1] = '2';
		ml_st[0] = '3';
		ml_st[1] = '2';
		for (count = 0; count < 9; count++)
			SPARA.sim[count] = (count + 1) | 0x30;  //sim 123456789

		SPARA.rd_interval[0] = '3';     //实时数据上报时间 60秒
		SPARA.rd_interval[1] = '0';
		SPARA.rd_interval[2] = '0';

		for (count = 0; count < 5; count++)
			SPARA.overtime[count] = '0';    //超时时间 5秒
		SPARA.overtime[4] = '5';
		SPARA.resendtime[0] = '0';		//重发次数 3次
		SPARA.resendtime[1] = '3';
		for (count = 0; count < 5; count++)
			SPARA.warntime[count] = '0';    //报警时间 5
		SPARA.warntime[4] = '5';

		for (count = 0; count < 4; count++)
			SPARA.reporttime[count] = '0';	//上报时间 5
		SPARA.reporttime[3] = '5';
		for (count = 0; count < 2; count++)
			SPARA.alarmtarge[count] = 0x30 + count;		//仪表污染物编号
		SPARA.alarmtarge[2] = '\0';
		SPARA.alarmtarge[3] = '\0';

		for (count = 0; count < 8; count++) {
			ADPARA(count).po_id[0]='0';
			ADPARA(count).po_id[1]='0';
			ADPARA(count).po_id[2]='0';
			ADPARA(count).ADUV.b=16.0;
			ADPARA(count).ADLV.b=0.0;
			ADPARA(count).U_Alarmlimt.b=10.0;
			ADPARA(count).L_Alarmlimt.b=0.0;
			ADPARA(count).rate.b=(16.0-0.0)/0x666;
			ADPARA(count).AI_Type=2;

		}

		for (count = 0; count < 6; count++)
			SPARA.Serial_Baud[count] = 0;

		//LCD_Baud=0;
		for (checknum[0] = 0; checknum[0] < 6; checknum[0]++)
			for (count = 0; count < 16; count++)
				SPARA.PO_SerialNum[checknum[0]][count] = 0xff;

		SPARA.PO_SerialNum[0][0] = 0x05;

		for (count = 0; count < 6; count++)         //都设置为0
				{
			SPARA.PO_Type[count] = 0;
			Channel_Num[count] = 0;
		}
		SPARA.PO_Type[0] = 1; //水,哈希   但是这个地方又设置了第一个为1
		Channel_Num[0] = 1;
		SPARA.alarmtarge[10] = 0; //baud rate
		SPARA.LCD_Backtime = 1;

		AT24C64_W(parameter.sys_setting, 0x10, sizeof(PARAMETER));
		/*初始化历史数据标志组结构体，存储于Flash第一页（页地址0x00）*/
		INT8U Rdaddr[3] = { 0, 0, 0 };
		INT16U pageaddr = 0;
		HISDATAFLAGS Sighisdata;
		MemoryClear(&Sighisdata, sizeof(Sighisdata));
		for (count = 0; count < 7;) {
			Sighisdata.page = 0x10 + count * 31 * 24;
			Rdaddr[1] = (INT8U) (pageaddr >> 8);
			Rdaddr[2] = (INT8U) (pageaddr);
			FlashBufferWrite(Rdaddr, &Sighisdata, sizeof(Sighisdata),
					FLASHBUFFER1);
			FlashBufferWrite(Rdaddr, &Sighisdata, sizeof(Sighisdata),
					FLASHBUFFER1);
			count++;
			pageaddr = count * 120;
		}
		Rdaddr[0] = 0;
		Rdaddr[1] = 0;
		Rdaddr[2] = 0;
		FlashBuffertoMemory(Rdaddr, FLASHBUFFER1);

		HISDATAFLAGS_D sig_d;
		pageaddr = 0;
		MemoryClear(&sig_d, sizeof(sig_d));
		for (count = 0; count < 13;) {
			sig_d.page = 5400 + count * 31;
			Rdaddr[0] = 0;
			Rdaddr[1] = ((INT8U) (pageaddr >> 8)) | 0x28;  //page 5
			Rdaddr[2] = (INT8U) (pageaddr);
			FlashBufferWrite(Rdaddr, &sig_d, sizeof(sig_d), FLASHBUFFER1);
			count++;
			pageaddr = count * 80;
		}
		Rdaddr[0] = 0;
		Rdaddr[1] = 0x28;
		Rdaddr[2] = 0;
		FlashBuffertoMemory(Rdaddr, FLASHBUFFER1);

		HISDATAFLAGS_R sig_r;
		MemoryClear(&sig_r, sizeof(sig_r));
		pageaddr = 0;
		for (count = 0; count < 3;) {
			sig_r.page = 6000 + count * 24 * 12;
			Rdaddr[0] = 0;
			Rdaddr[1] = ((INT8U) (pageaddr >> 8)) | 0x50;
			Rdaddr[2] = (INT8U) (pageaddr);
			FlashBufferWrite(Rdaddr, &sig_r, sizeof(sig_r), FLASHBUFFER1);
			count++;
			pageaddr = count * 200;
		}
		Rdaddr[0] = 0;
		Rdaddr[1] = 0x50; // page 10
		Rdaddr[2] = 0;
		FlashBuffertoMemory(Rdaddr, FLASHBUFFER1);

		//运行日志存储于8190页（1FFE）
		RUNRECORD runlog;
		MemoryClear(&runlog, sizeof(runlog));
		pageaddr = 0;
		for (count = 0; count < 10; count++) {
			pageaddr = count * 64;
			Rdaddr[0] = 0xff;
			Rdaddr[1] = ((INT8U) (pageaddr >> 8)) | 0xf0;
			Rdaddr[2] = (INT8U) (pageaddr);
			FlashBufferWrite(Rdaddr, &runlog, sizeof(runlog), FLASHBUFFER1);
		}
		Rdaddr[0] = 0xff;
		Rdaddr[1] = 0xf0;
		Rdaddr[2] = 0;
		FlashBuffertoMemory(Rdaddr, FLASHBUFFER1);
		AT24C64_W(checkcode, 0x00, 6);
	} else {
		//用户参数在Flash第1页 页地址0x00;
		Delay_N_mS(20000);
		AT24C64_RS(parameter.sys_setting, 0x10, ParaNum);

		for (count = 0; count < 8; count++) {
			if (ADPARA(count).AI_Type==2)
			ADPARA(count).rate.b=(ADPARA(count).ADUV.b-ADPARA(count).ADLV.b)/0x666;
			else
			ADPARA(count).rate.b=(ADPARA(count).ADUV.b-ADPARA(count).ADLV.b)/0x1000;
		}

		for (checkcode[0] = 0; checkcode[0] < 6; checkcode[0]++)
			for (count = 0; count < 16; count++) {
				if (SPARA.PO_SerialNum[checkcode[0]][count] != 0xff) {
					Channel_Num[checkcode[0]]++;
				} else {
					break;
				}
			}

		if (SPARA.PO_Type[0] == 1) {
			Channel_Num[0] = 1;
		} else {
			Channel_Num[0] = 0;
		}
		SPARA.PO_SerialNum[0][0] = 0x05;
	}
}

void Hjt212_UploadMsg()
{
	static INT16U count = 0;
	static INT8U old_second = 0, first = 1;
	static INT16U interval;

	if (first) {
		first = 0;
		interval = Hjt212_GetRtdUploadInterval();
	}

	//1s过去了 进行需要秒级的计算处理
	if (old_second != current_second) {
		old_second = current_second;
		count++;
	}

	/* 判断实时数据上传间隔是否改变 */
	if (Symbol.rd_change) {
		Symbol.rd_change = 0;
		count = 0;
		interval = Hjt212_GetRtdUploadInterval();
	}

	/*数据上报及保存*/
	if (count >= interval) {
		count = 0;
		run_log_record(&RunLog);
		_BIC_SR(GIE);

		if (Symbol.stop_watch == 1) {
			collect_realdata(0, 0);
		}

		if (stop_watch_devstatus == 1) {
			Device_Status();
		}
		_BIS_SR(GIE);
	}

	/*  分钟数据 */
	if (Rpthisdata.sdminutedata) {
		Rpthisdata.sdminutedata = 0;
		_BIC_SR(GIE);
		Reporthisdata_M();
		_BIS_SR(GIE);
	}

	/* 小时数据 */
	if (Rpthisdata.sdhourdata) {
		Rpthisdata.sdhourdata = 0;
		_BIC_SR(GIE);
		Reporthisdata_H();
		_BIS_SR(GIE);
	}

	/* 日数据 */
	if (Rpthisdata.sddaydata) {
		Rpthisdata.sddaydata = 0;
		_BIC_SR(GIE);
		Reporthisdata_D();
		_BIS_SR(GIE);
	}
}

void Proc_Control()
{
	//仪表反控
	if ((Symbol.Mod_checkover != 0) && (Symbol.Mod_symbol == 0)) {
		if (Devctr.calibrate == 1) {

			Devctr.calibrate = 0;
			dev_calibrate_sample('c');

		}
		if (Devctr.sample == 1) {
			Devctr.sample = 0;
			dev_calibrate_sample('s');
		}
		if (Devctr.operate == 1) {
			Devctr.operate = 0;
			dev_operate();
		}
		if (Devctr.settimes == 1) {
			Devctr.settimes = 0;
			dev_settimes();
		}
	}
}

void Data_Proc()
{
	static INT8U old_second = 0;
	static INT8U old_hour = 0;
	static INT8U first = 1;

	if (first) {
		old_second = current_second;
		old_hour = current_hour;
		first = 0;
	}

	//1s过去了 进行需要秒级的计算处理
	if (old_second != current_second) {

		old_second = current_second;

		AnalogDataStatistic();

		DevCalculation();

		if ((current_minute == 0x00) && (current_hour == 0x00)
				&& (current_second == 0x00)) {
			Rpthisdata.sddaydata = 1;
		}

		if (old_hour != current_hour) {
			old_hour = current_hour;
			Rpthisdata.sdhourdata = 1;	//enable sending hour his_data
		}

		if ((current_minute == 0x00) && (current_hour == 0x00)
				&& (current_second == 0x05)) {
			GPRS_POWEROFF;
		}

		if ((current_minute == 0x00) && (current_hour == 0x00)
				&& (current_second == 0x06)) {
			GPRS_POWERON;
		}

		Led_Run();
		Lcd_Update();
		Lcd_Backlightcontrol();
	} //1s内需要执行操作完毕
}

void Hjt212_CmdProc()
{
	if (Symbol.dealcommand) {
		_BIC_SR(GIE);
		dealdata_wjj();							//	命令处理
		_BIS_SR(GIE);
		Symbol.dealcommand = 0;					//  命令处理完成标志为0
		Receive_Package_length = 0;				//接收数据包的长度
		Receive_Data_length = 0;					//接收数据总长度
		Receive_Package_length = 0;				//接收数据包的长度
	}
}

void Time_Proc()
{
	static INT8U old_day = 0, first = 0;
	static INT16U cnt = 0;

	if (first == 0) {
		first = 1;
		old_day = current_date;
	}

	if (cnt++ % 10 == 0) {
		Rtc_Sync();
		if (old_day != current_date) {
			yestoday = old_day;
			old_day = current_date;
		}
	}
}

void Di_Init()
{
	INT16U temp;
	temp = DIInput();  //读入DI值
	RealData.R_D.DI[0] = (INT8U) (temp >> 8);
	RealData.R_D.DI[1] = (INT8U) temp;
}

/* 北郊出口程序 */
int main(void)
{
	Hardware_Init();
	System_Init();
	Rtc_Sync();
	run_log_init(&RunLog);
	Lcd_Init();
	Di_Init();
	//enable the interrupt
	_BIS_SR(GIE);

	/***************************************************
	 main loop
	 ***************************************************/
	while (1) {
		//处理接收上位机命令
		Hjt212_CmdProc();
		Time_Proc();
		Data_Proc();
		Modbus_Run();
		Gprs_Run();
		Adc_Run();
		Dio_Run();
		Hjt212_UploadMsg();
		Lcd_Proc();
		Proc_Control();
	}
}

/*******************************************
 AD interrupt function
 *******************************************/
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void)
{
	ADResult[0][2 * ADTimes] = ADC12MEM0;
	ADResult[0][2 * ADTimes + 1] = ADC12MEM1;
	ADResult[1][2 * ADTimes] = ADC12MEM2;
	ADResult[1][2 * ADTimes + 1] = ADC12MEM3;
	ADResult[2][2 * ADTimes] = ADC12MEM4;
	ADResult[2][2 * ADTimes + 1] = ADC12MEM5;
	ADResult[3][2 * ADTimes] = ADC12MEM6;
	ADResult[3][2 * ADTimes + 1] = ADC12MEM7;
	ADResult[4][2 * ADTimes] = ADC12MEM8;
	ADResult[4][2 * ADTimes + 1] = ADC12MEM9;
	ADResult[5][2 * ADTimes] = ADC12MEM10;
	ADResult[5][2 * ADTimes + 1] = ADC12MEM11;
	ADResult[6][2 * ADTimes] = ADC12MEM12;
	ADResult[6][2 * ADTimes + 1] = ADC12MEM13;
	ADResult[7][2 * ADTimes] = ADC12MEM14;
	ADResult[7][2 * ADTimes + 1] = ADC12MEM15;

	ADTimes++;
	if (ADTimes >= 5) {
		ADTimes = 0;
		AD_CONVERTER = 1;
	}
}
/*******************************************
 AD Converter
 *******************************************/
void AD_READ(void)
{
	INT8U i, j;
	INT16U *max, *min, *mid;

	for (i = 0; i < 8; i++) {
		ADValue[i] = 0;
		max = &ADResult[i][0];
		min = max;
		mid = &ADResult[i][1];
		//查找最高最低值
		for (j = 0; j < 9; j++) {
			if (*max < *mid)
				max = mid;
			if (*min > *mid)
				min = mid;
			mid = &ADResult[i][j + 2];
		}
		*max = 0;      //去掉最高值
		*min = 0;      //去掉最低值
		for (j = 0; j < 10; j++)
			ADValue[i] += ADResult[i][j];
		ADValue[i] = (ADValue[i] >> 3);   //取平均值
		if (ADValue[i] <= 0x100)
			ADValue[i] -= 2;
		else
			ADValue[i] += 3;
	}
}

void ADCalculation(void)
{
	INT8U i;
	INT16U AD_f;
	float AD_k;

	for (i = 0; i < 8; i++) {
		AD_f = ADValue[i];
		switch (ADPARA(i).AI_Type) {
			case 0:
			AD_k=ADPARA(i).rate.b*AD_f+ADPARA(i).ADLV.b;
			break;
			case 1:
			AD_k=ADPARA(i).rate.b*AD_f*2+ADPARA(i).ADLV.b;
			break;
			case 2:
			if(AD_f<0x199)
			AD_f=0x199;
			AD_k=ADPARA(i).rate.b*(AD_f-0x199)+ADPARA(i).ADLV.b;
			break;
			default:
			break;
		}

		if (AD_k > ADPARA(i).ADUV.b)
		RealData.R_D.FF.ADF[i]=ADPARA(i).ADUV.b;
		else
		RealData.R_D.FF.ADF[i]=AD_k;
	}
}

void AnalogCalcMinusData()
{
	INT16U pos;
	INT8U b01_flag = 0, b01_pos = 0;

	for (pos = 0; pos < 8; pos++) {
		if (!strcmp(ADPARA(pos).po_id, "B01")) {
			b01_flag = 1;
			b01_pos = pos;
			break;
		}
	}

	for (pos = 0; pos < 8; pos++) {
		if (local_mma_M[pos].num == 0) {
			local_mma_M[pos].max = local_mma_M[pos].min = local_mma_M[pos].sum =
					local_mma_M[pos].cou = RealData.R_D.FF.ADF[pos];
			local_mma_M[pos].num++;
		} else {
			if (RealData.R_D.FF.ADF[pos] < local_mma_M[pos].min)
				local_mma_M[pos].min = RealData.R_D.FF.ADF[pos];

			if (RealData.R_D.FF.ADF[pos] > local_mma_M[pos].max)
				local_mma_M[pos].max = RealData.R_D.FF.ADF[pos];

			local_mma_M[pos].sum += RealData.R_D.FF.ADF[pos];

			if (!strcmp(ADPARA(pos).po_id, "060")) {
				if (b01_flag == 1) {
					local_mma_M[pos].cou += RealData.R_D.FF.ADF[pos] * RealData.R_D.FF.ADF[b01_pos];
				} else {
					local_mma_M[pos].cou = 0;
				}
			} else {
				local_mma_M[pos].cou += RealData.R_D.FF.ADF[pos];
			}
			local_mma_M[pos].num++;
		}
	}
}

void AnalogCalcHourData()
{
	INT16U pos;
	INT8U b01_flag = 0, b01_pos = 0;

	for (pos = 0; pos < 8; pos++) {
		if (!strcmp(ADPARA(pos).po_id, "B01")) {
			b01_flag = 1;
			b01_pos = pos;
			break;
		}
	}

	for (pos = 0; pos < 8; pos++) {
		if (local_mma_H[pos].num == 0) {
			local_mma_H[pos].max = local_mma_H[pos].min = local_mma_H[pos].sum =
					local_mma_H[pos].cou = RealData.R_D.FF.ADF[pos];
			local_mma_H[pos].num++;
		} else {
			if (RealData.R_D.FF.ADF[pos] < local_mma_H[pos].min)
				local_mma_H[pos].min = RealData.R_D.FF.ADF[pos];

			if (RealData.R_D.FF.ADF[pos] > local_mma_H[pos].max)
				local_mma_H[pos].max = RealData.R_D.FF.ADF[pos];

			local_mma_H[pos].sum += RealData.R_D.FF.ADF[pos];

			if (!strcmp(ADPARA(pos).po_id, "060")) {
				if (b01_flag == 1) {
					local_mma_H[pos].cou += RealData.R_D.FF.ADF[pos] * RealData.R_D.FF.ADF[b01_pos];
				} else {
					local_mma_H[pos].cou = 0;
				}
			} else {
				local_mma_H[pos].cou += RealData.R_D.FF.ADF[pos];
			}
			local_mma_H[pos].num++;
		}
	}
}

void AnalogCalcDayData()
{
	INT16U pos;
	INT8U b01_flag = 0, b01_pos = 0;

	for (pos = 0; pos < 8; pos++) {
		if (!strcmp(ADPARA(pos).po_id, "B01")) {
			b01_flag = 1;
			b01_pos = pos;
			break;
		}
	}

	for (pos = 0; pos < 8; pos++) {
		if (local_mma_D[pos].num == 0) {
			local_mma_D[pos].max = local_mma_D[pos].min = local_mma_D[pos].sum =
					local_mma_D[pos].cou = RealData.R_D.FF.ADF[pos];
			local_mma_D[pos].num++;
		} else {
			if (RealData.R_D.FF.ADF[pos] < local_mma_D[pos].min)
				local_mma_D[pos].min = RealData.R_D.FF.ADF[pos];
			if (RealData.R_D.FF.ADF[pos] > local_mma_D[pos].max)
				local_mma_D[pos].max = RealData.R_D.FF.ADF[pos];
			local_mma_D[pos].sum += RealData.R_D.FF.ADF[pos];

			if (!strcmp(ADPARA(pos).po_id, "060")) {
				if (b01_flag == 1) {
					local_mma_D[pos].cou += RealData.R_D.FF.ADF[pos] * RealData.R_D.FF.ADF[b01_pos];
				} else {
					local_mma_D[pos].cou = 0;
				}
			} else {
				local_mma_D[pos].cou += RealData.R_D.FF.ADF[pos];
			}
			local_mma_D[pos].num++;
		}
	}
}

/* Add By KangQi At 2014-06-30 */
void AnalogDataStatistic(void)
{
	AnalogCalcMinusData();
	AnalogCalcHourData();
	AnalogCalcDayData();
}
/****************************************
 DO OUTPUT
 *****************************************/
void DOOutput(INT8U dout)
{
	CS_4245_EN;
	P1DIR = 0XFF;   //direction output
	DO_ENABLE;
	Delay_N_mS(2);
	DOOUT = IOOUTPUTs[dout];
	Delay_N_mS(2);
	DO_DISABLE;
	CS_4245_DIS;
	P1DIR = 0X00;   //direction input
}
/****************************************
 DI INPUT
 *****************************************/
INT16U DIInput(void)
{
	INT16U DValue;
	DI1_ENABLE;
	DValue = DIN;
	DI1_DISABLE;
	Delay_N_mS(2);
	DI2_ENABLE;
	DValue |= ((INT16U) DIN) << 8;
	DI2_DISABLE;
	DValue = ~DValue;
	return (DValue);
}

