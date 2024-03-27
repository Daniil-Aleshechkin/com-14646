#include "util.h"

void delay(volatile int x) {
	volatile int i;
	while (1) {
		i++;
		
		if (i > x) {return;}
	}
}
