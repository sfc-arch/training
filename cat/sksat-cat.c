#include <unistd.h>
#include <fcntl.h>

// my stdlib

// system call

#define TO_STRING(str)	#str
#define STR(val) TO_STRING(val)

#define NUM_READ	0
#define NUM_WRITE	1
#define NUM_OPEN	2
#define NUM_CLOSE	3
#define NUM_EXIT	60
#define NUM_OPENAT	257

#define AT_FDCWD	-100

ssize_t sys_read(unsigned int fd, char *buf, size_t count);
void sys_write(unsigned int fd, const char *buf, size_t count);
int  sys_open(const char *fname, int flags, int mode);
int  sys_close(unsigned int fd);
void sys_exit(int status);

// file descriptor
#define stdin	0
#define stdout	1
#define stderr	2

// funcs
void* memset(void *buf, int ch, size_t n);
size_t strlen(const char *str);
void fputs(int fd, const char *str);
void puts(const char *str);


#define BUF_SIZE	256

void cat_loop(int fd);
void error(const char *msg);

int main(int argc, char **argv){
	char buf[BUF_SIZE];

	if(argc == 1){
		cat_loop(stdin);
		return 0;
	}

	for(int n=1;n<argc;n++){
		int fd = sys_open(argv[n], O_RDONLY, 0);
		if(fd == -1)
			error("cannot open file.\n");
		cat_loop(fd);
		sys_close(fd);
	}

	sys_exit(0);
}

void cat_loop(int fd){
	char buf[BUF_SIZE];

	for(;;){
		memset(buf, '\0', BUF_SIZE);
		if(sys_read(fd, buf, BUF_SIZE) == 0)
			break;
		puts(buf);
	}
}

void error(const char *msg){
	puts(msg);
	sys_exit(-1);
}

// library funcs impl

void* memset(void *buf, int ch, size_t n){
	int i;
	for(i=0;i<n;i++){
		((char*)buf)[i] = ch;
	}
	return buf;
}

size_t strlen(const char *str){
	size_t len;
	for(len=0;;len++){
		if(str[len] == '\0')
			break;
	}
	return len;
}

void fputs(int fd, const char *str){
	sys_write(fd, str, strlen(str));
	return;
}

void puts(const char *str){
	fputs(stdout, str);
}

// system call wrapper impl

ssize_t sys_read(unsigned int fd, char *buf, size_t count){
	asm volatile (
			"mov $" STR(NUM_READ) ", %rax;"
			"syscall");
}

void sys_write(unsigned int fd, const char *buf, size_t count){
	asm volatile (
			"mov $" STR(NUM_WRITE) ", %rax;"
			"syscall");
}

int sys_open(const char *fname, int flags, int mode){
	asm volatile (
			"mov $" STR(NUM_OPEN) ", %rax;"
			"syscall");
}

int  sys_close(unsigned int fd){
	asm volatile (
			"mov $" STR(NUM_CLOSE) ", %rax;"
			"syscall");
}

void sys_exit(int status){
	asm volatile (
			"mov $" STR(NUM_EXIT) ", %rax;"
			"syscall");
}
