
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
int length(char string[]);
void main(){
    char opcode[10],label[10],operand[10],mnuemonic[10],value[10],temp[10],opcodetemp[10];
    int LOCCTR=0,flag,startingAddress,i,temp1;
    FILE *input,*output,*optab,*symtab,*lengthFile;

    input=fopen("two pass assembler files/input.txt","r");
    output=fopen("two pass assembler files/output.txt","w");
    optab=fopen("two pass assembler files/optab.txt","r");
    symtab=fopen("two pass assembler files/symtab.txt","w+");

    fscanf(input,"%s %s %s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        LOCCTR=atoi(operand);
        startingAddress=LOCCTR;
        fprintf(output,"%s %s %s %s\n","\t",label,opcode,operand);
        fscanf(input,"%s %s %s",label,opcode,operand);
    }

    //while NOT END
    while(strcmp(opcode,"END")!=0){

        itoa(LOCCTR,temp,10);
        fprintf(output,"%s %s %s %s\n",temp,label,opcode,operand);

        // if symbol in label field
        if(strcmp(label,"-")!=0){
            rewind(symtab);
            flag=0;
            while(!feof(symtab)){
                fscanf(symtab,"%s %s",mnuemonic,value);
                if(strcmp(mnuemonic,label)==0){
                    printf("Duplicate symbol %s\n",label);
                    flag=1;
                }
            }
            if(flag!=1){
                itoa(LOCCTR,temp,10);
                fprintf(symtab,"%s %s\n",label,temp);
            }
        }

        flag=0;

        // search optab for opcode
        rewind(optab);
        while(!feof(optab)){
            fscanf(optab,"%s %s",opcodetemp,value);
            if(strcmp(opcode,opcodetemp)==0){
                flag=1;
                break;
            }
        }

        if(flag){
            LOCCTR+=3;
        }
        else if(strcmp(opcode,"WORD")==0){
            LOCCTR+=3;
        }
        else if(strcmp(opcode,"RESW")==0){
            LOCCTR+=3*atoi(operand);
        }
        else if(strcmp(opcode,"RESB")==0){
            LOCCTR+=atoi(operand);
        }
        else if(strcmp(opcode,"BYTE")==0){
            LOCCTR+=length(operand)-3;

        }
        else{
            printf("Invalid opcode %s\n",opcode);
        }
        
        fscanf(input,"%s %s %s",label,opcode,operand);
    }
    itoa(LOCCTR,temp,10);
    fprintf(output,"%s %s %s %s\n",temp,label,opcode,operand);
    printf("Program length=%d",LOCCTR-startingAddress);

    // write length to length.txt
    lengthFile=fopen("two pass assembler files/length.txt","w+");
    sprintf(temp,"%d",LOCCTR-startingAddress);
    fprintf(lengthFile,"%s",temp);

    fclose(input);
    fclose(output);
    fclose(optab);
    fclose(symtab);
    fclose(lengthFile);
}



int length(char string[]){
    int i=0;
    while(string[i]!='\0'){
        i=i+1;
    }
    return i;
}