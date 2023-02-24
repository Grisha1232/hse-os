#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

const int buf_size = 30;

int main(int argc, char *argv[]) {
    char *input = argv[1];
    char *output = argv[2];
    int fd;
    char buffer[buf_size];
    ssize_t read_bytes;
    if ((fd = open(input, O_RDONLY)) < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }
    read_bytes = read(fd, buffer, buf_size);
    if (read_bytes == -1) {
        printf("Can\'t write this file\n");
        exit(-1);
    }
    buffer[read_bytes] = '\0';
    if (close(fd) < 0) {
        printf("Can\'t close file\n");
    }

    if ((fd = open(output, O_WRONLY | O_CREAT, 0666)) < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }
    ssize_t size = write(fd, buffer, buf_size);
    if (size != buf_size) {
        printf("Can\'t write all string\n");
        exit(-1);
    }
    if (close(fd) < 0) {
        printf("Can\'t close file\n");
    }

    return 0;
}