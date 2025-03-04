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

    // Создаем очередь сообщений
    msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("Ошибка создания очереди");
        exit(1);
    }

    printf("Сервер: ожидаю подключение клиента...\n");

    // Ожидаем сообщение от клиента (подключение)
    if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1) {
        perror("Ошибка получения сообщения");
        msgctl(msgid, IPC_RMID, NULL);
        exit(1);
    }

    printf("Сервер: клиент подключился, отправляю сообщение...\n");

    // Отправляем сообщение клиенту
    msg.type = 2;  // Тип сообщения для клиента
    strcpy(msg.text, "Hi!");
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
        perror("Ошибка отправки сообщения");
        msgctl(msgid, IPC_RMID, NULL);
        exit(1);
    }
    printf("Сервер: отправлено сообщение '%s'\n", msg.text);

    // Ждем ответ от клиента
    if (msgrcv(msgid, &msg, sizeof(msg.text), 3, 0) == -1) {
        perror("Ошибка получения ответа");
        msgctl(msgid, IPC_RMID, NULL);
        exit(1);
    }

    printf("Сервер: получено сообщение от клиента '%s'\n", msg.text);

    // Удаляем очередь
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
