#include <msp430xG46x.h>
#include "test.h"

#include <string.h>

INT16U PO_No = 0;	//污染物个数累加器
INT8U POdata_Type = 0;	//污染物数据类型  Rtd Rtp等
INT16U POdata_Receive = 0;	//污染物数据接收标志位 Rtd Rtp等
INT8U PO_Retime = 0;  //超时重发次数计数器

INT8U Channel_Num[6] = { 0, 0, 0, 0, 0, 0 };
INT8U Mod_checkover = 1;
long WatchDogCNT = 0;
INT8U Device_ID = 0;

//extern unsigned char xdata Mod_Receive[10];
//extern unsigned char ftstring[18];
//extern unsigned char xdata Mod_method;
//extern bit Mod_symbol;
//extern bit Mod_ontime;

struct MOD {
	INT8U PO_code[4];
	INT8U modbus_address[2];
};

const struct MOD MOD_Gas[] = { { "S01\0", { 0x00, 0x00 } }, { "S02\0", { 0x00,
		0x64 } }, { "S03\0", { 0x00, 0xc8 } }, { "S04\0", { 0x01, 0x2c } }, {
		"S05\0", { 0x01, 0x90 } }, { "S06\0", { 0x01, 0xf4 } }, { "S07\0", {
		0x02, 0x58 } }, { "S08\0", { 0x02, 0xbc } },
		{ "B02\0", { 0x03, 0x20 } }, { "01\0", { 0x03, 0x84 } }, { "02\0", {
				0x03, 0xe8 } }, { "03\0", { 0x04, 0x4c } }, { "04\0", { 0x04,
				0xb0 } }, { "05\0", { 0x05, 0x14 } },
		{ "06\0", { 0x05, 0x78 } }, { "07\0", { 0x05, 0xdc } }, { "08\0", {
				0x06, 0x40 } }, { "09\0", { 0x06, 0xa4 } }, { "10\0", { 0x07,
				0x08 } }, { "11\0", { 0x07, 0x6c } },
		{ "12\0", { 0x07, 0xd0 } }, { "13\0", { 0x08, 0x34 } }, { "14\0", {
				0x08, 0x98 } }, { "15\0", { 0x08, 0xfc } }, { "16\0", { 0x09,
				0x60 } }, { "17\0", { 0x09, 0xc4 } },
		{ "18\0", { 0x0a, 0x28 } }, { "19\0", { 0x0a, 0x8c } }, { "20\0", {
				0x0a, 0xf0 } }, { "21\0", { 0x0b, 0x54 } }, { "22\0", { 0x0b,
				0xb8 } }, { "23\0", { 0x0c, 0x1c } },
		{ "24\0", { 0x0c, 0x80 } }, { "25\0", { 0x0c, 0xe4 } }, { "26\0", {
				0x0d, 0x48 } }, { "27\0", { 0x0d, 0xac } }, { "28\0", { 0x0e,
				0x10 } }, { "29\0", { 0x0e, 0x74 } },
		{ "30\0", { 0x0e, 0xd8 } }, { "31\0", { 0x0f, 0x3c } }, { "32\0", {
				0x0f, 0xa0 } }, { "33\0", { 0x10, 0x04 } }, { "34\0", { 0x10,
				0x68 } }, { "35\0", { 0x10, 0xcc } },
		{ "36\0", { 0x11, 0x30 } }, { "37\0", { 0x11, 0x94 } }, { "99\0", {
				0x11, 0xf8 } }, { "Pfk\0", { 0x12, 0x5c } }

};
const struct MOD MOD_Water[] = { { "B01\0", { 0x00, 0x00 } }, { "001\0", { 0x00,
		0x64 } }, { "002\0", { 0x00, 0xC8 } }, { "003\0", { 0x01, 0x2C } }, {
		"010\0", { 0x01, 0x90 } }, { "011\0", { 0x00, 0x00 } }, { "015\0", {
		0x02, 0x58 } }, { "020\0", { 0x02, 0xBC } },
		{ "021\0", { 0x03, 0x20 } }, { "022\0", { 0x03, 0x84 } }, { "023\0", {
				0x03, 0xE8 } }, { "024\0", { 0x04, 0x4C } }, { "025\0", { 0x04,
				0xb0 } }, { "026\0", { 0x05, 0x14 } },
		{ "027\0", { 0x05, 0x78 } }, { "028\0", { 0x05, 0xdc } }, { "029\0", {
				0x06, 0x40 } }, { "030\0", { 0x06, 0xa4 } }, { "031\0", { 0x07,
				0x08 } }, { "032\0", { 0x07, 0x6c } },
		{ "033\0", { 0x07, 0xd0 } }, { "034\0", { 0x08, 0x34 } }, { "035\0", {
				0x08, 0x98 } }, { "036\0", { 0x08, 0xfc } }, { "037\0", { 0x09,
				0x60 } }, { "038\0", { 0x09, 0xc4 } },
		{ "039\0", { 0x0a, 0x28 } }, { "040\0", { 0x0a, 0x8c } }, { "041\0", {
				0x0a, 0xf0 } }, { "060\0", { 0x0B, 0x54 } }, { "061\0", { 0x0b,
				0xb8 } }, { "065\0", { 0x0c, 0x1c } },
		{ "080\0", { 0x0c, 0x80 } }, { "101\0", { 0x0C, 0xE4 } }, { "Pfk\0", {
				0x0d, 0x48 } } };

