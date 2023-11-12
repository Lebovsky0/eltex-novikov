#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

char *findSubstring(const char *str, const char *substr) // Эта функция принимает две строки str и substr и ищет подстроку substr
{
    int strLen = strlen(str);
    int substrLen = strlen(substr);

    for (int i = 0; i <= strLen - substrLen; i++)
    {
        int j;
        for (j = 0; j < substrLen; j++)
        {
            if (str[i + j] != substr[j])
                break;
        }
        if (j == substrLen)
            return (char *)(str + i);
    }

    return NULL;
}

int main(void)
{
    char str[MAX_LENGTH];
    char substr[MAX_LENGTH];

    printf("Введите строку: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';  // Удаляем символ новой строки

    printf("Введите подстроку: ");
    fgets(substr, sizeof(substr), stdin);
    substr[strcspn(substr, "\n")] = '\0';  // Удаляем символ новой строки

    char *result = findSubstring(str, substr);

    if (result != NULL)
        printf("Подстрока найдена: %s\n", result);
    else
        printf("Подстрока не найдена\n");

    return 0;
}