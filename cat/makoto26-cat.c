#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

int main(int argc, const char *argv[]) {
  int input;
  int length;
  int fd;
  char *str[BUFFER_SIZE];

  switch (argc) {
    case 0:
            write(2, "An error occured.\n", 18);
            return -1;
    case 1:
            while ((input = read(0, str, BUFFER_SIZE)) > 0) {
              write(1, str, input);
            }
            return -1;
    default:
            for (int i = 1; i < argc; i++) {
              fd = open(argv[i],O_RDONLY);

              if (fd < 0) {
                write(2, "An error occured.\n", 18);
                return -1;
              }

              if (fd >= 0 ) {
                while ((length = read(fd,str,BUFFER_SIZE)) > 0) {
                  write(1,str,length);
                }
              }
              close(fd);
              return 0;
            }
  }
}