extern COMBAG CBAG;

float Modbustore;
float NHdatastore;  //用来记录氨氮的采集值。
float B01datastore;  //用来记录流量的采集值。
//float Modbustore[6][16][4];

extern struct _LCD {
	unsigned LCD_DOS :1;
	unsigned LCD_set :1;
	unsigned LCD_back :1;
	unsigned LCD_backdoor :1;
	unsigned LCD_Dot :1;
	unsigned LCD_EQU :1;
	unsigned LCD_LOG :1;
} LCDSymbol;
extern float MODBUS_EQU[6];
void Modbus_RCommand(const INT8U *Maddr, INT8U method, INT8U PoType,
		INT8U Device);

void Mod_Command(INT8U method)
{
	//unsigned char Mod_bag[8]={0x01,0x03,0,0,0x00,0x02};
	INT8U i;
	//INT16U j;
	//INT8U Flag_N[2]="N\0";
	switch (method) {
	case Mod_RealD:
		i = 1;
		break;
	case Mod_MinD:
		i = 13;
		break;
	case Mod_DayD:
	case Mod_HourD:
		i = 12;
		break;
	default:
		break;
	}
	if (PO_Retime >= 2)		//重发次数超过三次
			{
		PO_Retime = 0;
		POdata_Type++;
	} else {
		if ((POdata_Receive & (0x01 << POdata_Type)) != 0)		//已经接收到数据
				{
			POdata_Type++;
			PO_Retime = 0;
		}

	}
	if (POdata_Type >= i) {
		if (POdata_Receive != 0) {
			/*if(method==Mod_RealD)
			 {
			 j=strlen(Mod_bagR);
			 strcat(Mod_bagR,Mod_PPR[POdata_Type]);
			 if(SPARA.PO_Type[Device_ID]==2)
			 insert(Mod_bagR,MOD_Gas[SPARA.PO_SerialNum[Device_ID][PO_No]].PO_code,j+2);
			 else if(SPARA.PO_Type[Device_ID]==1)
			 insert(Mod_bagR,MOD_Water[SPARA.PO_SerialNum[Device_ID][PO_No]].PO_code,j+2);
			 strcat(Mod_bagR,Flag_N);
			 }*/
			//Channel_Receive|=(0x01<<PO_No);
			//Symbol.Mod_complete=1;
		}
		PO_No++;
		POdata_Receive = 0;
		POdata_Type = 0;
		PO_Retime = 0;
		return;

	}
	if (PO_No >= Channel_Num[Device_ID]) {
		PO_No = 0;
		Device_ID++;
		if (Device_ID > 5) {
			Device_ID = 0;
			if (Mod_method == Mod_RealD)
				Symbol.Mod_checkover = 2;
			else
				Symbol.Mod_checkover = 1;
			Symbol.Mod_ontime = 0;
			Symbol.Hour_data = 0;
			Symbol.Day_data = 0;
		}
		/*if(Channel_Receive!=0)
		 {
		 //Mod_complete=1;
		 Channel_Receive=0;
		 }*/
		return;
	}
	//if((Device_Enable&(0x01<<(Device_ID)))!=0)
	switch (SPARA.PO_Type[Device_ID]) {
	case 1:			//water
		Modbus_RCommand(
				MOD_Water[SPARA.PO_SerialNum[Device_ID][PO_No]].modbus_address,
				method, 0, Device_ID);
		break;
	case 2:			//gas
		Modbus_RCommand(
				MOD_Gas[SPARA.PO_SerialNum[Device_ID][PO_No]].modbus_address,
				method, 1, Device_ID);
		break;
	default:
		break;
	}
	//else
	//	Device_ID++;	
}

void Modbus_RCommand(const INT8U *Maddr, INT8U method, INT8U PoType,
		INT8U Device)
{
	INT8U mod_bag[9];	//={0x01,0x03};
	volatile INT8U Mod_send = 0;
	union {
		char add1[2];
		int add2;
	} add3;
	INT8U CRC16[2];
	add3.add1[0] = *(Maddr + 1);
	add3.add1[1] = *Maddr;
	add3.add2 += 2 * POdata_Type;
	mod_bag[0] = Device + 1;
	mod_bag[1] = 0x03;
	mod_bag[2] = add3.add1[1];
	mod_bag[3] = add3.add1[0];
	mod_bag[4] = 0x00;
	mod_bag[5] = 0x02;
	if (PoType) {
		Mod_send = 1;

	} else
		switch (method) {
		case Mod_RealD: {
			if ((POdata_Type == 2) || (POdata_Type == 3)) {
				Mod_send = 0;
				POdata_Type++;
				PO_Retime = 0;
			} else
				Mod_send = 1;
		}
			break;
			/*case Mod_MinD:
			 {
			 if(((POdata_Type>2)&&(POdata_Type<7))||(POdata_Type>9))
			 {
			 POdata_Type++;
			 Mod_send=0;
			 PO_Retime=0;
			 }
			 else
			 Mod_send=1;
			 }

			 break;*/
		case Mod_DayD:
		case Mod_HourD: {
			if (POdata_Type > 5) {
				Mod_send = 0;
				POdata_Type++;
				PO_Retime = 0;
			} else
				Mod_send = 1;
		}
			break;
		default:
			break;
		}
	if (Mod_send) {
		CRC_Calculation_B(mod_bag, 6, CRC16);
		mod_bag[6] = CRC16[0];		//CRC高
		mod_bag[7] = CRC16[1];		//CRC低
		Mod_send = 0;
		/*禁止中断*/
		_BIC_SR(GIE);
		if (mod_bag[0] <= 0x04)
			SendData(mod_bag, 8, COM5); //485
		else if (mod_bag[0] == 0x05)
			SendData(mod_bag, 8, COM2); //232
		else
			SendData(mod_bag, 8, COM3); //232
		PO_Retime++;
		/*开中断*/
		_BIS_SR(GIE);
	}
}

