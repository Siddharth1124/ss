#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_KEY 0x1234  // Define a unique key for shared memory
#define SHM_SIZE 1024   // Size of shared memory segment

int main() {
    int shmid;
    char *shared_memory;

    // Create a shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the server's address space
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Write a message to the shared memory segment
    const char *message = "Hello from the server!";
    strncpy(shared_memory, message, SHM_SIZE);

    printf("Server: Message written to shared memory: %s\n", message);

    // Detach from the shared memory segment
    shmdt(shared_memory);

    return 0;
}
