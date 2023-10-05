#include <stdlib.h>
#include <stdio.h>

typedef __uint8_t u8;
#include "file.c"
#include "outputs.c"
#include "alphabet.c"


//  // //  // //  // //  // //  // //  // //  // //  // //  // //  // //  // // USER PROMPT FOR ONE WORD TO ONECOMPLETESENTENCE // //  // //  // //  // //  // //  // //  // //  // //  // //  // 
u8 input_get_word(char *word){

    // user prompt
    char output[OUT_SIZE];
    char* o = gnu_Output(0,output);
    o_ut(o);
    // input
    fgets(word,64,stdin);
    unsigned short int count = str_format(word);
    // printing formatted 
    o = gnu_Output(1,o);
    o_ut(o);
    printf(" %s\n", word);
    return count ;
}

//  // //  // //  // //  // //  // //  // //  // //  // //  // //  // //  // //  // //  // //  // //  M A I N  // //  // //  // //  // //  // //  // //  // //  // //  // //  // //  // //  // //  // 
void main(){
    printf("#################################################################\n");
    printf("#                                                               #\n");
    printf("#                       WELCOME TO RELACY                       #\n");
    printf("#   Relacy is an interface connecting to e-paty.                #\n");
    printf("#   With relacy you can navigate in e-pathy througt paths.      #\n");
    printf("#   Create a database with e-paty.                              #\n");
    printf("#   With relacy the research for words is extremely fast,       #\n");
    printf("#   the shape of the databse is not even a question,            #\n");
    printf("#   humans does not apply to relacy, relacy applies to humnas   #\n");
    printf("#   Tecknology should help, relacy is one of the answers.       #\n");
    printf("#                                                               #\n");
    printf("#################################################################\n");
    printf("\n");

    // check existence of files
    relacy_check();

    // enought for 1 word , even in dutch, the longest dutch word according to lingo is 60 chars
    char word[64];
    u8 zis_e = input_get_word(word);

    // splitting and printing
    char ** strings = strsplit( "\n" , "GET /search?q=test HTTP/2\nHost: www.bing.com\nUser-Agent: curl/7.54.0\nAccept: */*");
    unsigned int count = get_crazyglobalcounter();
    for (unsigned int i = 0; i < count; i++){
        printf("%s\n" , strings[i] );
    }
    


}