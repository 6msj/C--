#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void tokenizeArgs(char *args[], char *str);


int main() {
    // static so can't be used with strtok
    char * str = "this is a string"; 
    char * bac = strdup(str);  
    // create an array as big as the string, so tokens will always fit
    char *args [strlen(bac)]; 
    tokenizeArgs(args, bac);

    return 0;
}

void tokenizeArgs(char *args[], char *str) {
    char *p = strtok(str, " ");
    args[0] = p;
    int i = 1;
    while (p) {
        p = strtok(NULL, " ");
        args[i] = p;
        i++;
        printf("%s\n", p);
    }
    args[i] = (char*)0;

    //printf("%s", args[0]);
    //printf("%s", args[1]);
    //printf("%s", args[2]);
    //printf("%s", args[3]);
    //printf("%s", args[4]);

}

