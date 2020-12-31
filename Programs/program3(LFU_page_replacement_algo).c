#include<stdio.h>
#include<stdlib.h>

int input[100],size,RIindex[100],risize=0;

struct node{
    int item;
    int frequency;
    struct node *link;
}*ptr,*new,*header=NULL;


void deleteLFU(int item){
    struct node *prev=NULL;
    ptr=header;
    while(ptr!=NULL){
        if(header==ptr && ptr->item==item){
            header=ptr->link;
            free(ptr);
            break;
        }
        else if(ptr->item==item){
            prev->link=ptr->link;
            free(ptr);
            break;

        }
        prev=ptr;
        ptr=ptr->link;
    }
}

// increments frequency table
void findAndIncrement(int item){
    ptr=header;
    while(ptr!=NULL){
        if(ptr->item==item){
            ptr->frequency=ptr->frequency+1;
        }
        ptr=ptr->link;
    }

    // ptr=header;
    // printf("item---->frequency\n");
    // while(ptr!=NULL){
    //     printf("%d---->%d\n",ptr->item,ptr->frequency);
    //     ptr=ptr->link;
    // }


}

//find index of element in a array
int in(int array[],int size,int item){
    for(int i=0;i<size;i++){
        if(array[i]==item){
            return i;
        }
    }
    return -1;
}

// find first inputted element
int findFirst(int array[],int limit){
    for(int i=0;i<size;i++){
        if(in(RIindex,risize,i)==-1){
            for(int j=0;j<limit;j++){
                if(array[j]==input[i]){
                    RIindex[risize]=i;
                    risize++;
                    return array[j];
                }
            }
        }
    }
}


// finds lfu
int leastFrequenltyUsed(){
    ptr=header;
    int min=0,flag=0,minElements[100];
    while(ptr!=NULL){
        if(min>ptr->frequency || min==0){
            flag=1;
            min=ptr->frequency;
            minElements[0]=ptr->item;
        }
        else if(min==ptr->frequency){
            minElements[flag]=ptr->item;
            flag++;
        }
        ptr=ptr->link;
    }
    
    if(flag>1){
        return findFirst(minElements,flag);
    }
    else{
        return minElements[0];
    }


}

void main(){

    // declaration
    int frame[100],max,i,j,flag,rear=-1,lfu,lfuIndex,fault=0;

    // reading input
    printf("Enter number of pages\n");
    scanf("%d",&size);

    for(i=0;i<size;i++){
        RIindex[i]=-1;
    }

    printf("Enter frame size\n");
    scanf("%d",&max);

    // intialising frame
    for(i=0;i<max;i++){
        frame[i]=-1;
    }

    // iterating page request
    for(i=0;i<size;i++){
        flag=0;
        scanf("%d",&input[i]);
        for(j=0;j<max;j++){
            if(input[i]==frame[j]){
                flag=1;
                break;
            }
        }

        // if hit
        if(flag==1){
            printf("%d\thit\n",input[i]);
            findAndIncrement(input[i]);
        }

        // if fault
        else{

            fault++;

            // if frame not full
            if(rear+1<max){
                rear++;
                frame[rear]=input[i];

                new=(struct node*)malloc(sizeof(struct node));
                new->item=input[i];
                new->frequency=1;
                new->link=header;
                header=new;

            }

            // if full find lfu 
            else{

                lfu=leastFrequenltyUsed();
                lfuIndex=in(frame,max,lfu);
                frame[lfuIndex]=input[i];
                deleteLFU(lfu);
                

                new=(struct node*)malloc(sizeof(struct node));
                new->item=input[i];
                new->frequency=1;
                new->link=header;
                header=new;
            }
        }

        printf("frame\n");
        for(j=0;j<max;j++){
            printf("%d\t",frame[j]);
        }
        printf("\n");
    }

    printf("\n\nFaults:%d",fault);
}