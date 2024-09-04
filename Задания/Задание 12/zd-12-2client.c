#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int fd;
    char buf[10];

    /* Открываем канал на чтение */
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Читаем сообщение из канала */
    read(fd, buf, sizeof(buf));
    printf("Received: %s\n", buf);

    /* Закрываем дескриптор */
    close(fd);

    /* Удаляем именованный канал */
    unlink(FIFO_NAME);

    return 0;
}
