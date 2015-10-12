/*
Thanks to
  http://curtaincall.weblike.jp/portfolio-unix/api.html
*/

// print
// prints out a String to std output without a newline.
void print(char *string) {
    write(STDOUT_FILENO, string, strlen(string));
}

// puts
// prints out a String to std output with a newline.
void puts(char *string) {
    print(string);
    print("\n");
}

// gets_to
// gets a String from std input, and inputs to str.
// !! Always create a char * object before !!
// Also, this method deletes the endline for you.
// this method is not used for now(under development). Use gets_to2() instead.
char *gets_to(char *str) {
  //char string[size];
  char tmpstr[10] = "";
  int result = read(STDIN_FILENO, tmpstr, sizeof(str) ); // NOTE: The third argument includes the input's endline
        // COMMENT...
        // Afterall, sizeof(str) always passes "8"(size of char). How can I change this?
        // I want this expression to pass the exact length of what-ever-input-string you give. (Which may not able in C)
        // Another solution is to expressly pass the length of the *char[] to gets_to(), which I have comment-outed for now.
        // It's not beautiful, but may be the right way. If you do that, the usage will be like this:
        //    char ans[some-kind-of-memory];
        //    int lengthOfInputCharWhichYouThinkAsMaximumForSure;
        //    gets_to(ans, lengthOfInput...)
  if((result == 0) | (result == -1)) {
    //puts("\nInput canceled. Aborting.");
    _exit(0);
  }
  int newlength = strlen(tmpstr)-1;
  strncpy(str, tmpstr, newlength);
  return str;
}

char *gets_to2(char *str, int size) {
    memset( str , '\0' , strlen( str ) );
    char tmpstr[size];
    int result = read(STDIN_FILENO, tmpstr, size ); // NOTE: The third argument includes the input's endline
        // COMMENT...
        // Yeah yeah, in this version I did the thing I wrote in gets_to().
        // Now I can easily handle large strings. ...but far beautiful
    if((result == 0) | (result == -1)) {
        //input canceled by Ctrl-D.
        return(0);
    }
    int newlength = strlen(tmpstr);//-1;
    strncpy( str, tmpstr, newlength );
    memset( tmpstr , '\0' , strlen( tmpstr ) );
    return str;
}

// includes_in_array
// returns 0 if includes.
// returns 1 if not.
int includes_in_array(char word[], char *array[], int array_size) {
    int i;
    int wordlen = strlen(word);
    for(i = 0; i < array_size - 1; i++) {  // Somehow the size becomes 0
        /* // test //
        print(word);
        print(" ");
        print(array[i]);
        */ // end of test //
        int arrlen = strlen(array[i]);
          // int maxlength : the length of the longer string.
        int maxlength = (wordlen > arrlen) ? wordlen : arrlen;
        if( strncmp( word, array[i], maxlength ) == 0 ) {
            /* // test //
            puts(" > true, ");
            */ //end of test //
            return 0;
        } else {
            /* // test //
            puts(" > false, ");
            */ //end of test //
        }
    }
    // if none does,
    return 1;
}
