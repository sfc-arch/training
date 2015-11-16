#include<unistd.h>/*open STDOUT_FILEなどのマクロ定義 */
#include<sys/types.h>
#include<sys/uio.h>
#include<fcntl.h>/*read */ /*write*/ /*close*/
#include<sys/stat.h>/*open*/

#define BUFFER_SIZE 1024

int openerror(void);
int writeerror(void);
int readerror(void);
int closeerror(void); //プロとタイプ宣言

int main(int argc, char *argv[])
{
    int i;
    int fd;
    ssize_t cc;
    char buf[BUFFER_SIZE];
    const char notation[] = "終了させる場合は、control + Dをおしてください。\n";

    if( argc == 1 )
    {
        write( STDOUT_FILENO, notation, sizeof(notation));
        while( (cc = read (STDIN_FILENO, buf, sizeof(buf) ) ) > 0)
            {
                if ( write( STDOUT_FILENO, buf, cc) == -1)
                {
                    writeerror();
                }
            }
        return 0;
    }

    for(i = 1; i < argc; i++)
    {
        if(( fd = open( argv[i], O_RDONLY)) == -1)
        {
            openerror();
        }

        while( ( cc = read(fd, buf, sizeof(buf) ) ) > 0)
        {
            if( (write( STDOUT_FILENO, buf, cc) ) == -1)
            {
                writeerror();
            }
        }

        if( close(fd) == -1)
        {
            closeerror();
        }
    }
    return 0;
}

int openerror(void)
{
    char open_error[] = "Open error\n";
    write( STDOUT_FILENO, open_error, sizeof(open_error) );
    return 1;
}

int writeerror(void)
{
    char write_error[]  = "Write error\n";
    write( STDOUT_FILENO, write_error, sizeof(write_error) );
    return 1;
}

int readerror(void)
{
    char read_error[] = "Read error\n";
    write( STDOUT_FILENO, read_error, sizeof(read_error) );
    return 1;
}

int closeerror(void)
{
     char close_error[] = "Close error\n";
     write( STDOUT_FILENO, close_error, sizeof(close_error) );
     return 1;
}
