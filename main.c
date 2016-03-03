
#include <led.h>

int main(void)
{
#ifdef __ENABLE_MMU__
	init_mmu();
#endif
	
	marquee();
	
	return 0;
}