void Mod_dealdata(INT8U *receive)
{
	union {
		char a[4];
		float b;
	} Mod_D;
	//INT16U i;
	//INT8U NP=0;
	//INT8U Negtive[2]="-\0";
	//INT8U ftstring[18];
	INT8U CRC16[2];
	//unsigned char xdata Flag_N[2]="N\0";
	CRC_Calculation_B(receive, 7, CRC16);
	if ((CRC16[0] == *(receive + 7)) && (CRC16[1] == *(receive + 8))
			&& (*(receive + 1) == 0x03))	//高低位判别？
			{
		Mod_D.a[0] = *(receive + 4);	//Mod_Receive[5];
		Mod_D.a[1] = *(receive + 3);	//Mod_Receive[6];
		Mod_D.a[2] = *(receive + 6);	//Mod_Receive[3];
		Mod_D.a[3] = *(receive + 5);	//Mod_Receive[4];

		MODBUS_EQU[Device_ID] = Mod_D.b;
		if (LCD_page == 44) {
			LCDSymbol.LCD_EQU = 1;
			Symbol.LCD_deal = 1;
		}
		Modbustore = Mod_D.b; //采集到数据

	} else if ((CRC16[0] == *(receive + 7)) && (CRC16[1] == *(receive + 8))
			&& (*(receive + 1) == 0x10)) {
		POdata_Receive = 0;
		Symbol.Mod_checkover = 1;
	} else {
		POdata_Receive &= (~(0x01 << POdata_Type));
	}
	//Symbol.Mod_symbol=0;
}
/*
 void tempfunction()
 {
 union
 {
 char a[4];
 float b;
 }Mod_D;
 INT16U i;
 INT8U NP=0;
 INT8U Negtive[2]="-\0";
 INT8U ftstring[18];
 INT8U CRC16[2];
 if((Mod_D.a[3]&0x80)==0x80)
 {
 Mod_D.a[3]&=0x7f;
 NP=1;
 }

 float_to_string(Mod_D.b,ftstring);
 if(NP)
 {
 insert(ftstring,Negtive,1);
 }
 switch(Mod_method)
 {
 case Mod_RealD:
 i=strlen(Mod_bagR);
 strcat(Mod_bagR,Mod_PPR[POdata_Type]);
 if(SPARA.PO_Type[Device_ID]==2)
 insert(Mod_bagR,MOD_Gas[SPARA.PO_SerialNum[Device_ID][PO_No]].PO_code,i+2);
 else if(SPARA.PO_Type[Device_ID]==1)
 insert(Mod_bagR,MOD_Water[SPARA.PO_SerialNum[Device_ID][PO_No]].PO_code,i+2);
 //if(POdata_Type==4)
 //	strcat(Mod_bagR,Flag_N);
 //else
 strcat(Mod_bagR,ftstring);
 break;
 case Mod_MinD:
 case Mod_DayD:
 case Mod_HourD:
 if((PO_No<(Channel_Num[Device_ID]-1))&&(POdata_Type==0))
 {
 strcat(Mod_bagR,semicolon);
 }
 else
 strcat(Mod_bagR,comma);
 if(SPARA.PO_Type[Device_ID]==2)
 strcat(Mod_bagR,MOD_Gas[SPARA.PO_SerialNum[Device_ID][PO_No]].PO_code);
 else if(SPARA.PO_Type[Device_ID]==1)
 strcat(Mod_bagR,MOD_Water[SPARA.PO_SerialNum[Device_ID][PO_No]].PO_code);
 //if(Mod_method==Mod_MinD)
 //	strcat(CBAG.cbag_dynamic,Mod_PPM[POdata_Type]);
 //else
 strcat(Mod_bagR,Mod_PP[POdata_Type]);
 strcat(Mod_bagR,ftstring);
 break;
 default:
 break;
 }

 }
 */

