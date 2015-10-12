/*
Thanks to
  http://curtaincall.weblike.jp/portfolio-unix/api.html
*/

//#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <regex.h>
#include "u-dory/cat_helper.h"
#include "u-dory/cat_consts.h"

#include "u-dory/cat_methods.c"

const int N = 1024;

int main(int argc, char *argv[]) {
    int i, n, fdr, result;
        char buf[sizeof(char)*N];
        if( argc <= 1 ) {
            main_function();
        } else {
            if( check_arguments( argv, argc, "^--version" ) > 0 ) {
                show_paragraph( NuVersionSentences, sizeof( VersionSentences ) / sizeof( VersionSentences[0] ) );
                //return(0);
            } else if( check_arguments( argv, argc, "^--help" ) > 0)  {
                show_paragraph( HelpSentences, sizeof( HelpSentences ) / sizeof( HelpSentences[0] ) );
                //return(0);
            } else {

                    // # todo:
                    // after the if statement above,
                    // delete things from the array.
                    // wrap things below as a method, and pass options as arguments.

                for( i = 1; i < argc; i++ ) {
                    if( strcmp( "-", argv[i] ) == 0 ) {
                        result = main_function();
                        if( result == 0 ) {
                            continue;
                        }
                    } else {
                        // open the file
                        fdr = open( argv[i], O_RDONLY );
                        if( fdr == -1 ) {
                            print( "*cat: " );
                            print( argv[i] );
                            puts( ": no such file or directory" ); return(1);
                        }
                        // copy to the buffer
                        n = read( fdr, buf, sizeof( buf ) );
                        if( n == -1 ) {
                            puts( "*cat: make buffer error" ); return(1);
                        }
                        print( buf );
                        close( fdr );
                    }
                }
            }
        }
    return(0);
}
