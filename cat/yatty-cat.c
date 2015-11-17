#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	
	int fd, i, rf;
	
	char buf[256];
	

	for(i = 1; i < argc; i++){
		fd = open(argv[i], O_RDONLY);

		while(1){
			rf = read(fd, buf, 255);

			write(2, buf, rf);
		

			if(rf == 0){
				break;
			}
			else if(rf < 0){
				return -1;
			}
	
		}
	close(fd);
	}	

	
    return 0;
}
