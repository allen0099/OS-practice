#include <stdio.h>
#include <zconf.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid > 0) {
        printf("parent process");
    } else if (pid == 0) {
        printf("child process");
    } else {
        printf("fork failed!");
    }
}