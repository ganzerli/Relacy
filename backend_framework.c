// backend framework
#include "request.c"
#include "response.c"

// CONTROLLERS
#include "controllers.c"

// ROUTER
u8 found;
void route(char* route , void(*controller)() );
void router();




// DEFINE HERE YOUR ROUTES ( URI , CONTROLLER )
void get(){
        route( "/" , ctrl_home );
        route( "/favicon.ico" , ctrl_favicon );
}

void post(){
        route("/" , ctrl2 );
}

// NEEDED TO FREE REQUEST STRINGS
unsigned int backend_framework(char* buffer , unsigned int size){
        unsigned int request_size = size;
        manage_request(buffer , size );
        // use same buffer also for response
        response_config(buffer);
        router();
        // free all the memory allocated for strings in request
        str_free_all();
        return http_response.response_length;;
}


// ROUTER
void route(char* route , void(*controller)() ){
        if(found) return;
        int _len = str_len(http_request.URI);
        if(str_cmp(_len , http_request.URI, route)){
                found = 1;
                controller();
        }

}
void router(){
        found = 0;
        char* method = http_request.method;
        if( str_cmp(3 , "GET" ,method) ) get();
        if( str_cmp(4 , "POST" ,method) ) post();
        // all the others are the same
};