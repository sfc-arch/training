#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[]){
  int fdescript;
	ssize_t readbytes;
	ssize_t writebytes;
  char buf[1024];
    for (int i = 1; i < argc; i++) {
			fdescript = open(argv[i], O_RDONLY);
			if (fdescript == -1)
				continue;
		}
		while(1) {
			readbytes = read(fdescript,buf,1024);
			if (readbytes > 0 && readbytes <= 1024) {
				writebytes = write(1,buf,readbytes);
			} else if (readbytes == 0) {
				close(fdescript);
				writebytes = write(1,"\n",1);
				break;
			} else {
				break;
			}
		}
	}

