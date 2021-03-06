#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdarg.h>

#define E_NOT_FOUND 0
#define E_DIRECTORY 1
#define E_PERMISSION 2

void print(int file);
void error(int e_type, char *name);

int main(int argc, char *argv[])
{
    int file;
    struct stat stduf;

    if (--argc > 0) {
        while (*++argv) {
            stat(*argv, &stduf);
            if ((stduf.st_mode & S_IFMT) == S_IFDIR) {
                error(E_DIRECTORY, *argv);
                break;
            }
            if (access(*argv, F_OK) != 0) {
                error(E_NOT_FOUND, *argv);
                break;
            } else {
                if (access(*argv, R_OK) != 0) {
                    error(E_PERMISSION, *argv);
                    break;
                }
            }

            file = open(*argv, O_RDONLY, 0);
            print(file);
            close(file);
        }
    } else
        print(0);
    return 0;
}

#define BUFSIZE 1000

void print(int file)
{
    char buf[BUFSIZE];
    int n;

    while ((n = read(file, buf, BUFSIZE)) > 0)
        write(1, buf, n);
}

#define ERROR_MSG_SIZE 256

void error(int e_type, char *name)
{
    char error_msg[ERROR_MSG_SIZE];

    strcpy(error_msg, "cat: ");
    switch (e_type) {
        case E_NOT_FOUND:
            strcat(error_msg, name);
            strcat(error_msg, ": No such file or directory");
            break;
        case E_DIRECTORY:
            strcat(error_msg, name);
            strcat(error_msg, ": Is a directory");
            break;
        case E_PERMISSION:
            strcat(error_msg, name);
            strcat(error_msg, ": Permission denied");
            break;
        default:
            break;
    }
    strcat(error_msg, "\n");

    write(2, error_msg, strlen(error_msg));
}
