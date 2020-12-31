// program to implement FIFO page replacement algorithm

// ? include necessary libraries
#include<stdio.h>
void main(){

    //? variable declarations and initializations
    int queue[100],input[100],n,i,j,f,flag,front=-1,rear=-1,faults=0;

    // ? read number of pages (n)
    printf("Enter the number of pages\n");
    scanf("%d",&n);

    // ? read the pages
    printf("Enter the page numbers\n");
    for(i=0;i<n;i++){
        scanf("%d",&input[i]);
    }

    // ? read number of frames (f)
    printf("Enter the number of frames\n");
    scanf("%d",&f);

    // ? initializing the array with all elements as -999 so that there is no issues of garbage values
    for(i=0;i<f;i++){
        queue[i]=-999;
    }

    // ? working
    printf("page no.\tstatus\n");
    for(i=0;i<n;i++){

        // ? setting flag = 0 initially
        flag=0;
        for(j=0;j<f;j++){

            // ? checking for hit
            if(queue[j]==input[i]){

                // ? change the flag to 1 (page hit)
                flag=1;
                break;
            }
        }

        // ? procedures to follow when page hit
        if(flag==1){
            printf("%d\t%s",input[i],"hit\n");
            // for(int k=0;k<f;k++){
            //     printf("%d\t",queue[k]);
            // }
            // printf("\n");
        }

        // ? procedures to follow when page fault
        else{
            printf("%d\t%s",input[i],"fault\n");

            // ? increment faults variable
            faults++;

            // ? front == -1 means queue empty so changing front = 0
            if(front==-1){
                front=0;
            }

            // ? if rear less than frame size queue not full... add to queue
            if(rear+1<f){
                rear++;
                queue[rear]=input[i];
            }

            // ? queue is full remove the element queue[front] and increment front
            else{
                queue[front]=input[i];
                front=(front+1)%f;
            }

        }
    }

    // ? display number of faults
    printf("faults=%d",faults);

}