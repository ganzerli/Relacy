#include "E-pahcreept.c"
/* // // // // // // // // // // // // // // // // // //    INFO ABOUT REQUEST
struct HTTP_request{
    char* method;
    char* URI;
    char* params;
    char* HTTP_version;
    unsigned int headers_count;
    char** headers;
    unsigned int attributes_count;
    char* body;
}http_request;*/

//                   // G E T    C O N T R O L L E R S 
// '/favicon.ico'
void ctrl_favicon(){
    response_send_pic("favicon.ico");
}
// 'images'
void ctrl_image(){
    response_send_pic(http_request.params);
}

// '/'
void ctrl_home(){
    // EPAHCREEPT
    epahcreept_reset();
    add_var("<-12345->"  , "<p>this is a paragraph , and as all paragraps theres a lot of text here..</p>");

    // load html file with e-pahcreep syntax in it
    char bf[1024]; 
    file_load(bf,"views/html.html");
    // splitting html text form epahcreept variables
    char** substrings = malloc( sizeof (char*) * 126);
    unsigned int strgs_count = split_n_keep( substrings , bf );
    // translate the variables to values and concat all in buffer
    var_to_values(bf,substrings , strgs_count);
    //  create tempfile for html
    file_write(bf, "tempfile.html");
    free(substrings);

    // char* dt = "{\"data\": [{\"type\": \"articles\",\"id\": \"1\",\"attributes\": {\"title\": \"JSON:API paints my bikeshed!\",\"body\": \"The shortest article. Ever.\"},\"relationships\": {\"author\": {\"data\": {\"id\": \"42\", \"type\": \"people\"}}}}],\"included\": [{\"type\": \"people\",\"id\": \"42\",\"attributes\": {\"name\": \"John\"}},{\"type\": \"people\",\"id\": \"24\",\"attributes\": {\"name\": \"Doe\"}}]}";
    // char result_buffer[1024] , data[1024]
    // str_cpy(data , dt);
    // JSON_parse(data);
    // JSON_get(result_buffer , data , "included");
    // JSON_get_array(result_buffer, result_buffer , 1);
    // JSON_get(result_buffer , result_buffer , "attributes");
    // JSON_get(result_buffer , result_buffer , "name");

    // just remembering how it was without epahcreept...
    add_response_header("Server: E-pache 1.0");
    response_send_file("tempfile.html");
    remove("tempfile.html");
    epahcreept_reset();
}

//                      // P O S T    C O N T R O L L E R S
// '/'
void ctrl2(){
        response_send_pic("E-pachy_512x512.png");

}