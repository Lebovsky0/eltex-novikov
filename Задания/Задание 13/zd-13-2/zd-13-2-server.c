#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_KEY 5678
#define MAX_SIZE 1024

struct message {
    long type;
    char text[MAX_SIZE];
};

int main() {
    int msgid;
    struct message msg;

    // Создаем очередь сообщений
    msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("Ошибка создания очереди");
        exit(1);
    }

    printf("Сервер запущен. Ожидание клиентов...\n");

    while (1) {
        // Получаем сообщение от клиента
        if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1) {
            perror("Ошибка получения сообщения");
            continue;
        }

        printf("Новое сообщение: %s\n", msg.text);

        // Рассылаем сообщение всем клиентам
        msg.type = 2; // Тип для всех клиентов
        if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
            perror("Ошибка отправки сообщения клиентам");
        }
    }

    // Очистка очереди (если сервер завершится)
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
