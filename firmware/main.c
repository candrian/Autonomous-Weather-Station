/***************************************************************************
 GSM/GPRS Autonomous Weather Station (Tracking System) May, 2011
 (c) 2011 Andrianakis Charalampos , Tsompanakis Konstantinos
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Attention !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/* The code was written just to test the hardware. So it is as simple as it could. 
 It takes an analoge measurement and sends it to a web server over gprs. There isn't 
 a good communication between the gsm and the pic because the pic checks only if 
 an answer is received and not the content of the answer. */

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Attention !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


/* The code Compiled with CCS */
#include <string.h>
#include "lcd_conf.c"
#include "main.h"

#use delay(clock = 16000000)
#USE RS232 (BAUD = 9600, XMIT = PIN_C6, RCV = PIN_C7, STREAM = gsm)

/* Define Carriage Return & New Line */
#define CR 0x0d
#define N 0x0A

/* Define Uart buffer size */
#define BUFFER_SIZE 16

/* Uart buffer */
BYTE buffer[BUFFER_SIZE];
BYTE next_in = 0;
BYTE wait_for_n=2;
BYTE data_ready=0;

/* Temp is used to calculate the temperature */
float temp;

/* String For Call Ready */
char ready[10]={'C','a','l','l',' ','R','e','a','d','y'};

/* ISR POWER-LCD jumper reset (meaning 
that lcd plugged in so run LCD initialization)*/
/*
#int_ext
void LCD_plug(){
	enable_interrupts(GLOBAL); 
	delay_ms(500);
	lcd_init();
}
*/

/* ISR Data Received */
/* capturing the incoming bytes from the gsm (uart) */
#int_rda
void serial_isr() {
	
	//disable_interrupts(global);

	//Read byte and write to buffer
	buffer[next_in]=getc();
	//Check if it is Carriage Return
	if (buffer[next_in]==CR){
		//Wait the next to be New Line
		wait_for_n=1;
	}else if (wait_for_n==1 && buffer[next_in]==N){
		wait_for_n=0;
		if (data_ready==1){
			data_ready=0;
		}else{
			data_ready=1;
		}
		//Reset buffer to clear CR & N
		next_in=0;
	}else{
		next_in++;
	}
	//If buffer is full write from the begin
	if(next_in==BUFFER_SIZE){
		// Buffer full !!
		next_in=0;           
	} 
	
	//enable_interrupts(global);
}

/* Initialize GRPS to send data */
void gprs_init(){
	
	/*The initialization routine is very simple and it just checks
	 if an answer received. It doesn't check the content of the answer.
	 I did this for writing time saving.*/

	//Inform the user
	lcd_putc("\fInitialize  GPRS ");
	lcd_putc("\n  to send data   ");
	delay_ms(1000);
	delay_ms(1000);
   
	//Disable gsm echo mode   
	fprintf(gsm, "\r\nATE0\r\n");
	lcd_putc("\fDisabling echo ");
	//Wait for answer
	while (data_ready==0)
	lcd_putc("\n               ");
	//The delay is for the user to have time to read the LCD message
	delay_ms(1000);
   
	//Attach to GPRS Service
	fprintf(gsm, "\r\nAT+CGATT=1\r\n");
	lcd_putc("\fAttaching Gprs");
	while (data_ready==0)
	lcd_putc("\n               ");
	delay_ms(1000);
	
   	/********************************************************************/
	/*The configuration commands are written for Greek Vodafone network */
	/********************************************************************/
	
	//Define pdp context (cid,pdp type, APN)
	fprintf(gsm, "\r\nAT+CGDCONT=1,\"IP\",\"internet.vodafone.gr\"\r\n");
	lcd_putc("\fDefine PDP");
	while (data_ready==0)
	lcd_putc("\n               ");
	delay_ms(1000);
   
/*  
	//Configure DNS servers Primary & Secondary
	fprintf(gsm, "\r\nAT+CDNSCFG=\"213.249.17.10\",\"213.249.17.11\"\r\n");
	lcd_putc("\fDefine DNS");
	while (data_ready==0)
	printf(lcd_putc,"nf%s   ",buffer);
	delay_ms(1000);
*/

	//Start task give APN UID AND PWD
	fprintf(gsm, "\r\nAT+CSTT=\"internet.vodafone.gr\",\"wap\",\"wap\"\r\n");
	lcd_putc("\fStart Task");  
	while (data_ready==0)
	lcd_putc("\n               ");
	delay_ms(1000);
   
	//Bring up wireless connection with GPRS
	fprintf(gsm, "\r\nAT+CIICR\r\n");
	lcd_putc("\fBringUpWireless");
	while (data_ready==0)
	lcd_putc("\n               ");
	delay_ms(1000);
   
	//Get Ip Address
	fprintf(gsm, "\r\nAT+CIFSR\r\n");
	lcd_putc("\f GetLocalIpAddr ");
	//while (data_ready==0)
	delay_ms(1000);
	delay_ms(1000);
	lcd_putc("\n               ");
   
	//Tells module to add an 'IP Header' to receive data
	fprintf(gsm, "\r\nAT+CIPHEAD=1\r\n");
	lcd_putc("\fIp Header");
	while (data_ready==0)
	lcd_putc("\n               ");
	delay_ms(1000);

/*
	//Indicates whether connection request will be IP address (0), or domain name (1)
	fprintf(gsm, "\r\nAT+CDNSORIP=1\r\n");
	lcd_putc("\nIndicate Domain");
	delay_ms(1000);
*/
	
	//Start up TCP connection (mode, IP address/name, port)
	fprintf(gsm, "\r\nAT+CIPSTART=\"TCP\",\"www.yourserver.com\",\"80\"\r\n");
	lcd_putc("\f Tcp Connecting ");
	while (data_ready==0)
	lcd_putc("\n               ");
	delay_ms(1000);
	delay_ms(1000);
   
	//Get ready to send data
	fprintf(gsm, "\r\nAT+CIPSEND\r\n");
	lcd_putc("\fRdy to send Data");
	delay_ms(1000);
	
}  

