#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int fd;
    char *msg = "Hi!";

    /* Создаем именованный канал (FIFO) */
    mkfifo(FIFO_NAME, 0666);

    /* Открываем канал на запись */
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Записываем сообщение в канал */
    write(fd, msg, sizeof(msg));

    /* Закрываем дескриптор */
    close(fd);

    return 0;
}
