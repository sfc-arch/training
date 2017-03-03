#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void print_error(int errnum){
	write(2, strerror(errnum), 256);
	write(1, "\n", 1);
}

void print(int fd){
	char buf[1024]; int rc;
	while ((rc = read(fd, buf, 1024)))
		write(1, buf, rc);
	if (rc < 0)
		print_error(errno);
}

int main(int argc, const char *argv[]) {
	char buf[1024]; int rc, i, fd;

	if (argc == 1 || (argc == 2 && *argv[1] == '-')) {
		print(0);
	} else {
		for (i = 1; i < argc; i++) {
			if ((fd = open(argv[i], 0)) < 0) {
				print_error(errno);
				return 1;
			}
			print(fd);
			close(fd);
		}
	}
	return 0;
}
