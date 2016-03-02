

#define WTCON		(0x7E004000)
#define GPMCON		(0x7F008820)
#define GPMDAT		(0x7F008824)
#define DDR_BASE	(0x50000000)

#define VGPMCON		(0xa0008820)
#define VGPMDAT		(0xa0008824)

#define Wr(addr, data) 	(*((volatile unsigned long *)(addr))=(data))
#define Rd(addr) 		(*((volatile unsigned long *)(addr)))