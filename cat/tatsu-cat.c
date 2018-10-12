#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    int fd;
    if ((fd = open(argv[1], O_RDONLY)) < 0)
        _exit(1);
    int buflen;
    char buf[1024];
    while ((buflen = read(fd, buf, 1024)) > 0)
        write(1, buf, buflen);
    close(fd);
    return 0;
}
