#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "fifo"

int main(int argc, char *argv[])
{
    int n, fd;
    char buffer[256];
    umask(0);
    mknod(FIFO_NAME, S_IFIFO | 0666, 0);

    while (1)
    {
        fd = open(FIFO_NAME, O_RDONLY);
        n = read(fd, buffer, 256);
        printf("Полученное сообщение: %s\n", buffer);
        close(fd);
    }
    return 0;
}