#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LEN 1024
#define MAX_ARGS 64

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    char *token = strtok(cmd, " \t\n");
    int i = 0;

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    execvp(args[0], args);
    perror("execvp");
    exit(EXIT_FAILURE);
}

void parse_and_execute(char *line) {
    int pipefd[2];
    pid_t pid;
    char *cmd1, *cmd2;
    char *pipe_pos = strchr(line, '|');

    if (pipe_pos != NULL) {
        *pipe_pos = '\0';   // Разделяем строку по символу '|'
        cmd1 = line;
        cmd2 = pipe_pos + 1;

        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {   // Дочерний процесс (выполняет первую команду)
            close(pipefd[0]);   // Закрываем дескриптор для чтения
            dup2(pipefd[1], STDOUT_FILENO);  // Перенаправляем stdout в канал
            close(pipefd[1]);
            execute_command(cmd1);
        } else {           // Родительский процесс (выполняет вторую команду)
            close(pipefd[1]);   // Закрываем дескриптор для записи
            dup2(pipefd[0], STDIN_FILENO);   // Перенаправляем stdin из канала
            close(pipefd[0]);
            wait(NULL);         // Ожидаем завершения дочернего процесса
            execute_command(cmd2);
        }
    } else {
        execute_command(line);  // Если конвейера нет, просто выполняем команду
    }
}

int main() {
    char line[MAX_COMMAND_LEN];

    while (1) {
        printf("shell> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        if (strncmp(line, "exit", 4) == 0) {
            break;
        }

        parse_and_execute(line);
    }

    return 0;
}
