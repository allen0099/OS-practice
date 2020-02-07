#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define MAX 25

int main() {
    int fd[2];
    pid_t p; /* make fork */
    FILE *file;

    char s[100];
    file = fopen("pipe.txt", "r");
    rewind(file);

    fscanf(file, "%s", s);
    printf("%s", s);

//    fprintf(file, "1234meow");
//    fclose(file);
    pipe(fd); /* make pipe */
    if (fd < 0) {
        printf("Create pipe fail\n");
    }
    p = fork();
    if (p > 0) { /* parent process */
        char pass_string[MAX] = "Meow";
        close(fd[0]); /* close read end */
        write(fd[1], pass_string, strlen(pass_string) + 1);
        close(fd[1]); /* close write end */
        wait(NULL);
    } else if (p == 0) { /* child process */
        char store_string[MAX];
        close(fd[1]); /* close write end */
        read(fd[0], store_string, sizeof(store_string));
        printf("Child Process read: %s\n", store_string);
        close(fd[0]); /* close read end */
    } else {
        printf("Create fork fail!\n");
    }
}