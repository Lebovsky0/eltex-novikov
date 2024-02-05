#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
};

void add_abonent(struct abonent** directory, int* size) {
    *size += 1;
    *directory = reinterpret_cast<abonent*>(realloc(*directory, (*size) * sizeof(struct abonent)));
    
    struct abonent new_abonent;
    printf("Введите имя абонента: ");
    scanf("%s", new_abonent.name);
    printf("Введите фамилию абонента: ");
    scanf("%s", new_abonent.second_name);
    printf("Введите телефон абонента: ");
    scanf("%s", new_abonent.tel);
    
    (*directory)[*size - 1] = new_abonent;
    
    printf("Абонент добавлен.\n");
}

void remove_abonent(struct abonent** directory, int* size) {
    if (*size == 0) {
        printf("Справочник пуст.\n");
        return;
    }
    
    char name[10];
    printf("Введите имя абонента, которого нужно удалить: ");
    scanf("%s", name);
    
    int found = 0;
    for (int i = 0; i < *size; i++) {
        if (strcmp((*directory)[i].name, name) == 0) {
            // Перемещаем элемент в конец массива
            (*directory)[i] = (*directory)[*size - 1];
            
            *size -= 1;
            *directory = static_cast<abonent*>(realloc(*directory, (*size) * sizeof(struct abonent)));
            
            found = 1;
            printf("Абонент удален.\n");
            break;
        }
    }
    
    if (!found) {
        printf("Абонент не найден.\n");
    }
}

void search_abonent(struct abonent* directory, int size) {
    if (size == 0) {
        printf("Справочник пуст.\n");
        return;
    }
    
    char name[10];
    printf("Введите имя абонента для поиска: ");
    scanf("%s", name);
    
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            printf("Имя: %s\n", directory[i].name);
            printf("Фамилия: %s\n", directory[i].second_name);
            printf("Телефон: %s\n", directory[i].tel);
            
            found = 1;
        }
    }
    
    if (!found) {
        printf("Абонент не найден.\n");
    }
}

void print_directory(struct abonent* directory, int size) {
    if (size == 0) {
        printf("Справочник пуст.\n");
        return;
    }
    
    for (int i = 0; i < size; i++) {
        printf("Абонент %d:\n", i + 1);
        printf("Имя: %s\n", directory[i].name);
        printf("Фамилия: %s\n", directory[i].second_name);
        printf("Телефон: %s\n", directory[i].tel);
        printf("\n");
    }
}

int main() {
    struct abonent* directory = NULL;
    int size = 0;
    int choice;
    
    do {
        printf("1) Добавить абонента\n");
        printf("2) Удалить абонента\n");
        printf("3) Поиск абонентов по имени\n");
        printf("4) Вывод всех записей\n");
        printf("5) Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_abonent(&directory, &size);
                break;
            case 2:
                remove_abonent(&directory, &size);
                break;
            case 3:
                search_abonent(directory, size);
                break;
            case 4:
                print_directory(directory, size);
                break;
            case 5:
                printf("Выход.\n");
                break;
            default:
                printf("Некорректный ввод.\n");
                break;
        }
        
        printf("\n");
    } while (choice != 5);
    
    free(directory);
    
    return 0;
}