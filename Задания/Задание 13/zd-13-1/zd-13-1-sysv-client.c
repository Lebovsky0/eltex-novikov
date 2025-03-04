#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_KEY 1234
#define MAX_SIZE 1024

struct message {
    long type;
    char text[MAX_SIZE];
};

int main() {
    int msgid;
    struct message msg;

    // Подключаемся к очереди сообщений (ожидание, если сервер еще не создал)
    while ((msgid = msgget(QUEUE_KEY, 0666)) == -1) {
        perror("Ожидание создания очереди сервером...");
        sleep(1);
    }

    printf("Клиент: подключился к очереди сообщений.\n");

    // Отправляем серверу уведомление о подключении
    msg.type = 1;  // Сообщение для сервера
    strcpy(msg.text, "Client connected");
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
        perror("Ошибка отправки запроса серверу");
        exit(1);
    }

    // Ждем сообщение от сервера
    if (msgrcv(msgid, &msg, sizeof(msg.text), 2, 0) == -1) {
        perror("Ошибка получения сообщения от сервера");
        exit(1);
    }
    printf("Клиент: получено сообщение '%s'\n", msg.text);

    // Отправляем ответ серверу
    msg.type = 3;  // Сообщение для сервера
    strcpy(msg.text, "Hello!");
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
        perror("Ошибка отправки ответа серверу");
        exit(1);
    }
    printf("Клиент: отправил сообщение '%s'\n", msg.text);

    return 0;
}
