#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int fd, len, i;
	char input;
	char buf[512];
	
	if(argc == 1){
		for(;input >= 0;){
			input = read(0, buf, 512);
			write(1, buf, input);
		}
	}
	
	for(i = 1; i < argc; ++i){
		fd = open(argv[i], O_RDONLY);
		
		if(fd == -1){
			return -1;
		}
		
		while(1){
			len = read(fd, buf, 512);
			
			if(len > 0){
				write(1, buf, len);
			}else{
				return -1;
			}
		}
	}
	close(fd);
	return 0;
}
