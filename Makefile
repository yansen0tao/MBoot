
include makefile_configure

SSRCS = start.S
SRCS = main.c
#LIB_SRCS = lib1.c
LIB_SRCS = driver/mem.S
LIB_SRCS += driver/clock.S
LIB_SRCS += driver/led.c
#LIB_SRCS += driver/mmu.c
#LIB_SRCS += driver/led.c
#LIB_SRCS += driver/button.c

SOBJS	= $(SSRCS:%.S=%.o$(SUFFIX))
OBJS	= $(SRCS:%.c=%.o$(SUFFIX))
LIB_OBJS = $(LIB_SRCS:%.S=%.o$(SUFFIX)) $(LIB_SRCS:%.c=%.o$(SUFFIX))

entry:clean boot

lib.a: $(LIB_OBJS)
	$(AR) -q $@ $^

boot.elf:$(SOBJS) $(OBJS) lib.a
	$(LD) -Tboot.lds $(LD_FLAGS) -e __start -o $@ $^

boot.asm:
	$(DUMP) $(DUMP_FLAGS) boot.elf > $@
	
boot.map:
	$(READELF) -a boot.elf > $@

boot:clean boot.elf boot.asm boot.map
	@echo "start convert..."
	$(OBJCOPY) -O binary boot.elf boot.bin
	
#.c.o <==> %.o:%.c
.c.o:
	$(CC) $(CC_FLAGS) $< -o $@
#.S.o <==> %.o:%.S
.S.o:
	$(CC) $(CC_FLAGS) $< -o $@

.PHONY:
clean:
	rm -rf *.bak *.elf *.bin *.asm *.a *.map
	rm -rf driver/*.o *.o


