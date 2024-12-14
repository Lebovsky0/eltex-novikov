#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234
#define MSG_SIZE 128

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    int msgid;
    struct msg_buffer message;

    // Подключение к очереди
    msgid = msgget(MSG_KEY, 0666);
    if (msgid == -1) {
        perror("Ошибка подключения к очереди");
        exit(EXIT_FAILURE);
    }

    // Чтение сообщения
    if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
        perror("Ошибка чтения сообщения");
        exit(EXIT_FAILURE);
    }
    printf("Клиент получил: %s\n", message.msg_text);

    // Ответ серверу
    message.msg_type = 2;
    strcpy(message.msg_text, "Hello!");
    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("Ошибка отправки ответа");
        exit(EXIT_FAILURE);
    }
    printf("Клиент отправил: %s\n", message.msg_text);

    return 0;
}
