
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

    return result;
}

// CHARS TO KEEP
int trimNotAZaz09(char s) {
    char c;
    int pass = 0;
    int i = 0;
    char keep[6] = {'.',',',';',':','?','!'};

    // LOWERCAS
    if(!pass){
        for (c = 'a'; c <= 'z'; ++c){
            if(s == c) pass = 1;
        }
    }
    // SPACE
    if(!pass){
        if(s == ' '){
            pass = 1;
        }
    }
    // PUNCTATION
    if(!pass){
        for (i = 0; i < 6; i++){
            if(s == keep[i]) pass = 1;
        }
    }
    //UPPERCASE
    if(!pass){
        for (c = 'A'; c <= 'Z'; ++c){
            if(s == c) pass = 1;
        }
    }
    // DIGITS
    if(!pass){
        for (c = '0'; c <= '9'; ++c){
            if(s == c) pass = 1;
        }
    }

    return pass;
}


void ignoreHtml(char* content, char* buffer, int size){

    char ignore = '0';
    int num = 0;

    for (int i = 0; i < size; i++){
        // check fo opening tag
        if(content[i] == '<'){
            ignore = '1';
        } 

        if(ignore == '0'){
            if(trimNotAZaz09(content[i])){
                buffer[num] = content[i];
                num++; 
                printf("%c", buffer[num]);
            }
        }

        if(content[i] == '>'){
            ignore = '0';
            buffer[num] = ' ';
            num++; 
        }

    }

    buffer[num] ='\0';
    buffer[num+1] ='@';
    buffer[num+2] ='@';
    buffer[num+3] ='\0';
    num += 3;

}




int replaceChar(char * s, char ch, char ch2){
    int i=0;
    while(s[i]!='\0')
    {
        if(s[i]==ch)
        {
            s[i]=ch2;
        }
        i++;
    }

    printf("%s",s);
    return 0;
}

int strCompare(char * s, char * s2){
    int i=0;
    int result = 0;

    while(s[i]!='\0')
    {
        if(s[i] == s2[i]){
            result = 1;
        }
        i++;
    }

    printf("%s %d",s, result);

    return result;
}

int fileWrite(char* content, char* path){
    FILE *fp;
    fp = fopen(path, "w");

    char* closingFile = "@@@\0\0";
 
    if(fp == NULL) {
        printf("file couldn't be opened\n");
        exit(1);
    }

    printf("11111111111111111\n");

 
    fputs(content,fp);
    fputs(closingFile,fp);
    fclose(fp);

    printf("77777777777777777777\n");

}


int readFile(char* buffer,int size, char* path){

 FILE *fp = fopen(path, "r");
 char ch = '\0';
 char flag = '0';

    if(fp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    int num = 0;
    ch = getc(fp);
    
    while(1) {
        if(ch == '@'){
            flag = '@';
        }

        buffer[num]= ch;

        ch = getc(fp);

        //printf("%c",ch);

        if( flag == '@'){
            if(ch == '@'){
                buffer[num+1] = '\0';
                buffer[num+1] = '@';
                buffer[num+1] = '@';
                break;
            }else{
                flag = '0';
            }
        }
        num++;
    }

    fclose(fp);
    return num;

}

signed int strLen(char* str){
    signed int c = 0;
    while (str[c] != '\0'){
        c++;
    }
    //printf("Length of the string: %d\n", c);
    return c;
}

void printPorcamadonna(int num){
    printf("\n");
    printf("%s %d %s %d %s %d %s %d","porcamadonna ",num,"PORCAMADONNA ",num,"porcamadonna",num,"PORCAMADONNA",num);
    printf("\n");
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
