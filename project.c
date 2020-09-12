/*****************************************************
This program was produced by the
CodeWizardAVR V1.24.4 Standard
Automatic Program Generator
© Copyright 1998-2004 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com
e-mail:office@hpinfotech.com

Project : 
Version : 
Date    : 2007/01/25
Author  : applecoinc                      
Company : avr                             
Comments: 


Chip type           : ATmega16
Program type        : Application
Clock frequency     : 8.000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 256
*****************************************************/

#include <mega16.h>
#include <delay.h>
#include <stdio.h>
#include <lcd.h> 

#asm
   .equ __lcd_port=0x1B ;PORTA
#endasm

unsigned long int timer0_ov;
unsigned long int in_freq;
unsigned char lcd_buff[20];

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
timer0_ov ++;
}

void main(void)
{

// Timer/Counter 0 initialization
// Clock source: T0 pin Falling Edge
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCNT0=0x00;
OCR0=0x00;
TCCR0=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x01;

// LCD module initialization
lcd_init(16);

while (1)
{
      TCCR0=0x06;     // Start Timer T0 pin Falling Edge
      #asm("sei")     // Global enable interrupts
      delay_ms(1000);
      #asm("cli");    // Global disable interrupts
      in_freq = timer0_ov * 256 + TCNT0;
      sprintf(lcd_buff,"FREQUENCY=%dHz",in_freq);
      lcd_clear();
      lcd_puts(lcd_buff); 
      lcd_gotoxy(0,1); 
      lcd_putsf("  EG PROJECTS");
      TCCR0=0x00;    //Stopt Timer0
      timer0_ov=0;   //Prepare for next count
      TCNT0=0;       //Clear Timer0
      };
}
