#include <msp430xG46x.h>
#include "test.h"

#define CONTINUOUS_MREAD      0X03
#define BUFFER1_READ          0XD1
#define BUFFER2_READ          0XD3
#define BUFFER1_WRITE         0x84
#define BUFFER2_WRITE         0x87
#define MEMORY_WRITE_THBUFF1  0X82
#define MEMORY_WRITE_THBUFF2  0X85
#define BUFFER1_TO_MEMORY     0x83
#define BUFFER2_TO_MEMORY     0x86
#define MEMORY_TO_BUFFER1     0x53
#define MEMORY_TO_BUFFER2     0x55

#define FLASH_ENABLE  P4OUT &=~BIT1/*P5OUT &=~BIT2*/
#define FLASH_DISABLE P4OUT |=BIT1/*P5OUT |=BIT2*/
#define FLASH_RST     P4OUT &=~BIT0;P4OUT |=BIT0
#define FLASH_PROTECT P5OUT &=~BIT7
#define FLASH_UNPROTECT P5OUT |=BIT7

#define FLASHBUFFER1       0X00
#define FLASHBUFFER2       0X01
/*
*********************************************************************************************************
*                               FLASH MEMORY READ
*
* Description: This function is used to read the main memory of the flash
*
* Arguments  : addr:  memory address where to store the data
*              array: pointer to the stored data
*              len:   the length of the data to be stored
*
* Returns    : none
*
* write by   : Wen Jianjun
*
* data       : 0722 2008
*
*********************************************************************************************************
*/
void FlashMemoryRead(INT8U *addr,void *array,INT16U len)
{
  INT8U i;
  INT8U *Dest;

  Dest  =(INT8U *)array;
  _BIC_SR(GIE);
  FLASH_ENABLE;
  /*send command*/
  while(!(IFG2&UTXIFG1));
  U1TXBUF =CONTINUOUS_MREAD;
  /*send address 3 bytes*/
  for(i=0;i<3;i++)
  {
    while(!(IFG2&UTXIFG1));
    U1TXBUF =*addr++;
  }
  /*read a dummy byte*/
  Delay_N_mS(20);
  while(!(IFG2&UTXIFG1));
    U1TXBUF =0;
    while(!(IFG2&URXIFG1));
    *Dest=U1RXBUF;
  /*read data from flash*/
  while(len--)
  {
    while(!(IFG2&UTXIFG1));
    U1TXBUF =0;
    while(!(IFG2&URXIFG1));
    *Dest++=U1RXBUF;
  }
  _BIS_SR(GIE);
  Delay_N_mS(20);
  FLASH_DISABLE;
}
/*
*********************************************************************************************************
*                               FLASH BUFFER READ
*
* Description: This function is used to read the data from the buffers of the flash
*
* Arguments  : addr:  memory address where to read the data
*              array: pointer to the stored data
*              len:   the length of the data to read
*              buff:  indicate that which buffer to read from(the value should be one
*                     of these:FLASHBUFFER1,FLASHBUFFER2)
*
* Returns    : none
*
* write by   : Wen Jianjun
*
* data       : 0722 2008
*
*********************************************************************************************************
*/
void FlashBufferRead(INT8U *addr,void *array,INT16U len,INT8U buff)
{
  INT8U i;
  INT8U *Dest;

  Dest  =(INT8U *)array;
  _BIC_SR(GIE);
  FLASH_ENABLE;
  /*send command*/
  //while(!(IFG2&UTXIFG1));
  if(buff==FLASHBUFFER1)
    U1TXBUF =BUFFER1_READ;
  else
    U1TXBUF =BUFFER2_READ;
  /*send address 3 bytes*/
  for(i=0;i<3;i++)
  {
    while(!(IFG2&UTXIFG1));
    U1TXBUF =*addr++;
  }
  /*send one don't care byte*/
  //while(!(IFG2&UTXIFG1));
  //U1TXBUF =0;
  /*receive a dummy byte*/
  while(!(IFG2&UTXIFG1));
    U1TXBUF =0;
    while(!(IFG2&URXIFG1));
    *Dest=U1RXBUF;

  /*read data from flash*/
  while(len--)
  {
    while(!(IFG2&UTXIFG1));
    U1TXBUF =0;
    while(!(IFG2&URXIFG1));
    *Dest++=U1RXBUF;
  }
  _BIS_SR(GIE);
  FLASH_DISABLE;
}
/*
*********************************************************************************************************
*                               FLASH BUFFER WRITE
*
* Description: This function is used to write the buffers of the flash
*
* Arguments  : addr:  memory address where to store the data
*              array: pointer to the stored data
*              len:   the length of the data to be stored
*              buff:  indicate that which buffer to write to (the value should be one
*                     of these:FLASHBUFFER1,FLASHBUFFER2)
*
* Returns    : none
*
* write by   : Wen Jianjun
*
* data       : 0722 2008
*
*********************************************************************************************************
*/
void FlashBufferWrite(INT8U *addr,void *array,INT16U len,INT8U buff)
{
  INT8U i;
  INT8U *Dest;

  FLASH_UNPROTECT;
  Dest  =(INT8U *)array;
  FLASH_ENABLE;
  _BIC_SR(GIE);
  /*send command*/
  //while(!(IFG2&UTXIFG1));
  if(buff==FLASHBUFFER1)
    U1TXBUF =BUFFER1_WRITE;
  else
    U1TXBUF =BUFFER2_WRITE;
  /*send address 3 bytes*/
  for(i=0;i<3;i++)
  {
    while(!(IFG2&UTXIFG1));
    U1TXBUF =*addr++;
  }
  /*write data to flash buffer*/
  while(len--)
  {
    while(!(IFG2&UTXIFG1));
    U1TXBUF =*Dest++;
  }
  while(!(TXEPT&U1TCTL));
  //Delay_N_mS(20);
  _BIS_SR(GIE);
  FLASH_DISABLE;
  FLASH_PROTECT;
}
/*
*********************************************************************************************************
*                               FLASH MEMORY WRITE
*
* Description: This function is used to program the memory of the flash through the buffers
*
* Arguments  : addr:  memory address where to store the data
*              array: pointer to the stored data
*              len:   the length of the data to be stored
*              buff:  indicate that which buffer to be used (the value should be one
*                     of these:FLASHBUFFER1,FLASHBUFFER2)
*
* Returns    : none
*
* write by   : Wen Jianjun
*
* data       : 0722 2008
*
*********************************************************************************************************
*/
void FlashMemoryWrite(INT8U *addr,void *array,INT16U len,INT8U buff)
{
  INT8U i;
  INT8U *Dest;

  FLASH_UNPROTECT;
  Dest  =(INT8U *)array;
  FLASH_ENABLE;
  _BIC_SR(GIE);
  /*send command*/
  //while((IFG2&UTXIFG1)==0);
  if(buff==FLASHBUFFER1)
    U1TXBUF =MEMORY_WRITE_THBUFF1;
  else
    U1TXBUF =MEMORY_WRITE_THBUFF2;
  /*send address 3 bytes*/
  for(i=0;i<3;i++)
  {
    while((IFG2&UTXIFG1)==0);
    U1TXBUF =*addr++;
  }
  /*write data to flash memory*/
  Delay_N_mS(20);
  while(len--)
  {
    while((IFG2&UTXIFG1)==0);
    U1TXBUF =*Dest++;
  }
  while(!(TXEPT&U1TCTL));
  //Delay_N_mS(10);
  _BIS_SR(GIE);
  FLASH_DISABLE;
  FLASH_PROTECT;
  Delay_N_mS(2500);
}

