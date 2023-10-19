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

    epahcreept_prelude();
    add_var("user"  , "User_Name@http.com"); 
    add_var("password"  , "************************");
    add_var("tree_structure"  , "abc{abc2{abc2.0;abc2.1;abc2.3}abc3{abc3.O;abc3.1}}");
    add_var("brunch_users"  , "name,password,profileid");

    char text[] = "abcdefg<-123-> abcdef <-1234-> abc abfcdadolfefg <-12345->  i234567 <-abcd->  abc abc abcde <-abc-> <-abcd->  <-ab-> <-abcd->abc";
    char** substrings = malloc( sizeof (char*) * 126);
    unsigned int strgs_count = split_n_keep( substrings , text );
    substrings = realloc(substrings , sizeof(char*) * strgs_count );

    for (int i = 0; i < strgs_count; i++){
        printf("\n[%d] --%s" ,i,  substrings[i]);
    }
    free(substrings);


    add_response_header("Server: E-pache 1.0");
    response_send_file("views/html.html");
}


// // // // // // // // // // // // // // // // // // // // // POST CONTROLLERS
// '/'
void ctrl2(){
        response_send_pic("E-pachy_512x512.png");
}