
// group words and have info from buffer perspactive
extern struct words{
    char word[20];
    int size;
    int index;
    int count;
    int timesFound;
  }words;



int strCompare(char * s, char * s2){
    int i=0;
    int result = 0;

    while(s[i]!='\0'){
        if(s[i] == s2[i]){
            result = 1;
        }else{
            result = 0;
            break;
        }
        i++;
    }

    //printf("%s %d",s, result);

    return result;
}

void printPorcamadonna(int num){
    printf("\n");
    printf("%s %d %s %d %s %d %s %d","porcamadonna ",num,"PORCAMADONNA ",num,"porcamadonna",num,"PORCAMADONNA",num);
    printf("\n");
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



int ignoreJs(char* content, char* buffer, int size){

    char ignore = '0';
    int num = 0;
    char ch = '0';

    for (int i = 0; i < size; i++){
        // check fo <script ... > </script> tag
        ch = content[i];
        if(ch == '<'){
            // check if script
            ch = content[i+1];

            if( ch == 's' ){
                ch = content[i+2];
                if( ch == 'c' ){
                    ch = content[i+3];
                    if( ch == 'r' ){
                        // set ignore = true;
                        ignore = '1';
                        i+=7;
                        // printf("%c",ch);
                    }
                }
            }
            if( ch == '/' ){
                ch = content[i+2];
                if( ch == 's' ){
                    ch = content[i+3];
                    if( ch == 'c' ){
                        // set ignore = false;
                        ignore = '0';
                        i+=7;
                        // printf("%c",ch);
                    }
                }
            }
        }   
        ch = content[i+1];
        if(ignore == '0'){
           buffer[num] = content[i];
           //printf("%c",ch);
            num++; 
        }else{
         //   printf("%c",ch);
        }
    }
    buffer[num] ='\0';
    buffer[num+1] ='@';
    buffer[num+2] ='@';
    buffer[num+3] ='\0';
    num += 3;
    return num;
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
               // printf("%c", buffer[num]);
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

int alphabethic(char ch){
    
    int pass = 0;
    char c = '0';

    for (c = 'a'; c <= 'z'; ++c){
        if(ch == c){
            pass = 1;
            break;
        } 
    }
    
    if(ch == ' '){
        pass = 0;
    }

    if(!pass){
        for (c = 'A'; c <= 'Z'; ++c){
            if(ch == c){
                pass = 1;
                break;
            }
        }

    }

    return pass;

}

int trimUnwantedStrLength(char* buf, struct words* wrds, int bufferSize, int min, int max){
    // _c = count;
    int words_c = 0;
    char ch = '0';
    int ch_c = 0;
    int index = 0;
    char word[max];

    for(int i = 0; i < bufferSize; i++){
        ch = buf[i];
        // load char in new word
        word[ch_c] = ch;
        // if word too large, dump all
        if(ch_c >= max){
            // reset index of word[] 
            ch_c = 0;
        }
        // FINDING SPACE LOAD THE WORD IN BUFFER 2
        if(ch == ' '){
            // check for enought chars ,  prepare for saving...
            if(ch_c >= min){
                // save word in buffer 
                wrds[words_c].count = words_c;
                wrds[words_c].index = i;
                wrds[words_c].timesFound = 1;

                for(int w = 0; w < ch_c; w++){
                    buf[index] = word[w];
                    wrds[words_c].word[w] = word[w];
                    // update index for buffer 2 -> result
                   // printf("%c", word[w]);
                    index++;
                    wrds[words_c].size++;
                }
                // collect the number of words saved
                words_c++;
                   //printf("%c", '\n');
            }
            ch_c = 0;
        }
        ch_c++;
    }
    return words_c;
}


int count_reduce(struct words *_wrdArr,int words_num, int _1wrdSize){
   
    int pass = 1;
    int wrds_c = 0;
    char ch = '0';
    char refined[_1wrdSize];
    int refinedI =0;
    int charInRefWord=0;

    struct words _newWordStruct[words_num];

    void cleanArr(char*p){
        for (int r = 0; r < _1wrdSize; r++){
            p[r] = '\0';
        }
    }

    void fillWord(char* p1 , char* p2 ){
        for (int r = 0; r < _1wrdSize; r++){
            p1[r] = p2[r];
        }
    }


    // FIRST, EMPTY ALL WHAT HAS UNWANTED CHARS
    for (int i = 0; i < words_num; i++){
        //clean refined
        cleanArr(refined);
        // check for strange chars, saving only alphabetic in temp str[]
        for (int j = 0; j < _1wrdSize; j++){
            ch = _wrdArr[i].word[j];
            // case char NOT good
            pass = alphabethic(ch);
            if(pass){
                //printf("%c",ch);
                refined[refinedI] = ch;
                refinedI++;
            }

        }
        cleanArr(_wrdArr[i].word);
        // save only if enought chars
        if(refinedI >= 4){
            // having refined word write back in original struct
            for (int k = 0; k < _1wrdSize; k++){
                ch = refined[k];
                _wrdArr[i].word[k] = ch;
            }
            _wrdArr[i].size = refinedI;
        }
        refinedI = 0;
    }

    // START WITH CLEAN ARRAY TO COUNT
    for (int i = 0; i < words_num; i++){
        if(_wrdArr[i].word[0] != '\0'){
            // take first found same word
            if(_wrdArr[i].timesFound == 1){
                // check all the other words if there is
                for (int j = i+1; j < words_num ; j++){
                    if(strCompare(_wrdArr[i].word, _wrdArr[j].word)){
                        _wrdArr[i].timesFound++;
                        // disable entering in the loop for future checks..
                        _wrdArr[j].timesFound = 0;
                    }
                }

                // if found more than 1x
                if( _wrdArr[i].timesFound > 1){
                   // printf("%s %s %s %d\n","word: ", _wrdArr[i].word ," n-found  " ,_wrdArr[i].timesFound);
                    fillWord(_newWordStruct[wrds_c].word, _wrdArr[i].word);

                    _newWordStruct[wrds_c].timesFound = _wrdArr[i].timesFound;
                    _newWordStruct[wrds_c].count = wrds_c;
                    _newWordStruct[wrds_c].index = _wrdArr[i].index;
                    _newWordStruct[wrds_c].size = _wrdArr[i].size;

                    wrds_c++;
                }
            }
        }
    }


    for (int i = 0; i < wrds_c; i++){
       // printf("%d %s %s %s %d %s %d \n", _newWordStruct[i].count, "): ", _newWordStruct[i].word ," n-found  " , _newWordStruct[i].timesFound , " size ",_newWordStruct[i].size );
        
        fillWord(_wrdArr[i].word , _newWordStruct[i].word);
        _wrdArr[i].timesFound = _newWordStruct[i].timesFound;
        _wrdArr[i].count = _newWordStruct[i].count;
        _wrdArr[i].index = _newWordStruct[i].index;
        _wrdArr[i].size = _newWordStruct[i].size;
       // printf("%d %s %s %s %d %s %d \n", _wrdArr[i].count, "): ", _wrdArr[i].word ," n-found  " , _wrdArr[i].timesFound , " size ",_wrdArr[i].size );

    }
    
    // replace all in newwordsstrucr

    return wrds_c;
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

   // printf("%s",s);
    return 0;
}



int fileWrite(char* content, char* path){
    FILE *fp;
    fp = fopen(path, "w");

    char* closingFile = "@@@\0\0";
 
    if(fp == NULL) {
        printf("file couldn't be opened\n");
        exit(1);
    }

    fputs(content,fp);
    fputs(closingFile,fp);
    fclose(fp);

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
