#ifndef UPDATE_H
#define UPDATE_H

typedef char  INT8U;
typedef unsigned int INT16U;
typedef unsigned long INT32U;

#define FLASHBUFFER1       0X00
#define FLASHBUFFER2       0X01



void Delay_N_mS( unsigned int n_milisecond);
INT8U StrToASCII(INT8U *src,INT8U *des,INT16U len);
void CRC_Calculation(INT8U *src,INT16U len,INT8U *des);
void MemoryClear(INT8U *pdes,INT16U size);
int CPU_init(void);
void FlashMemoryWrite(INT8U *addr,void *array,INT16U len,INT8U buff);
void FlashMemoryRead(INT8U *addr,void *array,INT16U len);
#endif
