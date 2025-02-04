/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "flappybird.h" /* Declatations for these labs */

/* Declare a helper function which is local to this file */
static void num32asc(char *s, int);

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* code from labs */
void quicksleep(int cyc)
{
	int i;
	for (i = cyc; i > 0; i--)
		;
}

/* code from labs */
void display_debug(volatile int *const addr)
{
	display_string(1, "Addr");
	display_string(2, "Data");
	num32asc(&textbuffer[1][6], (int)addr);
	num32asc(&textbuffer[2][6], *addr);
	display_update();
}

/* code from labs */
uint8_t spi_send_recv(uint8_t data)
{
	while (!(SPI2STAT & 0x08))
		;
	SPI2BUF = data;
	while (!(SPI2STAT & 1))
		;
	return SPI2BUF;
}

/* code from labs */
void display_init(void)
{
	DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);

	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0xAF);
}

/* code from labs */
void display_string(int line, char *s)
{
	int i;
	if (line < 0 || line >= 4)
		return;
	if (!s)
		return;

	for (i = 0; i < 16; i++)
		if (*s)
		{
			textbuffer[line][i] = *s;
			s++;
		}
		else
			textbuffer[line][i] = ' ';
}

/* code from labs */
void display_image(int x, const uint8_t *data)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));

		DISPLAY_CHANGE_TO_DATA_MODE;

		for (j = 0; j < 32; j++)
			spi_send_recv(~data[i * 32 + j]);
	}
}

/* code from labs */
void display_update(void)
{
	int i, j, k;
	int c;
	for (i = 0; i < 4; i++)
	{
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x0);
		spi_send_recv(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for (j = 0; j < 16; j++)
		{
			c = textbuffer[i][j];
			if (c & 0x80)
				continue;

			for (k = 0; k < 8; k++)
				spi_send_recv(font[c * 8 + k]);
		}
	}
}

/*code written by Malin Andreasson*/
//updates display for the game
void display_gameupdate(){
	int i, j, k, m , n;
	int display;
	for (i = 0; i < 4; i++)
	{
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x0);
		spi_send_recv(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for ( m = 0; m < 128; m++) {
			for ( n = 0; n < 32; n++)
			{
				displaypixels[n][m] |= pipes[n][m];
			}		
		}
		for (j = 0; j < 128; j++)
		{
			display = displaypixels[i * 8][j];
			for (k = 0; k < 8; k++)
			{
				display |= displaypixels[i * 8 + k][j] << k;
			}
			spi_send_recv(display);
		}
	}
}

/*code written by Malin Andreasson*/
void clearDisplay(){
	int i, j;
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 128; j++)
		{
			displaypixels[i][j] = 0;
		}
	}
}
void clearpip(){
	int i, j;
	for ( i = 0; i <= 136; i++)
	{
		for ( j = 0; j < 32; j++){
			pipes[j][i] = 0;
		}
	}
}		

void clearpipes(){
	int i, j;
	for ( i = 0; i <= 136; i++)
	{
		for ( j = 0; j < 32; j++)
		{
		if (i == 136)
		{
			pipes[j][i] = 0;
		}
		else pipes[j][i] = pipes[j][i + 1];
		}
	
	}

}

/*code written by Malin Andreasson*/
void insertplayer(int y){
	int i, j; //j x vädre, i y värde
	for (i = y; i < y + 4; i++)
	{
		for (j = 38; j < 42; j++)
		{
			displaypixels[i][j] = player[i - y][j - 38];
		}
		
	}
}

/*code written by Malin Andreasson*/
void insertobstacl1(int x, int off){
	int i, j;
	for (i = 0; i < 32; i++) {
		for (j = x; j < (x + 8); j++)
		{
			if ((i < 10 + off) || (i > 20 + off)) {
				pipes[i][j] = 1;
			}
			else pipes[i][j] = 0;				
			
		}
	}
	
}

/*code written by Malin Andreasson*/
void gameover(int * y, int * tick){
	clearDisplay();
	clearpip();
	*y = 15;
	*tick = 0;
	PORTE = 0;
	delay(1500);
}

/*code written by Malin Andreasson*/
int collision(int y){
	int i, j;
	for ( i = y; i < y + 4; i++)
	{
		for (j = 38; j < 42; j++)
		{
			if (player[i][j] & pipes[i][j]){
				return 1;
			}
		}		
	}
	return 0;
	
}
//dosent work
/*void score(int x){
	if (x % 40 == 0)
	{
	PORTE += 1;
	}
}*/

/*code written by Malin Andreasson*/
//knapp, ska retunera ett värde beroende på btn4
int buttons(){
   static int btnpress = 0;
   int button = getbtns();

   if (((button & 0b100) && !btnpress))
   {
      btnpress = 1;
      return 1;
   }
   else if (!(button & 0b100) && btnpress)
   {
	btnpress = 0;
   }
      return 0;
} 

/*code written by Malin Andreasson*/
//switch, bara switch 1 ska användas
int swiches(){
	int switchs = getsw();

	if ((switchs == 1))
	{
		return 1;
	}
	return 0;
	}

/* Code from labs */
static void num32asc(char *s, int n)
{
	int i;
	for (i = 28; i >= 0; i -= 4)
		*s++ = "0123456789ABCDEF"[(n >> i) & 15];
}

#define ITOA_BUFSIZ (24)
char *itoaconv(int num)
{
	register int i, sign;
	static char itoa_buffer[ITOA_BUFSIZ];
	static const char maxneg[] = "-2147483648";

	itoa_buffer[ITOA_BUFSIZ - 1] = 0; /* Insert the end-of-string marker. */
	sign = num;						  /* Save sign. */
	if (num < 0 && num - 1 > 0)		  /* Check for most negative integer */
	{
		for (i = 0; i < sizeof(maxneg); i += 1)
			itoa_buffer[i + 1] = maxneg[i];
		i = 0;
	}
	else
	{
		if (num < 0)
			num = -num;		 /* Make number positive. */
		i = ITOA_BUFSIZ - 2; /* Location for first ASCII digit. */
		do
		{
			itoa_buffer[i] = num % 10 + '0'; /* Insert next digit. */
			num = num / 10;					 /* Remove digit from number. */
			i -= 1;							 /* Move index to next empty position. */
		} while (num > 0);
		if (sign < 0)
		{
			itoa_buffer[i] = '-';
			i -= 1;
		}
	}
	/* Since the loop always sets the index i to the next empty position,
	 * we must add 1 in order to return a pointer to the first occupied position. */
	return (&itoa_buffer[i + 1]);
}