void ModataUpload(INT8U ModM)
{
	union {
		char a[4];
		float b;
	} Mod_D;
	INT8U NP = 0;
	INT8U Negtive[2] = "-\0";
	INT8U rtdstr[11] = ";011-Rtd=\0";
	INT8U flagstr[13] = ",011-Flag=N\0";
	INT8U minstr[11] = ";011-Min=\0";
	INT8U avgstr[11] = ",011-Avg=\0";
	INT8U maxstr[11] = ",011-Max=\0";
	INT8U coustr[11] = ",011-Cou=\0";
	INT8U ftstring[18];

	if (ModM == Mod_RealD) {
		Mod_D.b = Modbustore;
		if ((Mod_D.a[3] & 0x80) == 0x80) {
			Mod_D.a[3] &= 0x7f;
			NP = 1;
		}

		float_to_string(Mod_D.b, ftstring);
		if (NP) {
			insert(ftstring, Negtive, 1);
		}
		strcat(CBAG.cbag_dynamic, rtdstr);
		strcat(CBAG.cbag_dynamic, ftstring);
		MemoryClear(ftstring, sizeof(ftstring));
		strcat(CBAG.cbag_dynamic, flagstr);
	} else {
		MAX_MIN *maxminp;
		switch (ModM) {
		case Mod_MinD:
			maxminp = dev_mma_M;
			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->min;

			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, minstr); //min
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				maxminp->avg = 0;
			else
				maxminp->avg = maxminp->sum / maxminp->num;

			Mod_D.b = maxminp->max; //小时cod的平均值就等于它的测量值（环保局091026）
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, avgstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->max;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, maxstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->cou / 1000000;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, coustr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));
			maxminp->num = 0;
			break;
		case Mod_HourD:
			maxminp = dev_mma_H;
			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->min;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, minstr); //min
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				maxminp->avg = 0;
			else
				maxminp->avg = maxminp->sum / maxminp->num;
			Mod_D.b = maxminp->max; //小时cod的平均值就等于它的测量值（环保局091026）
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, avgstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->max;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, maxstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->cou / 1000000;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, coustr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));
			break;
		case Mod_DayD:
			maxminp = dev_mma_D;
			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->min;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, minstr); //min
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

#if 0
			for(i=0;i<24;i++) {
				totaltmp += Hour_B01_avg[i]*Hour_COD_avg[i];
				total_b01_tmp +=Hour_B01_avg[i];
			}
			if(total_b01_tmp!=0.0) {
				maxminp->avg=totaltmp/total_b01_tmp;
			} else {
				maxminp->avg=0;
			}
#else 	/* Add By KangQi At 2014-07-04 */
			if (maxminp->num == 0)
				maxminp->avg = 0;
			else
				maxminp->avg = maxminp->sum / maxminp->num;
#endif
			Mod_D.b = maxminp->avg;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, avgstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->max;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, maxstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->cou / 1000000;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, coustr);
			strcat(CBAG.cbag_dynamic, ftstring);

			MemoryClear(ftstring, sizeof(ftstring));
			break;
		default:
			maxminp = 0;
			break;
		}
	}
}

