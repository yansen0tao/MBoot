
#ifndef __REGISTER_H__
#define __REGISTER_H__

#define WTCON			(0x7E004000)

#define GPMCON			(0x7F008820)
#define GPMDAT			(0x7F008824)

#define GPNCON			(0x7F008830)
#define GPNDAT			(0x7F008834)

#define EINT0CON0		(0x7F008900)
#define EINT0MASK		(0x7F008920)

#define VIC0INTENABLE	(0x71200010)
#define VIC1INTENABLE	(0x71300010)

#define Wr(addr, data) 	(*((volatile unsigned long *)(addr))=(data))
#define Rd(addr) 		(*((volatile unsigned long *)(addr)))

#endif