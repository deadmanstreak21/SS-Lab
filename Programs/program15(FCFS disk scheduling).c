#include<stdio.h>
#include<stdlib.h>
void main(){
    int sequence[50],n,i,current,seekTime=0;
    printf("Enter no. of sequence:");
    scanf("%d",&n);
    printf("Enter the sequence\n");
    for(i=0;i<n;i++){
        scanf("%d",&sequence[i]);
    }
    printf("Enter current head position:");
    scanf("%d",&current);
    for(i=0;i<n;i++){
        printf("Moving from %d to %d; Seek time:%d\n",current,sequence[i],abs(sequence[i]-current));
        seekTime+=abs(current-sequence[i]);
        current=sequence[i];
    }
    printf("Total seek time:%d\n",seekTime);
}