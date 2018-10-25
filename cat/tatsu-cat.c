#include <fcntl.h>
#include <unistd.h>
#define N 1024
int main(int argc, char *argv[])
{
    int fd, buflen;
    char buf[N];
    if (argc < 2)
        _exit(1);
    for (int i = 1; i < argc; i++)
    {
        if ((fd = open(argv[i], O_RDONLY)) < 0)
        {
            close(fd);
            _exit(1);
        }
        while ((buflen = read(fd, buf, N)) > 0)
            write(1, buf, buflen);
        close(fd);
    }
    return 0;
}
