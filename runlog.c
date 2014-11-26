#include <string.h>
#include"test.h"

struct _LCD {
	unsigned LCD_DOS :1;
	unsigned LCD_set :1;
	unsigned LCD_back :1;
	unsigned LCD_backdoor :1;
	unsigned LCD_Dot :1;
	unsigned LCD_EQU :1;
	unsigned LCD_LOG :1;
};
extern struct _LCD LCDSymbol;
void run_log_record(RUNRECORD *runlog)
{
	INT16U pageaddr;
	INT8U rdaddr[3];

	pageaddr = 64 * 9;
	rdaddr[0] = 0xff;
	rdaddr[1] = ((INT8U) (pageaddr >> 8)) | 0xf0;
	rdaddr[2] = (INT8U) (pageaddr);

	if (System_Time[9] != runlog->Rtstime[9]) {
		runlog->acctime += 1;
		if ((Symbol.LCD_deal == 0) && (LCD_page == 44)) {
			LCDSymbol.LCD_EQU = 1;
			Symbol.LCD_deal = 1;
		}
	}
	MemoryCopy(System_Time, runlog->Rtstime, 14);
	FlashMemoryWrite(rdaddr, runlog, sizeof(RUNRECORD), FLASHBUFFER1);
}

void run_log_init(RUNRECORD *runlog)
{
	INT16U pageaddr, i;
	INT8U rdaddr[3];
	RUNRECORD runlogtmp;

	//pageaddr =64*9;
	rdaddr[0] = 0xff;
	rdaddr[1] = 0xf0;
	rdaddr[2] = 0;
	MemoryClear(&runlogtmp, sizeof(RUNRECORD));
	FlashMemorytoBuffer(rdaddr, FLASHBUFFER1);
	Delay_N_mS(600);
	FlashMemorytoBuffer(rdaddr, FLASHBUFFER1);
	Delay_N_mS(600);

	pageaddr = 9 * 64;   //current struct buffer offset address
	rdaddr[0] = 0;
	rdaddr[1] = (INT8U) (pageaddr >> 8);
	rdaddr[2] = (INT8U) (pageaddr);
	FlashBufferRead(rdaddr, &runlogtmp, sizeof(RUNRECORD), FLASHBUFFER1); //hour data flag struct
	Delay_N_mS(200);
	FlashBufferRead(rdaddr, &runlogtmp, sizeof(RUNRECORD), FLASHBUFFER1);

	MemoryCopy(runlogtmp.Rtstime, runlog->OFFtime, 14);
	MemoryCopy(System_Time, runlog->ONtime, 14);
	MemoryCopy(System_Time, runlog->Rtstime, 14);
	runlog->acctime = 0;

	pageaddr = 0;
	for (i = 0; i < 9; i++) {
		MemoryClear(&runlogtmp, sizeof(RUNRECORD));
		pageaddr = 64 * (i + 1);
		rdaddr[0] = 0;
		rdaddr[1] = (INT8U) (pageaddr >> 8);
		rdaddr[2] = (INT8U) (pageaddr);
		FlashBufferRead(rdaddr, &runlogtmp, sizeof(RUNRECORD), FLASHBUFFER1);

		pageaddr = 64 * i;
		rdaddr[0] = 0;
		rdaddr[1] = (INT8U) (pageaddr >> 8);
		rdaddr[2] = (INT8U) (pageaddr);
		FlashBufferWrite(rdaddr, &runlogtmp, sizeof(RUNRECORD), FLASHBUFFER1);
	}
	pageaddr = 64 * 9;
	rdaddr[0] = 0;
	rdaddr[1] = (INT8U) (pageaddr >> 8);
	rdaddr[2] = (INT8U) (pageaddr);
	FlashBufferWrite(rdaddr, runlog, sizeof(RUNRECORD), FLASHBUFFER1);
	Delay_N_mS(400);
	rdaddr[0] = 0xff;
	rdaddr[1] = 0xf0;
	rdaddr[2] = 0;
	FlashBuffertoMemory(rdaddr, FLASHBUFFER1);
	Delay_N_mS(400);
}

void runlogreport(void)
{
	INT16U pageaddr, i;
	INT8U rdaddr[3];
	RUNRECORD runlogtmp;
	INT8U tmpbuff[18] = "\0";
	INT8U offtime[10] = "OFFTime=\0";
	INT8U ontime[10] = ";ONTime=\0";
	INT8U runtime[11] = ";RunTime=\0";

	//pageaddr =64*9;
	rdaddr[0] = 0xff;
	rdaddr[1] = 0xf0;
	rdaddr[2] = 0;
	FlashMemorytoBuffer(rdaddr, FLASHBUFFER1);
	Delay_N_mS(400);

	for (i = 0; i < 10; i++) {
		pageaddr = 64 * i;
		rdaddr[0] = 0;
		rdaddr[1] = (INT8U) (pageaddr >> 8);
		rdaddr[2] = (INT8U) (pageaddr);
		FlashBufferRead(rdaddr, &runlogtmp, sizeof(RUNRECORD), FLASHBUFFER1);
		if (runlogtmp.OFFtime[0] == 0)
			continue;
		Symbol.ccc = 1;
		Response('x');
		Symbol.ccc = 0;

		strcat(CBAG.cbag_dynamic, offtime);
		MemoryCopy(runlogtmp.OFFtime, tmpbuff, 14);
		strcat(CBAG.cbag_dynamic, tmpbuff);
		MemoryClear(tmpbuff, sizeof(tmpbuff));

		strcat(CBAG.cbag_dynamic, ontime);
		MemoryCopy(runlogtmp.ONtime, tmpbuff, 14);
		strcat(CBAG.cbag_dynamic, tmpbuff);
		MemoryClear(tmpbuff, sizeof(tmpbuff));

		strcat(CBAG.cbag_dynamic, runtime);
		float_to_string(RunLog.acctime, tmpbuff);
		strcat(CBAG.cbag_dynamic, tmpbuff);
		MemoryClear(tmpbuff, sizeof(tmpbuff));

		Add_Send()
		;
	}
}

