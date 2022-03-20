#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
  if (argc == 1) {
    while (1) {
      char buf[1024];
      fgets(buf,1024,stdin);
      printf("%s",buf);
    }
  }

  for (int i = 0; i < argc; i++) {
    struct stat stbuf;
    int fd = open(argv[i], O_RDONLY);
    if (fstat(fd, &stbuf) == -1) {
        exit(EXIT_FAILURE);
    }
    long fsize = stbuf.st_size;

    FILE *fp;
    if ((fp = fdopen(fd, "r")) == NULL) {
      exit(EXIT_FAILURE);
    }
    char *buffer = (char *)malloc(fsize);
    long count = 0;
    int c;
    while((c = fgetc(fp)) != EOF){
        *(buffer+count) = (char)c;
        count++;
    }
    printf("%s\n", buffer);
    fclose(fp);
  }
  return 0;
}
