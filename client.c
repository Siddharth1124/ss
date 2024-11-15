#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_KEY 0x1234  // Same key as the server
#define SHM_SIZE 1024   // Size of shared memory segment

int main() {
    int shmid;
    char *shared_memory;

    // Locate the shared memory segment created by the server
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the client's address space
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Read and display the message from the shared memory segment
    printf("Client: Message read from shared memory: %s\n", shared_memory);

    // Detach from the shared memory segment
    shmdt(shared_memory);

    return 0;
}
