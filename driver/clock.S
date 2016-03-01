

#define CLK_DIV0	(0x7e00f020)
#define OTHERS		(0x7e00f900)
#define MPLL_CON 	(0x7e00f010)
#define APLL_CON 	(0x7e00f00c)
#define CLK_SRC 	(0x7e00f01c)
#define DIV_VAL 	((0x0<<0)|(0x1<<9)|(0x1<<8)|(0x3<<12))
#define PLL_VAL 	((1<<31)|(266<<16)|(3<<8)|(1<<0))

.text
.global init_clock
init_clock:
	ldr r0, =CLK_DIV0
	ldr r1, =DIV_VAL
	str r1, [r0]
	
	ldr r0, =OTHERS
	ldr r1, [r0]
	bic r1,r1,#0xc0
	str r1, [r0]
	
	ldr r0, =APLL_CON
	ldr r1, =PLL_VAL
	str r1, [r0]
	
	ldr r0, =MPLL_CON
	ldr r1, =PLL_VAL
	str r1, [r0]
	
	ldr r0, =CLK_SRC
	mov r1, #0x3
	str r1, [r0]
	
	mov pc, lr