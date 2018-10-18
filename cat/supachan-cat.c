#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

const char crlf[2] = "\r\n";
const char msg[7] = "supacat";
const char colon[2] = ": ";
void err(char* fname, int preverr);
int errstate = 0;

int main(int argc, char* argv[]) {
	short int isopen;
	short int isread;
	char buff[256];
	for (int i = 1; i < argc; i++) {
		isopen = open(argv[i], O_RDONLY);	
		int fnamelen = strlen(argv[i]);
		if (isopen == -1) {
			int errornum = errno;
			err(argv[i],errornum);
		} else {
			while(1) {
				isread = read(isopen,buff,256);
				if (isread > 0) {
					write(1,buff,isread);
				} else if (isread == 0) {
					close(isopen);
					break;
				} else {
					int errornum = errno;
					err(argv[i],errornum);
					break;
				}
			}
		}
		write(1,crlf,2);
	}
	return errstate;
}

void err(char* fname, int preverr) {
	write(1,msg,7);
	write(1,colon,2);
	write(1,fname,strlen(fname));
	write(1,colon,2);
	write(1,strerror(preverr),strlen(strerror(preverr)));
	errstate = 1;
}
