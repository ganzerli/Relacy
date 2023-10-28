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

    // EPAHCREEPT
    epahcreept_reset();
    //add_var("<-VARNAME_1->"  , "<h2>Hi, I am Josefine</h2>");
    add_var("<-12345->"  , "<p>this is a paragraph , and as all paragraps theres a lot of text here..</p>");

    // load html file with e-pahcreep syntax in it
    char bf[1024]; 
    file_load(bf,"views/html.html");

    // can be better
    char** substrings = malloc( sizeof (char*) * 126);
    unsigned int strgs_count = split_n_keep( substrings , bf );
    substrings = realloc(substrings , sizeof(char*) * strgs_count );
    
    // change variables in html of file with values
    var_to_values(bf,substrings , strgs_count);

    //  create tempfile for html
    file_write(bf, "tempfile.html");
    free(substrings);

    ///// JSON JSON JSON JSON JSON JSON JSON JSON JSON JSON JSON JSON 
    // char* dt = "{\"data\": [{\"type\": \"articles\",\"id\": \"1\",\"attributes\": {\"title\": \"JSON:API paints my bikeshed!\",\"body\": \"The shortest article. Ever.\"},\"relationships\": {\"author\": {\"data\": {\"id\": \"42\", \"type\": \"people\"}}}}],\"included\": [{\"type\": \"people\",\"id\": \"42\",\"attributes\": {\"name\": \"John\"}},{\"type\": \"people\",\"id\": \"24\",\"attributes\": {\"name\": \"Doe\"}}]}";
    // char result_buffer[1024];
    // char data [1024];
    // str_cpy(data , dt);
    // JSON_print(data);
    // JSON_parse(data);
    // JSON_print(data);
    // JSON_get(result_buffer , data , "included");
    // JSON_print(result_buffer);
    // JSON_get_array(result_buffer, result_buffer , 1);
    // JSON_print(result_buffer);
    // JSON_get(result_buffer , result_buffer , "attributes");
    // JSON_print(result_buffer);
    // JSON_get(result_buffer , result_buffer , "name");
    // JSON_print(result_buffer);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // just remembering how it was without epahcreept...
    add_response_header("Server: E-pache 1.0");
    response_send_file("tempfile.html");
    // remove temp file
    remove("tempfile.html");
}

// // // // // // // // // // // // // // // // // // // // // POST CONTROLLERS
// '/'
void ctrl2(){
        response_send_pic("E-pachy_512x512.png");
}