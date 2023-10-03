// ALL WHAT HAS TO DO WITH ALPHABET

struct index {
    unsigned int size;
    unsigned int index;
};

unsigned int crazy_global_counter = 0;


// rewrites in the same buffer the allowed charachters and adds 0 at the end
unsigned short str_format(char* word){

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
// //  // //  // //  // //  // //  // //  // //  // //  // //  // // LENGT OF STRING // //  // //  // //  // //  
unsigned int str_len(char* str){
    unsigned int size = 0;
    unsigned int i = 0;
        while(str[i] != '\0'){
            size++;
            i++;
        }
    return size;
}
// //  // //  // //  // //  // //  // //  // //  // //  // //  // // COMPARE 2 STRINGS // //  // //  // //  // //  
unsigned char str_cmp(unsigned int size, char* _1 , char* _2){
    unsigned char result = 1;
    for(unsigned int i = 0; i < size; i++){
        if (_1[i] != _2[i]) return 0;
    }
    return result;
}


// //  // //  // //  // //  // //  // //  // //  // //  // //  // // PREPROCESS STRING // //  // //  // //  // //  
struct index* strpreprocess(char* splitter , char* str){
    // splitter , str : size
    unsigned int spl_sz = str_len(splitter);
    unsigned int str_sz = str_len(str);

    // get first char 
    register char frc = splitter[0];    

    struct index iiddxx;
    // worst case scenario
    struct index *idx_s = malloc(sizeof iiddxx * (str_sz / 2) );

    // set o as first index
    unsigned int indextosave = 0;

    // iterators
    unsigned int i = 0;
    unsigned int struct_counter = 0;
    
    while ( str[i] != '\0' ){
        // chaeck if first char of splitter is found
        if(str[i] == frc){
            if( str_cmp(spl_sz , splitter , &str[i]) ) {
                iiddxx.index = indextosave;
                iiddxx.size = i - indextosave;                                                                      // size of that part is indextosave = 0; i = 99; splitter found = i 
                // set iterators
                i+= spl_sz;                                                                                         //  set i after splitter   ab[c]<,>[i]bcdef
                indextosave = i;                                                                                    // set indx after splitter ab c <,>[a]bcdef

                // load struct in array of structs
                idx_s[struct_counter++] = iiddxx;
            }
        }
        i++;
    }
    // collecting the last one
    iiddxx.index = indextosave;
    iiddxx.size = i - indextosave;
    idx_s[struct_counter] = iiddxx;

    for(i = 0 ; i <= struct_counter; i++){
        iiddxx = idx_s[i];
        printf("index saved=%u\nsize=%u\n",iiddxx.index , iiddxx.size );
    }

    idx_s = realloc(idx_s , sizeof(iiddxx)* struct_counter);
    crazy_global_counter = struct_counter;

    return idx_s;
}



