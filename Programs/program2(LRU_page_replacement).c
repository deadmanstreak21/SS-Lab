#include<stdio.h>

// ? function to add new recently used item to list
void add_recent(int recent[], int max, int element){
    int i;
    for(i=0;i<max-1;i++){
        recent[i]=recent[i+1];
    }
    recent[max-1]=element;
}


// ? function to move the existing element in recent list to last index(i.e. recently used)
void replace_recent(int recent[], int max, int element){
    int index,i,temp;
    for(i=0;i<=max;i++){
        if(recent[i]==element){
            index=i;
            break;
        }
    }
    temp=recent[index];
    i=index;
    while(i<max-1){
        recent[i]=recent[i+1];
        i++;
    }

    recent[max-1]=temp;

}


// ? function that returns index of an element in an array
int getindex(int array[],int element,int limit){
    for(int i=0;i<limit;i++){
        if(array[i]==element){
            return i;
        }
    }
    return -1;
}


// ? main function
void main(){

    // ? declaring and initialising variables
    int a[100],n,i,j,q[100],max,rear=-1,flag,recent[100],rhead=0,lru_index,faults=0,lru;

    // ? reading inputs starts
    printf("Enter the number of pages\n");
    scanf("%d",&n);
    printf("Enter n page ids\n");
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    printf("Enter the frame size\n");
    scanf("%d",&max);
    // ? reading inputs ends

    // ? initialising q,recent
    for(i=0;i<max;i++){
        q[i]=-1;
        recent[i]=-1;
    }

    // ? algo starts
    for(i=0;i<n;i++){

        
        // ? flag
        flag=0;

        // ? checking page id in frame
        for(j=0;j<max;j++){
            if(a[i]==q[j]){
                flag=1;
                break;
            }
        }

        // ? if found do following
        if(flag==1){
            printf("%d\t%s\n",a[i],"hit");
            replace_recent(recent,max,q[j]);
        }

        // ? if not found do the following
        else{

            // ? increase no. of faults
            faults++;

            printf("%d\t%s\n",a[i],"fault");

            // ? checking if frame is not full.... if not full add page id to frame and update recent
            if(rear+1<max){

                rear++;
                q[rear]=a[i];
                recent[rear]=a[i];


            }
            
            // ? if frame full do the following
            else{
                // ? finding least recently used page id from recent and find the index of that page id in frame and 
                // ?then replace the element in found out index of frame with new page id and update recent
                lru=recent[0];
                lru_index=getindex(q,lru,max);
                q[lru_index]=a[i];
                add_recent(recent,max,a[i]);
            }

        }
        // ? print frames during each iteration
        for(j=0;j<max;j++){
            printf("%d\t",q[j]);
        }
        printf("\n");
    }

    // ? print o. of faults
    printf("\nfaults:%d",faults);
}