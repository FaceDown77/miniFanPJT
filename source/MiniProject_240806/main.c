#define F_CPU 16000000UL
#include <avr/io.h>
#include "ap/apMain.h"


int main(void)
{
    apMain_init();
	
    while (1) 
    {
		apMain_run();
    }
}

