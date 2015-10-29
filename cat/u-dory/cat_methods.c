// main function of cat.
int main_function() {
    int N = 256;
    char std_in[N];
    while(1) {
    if ( gets_to( std_in, N ) == 0) { break; }
        print( std_in );
        memset( std_in , '\0' , strlen( std_in ) );
    }
    return(0);
}

// This function is just for outputting the paragraphs in cat_const.h
// in C, seemes you need to hand the number of array.
void show_paragraph( const char *sentences[], int lines ) {
    int i;
    for( i = 0; i < lines; i++ ) {
        puts( sentences[i] );
    }
}

// receive reglar expression string and check for matches in the arguments.
int check_arguments( char *argv[], int argc, char regexp[] ) {
    regex_t preg;
    size_t nmatch = 2;
    int count = 0;
    regmatch_t pmatch[nmatch];
    int i;

    if( regcomp( &preg, regexp, REG_EXTENDED|REG_NEWLINE ) != 0 ) {
        puts( "*error: regex complile failed." );
        _exit(1);
    }
    for( i = 0; i < argc; i++ ) {
        // puts( argv[i] );
        if( regexec( &preg, argv[i], nmatch, pmatch, 0 ) == 0 ) {
            //puts( "match" );
            count++;
            continue;
        }
    }
    regfree( &preg );

    return( count );
}