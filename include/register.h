

#define WTCON	(0x7E004000)

#define GPMCON	(0x7F008820)
#define GPMDAT	(0x7F008824)

#define Wr(addr, data) 	(*((volatile unsigned long *)(addr))=(data))
#define Rd(addr) 		(*((volatile unsigned long *)(addr)))