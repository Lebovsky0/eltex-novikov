#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *fifo = "/tmp/myfifo";
    char message[] = "Hi!";

    mkfifo(fifo, 0666);

    int fd = open(fifo, O_WRONLY);
    write(fd, message, strlen(message) + 1);
    close(fd);

    printf("Сервер отправил сообщение: %s\n", message);

    return 0;
}
