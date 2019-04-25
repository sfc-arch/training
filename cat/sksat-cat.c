// compile: $(CC) sksat-cat.c -o sksat-cat -nostdlib -fno-builtin -fno-stack-protector

// std types
typedef _Bool			bool;
#define	true			1
#define false			0
// 64bit
#define __SIZE_TYPE__		long unsigned int
typedef long			__kernel_ssize_t;

typedef __SIZE_TYPE__		size_t;
typedef __kernel_ssize_t	ssize_t;

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

// file
#define stdin	0
#define stdout	1
#define stderr	2

#define O_RDONLY	0x0000
#define O_WRONLY	0x0001
#define O_RDWR		0x0002
#define O_ACCMODE	0x0003

// funcs
void* memset(void *buf, int ch, size_t n);
size_t strlen(const char *str);
int strcmp(const char *s1, const char *s2);
void fputs(int fd, const char *str);
void puts(const char *str);


#define BUF_SIZE	256

char output_opt;	// do not initialize here!!!
#define OPT_END		0b00000001
#define OPT_NUMBER	0b00000010
#define OPT_TAB		0b00000100

int main(int argc, char **argv);
size_t check_cmdline(const int argc, char **argv);
void check_option(const char *opt);
void cat_loop(int fd);
void print_with_opt(const char *buf);
void error(const char *msg);

// entry point
asm(
		".global _start;"
		"_start:\n"
		"	xorl %ebp, %ebp;"
		"	movq 0(%rsp), %rdi;"
		"	lea 8(%rsp), %rsi;"
		"	call main");

int main(int argc, char **argv){
	char buf[BUF_SIZE];

	if(check_cmdline(argc, argv) == 0){
		cat_loop(stdin);
		sys_exit(0);
	}

	for(int n=1;n<argc;n++){
		int fd;
		size_t len = strlen(argv[n]);

		if(len == 0) continue;

		if(argv[n][0] == '-' && len  == 1)
			fd = stdin;
		else
			fd = sys_open(argv[n], O_RDONLY, 0);
		if(fd < 0)
			error("cannot open file.\n");
		cat_loop(fd);
		sys_close(fd);
	}

	sys_exit(0);
}

size_t check_cmdline(const int argc, char **argv){
	size_t fnum = 0;
	output_opt = 0x00;
	for(int n=1;n<argc;n++){
		if(strlen(argv[n]) == 0) continue;
		if(argv[n][0] != '-'){
			fnum++;
			continue;
		}
		if(argv[n][1] == '\0'){ // "-" stdin
			fnum++;
			continue;
		}
		check_option(argv[n]);
		memset(argv[n], '\0', strlen(argv[n]));
	}
	return fnum;
}

void check_option(const char *opt){
	bool flg_exit = false;
	size_t h_num = 1;
	opt++;
	if(*opt == '-'){ // --***
		h_num++;
		opt++;
	}

	if((h_num==1 && strcmp(opt, "E")==0) |
			(h_num==2 && strcmp(opt, "show-ends")==0))
		output_opt |= OPT_END;
	else if((h_num==1 && strcmp(opt, "T")==0) |
			(h_num==2 && strcmp(opt, "show-tabs")==0))
		output_opt |= OPT_TAB;
	else if(h_num == 2 && strcmp(opt, "help") == 0){
		flg_exit = true;
		puts("Usage: ./sksat-cat [OPTION]... [FILE]...\n"
			"Concatenate FILE(s) to standard output.\n\n"
			"With no FILE, or when FILE is -, read standard input.\n\n"
			"  -E, --show-ends          display $ at end of each line\n"
			"  -T, --show-tabs          display TAB characters as ^I\n"
			"    --help     display this help and exit\n"
			"    --version  output version information and exit\n"
			"Examples:\n"
			"  ./sksat-cat f - g  Output f's contents, then standard input, then g's contents.\n"
			"  ./sksat-cat        Copy standard input to standard output.\n"
			"\n");
	}else if(h_num == 2 && strcmp(opt, "version") == 0){
		flg_exit = true;
		puts("sksat-cat 0.1\n"
			"Copyright (C) 2019 sksat\n"
			"License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n"
			"This is free software: you are free to change and redistribute it.\n"
			"There is NO WARRANTY, to the extent permitted by law.\n\n"
			"Written by sksat <sksat@sfc.wide.ad.jp>\n");
	}else{
		flg_exit = true;
		puts("sksat-cat: unrecognized option '");
			for(int i=0;i<h_num;i++) puts("-");
			puts(opt);
			puts("\'\n");
		puts("Try \'sksat-cat --help\' for more information.\n");
	}

	if(flg_exit)
		sys_exit(0);
}

void cat_loop(int fd){
	char buf[BUF_SIZE];

	for(;;){
		memset(buf, '\0', BUF_SIZE);
		if(sys_read(fd, buf, BUF_SIZE-1) == 0)
			break;
		if(output_opt != 0x00)
			print_with_opt(buf);
		else
			puts(buf);
	}
}

void print_with_opt(const char *buf){
	char buf2[BUF_SIZE*2];

	const char *read = buf;
	char *write = buf2;
	for(;;){
		if(*read == '\0'){
			*write = '\0';
			break;
		}
		switch(*read){
		case '\n':
			if(output_opt & OPT_END){
				*write    = '$';
				*(write+1)= '\n';
				write++;
			}
			break;
		case '\t':
			if(output_opt & OPT_TAB){
				*write  = '^';
				*(write+1)= 'I';
				write++;
			}
			break;
		default:
			*write = *read;
			break;
		}

		read++;
		write++;
	}

	puts(buf2);
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

int strcmp(const char *s1, const char *s2){
	size_t l1, l2, len;
	l1 = strlen(s1);
	l2 = strlen(s2);
	len = (l1<l2 ? l1 : l2);
	for(int n=0;n<len;n++){
		if(s1[n] != s2[n]) return 1;
	}
	return 0;
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
