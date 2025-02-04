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

int mytime = 0x5957;
 
volatile int* trise = (volatile int*) 0xbf886100; //the pointers to port E input and output
volatile int* porte = (volatile int*) 0xbf886110;

int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  //initalization of timer 2, refence to timer sheet
  T2CON = 0x0; //reseting timercontrol and timer register
  TMR2 = 0x0;
  PR2 = (80000000 / 256) / 10; //clk period div by prescale value. 80 miljoner/256 är 1 sek för timer2

  T2CON = 0x8070; //start timer ref page 9 timersheet

  *trise &= 0xFFFFFF00; //everything but the least 8 significant bits
  TRISDSET = 0xFE0;; // Port D bits 11-5 are outputs
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  int button = getbtns();
  int switches = getsw(); 

//changeing the mytime value, accordig to switches and btns.
  if((button & 0b001) == 1){
    mytime &= 0xff0f; 
    mytime |= (switches << 4);
  }

  if((button & 0b010) == 2){
    mytime &= 0xf0ff;
    mytime |= (switches << 8); 
  }

  if((button & 0b100) == 4){
    mytime &= 0x0fff;
    mytime |= (switches << 12); 
  }

  if (IFS(0) & 0x100)
  {
    timeoutcount += 1;
    IFSCLR(0) = 0x100;
  }
  

  if (timeoutcount == 10)
  {
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  *porte += 1;  
  
  timeoutcount = 0;
  }

  display_image(96, icon);
  //delay( 1000 );


}
