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

#define ADD_NODE 1
#define DIAPLAY_PATH 3
#define ROOT 1
#define NO_OPTIONS 0

void dev(){
        // forwarding to e-pathy
    u32 epathy_response_buffer[4096];
    
    const unsigned int HEADER_SIZE = 5;
    u32 epathy_request[ HEADER_SIZE + 2 + 0 ];

    // [0] = INSTRUCTION
    epathy_request[0] = DIAPLAY_PATH;        // opcode
    // [1] = WHERE COUNT
    epathy_request[1] = 2;                   // COUNT OF NODES TO PATH
    // [2] = WHAT COUNT
    epathy_request[2] = 1;                   // COUNT OF DATA TO ADD
    // [3] = OPTIONS
    epathy_request[3] = NO_OPTIONS;          // IF OPTIONS NEEDED
    // [4] = SIZE
    epathy_request[4] = HEADER_SIZE + epathy_request[1] + epathy_request[2];// SIZE OF PACKAGE    

    //[5+] DATA WHERE
    //epathy_request[5] = 0x00000000;             // WHEN ROOT 0
    epathy_request[5] = 0x00002222;
    epathy_request[6] = 0x00002223;

    // DATA WHAT
    //epathy_request[6] = 0x00002223;
 

    unsigned int res_size = client_call( "127.0.0.1" , "8680", epathy_request , epathy_request[4] , epathy_response_buffer );
    res_size /= sizeof (u32);

    printf("\nres_size =%u", res_size);
    for(u32 i = 0; i < res_size; i++){
        printf("\ne-pathy response: %0x", epathy_response_buffer[i]);
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