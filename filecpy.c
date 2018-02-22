// README:
// Filecpy is a program designed to copy the content of one file to another
// Call file using "./filecpy", then pass in source and destination values
// EX: "./filecpy source.txt dest.txt"
// Author: Gabriel Hunt
// Date Last Modified: 2/5/2018 


#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
int main(int argc, char *argv[])
{
	// Check for valid number of agruments 
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <source> <dest> \n", argv[0]);
		return -1;
	}

	// Create file discriptor for source file
	int fd1 = open(argv[1], O_RDONLY, S_IRUSR);

	// Error check
	if (fd1 < 0)
	{
		fprintf(stderr, "Error opening file %s \n", argv[1],
			strerror(errno));
		return -1;
	}

	// Create file discriptor for destination file
	int fd2 = open(argv[2], O_WRONLY, S_IWUSR);


	// Error check
	if (fd2 < 0)
	{
		fprintf(stderr, "Error opening file %s \n", argv[2],
			strerror(errno));
		return -1;
	}
	
	// Initialize buffer and status variables to non-zero values
	char buffer[512];
	int readStat = 8;
	int writeStat = 8;
	int nbyte = 512;

	// Read data from source file into buffer. readstat holds return value
	readStat = read(fd1, buffer, nbyte);

	// Loop through file as long as there is data to read
	while (readStat > 0)
	{
		// Error check (reading source file)
		if (readStat < 0)
		{
			fprintf(stderr, "Error reading file %s \n", argv[1]);
			printf(strerror(errno));
			return -1;
		}

		// Write data to destination file. writestat holds return value
		writeStat = write(fd2, buffer, sizeof(char)*strlen(buffer));

		// Error check (writting dest file)
		if (writeStat < 0)
		{
			fprintf(stderr, "Error writting to file %s \n",
				 argv[2]);
			printf( strerror(errno));
			return -1;
		}

		// Read more data.
		// Updates readstat value before loop condition is re-evluated
		readStat = read(fd1, buffer, nbyte);
	}

	// Close files
	close(fd1);
	close (fd2);

	// Terminate successfully
	return 0;
}

// STRACE RESULTS:
//
// [hunt043@empress cs433]$ strace ./filecpy source.txt dest.txt
// execve("./filecpy", ["./filecpy", "source.txt", "dest.txt"], [/* 29 vars */]) = 0
// brk(NULL)                               = 0x116e000
// mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fc27f402000
// access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
// open("/opt/rh/rh-ruby24/root/usr/local/lib64/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-ruby24/root/usr/local/lib64/tls/x86_64", 0x7ffcf597f000) = -1 ENOENT (No such file or directory)
// open("/opt/rh/rh-ruby24/root/usr/local/lib64/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-ruby24/root/usr/local/lib64/tls", 0x7ffcf597f000) = -1 ENOENT (No such file or directory)
// open("/opt/rh/rh-ruby24/root/usr/local/lib64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-ruby24/root/usr/local/lib64/x86_64", 0x7ffcf597f000) = -1 ENOENT (No such file or directory)
// open("/opt/rh/rh-ruby24/root/usr/local/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-ruby24/root/usr/local/lib64", {st_mode=S_IFDIR|0755, st_size=6, ...}) = 0
// open("/opt/rh/rh-ruby24/root/usr/lib64/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-ruby24/root/usr/lib64/tls/x86_64", 0x7ffcf597f000) = -1 ENOENT (No such file or directory)
// open("/opt/rh/rh-ruby24/root/usr/lib64/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-ruby24/root/usr/lib64/tls", {st_mode=S_IFDIR|0555, st_size=6, ...}) = 0
// open("/opt/rh/rh-ruby24/root/usr/lib64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-ruby24/root/usr/lib64/x86_64", 0x7ffcf597f000) = -1 ENOENT (No such file or directory)
// open("/opt/rh/rh-ruby24/root/usr/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-ruby24/root/usr/lib64", {st_mode=S_IFDIR|0555, st_size=4096, ...}) = 0
// open("/opt/rh/rh-python36/root/usr/lib64/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-python36/root/usr/lib64/tls/x86_64", 0x7ffcf597f000) = -1 ENOENT (No such file or directory)
// open("/opt/rh/rh-python36/root/usr/lib64/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-python36/root/usr/lib64/tls", {st_mode=S_IFDIR|0555, st_size=6, ...}) = 0
// open("/opt/rh/rh-python36/root/usr/lib64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-python36/root/usr/lib64/x86_64", 0x7ffcf597f000) = -1 ENOENT (No such file or directory)
// open("/opt/rh/rh-python36/root/usr/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
// stat("/opt/rh/rh-python36/root/usr/lib64", {st_mode=S_IFDIR|0555, st_size=4096, ...}) = 0
// open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
// fstat(3, {st_mode=S_IFREG|0644, st_size=44700, ...}) = 0
// mmap(NULL, 44700, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fc27f3e9000
// close(3)                                = 0
// open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
// read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\20\35\2\0\0\0\0\0"..., 832) = 832
// fstat(3, {st_mode=S_IFREG|0755, st_size=2127336, ...}) = 0
// mmap(NULL, 3940800, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fc27ee11000
// mprotect(0x7fc27efc9000, 2097152, PROT_NONE) = 0
// mmap(0x7fc27f1c9000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b8000) = 0x7fc27f1c9000
// mmap(0x7fc27f1cf000, 16832, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fc27f1cf000
// close(3)                                = 0
// mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fc27f401000
// mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fc27f3ff000
// arch_prctl(ARCH_SET_FS, 0x7fc27f3ff740) = 0
// mprotect(0x7fc27f1c9000, 16384, PROT_READ) = 0
// mprotect(0x600000, 4096, PROT_READ)     = 0
// mprotect(0x7fc27f3fa000, 4096, PROT_READ) = 0
// munmap(0x7fc27f3e9000, 44700)           = 0
// open("source.txt", O_RDONLY)            = 3
// open("dest.txt", O_WRONLY)              = 4
// read(3, "This is \na test\nof the \ncpy func"..., 512) = 37
// write(4, "This is \na test\nof the \ncpy func"..., 48) = 48
// read(3, "", 512)                        = 0
// close(3)                                = 0
// close(4)                                = 0
// exit_group(0)                           = ?
// +++ exited with 0 +++
// [hunt043@empress cs433]$
//
