//LCD 4 Bit Mode 8051

#include <8051.h>
#include "delay.h"
#define LCD     P1
#define ENABLE      0x10
#define REG_SL      0x20
/* 

LCD: DB4|DB5|DB6|DB7|EN |RS    RW
P1:   0   1   2   3   4   5    GND 

*/

void lcd_reset()  //Reset sequence as stated in the LCD datasheet
{
	delay_ms(350);
	LCD = 0xFF;
	delay_ms(20);
	LCD = 0x03|ENABLE;
	LCD = 0x03;
	delay_ms(15);
	LCD = 0x03|ENABLE;
	LCD = 0x03;
	delay_ms(5);
	LCD = 0x03|ENABLE;
	LCD = 0x03;
	delay_ms(5);
	LCD = 0x02|ENABLE;
	LCD = 0x02;
	delay_ms(5);
}


void lcd_cmd(unsigned char cmd)               //Subroutine to send command
{ 
	LCD = ((cmd>>4)&0x0F)|ENABLE;     //Sending higher nibble by shifting with Pulsing Enable high
	delay_ms(5);
	LCD = ((cmd>>4)&0x0F);
  	delay_ms(5);
	LCD = (cmd & 0x0F)|ENABLE;          //Sending lower nibble Enable low
	LCD = (cmd & 0x0F);
}


void lcd_data (char *dat)          //Subroutine to send data
{ 
  	while(*dat != '\0') {
		LCD = (((*dat>>4)&0x0F)|ENABLE|REG_SL); //Sending data by making RS=1
		delay_ms(1);
		LCD = (((*dat>>4)&0x0F)|REG_SL);
		delay_ms(1);
		LCD = ((*dat & 0x0F)|ENABLE|REG_SL);
		delay_ms(1);
		LCD = ((*dat & 0x0F)|REG_SL);
		delay_ms(1);
		dat++;
	}
}


void lcd_init () 
{
	lcd_cmd(0x28);       // 4-bit mode - 2 line - 5x7 font. 
	lcd_cmd(0x0F);       // Display cursor with blink.
	lcd_cmd(0x06);       // Automatic Increment - No Display shift.
   	lcd_cmd(0x01);
   	lcd_cmd(0x02);       //Clear screen and return home    
	lcd_cmd(0x80);       // First row first column
}


void sweep(void) 
{
unsigned int freq;
unsigned int z;
unsigned int notes;
unsigned int cycles;

		freq=398;
		z=3980;
		for(notes=398;notes>2;notes--) {
			for(cycles=z/20;cycles>0;cycles--) {
				P3=0x55;
				delay_us(freq);
				P3=0xAA;
				delay_us(freq);
			}
			freq--;
			z=z-5;
		}

}



