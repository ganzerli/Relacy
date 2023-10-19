#include "E-pahcreept.c"
/* // // // // // // // // // // // // // // // // // //    INFO ABOUT REQUEST

struct HTTP_request{
    char* method;
    char* URI;
    char* HTTP_version;
    unsigned int headers_count;
    char** headers;
    unsigned int attributes_count;
    char* body;
}http_request;

*/

// // // // // // // // // // // // // // // // // // // // GET CONTROLLERS

// '/favicon.ico'
void ctrl_favicon(){
    response_send_pic("E-pachy_512x512.png");
}

// '/'
void ctrl_home(){

    epahcreept_reset();
    add_var("<-ANUSHKA->"  , "<h2>Hi, I am Anushka</h2>");
    add_var("<-12345->"  , "<p>this is a paragraph , and as all paragraps theres a lot of text here..</p>");

    char text[] = "abcdefg<-123-> abcdef <-ANUSHKA-> abc abfcdadolfefg <-12345->  i234567 <-ANUSHKA->  abc abc abcde <-abc-> <-12345->  <-ab-> <-abcd->abc";

    char** substrings = malloc( sizeof (char*) * 126);
    unsigned int strgs_count = split_n_keep( substrings , text );
    substrings = realloc(substrings , sizeof(char*) * strgs_count );
    
    populate_strgs(substrings , strgs_count);

    for (int i = 0; i < strgs_count; i++){
        printf("\n[%d] --%s" ,i,  substrings[i]);
    }
    free(substrings);
    
    // just remembering how it was without epahcreept...
    add_response_header("Server: E-pache 1.0");
    response_send_file("views/html.html");
}

// // // // // // // // // // // // // // // // // // // // // POST CONTROLLERS
// '/'
void ctrl2(){
        response_send_pic("E-pachy_512x512.png");
}