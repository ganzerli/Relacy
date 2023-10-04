// ALL WHAT HAS TO DO WITH ALPHABET

struct index {
    unsigned int size;
    unsigned int index;
};

unsigned int crazy_global_counter = 0;

void set_crazyglobalcounter(unsigned int n){
    crazy_global_counter = n;
}

unsigned int get_crazyglobalcounter(){
    return crazy_global_counter;
}


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

// //  // //  // //  // //  // //  // //  // //  // //  // //  // // PREPROCESS STRING , LOAD STRUCTS WITH INDEX AND SIZE OF SUBSTRINGS // //  // //  // //  // //  
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
    unsigned int structs_counter = 0;
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
                idx_s[structs_counter++] = iiddxx;
            }
        }
        i++;
    }
    // collecting the last one
    iiddxx.index = indextosave;
    iiddxx.size = i - indextosave;
    idx_s[structs_counter] = iiddxx;
    // memory
    idx_s = realloc(idx_s , sizeof(iiddxx)* structs_counter);
    set_crazyglobalcounter(structs_counter + 1);
    return idx_s;
}

// //  // //  // //  // //  // //  // //  // //  // //  // //  // // GET ARRAY OF POINTERS FOR STRINGS // //  // //  // //  // //  
char ** strsplit(char* splitter , char* str){
    // getting struct array of data abou splitting
    struct index* idx_s;
    idx_s = strpreprocess(splitter , str);
    // knowing size of array of pointers
    unsigned int count = get_crazyglobalcounter();
    char ** splitted_strings = malloc( sizeof (char*) * count );
    // get substring from to following index structure
    char* new_string_from(char* str , unsigned int index , unsigned int size){
        char* newstr = malloc( (sizeof (char) * size) + 1 );
        for (unsigned int i = 0; i < size; i++){
            newstr[i] = str[index + i];
        }
        newstr[size] = '\0';
        return newstr;
    };
    // making a new string substringing str and saving the pointer in splitted_strings
    char *newstr;
    for (unsigned int i = 0; i < count; i++){
        newstr = new_string_from(str , idx_s[i].index, idx_s[i].size ) ;
        splitted_strings[i] = newstr;
    }
    // is already count, but just in this unix time
    set_crazyglobalcounter(count);
    free(idx_s);
    return splitted_strings;
}
