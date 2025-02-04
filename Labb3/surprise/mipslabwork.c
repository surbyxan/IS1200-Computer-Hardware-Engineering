/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 


   For copyright and licensing, see file COPYING */
   //Modified 20240220 by malin andreasson

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
int prime = 1234567;

int mytime = 0x5957;

volatile int* trise = (volatile int*) 0xbf886100; //the pointers to port E input and output
volatile int* porte = (volatile int*) 0xbf886110;

int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
if (IFS(0) & 0x100)
{
 timeoutcount += 1;
IFSCLR(0) = 0x100; //interupt reset condition 
}

if (IFS(0) & 0x8000)
{
  *porte += 1;
  IFSCLR(0) = 0x8000;
}

if (timeoutcount == 10)
{
time2string( textstring, mytime );
display_string( 3, textstring );
display_update();
tick( &mytime );
timeoutcount = 0;
}


return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  
  T2CON = 0x0; 
  TMR2 = 0x0;
  PR2 = (80000000 / 256) / 10;

  IPCSET(2) = 0x1F;
  IPCSET(3) = 0x1F000; //surprise

  IECSET(0) = 0x100;
  IECSET(0) = 0x8000; //surprise

  T2CON = 0x8070; //start timer ref page 9 timersheet

  *trise &= 0xFFFFFF00; 
  TRISDSET = 0xFE0;; // Port D bits 11-5 are outputs


    enable_interrupt();

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
prime = nextprime( prime );
display_string( 0, itoaconv( prime ) );
display_update();

}
