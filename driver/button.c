
#include <register.h>

#define MASK_BITS	(~(0x03 << 2*0 | 0x03 << 2*1 | 0x03 << 2*2 | 0x03 << 2*3 | 0x03 << 2*4 | 0x03 << 2*5))
#define INT_ENABLE	(0x02 << 2*0 | 0x02 << 2*1 | 0x02 << 2*2 | 0x02 << 2*3 | 0x02 << 2*4 | 0x02 << 2*5)

void init_button(void)
{
//把GPIO_N的引脚配置为外部中断功能
	Wr(GPNCON, Rd(GPNCON) & MASK_BITS | INT_ENABLE);
}

