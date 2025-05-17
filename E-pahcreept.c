#include <stdlib.h>
#include <stdio.h>

// A PRELUDE OF A NEW GENERAL PORPOSE PROGRAMMING SCRIPTING LANGUAGE THAT WORKS WELL WITH E-PATHY

    // those will work on parallel
    // is the list of the variables in the environment of E-pacreept.ec

#define EPACREEP_VARS_NUM 128
char *vars[EPACREEP_VARS_NUM];
char *values[EPACREEP_VARS_NUM];
const char arrayend[] = "arrayend";

// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // RESET ALL EPHACREEPT VARIABLE ARCHITECTURE  // //
void epahcreept_reset(){
    vars[0] = arrayend;
    values[0] = arrayend;
}

unsigned int var_count(){
    unsigned int i = 0;
    while( !str_cmp( str_len(vars[i]) , vars[i] , arrayend ) ){
        printf("\npresent: %s = %s" ,vars[i] ,values[i] );
        i++;
    }
    return i;
}

unsigned int var_find(char* varname){
    unsigned int i = 0;
    u8 size = str_len(varname);
    while( !str_cmp( str_len(vars[i]) , vars[i] , arrayend ) ){
        if( str_cmp(size , varname ,vars[i]) ) return i;
        i++;
    }

    return EPACREEP_VARS_NUM +1;

}

void var_concat(char* varname, char* data){
    unsigned int index = var_find(varname);
    char* old_p = values[index];
    unsigned int old_length = str_len(old_p);
    char * new_string = malloc( sizeof (char) * (str_len(data) + old_length + 1 ) );
    str_cat(new_string , old_p , data );
    printf("new string: %s" , new_string);
    free(old_p);
    values[index] = new_string;
}

// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  ADD VAR // // //  // //  // 
void add_var(char* varname , char* value ){
    unsigned int i = 0;
    while( !str_cmp( str_len(vars[i]) , vars[i] , arrayend ) ){
        printf("\npresent: %s = %s" ,vars[i] ,values[i] );
        i++;
    }
    char* p = malloc(sizeof(char) * str_len(value));
    str_cpy(p , value);
    vars[i] = varname; 
    values[i] = p;
    vars[i+1] = arrayend;
    values[i+1] = arrayend;
    printf("\nadded var: %s , value: %s\n\n" , vars[i] , values[i] );
}

// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  // GET VAR // //  // //  //
char* get_var(char* var_name){
    unsigned int i = 0;
    char* ret = "undefined";
    u8 size = str_len(var_name);
    while( !str_cmp( str_len(vars[i]) , vars[i] , arrayend ) ){
        if( str_cmp(size , var_name ,vars[i]) ) return values[i];
        printf("\npresent: %s = %s" ,vars[i] ,values[i] );
        i++;
    }
    return ret;
}

// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  // POPULATE STRINS WITH VALUES IN VARS // // 
void var_to_values(char* buffer, char** strings , unsigned int count){
    char *current_s;
    unsigned int length;
    unsigned int j;
    //                   v <<----[]
    char* replace_string(char* str1 , char* str2){
        const unsigned int length = str_len(str2);
        str1 = malloc( sizeof (char) * length );
        for(int i = 0; i < length; i++){
            str1[i] = str2[i];
        }   
        str1[length] = '\0';
        return str1;
    }
    // looping throught many strings
    for (unsigned int i = 0; i < count; i++){
        j=0;
        // looping throught the variables of epacreept
        while( !str_cmp( str_len(vars[j]) , vars[j] , arrayend ) ){
            length = str_len(vars[j]);
            if( str_cmp(length , strings[i] , vars[j] ) ){
                free(strings[i]);
                strings[i] = replace_string(current_s , values[j]);
            }
            j++;
        }
    }
    buffer[0]='\0';                                                     // preventing sparkling
    // joining string 
     for (unsigned int i = 0; i < count; i++){
        str_cat(buffer , buffer , strings[i]);
        free(strings[i]);
     }
}

// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  // SEARCH INDEXES SURROUNDING THE "VARIABLES" IN THE HTML // // 
// this function is to keep as it is.. dont modulate it

