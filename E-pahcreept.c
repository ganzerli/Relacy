// A PRELUDE OF A NEW GENERAL PORPOSE PROGRAMMING LANGUAGE THAT WORKS WELL WITH E-PATHY

    // those will work on parallel
    // is the list of the variables in the environment of E-pacreept.ec

#define EPACREEP_VARS_NUM 126

    char *vars[EPACREEP_VARS_NUM];
    char *values[EPACREEP_VARS_NUM];
    const char arrayend[] = "arrayend";

void epahcreept_prelude(){
    vars[0] = arrayend;
    values[0] = arrayend;
}

void add_var(char* varname , char* value ){
    unsigned int i = 0;
    while( !str_cmp( str_len(vars[i]) , vars[i] , arrayend ) ){
        printf("\npresent: %s = %s" ,vars[i] ,values[i] );
        i++;
    }
    vars[i] = varname; 
    values[i] = value;
    vars[i+1] = arrayend;
    values[i+1] = arrayend;
    printf("\nadded var: %s , value: %s\n\n" , vars[i] , values[i] );
}


// this function is to keep as it is.. dont modulate it
int find_in_str (char * text, char* from , char* to , unsigned int* indexes){
    unsigned int i = 0;
    char frs_c = from[0];
    char lst_c = to[ ( str_len(to)-1 ) ];
    char c = text[0];
    unsigned int delicious_lasagna(char* text, unsigned int i , char* begin  , char* end) {
        u8 bg_sz = str_len(begin);
        u8 nd_sz = str_len(end);
        unsigned int index_begin = 0;
        unsigned int index_end = 0;
        unsigned int j = 0;
        if(str_cmp( bg_sz , begin , &text[i] ) ){
            index_begin = i;
            j = bg_sz;
            while ( text[ i + j ] != '\0'){
                if( text [i + j] == end[0]){
                    if (str_cmp(nd_sz , end , &text[i+j])){
                        index_end = i + j + nd_sz - 1;
                        return index_end;
                    }
                }
                j++;
            }
        } 
        return 0;
    }
    unsigned int counter = 0;
    unsigned int index_end = 0;
    while (c != '\0'){
        if(c == frs_c){
            // check if
            index_end = delicious_lasagna( text , i , "<-" , "->");
            if(index_end != 0){
                indexes[counter] = i;
                indexes[counter+1] = index_end;
                i = index_end;
                index_end = 0;
                counter += 2;
                printf("i = %u \n" , i);
            }else{
                break;
            }     
        }
        i++;
        c = text[i];
    }
    return counter;
}


unsigned int split_n_keep(char** substrings, char* text){
    unsigned int size = 0;
    unsigned int indexes[512];
    unsigned int counter = find_in_str( text , "<-" , "->" , indexes );
    unsigned int i;
    unsigned int j = 0;
    unsigned int lastIndex = 0;
    unsigned int terator = 0;;
    for (i = 0; i < counter; i++){
        //                     0 1 2 3 4 5 6 7 8 9          
        // indexes[i] = 9 = <                   [<][-][a][b][-][>]
        //       j < indexes[i]              [ ]                   good stop splitting
        //       j < indexes[i]   not good stop splitting   [ ]    ops.. and the [>] ??? 
        if( i % 2 == 0){
            lastIndex = indexes[i];
        }else{
            lastIndex = indexes[i]+1;
        }
        char *substring = malloc( lastIndex - j + 1 );
        while( j < lastIndex ){                                                     // continue collecting until next index
            substring[terator] = text[j];
            j++;
            terator++;
        }
        substring[terator] = '\0';                                                  // padding 0
        terator = 0;
        substrings[i] = substring;                                                  // saving new string in strings
    }
    // collect the last part of text
    char* substring = malloc(  ( str_len(&text[j]) + 1 )  * sizeof (char*)  );
    terator = 0;
    while (text[j] != '\0'){
        substring[terator] = text[j];
        j++;
        terator++;
    }
    substring[terator] = '\0';
    substrings[i] = substring;
    return i+1;
}


