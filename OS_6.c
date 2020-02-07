// GitHub 連結 https://gist.github.com/allen0099/1245166cf7d5968ee6ed88a6927cb910
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX 25
#define READ_END 0
#define WRITE_END 1
#define TRUE 1
#define FALSE 0

int fd[2], fd2[2];

typedef struct my_data {
    FILE *file;
    int pipe_using;
    char in_buf[MAX];
    char out_buf[MAX];
} Data;

void *read_file_in(void *arg) {
    Data *data = (Data *) arg;

    while (data->pipe_using == TRUE);

    close(fd2[READ_END]); /* close read end */
    for (int i = 0; i < MAX; i++) {
        if (fgets(data->in_buf, MAX, data->file) == NULL) {
            break;
        }

        write(fd2[WRITE_END], data->in_buf, sizeof(data->in_buf));

//        printf("%d ", i);
//        printf("[PIPE OUT] %s ", data->in_buf);
    }
    write(fd2[WRITE_END], "-1", sizeof("-1"));
    close(fd2[WRITE_END]); /* close write end */
    pthread_exit(NULL);
}

void *write_file_out(void *arg) {
    Data *data = arg;

    FILE *file = fopen("pipe_out.txt", "a+");

    close(fd2[WRITE_END]); /* close write end */
    for (int i = 0; i < MAX; i++) {
        read(fd2[READ_END], data->out_buf, sizeof(data->out_buf));
        if (strcmp(data->out_buf, "-1") == 0) {
            break;
        }

        fprintf(file, "%s", data->out_buf);

//        printf("%d ", i);
//        printf("[PIPE IN] %s\n", data->out_buf);
    }
    close(fd2[READ_END]); /* close read end */
    fclose(file);
    pthread_exit(NULL);
}

void *scan_in(void *arg) {
    Data *data = (Data *) arg;

    close(fd[READ_END]); /* close read end */
    while (scanf("%s", data->in_buf) > 0) {
        if (strcmp(data->in_buf, "-1") == 0) {
            break;
        }

        write(fd[WRITE_END], data->in_buf, sizeof(data->in_buf));

//        printf("[PIPE OUT] %s ", data->in_buf);
    }
    write(fd[WRITE_END], "-1", sizeof("-1"));
    close(fd[WRITE_END]); /* close write end */
    pthread_exit(NULL);
}

void *write_scan_out(void *arg) {
    Data *data = arg;
    FILE *file = fopen("pipe_out.txt", "a+");

    close(fd[WRITE_END]); /* close write end */
    for (int i = 0; i < MAX; i++) {
        read(fd[READ_END], data->out_buf, sizeof(data->out_buf));
        if (strcmp(data->out_buf, "-1") == 0) {
            break;
        }

        fprintf(file, "%s\n", data->out_buf);

//        printf("%d ", i);
//        printf("[PIPE IN] %s\n", data->out_buf);
    }
    close(fd[READ_END]); /* close read end */
    fclose(file);
    data->pipe_using = FALSE;
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    Data data;

    pthread_t tid, tid2;

    pipe(fd); // pipe 1
    pipe(fd2); // pipe 2
    if (fd < 0 || fd2 < 0) {
        printf("Create pipe fail\n");
    }

    pid_t pid;
    pid = fork(); // fork
    data.pipe_using = TRUE;
    if (pid > 0) { // parent
        pthread_create(&tid2, NULL, (void *(*)(void *)) write_scan_out, &data); // thread B
        pthread_join(tid2, NULL); // wait thread B end
        printf("Parent Process of ThreadB is Done\n");

        data.file = fopen("pipe.txt", "r");
        pthread_create(&tid, NULL, (void *(*)(void *)) read_file_in, &data); // thread A
        pthread_join(tid, NULL); // wait thread A end
        printf("Parent Process of ThreadA is Done\n");

        printf("Parent Process Done\n");
        wait(NULL); // wait child to finish
    } else if (pid == 0) { // child
        pthread_create(&tid, NULL, (void *(*)(void *)) scan_in, &data); // thread A
        pthread_join(tid, NULL); // wait thread A end
        printf("Child Process of ThreadA is Done\n");

        pthread_create(&tid2, NULL, (void *(*)(void *)) write_file_out, &data); // thread B
        pthread_join(tid2, NULL); // wait thread B end
        printf("Child Process of ThreadB is Done\n");

        printf("Child Process Done\n");
        exit(0);
    } else {
        printf("Create fork fail!\n");
    }
    return 0;
}
