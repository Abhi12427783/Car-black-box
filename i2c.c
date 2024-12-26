
#include <xc.h>

void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON1 = 0x28;

	SSPADD = 0x31; //in order to select frequency
	/* Use I2C levels, worked also with '0' */
	CKE = 0; //
	/* Disable slew rate control  worked also with '0' */
	SMP = 1; //to select the slew rate
	/* Clear SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear bus collision flag */
	BCLIF = 0;
}

void i2c_idle(void)  //whether communication is happened or not
{
	while (!SSPIF);
	SSPIF = 0;  //instruction not completed
}

void i2c_ack(void)  //if using only complete
{
	if (ACKSTAT)
	{
		/* Do debug print here if required */
	}
}

void i2c_start(void) //to start the communication
{
	SEN = 1; 
	i2c_idle();
}

void i2c_stop(void) //to stop communication
{
	PEN = 1;
	i2c_idle(); //to confirm it stops
}

void i2c_rep_start(void)  //to start repeat start
{
	RSEN = 1;
	i2c_idle(); //to check whether it performs that
}

void i2c_write(unsigned char data) //to check transmission is over or not
{
	SSPBUF = data;
	i2c_idle(); //for confirming
}

void i2c_rx_mode(void) //to keep the mc in receive mode
{
	RCEN = 1;
	i2c_idle();
}

void i2c_no_ack(void) //to check whether ack is sent or not
{
	ACKDT = 1; //since ack enable bit is disabled 
	ACKEN = 1;
}

unsigned char i2c_read(void)  //to receive a data from the slave
{
	i2c_rx_mode();  //to be in receive mode
	i2c_no_ack();   //once received it should sent no ack

	return SSPBUF;
}