/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurred during read the IDE disk, panic. 
// 	
// Hint: use syscalls to access device registers and buffers
void
ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs)
{
	// 0x200: the size of a sector: 512 bytes.
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	int read = 0;
	int disk_addr = 0x13000000;
	int flag;
	int temp;

	if (diskno) {
		user_panic("invalid diskno : %d", diskno);
	}

	int disk_offset = disk_addr + 0x0000;
	int disk_diskno = disk_addr + 0x0010;
	int disk_opnum  = disk_addr + 0x0020;
	int disk_return = disk_addr + 0x0030;
	int disk_buffer = disk_addr + 0x4000;

	while (offset_begin + offset < offset_end) {
            // Your code here
            // error occurred, then panic.
		temp = offset_begin + offset;
		if (syscall_write_dev(&temp, disk_offset, sizeof(temp)) < 0) {
			user_panic("write offset addr error!");
		}
		if (syscall_write_dev(&diskno, disk_diskno, sizeof(diskno)) < 0) {
			user_panic("write diskno error!");
		}
		if (syscall_write_dev(&read, disk_opnum, sizeof(read)) < 0) {
			user_panic("write op error!");
		}
		if (syscall_read_dev(&flag, disk_return, sizeof(flag)) < 0 || !flag) {
			user_panic("operation error!");
		}
		if (syscall_read_dev(dst + offset, disk_buffer,BY2SECT) < 0) {
			user_panic("reading data error!");
		} 
		
		offset += BY2SECT;
	}

}


// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurred during read the IDE disk, panic.
//	
// Hint: use syscalls to access device registers and buffers
void
ide_write(u_int diskno, u_int secno, void *src, u_int nsecs)
{
        // Your code here
	// int offset_begin = ;
	// int offset_end = ;
	// int offset = ;

	// DO NOT DELETE WRITEF !!!
	writef("diskno: %d\n", diskno);

	// while ( < ) {
	    // copy data from source array to disk buffer.

            // if error occur, then panic.
	// }
	
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	int write = 1;
	int disk_addr = 0x13000000;
	int flag;
	int temp;

	if (diskno) {
		user_panic("invalid diskno : %d", diskno);
	}

	int disk_offset = disk_addr + 0x0000;
	int disk_diskno = disk_addr + 0x0010;
	int disk_opnum  = disk_addr + 0x0020;
	int disk_return = disk_addr + 0x0030;
	int disk_buffer = disk_addr + 0x4000;

	while (offset_begin + offset < offset_end) {
            // Your code here
            // error occurred, then panic.
		temp = offset_begin + offset;
		if (syscall_write_dev(&temp, disk_offset, sizeof(temp)) < 0) {
			user_panic("write offset addr error!");
		}
		if (syscall_write_dev(&diskno, disk_diskno, sizeof(diskno)) < 0) {
			user_panic("write diskno error!");
		}
		if (syscall_write_dev(src + offset, disk_buffer, BY2SECT) < 0) {
			user_panic("writing data error!");
		} 
		if (syscall_write_dev(&write, disk_opnum, sizeof(write)) < 0) {
			user_panic("write op error!");
		}
		if (syscall_read_dev(&flag, disk_return, sizeof(flag)) < 0 || !flag) {
			user_panic("operation error!");
		}
		
		offset += BY2SECT;
	}
}

