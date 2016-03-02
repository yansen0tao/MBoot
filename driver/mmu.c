
#include <register.h>

#define TTB_BASE		(DDR_BASE)
#define GPIO_VADDR		(0xa0008000)
#define GPIO_PADDR		(0x7f008000)

#define DDR_VADDR		(DDR_BASE)
#define DDR_PADDR		(DDR_BASE)

#define TTB_TYPE		(0b10 << 0)//section 
#define BUFFER_ENABLE	(0b1 << 2)
#define CAHCE_ENABLE	(0b1 << 3)
#define SPECIAL			(0b1 << 4)
#define DOMAIN			(0b11 << 5)
#define AP				(0b11 << 10)

#define GPIO_TTB_ITEM	(AP | DOMAIN | SPECIAL | TTB_TYPE)
#define DDR_TTB_ITEM	(AP | DOMAIN | SPECIAL | CAHCE_ENABLE | BUFFER_ENABLE | TTB_TYPE)

//1������һ��ҳ��
void create_TTB(void)
{
	unsigned long ddr_vaddr = DDR_VADDR;
	unsigned long ddr_paddr = ddr_vaddr;
	
	//map GPIO vaddr->paddr
	*(volatile unsigned long*)(TTB_BASE + (GPIO_VADDR >> 20)) = (GPIO_PADDR & 0xfff00000) | GPIO_TTB_ITEM;
	
	while (ddr_paddr < 0x54000000)
	{
		*(volatile unsigned long*)(TTB_BASE + (ddr_vaddr >> 20)) = (ddr_paddr & 0xfff00000) | DDR_TTB_ITEM;
		ddr_vaddr += 0x100000;
		ddr_paddr += 0x100000;
	}
}

//2��ʹMMU��ȡ����1������һ��ҳ��Ļ���ַ
void config_mmu(void)
{
	__asm__(
		//����ַд��cp15��c2�Ĵ���
		"ldr r0, =0x50000000\n"
		"mcr p15, 0, r0, c2, c0, 0\n"
		//domain access control
		"mvn r0, #0x0\n"
		"mcr p15, 0, r0, c3, c0, 0\n"
		:
		:
	);
}

//ʹ��MMU
void init_mmu()
{
	create_TTB();
	
	config_mmu();
	
	__asm__(
		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr r0, r0, #0x1\n"
		"mcr p15, 0, r0, c1, c0, 0\n"
		:
		:
	);
}