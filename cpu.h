#ifndef CPU_H
#define CPU_H

#ifdef MAINBOARD
  #define RUN_ON        P9OUT&=~BIT4
  #define RUN_OFF       P9OUT|=BIT4
#else
  #define DI1_ENABLE    P2OUT&=~BIT3
  #define DI1_DISABLE   P2OUT|=BIT3
  #define DI2_ENABLE    P2OUT&=~BIT4
  #define DI2_DISABLE   P2OUT|=BIT4

  #define CS_4245_EN    P2OUT&=~BIT5
  #define CS_4245_DIS   P2OUT|=BIT5
  #define DO_ENABLE     P2OUT&=~BIT0
  #define DO_DISABLE    P2OUT|=BIT0
  #define DO_Disable DO_DISABLE
  #define DO_Enable  DO_ENABLE

  #define RUN_ON        P7OUT&=~BIT4
  #define RUN_OFF       P7OUT|=BIT4

  #define DOOUT         P1OUT
  #define DIN           P1IN

  #define COM1_SEND
  #define COM1_RECEIVE
  #define COM2_SEND     P5OUT|=BIT2
  #define COM2_RECEIVE  P5OUT&=~BIT2
  #define COM3_SEND     P5OUT|=BIT3
  #define COM3_RECEIVE  P5OUT&=~BIT3
  #define COM4_SEND     P5OUT|=BIT4
  #define COM4_RECEIVE  P5OUT&=~BIT4
  #define COM5_SEND     P5OUT|=BIT5
  #define COM5_RECEIVE  P5OUT&=~BIT5

  #define LCD_light_ON P9OUT&=~BIT2
  #define LCD_light_OFF  P9OUT|=BIT2

  #define GPRS_RST      P3OUT|=BIT4;P3OUT&=~BIT4
  #define GPRS_ONLINE   P3IN&BIT3
  #define GPRS_POWERON  P7OUT|=BIT3
  #define GPRS_POWEROFF P7OUT&=~BIT3
#endif

#endif
