#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int sum; /* make sum a public variable */


void runner1(void *a) { /* sum 1 to a */
    sum = 0; /* init sum to 0 */
    for (int i = 1; i <= atoi(a); i++) {
        sum += i; /* add i to sum */
    }
    pthread_exit(NULL); /* thread exit without error */
}

int main(int argc, char *argv[]) {
    pthread_t tid; /* var a pointer of thread */

    pid_t pid; /* var a pointer of fork */

    if (argc != 3) { /* check the argument is 3 */
        printf("must have 3 argc");
        return -1;
    }

    pid = fork(); /* fork the process */
    if (pid > 0) { /* parent process */
        sum = atoi(argv[2]); /* convert pointer string to integer */
        printf("sum = %d | this is parent process and pid = %d\n", sum, getpid());
        wait(NULL); /* wait the child process end */
    } else if (pid == 0) { /* child process */
        pthread_create(&tid, NULL, (void *(*)(void *)) runner1, argv[1]); /* create a thread in child process */
        pthread_join(tid, NULL); /* wait thread end */
        printf("sum = %d | this is child process and pid = %d\n", sum, getpid());
        exit(0); /* exit the child process */
    }
    printf("total %d parameters, the parameter is %s and %s\n", argc - 1, argv[1], argv[2]);
    return 0;
}