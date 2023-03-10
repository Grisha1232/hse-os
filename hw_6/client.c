#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

#define SHM_SIZE 1024

int *data_int_signal;

int main() {
    srand(time(NULL));
    key_t key = ftok("server.c", 'R');
    int shmid = shmget(key, SHM_SIZE, 0644);
    char *data = shmat(shmid, (void *) 0, 0);
    int *data_int = (int *) data;

    key_t key_signal = ftok("server_signal.c", 'R');
    int shmid_signal = shmget(key_signal, SHM_SIZE, 0640 | IPC_CREAT);
    char *data_signal = shmat(shmid_signal, (void *) 0, 0);
    data_int_signal = (int *) data_signal;
    *data_int_signal = 0;

    while (1) {
        if (*data_int_signal == 1) {
            printf("Server finished\n");
            exit(0);
        }
        int num = rand() % 100;
        printf("Client: %d\n", num);
        *data_int = num;
        sleep(1);
    }

    return 0;
}
