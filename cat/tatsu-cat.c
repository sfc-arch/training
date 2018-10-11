#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    int *fd;

    if ((fd = open(argv[1], O_RDONLY)) < 0)
    {
        // fprintf(stderr, "cannot open\n");
        exit(1);
    }

    int buflen;
    char buf[1024];

    // while ((buflen = read(fd, buf, 1024)) > 0)
    // {
    buflen = read(fd, buf, 1024);
    write(1, buf, buflen);
    // }
    close(fd);
    return 0;
}
