#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd, buflen;
    char buf[1024];
    if (argc < 2)
        return 1;
    if ((fd = open(argv[1], O_RDONLY)) < 0)
        _exit(1);
    while ((buflen = read(fd, buf, 1024)) > 0)
        write(1, buf, buflen);
    close(fd);
    return 0;
}
