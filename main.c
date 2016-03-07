
#include <led.h>

#define IRQ_TEST
//#define ENABLE_MMU

int main(void)
{
#ifdef ENABLE_MMU
	init_mmu();
#endif
	
	//marquee();
	
#ifdef IRQ_TEST	
	init_button();
	led_init();
	init_irq();
#endif

	while (1);

	return 0;
}