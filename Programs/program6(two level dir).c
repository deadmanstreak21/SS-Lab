#include<stdio.h>
#include<string.h>

struct directory{
    char fname[10][50],dname[50];
    int fcount;
}dir[10];

void main(){
    int dircount=0,choice,exit=0,i,j,flag,fileflag;
    char filename[50],dirname[50];

    for(i=0;i<10;i++){
        dir[i].fcount=0;
    }

    do{
        printf("Enter\n1 to create new dir\n2 to create new file\n3 to search file\n4 to delete file\n5 to display files in a dir\n6 to exit\nEnter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                if(dircount<=9){

                    flag=0;
                    printf("Enter directory name:");
                    scanf("%s",dirname);

                    for(i=0;i<dircount;i++){
                        if(strcmp(dirname,dir[i].dname)==0){
                            flag=1;
                            break;
                        }
                    }

                    if(flag!=1){
                        strcpy(dir[dircount].dname,dirname);
                        dircount++;
                        printf("Directory created successfully\n");
                    }
                    else{
                        printf("Directory name already exits\n");
                    }

                }
                else{
                    printf("Directory limit reached\n");
                }
                break;
            }

            case 2:{
                
                printf("Enter the directory name:");
                scanf("%s",dirname);
                flag=0;

                for(i=0;i<dircount;i++){
                    if(strcmp(dirname,dir[i].dname)==0){
                        flag=1;
                        if(dir[i].fcount>9){
                            printf("File limit reached\n");
                            flag=0;
                            break;
                        }

                        printf("Enter filename:");
                        scanf("%s",filename);

                        fileflag=0;
                        for(j=0;j<dir[i].fcount;j++){
                            if(strcmp(filename,dir[i].fname[j])==0){
                                fileflag=1;
                                printf("Filename already exists\n");
                                break;
                            }
                        }

                        if(fileflag!=1){
                            strcpy(dir[i].fname[dir[i].fcount],filename);
                            dir[i].fcount++;
                            printf("File created successfully\n");
                        }

                        break;
                    }
                }

                if(flag!=1){
                    printf("Directory not found\n");
                }

                break;
            }

            case 3:{
                printf("Enter directory name:");
                scanf("%s",dirname);
                flag=0;
                for(i=0;i<dircount;i++){
                    if(strcmp(dirname,dir[i].dname)==0){
                        flag=1;

                        printf("Enter file name:");
                        scanf("%s",filename);
                        fileflag=0;
                        for(j=0;j<dir[i].fcount;j++){
                            if(strcmp(filename,dir[i].fname[j])==0){
                                fileflag=1;
                                printf("File found\n");
                                break;
                            }
                        }

                        if(fileflag!=1){
                            printf("File not found\n");
                        }

                        break;
                    }
                }

                if(flag!=1){
                    printf("Directory not found\n");
                }

                break;
            }

            case 4:{
                printf("Enter directory name:");
                scanf("%s",dirname);
                flag=0;
                for(i=0;i<dircount;i++){
                    if(strcmp(dirname,dir[i].dname)==0){
                        flag=1;

                        if(dir[i].fcount=0){
                            printf("Empty directory\n");
                            break;
                        }

                        printf("Enter file name:");
                        scanf("%s",filename);
                        fileflag=0;
                        for(j=0;j<dir[i].fcount;j++){
                            if(strcmp(filename,dir[i].fname[j])==0){
                                fileflag=1;
                                printf("File found\n");
                                break;
                            }
                        }


                        if(fileflag!=1){
                            printf("File not found\n");
                        }
                        else{
                            for(j=j;j<dir[i].fcount-1;j++){
                                strcpy(dir[i].fname[j],dir[i].fname[j+1]);
                            }
                            strcpy(dir[i].fname[dir[i].fcount-1],"");
                            dir[i].fcount--;
                            printf("File deleted successfully\n");
                        }

                        break;
                    }
                }

                if(flag!=1){
                    printf("Directory not found\n");
                }

                break;
            }

            case 5:{
                printf("Enter directory name:");
                scanf("%s",dirname);
                flag=0;
                for(i=0;i<dircount;i++){
                    if(strcmp(dirname,dir[i].dname)==0){
                        flag=1;
                        for(j=0;j<dir[i].fcount;j++){
                            printf("%s\t",dir[i].fname[j]);
                        }
                        printf("\n");
                        if(j==0){
                            printf("Empty directory\n");
                        }
                        break;
                    }
                }
                if(flag!=1){
                    printf("Directory not found\n");
                }
                break;
            }

            case 6:{
                exit=1;
                break;
            }

            default:{
                printf("Wrong choice\n");
                break;
            }
        }
    }while(exit==0);
    printf("Exited successfully");
}
