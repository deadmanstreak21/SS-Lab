#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int isDigit(char number[]);
int Length(char string[]);
void main(){
    FILE *input,*optab,*symtab,*object,*leng;
    char startingAddress[10],symboladdress[10],textrecordaddress[10],objectcode[10],temp[10]="\0",temp1[10],address[10]="000000",progleng[10]="\0",name[6]="\0",value[10]="\0",opcode[10],label[10]="      ",operand[10],textrecord[100]="\0",mnuemonic[10],symbol[10];
    int i,j,length=25,len,flag,textrecordlength;
    input=fopen("two pass assembler files/output.txt","r");
    optab=fopen("two pass assembler files/optab.txt","r");
    symtab=fopen("two pass assembler files/symtab.txt","r");
    object=fopen("two pass assembler files/object.txt","w");
    leng=fopen("two pass assembler files/length.txt","r");

    // read length from length.txt
    fscanf(leng,"%s",temp1);
    length=atoi(temp1);
    

    fscanf(input,"%s %s %s",label,opcode,operand);
    
    // if opcode equals START
    if(strcmp(opcode,"START")==0){
        address[0]='\0';

        i=strlen(label);
        if(i<6){
            while(i<6){
                strcat(label," ");
                i++;
            }
        }

        // starting address
        len=strlen(operand)+1;

        for(int k=len;k<=6;k++){
            strcat(address,"0");
        }
        strcat(address,operand);
        strcpy(startingAddress,address);
        
        // program length
        sprintf(temp,"%x",length);
        len=strlen(temp)+1;

        for(int k=len;k<=6;k++){
            strcat(progleng,"0");
        }
        strcat(progleng,temp);

    }

    // write object code
    fprintf(object,"%s^%s^%s^%s\n","H",label,address,progleng);
    
    strcpy(textrecordaddress,address);

    while(strcmp(opcode,"END")!=0){
        objectcode[0]='\0';
        rewind(optab);
        flag=0;

        // search optab for opcode
        while((!feof(optab))){
            fscanf(optab,"%s %s",mnuemonic,value);
            if(strcmp(mnuemonic,opcode)==0){
                flag=1;
                break;
            }
        }

        // if opcode found
        if(flag==1){
            // if symbol in operand field
            if(strcmp(operand,"-")!=0){

                rewind(symtab);
                flag=0;
                // search symtab for operand
                while(!feof(symtab)){
                    fscanf(symtab,"%s %s",symbol,symboladdress);
                    if(strcmp(operand,symbol)==0){
                        flag=1;
                        break;
                    }
                }
                // if symbol not defined
                if(flag!=1){
                    strcpy(symboladdress,"0000");
                    printf("Unknown symbol\n");
                }

            }
            //if no symbol in operand field
            else{
                strcpy(symboladdress,"0000");
            }
            // assemble object code
            strcat(value,symboladdress);
            strcat(objectcode,value);
        }
        // if opcode equal to BYTE or WORD
        else if(strcmp(opcode,"WORD")==0 || strcmp(opcode,"BYTE")==0){

            value[0]='\0';

            if(isDigit(operand)!=0){
                i=strlen(operand)+1;
                while(i<=6){
                    strcat(value,"0");
                    i++;
                }
                strcat(value,operand);
            }else{
                sprintf(temp,"%x",operand);
                i=strlen(temp)+1;
                while(i<=6){
                    strcat(value,"0");
                    i++;
                }
                strcat(value,temp);
            }
            strcpy(objectcode,value);
        }

        // if object code not fit into current text record
        if(strlen(textrecord)+strlen(objectcode)>70){

            // write current text record to object program
            textrecordlength=Length(textrecord)/2;
            sprintf(temp,"%x",textrecordlength);
            fprintf(object,"T^%s^%s%s\n",textrecordaddress,temp,textrecord);
            
            //initialize new text record
            textrecord[0]='\0';
            strcpy(textrecord,address);
        }

            
        // write object code to text record
        if(objectcode[0]!='\0'){
            sprintf(temp,"^%s",objectcode);
            strcat(textrecord,temp);
        }

        // read new line
        fscanf(input,"%s %s %s %s",address,label,opcode,operand);
    }

    // printf("%d",Length(textrecord));

    // write last text record and emd record
    textrecordlength=Length(textrecord)/2;
    sprintf(temp,"%x",textrecordlength);
    fprintf(object,"T^%s^%s%s\n",textrecordaddress,temp,textrecord);
    fprintf(object,"E^%s",startingAddress);
    
    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(object);
    fclose(leng);
}

int isDigit(char number[]){
    int i;
    for(i=0;i<strlen(number);i++){
        if(isdigit(number[i])==0)
            return 0;
    }
    return 1;
}

int Length(char string[]){
    int i=0,not=0;
    while(string[i]!='\0'){
        if(string[i]=='^')
            not++;
        i++;
    }
    return i-not;
}