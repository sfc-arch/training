#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int fd, dt, len, i;
	char input;
	char buf[512];
	
	if(argc==1){
		input=read(0, buf, 512);       //0はstdin(ファイルディスクリプタにあらかじめ予約されている)
		
		if(input > 0){
			write(1, buf, input);      //1はstdout(ファイルディスクリプタにあらかじめ予約されている)
		}
		if(input <= 0){
			write(2, buf, input);      //2はstderr(ファイルディスクリプタにあらかじめ予約されている)
		}
	}
	
	for(i=1; i<argc; i++){
		fd = open(argv[i], O_RDONLY);
		
		if(fd==-1){
			return -1;
		}
		
		len= read(fd, buf, 512);
		
		if(len>0){
			write(1, buf, len);
		}else{
			return -1;
		}
	}
	close(fd);
	return 0;
}
