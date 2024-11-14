#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define max 10

int arr[max];

void bubbleSort(int arr[], int n){
    for(int i=0;i < n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){
    printf("Enter number of elements you want to insert");
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Enter elements");
        scanf("%d", &arr[i]);
    }

    pid_t id = fork();
    if(id == 0 ){
        printf("Child process start executing\n");
        printf("Child process starts sorting elemets\n");
        bubbleSort(arr, n);
        printf("Child process completed its sorted\n");
        printf("Sorted array : ");
        for(int i=0;i<n;i++){
            printf(" %d - ", arr[i]);
        }
        printf("\n");
        printf("Child process complted\t");
        
    }
    else if(id > 0){
        printf("Parent process start executing\n");
        printf("Parent process starts sorting elemets\n");
        bubbleSort(arr, n);
        printf("Sorted array : ");
        for(int i=0;i<n;i++){
            printf(" %d - ", arr[i]);
        }
        printf("\n");
        printf("Parent process completed its sorted\n");
        printf("parent process waiting for child to complete its'execution\n");
        int k;
        wait(&k);
        printf("Parent process completed its execution\n");
    }
}
