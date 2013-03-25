#include <stdio.h>
#include <stdlib.h>

int main() {
    char ch;
    
    // the text files for input and output are predetermined
    char sourceFile[] = "text1";
    char targetFile[] = "text2";

    // the files that are opened
    FILE *source, *target;

    // open source in read mode and target in write mode
    source = fopen(sourceFile, "r");
    target = fopen(targetFile, "w");


    // if file wasn't opened for some reason, exit
    if(source == NULL || target == NULL) {
        if(source != NULL) fclose(source);
        printf("exiting");
        exit(EXIT_FAILURE);
    }

    // get a char from source and write it to target 
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, target);
    }

    printf("Copied");
    fclose(source);
    fclose(target);

    return 0;
}
