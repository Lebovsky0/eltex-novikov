#include <stdio.h>

int main() {
    int n;
    printf("Введите размер матрицы: ");
    scanf("%d", &n);

    int matrix[n][n];

    // Заполнение матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) {
                matrix[i][j] = 0;  // Заполнение верхнего треугольника нулями
            } else {
                matrix[i][j] = 1;  // Заполнение нижнего треугольника единицами
            }
        }
    }

    // Вывод матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}