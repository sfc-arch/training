#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
    char buf[1024]; int i, fd;

    if (argc == 1 || (argc == 2 && *argv[1] == '-')) {
        while ((write(1, buf, read(0, buf, 1024))));
    } else {
        for (i = 1; i < argc; i++) {
                if ((fd = open(argv[i], 0)) > 0)
                        while ((write(1, buf, read(fd, buf, 1024)))) ;
                else
                        write(1, "No such file or directory\n", 26);
            }
    }
    return 0;
}
