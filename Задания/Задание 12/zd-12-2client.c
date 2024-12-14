#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *fifo = "/tmp/myfifo";
    char buffer[10];

    int fd = open(fifo, O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    printf("Клиент получил сообщение: %s\n", buffer);
    close(fd);

    unlink(fifo); // Удаляем именованный канал

    return 0;
}
