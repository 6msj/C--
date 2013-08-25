#include <stdio.h>
#include <stdlib.h>

bool reverseWords( char str[] );

int main() {
    reverseWords( "string" );
    return 0;
}


bool reverseWords( char str[] ) {
    char *buffer;
    int tokenReadPos, wordReadPos, wordEnd, writePos = 0;

    /* Position of the last character is length - 1 */
    tokenReadPos = strlen(str) - 1;

    buffer = (char *) malloc(tokenReadPos + 2);
    if( !buffer ) {
        return false; /* reverseWords failed */
    }

    while( tokenReadPos >= 0 ) {
        if( str[tokenReadPos] == ' ' ) { // Non-word character
            /* Write character */
            buffer[writePos++] = str[tokenReadPos--];
        } else { // non word character
            // Store position of end of word
            wordEnd = tokenReadPos;

            // Scan to next non-word character
            while( tokenReadPos >= 0 && str[tokenReadPos] != ' ' ) {
                tokenReadPos--;
            }

            // tokenReadPos went past the start of the word
            wordReadPos = tokenReadPos + 1;

            // Copy the character of the word
            while( wordReadPos <= wordEnd ) {
                buffer[writePos++] = str[wordReadPos++];
            }
        }
    }
    // null terminate buffer and copy over str
    buffer[writePos] = '\0';
    strcpy(str, buffer);
    free(buffer);
    return true; // ReverseWords successful

}
