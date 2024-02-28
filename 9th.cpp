#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024 

int main() {
    int shmid;
    char *shmaddr;
    key_t key = 1234; 

    
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    
    sprintf(shmaddr, "Hello from process 1!");

   
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {  
        if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
            perror("shmat");
            exit(1);
        }

        
        printf("Message received by process 2: %s\n", shmaddr);

    
        if (shmdt(shmaddr) == -1) {
            perror("shmdt");
            exit(1);
        }
    } else {  
        wait(NULL);

       
        if (shmdt(shmaddr) == -1) {
            perror("shmdt");
            exit(1);
        }

       
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    }

    return 0;
}

