#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int perror(int errnum){
	write(2, strerror(errnum), 256);
	write(1, "\n", 1);
	return -1;
}

int main(int argc, const char *argv[]) {
	char buf[1024]; int i, fd;

	if (argc == 1 || (argc == 2 && *argv[1] == '-')) {
		if (read(0, buf, 1024) < 0)
            return perror(errno);
        else
            while (write(1, buf, read(0, buf, 1024)));
	} else {
		for (i = 1; i < argc; i++) {
			if ((fd = open(argv[i], 0)) < 0) {
				return perror(errno);
			} else if(read(fd, buf, 1024) < 0) {
				return perror(errno);
			} else {
				fd = open(argv[i], 0);
				while (write(1, buf, read(fd, buf, 1024)));
			}
		}
	}
	return 0;
}
