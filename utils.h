
char* strConcat(char* result , char* str1, int size1, char* str2, int size2){
    int sum = size1 + size2;
    int incrementor = 0;

    for (int i = 0; i < size1; i++){
        result[i]= str1[i];
        incrementor++;
    }

    for (int i = 0; i < size2; i++){
        result[incrementor+i]= str2[i];
    }

    result[sum-1] = '}';
    result[sum] = '}';
    result[sum+1] = '}';


    return result;
}



int fileWrite(char* content, char* path){
    FILE *fp;
    fp = fopen(path, "w");
 
    if(fp == NULL) {
        printf("file couldn't be opened\n");
        exit(1);
    }
 
    fputs(content,fp);
    fclose(fp);
}



int readFile(char* buffer,int size, char* path){

 FILE *fp = fopen(path, "r");
 char ch = '\0';

    if(fp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    int num = 0;
    ch = getc(fp);
    while(ch != '}') {
        ch = getc(fp);
        printf("%c",ch);
        buffer[num]= ch;
        num++;
    }

    fclose(fp);

    return 0;

}




signed int strLen(char* str){
    signed int c = 0;
    while (str[c] != '\0'){
        c++;
    }
    //printf("Length of the string: %d\n", c);
    return c;
}


char* printPorcamadonna(){
    printf("porcamadonna");
    char* plmdn;
    return plmdn;
}

int countLines(char* buffer, int* indexes){
    signed int length = strLen(buffer);
    signed int count = 0;
    char tempchar = ' ';
    // [0] is for the sie of the array
    signed int i = 1;

    do{
        tempchar = buffer[count];
        if(tempchar == '\n'){
            indexes[i]=count+1;
            i++;
        };
        count++;
    }while(count < length);
    indexes[0] = i;

    return i;
}
