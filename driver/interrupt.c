
#include <register.h>
#include <interrupt.h>

void process_irq()
{
	int i = 0, ret = 0;
	
	//1、保存环境，arm三级流水线机制导致有一条译码的指令
	//没有机会执行，因此调整链接地址，使得该译码指令可以被执行
	__asm__(
		"sub lr, lr, #4\n"
		"stmfd sp!, {r0-r12, lr}\n"
		:
		:
	);
	//2、中断处理
	led_on(0);
	
	//3、清除中断
	Wr(EINT0PEND, ~0x0);
	Wr(VIC0ADDRESS, 0x0);
	//4、恢复环境,"^"的意思是指令完成后，把SPSR拷贝到CPSR
	__asm__(
		"ldmfd sp!, {r0-r12, pc}^ \n"
		:
		:
	);
}

void init_irq()
{
	//1、设置EINT0-5，下降沿触发，即KEY0-KEY5
	Wr(EINT0CON0, 0x20 << 0 | 0x20 << 4 | 0x20 << 8);
	
	//去除EINT0-5中断屏蔽掩码，该寄存器的默认值都是1
	Wr(EINT0MASK, Rd(EINT0MASK) & ~0x3f);
	
	//开启中断控制器EINT0-5中断
	Wr(VIC0INTENABLE, 0x3f);
	
	//注册中断处理函数
	Wr(VIC0VECTADDR + 0, (int)process_irq);
	Wr(VIC0VECTADDR + 4, (int)process_irq);	
		
	//打开向量中断(默认兼容2440，是默认不打开的，210默认打开)，设置CPSR打开IRQ总中断
	__asm__(
		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr r0, r0, #(0x01 << 24)\n"
		"mcr p15, 0, r0, c1, c0, 0\n"
		
		"mrs r0, cpsr\n"
		"bic r0, r0, #0x80\n"
		"msr cpsr_c, r0\n"
		:
		:
	);
}

