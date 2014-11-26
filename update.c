#include <msp430xG46x.h>
#include <string.h>
//#include "update.h"

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

#define FLASHBUFFER1       0X00
#define FLASHBUFFER2       0X01

//#define INT8U  char
//#define INT16U unsigned int
//#define INT32U unsigned long

//void CRC_Calculation(INT8U *src,INT16U len,INT8U *des);
//INT8U StrToASCII(INT8U *src,INT8U *des,INT16U len);
//void FlashMemoryWrite(INT8U *addr,void *array,INT16U len,INT8U buff);
void UDelay_N_mS( unsigned int n_milisecond);
extern void Relocation(void);
void SendReflect(const INT8U *src,INT16U len);
void CRC_update(INT8U *src,INT16U len,INT8U *des);
struct _UPDATE
{
  INT8U head[2];
  INT8U lenth[4];
  INT8U prog[1024];
  INT8U CRC[5];
  INT8U tail[2];
  INT8U symbolover;
}UpdateProg;
INT8U NewProg[512];
INT8U NewProgStoreAddr[3]={0xf0,0x00,0x00};
INT16U ProgBlockNum=0;
INT16U UPackageLen=0;
INT16U UProgLen=0;
INT16U UProgCount=0;
INT32U SECTIONS=0Xf000;
INT32U PROG_SADDR;
INT16U PROG_BYTENUM;
//INT8U *PNewProg;
#pragma location="UPDATESEG"
void ASCIIToStr(INT8U *src,INT8U *des,INT16U len)
{
  INT16U i,lens;
  INT8U tempL,tempH;

  lens=len>>1;
  for(i=0;i<lens;i++)
  {
    if(*src>'9')
      tempH=((*src)-0x37)&0x0f;
    else
      tempH=(*src)&0x0f;
    if(*(src+1)>'9')
      tempL=((*(src+1))-0x37)&0x0f;
    else
      tempL=(*(src+1))&0x0f;
    src=src+2;
    *des=tempL|(tempH<<4);
    des++;
  }
}
//#pragma vector=USCIAB0RX_VECTOR
#pragma location="UPINTSEG"
__interrupt void ProgUpdateRX_ISR(void)
{
  INT8U temp;
  temp=UCA0RXBUF;
  switch(temp)
  {
    case 'U':
      UpdateProg.head[0]=temp;
      UPackageLen=1;
      UProgLen=0;
      UProgCount=0;
    break;
    case 'P':
    case 'L':
      if(UPackageLen==1)
      {
        UpdateProg.head[1]=temp;
        UPackageLen++;
      }
      else
      {
        UPackageLen=0;
        UProgLen=0;
        UProgCount=0;
      }
    break;
    case 0x0d:
      if((UProgCount+10)==UPackageLen)
      {
         UpdateProg.tail[0]=temp;
         UpdateProg.CRC[4]=0;
         UPackageLen++;
      }
      else
      {
        UPackageLen=0;
        UProgLen=0;
        UProgCount=0;
      }
    break;
    case 0x0a:
      if((UProgCount+11)==UPackageLen)
      {
         UpdateProg.tail[1]=temp;
         UPackageLen++;
         UpdateProg.symbolover=1;
      }
      else
      {
        UPackageLen=0;
        UProgLen=0;
        UProgCount=0;
      }
    break;
    default:
      if((UPackageLen>=2)&&(UPackageLen<6))
      {
        UpdateProg.lenth[UPackageLen-2]=temp;
        UPackageLen++;
        if(UPackageLen==6)
        {
          UProgLen  =(UpdateProg.lenth[0]&0x0f)*1000+(UpdateProg.lenth[1]&0x0f)*100+(UpdateProg.lenth[2]&0x0f)*10+(UpdateProg.lenth[3]&0x0f);
        }
      }
      else if(UPackageLen>=6)
      {
        if(UProgCount<UProgLen)
        {
          UpdateProg.prog[UProgCount++]=temp;
          UPackageLen++;
        }
        else
        {
          UpdateProg.CRC[UPackageLen-UProgLen-6]=temp;
          UPackageLen++;
        }
      }
      else
      {
        UPackageLen=0;
        UProgLen=0;
        UProgCount=0;
      }
    break;
  }
}

