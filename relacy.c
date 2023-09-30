#include <stdlib.h>
#include <stdio.h>
#include "file.c"

typedef __uint8_t u8;

u8 input_get_word(char *word){

    fgets(word,64,stdin);
    printf("selected word:  %s", word);
    
    u8 count = 0;
    char c = word[count];
    
    while(c != '\0'){
        count ++;
        c = word[count];
    }

    printf("word size: %u\n" , count-1);
    return count - 1 ;
}


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

    u8 wsz = input_get_word(word);

}