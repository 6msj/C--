/* James Nguyen */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

void forkAProcess(char *args[]);
void tokenizeArgs(char *args[], char *str);
void changedir(char *args[]);

int main(void) {
    char str[256];
    while(1) {
        printf("%s> ", (getpwuid (getuid()))->pw_name); // username prompt!
        fgets(str, 256, stdin);
        strtok(str, "\n"); // get rid of the null terminator for parsing later
        char *args[strlen(str)];
        tokenizeArgs(args, str);
        if(!(strcmp(str, "quit"))) exit(0); // if it matches a 0, stop the program
        !(strcmp(str, "cd")) ? changedir(args) : forkAProcess(args);
    }
}

void tokenizeArgs(char *args[], char *str) {
    char *p = strtok(str, " ");
    args[0] = p;
    int i = 1;
    while (p) {
        p = strtok(NULL, " ");
        args[i] = p;
        i++;
    }
    args[i] = (char*)0;
}

void changedir(char *args[]) {
    if(!args[1] || !(strcmp(args[1], "~/"))) {
        char *home = getenv("HOME");
        chdir(home); return;
    } else {
        chdir(args[1]);
    }
}

void forkAProcess(char *args[]) {
    int pid = fork();
    pid == 0 ? printf("Result: %d\n", execvp(args[0], args)) : wait(NULL); // assume it won't fail at creating a process =D
}
