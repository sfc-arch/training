#include<unistd.h>/*open STDOUT_FILEなどのマクロ定義 */
#include<sys/types.h>
#include<sys/uio.h>
#include<fcntl.h>/*read */ /*write*/ /*close*/
#include<sys/stat.h>/*open*/


#define BUFFER_SIZE 1024
#define ERNOTE "error occered\n"
#define ERNUM 15


int main( int argc, char *argv[])
{
    int fd;
    ssize_t cc;
    char buf[BUFFER_SIZE];
    char notation[] = "終了させる場合は、control + Dをおしてください。\n";


    if( argc == 1)
    {
        write( STDOUT_FILENO, notation, sizeof(notation));
        while( ( cc = read ( STDIN_FILENO, buf, sizeof(buf) ) ) > 0)
            {
                if ( write( STDOUT_FILENO, buf, cc) == -1)
                {
                    write( STDOUT_FILENO, ERNOTE, ERNUM);
                    return 1;
                }
            
            }
        return 0;
    }

    int i;
    for( i = 1; i < argc; i++)
    {
        if( ( fd = open( argv[i], O_RDONLY) ) == -1)
        {
            write( STDOUT_FILENO, ERNOTE, ERNUM);
            return 1;
        }

        while( ( cc = read( fd, buf, sizeof(buf) ) ) > 0)
        {
            if( (write( STDOUT_FILENO, buf, cc) ) == -1)
            {
                write(STDOUT_FILENO, ERNOTE, ERNUM);
                return 1;
            }
        }

        if( close(fd) == -1)
        {
            write( STDOUT_FILENO, ERNOTE, ERNUM);
            return 1;
        }

    }
    return 0;
}