void DevCalculation(void)
{
	INT16U pos;
	INT8U b01_flag = 0, b01_pos;

	for (pos = 0; pos < 8; pos++) {
		if (!strcmp(ADPARA(pos).po_id, "B01")) {
			b01_flag = 1;
			b01_pos = pos;
			break;
		}
	}

	//COD
	if (dev_mma_M[0].num == 0) {
		dev_mma_M[0].max = dev_mma_M[0].min = dev_mma_M[0].sum = Modbustore;
		dev_mma_M[0].cou = Modbustore;
		dev_mma_M[0].num++;
	} else {
		if (Modbustore < dev_mma_M[0].min)
			dev_mma_M[0].min = Modbustore;
		if (Modbustore > dev_mma_M[0].max)
			dev_mma_M[0].max = Modbustore;
		dev_mma_M[0].sum += Modbustore;

		if (b01_flag == 1) {
			dev_mma_M[0].cou += Modbustore * RealData.R_D.FF.ADF[b01_pos];
		} else {
			dev_mma_M[0].cou = 0;
		}

		dev_mma_M[0].num++;
	}

	if (dev_mma_H[0].num == 0) {
		dev_mma_H[0].max = dev_mma_H[0].min = dev_mma_H[0].sum = Modbustore;
		dev_mma_M[0].cou = Modbustore;
		dev_mma_H[0].num++;
	} else {
		if (Modbustore < dev_mma_H[0].min)
			dev_mma_H[0].min = Modbustore;
		if (Modbustore > dev_mma_H[0].max)
			dev_mma_H[0].max = Modbustore;
		dev_mma_H[0].sum += Modbustore;

		if (b01_flag == 1) {
			dev_mma_H[0].cou += Modbustore * RealData.R_D.FF.ADF[b01_pos];
		} else {
			dev_mma_H[0].cou = 0;
		}
		dev_mma_H[0].num++;
	}

	if (dev_mma_D[0].num == 0) {
		dev_mma_D[0].max = dev_mma_D[0].min = dev_mma_D[0].sum = Modbustore;
		dev_mma_M[0].cou = Modbustore;
		dev_mma_D[0].num++;
	} else {
		if (Modbustore < dev_mma_D[0].min)
			dev_mma_D[0].min = Modbustore;
		if (Modbustore > dev_mma_D[0].max)
			dev_mma_D[0].max = Modbustore;
		dev_mma_D[0].sum += Modbustore;

		if (b01_flag == 1) {
			dev_mma_D[0].cou += Modbustore * RealData.R_D.FF.ADF[b01_pos];
		} else {
			dev_mma_D[0].cou = 0;
		}
		dev_mma_D[0].num++;
	}

	//NH3
	if (NH_dev_mma_M[0].num == 0) {
		NH_dev_mma_M[0].max = NH_dev_mma_M[0].min = NH_dev_mma_M[0].sum =
				NHdatastore;
		NH_dev_mma_M[0].cou = NHdatastore;
		NH_dev_mma_M[0].num++;
	} else {
		if (NHdatastore < NH_dev_mma_M[0].min)
			NH_dev_mma_M[0].min = NHdatastore;
		if (NHdatastore > NH_dev_mma_M[0].max)
			NH_dev_mma_M[0].max = NHdatastore;
		NH_dev_mma_M[0].sum += NHdatastore;

		if (b01_flag == 1) {
			NH_dev_mma_M[0].cou += NHdatastore * RealData.R_D.FF.ADF[b01_pos];
		} else {
			NH_dev_mma_M[0].cou = 0;
		}
		NH_dev_mma_M[0].num++;
	}

	if (NH_dev_mma_H[0].num == 0) {
		NH_dev_mma_H[0].max = NH_dev_mma_H[0].min = NH_dev_mma_H[0].sum =
				NHdatastore;
		NH_dev_mma_H[0].cou = NHdatastore;
		NH_dev_mma_H[0].num++;
	} else {
		if (NHdatastore < NH_dev_mma_H[0].min)
			NH_dev_mma_H[0].min = NHdatastore;
		if (NHdatastore > NH_dev_mma_H[0].max)
			NH_dev_mma_H[0].max = NHdatastore;
		NH_dev_mma_H[0].sum += NHdatastore;
		if (b01_flag == 1) {
			NH_dev_mma_H[0].cou += NHdatastore * RealData.R_D.FF.ADF[b01_pos];
		} else {
			NH_dev_mma_H[0].cou = 0;
		}
		NH_dev_mma_H[0].num++;
	}
	if (NH_dev_mma_D[0].num == 0) {
		NH_dev_mma_D[0].max = NH_dev_mma_D[0].min = NH_dev_mma_D[0].sum =
				NHdatastore;
		NH_dev_mma_D[0].cou = NHdatastore;
		NH_dev_mma_D[0].num++;
	} else {
		if (NHdatastore < NH_dev_mma_D[0].min)
			NH_dev_mma_D[0].min = NHdatastore;
		if (NHdatastore > NH_dev_mma_D[0].max)
			NH_dev_mma_D[0].max = NHdatastore;
		NH_dev_mma_D[0].sum += NHdatastore;
		if (b01_flag == 1) {
			NH_dev_mma_D[0].cou += NHdatastore * RealData.R_D.FF.ADF[b01_pos];
		} else {
			NH_dev_mma_D[0].cou = 0;
		}
		NH_dev_mma_D[0].num++;
	}
}

void dev_calibrate_sample(INT8U type)
{
	INT8U caltemp[12];
	INT16U devidtmp = 0, devchtmp = 0;
	INT8U CRC16[2];
	union {
		char add1[2];
		int add2;
	} add3;

	for (devidtmp = 0; devidtmp < 6; devidtmp++) {
		for (devchtmp = 0; devchtmp < 16; devchtmp++) {
			if (SPARA.PO_Type[devidtmp] == 2) {
				if (strcmp(devcpoID,
						MOD_Gas[SPARA.PO_SerialNum[devidtmp][devchtmp]].PO_code)
						== 0) {
					caltemp[0] = devidtmp + 1;
					caltemp[1] = 0x10;
					add3.add1[0] =
							MOD_Gas[SPARA.PO_SerialNum[devidtmp][devchtmp]].modbus_address[1];
					add3.add1[1] =
							MOD_Gas[SPARA.PO_SerialNum[devidtmp][devchtmp]].modbus_address[0];
					if (type == 'c') {
						caltemp[2] = add3.add1[1];
						caltemp[3] = add3.add1[0];
					} else if (type == 's') {
						add3.add2 += 1;
						caltemp[2] = add3.add1[1];
						caltemp[3] = add3.add1[0];
					}
					caltemp[4] = 0x00;
					caltemp[5] = 0x01;    //number of registers
					caltemp[6] = 0x02;    //two bytes
					caltemp[7] = 0xff;    //data high byte
					caltemp[8] = 0x00;        //data low byte

					CRC_Calculation(caltemp, 9, CRC16);
					caltemp[9] = CRC16[0];		//CRC高
					caltemp[10] = CRC16[1];		//CRC低

					/*禁止中断*/
					_BIC_SR(GIE);
					if (caltemp[0] <= 0x04)
						SendData(caltemp, 11, COM5); //485
					else if (caltemp[0] == 0x05)
						SendData(caltemp, 11, COM2); //232
					else
						SendData(caltemp, 11, COM3); //232
					/*开中断*/
					_BIS_SR(GIE);
					return;
				}
			}

			else if (SPARA.PO_Type[devidtmp] == 1) {
				if (strcmp(devcpoID,
						MOD_Water[SPARA.PO_SerialNum[devidtmp][devchtmp]].PO_code)
						== 0) {
					caltemp[0] = devidtmp + 1;
					caltemp[1] = 0x10;
					add3.add1[1] =
							MOD_Water[SPARA.PO_SerialNum[devidtmp][devchtmp]].modbus_address[0];
					add3.add1[0] =
							MOD_Water[SPARA.PO_SerialNum[devidtmp][devchtmp]].modbus_address[1];
					if (type == 'c') {
						caltemp[2] = add3.add1[1];
						caltemp[3] = add3.add1[0];
					} else if (type == 's') {
						add3.add2 += 1;
						caltemp[2] = add3.add1[1];
						caltemp[3] = add3.add1[0];
					}
					caltemp[4] = 0x00;
					caltemp[5] = 0x01;    //number of registers
					caltemp[6] = 0x02;    //two bytes
					caltemp[7] = 0xff;    //data high byte
					caltemp[8] = 0x00;    //data low byte

					CRC_Calculation(caltemp, 9, CRC16);
					caltemp[9] = CRC16[0];		//CRC高
					caltemp[10] = CRC16[1];		//CRC低

					/*禁止中断*/
					_BIC_SR(GIE);
					if (caltemp[0] <= 0x04)
						SendData(caltemp, 11, COM5); //485
					else if (caltemp[0] == 0x05)
						SendData(caltemp, 11, COM2); //232
					else
						SendData(caltemp, 11, COM3); //232
					/*开中断*/
					_BIS_SR(GIE);
					return;
				}
			}

		}
	}
}

