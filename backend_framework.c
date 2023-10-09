// backend framework
#include "request.c"
#include "response.c"




void routes_GET(){


}

void routes_POST(){

}


// size unsigned int is good until 4GB
unsigned int backend_framework(char* buffer , unsigned int size){

        unsigned int request_size = size;
        unsigned int response_size = size;

        struct HTTP_request{
                char* method;
                char* URI;
                char* HTTP_version;
                unsigned int header_count;
                char** headers;
                unsigned int attributes_count;
                char* body;
        }http_request;

        // manage request
        manage_request(buffer , size , &http_request);

        //select_commands();

        //get_result();
        
        // create response
        response_size = create_response(buffer);

        return response_size;
}