#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct directory{
    int dircount,fcount;
    char filename[10][50],dirname[50];
    struct directory *dirs[10];
}*currentDir=NULL,*root[10],*temp=NULL,*levels[100];

void main(){
    int rootDircount=0,i,j,choice,end=0,level=0,flag;
    char dirname[50],filename[50],ch[50];
    do{
        printf("Enter 1 for a creating a directory at current dir\n2 for creating a file at current dir\n3 for list all files and folders in current dir\n4 for deleting a file in current dir\n5 for navigating to other dir\n6 for searching a file in current dir\n7 to exit\nEnter your choice:");
        scanf("%d",&choice);
        switch(choice){
            // create new dir
            case 1:{
                printf("Enter name of directory:");
                scanf("%s",dirname);

                // check if dir with same name exits
                flag=0;
                if(currentDir==NULL){
                    for(i=0;i<rootDircount;i++){
                        if(strcmp(dirname,root[i]->dirname)==0){
                            flag=1;
                            break;
                        }
                    }
                }
                else{
                    for(i=0;i<currentDir->dircount;i++){
                        if(strcmp(dirname,currentDir->dirs[i]->dirname)==0){
                            flag=1;
                            break;
                        }
                    }
                }
                if(flag==1){
                    printf("Directory with same name exits\n");
                    break;
                }
                // check ends

                temp=(struct directory*)malloc(sizeof(struct directory));
                temp->fcount=0;
                temp->dircount=0;
                strcpy(temp->dirname,dirname);
                if(rootDircount<10 && currentDir==NULL){
                    root[rootDircount]=temp;
                    rootDircount++;
                }
                else if(currentDir->dircount<10){
                    currentDir->dirs[currentDir->dircount]=temp;
                    currentDir->dircount++;
                }
                else{
                    printf("Dir limit exceeded\n");
                    break;
                }
                printf("------Dir created successfully------\n");
                break;
            }
            // create new file
            case 2:{
                if(currentDir==NULL){
                    printf("You are not allowed to create files in root dir\n");
                }
                else{
                    printf("Enter file name:");
                    scanf("%s",filename);

                    // check if file with same name exits
                    flag=0;
                    
                    for(i=0;i<currentDir->fcount;i++){
                        if(strcmp(filename,currentDir->filename[i])==0){
                            flag=1;
                            break;
                        }
                    }
                    if(flag==1){
                        printf("File with same name exits\n");
                        break;
                    }
                    // check ends


                    if(currentDir->fcount<10){
                        strcpy(currentDir->filename[currentDir->fcount],filename);
                        currentDir->fcount++;
                        printf("File created successfully\n");
                    }
                    else{
                        printf("File limit exceeded\n");
                    }
                }
                break;
            }
            // display files and folders
            case 3:{
                if(currentDir==NULL){
                    printf("----Folders(root)\n");
                    for(i=0;i<rootDircount;i++){
                        printf("%s\n",root[i]->dirname);
                    }
                    printf("\n");
                }
                else{
                    printf("dircount: %d\tfcount: %d\n",currentDir->dircount,currentDir->fcount);
                    printf("----Folders\n");
                    for(i=0;i<currentDir->dircount;i++){
                        printf("%s\n",currentDir->dirs[i]->dirname);
                    }
                    printf("\n");
                    printf("----Files\n");
                    for(i=0;i<currentDir->fcount;i++){
                        printf("%s\n",currentDir->filename[i]);
                    }
                    printf("\n");
                }
                break;
            }
            // delete a file
            case 4:{
                if(currentDir!=NULL){
                    flag=0;
                    printf("Enter file name to delete:");
                    scanf("%s",filename);
                    for(i=0;i<currentDir->fcount;i++){
                        if(strcmp(currentDir->filename[i],filename)==0){
                            flag=1;
                            break;
                        }
                    }
                    if(flag==1){
                        for(j=i;j<currentDir->fcount-1;j++){
                            strcpy(currentDir->filename[j],currentDir->filename[j+1]);
                        }
                        currentDir->filename[j][0]='\0';
                        currentDir->fcount--;
                        printf("File deleted successfully\n");
                    }
                    else{
                        printf("File not found\n");
                    }

                }
                else{
                    printf("No files in root dir\n");
                }
                break;
            }
            // Navigate
            case 5:{
                printf("Enter dir name to enter that dir\nto go back enter 0\n");
                printf("Enter your choice:");
                scanf("%s",ch);
                if(strcmp(ch,"0")==0){
                    if(level==0){
                        if(currentDir!=NULL){
                            currentDir=NULL;
                        }
                        else{
                            printf("Cannot go back\n");
                        }
                    }
                    else{
                        currentDir=levels[level-1];
                        levels[level-1]=NULL;
                        level--;
                    }
                }
                else{
                    flag=0;
                    if(currentDir==NULL){
                        for(i=0;i<rootDircount;i++){
                            if(strcmp(root[i]->dirname,ch)==0){
                                flag=1;
                                break;
                            }
                        }
                        if(flag==1){
                            currentDir=root[i];
                            printf("dircount: %d\tfcount: %d\n",currentDir->dircount,currentDir->fcount);
                        }
                    }
                    else{
                        for(i=0;i<currentDir->dircount;i++){
                            if(strcmp(currentDir->dirs[i]->dirname,ch)==0){
                                flag=1;
                                break;
                            }
                        }
                        if(flag==1){
                            levels[level]=currentDir;
                            level++;
                            currentDir=currentDir->dirs[i];
                        }
                    }
                    if(flag==0){
                        printf("Dir not found\n");
                    }
                }
                break;
            }
            // search a file
            case 6:{
                if(currentDir!=NULL){
                    printf("Enter filename to be searched:");
                    scanf("%s",filename);
                    flag=0;
                    for(i=0;i<currentDir->fcount;i++){
                        if(strcmp(filename,currentDir->filename[i])==0){
                            flag=1;
                            break;
                        }
                    }
                    if(flag==1){
                        printf("File found\n");
                    }
                    else{
                        printf("File not found\n");
                    }
                }
                else{
                    printf("No file exits in root level dir\n");
                }
                break;
            }
            // exit
            case 7:{
                end=1;
                break;
            }

            default:{
                printf("Wrong choice\n");
            }

        }
    }while(end!=1);
    printf("Exited successfully\n");
}
