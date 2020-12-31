#include<stdio.h>

void main(){

    // declaration
    int  alloc[10][10], avail[10], max[10][10], total[10], need[10][10], p, r, i, j, safeSequence[10], ssIndex=0, count, process, complete[10];

    // accepting p and r
    printf("Enter no. of processes:\n");
    scanf("%d",&p);
    printf("Enter no. of resources:\n");
    scanf("%d",&r);

    // making all processed not complete
    for(i=0;i<p;i++){
        complete[i]=0;
    }

    printf("Enter total resources\n");
    for(i=0;i<r;i++){
        scanf("%d",&avail[i]);
    }

    // total=avail;

    // accepting max resources 
    printf("Enter max resources required for each process\n");
    for(i=0;i<p;i++){
        printf("Enter max resources for Process %d\n",i+1);

        for(j=0;j<r;j++){
            scanf("%d",&max[i][j]);
        }
    }

    // accepting allocated resources 
    printf("Enter allocated resources for each process\n");
    for(i=0;i<p;i++){
        printf("Enter allocated resources for Process %d\n",i+1);

        for(j=0;j<r;j++){
            scanf("%d",&alloc[i][j]);
            avail[j]-=alloc[i][j];
        }
    }

    // // accepting no. available resources 
    // printf("Enter available resources\n");
    // for(i=0;i<r;i++){
    //         scanf("%d",&avail[i]);
    // }

    // needed resources
    for(i=0;i<p;i++){  
        for(j=0;j<r;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }

    // bankers algo computation
    count=0;
    threshold=0;
    while(process!=-1 && count!=p){

        // printf("\n\nAvaialbe resources\n");
        // for(i=0;i<r;i++){
        //     printf("%d\t",avail[i]);
        // }
        // printf("\n\n");

        // temp=process!=-1?process:0;


        process=-1;
        for(i=0;i<p;i++){
            if(complete[i]==0){
                process=i;
                for(j=0;j<r;j++){
                    if(need[i][j]>avail[j]){
                        process=-1;
                        break;
                    }
                }
            }
            if(process!=-1){
                break;
            }
        }

        if(process!=-1){
            printf("Process %d completed\n",process+1);
            complete[process]=1;
            safeSequence[ssIndex]=process+1;
            ssIndex++;
            count++;
            for(j=0;j<r;j++){
                avail[j]+=alloc[process][j];
            }
        }

    }

    if(count==p){
        printf("The safe sequence is:\t");
        for(i=0;i<p;i++){
            printf("%d\t",safeSequence[i]);
        }
    }
    else{
        printf("System is in unsafe state\n");
    }



}