// backend framework
#include "request.c"
#include "response.c"

u8 found;

void ctrl_favicon(){

    char content_type[] = "image/gif";
    char * res = http_response.response_buffer;
    int8_t content[BF_SIZE - 256];
    size_t size = get_pic(content);
    unsigned int h_size = snprintf(res, 1024*1024, "HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %lu\n\n", content_type, size);
    // secret of c for what are doing char* strings and integers ;)
    memcpy(res + h_size, content, size);
    // anyways will be a stream
    http_response.response_length = size + h_size;

}

// controllers from other file
void ctrl_home(){
        add_response_header("Server: E-pache 1.0");
        response_send_file("views/html.html");
}

void ctrl2(){
        printf("this is another controller\n");
        
}




void route(char* route , void(*controller)() ){
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



void router(){
        unsigned int found = 0;
        char* method = http_request.method;
        if( str_cmp(3 , "GET" ,method) ) get();
        if( str_cmp(4 , "POST" ,method) ) post();
};




// size unsigned int is good until 4GB
unsigned int backend_framework(char* buffer , unsigned int size){

        unsigned int request_size = size;
        manage_request(buffer , size , &http_request);
        // use same buffer also for response
        response_config(buffer);
        router();
        return http_response.response_length;;
}