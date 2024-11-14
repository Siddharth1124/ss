#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define max 10

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
    
    int arr[max];

    printf("Enter number of elements you want to insert");
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Enter elements");
        scanf("%d", &arr[i]);
    }

    pid_t id = fork();
    if(id > 0){
        printf("Parent process start executing\n");
        printf("Parent process starts sorting elemets\n");
        bubbleSort(arr, n);
        printf("Sorted array : ");
        for(int i=0;i<n;i++){
            printf("%d -", arr[i]);
        }
        printf("\n");
        printf("Parent process completed its sorted\n");
    }

    else if(id == 0){
        
       printf("Child process start executing\n");
       
       char* argc[n+2];
       argc[0] = "./reverse";

       for(int i=0;i<n;i++){
        char* num = malloc(10);
        sprintf(num,"%d", arr[i]);
        argc[i+1] = num;
       }
       argc[n+1] = NULL;
       execve(argc[0], argc, NULL);
    }
}