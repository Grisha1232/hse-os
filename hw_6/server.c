#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>

#define SHM_SIZE 1024

int shmid;
int shmid_signal;
int *data_int;
int *data_int_signal;

void handle_sigint(int sig) {
    printf("Server finished\n");
    shmctl(shmid, IPC_RMID, NULL);
    *data_int_signal = 1;
    exit(0);
}

int main() {
    key_t key = ftok("server.c", 'R');
    shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT);
    char *data = shmat(shmid, (void *)0, 0);
    data_int = (int *)data;

    key_t key_signal = ftok("server_signal.c", 'R');
    shmid_signal = shmget(key_signal, SHM_SIZE, 0640 | IPC_CREAT);
    char *data_signal = shmat(shmid_signal, (void *)0, 0);
    data_int_signal = (int *)data_signal;

    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    while(1) {
        if(*data_int != 0) {
            printf("Server: %d\n", *data_int);
            *data_int = 0;
        }
    }

    return 0;
}
