#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME "/posix_msg_queue"
#define MSG_SIZE 128

int main() {
    mqd_t mq;
    char buffer[MSG_SIZE];

    // Подключение к очереди
    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == -1) {
        perror("Ошибка подключения к очереди");
        exit(EXIT_FAILURE);
    }

    // Чтение сообщения
    if (mq_receive(mq, buffer, MSG_SIZE, NULL) == -1) {
        perror("Ошибка чтения сообщения");
        exit(EXIT_FAILURE);
    }
    printf("Клиент получил: %s\n", buffer);

    // Ответ серверу
    mq_close(mq);
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    strcpy(buffer, "Hello!");
    if (mq_send(mq, buffer, MSG_SIZE, 0) == -1) {
        perror("Ошибка отправки ответа");
        exit(EXIT_FAILURE);
    }
    printf("Клиент отправил: %s\n", buffer);

    mq_close(mq);
    return 0;
}
