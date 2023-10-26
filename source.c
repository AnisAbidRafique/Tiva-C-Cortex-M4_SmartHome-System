#include"tm4c123gh6pm.h"

void gpio_init(void);
void delay(int ms);
void lcd_port_init(void);//initilzing lcd
void write_command( int cmd);
void write_data (char data);
void lcd_init(void);
void  lcd_clear(void);
void lcd_pos_xy(unsigned char x,unsigned char y);
void write_string(char *ptr);

/*void output1_status();
void output2_status();
void output3_status();
void output4_status();

int sendData = 0;*/


void gpio_init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x10;//01 0000//       A
	;
	;
	;
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY; // for relay firs
	GPIO_PORTE_CR_R = 0x0F;//1111 
	
	GPIO_PORTE_AFSEL_R = 0;
	GPIO_PORTE_DEN_R = 0x0F;
	GPIO_PORTE_DIR_R = 0x0F;
}

void lcd_port_init(void)//initilzing lcd
{
	SYSCTL_RCGC2_R |= 0X22;//10 0010 
	;
	;
	;
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R = 0x0E;// PF1(RS) PF2
	
	GPIO_PORTF_AFSEL_R= 0;
	GPIO_PORTF_DEN_R = 0x0E;//0 1110
	GPIO_PORTF_DIR_R =0X0E;//0 1110
	
	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTB_CR_R = 0xFF;//
	
	GPIO_PORTB_AFSEL_R=0;
	GPIO_PORTB_DEN_R = 0xFF;//0 1110
	GPIO_PORTB_DIR_R =0XFF;//0 1110
	
}

void uart0_port_init(void) //uar 0 
{
	GPIO_PORTA_LOCK_R = 0x4C4F434B; // Unlock key //GPIO_LOCK_KEY // 
	GPIO_PORTA_CR_R = 0x03; // Unlock all pins //A0 A1 
	GPIO_PORTA_DEN_R = 0x03; // Digital enable on all pins
	GPIO_PORTA_AFSEL_R = 0x03; // PA 0-1 as UARTs
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011; // PA 0-1 as UART TX RX
}

void uart0_peripheral_init(void)
{
	SYSCTL_RCGCUART_R |= 0x01; // Enable UART 0
	SYSCTL_RCGC2_R |= 0x01; // Enable port A
	;
	;
	;
	UART0_CTL_R = 0x0;  // disable // 
  UART0_IBRD_R = 8;   // 16000000/(16*115200) = 8.6805 // f/16*B.R
	UART0_FBRD_R = 44; //0.6805*64
	UART0_LCRH_R = 0x68; // 2 stop bits, no parity //01101000 // 8 bi da // FIFO Enabled
	uart0_port_init();
	UART0_CTL_R = 0x301; //001100000001  // Tx,Rx seT and Enable
}

void uart0_send_char(char ch) // print
{
	while ((UART0_FR_R & 0x80) != 0x80)  // 1 Tx FIFO is EmpTie // prin da
	{
	}
	UART0_DR_R = ch;
}

char uart0_get_char(void) //read
{
	char c;
	if((UART0_FR_R & 0x10) != 0x10)  // 1 Rx FIFO is empty // receive // user some da
		c = (UART0_DR_R & 0x0FF);
	return c;
}
void printString (char * string)
{
	while(*string)
	{
		uart0_send_char(*(string));
		string++;
	}
}

//LCD
void delay(int ms)
{
	int i,j;
	for( i=0;i<ms;i++)
		for(j=0;j<4000;j++)
			;
}

void write_command( int cmd)
{
	GPIO_PORTF_DATA_R = 0x0;// PF3=En PF2=R/w	PF1 = RS
	GPIO_PORTB_DATA_R = cmd;

	//generating pulse
	delay(1);
	GPIO_PORTF_DATA_R |= 0x08;//00 1000
	delay	(1);
	GPIO_PORTF_DATA_R &= ~0x08;
	delay(4);
}

