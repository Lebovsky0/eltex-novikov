#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_NAME "/posix_msg_queue"
#define MSG_SIZE 128

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MSG_SIZE];

    // Настройки очереди
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Создание очереди
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == -1) {
        perror("Ошибка создания очереди");
        exit(EXIT_FAILURE);
    }

    // Отправка сообщения
    strcpy(buffer, "Hi!");
    if (mq_send(mq, buffer, MSG_SIZE, 0) == -1) {
        perror("Ошибка отправки сообщения");
        exit(EXIT_FAILURE);
    }
    printf("Сервер отправил: %s\n", buffer);

    // Получение ответа
    mq_close(mq);
    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq_receive(mq, buffer, MSG_SIZE, NULL) == -1) {
        perror("Ошибка получения сообщения");
        exit(EXIT_FAILURE);
    }
    printf("Сервер получил: %s\n", buffer);

    // Удаление очереди
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    return 0;
}
