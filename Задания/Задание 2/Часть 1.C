#include <stdio.h>

void printMatrix(int n) {
    int matrix[n][n];
    int count = 1;

    // Заполнение матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = count++;
        }
    }

    // Вывод матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Введите число N: ");
    scanf("%d", &n);

    printMatrix(n);

    return 0;
}