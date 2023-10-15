// backend framework
#include "request.c"
#include "response.c"

u8 found;

void ctrl_favicon(){
        response_send_pic("E-pachy_512x512.png");

}

// controllers from other file
void ctrl_home(){

        add_response_header("Server: E-pache 1.0");
        response_send_file("views/html.html");


}

void ctrl2(){
}


void route(char* route , void(*controller)() ){
        if(found) return;


        int _len = str_len(http_request.URI);

        if(str_cmp(_len , http_request.URI, route)){
                found = 1;
                controller();
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
        found = 0;
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