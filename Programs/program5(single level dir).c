#include<stdio.h>
#include<string.h>

struct directory{
    char dname[50],fname[10][50];
    int fcount;
}dir;

void main(){
    int i,j,choice,exit=0,fileflag;
    char name[50];
    dir.fcount=0;
    printf("Enter the name of the directory:");
    scanf("%s",dir.dname);

    
    do{
        printf("Enter\n1 to create a file\n2 to search a file\n3 to delete a file\n4 to list all files\n5 to exit\nEnter your choice:");
        scanf("%d",&choice);
        switch(choice){

            case 1:{
                if(dir.fcount<9){
                    printf("Enter file name:");
                    scanf("%s",dir.fname[dir.fcount]);
                    dir.fcount++;
                    printf("File created successfully\n");
                }
                else{
                    printf("File limit exceeded\n");
                }
                break;
            }

            case 2:{
                if(dir.fcount==0){
                    printf("Empty directory\n");
                }
                else{
                    printf("Enter name of file:");
                    scanf("%s",name);
                    fileflag=0;
                    for(i=0;i<dir.fcount;i++){
                        if(strcmp(name,dir.fname[i])==0){
                            printf("File found\n");
                            fileflag=1;
                        }
                    }
                    if(fileflag!=1){
                        printf("File not found\n");
                    }
                }
                break;
            }

            case 3:{
                if(dir.fcount==0){
                    printf("Empty directory\n");
                }
                else{
                    printf("Enter the name of file:");
                    scanf("%s",name);
                    fileflag=0;
                    for(i=0;i<dir.fcount;i++){
                        if(strcmp(name,dir.fname[i])==0){
                            fileflag=1;
                            strcpy(dir.fname[i],"");
                            dir.fcount--;
                            printf("File deleted successfully\n");
                        }
                    }
                    if(fileflag!=1){
                        printf("File not found\n");
                    }
                }
                break;
            }

            case 4:{
                if(dir.fcount==0){
                    printf("Empty directory\n");
                }
                else{
                    for(i=0;i<dir.fcount;i++){
                        printf("%s\t",dir.fname[i]);
                    }
                    printf("\n");
                }
                break;
            }

            case 5:{
                exit=1;
                printf("Successfully exited\n");
                break;
            }

            default:{
                printf("Wrong choice\n");
                break;
            }

        }
    }while(exit==0);
    
}