void dev_operate(void)
{
	Symbol.Mod_checkover = 1;
}

void dev_settimes(void)
{
	INT8U caltemp[60];
	INT16U devidtmp = 0, devchtmp = 0, i;
	INT8U CRC16[2];
	union {
		char add1[2];
		int add2;
	} add3;

	for (devidtmp = 0; devidtmp < 6; devidtmp++) {
		for (devchtmp = 0; devchtmp < 16; devchtmp++) {
			if (SPARA.PO_Type[devidtmp] == 2) {
				if (strcmp(devcpoID,
						MOD_Gas[SPARA.PO_SerialNum[devidtmp][devchtmp]].PO_code)
						== 0) {
					caltemp[0] = devidtmp + 1;
					caltemp[1] = 0x10;
					add3.add1[0] =
							MOD_Gas[SPARA.PO_SerialNum[devidtmp][devchtmp]].modbus_address[1];
					add3.add1[1] =
							MOD_Gas[SPARA.PO_SerialNum[devidtmp][devchtmp]].modbus_address[0];

					add3.add2 += 10;
					caltemp[2] = add3.add1[1];
					caltemp[3] = add3.add1[0];

					caltemp[4] = (INT8U) (devctnum >> 8);
					caltemp[5] = (INT8U) devctnum;    //number of registers
					caltemp[6] = (INT8U) (2 * devctnum);    //bytes
					for (i = 0; i < devctnum; i++) {
						caltemp[7 + 2 * i] = 0x00;    //data high byte
						caltemp[8 + 2 * i] = devctime[i];        //data low byte
					}
					CRC_Calculation(caltemp, 7 + 2 * i, CRC16);
					caltemp[7 + 2 * i] = CRC16[0];		//CRC高
					caltemp[8 + 2 * i] = CRC16[1];		//CRC低

					/*禁止中断*/
					_BIC_SR(GIE);
					if (caltemp[0] <= 0x04)
						SendData(caltemp, 9 + 2 * i, COM5); //485
					else if (caltemp[0] == 0x05)
						SendData(caltemp, 9 + 2 * i, COM2); //232
					else
						SendData(caltemp, 9 + 2 * i, COM3); //232
					/*开中断*/
					_BIS_SR(GIE);
					devctnum = 0;
					return;
				}
			}

			else if (SPARA.PO_Type[devidtmp] == 1) {
				if (strcmp(devcpoID,
						MOD_Water[SPARA.PO_SerialNum[devidtmp][devchtmp]].PO_code)
						== 0) {
					caltemp[0] = devidtmp + 1;
					caltemp[1] = 0x10;
					add3.add1[1] =
							MOD_Water[SPARA.PO_SerialNum[devidtmp][devchtmp]].modbus_address[0];
					add3.add1[0] =
							MOD_Water[SPARA.PO_SerialNum[devidtmp][devchtmp]].modbus_address[1];
					add3.add2 += 10;
					caltemp[2] = add3.add1[1];
					caltemp[3] = add3.add1[0];

					caltemp[4] = (INT8U) (devctnum >> 8);
					caltemp[5] = (INT8U) devctnum;    //number of registers
					caltemp[6] = (INT8U) (2 * devctnum);    //bytes
					for (i = 0; i < devctnum; i++) {
						caltemp[7 + 2 * i] = 0x00;    //data high byte
						caltemp[8 + 2 * i] = devctime[i];        //data low byte
					}
					CRC_Calculation(caltemp, 7 + 2 * i, CRC16);
					caltemp[7 + 2 * i] = CRC16[0];		//CRC高
					caltemp[8 + 2 * i] = CRC16[1];		//CRC低

					/*禁止中断*/
					_BIC_SR(GIE);
					if (caltemp[0] <= 0x04)
						SendData(caltemp, 9 + 2 * i, COM5); //485
					else if (caltemp[0] == 0x05)
						SendData(caltemp, 9 + 2 * i, COM2); //232
					else
						SendData(caltemp, 9 + 2 * i, COM3); //232
					/*开中断*/
					_BIS_SR(GIE);
					devctnum = 0;
					return;
				}
			}

		}
	}
}

