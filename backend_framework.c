// backend framework
#include "request.c"
#include "response.c"

char* URI_;

// controllers from other file
void ctrl(){
        printf("this is a controller\n");
}

void ctrl2(){
        printf("this is another controller\n");
}


route(char* route , void(*controller)() ){
        int _len = str_len(URI_);
        if(str_cmp(_len , URI_ , route))  controller();
}

///////////// defining
void get(){
        route( "/" , ctrl );
}

void post(char* body){
        route("/" , ctrl2 );
}


router(char* method , char* URI , char* body){
        URI_ = URI; 
        if( str_cmp(3 , "GET" ,method) ) get( );
        if( str_cmp(4 , "POST" ,method) ) post( body );
};


// size unsigned int is good until 4GB
unsigned int backend_framework(char* buffer , unsigned int size){

        unsigned int request_size = size;
        unsigned int response_size = size;

        struct HTTP_request http_request;

        // manage request
        manage_request(buffer , size , &http_request);

        router(http_request.method , http_request.URI, http_request.body);

        // create response
        response_size = create_response(buffer);

        return response_size;
}