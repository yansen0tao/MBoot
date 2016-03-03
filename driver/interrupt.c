
#include <register.h>
#include <interrupt.h>

void init_irq()
{
	//EINT0-5 Falling edge triggered
	Wr(EINT0CON0, 0b01 | 0b01 << 4 | 0b01 << 8);
	
	//去除中断屏蔽掩码
	Wr(EINT0MASK, Rd(EINT0MASK) & ~0x3f);
	
	//开启中断
	Wr(VIC0INTENABLE, 0x3f);
	
	//CPSR打开总中断
	__asm__(
		"mrs r0, cpsr\n"
		"bic r0, r0, #0x80\n"
		"msr cpsr_c, r0\n"
		:
		:
	);
}