#pragma location="UPDATESEG"
void FlashMemoryProgRead(INT8U *addr,void *array,INT16U len)
{
  INT8U i;
  INT8U *Dest;
  INT8U *addrs;

  Dest  =(INT8U *)array;
  addrs =addr;
  FLASH_ENABLE;
  /*send command*/
  while(!(IFG2&UTXIFG1));
  U1TXBUF =CONTINUOUS_MREAD;
  /*send address 3 bytes*/
  for(i=0;i<3;i++)
  {
    while(!(IFG2&UTXIFG1));
    U1TXBUF =*addrs++;
  }
  /*read a dummy byte*/
  UDelay_N_mS(20);
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
  UDelay_N_mS(20);
  FLASH_DISABLE;
}
#define FLASH_PROTECT P5OUT &=~BIT7
#define FLASH_UNPROTECT P5OUT |=BIT7

#pragma location="UPDATESEG"

void FlashMemoryProgWrite(INT8U *addr,void *array,INT16U len,INT8U buff)
{
  INT8U i;
  INT8U *Dest;

  Dest  =(INT8U *)array;
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
    U1TXBUF =*Dest++;
  }
  while(!(TXEPT&U1TCTL));
  //Delay_N_mS(10);
  FLASH_DISABLE;
  FLASH_PROTECT;
}
#pragma location="UPDATESEG"
void StoreProgram(void)
{

  INT16U addrtemp;
  INT16U lentemp;
  INT8U temp[2];
  //INT8U *NewProg;

  //NewProg=(INT8U *)0X1200;

  {
    lentemp=UProgLen>>1;
    temp[0]=(INT8U)(lentemp>>8);
    temp[1]=(INT8U)lentemp;
    FlashMemoryProgWrite(NewProgStoreAddr,temp,2,FLASHBUFFER1);//存储程序段长度
    UDelay_N_mS(2000);
    NewProgStoreAddr[2]=0x10;
    ASCIIToStr(UpdateProg.prog,NewProg,UProgLen);
    FlashMemoryProgWrite(NewProgStoreAddr,NewProg,lentemp,FLASHBUFFER1);
    //FlashMemoryWrite(NewProgStoreAddr,NewProg,lentemp,FLASHBUFFER1);
    UDelay_N_mS(2000);
      //FlashMemoryProgRead(NewProgStoreAddr,NewProg,lentemp);
    //FlashMemoryRead(NewProgStoreAddr,NewProg,lentemp);
    ProgBlockNum++;//程序段计数器加1
    addrtemp=(((INT16U)NewProgStoreAddr[0])<<8)|((INT16U)NewProgStoreAddr[1]);
    addrtemp+=0X08;//页地址加1
    NewProgStoreAddr[0]=(INT8U)(addrtemp>>8);
    NewProgStoreAddr[1]=(INT8U)(addrtemp);
    NewProgStoreAddr[2]=0;
  }

}



