
/*
	代码运行的平台，一般没有用
*/
OUTPUT_ARCH(ARM)

/*
	指明程序的入口函数，不过也可以在
	使用该链接器脚本的时候使用参数-e 指出
*/
ENTRY(__start)

SECTIONS{
/*程序起始链接地址*/
	. = 0x50008000;
/*
	由于arm读取指令是4字节对齐的，因此这里使代码4字节对齐
	提高访问效率
*/
	. = ALIGN(4);
	.start : {start.o(.text)}
	.text : {*(.text)}
	
	. = ALIGN(4);
	.data : {*(.data)}
	
	. = ALIGN(4);
	BSS_BEGIN = .;
	.bss : {*(.bss)}
	BSS_END = .;
}