/* Print Welcome Messages To LCD */
void welcome(){
	
	lcd_putc("\fWelcome to GPRS ");
	lcd_putc("\ntracking system ");

	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

	lcd_putc("\f  Version 1.0   ");
	lcd_putc("\n Copyright 2011 ");

	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	lcd_putc("\fAndrianakis Har.");
	lcd_putc("\nTsompanakis Kos."); 

	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

	lcd_putc("\f Ready to power ");
	lcd_putc("\n on Gprs module ");
	
}

/* Take Measurements Routine */
void take_measurement(){
	
	unsigned int value0;//, value1, value2;
	
	//The 30ms delay is for the adc to stabilize

/*
	//Wind
	set_adc_channel( 0 ); 
    delay_ms(30);
    value0 = read_adc();
   
	//Humidity
    set_adc_channel( 1 ); 
    delay_ms(30);
    value1 = read_adc();
*/
	
	//Temperature
	set_adc_channel( 2 );
	delay_ms(30);
	value0 = read_adc();

	//Calculate temperature value
	//Value = (MeasuredVoltage/VREF)*256
    temp=(value0/3)*256;
	
	//Send temperature value to LCD
    printf(lcd_putc,"\fT=%fC\n",temp);

}

/* PIC Peripherals Setup */
void setup(){
	//Configure ADC
	setup_adc_ports(AN0_AN1_AN2_AN4_VSS_VREF);
	setup_adc(ADC_CLOCK_INTERNAL);
	
	setup_psp(PSP_DISABLED);
	setup_spi(SPI_SS_DISABLED);
	
	//Power LCD's backlight
	output_low(PIN_C2);
/*
	setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
	setup_timer_1(T1_DISABLED);
	setup_timer_2(T2_DISABLED,0,1);
	setup_comparator(NC_NC_NC_NC); 
 
	//Configure PWM for driving LCD LED on CCP1 (PIN17)
	setup_ccp1(CCP_PWM);
	setup_timer_2(T2_DIV_BY_16, 124, 1); // 2khz
	set_pwm1_duty(35); // 26% duty cycle on pin C2   
*/

}

void main(){

	//Setup PIC's Peripherals
	setup();
	
	// Initialize LCD
	lcd_init();
   
	//Enable UART Receive interrupt
	enable_interrupts(INT_RDA);
	
	//POWER-LCD jumper interrupt
	//enable_interrupts(INT_EXT);
	
	enable_interrupts(GLOBAL); 

	delay_ms(1000);
   
	//Clear Uart buffer
	strcpy(buffer, " ");

	//Print welcome messages to LCD
	welcome();

	delay_ms(1000);
	delay_ms(1000);
	
	take_measurement();
	
	delay_ms(1000);
	delay_ms(1000);
	
	lcd_putc("\nPowerOnGsmToSend");
   
	//Untill "Call Ready" received print the messages to LCD
	while(strncmp (buffer, ready, 10)){
		delay_ms(1000);
		if (wait_for_n==0){
			printf(lcd_putc,"\f%s",buffer);
			lcd_putc("\n                ");
			next_in=0;
		}
	}
	
	//Initialize gprs to send data
	gprs_init();

	delay_ms(1000);
	delay_ms(1000);
	
	//Send data
	fprintf(gsm, "GET /receive.php?value0=%f HTTP/1.0\r\n\r\n%c",temp,26);
	lcd_putc("\f Data send!");   

	//Do nothing Loop
	while(1){
	}
}
