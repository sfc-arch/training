#include <fcntl.h> // need to use open
#include <unistd.h> // need to use read, write and close

/* Prototype Functions */

void print(char[]); // prints string
int length(const char[]); // returns length
void contents(const char*, char*); // reads and store the contents of the file
void option(const char*, char*); // handles options
void error(int); // handles errors

/* Main */

int main(int argc, const char *argv[]) {
        char buf[1024];
        int i;
        if (argc == 1 || (argc == 2 && *argv[1] == '-')) {
                while(1) write(1, buf, read(0, buf, 1024));
        } else if (argc > 1) {
                for ( i = 1; i < argc; i++) {
                        if (argv[i][0] != '-') {
                                contents(argv[i], buf);
                        } else {
                                option(*argv, buf);
                        }
                }
        }
        return 0;
}

/* Functions */

void print(char str[]) {
        int count = length(str);
        write(1, str, count);
}

int length(const char str[]) {
        int len = 0;
        while (*str++) len++;
        return len;
}

void contents(const char *path, char *buf) {
        int fd, rcount;
        if ((fd = open(path, 0)) < 0) error(0);

        while ((rcount = read(fd, buf, 1024)) > 0) print(buf);
        if (rcount < 0) error(2);
        if (close(fd) < 0) error(3);
}

void option(const char argv[], char *buf) { // b e n s t u v
        int i;
        char data[1024];

        for (i = 1; i < length(argv); i++) {
                if (argv[i] == 'n') {
                        print("Option -n is not yet supported.\n");
                } else {
                        print("That option is not supported.");
                }
        }
}

void error(int err_num) {
        switch (err_num) {
        case 0: print("No such file or directory\n"); break;
        case 1: print("There was an error writing to standard out\n"); break;
        case 2: print("There was an error reading the file\n"); break;
        case 3: print("There was an error closing the file\n"); break;
        default: print("Unknown error\n"); break;
        }
}
