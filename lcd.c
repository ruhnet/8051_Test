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
	delay_us(20);
	LCD = ((cmd>>4)&0x0F);
  	delay_us(20);
	LCD = (cmd & 0x0F)|ENABLE;          //Sending lower nibble Enable low
	LCD = (cmd & 0x0F);
  	delay_us(60);
}


void lcd_data (char *dat)          //Subroutine to send data
{ 
  	while(*dat != '\0') {
		LCD = (((*dat>>4)&0x0F)|ENABLE|REG_SL); //Sending data by making RS=1
		delay_us(20);
		LCD = (((*dat>>4)&0x0F)|REG_SL);
		delay_us(20);
		LCD = ((*dat & 0x0F)|ENABLE|REG_SL);
		delay_us(20);
		LCD = ((*dat & 0x0F)|REG_SL);
		delay_us(20);
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


void achord(unsigned char count)
{
	unsigned char y;
	unsigned char r;
	for(r=0;r<count;r++) {
		for(y=110;y>0;y--) { //0.25 sec, A 440Hz
			P3=0x55;
			delay_us(91);
			P3=0xAA;
			delay_us(91);
		}
		for(y=139;y>0;y--) { //0.25 sec, C# 554Hz
			P3=0x55;
			delay_us(72);
			P3=0xAA;
			delay_us(72);
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
	}

}



void main()
{
	//unsigned int freq;
	//unsigned int notes;
	//unsigned int cycles;
	unsigned int y;
	//unsigned int z;

    lcd_reset();
    lcd_init();
    lcd_data(" [RuhNet Labs] ");
    while(1) {
		delay_ms(1000);
   		lcd_init();       //Clear screen and return home    
    	lcd_data(" [RuhNet Labs] ");
		P3 = 0xFF; //turn all P3 outputs on
		delay_ms(1000);
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("_Intel 8051 MCU_");
		delay_ms(1000);
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
    	lcd_data("P3 rate: ~10Hz  ");
		for(y=10;y>0;y--) { //0.2 seconds of 100Hz
			P3=0x55;
			delay_ms(5);
			P3=0xAA;
			delay_ms(5);
		}
		for (y=24;y>0;y--) { 
			P3=0x55;
			delay_ms(50);
			P3=0xAA;
			delay_ms(50);
		}
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("P3 rate: ~100Hz ");
		for(y=100;y>0;y--) { //2 seconds, 100Hz
			P3=0x55;
			delay_ms(5);
			P3=0xAA;
			delay_ms(5);
		}
		lcd_cmd(0xC0);      

    	lcd_data("P3 rate: ~1000Hz");
		for(y=1000;y>0;y--) { 
			P3=0x55;
			delay_us(40);
			P3=0xAA;
			delay_us(40);
		}
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("P3 rate: ~10kHz ");
		for(y=10000;y>0;y--) { 
			P3=0x55;
			delay_us(4);
			P3=0xAA;
			delay_us(4);
		}
		lcd_cmd(0xC0);     
    	lcd_data("P3 rate: 220Hz~A");
		for(y=220;y>0;y--) { 
			P3=0x55;
			delay_us(181);
			P3=0xAA;
			delay_us(181);
		}
		lcd_cmd(0xC0);     
    	lcd_data("P3 rate: 247Hz~B");
		for(y=247;y>0;y--) {
			P3=0x55;
			delay_us(161);
			P3=0xAA;
			delay_us(161);
		}
		lcd_cmd(0xC0);    
    	lcd_data("P3 rate: 262Hz~C");
		for(y=262;y>0;y--) { 
			P3=0x55;
			delay_us(152);
			P3=0xAA;
			delay_us(152);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: 294Hz~D");
		for(y=294;y>0;y--) { 
			P3=0x55;
			delay_us(136);
			P3=0xAA;
			delay_us(135);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: 329Hz~E");
		for(y=329;y>0;y--) { 
			P3=0x55;
			delay_us(121);
			P3=0xAA;
			delay_us(121);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: 370Hz~F");
		for(y=370;y>0;y--) { 
			P3=0x55;
			delay_us(108);
			P3=0xAA;
			delay_us(107);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: 415Hz~G");
		for(y=415;y>0;y--) { 
			P3=0x55;
			delay_us(96);
			P3=0xAA;
			delay_us(96);
		}
		lcd_cmd(0xC0);      
    	lcd_data("P3 rate: 440Hz~A");
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
		for(y=4334;y>0;y--) {  //2 seconds
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
		for(y=554;y>0;y--) { //1 sec, C# 554Hz
			P3=0x55;
			delay_us(72);
			P3=0xAA;
			delay_us(72);
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

		achord(4);

		lcd_cmd(0x80);       
		lcd_data("   -The|End-    ");
		lcd_cmd(0xC0);       // Second row first column
    	lcd_data("https://ruel.io ");
		//delay_ms(1000);

	 	/*
	 	//Doesn't work for some reason:
	 	//Maintins 100Hz indefinitely... :-(
		freq=399;
		z=3985;
		for(notes=398;notes>2;notes--) {
			freq--;
			z=z-5;
			for(cycles=(z/40);cycles>0;cycles--) {
			//for(cycles=freq;cycles>0;cycles--) {
				P3=0x55;
				delay_us(freq);
				P3=0xAA;
				delay_us(freq);
			}
		}
		*/
	}
}
