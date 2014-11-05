#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int my_strlen(const char *str){
	int l = 0; 

	while(*str++) l++;
	return l;
}

int writestr(const char* str){
	int i = my_strlen(str);
	write(1, str, i);
}

int main(int argc, char *argv[]){
	char buf[1024];
	int fd;
	int rc;
	int count = 0;

	if(argc == 1){
		while((rc = read(0, buf, 1024)) > 0){
			write(1, buf, rc);
		}
	}else{
		int i;
		for(i = 1; i < argc; i++){
			if ((fd = open(argv[i], O_RDONLY)) == -1){
				writestr("Error. No such file or directory.\n");
			}else{
				while((rc = read(fd, buf, 1024)) > 0){
				write(1, buf, rc);
				}
				if(rc == -1)writestr("Error. File can not be read.\n");
				close(fd);
				}
			}
	}
	return 0;
}
