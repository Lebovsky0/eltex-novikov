#include <stdio.h>
int main(void)
{
    float x = 5.0;
    printf("x = %f, ", x);
    float y = 6.0;
    printf("y = %f\n", y);
    float *xp = &y; // было: "float *xp = &x", стало: "*xp = &y"
    float *yp = &y; // если я правильно понял, то для получения результата 12, нужно приравнять "X" к "Y"
    printf("Результат: %f\n", *xp + *yp);
}