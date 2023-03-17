#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <time.h>

#define SHARED_MEM_NAME "/shared_memory"

int *shared_mem;

void handle_sigint(int sig) {
    printf("Client: got SIGINT\n");
    exit(0); 
}

int main() {
    srand(time(NULL));

    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, sizeof(int)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    shared_mem = (int *) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    while (1) {
        if (*shared_mem == -1) {
            printf("Server finished\n");
            exit(0);
        }
        int num = rand() % 100 + 1;
        printf("Client: %d\n", num);
        *shared_mem = num;
        sleep(1);
    }

    return 0;
}