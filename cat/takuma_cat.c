#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFSIZE 1024

int read_file(char *filename);
void print_error(int n, char *filename);
int flow_stream();

int main(int argc, char *argv[]){
    if(argc < 2){
        flow_stream();
    } else if(argc >= 2){
        for (int i=1; i<argc; i++){
            read_file(argv[i]);
        }
    }
}

int flow_stream(){
    char buff[BUFFSIZE];
    ssize_t count;

    while (1){
        count = read(STDIN_FILENO, buff, BUFFSIZE);
        write(STDOUT_FILENO,buff,count);
    }
    return 1;
}

int read_file(char *filename){
    int fd;
    char buff[BUFFSIZE];
    int rcount;

    fd = open(filename, O_RDONLY);

    if(fd == -1){
        print_error(errno, filename);
        return 1;
    }

    while((rcount=read(fd,buff,BUFFSIZE)) > 0){
        if(write(STDOUT_FILENO,buff,rcount) == -1){
            print_error(errno,filename);
            return 1;
        }
    }
    close(fd);
    return 0;
}

void print_error(int n, char *filename){
    char *emsg_pointer = strerror(n);
    int emsg_len = strlen(emsg_pointer);
    write(STDOUT_FILENO,"cat: ",5);
    write(STDOUT_FILENO,filename,strlen(filename));
    write(STDOUT_FILENO,": ",2);
    write(STDERR_FILENO, emsg_pointer, emsg_len);
    write(STDOUT_FILENO, "\n", 2);
}
