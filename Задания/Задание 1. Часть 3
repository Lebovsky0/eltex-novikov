#include <stdio.h>

// Функция для подсчета количества единиц
int countOnes(int num) {
    int count = 0;
    
    // Пока число не станет равным нулю
    while (num != 0) {
        // Проверяем последний бит и увеличиваем счетчик, если это единица
        if (num & 1) {
            count++;
        }
        
        // Побитовый сдвиг числа вправо
        num >>= 1;
    }
    
    return count;
}

int main() {
    int num;
    printf("Введите целое положительное число: ");
    scanf("%d", &num);

    int onesCount = countOnes(num);
    printf("Количество единиц в двоичном представлении числа: %d\n", onesCount);

    return 0;
}
