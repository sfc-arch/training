#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define ECHOBUF 1024


void echo_arg(void)
{
  // echo mode
  char buf[ECHOBUF];
  ssize_t len;
  while (len >= 0) {
    len = read(fd, buf, ECHOBUF);
    write(STDOUT, buf, len);
  }
  _exit(EXIT_FAILURE);
}


long calculate_fsize(int fd)
{
  struct stat stbuf;
  if(fstat(fd,&stbuf) == -1){
    exit(EXIT_FAILURE);
  }
  long fsize = stbuf.st_size;
  return fsize;
}

char *do_buffering(int argc, char *argv[])
{
  int fd;
  long fsize;
  char *buf;
  for(int i = 0; i < (argc - 1);i++){
    fd = open(argv[i+1],O_RDONLY;
      if (fd == -1){
        exit(EXIT_FAILURE);
      }
      fsize += calculate_fsize(fd);
  }
  // malloc buf
  return buf;
}



int main(int argc, char *argv[])
{
  if (argc == 1)
    echo_arg();

  char *buf = do_buffering(argc,argv);

}
