#include <stdio.h>
#include <stdlib.h>

#define max_len 200

void SSJF(){
    int request[max_len], n, initial;
    int total_head_movement = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter head position: ");
    scanf("%d", &initial);

    for(int count = 0; count < n; count++) {
        int min_distance = 10000;
        int index = -1;

        for(int i = 0; i < n; i++) {
            int distance = abs(request[i] - initial);
            if(distance < min_distance) {
                min_distance = distance;
                index = i;
            }
        }
        total_head_movement += min_distance;
        initial = request[index];
        request[index] = 10000;  // Mark this request as processed
    }

    printf("Total head movement: %d\n", total_head_movement); 
}

void scan(){
    int request[max_len], size, initial, n, dir;
    int disk_movement = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter size of disk: ");
    scanf("%d", &size);

    printf("Enter head position: ");
    scanf("%d", &initial);

    printf("Enter direction for scan (1 = ascending, 0 = descending): ");
    scanf("%d", &dir);

    // Sort requests in ascending order
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(request[j] > request[j + 1]) {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    // Find the first request greater than the initial head position
    int index;
    for(index = 0; index < n; index++) {
        if(request[index] > initial) {
            break;
        }
    }

    if(dir == 1) {  // Ascending
        for(int i = index; i < n; i++) {
            disk_movement += abs(request[i] - initial);
            initial = request[i];
        }
        disk_movement += abs(size - 1 - initial);
        initial = size - 1;
        for(int i = index - 1; i >= 0; i--) {
            disk_movement += abs(request[i] - initial);
            initial = request[i];
        }
    } else {  // Descending
        for(int i = index - 1; i >= 0; i--) {
            disk_movement += abs(request[i] - initial);
            initial = request[i];
        }
        disk_movement += abs(0 - initial);
        initial = 0;
        for(int i = index; i < n; i++) {
            disk_movement += abs(request[i] - initial);
            initial = request[i];
        }
    }

    printf("Total disk movement: %d\n", disk_movement);
}

void clook(){
    int request[max_len], size, initial, n;
    int disk_movement = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter size of disk: ");
    scanf("%d", &size);

    printf("Enter head position: ");
    scanf("%d", &initial);

    // Sort requests in ascending order
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(request[j] > request[j + 1]) {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    int index;
    for(index = 0; index < n; index++) {
        if(request[index] > initial) {
            break;
        }
    }

    // Process from initial position to the end
    for(int i = index; i < n; i++) {
        disk_movement += abs(request[i] - initial);
        initial = request[i];
    }

    // Move back to the beginning and process remaining requests
    if(index > 0) {
        disk_movement += abs(request[0] - initial);
        initial = request[0];
        for(int i = 0; i < index; i++) {
            disk_movement += abs(request[i] - initial);
            initial = request[i];
        }
    }

    printf("Total disk movement: %d\n", disk_movement);
}

int main(){
    SSJF();
    scan();
    clook();
    return 0;
}