void dataget_jiubo(void) //通过232扩展串口 com2来处理
{
	INT8U cmd = 0x11;
	/*禁止中断*/
	_BIC_SR(GIE);
	SendData(&cmd, 1, COM2); //232
	_BIS_SR(GIE);
}
void dataparse_jiubo(INT8U *buf)
{
	INT8U valustr[6];
	//十六进制：30H，30H，32H，33H，34H，35H，00H，ODH
	if (*(buf + 6) == 0x00 && *(buf + 5) != 0x00) {

		strncpy(valustr, buf, 6);
		B01datastore = (valustr[0] - 0x30) * 1000 + (valustr[1] - 0x30) * 100
				+ (valustr[2] - 0x30) * 10 + (valustr[3] - 0x30)
				+ (valustr[4] - 0x30) * 0.1 + (valustr[5] - 0x30) * 0.01;

	} else {
		memset(valustr, 0, 6);
	}
}
void B01_ModataUpload(INT8U ModM)
{
	union {
		char a[4];
		float b;
	} Mod_D;
	INT8U NP = 0;
	INT8U Negtive[2] = "-\0";
	INT8U rtdstr[11] = ";B01-Rtd=\0";
	INT8U flagstr[13] = ",B01-Flag=N\0";
	INT8U minstr[11] = ";B01-Min=\0";
	INT8U avgstr[11] = ",B01-Avg=\0";
	INT8U maxstr[11] = ",B01-Max=\0";
	INT8U coustr[11] = ",B01-Cou=\0";
	INT8U ftstring[18];	//污染采集值的缓存
	INT16U i;
	float totaltmp = 0, total_b01_tmp = 0;

	if (ModM == Mod_RealD) {
		Mod_D.b = B01datastore;
		if ((Mod_D.a[3] & 0x80) == 0x80) {
			Mod_D.a[3] &= 0x7f;
			NP = 1;
		}

		float_to_string(Mod_D.b, ftstring);
		if (NP) {
			insert(ftstring, Negtive, 1);
		}
		strcat(CBAG.cbag_dynamic, rtdstr);
		strcat(CBAG.cbag_dynamic, ftstring);
		MemoryClear(ftstring, sizeof(ftstring));
		strcat(CBAG.cbag_dynamic, flagstr);
	} else {
		MAX_MIN *maxminp;
		switch (ModM) {
		case Mod_MinD:
			maxminp = B01_dev_mma_M;
			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->min;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, minstr); //min
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				maxminp->avg = 0;
			else
				maxminp->avg = maxminp->sum / maxminp->num;
			Mod_D.b = maxminp->avg;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, avgstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->max;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, maxstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->sum / 1000; //L/s=>m3/s
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, coustr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));
			break;
		case Mod_HourD:
			maxminp = B01_dev_mma_H;
			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->min;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, minstr); //min
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				maxminp->avg = 0;
			else
				maxminp->avg = maxminp->sum / maxminp->num;
			Mod_D.b = maxminp->avg;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, avgstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->max;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, maxstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->sum / 1000; //L/s=>m3/s
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, coustr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));
			break;
		case Mod_DayD:
			maxminp = B01_dev_mma_D;
			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->min;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}

			strcat(CBAG.cbag_dynamic, minstr); //min
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

#if 0
			for (i = 0; i < 24; i++) {
				total_b01_tmp += Hour_B01_avg[i];
			}
			if (total_b01_tmp != 0.0) {
				maxminp->avg = totaltmp / 24;
			} else {
				maxminp->avg = 0;
			}
#else
			if (maxminp->num == 0)
				maxminp->avg = 0;
			else
				maxminp->avg = maxminp->sum / maxminp->num;
#endif
			Mod_D.b = maxminp->avg;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, avgstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->max;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, maxstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->sum / 1000; //L/s=>m3/s
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, coustr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			break;
		default:
			maxminp = 0;
			break;
		}
	}
}