void write_data (char data)
{
	GPIO_PORTF_DATA_R = 0x02;//00 0010
	GPIO_PORTB_DATA_R = data;
	
	//generating pulse
	delay(1);
	GPIO_PORTF_DATA_R |= 0x08;//00 0100
	delay	(1);
	GPIO_PORTF_DATA_R &= ~0x08;
	delay(4);

}

void lcd_init(void)
{
	GPIO_PORTF_DATA_R=0x0;
	delay(15);
	
	write_command(0x38); // 8 bit
	write_command(0x10); // set cursor
	write_command(0x0C); // disp on . coursor off
	write_command(0x06);// entry mode
}

void  lcd_clear(void)
{
	write_command (0x01);//clear disp

	delay(2);
	write_command (0x02); // move coursor to home
	delay(2);
}
 
void lcd_pos_xy(unsigned char x,unsigned char y)
{
	unsigned char row_start_address[]={0x80,0xC0};
	write_command(row_start_address[x-1]+y-1);
	delay(2);
}

void write_string(char *ptr)
{
	while(*ptr)
	{
		write_data(*ptr);
		ptr++;
  }
}


void output1_status()
{
if((GPIO_PORTE_DATA_R & 0x1) == 0x1) // relay off 
{
	lcd_pos_xy(2,2);
	write_string("x");
}
else if((GPIO_PORTE_DATA_R & 0x1) != 0x1) // relay on 
{
	lcd_pos_xy(2,2);
write_string("o");
}
}

void output2_status()
{
lcd_pos_xy(2, 4);
if((GPIO_PORTE_DATA_R & 0x2) == 0x2)
	write_string("x");
else if((GPIO_PORTE_DATA_R & 0x2) != 0x2)
	write_string("o");
}

void output3_status()
{
lcd_pos_xy(2, 6);
if((GPIO_PORTE_DATA_R & 0x4) == 0x4)
	write_string("x");
else if((GPIO_PORTE_DATA_R & 0x4) != 0x4)
	write_string("o");
}

void output4_status()
{
lcd_pos_xy(2, 8);
if((GPIO_PORTE_DATA_R & 0x8) == 0x8)
	write_string("x");
else if((GPIO_PORTE_DATA_R & 0x8) != 0x8)
	write_string("o");
}

 void status (void)
 {
	 output1_status();
	 output2_status();
	 output3_status();
	 output4_status();
 }
int main(void)
{
	char read;
	lcd_port_init();
	lcd_init();
	lcd_clear();
	lcd_pos_xy(1,2);
	write_string("1 2 3 4");
	uart0_peripheral_init();
	gpio_init(); //port E for relay
	GPIO_PORTE_DATA_R &= (~0x0000); // ac low 0 on  1 off 
	status ();
	printString("Choose between 1 to 6 which switch you want On:\n\r"); // 5 all 4 se
	while(1)
	{
		read = uart0_get_char(); // Read input
		//uart0_send_char(read);   // displa 
		switch(read)
		{
			case '1':
				GPIO_PORTE_DATA_R ^= 0x01; 
			  output1_status();
				break;
			case '2':
				GPIO_PORTE_DATA_R ^= 0x02;
			  output2_status();
				break;
			
			case '3':
				GPIO_PORTE_DATA_R ^= 0x04;
			  output3_status();
				break;
			case '4':
				GPIO_PORTE_DATA_R ^= 0x08;
			  output4_status();
				break;
			case '5': 
				GPIO_PORTE_DATA_R &= (~0x0F); // 0000 1111 
			  status ();
				break;
			case '6':
				GPIO_PORTE_DATA_R |= (0x0F);
			  status ();
				break;
			default:{}
			}
			/*if(read == '4')
			{
				GPIO_PORTE_DATA_R ^= 0x08;
				output4_status();
			}*/
	}
}
