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
    response_send_pic("E-pachy_512x512.png");
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

    const char filein[] = "views/html.html";
    const char fileout[] = "tempfile.html";
    epahcreept_makefile(fileout , filein);

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
    response_send_file(fileout);
    remove(fileout);
    epahcreept_reset();
}

//                      // P O S T    C O N T R O L L E R S
// '/'
void ctrl2(){
        // forwarding to e-pathy
    u32 epathy_response[4096];
    u32 epathy_request[4+3];

    // [0] = INSTRUCTION
    epathy_request[0] = 99;     // opcode
    // [1] = WHERE 
    epathy_request[1] = 0;      // path begin (indexed), 0 = ROOT
    // [2] = count   
    epathy_request[2] = 3;      // count
    epathy_request[3] = 0;      // options

    //[4+] DATA
    epathy_request[4] = 0x10000001;
    epathy_request[5] = 0x11E77011;
    epathy_request[6] = 0x10000001;

    unsigned int res_size = client_call( "127.0.0.1" , "8680", epathy_request , 7 , epathy_response );
    res_size /= sizeof (u32);
    
    for(u32 i = 0; i < res_size; i++){
         printf("\ne-pathy response: %0x , res size= %u", epathy_response[i] , res_size);
    }

    //snprintf( stdout , res_size , "\n%u", epathy_response[0]);

    //  create tempfile for html
    file_write(epathy_response, "tempfile.html");
    response_send_file("tempfile.html");
    remove("tempfile.html");

}