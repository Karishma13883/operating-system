#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define SHM_SIZE 1024  
int main() {
    int shmid;
    key_t key;
    char *shm_ptr;
    char *message = "Hello, shared memory!";
    key = ftok("shmfile", 'R');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    strcpy(shm_ptr, message);
    printf("Message written to shared memory: %s\n", shm_ptr);
    sleep(5);
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    return 0;
}

