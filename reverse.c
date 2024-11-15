# include<stdio.h>
# include <stdlib.h>
# include<sys/types.h>
# include<unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int *data = (int *) malloc((argc) * sizeof(int));
	
	printf("\nArgc:%d",argc);
    for(int i = 0;i < argc;i++) 
    {
        data[i] = atoi(argv[i]);
    }
 
    printf("\nPrinting Element in Reverse:");
    for(int i = argc-1; i>0;i--)
    {
        printf(" %d ",data[i]);
    }
     
    printf("\n\nEXCEV task Completed \n");
}


