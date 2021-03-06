#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdarg.h>

#define E_NOT_FOUND 0
#define E_DIRECTORY 1
#define E_PERMISSION 2
#define E_INVALID_ARG 3

typedef struct options {
    int number;
} Options;

void print(int file, Options options);
void itoa(int n, char s[]);
void reverse(char s[]);
void error(int e_type, char *name);

int main(int argc, char *argv[])
{
    int file, c;
    int number = 0;
    Options options = { 0 };
    struct stat stduf;

    // 引数がない場合は標準入力から読み込んで出力
    if (argc > 1) {
        while (--argc > 0 && (*++argv)[0] == '-') {
            //引数がハイフンだけだった場合は標準入力から読み込んで出力
            if (*++argv[0] == NULL) {
                print(0, options);
                return 0;
            }
            while ((c = *argv[0]++)) {
                switch (c) {
                    case 'n':
                        options.number = 1;
                        break;
                    default:
                        // cat -[invalid arguments]とした場合、エラーメッセージには一番最初の不正なオプションのみを表示する
                        // (例) cat -aho の場合、cat: illegal option -- a
                        argv[0]--;
                        (*argv)[1] = '\0';
                        error(E_INVALID_ARG, *argv);
                        return 1;
                }
            }
        }

        // オプションだけ指定した場合は標準入力から読み込んで出力
        if (argc > 0) {
            while (*argv) {
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
                print(file, options);
                close(file);
                argv++;
            }
        } else
            print(0, options);
    } else
        print(0, options);
    return 0;
}

#define BUFSIZE 1000
#define MAXSIZE 1000

void print(int file, Options options)
{
    // -nオプション
    if (options.number) {
        char c;
        int n, i = 0, lc = 1;
        char line[MAXSIZE], lc_char[10];

        while ((n = read(file, &c, 1)) == 1) {
            line[i] = c;
            i++;
            if (c == '\n') {
                itoa(lc++, lc_char);
                line[i] = '\0';

                write(1, "     ", strlen("     "));
                write(1, lc_char, strlen(lc_char));
                write(1, "  ", strlen("  "));
                write(1, line, strlen(line));

                i = 0;
            }
        }
    } else {
        char buf[BUFSIZE];
        int n;

        while ((n = read(file, buf, BUFSIZE)) > 0)
            write(1, buf, n);
    }


}

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
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
        case E_INVALID_ARG:
            strcat(error_msg, "illegal option -- ");
            strcat(error_msg, name);
            strcat(error_msg, "\nusage: cat [-n] [file ...]");
            break;
        default:
            break;
    }
    strcat(error_msg, "\n");

    write(2, error_msg, strlen(error_msg));
}
