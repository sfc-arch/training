#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * constants
 */
typedef enum {
    FLAG_LINE_NUMBER = 0x01,
    FLAG_SKIP_BLANK = 0x02
} Flag;

const char *HELP = "usage: unicat [-bn] [file ...]\n";
const char *OPEN_ERROR = "No such file or directory\n";
const char *OPTION_ERROR = "illegal option -- ";
const char *LINE_NO_ERROR = "file too large to show line number\n";

/*
 * utility functions
 */
int int_to_str(int n, char *str) {
    int place = 1;
    int strc = 1;
    while(place * 10 <= n) {
        ++strc;
        place *= 10;
    }
    while(place >= 1) {
        *str = n / place;
        n -= *str * place;
        *str += '0';
        ++str;
        place /= 10;
    }
    *str = '\0';
    return strc;
}

int length(const char *str) {
    int len;
    for(len = 0; *str != '\0'; ++len, ++str);
    return len;
}

/*
 * display functions
 */
void print_help() {
    write(2, HELP, length(HELP));
}

void print_error_prefix() {
    write(2, "unicat: ", 8);
}

void print_error(const char *message) {
    write(2, message, length(message));
}

void display_char(char c, int flush) {
    static char buf[512];
    static int ptr = 0;
    if(c) {
        buf[ptr++] = c;
    }
    if(flush || ptr == 511) {
        buf[ptr] = '\0';
        write(1, buf, ptr);
        ptr = 0;
    }
}

void display_chars(char *cs, int flush) {
    while(*cs) {
        display_char(*(cs++), flush);
    }
}

int display_lineno(int lineno) {
    char str[9];
    int strc = int_to_str(lineno, str);
    int i;

    if(strc > 8) {
        print_error_prefix();
        print_error(LINE_NO_ERROR);
        return 0;
    }

    if(strc < 7) {
        for(i = 0; i < 6 - strc; ++i) {
            display_char(' ', 0);
        }
    }
    display_chars(str, 0);
    display_char('\t', 0);

    return 1;
}

/*
 * core functions
 */
int cat(int flag, int filec, const char *files[]) {
    int i, j, fd, readlen;
    int lineno = 0;
    int linefeeded = 1;
    char buf[512];
    char *strbuf;

    i = 0;
    do {
        fd = filec < 1 ? 0 : open(files[i], O_RDONLY);
        if(fd < 0) {
            print_error_prefix();
            print_error(files[i]);
            print_error(": ");
            print_error(OPEN_ERROR);
            return 0;
        }

        if(flag & (FLAG_LINE_NUMBER | FLAG_SKIP_BLANK)) {
            lineno = 1;
        }
        while((readlen = read(fd, buf, 512)) > 0) {
            for(j = 0; j < readlen; ++j) {
                if(lineno && linefeeded) {
                    if(!(flag & FLAG_SKIP_BLANK) || buf[j] != '\n') {
                        display_lineno(lineno++);
                    }
                    linefeeded = 0;
                }
                display_char(buf[j], 0);
                if(buf[j] == '\n') {
                    linefeeded = 1;
                    if(fd == 0) {
                        display_char(0, 1);
                    }
                }
            }
        }
        ++i;
    } while(i < filec);
    display_char('\0', 1);

    close(fd);
    return 1;
}

int parse_options(int argc, const char *argv[], int *filec, const char **files[]) {
    int flag, i, optionc, j;
    char error_char;
    for(i = 1, flag = 0; i < argc; ++i) {
        if(*argv[i] == '-') {
            optionc = length(argv[i]);
            for(j = 1; j < optionc; ++j) {
                switch(*(argv[i] + j)) {
                    case 'n':
                        flag = flag | FLAG_LINE_NUMBER;
                        break;
                    case 'b':
                        flag = flag | FLAG_SKIP_BLANK;
                        break;
                    default:
                        error_char = *(argv[i] + j);
                        print_error_prefix();
                        print_error(OPTION_ERROR);
                        print_error(&error_char);
                        print_error("\n");
                        return -1;
                }
            }
        } else {
            break;
        }
    }
    *filec = argc - i;
    *files = &argv[i];
    return flag;
}

/*
 * main function
 */
int main(int argc, const char *argv[]) {
    int flag, filec;
    const char **files;

    flag = parse_options(argc, argv, &filec, &files);
    if(flag < 0) {
        print_help();
        return -1;
    }

    if(!cat(flag, filec, files)) {
        return -1;
    }

    return 0;
}