// this function does:
// - checks all chars in the html,' ',' ', until   "<-"
// - writes in indexes where are located begin and end of the searched container for the variable [<]- variable -[>]
// - that is then used in split_n_keep to split the whole html in many strings** 
int find_in_str (char * text, char* from , char* to , unsigned int* indexes){

    char frs_c = from[0];
    char lst_c = to[ ( str_len(to)-1 ) ];

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
        return i;
    }
    unsigned int counter = 0;
    unsigned int index_end = 0;
    unsigned int len = str_len(text);
    for (unsigned int i = 0; i < len; i++){
        if(text[i] == frs_c){
            // check if
            index_end = delicious_lasagna( text , i , from , to);
            if(index_end != 0){
                indexes[counter] = i;
                indexes[counter+1] = index_end;
                i = index_end;
                index_end = 0;
                counter += 2;
            }
        }
    }
    return counter;
}

// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  // SPLIT THROUGHT "str" KEEP ALSO str // // 
// - keep the whole html in the first string until [<]-variable-> mallocking all
// - save also the [<]-variable-[>] in a separated mallocked string

// - practically based on indexes[] from firsts_in_str
// - malloc begin until "<-" , malloc <-variable-> , malloc the rest until next variable or end of html

// then to replace the variables in the html with whatever value is easy to check for "<-variable->" , free that, malloc the value, save the pointer there.

// i know is kind of unreadable, can be better with all of indexes[] , is that the whole relacy is done with the sole purpose to display the result of e-pathy in the html, then was done that it works, nothing much more, for whats about these 2 functions..

