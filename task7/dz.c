#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void output_content(int fd) {
    char buffer[4096];
    ssize_t size; 
    while ((size = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, size); 
    }
    if (size < 0) {
        printf("Ошибка при чтении файла.\n");
    }
}

void write_content(int fd) {
    char buffer[4096];
    ssize_t size; 
    while ((size = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        write(fd, buffer, size);
    }
    if (size < 0) {
        printf("Ошибка при чтении stdin.\n"); 
    }
}

int main(int argc, char *argv[]) {
    int fd;

    if (argc == 2) {
        fd = open(argv[1], O_RDONLY, 0);
        if (fd < 0) {
            printf("Ошибка при открытии файла.\n");
            return 1;
        }
        output_content(fd);
        close(fd);
    } 
    else if (argc == 1) { 
        write_content(STDOUT_FILENO);
    } else {
        printf("Некорректные аргументы командной строки.\n");
        return 1;
    }

    return 0;
}