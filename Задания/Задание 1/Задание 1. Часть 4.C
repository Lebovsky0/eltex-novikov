#include <stdio.h>

// Функция для замены значения третьего бита
int replaceThirdBit(int num, int bit) {
    // Маска для получения третьего бита
    int mask = 1 << 2;
    
    // Если третий бит исходного числа равен 1, устанавливаем его в 0
    if (num & mask) {
        num &= ~mask;
    }
    
    // Если третий бит, который нужно вставить, равен 1, устанавливаем его в 1
    if (bit) {
        num |= mask;
    }
    
    return num;
}

int main() {
    int num;
    printf("Введите целое положительное число: ");
    scanf("%d", &num);
    
    int bit;
    printf("Введите значение третьего бита (0 или 1): ");
    scanf("%d", &bit);

    int result = replaceThirdBit(num, bit);
    printf("Число после замены третьего бита: %d\n", result);

    return 0;
}
