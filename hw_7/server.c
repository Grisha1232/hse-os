#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>

#define SHARED_MEM_NAME "/shared_memory"

int *shared_mem;

void handle_sigint(int sig) {
    printf("Server: got SIGINT\n");

    *shared_mem = -1;

    if (munmap(shared_mem, sizeof(int)) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink(SHARED_MEM_NAME) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    exit(0); 
}

int main() {
    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open error");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(shm_fd, sizeof(int)) == -1) {
        perror("ftruncate error");
        exit(EXIT_FAILURE);
    }

    shared_mem = (int *) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (shared_mem == MAP_FAILED) {
        perror("mmap error");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    while (1) {
        if (*shared_mem != 0) {
            printf("Server: %d\n", *shared_mem);
            *shared_mem = 0;
        }
    }

    return 0;
}