OUTPUT_ARCH(mips)
/*
Set the architecture to mips.
*/
ENTRY(_start)
/*
Set the ENTRY point of the program to _start.
*/
SECTIONS
{

/*
  Exercise 1.3. Please complete this part.
  To do:
  fill in the correct address of the key section
  such as text data bss.
  tips: maybe you can find the answer in include/ .
	look for the memory map.
*/
. = 0x00000000;
.text : { *(.text) };
. = 0x00000bd0;
.data : { *(.data) };
. = 0x00008bd0;
.bss : { *(.bss) };

end = . ;
}
