#include <stdlib.h>
#include <stdio.h>

typedef __uint8_t u8;
// 4 bytes unsigned integer
typedef u_int32_t  u32;  

// libraries
#include "file.c"
#include "alphabet.c"

// server
#include "server.c"

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

    char* port = "8086";
    unsigned int queue = 10;

    // serving using E-pachy.jerryfish
    printf("server connecting..\n");
    relacy_listen( port , queue );

}