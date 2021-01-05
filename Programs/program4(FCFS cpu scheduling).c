#include<stdio.h>

int process[100],burst[100],n,i,j,waitTime[100],turnaroundTime[100];
double avgwait=0,avgturnaround=0;


void findAverageTime(){
    waitTime[0]=0;
    turnaroundTime[0]=burst[0];
    for(i=1;i<n;i++){
        waitTime[i]=waitTime[i-1]+burst[i-1];
        turnaroundTime[i]=waitTime[i]+burst[i];
    }
}

void main(){


    
    printf("Enter number of processes\n");
    scanf("%d",&n);
    printf("Enter the process id along with its burst time\n");


    for(i=0;i<n;i++){
        scanf("%d",&process[i]);
        scanf("%d",&burst[i]);
    }

    findAverageTime();

    printf("process\tburst time\twaiting time\tturnaround time\n");
    for(i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n",process[i],burst[i],waitTime[i],turnaroundTime[i]);
        avgturnaround+=turnaroundTime[i];
        avgwait+=waitTime[i];
    }

    printf("\naverage wait time:\t%f",avgwait/n);
    printf("\naverage turnaround time:\t%f",avgturnaround/n);


}
