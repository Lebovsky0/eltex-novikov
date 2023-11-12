#include <stdio.h>

void changeThirdByte(int* num, int newByte) {
    unsigned char* bytePtr = (unsigned char*)num;  // Приведение указателя на int к указателю на unsigned char

    // Перемещаем указатель на третий байт
    bytePtr += 2;

    // Заменяем значение третьего байта
    *bytePtr = (unsigned char)newByte;
}

int main() {
    int num, newByte;

    printf("Введите целое число: ");
    scanf("%d", &num);

    printf("Введите новое значение для третьего байта: ");
    scanf("%d", &newByte);

    changeThirdByte(&num, newByte);

    printf("Измененное число: %d\n", num);

    return 0;
}