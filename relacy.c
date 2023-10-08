#include <stdlib.h>
#include <stdio.h>

typedef __uint8_t u8;
#include "file.c"
#include "outputs.c"
#include "alphabet.c"

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

    // splitting and printing
//    char ** strings = strsplit( "\n" , "GET /search?q=test HTTP/2\nHost: www.bing.com\nUser-Agent: curl/7.54.0\nAccept: */*");
//    print_strings(strings);

    char* port = "8086";
    unsigned int queue = 10;

    unsigned int buflen = 256;
    char buffer[buflen];

    printf("server connecting");
    relacy_listen( port , queue );

}