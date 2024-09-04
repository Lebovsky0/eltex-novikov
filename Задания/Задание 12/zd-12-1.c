#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t cpid;
    char buf;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    /* Дочерний процесс */
        close(pipefd[1]);          /* Закрываем дескриптор для записи */
        while (read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } else {            /* Родительский процесс */
        close(pipefd[0]);          /* Закрываем дескриптор для чтения */
        write(pipefd[1], "Hi!", 3);
        close(pipefd[1]);          /* Закрываем дескриптор для записи, завершая запись */
        wait(NULL);                /* Ожидаем завершения дочернего процесса */
        exit(EXIT_SUCCESS);
    }
}
