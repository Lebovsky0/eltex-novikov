#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_NAME "/posix_msg_queue"
#define MAX_SIZE 1024

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];

    // Подключение к очереди (цикл ожидания, если сервер еще не создал ее)
    while ((mq = mq_open(QUEUE_NAME, O_RDWR)) == (mqd_t)-1) {
        perror("Ожидание создания очереди сервером...");
        sleep(1);
    }

    printf("Клиент: подключился к очереди сообщений.\n");

    // Отправляем запрос серверу (факт подключения)
    snprintf(buffer, sizeof(buffer), "Client connected");
    if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
        perror("Ошибка отправки запроса серверу");
        mq_close(mq);
        exit(1);
    }

    // Читаем сообщение от сервера
    if (mq_receive(mq, buffer, MAX_SIZE, NULL) == -1) {
        perror("Ошибка чтения сообщения от сервера");
        mq_close(mq);
        exit(1);
    }
    printf("Клиент: получено сообщение '%s'\n", buffer);

    // Отправляем ответ серверу
    snprintf(buffer, sizeof(buffer), "Hello!");
    if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
        perror("Ошибка отправки ответа серверу");
        mq_close(mq);
        exit(1);
    }
    printf("Клиент: отправил сообщение '%s'\n", buffer);

    // Закрытие очереди
    mq_close(mq);
    return 0;
}

