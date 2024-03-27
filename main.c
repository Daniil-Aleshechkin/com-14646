#include "gpio.h"
#include "stdint.h"
#include "stm32f10x.h"
#include "com_14646_matrix.h"
#include "tim2.h"

int main() {
	
	//init_gpio();
	displayInit();
	
	
	int count = 0;
	
	int enable = 0;
	
	uint8_t mult = 0;
	//multiplex(mult);
	
	clearBuffer();
	struct pixel red = (struct pixel){true, false, false};
	struct pixel green = (struct pixel){false, true, false};
	struct pixel blue = (struct pixel){false, false, true};
	
	
	int offset = 2;
	
	
	//bufferPixel(red, 0, 1);
	
	while (1) {
/*		struct rgb_data pins;
		int i;
		

		mult++;
		multiplex(mult);
		
		for (i = 0; i < 32; i++) {
			pins.r1 = i % 2 == enable;
			pins.g1 = i % 2 != enable;
			pins.b1 = i % 2 == enable;
			
			pins.r2 = i % 4 == enable;
			pins.g2 = i % 8 == enable;
			pins.b2 = i % 2 == enable;
			
			output_rgb_data(pins);
			flip_clock();
		}
		
		flip_latch();
		
		count++; */

		
		if ((count % 4) == 0) {
			offset++;
			

			
			//offset = offset % 3;
			clearBuffer();
			
		}
		
		for (int x = 0; x < 32; x++) {
			for (int y = 0; y < 32; y++) {
				struct pixel color;
				int val = ((y+x+offset) % 3);
				
				switch (val) {
					case 0:
						bufferPixel(red, x, y);
						break;
					case 1:
						bufferPixel(blue, x, y);
						break;
					case 2:
						bufferPixel(green, x, y);
						break;
				}
			}
		}
		
		//bufferPixel(red, 1,1);
		
		//offset++;
		
		count++;
		__disable_irq();
		refreshDisplay();
		__enable_irq();
		
		for (int i = 0 ; i < 50; i++) {
			start_tim2();
		
			while (!isTim2Updated()) {}
		
			stop_tim2();
		
		}
	}
}