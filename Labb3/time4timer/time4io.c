//time4io.c
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

//checks the value of the swiches and shifting them to 4lsb
int getsw( void ){
	int sw = (PORTD & 0xF00) >> 8;
	return sw;
}
//checks tHe value of the btns and shifts them to 4lsb
int getbtns(void){
	int btns = (PORTD & 0xE0) >> 5;
	return btns;
}