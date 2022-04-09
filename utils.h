
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
    if(fp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

     while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
        //fputs("|*\n", stdout);  // marker string used to show where the content of the chunk array has ended
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

    result[sum-2] = '\0';




    return result;
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
