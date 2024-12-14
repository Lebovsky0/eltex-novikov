#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void execute_command(char *command) {
    char *args[MAX_COMMAND_LENGTH / 2 + 1]; // предполагаем, что аргументы разделены пробелами
    char *token = strtok(command, " ");
    int i = 0;

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (execvp(args[0], args) == -1) {
        perror("Ошибка при выполнении команды");
        exit(1);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *commands[2];

    while (1) {
        printf("Введите команду (или 'exit' для выхода): ");
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = 0; // Убираем символ переноса строки

        if (strcmp(command, "exit") == 0) {
            break;
        }

        int i = 0;
        commands[i++] = strtok(command, "|");

        while ((commands[i] = strtok(NULL, "|")) != NULL && i < 2) {
            i++;
        }

        if (i == 1) {
            // Обычная команда без конвейера
            pid_t pid = fork();
            if (pid == 0) {
                execute_command(commands[0]);
            } else {
                wait(NULL);
            }
        } else if (i == 2) {
            // Команда с конвейером
            int pipefd[2];
            pipe(pipefd);
            pid_t pid1 = fork();

            if (pid1 == 0) {
                // Первый процесс
                close(pipefd[0]); // Закрываем входное направление канала
                dup2(pipefd[1], STDOUT_FILENO); // Перенаправляем stdout в канал
                close(pipefd[1]);
                execute_command(commands[0]);
            }

            pid_t pid2 = fork();

            if (pid2 == 0) {
                // Второй процесс
                close(pipefd[1]); // Закрываем выходное направление канала
                dup2(pipefd[0], STDIN_FILENO); // Перенаправляем stdin в канал
                close(pipefd[0]);
                execute_command(commands[1]);
            }

            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }

    return 0;
}
