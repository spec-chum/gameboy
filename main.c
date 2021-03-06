#include <stdio.h>
#include "timer.h"
#include "rom.h"
#include "mem.h"
#include "cpu.h"
#include "lcd.h"
#include "sdl.h"

int main(int argc, char *argv[])
{
	int r;
	const char usage[] = "Usage: %s <rom>\n";

	if(argc != 2) {
		fprintf(stderr, usage, argv[0]);
		return 0;
	}

	r = rom_load(argv[1]);
	if(!r)
		return 0;

	sdl_init();

	printf("ROM OK!\n");

	mem_init();
	printf("Mem OK!\n");

	cpu_init();
	printf("CPU OK!\n");

	r = 0;

	while(1)
	{
		int now;

		if(!cpu_cycle())
			break;

		now = cpu_get_cycles();

		while(now != r)
		{
			if(!lcd_cycle())
				goto out;
			r++;

			timer_cycle();
		}

		r = now;
	}
out:
	sdl_quit();

	return 0;
}
