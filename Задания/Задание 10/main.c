#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void task1() {
    printf("=== Задание 1 ===\n");

    pid_t pid;

    pid = fork(); // создаем новый процесс

    if (pid < 0) {
        perror("Ошибка при создании процесса");
        exit(1);
    } else if (pid == 0) {
        // Дочерний процесс
        printf("Дочерний процесс: pid = %d, ppid = %d\n", getpid(), getppid());
        exit(0);
    } else {
        // Родительский процесс
        printf("Родительский процесс: pid = %d, ppid = %d\n", getpid(), getppid());
        
        int status;
        waitpid(pid, &status, 0); // ждем завершения дочернего процесса
        printf("Статус завершения дочернего процесса: %d\n", WEXITSTATUS(status));
    }
}

void task2() {
    printf("=== Задание 2 ===\n");

    int num_processes = 5;
    int max_depth = 2;

    void create_process(int num, int depth) {
        if (num > 0) {
            pid_t pid = fork();
            if (pid < 0) {
                perror("Ошибка при создании процесса");
                exit(1);
            } else if (pid == 0) {
                // Дочерний процесс
                printf("Процесс %d: pid = %d, ppid = %d\n", num, getpid(), getppid());
                create_process(num - 1, depth - 1);
                exit(0);
            } else {
                // Родительский процесс
                wait(NULL); // ждем завершения дочернего процесса
            }
        }
    }

    create_process(num_processes, max_depth);
}

void task3() {
    printf("=== Задание 3 ===\n");

    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("Введите команду (или 'exit' для выхода): ");
        fgets(command, sizeof(command), stdin);

        // Убираем символ переноса строки, если он есть
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Ошибка при создании процесса");
            exit(1);
        } else if (pid == 0) {
            // Дочерний процесс
            execlp(command, command, NULL); // выполняем команду
            perror("Ошибка при выполнении команды");
            exit(1);
        } else {
            // Родительский процесс
            int status;
            waitpid(pid, &status, 0); // ждем завершения дочернего процесса
            printf("Команда завершилась с кодом: %d\n", WEXITSTATUS(status));
        }
    }
}

int main() {
    int choice;

    printf("Выберите задание (1, 2 или 3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        default:
            printf("Некорректный выбор задания.\n");
            break;
    }

    return 0;
}
