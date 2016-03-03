
#include <register.h>

#define GPN0_MASK	(0b11 << 2*0)
#define GPN1_MASK	(0b11 << 2*1)
#define GPN2_MASK	(0b11 << 2*2)
#define GPN3_MASK	(0b11 << 2*3)
#define GPN4_MASK	(0b11 << 2*4)
#define GPN5_MASK	(0b11 << 2*5)

#define GPN0_INT	(0b10 << 2*0)
#define GPN1_INT	(0b10 << 2*1)
#define GPN2_INT	(0b10 << 2*2)
#define GPN3_INT	(0b10 << 2*3)
#define GPN4_INT	(0b10 << 2*4)
#define GPN5_INT	(0b10 << 2*5)

void init_button()
{
//set button mode is interrupt
	unsigned long value = Rd(GPNCON);

	value &= ~(GPN0_MASK | GPN1_MASK | GPN2_MASK | GPN3_MASK | GPN4_MASK | GPN5_MASK);
	value |= (GPN0_INT | GPN1_INT | GPN2_INT | GPN3_INT | GPN4_INT | GPN5_INT);
	Wr(GPNCON, value);
}

