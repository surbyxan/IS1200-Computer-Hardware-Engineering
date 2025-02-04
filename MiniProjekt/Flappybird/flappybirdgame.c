/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 


   For copyright and licensing, see file COPYING */
  

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"  /* Declarations for game */


/*code from labs*/



char textstring[] = "text, more text, and even more text!";


/* Interrupt Service Routine */
void user_isr( void )
{

}

/*modified code from labs*/
void IOinit(void){
volatile int* trise = (volatile int*) 0xbf886100; 
volatile int* porte = (volatile int*) 0xbf886110;
*trise &= 0xFFFFFF00; //everything but the least 8 significant bits
TRISDSET = 0xFE0; // Port D bits 11-5 are outputs
 }

/*modified code from labs*/
void timerinit( void )
{
  
  T2CON = 0x0; 
  TMR2 = 0x0;
  PR2 = (80000000 / 256) / 10;

  IPCSET(2) = 0x1f;
  IECSET(0) = 0x100;

  T2CON = 0x8070; //start timer ref page 9 timersheet
 
  enable_interrupt();

  return;
}