unsigned int split_n_keep(char** substrings, char* text){
    unsigned int size = 0;
    unsigned int indexes[512];
    unsigned int counter = find_in_str( text , "<-" , "->" , indexes );
    unsigned int i;
    unsigned int j = 0;
    unsigned int lastIndex = 0;
    unsigned int terator = 0;
    
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
    char* substring = malloc(  ( str_len(&text[j]) + 1 )  * sizeof (char)  );
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

void epahcreept_makefile(const char* fileout , const char* filein){
    // load html file with e-pahcreep syntax in it
    char bf[4096]; 
    file_load(bf,filein);
    // splitting html text form epahcreept variables
    char** substrings = malloc( sizeof (char*) * 128);
    unsigned int strgs_count = split_n_keep( substrings , bf );
    // translate the variables to values and concat all in buffer
    var_to_values(bf,substrings , strgs_count);
    //  create tempfile for html
    file_write( fileout , bf );
    free(substrings);
}





//    J S O N    J S O N    J S O N    J S O N       J  J    S S S S    O O O O    N     N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N    J S O N    J S O N          J    S          0     0    N N   N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N    J S O N    J S O N          J    S S S S    O     O    N N   N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N    J S O N    J S O N          J          S    0     0    N   N N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N    J S O N    J S O N        J            S    0     0    N   N N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N    J S O N    J S O N    J J        S S S S    0 0 0 0    N     N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    

u8 JSON_check_depth(char*data){
    unsigned int begins = 0;
    unsigned int ends = 0;
    unsigned int i = 0;
    u8 max_depth = 0;
    
    // check if begin contains any
    char c = data[i];

    while ( c != '\0'  ){
        if( c == '{' ) begins++;           
        if( c == '[' ) begins++;   

        if( c == '}' ) ends++;           
        if( c == ']' ) ends++;   

        //printf("\n%u\n",  (begins - ends) );
        if( (begins - ends) > max_depth) max_depth++;
        i++;
        c = data[i];
    }
    return max_depth;
} 

// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  // GET SURROUNDING BRACKETS AWAY {} OR [] // //
u8 JSON_uncover(char*data){
    u8 defined = 0;
    if(data[0] == '['){
        defined = 1;
    }
    if(data[0] == '{'){
        defined = 2;
    }
    if(!defined){
        //printf("error: segment not correctly wrapped");
        return 0;
    }

    unsigned int count = str_len(data);
    // just copy everything out of first and last char { [ or } ]
    for(unsigned int i = 1; i < count-1; i++){
        data[i-1] = data[i];
    }
    data[count - 2] = '\0';
    return 1;
}

// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  // REPLACE , WITH \n IN FIRST LAYER -> CURRENT STRING // //
void JSON_split_layer(char* data){
    u8 depth = 0;
    unsigned int i = 0;
    char c = data[i];

    while( c != '\0' ){
        if( c == '{' ) depth++;           
        if( c == '[' ) depth++;   
        if( c == '}' ) depth--;           
        if( c == ']' ) depth--;   

        // when depth is the same layer 
        if(depth == 0){
            if(c == ','){
                data[i] = '\n';
            }
        }        
        i++;
        c = data[i];
    }

}
// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  // REMOVES ALL "" // //
void JSON_unstring(char*data){
    unsigned int offset = 0;
    unsigned int  i = 0;
    char c = data[i];

    while (c != '\0'){
       // printf("%c" , c);

        if( (c != '\"') && (c != ' ') ){
            data[offset] = c;
            offset++;
        }

        i++;
        c= data[i];
    }
    data[offset] = '\0';
    
}
// //  // //  // // //  // //  // // //  // //  // // //  // //  // // //  // //  FIRST ACTION TO DO, TO PREPEARE DATA FOR EXTRACTING // //
void JSON_parse(char*data){
    JSON_unstring(data);
    if(!JSON_uncover(data)) printf("\n\n!!! JSON ERROR !!!\n\n json format returning: undefined \n Is supported only array[,,,] or object{a,a,a} ");
    JSON_split_layer(data);
}


void JSON_print(char*data){
    u8 depth = 0;
    unsigned int i = 0;
    char c = data[i];
    u8 occurred = 1;
    int last_depth = 0;
    void occurring(){
        for (u8 i = 0; i < depth; i++){
            printf("%s" , "   ");
        }
    }
    printf("\n");
    while( c != '\0' ){
        if(occurred){
            occurring();
            occurred = 0;
        }
        if( c == '{' ){ depth++; printf("%c\n",c); occurred = 1;}  
        if( c == '[' ){ depth++; printf("%c\n",c); occurred = 1;}
        if( c == '}' ){ depth--; printf("\n"); occurring(); printf("%c" , c);}
        if( c == ']' ){ depth--; printf("\n"); occurring(); printf("%c" , c);}
        if( c == ',' ){ printf(",\n"); last_depth=99; occurring();}
        if(last_depth == depth){
            printf("%c" , c);
        }
        last_depth = depth;
        i++;
        c = data[i];
    }
    printf("\n");
}

// get data from object having the right name
char* JSON_get(char*resultbf , char* data , char* search ){
    unsigned int i = 0;
    char c = data[i];

    void format_data(char* result){
        u8 i = 0;
        // find ":"
        while (result[i] != ':')i++;                            
        str_cpy( result , &result[i+1]);                            // get over :
        JSON_uncover(result);                                       // uncover -'[' ... -']'  or -'{' ... -'}' 
        JSON_split_layer(result);                                   // and replace ',' with '\n' in same layer
        return;
    }
// get data from this point..
    void load_data(char* datap_){
        unsigned int i = 0;
        while (datap_[i] != '\n'){
            resultbf[i] = datap_[i];
            i++;
            if(datap_[i]=='\0'){
                resultbf[i] = '\0';
                return;
            }
        }
        resultbf[i] = '\0';
    }

    // if first occourrence
    if( str_cmp( str_len(search) ,  search , data ) ) {
        load_data(data);
        format_data(resultbf);
        return resultbf;
    }

    // if new occourrence  '\n'
    while (c != '\0'){
        if( c == '\n' ){
            if( str_cmp( str_len(search) ,  search , &data[i+1] ) ) {
                load_data(&data[i+1]);
                format_data(resultbf);
                return resultbf;
            }
        }
        i++;
        c = data[i];
    }
    str_cpy(resultbf , "[{searched:undefined},{error: something went wrong, in JSON_get}]");
    return resultbf;
}

char* JSON_get_array(char* resultbf, char* data, unsigned int search){
    unsigned int i = 0;
    unsigned int indexes[2048];
    indexes[0] = 0;                                                                     // set 0 as first index
    unsigned int idxs_itr = 1;                                                          // [0] is set, +1

    char c = data[i];
    // get indexes
    while (c != '\0'){   
        if(c == '\n'){
            indexes[idxs_itr] = i+1;                                                    // get over '\n' setting next index
            //i++;
            idxs_itr++;
        }
        i++;
        c = data[i];
    }

    // all the others contain '\n' at the end! , so last can have '\0', easier for keeping same format

    indexes[idxs_itr] = i-1;                                                            
    char result[ indexes[search+1] - indexes[search]];

    // loop gets over'\n' to get next index, next index -1 = '\n' , -2 last char
    if( search != idxs_itr-1 ){
        sub_str(result , data, indexes[search] , (indexes[search+1] -2 ) );

    }else{
        // only the last index has the right index as "last char"
        sub_str(result , data, indexes[search] , indexes[search+1] );
    }
    JSON_uncover(result);
    JSON_split_layer(result);
    str_cpy( resultbf , result );
    return resultbf;
}



//    J S O N    J S O N          /    J S O N       J  J    S S S S    O O O O    N     N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N        /      J S O N          J    S          0     0    N N   N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N      / /      J S O N          J    S S        O     O    N N   N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N      /        J S O N          J        S S    0     0    N   N N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N    /          J S O N        J            S    0     0    N   N N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    
//    J S O N    J S O N    /          J S O N    J J        S S S S    0 0 0 0    N     N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N    J S O N  




//          EEEEEEE                 PPPPPP          A      TTTTTTTTTTT      H       H       Y       Y
//          E                       P     P        AAA          T           H       H        Y     Y
//          EEEEE       #######     P     P       A   A         T           H       H         YY YY
//          E                       PPPPPP       AAAAAAA        T           HHHHHHHHH           Y
//          E                       P           A       A       T           H       H           Y
//          EEEEEEEE                P          A         A      T           H       H           Y


#define DISPLAY_ROOT 0
#define ADD_NODE 1
#define ADD_TO_EXISTING_PATH 2
#define DISPLAY_PATH 3
#define DELETE 4
#define ROOT 0
#define NO_OPTIONS 0
#define HEADER_SIZE 5


u32 epathy_request(u32 *epathy_request_bf, u32 command, u32* data_where, u32 dt_wr_count, u32*data_what, u32 dt_wt_count ){
    // [0] = INSTRUCTION
    epathy_request_bf[0] = command;        // opcode
    // [1] = WHERE COUNT
    epathy_request_bf[1] = dt_wr_count;                   // COUNT OF NODES TO PATH
    // [2] = WHAT COUNT
    epathy_request_bf[2] = dt_wt_count;                   // COUNT OF DATA TO ADD
    // [3] = OPTIONS
    epathy_request_bf[3] = NO_OPTIONS;                    // IF OPTIONS NEEDED
    // [4] = SIZE
    epathy_request_bf[4] = HEADER_SIZE + dt_wr_count + dt_wt_count; // SIZE OF PACKAGE    
    //[5+] DATA WHERE

    for(u32 i = 5; i < dt_wr_count + 5; i++){
        epathy_request_bf[i] = data_where[i-5];
    }
    for(u32 i = 5 + dt_wr_count; i < dt_wr_count + 5 + dt_wt_count; i++ ){
            epathy_request_bf[i] = data_what[i-5-dt_wr_count];
    }
    return 5 + dt_wr_count + dt_wt_count;
}


           //     EEEEEEE                 PPPPPP          A      TTTTTTTTTTT      H       H       Y       Y
          //      E                       P     P        AAA          T           H       H        Y     Y
         //       EEEEE       #######     P     P       A   A         T           H       H         YY YY
        //        E                       PPPPPP       AAAAAAA        T           HHHHHHHHH           Y
       //         E                       P           A       A       T           H       H           Y
      //          EEEEEEEE                P          A         A      T           H       H           Y
