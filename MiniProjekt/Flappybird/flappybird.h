/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);

uint8_t spi_send_recv(uint8_t data);





/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];

/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string( char *, int );
char * itoaconv( int num );
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);


/*The code below is written by Malin Andreasson*/
//game initilazing methods
void display_gameupdate(void);
void IOinit();
void timerinit();
extern uint8_t displaypixels[32][128];
extern uint8_t pipes[32][136];
void clearDisplay(void);
//knapp och switch
int buttons();
int swiches();
void clearpipes();
void clearpip();
//game-related methods
//insert (spelare och hinder)
void insertplayer(int y);
void insertobstacl1(int x, int off);

// game logic
int collision(int y);
void gameover(int *y, int *x);
//void score(int x);


// spelare 
extern uint8_t const player[4][4];




