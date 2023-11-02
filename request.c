
struct HTTP_request{
    char* method;
    char* URI;
    char* params;
    char* HTTP_version;
    unsigned int headers_count;
    char** headers;
    unsigned int attributes_count;
    char* body;
}http_request;

void manage_request(char *buffer , unsigned int size ){
    buffer[size] = '\0';
    char** request = str_split( "\n" , buffer );                                // str_split allocates the memory!!
    char* first_line = request[0];                                              // separate first line of request from rest
    char** headers = &request[1];                                               // keep only headers
    unsigned int headers_count = get_strgs_counter()-1;                         // remember count of the headers -> str_split sets counter
    char** first_line_ = str_split(" " , first_line);                           // split first line
    http_request.method  = first_line_[0];
    // get parameters
    char* uri_params = first_line_[1];
   // char line_size = str_len(uri_params);

    char c;
    char *uri = uri_params;
    char *params = uri_params;

    for (u8 i = 0; i < str_len(uri_params); i++){
        if (uri_params[i] == '?'){
            uri_params[i] = '\0';                                               // end uri at '?'
            uri = uri_params;               
            params = &uri_params[i+1];                                          // begin of parameters
        } 
    }

    if(params == uri_params) params = &uri_params[str_len(uri_params)];         // params is '\0'

    http_request.URI  = uri;
    http_request.params = params;
    http_request.HTTP_version  =  first_line_[2] ;
    http_request.headers_count  = headers_count ;
    http_request.headers  = headers ;
    http_request.body  =  headers[headers_count-1];


}