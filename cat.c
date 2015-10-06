#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
  int input;
  int length;
  int fd;
  char *str[1024];

  if (argc < 1) {
    write(2, "An error occured.\n", 18);
  } else if (argc == 1) {
    while ((input = read(0, str, 1024)) > 0) {
      write(1, str, input);
    }
  } else {
    for (int i = 1; i < argc; i++) {
      fd = open(argv[i],O_RDONLY);

      if (fd<0) {
        write(2, "An error occured.\n", 18);
      } else {
        while ((length = read(fd,str,1024)) > 0) {
          write(1,str,length);
        }
      }
    }
  }

  return 0;
}
