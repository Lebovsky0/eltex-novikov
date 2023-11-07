#include <stdio.h>

void fillMatrix(int matrix[][100], int n) {
    int value = 1;
    int startRow = 0, endRow = n - 1;
    int startCol = 0, endCol = n - 1;

    while (startRow <= endRow && startCol <= endCol) {
        // Заполнение верхней строки
        for (int i = startCol; i <= endCol; i++) {
            matrix[startRow][i] = value++;
        }
        startRow++;

        // Заполнение последнего столбца
        for (int i = startRow; i <= endRow; i++) {
            matrix[i][endCol] = value++;
        }
        endCol--;

        // Заполнение нижней строки
        for (int i = endCol; i >= startCol; i--) {
            matrix[endRow][i] = value++;
        }
        endRow--;

        // Заполнение первого столбца
        for (int i = endRow; i >= startRow; i--) {
            matrix[i][startCol] = value++;
        }
        startCol++;
    }
}

int main() {
    int n;
    printf("Введите размер матрицы: ");
    scanf("%d", &n);

    int matrix[100][100];

    fillMatrix(matrix, n);

    // Вывод матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}