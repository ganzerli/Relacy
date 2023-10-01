// ALL WHAT HAS TO DO WITH ALPHABET

// rewrites in the same buffer the allowed charachters and adds 0 at the end
unsigned short int str_format(char* word){

    u8 count = 0;
    u8 check = 0;
    unsigned int i = 0;
    char c = word[i];

    while(c != '\0'){
        if( (u8) c > ' ') check++;
        if( (u8) c < 127) check++;
        if(check == 2){
            word[count] = word[i];
            //printf("%c", word[count]);
            count++;
        }
        check = 0;
        i++;
        c = word[i];
    }
    word[count] = '\0';
    return count;
}

// dreaming a world where no libraries already exist, no univerities, no predefied quantities, just a list, of where to get what... where the poor is really the poor, and the other, is in one of those places.
unsigned int str_conc(char* s1 , char* s2 , char* result){
    unsigned int zise = 0;
    unsigned int i = 0;

    while (s1[i] != '\0'){
        result[i] = s1[i];
        i++;
    }
    zise = i;
    i = 0;
    while (s2[i] != '\0'){
        result[zise] = s2[i];
        i++;
        zise++;
    }
    result[zise] = '\0';
    return zise;
}