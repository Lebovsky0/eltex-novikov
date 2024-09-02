#include <ncurses.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

#define MAX_FILES 1024

void draw_panel(WINDOW *win, int highlight, char *path, char **files, int n_files);
void list_files(const char *path, char **files, int *n_files);
void create_new_file(const char *filename);
void read_file_content(const char *filename);
void create_new_folder(const char *path);
void draw_help_bar(WINDOW *win);

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int highlight[2] = {0, 0};
    int current_panel = 0;
    char *paths[2] = {".", "."};
    char *files[2][MAX_FILES];
    int n_files[2] = {0, 0};

    for (int i = 0; i < 2; ++i) {
        list_files(paths[i], files[i], &n_files[i]);
    }

    WINDOW *left_win = newwin(LINES - 2, COLS / 2, 0, 0);  // Уменьшили высоту на 2 строки
    WINDOW *right_win = newwin(LINES - 2, COLS / 2, 0, COLS / 2);  // Уменьшили высоту на 2 строки
    WINDOW *help_bar = newwin(1, COLS, LINES - 1, 0);  // Добавили новое окно для подсказки

    while (1) {
        draw_panel(left_win, highlight[0], paths[0], files[0], n_files[0]);
        draw_panel(right_win, highlight[1], paths[1], files[1], n_files[1]);
        draw_help_bar(help_bar);  // Рисуем панель подсказок

        int ch = getch();
        switch (ch) {
            case KEY_UP:
                if (highlight[current_panel] > 0) --highlight[current_panel];
                break;
            case KEY_DOWN:
                if (highlight[current_panel] < n_files[current_panel] - 1) ++highlight[current_panel];
                break;
            case '\t':
                current_panel = 1 - current_panel;
                break;
            case 'r':
                if (n_files[current_panel] > 0) {
                    char filepath[PATH_MAX];
                    snprintf(filepath, PATH_MAX, "%s/%s", paths[current_panel], files[current_panel][highlight[current_panel]]);
                    read_file_content(filepath);
                }
                break;
            case 'w':
                echo();
                char new_filename[256];
                mvprintw(LINES - 1, 0, "Enter new file name: ");
                getstr(new_filename);
                noecho();
                create_new_file(new_filename);
                list_files(paths[current_panel], files[current_panel], &n_files[current_panel]);
                break;
            case 'c':
                create_new_folder(paths[current_panel]);
                list_files(paths[current_panel], files[current_panel], &n_files[current_panel]);
                break;
            case '\n':
                if (n_files[current_panel] > 0) {
                    char filepath[PATH_MAX];
                    snprintf(filepath, PATH_MAX, "%s/%s", paths[current_panel], files[current_panel][highlight[current_panel]]);
                    struct stat path_stat;
                    stat(filepath, &path_stat);
                    if (S_ISDIR(path_stat.st_mode)) {
                        paths[current_panel] = strdup(filepath);
                        list_files(paths[current_panel], files[current_panel], &n_files[current_panel]);
                        highlight[current_panel] = 0;
                    } else {
                        read_file_content(filepath);
                    }
                }
                break;
            case 'q':
                endwin();
                exit(0);
        }
    }

    endwin();
    return 0;
}

void draw_panel(WINDOW *win, int highlight, char *path, char **files, int n_files) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", path);

    for (int i = 0; i < n_files; ++i) {
        if (i == highlight) {
            wattron(win, A_REVERSE);
        }
        mvwprintw(win, i + 1, 1, "%s", files[i]);
        wattroff(win, A_REVERSE);
    }

    wrefresh(win);
}

void draw_help_bar(WINDOW *win) {
    werase(win);
    mvwprintw(win, 0, 0, "F1: Help | Tab: Switch Panel | Up/Down: Navigate | Enter: Open | w: New File | c: New Folder | r: Read File | q: Quit");
    wrefresh(win);
}

void list_files(const char *path, char **files, int *n_files) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    *n_files = 0;
    while ((entry = readdir(dir)) != NULL) {
        files[*n_files] = strdup(entry->d_name);
        (*n_files)++;
    }
    closedir(dir);
}

void create_new_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    mvprintw(LINES - 1, 0, "Enter content for the new file (end with Ctrl+D): ");
    refresh();
    char ch;
    while ((ch = getch()) != 4) {  // Ctrl+D to end input
        fputc(ch, file);
    }
    fclose(file);
    mvprintw(LINES - 1, 0, "                                      "); // Clear the line
    refresh();
}

void read_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    clear();

    if (file_size > 0) {
        char *content = (char *)malloc(file_size + 1);
        fread(content, 1, file_size, file);
        content[file_size] = '\0';
        
        bool is_text = true;
        for (long i = 0; i < file_size; ++i) {
            if ((unsigned char)content[i] > 127) {
                is_text = false;
                break;
            }
        }

        if (is_text) {
            printw("%s", content);
        } else {
            printw("The file contains non-text data and cannot be displayed.");
        }

        free(content);
    } else {
        printw("The file is empty.");
    }

    refresh();
    getch();
    fclose(file);
}

void create_new_folder(const char *path) {
    char folder_name[256];
    echo();
    mvprintw(LINES - 1, 0, "Enter new folder name: ");
    getstr(folder_name);
    noecho();

    char new_path[PATH_MAX];
    snprintf(new_path, PATH_MAX, "%s/%s", path, folder_name);
    if (mkdir(new_path, 0755) == -1) {
        perror("Error creating directory");
    }
}
