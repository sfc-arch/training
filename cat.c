#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int rw(int fd)
{
	if (fd < 0) {
		write(2, "open error\n", 11);
		return -1;
	}

	int rs;
	char buf[256];

	while (1) {
		rs = read(fd, buf, 256);

		if (rs < 0) {
			write(2, "read error\n", 11);
			return -1;
		}
		
		if (rs == 0) break;
		else write(1, buf, rs);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int i, fd;

	switch (argc) {
		case 0:
			write(2, "argument error\n", 15);
			return -1;
		case 1:
			if (rw(0) != 0) return -1;
			break;
		default:
			for (i = 1; i < argc; i++) {
				fd = open(argv[i], O_RDONLY);
				if (rw(fd) != 0) return -1;
				close(fd);
			}
	}

	return 0;
}
