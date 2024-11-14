#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int pid;
    int arrival_time;
    int completion_time;
    int remaining_time;
    int burst_time;
    int turnarroud_time;
    int waiting_time;
}process;

void sort_arrival(process p[], int n){
    for(int i=0;i<n-1;i++){
        for(int j =0;j< n-i-1;j++){
            if(p[j].arrival_time > p[j+1].arrival_time ){
                process temp  = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void SJFPreemptive(process p[], int n){
    int completed = 0;
    int time = 0;

    for(int i=0;i<n;i++){
        p[i].remaining_time = p[i].burst_time;
    }

    while (completed < n)
    {
        int min_remaining_time = 1000;
        int min_remaining_index = -1;

        for(int i=0;i<n;i++){
            if(p[i].remaining_time >0 && p[i].arrival_time <= time && p[i].remaining_time < min_remaining_time){
                min_remaining_time = p[i].remaining_time;
                min_remaining_index = i;
            }
        }

        if(min_remaining_index == -1){
            time++;
            continue;
        }

        p[min_remaining_index].remaining_time --;
        time++;

        if(p[min_remaining_index].remaining_time == 0){
            p[min_remaining_index].completion_time = time;
            p[min_remaining_index].turnarroud_time = p[min_remaining_index].completion_time - p[min_remaining_index].arrival_time;
            p[min_remaining_index].waiting_time = p[min_remaining_index].turnarroud_time - p[min_remaining_index].burst_time;
            completed ++;
        }
    }
}


void RoundRobbin(process p[], int n, int quantum){
    int completed = 0;
    int time = 0;
     for(int i=0;i<n;i++){
        p[i].remaining_time = p[i].burst_time;
    } 

    while (completed <n)
    {        
        int notready = 1;
        for(int i=0;i<n;i++){           
            if(p[i].arrival_time <=time&& p[i].remaining_time >0 ){
                notready = 0;
                if(p[i].remaining_time > quantum){
                    p[i].remaining_time -= quantum;
                    time += quantum;
                }
                else{
                    time += p[i].remaining_time;
                    p[i].remaining_time =0;
                    p[i].completion_time = time;
                    p[i].turnarroud_time = p[i].completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnarroud_time - p[i].burst_time;
                    completed++;
                }
            }
        }
        if(notready == 1){
            time++;
        }
    }
    



}

void display(process p[], int n){
    printf("Pid\tarrival_time\tBurst_time\tTurarround\twainting\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].turnarroud_time,p[i].waiting_time);
/    }
}

int main(){
    int n;      
    printf("Enter number of processes");
    scanf("%d", &n);

    process p[n];
    for(int i=0;i<n;i++){
        p[i].pid = i+1;
    }
    
    for(int i=0;i<n;i++){
        printf("Enter %d arrival time",i);
        scanf("%d", &p[i].arrival_time);
        printf("Enter %d burst time",i);
        scanf("%d", &p[i].burst_time);
    }

 //   sort_arrival(p,n);
   // SJFPreemptive(p,n);

   RoundRobbin(p,n,2);
    display(p,n);
}