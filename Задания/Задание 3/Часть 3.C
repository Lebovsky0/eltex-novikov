#include <stdio.h>

int main(void)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // Определяем массив

    int *ptr = arr;  // Инициализацируем указатель на начало массива

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", *ptr);  // Выводим значение, на которое указывает указатель
        ptr++;  // Переходим к следующему элементу массива с помощью арифметики указателей
    }

    printf("\n");

    return 0;
}