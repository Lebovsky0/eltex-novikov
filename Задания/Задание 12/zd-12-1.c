#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> // Подключаем заголовок для функции wait

int main() {
    int pipefd[2];
    pid_t pid;
    char message[] = "Hi!";
    char buffer[10];

    if (pipe(pipefd) == -1) {
        perror("Ошибка при создании канала");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("Ошибка при создании процесса");
        exit(1);
    } else if (pid == 0) {
        // Дочерний процесс
        close(pipefd[1]); // Закрываем дескриптор для записи
        read(pipefd[0], buffer, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0'; // Гарантируем завершающий нулевой символ
        printf("Дочерний процесс получил сообщение: %s\n", buffer);
        close(pipefd[0]);
    } else {
        // Родительский процесс
        close(pipefd[0]); // Закрываем дескриптор для чтения
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
        wait(NULL); // Ожидаем завершения дочернего процесса
    }

    return 0;
}