void FlashMemorytoBuffer(INT8U *addr,INT8U buff)
{
  INT8U i;

  FLASH_ENABLE;
  _BIC_SR(GIE);
  if(buff==FLASHBUFFER1)
    U1TXBUF =MEMORY_TO_BUFFER1;
  else
    U1TXBUF =MEMORY_TO_BUFFER2;
  for(i=0;i<3;i++)
  {
    while((IFG2&UTXIFG1)==0);
    U1TXBUF =*addr++;
  }
  while(!(TXEPT&U1TCTL));
  _BIS_SR(GIE);
  FLASH_DISABLE;
  Delay_N_mS(2500);
}

void FlashBuffertoMemory(INT8U *addr,INT8U buff)
{
  INT8U i;

  FLASH_UNPROTECT;
  FLASH_ENABLE;
  _BIC_SR(GIE);
  if(buff==FLASHBUFFER1)
    U1TXBUF =BUFFER1_TO_MEMORY;
  else
    U1TXBUF =BUFFER2_TO_MEMORY;
  for(i=0;i<3;i++)
  {
    while((IFG2&UTXIFG1)==0);
    U1TXBUF =*addr++;
  }
  while(!(TXEPT&U1TCTL));
  _BIS_SR(GIE);
  FLASH_DISABLE;
  FLASH_PROTECT;
  Delay_N_mS(2500);
}

void FlashClearMemory(INT8U *addr,INT16U len,INT8U buff)
{
  INT8U i;
  //INT8U *Dest;

  //Dest  =(INT8U *)array;
  FLASH_UNPROTECT;
  FLASH_ENABLE;
  /*send command*/
  //while((IFG2&UTXIFG1)==0);
  if(buff==FLASHBUFFER1)
    U1TXBUF =MEMORY_WRITE_THBUFF1;
  else
    U1TXBUF =MEMORY_WRITE_THBUFF2;
  /*send address 3 bytes*/
  for(i=0;i<3;i++)
  {
    while((IFG2&UTXIFG1)==0);
    U1TXBUF =*addr++;
  }
  /*write data to flash memory*/
  Delay_N_mS(20);
  while(len--)
  {
    while((IFG2&UTXIFG1)==0);
    U1TXBUF =0;
  }
  while(!(TXEPT&U1TCTL));
  //Delay_N_mS(10);
  FLASH_DISABLE;
  FLASH_PROTECT;
}
