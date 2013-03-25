#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv) {


    void runit(void);
    int pid;
    int status = 5;

    switch (pid = fork()) {
        case 0:
            runit();
            break;
        default:
            wait(&status);
            printf("I'm still here!\n");
            break;
        case -1:
            perror("fork");
            exit(1);
    }

    exit(0);
}

void runit (void) {
    printf ("About to run ls\n");
    execlp ("ls", "ls", "-aF", "/", (char*)0);
    perror("execlp");
    exit(1);
}