void dataget_zhonglv(void) //通过232扩展串口 com3来处理
{
	//INT8U *cmd="%02#RDD0152101525**\r\n";
	INT8U cmd[21] = { 0x25, 0x30, 0x32, 0x23, 0x52, 0x44, 0x44, 0x30, 0x31,
			0x35, 0x32, 0x31, 0x30, 0x31, 0x35, 0x32, 0x35, 0x2A, 0x2A, 0x0D,
			0x0A };
	// INT8U end=0x0D;
	// INT8U end2=0x0A;
	/*禁止中断*/
	_BIC_SR(GIE);
	// SendData(cmd,strlen(cmd),COM3); //232
	SendData(cmd, 21, COM3); //232

	//SendData(&end2,1,COM3); //232
	_BIS_SR(GIE);
}
void dataparse_zhonglv(INT8U *buf)
{
	INT8U valustr[8];

	//十进制：%02$RD0803271521260000040718回车
	//十六进制：25 30 32 24 52 44 30 38 30 33 32 37 31 35 32 31 32 36 30 30 30 30 30 34 30 37 31 38 回车
	// Delay_N_mS(20000);

	if (*(buf + 1) == '%' && *(buf + 29) == 0x0D && *(buf + 28) == '*'
			&& *(buf + 26) != '*') {

		strncpy(valustr, buf + 19, 8);
		NHdatastore = (valustr[0] - 0x30) * 1000000
				+ (valustr[1] - 0x30) * 100000 + (valustr[2] - 0x30) * 10000
				+ (valustr[3] - 0x30) * 1000 + (valustr[4] - 0x30) * 100
				+ (valustr[5] - 0x30) * 10 + (valustr[6] - 0x30)
				+ (valustr[7] - 0x30) * 0.1;
		NHdatastore = NHdatastore / 10;
		// SendData(buf,strlen(buf),COM3); //232
		//  SendData(&end,1,COM3); //232
		// SendData(&end2,1,COM3); //232
		memset(valustr, 0, 8);

	} else {
		memset(valustr, 0, 8);
	}
	//NHdatastore=string_to_float(valustr)/10;
}

void NH3_ModataUpload(INT8U ModM)
{
	union {
		char a[4];
		float b;
	} Mod_D;

	INT8U NP = 0;
	INT8U Negtive[2] = "-\0";
	INT8U rtdstr[11] = ";060-Rtd=\0";
	INT8U flagstr[13] = ",060-Flag=N\0";
	INT8U minstr[11] = ";060-Min=\0";
	INT8U avgstr[11] = ",060-Avg=\0";
	INT8U maxstr[11] = ",060-Max=\0";
	INT8U coustr[11] = ",060-Cou=\0";
	INT8U ftstring[18];	//污染采集值的缓存

	if (ModM == Mod_RealD) {
		Mod_D.b = NHdatastore;
		if ((Mod_D.a[3] & 0x80) == 0x80) {
			Mod_D.a[3] &= 0x7f;
			NP = 1;
		}

		float_to_string(Mod_D.b, ftstring);
		if (NP) {
			insert(ftstring, Negtive, 1);
		}
		strcat(CBAG.cbag_dynamic, rtdstr);
		strcat(CBAG.cbag_dynamic, ftstring);
		MemoryClear(ftstring, sizeof(ftstring));
		strcat(CBAG.cbag_dynamic, flagstr);
	} else {
		MAX_MIN *maxminp;
		switch (ModM) {
		case Mod_MinD:
			maxminp = NH_dev_mma_M;
			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->min;

			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, minstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				maxminp->avg = 0;
			else
				maxminp->avg = maxminp->sum / maxminp->num;
			Mod_D.b = maxminp->avg;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, avgstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->max;

			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, maxstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->cou / 1000000;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, coustr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));
			maxminp->num = 0;
			break;
		case Mod_HourD:
			maxminp = NH_dev_mma_H;
			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->min;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, minstr); //min
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				maxminp->avg = 0;
			else
				maxminp->avg = maxminp->sum / maxminp->num;
			Mod_D.b = maxminp->avg;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, avgstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->max;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, maxstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->cou / 1000000;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, coustr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			maxminp->num = 0;
			break;
		case Mod_DayD:
			maxminp = NH_dev_mma_D;
			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->min;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}

			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, minstr); //min
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0) {
				maxminp->avg = 0;
			} else {
				maxminp->avg = maxminp->sum / maxminp->num;
			}

			Mod_D.b = maxminp->avg;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, avgstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->max;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, maxstr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));

			if (maxminp->num == 0)
				Mod_D.b = 0;
			else
				Mod_D.b = maxminp->cou / 1000000;
			if ((Mod_D.a[3] & 0x80) == 0x80) {
				Mod_D.a[3] &= 0x7f;
				NP = 1;
			}
			float_to_string(Mod_D.b, ftstring);
			if (NP) {
				insert(ftstring, Negtive, 1);
			}
			strcat(CBAG.cbag_dynamic, coustr);
			strcat(CBAG.cbag_dynamic, ftstring);
			MemoryClear(ftstring, sizeof(ftstring));
			maxminp->num = 0;
			break;
		default:
			maxminp = 0;
			break;
		}
	}
}
#pragma vector=WDT_VECTOR
__interrupt void WatchDog_ISR(void)
{
	WatchDogCNT++;
	if ((WatchDogCNT % 0xc8) == 0)
		if ((Symbol.Mod_symbol == 0)) {
			Symbol.Mod_Device_Check = 1;
		}
}
