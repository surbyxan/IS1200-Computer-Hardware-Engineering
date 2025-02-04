//time4io.c
#include <stdint.h>
#include <pic32mx.h>
#include "flappybird.h"
void *stdin, *stdout, *stderr;

/* code from labs*/
int getsw(void){
	int sw = (PORTD & 0xF00) >> 8;
	return sw;
}
//checks tHe value of the btns and shifts them to 4lsb
int getbtns(void){
	int btns = (PORTD & 0xE0) >> 5;
	return btns;
}