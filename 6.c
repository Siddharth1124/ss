#include <stdio.h>
#include <stdlib.h>

#define max 10

typedef struct{
    char data[max];
    int end;
}queue;

void enqueue(queue *q, char dt){
    q->data[q->end] = dt;
    q->end ++;
}

void dequeue(queue *q){
    for(int i = 0; i<q->end-1; i++){
        q->data[i] = q->data[i+1];
    }
    q->end--;
}

void FCFS(char string[max], int frameSize, int count){
    queue q;
    q.end = 0;
    int pageFaults = 0;
    int flage;

    printf("Request\tcontent\tPageFault\n");

    for(int i=0;i<count;i++){
        printf("\n\t%c", string[i]);
        flage = 0;
        for(int j = 0; j<q.end;j++){
            if(string[i] == q.data[j]){
                flage = 1;
                break;
            }
        }

        if(flage == 0){
            if(q.end < frameSize){
                enqueue(&q, string[i]);
            }
            else{
                dequeue(&q);
                enqueue(&q, string[i]);
            }
            printf("\t");
            for(int k =0;k<q.end;k++){
                printf("%d ", q.data[k]);
            }
            printf("\t\tY");            
        }
        else{
            printf("\t");
            for(int k =0;k<q.end;k++){
                printf("%c ", q.data[k]);
            }
            printf("\t\tN");
        }
    }
}

void LRU(char string[max], int frameSize, int count){
    queue q;
    q.end = 0;
    int pageFaults = 0;
    int flage ;
    int recent[max];
    printf("Request\tcontent\tPageFault\n");
    for(int i=0;i<count;i++){
        printf("\n\t%c", string[i]);
        flage = 0;
        for(int j=0;j<q.end;j++){
            if(string[i] == q.data[j]){
                flage = 1;
                recent[j] = i; 
                break;
            }
        }

        if(flage == 0){
            if(q.end < frameSize){
                enqueue(&q, string[i]);
                recent[q.end-1] = i;
            }
            else{
                int LruIndex = 0;
                for( int j = 0; j<q.end;j++){
                    if(recent[j] < recent[LruIndex]){
                        LruIndex = j;
                    }
                }

                q.data[LruIndex] = string[i];
                recent[LruIndex] = i;
            }
            printf("\t");
            for(int k =0;k<q.end;k++){
                printf("%c ", q.data[k]);
                }
            printf("\t\tY");  
        }
        else{
            printf("\t");
            for(int k =0;k<q.end;k++){
                printf("%c ", q.data[k]);
            }
            printf("\t\tN");
        }
    }
}

void optimal(char string[max], int frameSize, int count) {
    queue q;
    q.end = 0;
    int pageFaults = 0;
    int flag;

    printf("Request\tContent\tPageFault\n");

    for (int i = 0; i < count; i++) {
        printf("\n\t%c", string[i]);
        flag = 0;

        // Check if the page is already in the queue
        for (int j = 0; j < q.end; j++) {
            if (string[i] == q.data[j]) {
                flag = 1;  // Page is found, no page fault
                break;
            }
        }

        // If the page is not found, a page fault occurs
        if (flag == 0) {
            pageFaults++;

            // If there is space in the queue, add the page
            if (q.end < frameSize) {
                enqueue(&q, string[i]);
            } else {
                // Determine the page to replace based on the farthest future use
                int farthestIndex = -1;
                int replacementIndex = -1

                for (int j = 0; j < frameSize; j++) {
                    int futureIndex = count; // Assume the page is not used again
                    for (int k = i + 1; k < count; k++) {
                        if (q.data[j] == string[k]) {
                            futureIndex = k;
                            break;
                        }
                    }

                    // Find the page with the farthest future use
                    if (futureIndex > farthestIndex) {
                        farthestIndex = futureIndex;
                        replacementIndex = j;
                    }
                }

                // Replace the identified page with the new page
                q.data[replacementIndex] = string[i];
            }

            // Print page content after a page fault
            printf("\t");
            for (int k = 0; k < q.end; k++) {
                printf("%c ", q.data[k]);
            }
            printf("\t\tY");
        } else {
            // Print page content without a page fault
            printf("\t");
            for (int k = 0; k < q.end; k++) {
                printf("%c ", q.data[k]);
            }
            printf("\t\tN");
        }
    }
}
    


int main(){
    int n;
    printf("Enter number of request");
    scanf("%d", &n);
    printf("Enter Frame size");
    int size;
    scanf("%d", &size);

    char string[max];
    for(int i=0;i<n;i++){
        printf("Enter request %d:", i);
        scanf(" %c", &string[i]);
    }

    optimal(string,size,n);
}