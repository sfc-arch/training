#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

const char crlf[2] = "\r\n";
const char msg[7] = "supacat";
const char colon[2] = ": ";
void err(char* fname, int preverr);
void dorw(char* fname, int fdescript);
int errstate = 0;
char buff[256];

int main(int argc, char* argv[]) {
	int fdescript;
	for (int i = 1; i < argc; i++) {
		fdescript = open(argv[i], O_RDONLY);
		if (fdescript == -1) {
			err(argv[i],errno);
			continue;
		}
		dorw(argv[i],fdescript);
	}
	return errstate;
}

void err(char* fname, int preverr) {
	write(2,msg,7);
	write(2,colon,2);
	if(fname != NULL) {
		write(2,fname,strlen(fname));
		write(2,colon,2);
	}
	write(2,strerror(preverr),strlen(strerror(preverr)));
	write(1,crlf,2);
	errstate = 1;
}

void dorw(char* fname, int fdescript) {
	ssize_t readbytes;
	ssize_t writebytes;
	while(1) {
		readbytes = read(fdescript,buff,256);
		if (readbytes > 0 && readbytes <= 256) {
			writebytes = write(1,buff,readbytes);
			if (writebytes == -1) err(NULL,errno);
		} else if (readbytes == 0) {
			close(fdescript);
			writebytes = write(1,crlf,2);
			if (writebytes == -1) err(NULL,errno);
			break;
		} else {
			int errornum = errno;
			err(fname,errornum);
			break;
		}
	}
}

