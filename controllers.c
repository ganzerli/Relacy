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
    add_var("<-12345->" , "<p>this is a paragraph , and as all paragraps theres a lot of text here..</p>");

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


//                      P O S T    C O N T R O L L E R S


//                   P P P        O O        S S S      T T T T T                                        
//                   P    P     O     O     S               T                                   
//                   P P P      O     O      S S S          T                                       
//                   P          O     O           S         T
//                   P            0 0       S S S           T                                                                                                             



//        '/'
//       '/'
//      '/'


void dev(){
        // forwarding to e-pathy
    u32 epathy_response_buffer[4096];

    u32 ept_req_bf[HEADER_SIZE + 2 + 1 +1];
    u32 data_where[2] = { 0x00002222 , 0x00002223 };
    u32 data_what[1] = {0};

    u32 req_size = epathy_request(ept_req_bf , DISPLAY_PATH, data_where, 2, data_what , 0 );

    for(u32 i = 0 ; i < req_size; i++){
    }
    unsigned int res_size = client_call( "127.0.0.1" , "8680", ept_req_bf , req_size , epathy_response_buffer );
    res_size /= sizeof (u32);

    for(u32 i = 0; i < res_size; i++){
    }
    //snprintf( stdout , res_size , "\n%u", epathy_response_buffer[0]);
    //  create tempfile for html
    file_write("tempfile.html", epathy_response_buffer);
    response_send_file("tempfile.html");
    remove("tempfile.html");

}

void display(){
    // EPAHCREEPT
    epahcreept_reset();
    add_var("<-12345->"  , "<p>node should be like that</p>");

    const char filein[] = "views/html.html";
    const char fileout[] = "tempfile.html";
    epahcreept_makefile(fileout , filein);

    response_send_file(fileout);
    remove(fileout);
    epahcreept_reset();

}

void add(){
    // EPAHCREEPT
    epahcreept_reset();
    add_var("<-12345->"  , "<p>ADD: option not available yet..</p>");

    char* body = http_request.body;
    
    const char filein[] = "views/html.html";
    const char fileout[] = "tempfile.html";
    epahcreept_makefile(fileout , filein);

    response_send_file(fileout);
    remove(fileout);
    epahcreept_reset();

}