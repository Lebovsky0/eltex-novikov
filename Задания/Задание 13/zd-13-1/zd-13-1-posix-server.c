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
    struct mq_attr attr;
    char buffer[MAX_SIZE];

    // Настройка атрибутов очереди
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // Удаляем очередь, если она уже существует
    mq_unlink(QUEUE_NAME);

    // Создание очереди сообщений
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == -1) {
        perror("Ошибка создания очереди");
        exit(1);
    }

    printf("Сервер: ожидаю подключение клиента...\n");

    // Ждем, пока клиент подключится (цикл на проверку)
    while (1) {
        if (mq_getattr(mq, &attr) == -1) {
            perror("Ошибка получения атрибутов очереди");
            mq_close(mq);
            mq_unlink(QUEUE_NAME);
            exit(1);
        }
        if (attr.mq_curmsgs > 0) break; // Ждем появления сообщения
        usleep(100000); // Спим 100 мс, чтобы не грузить процессор
    }

    // Получаем запрос от клиента (факт подключения)
    if (mq_receive(mq, buffer, MAX_SIZE, NULL) == -1) {
        perror("Ошибка чтения сообщения");
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        exit(1);
    }

    printf("Сервер: клиент подключился, отправляю сообщение...\n");

    // Отправка сообщения клиенту
    snprintf(buffer, sizeof(buffer), "Hi!");
    if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
        perror("Ошибка отправки сообщения");
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        exit(1);
    }
    printf("Сервер: отправлено сообщение '%s'\n", buffer);

    // Ждем ответа от клиента
    if (mq_receive(mq, buffer, MAX_SIZE, NULL) == -1) {
        perror("Ошибка получения ответа");
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        exit(1);
    }

    printf("Сервер: получено сообщение от клиента '%s'\n", buffer);

    // Закрытие и удаление очереди
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}

