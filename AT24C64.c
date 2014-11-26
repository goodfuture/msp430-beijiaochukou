#include <msp430xG46x.h>
#include "test.h"

#define AT24WR_PROTECT    P3OUT|=BIT0
#define AT24WR_UNPROTECT  P3OUT&=~BIT0

#define I2C_START     UCB0CTL1|=UCTXSTT
#define I2C_TRANSMIT  UCB0CTL1|=UCTR
#define I2C_RECEIVE   UCB0CTL1&=~UCTR
#define I2C_STOP      UCB0CTL1|=UCTXSTP

void Delay_N_mS(unsigned int n_milisecond) /* n mS delay */
{
	unsigned char i;
	while (n_milisecond--) {
		i = 17;
		while (i--)
			;
	}
}

void AT24C64_W(void *src, INT16U des, INT16U len)
{
	volatile INT16U i;
	INT8U *Source;

	Source = (INT8U *) src;
	I2C_TRANSMIT;   //transmit mode
	UCB0I2CSA = 0x50;
	AT24WR_UNPROTECT;
	for (i = 0; i < len; i++) {
		I2C_TRANSMIT;
		I2C_START;
		while ((IFG2 & UCB0TXIFG)==0);
		UCB0TXBUF = (INT8U) (des >> 8);
		while ((IFG2 & UCB0TXIFG)==0);
		UCB0TXBUF = (INT8U) des;
		while ((IFG2 & UCB0TXIFG)==0);
		UCB0TXBUF = *Source++;
		while ((IFG2 & UCB0TXIFG)==0);
		I2C_STOP;
		while (UCB0CTL1 & UCTXSTP)
			;
		des++;
		Delay_N_mS(500);
	}
	AT24WR_PROTECT;
}

void AT24C64_R(void *des, INT16U src, INT16U len)
{
	INT16U i;
	INT8U *Dest;
	Dest = (INT8U *) des;
	UCB0I2CSA = 0x50;
	for (i = 0; i < len; i++) {
		I2C_TRANSMIT;   //transmit mode

		I2C_START;
		while ((IFG2 & UCB0TXIFG)==0);
		UCB0TXBUF = (INT8U) (src >> 8);
		while ((IFG2 & UCB0TXIFG)==0);
		UCB0TXBUF = (INT8U) src;

		I2C_RECEIVE;
		I2C_START;
		while ((IFG2 & UCB0RXIFG)==0);
		*Dest = UCB0RXBUF;
		I2C_STOP;

		Dest++;
		src++;
		Delay_N_mS(200);
	}
}

void AT24C64_RS(void *des, INT16U src, INT16U len)
{
	INT16U i;
	INT8U *Dest;
	Dest = (INT8U *) des;

	I2C_TRANSMIT;   //transmit mode
	I2C_START;
	while ((IFG2 & UCB0TXIFG)==0);
	UCB0TXBUF = (INT8U) (src >> 8);
	while ((IFG2 & UCB0TXIFG)==0);
	UCB0TXBUF = (INT8U) src;
	while ((IFG2 & UCB0TXIFG)==0);

	I2C_RECEIVE;
	I2C_START;

	while ((IFG2 & UCB0RXIFG)==0);
	*Dest = UCB0RXBUF;

	for (i = 0; i < len; i++) {
		while ((IFG2 & UCB0RXIFG)==0);
		*Dest++ = UCB0RXBUF;
	}
	I2C_STOP;
}
