#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

#define BUFFSIZE 1024

void read_file(char *filename);

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr,"Usage: %s from to\n", argv[0]);
        _exit(1);
    }
    read_file(argv[1]);
}

void read_file(char *filename){
    int fd;
    char buff[BUFFSIZE];
    int rcount;

    fd = open(filename, O_RDONLY);

    if(fd == -1){
        perror(filename);
        _exit(1);
    }

    while((rcount=read(fd,buff,BUFFSIZE)) > 0){
        if(write(1,buff,rcount) == -1){
            _exit(1);
        }
    }
    close(fd);
}

