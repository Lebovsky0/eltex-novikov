#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_KEY 1234
#define MSG_SIZE 128

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    int msgid;
    struct msg_buffer message;

    // Создание очереди
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Ошибка создания очереди");
        exit(EXIT_FAILURE);
    }

    // Отправка сообщения
    message.msg_type = 1;
    strcpy(message.msg_text, "Hi!");
    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("Ошибка отправки сообщения");
        exit(EXIT_FAILURE);
    }
    printf("Сервер отправил: %s\n", message.msg_text);

    // Получение ответа
    if (msgrcv(msgid, &message, sizeof(message), 2, 0) == -1) {
        perror("Ошибка получения сообщения");
        exit(EXIT_FAILURE);
    }
    printf("Сервер получил: %s\n", message.msg_text);

    // Удаление очереди
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
