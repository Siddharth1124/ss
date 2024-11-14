#include <stdio.h>

#define MAX 10

int allocation[MAX][MAX], need[MAX][MAX], Max[MAX][MAX], available[MAX];
int n, m;

void calculate_need() {
    // Calculate the need matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = Max[i][j] - allocation[i][j];
        }
    }
}

int is_safe() {
    int work[MAX];
    int completed[MAX] = {0};
    int safe_sequence[MAX];
    int index = 0;

    // Initialize work array as available resources
    for(int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    for(int k = 0; k < n; k++) {
        int safe = 0;
        for(int i = 0; i < n; i++) {
            if(!completed[i]) {
                int j;
                // Check if process can be completed (its need <= work)
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        break;
                    }
                }

                if(j == m) {  // All needs can be satisfied
                    // Process can be completed, so add its allocation to work
                    for(int x = 0; x < m; x++) {
                        work[x] += allocation[i][x];
                    }
                    safe_sequence[index++] = i;
                    completed[i] = 1;
                    safe = 1;
                }
            }
        }
        if(safe == 0) {
            printf("System is not in safe state\n");
            return 0;
        }
    }

    // If we reach here, a safe sequence is found
    printf("System is in safe state\n");
    printf("Safe sequence: ");
    for(int i = 0; i < index; i++) {
        printf("P%d ", safe_sequence[i]);
        if(i < index - 1) printf("-> ");
    }
    printf("\n");

    return 1;
}

void request_resource(int process_num, int req[]) {
    // Check if request is valid
    for(int i = 0; i < m; i++) {
        if(req[i] > need[process_num][i]) {
            printf("Error: Request exceeds need for resource %d\n", i);
            return;
        }
        if(req[i] > available[i]) {
            printf("Error: Request exceeds available resources for resource %d\n", i);
            return;
        }
    }

    // Temporarily allocate requested resources
    for(int i = 0; i < m; i++) {
        available[i] -= req[i];
        need[process_num][i] -= req[i];
        allocation[process_num][i] += req[i];
    }

    // Check if system is safe after allocation
    if(is_safe() == 0) {
        printf("System will not be in safe state after request allocation\n");
        // Rollback the allocation if unsafe
        for(int i = 0; i < m; i++) {
            available[i] += req[i];
            need[process_num][i] += req[i];
            allocation[process_num][i] -= req[i];
        }
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Input allocation matrix
    printf("Enter allocation matrix\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("Enter allocation resource %d of process %d: ", j, i);
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input max matrix
    printf("Enter max matrix\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("Enter max resource %d of process %d: ", j, i);
            scanf("%d", &Max[i][j]);
        }
    }

    // Input available resources
    printf("Enter available matrix\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate the need matrix
    calculate_need();

    // Check if the system is in a safe state initially
    if(is_safe() == 0) {
        printf("System is not in a safe state\n");
        return 0;
    }

    // Request resources from a process
    int req[m];
    int p;
    printf("Enter request process number: ");
    scanf("%d", &p);
    printf("Enter request matrix: ");
    for(int i = 0; i < m; i++) {
        scanf("%d", &req[i]);
    }

    // Handle the resource request
    request_resource(p, req);

    return 0;
}
