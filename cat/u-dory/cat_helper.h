/*
Thanks to
  http://curtaincall.weblike.jp/portfolio-unix/api.html
*/

// print
// prints out a String to std output without a newline.
void print( char *string ) {
    write( STDOUT_FILENO, string, strlen( string ) );
}

// puts
// prints out a String to std output with a newline.
void puts( char *string ) {
    print( string );
    print( "\n" );
}

// gets_to
// gets a String from std input, and inputs to str.
// !! Always create a char * object before !!
char *gets_to( char *str, int size ) {
    memset( str , '\0' , strlen( str ) );
    char tmpstr[size];
    int result = read( STDIN_FILENO, tmpstr, size ); // NOTE: The third argument includes the input's endline
    if((result == 0) | (result == -1)) {
        //input canceled by Ctrl-D.
        return(0);
    }
    int newlength = strlen( tmpstr );//-1;
    strncpy( str, tmpstr, newlength );
    memset( tmpstr , '\0' , strlen( tmpstr ) );
    return str;
}

// includes_in_array
// returns 0 if includes.
// returns 1 if not.
int includes_in_array( char word[], char *array[], int array_size ) {
    int i;
    int wordlen = strlen( word );
    for( i = 0; i < array_size - 1; i++ ) {
        int arrlen = strlen( array[i] );
          // int maxlength : the length of the longer string.
        int maxlength = ( wordlen > arrlen ) ? wordlen : arrlen;
        if( strncmp( word, array[i], maxlength ) == 0 ) {
            return 0;
        }
    }
    // if none does,
    return 1;
}
