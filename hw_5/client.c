#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "fifo"

int main() {
    int fd;
    char buf[256];
    while (1) {
        fd = open(FIFO_NAME, O_WRONLY);
        printf("Введите сообщение: ");
        scanf("%s", buf);
        write(fd, buf, strlen(buf) + 1);
        close(fd);
    }
    return 0;
}
