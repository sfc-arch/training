#include <unistd.h>
#include <fcntl.h>

// my stdlib

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
		int fd = open(argv[n], O_RDONLY);
		if(fd == -1)
			error("cannot open file.\n");
		cat_loop(fd);
		close(fd);
	}
}

void cat_loop(int fd){
	char buf[BUF_SIZE];

	for(;;){
		memset(buf, '\0', BUF_SIZE);
		if(read(fd, buf, BUF_SIZE) == 0)
			break;
		puts(buf);
	}
}

void error(const char *msg){
	puts(msg);
	_exit(-1);
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
	write(fd, str, strlen(str));
	return;
}

void puts(const char *str){
	fputs(stdout, str);
}