void main()
{
	unsigned char x;
	unsigned int y;
    lcd_reset();
    lcd_init();
    lcd_data(" [RuhNet Labs] ");
    while(1) {
		delay_ms(1000);
   		lcd_init();       //Clear screen and return home    
    	lcd_data(" [RuhNet Labs] ");
		P3 = 0xFF; //turn all P3 outputs on
		delay_ms(2000);
		lcd_cmd(0x80);       // First row first column
    	lcd_data("_Intel 8051 MCU_");
		P3 = 0x00;
		delay_ms(1000);
		P3 = 0xFF;
		delay_ms(1000);
		lcd_cmd(0x80);       // First row first column
    	lcd_data(">LED/Audio Test<");
		P3 = 0x00;
		delay_ms(2000);
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("(Port P3: 0xAA) ");
		P3 = 0xAA;
		delay_ms(1000);
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("(Port P3: 0x55) ");
		P3 = 0x55;
		delay_ms(1000); 

		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("P3 rate: ~100Hz  ");
		for(x=100;x>0;x--) { //2 seconds, 100Hz
			P3=0x55;
			delay_ms(5);
			P3=0xAA;
			delay_ms(5);
		}
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("P3 rate: ~10Hz  ");
		for (x=24;x>0;x--) { //4.8 seconds, 10Hz
			P3=0x55;
			delay_ms(50);
			P3=0xAA;
			delay_ms(50);
		}
		for(x=10;x>0;x--) { //0.2 seconds, 
			P3=0x55;
			delay_ms(5);
			P3=0xAA;
			delay_ms(5);
		}
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("P3 rate: ~220Hz ");
		for(x=220;x>0;x--) { //2 sec, 200Hz
			P3=0x55;
			delay_us(250);
			P3=0xAA;
			delay_us(250);
		}
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("P3 rate: ~247Hz ");
		for(y=247;y>0;y--) { //2 sec, 250Hz
			P3=0x55;
			delay_us(161);
			P3=0xAA;
			delay_us(161);
		}
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("P3 rate: ~262Hz ");
		for(y=262;y>0;y--) { 
			P3=0x55;
			delay_us(152);
			P3=0xAA;
			delay_us(152);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: ~294Hz");
		for(y=294;y>0;y--) { 
			P3=0x55;
			delay_us(136);
			P3=0xAA;
			delay_us(135);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: ~329Hz");
		for(y=329;y>0;y--) { 
			P3=0x55;
			delay_us(121);
			P3=0xAA;
			delay_us(121);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: ~370Hz");
		for(y=370;y>0;y--) { 
			P3=0x55;
			delay_us(108);
			P3=0xAA;
			delay_us(107);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: ~415Hz");
		for(y=415;y>0;y--) { 
			P3=0x55;
			delay_us(96);
			P3=0xAA;
			delay_us(96);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: ~440Hz");
		for(y=440;y>0;y--) { 
			P3=0x55;
			delay_us(91);
			P3=0xAA;
			delay_us(91);
		}

		lcd_cmd(0xC0);      
    	lcd_data("Wait for it...  ");
		P3=0x00;
		delay_ms(500);

		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("FruitFly 2167Hz!");
		for(y=7585;y>0;y--) { 
			P3=0x55;
			delay_us(18);
			P3=0xAA;
			delay_us(18);
		}
		lcd_cmd(0x80);       
		lcd_data("~Chord: A Major");
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("A -> C# -> E-> A");
		for(y=440;y>0;y--) { //1 sec, A 440Hz
			P3=0x55;
			delay_us(91);
			P3=0xAA;
			delay_us(91);
		}
		for(y=523;y>0;y--) { //1 sec, C# 523Hz
			P3=0x55;
			delay_us(76);
			P3=0xAA;
			delay_us(76);
		}
		for(y=659;y>0;y--) { //1 sec, E 659Hz
			P3=0x55;
			delay_us(60);
			P3=0xAA;
			delay_us(60);
		}
		for(y=880;y>0;y--) { //1 sec, A 880Hz
			P3=0x55;
			delay_us(44);
			P3=0xAA;
			delay_us(44);
		}


		for(y=110;y>0;y--) { //0.25 sec, A 440Hz
			P3=0x55;
			delay_us(91);
			P3=0xAA;
			delay_us(91);
		}
		for(y=131;y>0;y--) { //0.25 sec, C# 523Hz
			P3=0x55;
			delay_us(76);
			P3=0xAA;
			delay_us(76);
		}
		for(y=165;y>0;y--) { //0.25 sec, E 659Hz
			P3=0x55;
			delay_us(60);
			P3=0xAA;
			delay_us(60);
		}
		for(y=220;y>0;y--) { //0.25 sec, A 880Hz
			P3=0x55;
			delay_us(44);
			P3=0xAA;
			delay_us(44);
		}


		for(y=110;y>0;y--) { //0.25 sec, A 440Hz
			P3=0x55;
			delay_us(91);
			P3=0xAA;
			delay_us(91);
		}
		for(y=131;y>0;y--) { //0.25 sec, C# 523Hz
			P3=0x55;
			delay_us(76);
			P3=0xAA;
			delay_us(76);
		}
		for(y=165;y>0;y--) { //0.25 sec, E 659Hz
			P3=0x55;
			delay_us(60);
			P3=0xAA;
			delay_us(60);
		}
		for(y=220;y>0;y--) { //0.25 sec, A 880Hz
			P3=0x55;
			delay_us(44);
			P3=0xAA;
			delay_us(44);
		}



		for(y=110;y>0;y--) { //0.25 sec, A 440Hz
			P3=0x55;
			delay_us(91);
			P3=0xAA;
			delay_us(91);
		}
		for(y=131;y>0;y--) { //0.25 sec, C# 523Hz
			P3=0x55;
			delay_us(76);
			P3=0xAA;
			delay_us(76);
		}
		for(y=165;y>0;y--) { //0.25 sec, E 659Hz
			P3=0x55;
			delay_us(60);
			P3=0xAA;
			delay_us(60);
		}
		for(y=220;y>0;y--) { //0.25 sec, A 880Hz
			P3=0x55;
			delay_us(44);
			P3=0xAA;
			delay_us(44);
		}



		for(y=110;y>0;y--) { //0.25 sec, A 440Hz
			P3=0x55;
			delay_us(91);
			P3=0xAA;
			delay_us(91);
		}
		for(y=131;y>0;y--) { //0.25 sec, C# 523Hz
			P3=0x55;
			delay_us(76);
			P3=0xAA;
			delay_us(76);
		}
		for(y=165;y>0;y--) { //0.25 sec, E 659Hz
			P3=0x55;
			delay_us(60);
			P3=0xAA;
			delay_us(60);
		}
		for(y=220;y>0;y--) { //0.25 sec, A 880Hz
			P3=0x55;
			delay_us(44);
			P3=0xAA;
			delay_us(44);
		}


		lcd_cmd(0x80);       
		lcd_data("Frequency Sweep:");
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("100Hz ~~~ 10kHz ");
		sweep();





	
	}
}
