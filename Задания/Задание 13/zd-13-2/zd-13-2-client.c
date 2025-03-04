#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>

#define QUEUE_KEY 5678
#define MAX_SIZE 1024

struct message {
    long type;
    char text[MAX_SIZE];
};

int msgid;
WINDOW *chat_win, *input_win;
char username[50];

// Поток для чтения сообщений
void *receive_messages(void *arg) {
    struct message msg;
    while (1) {
        if (msgrcv(msgid, &msg, sizeof(msg.text), 2, 0) != -1) {
            wprintw(chat_win, "%s\n", msg.text);
            wrefresh(chat_win);
        }
    }
    return NULL;
}

int main() {
    struct message msg;
    pthread_t thread;

    // Подключаемся к очереди (ждем сервер)
    while ((msgid = msgget(QUEUE_KEY, 0666)) == -1) {
        perror("Ожидание сервера...");
        sleep(1);
    }

    // Запуск ncurses
    initscr();
    cbreak();
    noecho();
    refresh();

    // Создаем окна
    chat_win = newwin(20, 50, 0, 0);
    input_win = newwin(3, 50, 20, 0);
    scrollok(chat_win, TRUE);

    // Запрашиваем имя
    wprintw(input_win, "Введите имя: ");
    wrefresh(input_win);
    wgetnstr(input_win, username, sizeof(username) - 1);

    // Отправляем серверу информацию о входе
    snprintf(msg.text, sizeof(msg.text), "%s подключился!", username);
    msg.type = 1;
    msgsnd(msgid, &msg, sizeof(msg.text), 0);

    // Запускаем поток приема сообщений
    pthread_create(&thread, NULL, receive_messages, NULL);

    // Ввод сообщений
    while (1) {
      wclear(input_win);
      wprintw(input_win, "Ваше сообщение: ");
    wrefresh(input_win);

    // Ограничиваем ввод, оставляя место для имени
      wgetnstr(input_win, msg.text, MAX_SIZE - 50);
      msg.text[MAX_SIZE - 50] = '\0'; // Гарантируем null-терминатор

      char temp[MAX_SIZE];

    // Ограничиваем длину итогового сообщения
      snprintf(temp, sizeof(temp), "%s: %.900s", username, msg.text);
      temp[MAX_SIZE - 1] = '\0';

      strncpy(msg.text, temp, sizeof(msg.text));
      msg.text[MAX_SIZE - 1] = '\0'; // Финальная защита

      if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
          perror("Ошибка отправки сообщения");
      }
}


    // Завершение работы
    delwin(chat_win);
    delwin(input_win);
    endwin();

    return 0;
}

