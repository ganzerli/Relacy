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
    add_var("<-12345->"  ,  http_request.body);
    
    const char filein[] = "views/html.html";
    const char fileout[] = "tempfile.html";
    epahcreept_makefile(fileout , filein);

    response_send_file(fileout);
    remove(fileout);
    epahcreept_reset();
}


u32 format_command(char* post_request){
    u32 split_index = 0;
    u32 i = 0;
    u32 offset = 0;
    char ch = post_request[0];
    const char slash[] = "%2F";

    while(ch != '\0'){

        // slash
        if(ch == '%'){
            if(str_cmp(str_len(slash), slash , &post_request[i])){
                ch = '/';
                post_request[i-offset] = ch;
                offset+= str_len(slash)-1;
                i+= str_len(slash)-1;                              
            }
        }
        if(ch == '&'){
            post_request[i- offset] = '\0';
            split_index = i-offset+1;
        }else{
            post_request[i-offset] = ch;
        }

        i++;
        ch = post_request[i];

    }

    post_request[i-offset] = '\0';

    printf("\n%s\n" , post_request);
    printf("\n%s\n" , &post_request[split_index]);

    return split_index;

}


u32 compile( char* stringToId , u32* buffer ){
    u32 size = 0;
    u32 i = 0;
    while(stringToId[i] != '='){
        i++;
    }
    printf("\n id of = %u" , i);
    char** splitted = str_split("/", &stringToId[i+1]);

    for(u32 i = 0; i < strgs_counter; i++){
        printf("\n%s" , splitted[i]);
        buffer[i] = word_index(splitted[i]);
        size++;
    }
    return size;
}


void add(){
    // EPAHCREEPT
    epahcreept_reset();

    char* command = http_request.body;
    
    u32 new_node = format_command(command);
    
    u32 data_where[128];
    u32 count = compile(command, data_where);
    //format_command(body);
    for(u32 i = 0; i < count; i++){
        printf("\ndata_where[%u] = %u", i , data_where[i]);
    }


    
    add_var("<-12345->"  , &command[new_node]);
    



    const char filein[] = "views/html.html";
    const char fileout[] = "tempfile.html";
    epahcreept_makefile(fileout , filein);

    response_send_file(fileout);
    remove(fileout);
    epahcreept_reset();

}