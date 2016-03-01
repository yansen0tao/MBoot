

#include <register.h>

void temp_delay(unsigned long times)
{
	unsigned long long i = times;
	
	for (i = 0; i < times; i++)	
		for (i = 0; i < 500000; i++)
			__asm__("nop");
}

void led_init()
{
	Wr(GPMCON, 0x1111);
	Wr(GPMDAT, 0b1111);
}

void led_on(int n)
{
	Wr(GPMDAT, ~(0x01 << n) & 0xF);
	temp_delay(1);
	Wr(GPMDAT, 0xF);
}

void marquee(void) 
{
	int i = 0;
	
	led_init();
	
	while (1)
	{
		for (i = 0; i < 2; i++)
			led_on(i);
	}
}