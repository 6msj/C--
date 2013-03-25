#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char **argv) {


    void runit(void);
    int pid;

    switch (pid = fork()) {
        case 0:
            runit();
            break;
        default:
            sleep(5);
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
