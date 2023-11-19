#include <stdio.h>
#include <string.h>

#define MAX_ABONENTS 100
#define NAME_LENGTH 10
#define TEL_LENGTH 10

struct abonent {
    char name[NAME_LENGTH];
    char second_name[NAME_LENGTH];
    char tel[TEL_LENGTH];
};

// Функция для добавления абонента в справочник
void addAbonent(struct abonent abonents[], int *count) {
    if (*count >= MAX_ABONENTS) {
        printf("Справочник переполнен. Невозможно добавить нового абонента.\n");
        return;
    }
    
    struct abonent newAbonent;
    
    printf("Введите имя абонента: ");
    scanf("%s", newAbonent.name);
    
    printf("Введите фамилию абонента: ");
    scanf("%s", newAbonent.second_name);
    
    printf("Введите номер телефона абонента: ");
    scanf("%s", newAbonent.tel);
    
    abonents[*count] = newAbonent;
    (*count)++;
    
    printf("Абонент успешно добавлен.\n");
}

// Функция для удаления абонента из справочника
void deleteAbonent(struct abonent abonents[], int *count) {
    if (*count == 0) {
        printf("Справочник пуст. Нет абонентов для удаления.\n");
        return;
    }
    
    char nameToDelete[NAME_LENGTH];
    
    printf("Введите имя абонента, которого хотите удалить: ");
    scanf("%s", nameToDelete);
    
    int i;
    int deleted = 0;
    
    for (i = 0; i < *count; i++) {
        if (strcmp(abonents[i].name, nameToDelete) == 0) {
            memset(&abonents[i], 0, sizeof(struct abonent));
            deleted = 1;
            break;
        }
    }
    
    if (deleted) {
        printf("Абонент успешно удален.\n");
    } else {
        printf("Абонент с таким именем не найден.\n");
    }
}

// Функция для поиска абонента по имени
void searchAbonent(struct abonent abonents[], int count) {
    if (count == 0) {
        printf("Справочник пуст. Нет абонентов для поиска.\n");
        return;
    }
    
    char nameToSearch[NAME_LENGTH];
    
    printf("Введите имя абонента для поиска: ");
    scanf("%s", nameToSearch);
    
    int i;
    int found = 0;
    
    printf("Результаты поиска:\n");
    
    for (i = 0; i < count; i++) {
        if (strcmp(abonents[i].name, nameToSearch) == 0) {
            printf("Имя: %s\n", abonents[i].name);
            printf("Фамилия: %s\n", abonents[i].second_name);
            printf("Номер телефона: %s\n", abonents[i].tel);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Абонент с таким именем не найден.\n");
    }
}

// Функция для вывода всех записей
void printAllAbonents(struct abonent abonents[], int count) {
    if (count == 0) {
        printf("Справочник пуст. Нет абонентов для вывода.\n");
        return;
    }
    
    int i;
    
    printf("Список всех абонентов:\n");
    
    for (i = 0; i < count; i++) {
        if (abonents[i].name[0] != '\0') {
            printf("Имя: %s\n", abonents[i].name);
            printf("Фамилия: %s\n", abonents[i].second_name);
            printf("Номер телефона: %s\n", abonents[i].tel);
        }
    }
}

int main() {
    struct abonent abonents[MAX_ABONENTS];
    int count = 0;
    
    int choice;
    
    do {
        printf("\nМеню:\n");
        printf("1) Добавить абонента\n");
        printf("2) Удалить абонента\n");
        printf("3) Поиск абонентов по имени\n");
        printf("4) Вывод всех записей\n");
        printf("5) Выход\n");
        printf("Выберите пункт меню: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addAbonent(abonents, &count);
                break;
            case 2:
                deleteAbonent(abonents, &count);
                break;
            case 3:
                searchAbonent(abonents, count);
                break;
            case 4:
                printAllAbonents(abonents, count);
                break;
            case 5:
                printf("Программа завершена.\n");
                break;
            default:
                printf("Неверный выбор. Пожалуйста, выберите пункт меню от 1 до 5.\n");
                break;
        }
    } while (choice != 5);
    
    return 0;
}