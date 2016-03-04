
#include <register.h>
#include <interrupt.h>

void init_irq()
{
	//1、设置EINT0-5，下降沿触发，即KEY0-KEY5
	Wr(EINT0CON0, 0x40 << 0 | 0x40 << 4 | 0x40 << 8);
	
	//去除EINT0-5中断屏蔽掩码，该寄存器的默认值都是1
	Wr(EINT0MASK, Rd(EINT0MASK) & ~0x3f);
	
	//开启中断控制器EINT0-5中断
	Wr(VIC0INTENABLE, 0x3f);
	
	//打开向量中断(默认兼容2440，不打开，210默认打开)，设置CPSR打开IRQ总中断
	__asm__(
		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr r0, 0x01 << 24\n"
		"mcr p15, 0, r0, c1, c0, 0\n"
		
		"mrs r0, cpsr\n"
		"bic r0, r0, #0x80\n"
		"msr cpsr_c, r0\n"
		:
		:
	);
}

void process_irq()
{
	//1、保存环境
	__asm__(
		"sub lr, lr, #4\n"
		"ldmfd sp!, {r0-r15, lr}"
	);
	//2、中断处理
	
	//3、清除中断
	
	//4、恢复环境
}