#pragma location="UPDATESEG"
void Progupdatemain(void)
//void main(void)
{
  INT8U CRC16[2];
  INT8U crc[5]="\0\0\0\0\0";
  INT16U i;
  volatile INT8U ProgReOver=0;
  INT8U Progstoreaddr[3];
  INT8U templen[2];
  INT16U  lenth;
  INT16U addrtemp;
  const char ReflOK[11]="UPOK75B7\r\n\0";
  const char ReflERR[12]="UPERRDC88\r\n\0";
  const char ReflSUS[16]="UPSUCCESS4953\r\n\0";
  //INT32U ProgAddrs;
  //INT8U *NewProg;

  //NewProg=(INT8U *)0X1500;
  _BIC_SR(GIE); //关总中断

  IE1 &=~WDTIE; //关看门狗中断
  ADC12IE=0x0000; //关AD中断
  P2IES=0x00;     //关外部中断
  IFG2=0;
  IFG1=0;
  P2IFG &=0x00;
  ADC12IFG=0X0000;

  SECTIONS=0XFFF2;
  ClearFlashSection();
  ChangeINTVector();
  Relocation();
  //INT8U tempRefl[]={Ready39FC};
  
  _BIS_SR(GIE);   //开总中断
  SendReflect("Ready39FC\r\n",11);
  while(1)
  {
    if(UpdateProg.symbolover==1)
    {
      CRC_update(UpdateProg.prog,UProgLen,CRC16);
      StrToASCII(CRC16,crc,2);
      if(strcmp(crc,UpdateProg.CRC)!=0)
      {
        SendReflect(ReflERR,11);
        //CRC校验错误
      }
      else
      {
        if(UpdateProg.head[1]=='P')
        {
          StoreProgram();
        }
        else if(UpdateProg.head[1]=='L')
        {
          StoreProgram();
          ProgReOver=1;
          NewProgStoreAddr[0]=0XF0;
          NewProgStoreAddr[1]=0X00;
          NewProgStoreAddr[2]=0X00;
        }
        SendReflect(ReflOK,10);
      }
      UpdateProg.symbolover=0;
    }
    if(ProgReOver)
    {
      _BIC_SR(GIE);
      Progstoreaddr[0]=0xf0;
      Progstoreaddr[1]=0x00;
      Progstoreaddr[2]=0x00;
      //PROG_SADDR=0X3100;
      /**************************************************
                clear the flash
                0x3100--0xfbff
                0xfe00--0xffff
                0xffff--0x1afff
      **************************************************/
      for(i=0;i<102;i++)//擦除0x3100－0xfbff
      {
        SECTIONS=0X3100+0X200*i;
        ClearFlashSection();//擦除flash
      }

      SECTIONS=0Xfffe;    //擦除中断向量表
      ClearFlashSection();//擦除flash

      for(i=0;i<88;i++) //擦除0x10000－0x1affff
      {
        SECTIONS=0X10010+0X200*i;
        ClearFlashSection();//擦除flash
      }

      /*************************************************
                    update new program
      *************************************************/
      WDTCTL  =WDTPW+WDTTMSEL+WDTCNTCL+WDTHOLD;
      for(i=0;i<ProgBlockNum;i++)
      {
        FlashMemoryProgRead(Progstoreaddr,templen,2);
        lenth=((INT16U)templen[0]<<8)|((INT16U)templen[1]);
        Progstoreaddr[2]=0x10;
        FlashMemoryProgRead(Progstoreaddr,NewProg,lenth);

        PROG_SADDR=(((long)NewProg[0])<<16)|(((long)NewProg[1])<<8)|((long)NewProg[2]);//the location of the block
        PROG_BYTENUM=lenth-3;//the number of bytes of the block
        asm("calla #01100h");//the writeflash function is relocated at 0x1100

        WDTCTL  =WDTPW+WDTTMSEL+WDTCNTCL+WDTHOLD;
        addrtemp=(((INT16U)Progstoreaddr[0])<<8)|((INT16U)Progstoreaddr[1]);
        addrtemp+=0X08;//页地址加1
        Progstoreaddr[0]=(INT8U)(addrtemp>>8);
        Progstoreaddr[1]=(INT8U)(addrtemp);
        Progstoreaddr[2]=0;
      }
      ProgReOver=0;
      SendReflect(ReflSUS,15);
      //判断更新是否成功
      asm("MOVX.A 0FFFEh,R5");
      asm("MOVX.A R5,PC");
    }
  }
}
#pragma location="UPDATESEG"
void SendReflect(const INT8U *src,INT16U len)
{
  INT16U i;
  for(i=0;i<len;i++)
  {
    //while(!(IFG2&UCA0TXIFG));
    UCA0TXBUF =*src++;
    while(!(IFG2&UCA0TXIFG));
  }
}
#pragma location="UPDATESEG"
void UDelay_N_mS( unsigned int n_milisecond)  /* n mS delay */
{
   unsigned char i;
   while(n_milisecond--)
  {
           i=20;
           while(i--);
  }
}
#pragma location="UPDATESEG"
void CRC_update(INT8U *src,INT16U len,INT8U *des)
{
  union
  {
    INT16U UC;
    INT8U UCHL[2];
  }CV;
  INT8U i;
  CV.UC=0XFFFF;
  while(len--)
  {
    CV.UCHL[0]^= *src++;
    for(i=0;i<8;i++)
    {
      if((CV.UC&0x0001)==1)
      {
        CV.UC>>=1;
        CV.UC^=0xa001;
      }
      else
      {
        CV.UC>>=1;
      }
    }
  }
  *des=CV.UCHL[0];
  *(des+1)=CV.UCHL[1];
}
/*
#pragma vector=RESET_VECTOR
__interrupt void RESET_ISR(void)
{
  //asm("MOV.W #WDTPW+WDTHOLD,&WDTCTL");
  //asm("BRA #__program_start");
  START();
}*/
