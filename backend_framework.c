// backend framework
#include "request.c"
#include "response.c"

u8 found;

void ctrl_favicon(){

    char content_type[] = "image/gif";
    char * res = http_response.response_buffer;

    int8_t* content[1024*1024];
    size_t size = get_pic(content);

    unsigned int h_size = snprintf(res, 1024*1024, "HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %lu\n\n", content_type, size);

    // secret of c for what are doing char* strings and integers ;)
    memcpy(res + h_size, content, size);
    // anyways will be a stream
    
    http_response.response_length = size + h_size;

}

// controllers from other file
void ctrl_home(){

        char * res = http_response.response_buffer;
        char* response_headers ="HTTP/1.0 200 OK\nServer: E-pacy1.0 Jerryfish\nDate: Mon, 30 Feb 1970 00:11:10 GMT\nContent-type: text/html; charset=UTF-8\nContent-Length: 417\r\n\r\n";
        str_cpy(res , response_headers);
        char html[512];
        file_load(html , "views/html.html");
        str_cat( res, response_headers , html );
        http_response.response_length = str_len(res);
}

void ctrl2(){
        printf("this is another controller\n");
        
}


route(char* route , void(*controller)() ){
        if(found) return;

        int _len = str_len(http_request.URI);

        if(str_cmp(_len , http_request.URI, route)){
                controller();
                found = 1;
        }   

}

///////////// defining
void get(){
        route( "/" , ctrl_home );
        route( "/favicon.ico" , ctrl_favicon );
        

}

void post(){
        route("/" , ctrl2 );
}


router(){
        unsigned int found = 0;
        char* method = http_request.method;
        if( str_cmp(3 , "GET" ,method) ) get();
        if( str_cmp(4 , "POST" ,method) ) post();
};


// size unsigned int is good until 4GB
unsigned int backend_framework(char* buffer , unsigned int size){

        unsigned int request_size = size;


        manage_request(buffer , size , &http_request);

        http_response.response_buffer = buffer;
        http_response.response_length = 0;

        router();
        create_response();


        return http_response.response_length;;
}