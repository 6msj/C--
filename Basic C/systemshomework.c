#include <stdlib.h>
#include <stdio.h>

int main () {
    printf ("just one process only\n");
    printf("calling fork\n");
    int pid = fork();
    if (pid==0) {
        printf("I am child process.");
    } else if (pid > 0) {
        printf("I am parent process.\n");
    }  else {
        printf("Error in fork");
    }
    return 0;
}

