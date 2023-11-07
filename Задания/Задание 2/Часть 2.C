#include <stdio.h>

void reverseArray(int arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int n;
    printf("Введите размер массива: ");
    scanf("%d", &n);

    int arr[n];
    printf("Введите элементы массива: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Массив в обратном порядке: ");
    reverseArray(arr, n);

    return 0;
}