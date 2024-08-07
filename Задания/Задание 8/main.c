#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "calc.h"

int main() {
    void *handle;
    int (*add)(int, int);
    int (*sub)(int, int);
    int (*mul)(int, int);
    int (*divide)(int, int);
    char *error;

    // Открытие динамической библиотеки
    handle = dlopen("./libcalc.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    // Получение указателей на функции
    add = dlsym(handle, "add");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    sub = dlsym(handle, "sub");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    mul = dlsym(handle, "mul");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    divide = dlsym(handle, "divide");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    int choice, num1, num2, result;

    do {
        printf("1) Сложение\n");
        printf("2) Вычитание\n");
        printf("3) Умножение\n");
        printf("4) Деление\n");
        printf("5) Выход\n");
        printf("Выберите операцию (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите два числа: ");
                scanf("%d %d", &num1, &num2);
                result = add(num1, num2);
                printf("Результат: %d\n", result);
                break;
            case 2:
                printf("Введите два числа: ");
                scanf("%d %d", &num1, &num2);
                result = sub(num1, num2);
                printf("Результат: %d\n", result);
                break;
            case 3:
                printf("Введите два числа: ");
                scanf("%d %d", &num1, &num2);
                result = mul(num1, num2);
                printf("Результат: %d\n", result);
                break;
            case 4:
                printf("Введите два числа: ");
                scanf("%d %d", &num1, &num2);
                if (num2 == 0) {
                    printf("Деление на ноль невозможно.\n");
                } else {
                    result = divide(num1, num2);
                    printf("Результат: %d\n", result);
                }
                break;
            case 5:
                printf("Программа завершена.\n");
                break;
            default:
                printf("Некорректный выбор. Попробуйте снова.\n");
        }
    } while (choice != 5);

    // Закрытие динамической библиотеки
    dlclose(handle);

    return 0;
}
