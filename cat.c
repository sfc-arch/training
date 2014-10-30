#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		write(2, "argument error\n", 16);
		return -1;
	}

	int i, fd, rs;
	char buf[256];

	for (i = 1; i < argc; i++)
	{
		fd = open(argv[i], O_RDONLY);

		if (fd < 0) {
			write(2, "open error\n", 16);
			return -1;
		}

		while (1) {
			rs = read(fd, buf, sizeof(buf));

			if (rs < 0) {
				write(2, "read error\n", 16);
				return -1;
			}
			
			if (rs == 0) break;
			else write(1, buf, rs);
		}

		close(fd);
	}

	return 0;
}