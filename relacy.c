#include <stdlib.h>
#include <stdio.h>

typedef __uint8_t u8;
// 4 bytes unsigned integer
typedef u_int32_t u32;  

// libraries
#include "file.c"
#include "alphabet.c"

// server
#include "server.c"

// now a word is a 32bits unsignet integer, that is what likes e-pathy
u32 word_index(char* word){
    u32 newwordlen = str_len(word);
    // place for files content
    u32 idbf[4096* sizeof(u32)];
    char wordsbf[4096];
    file_load(idbf , INDEXYX);
    file_load(wordsbf , WORDSDUMP);

    // CHECK IF WORD IS PRESENT
    // str_cmp for word and all indexed words
    u32 count = idbf[0];                                            // idbf[0] = count
    u32 index;
    // idbf[0] = count , first index is in 1, next index in 2, next , next ...
    for(u32 i = 1; i <= count; i++){
        index = idbf[i];
        if(str_cmp(newwordlen, word, &wordsbf[index])){             // word existing
            return index;
        }
    }
    // WORD IS NOT INDEXED
    // id-file / id-buffer example
    // assuming COUNT is [1] , count is always at idbf[0]
    // idbf[0]  idbf[1]          idbf[2]          ..
    // [COUNT]  [first word id]  [id for next word] ..
    // in this case next word index needs to be at[2]

    // idbf[count] = index of begin last word in wordsdump.txt
    u32 id_for_new_word = idbf[count+1];
    // concat new word
    str_cpy(&wordsbf[id_for_new_word] , word);
    // update count
    idbf[0] = count+1;
    // keep position for the next word getting indexed
    idbf[count+2] = idbf[count+1] + newwordlen;

    // print
    // for(u32 i = 0; i <= count+2; i++){
    //     printf("\nidbf[%u] = %u" , i , idbf[i]);
    // } 
    // printf("\n%s" ,wordsbf);

    // idbf[0] = count
    // idbf[count] = begin index of last word already present in the loaded file
    // idbf[count+1] = begin index of the new word just indexed
    // idbf[count+2] = index of just indexed word + his lingth -> index for the next
    // count + 3 = total number of 32bits int in the buffer
    const unsigned int filesize = (count+3) * sizeof(u32);
    file_write_bin( INDEXYX , filesize , idbf );
    file_write(WORDSDUMP,wordsbf);

    return id_for_new_word;
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

    u32 index = word_index("abc");
    printf("%u", index);

    // server directives
    const char* PORT = "8086";
    const unsigned int queue = 1;
    // serving using E-pachy.jerryfish
    printf("\nserver connecting..\n");
    relacy_listen( PORT , queue );

}