
struct HTTP_request{
    char* method;
    char* URI;
    char* HTTP_version;
    unsigned int headers_count;
    char** headers;
    unsigned int attributes_count;
    char* body;
}http_request;

void manage_request(char *buffer , unsigned int size , struct HTTP_request * req){
    buffer[size] = '\0';

    char** request = str_split( "\n" , buffer );                                // str_split allocates the memory!!
    
    char* first_line = request[0];                                              // separate first line of request from rest
    char** headers = &request[1];                                               // keep only headers
    unsigned int headers_count = get_strgs_counter()-1;                         // remember count of the headers -> str_split sets counter
                                                                                    
    char** first_line_ = str_split(" " , first_line);                           // split first line

    req->method  = first_line_[0];
    req->URI  = first_line_[1];
    req->HTTP_version  =  first_line_[2] ;
    req->headers_count  = headers_count ;
    req->headers  = headers ;
    req->body  =  headers[headers_count-1];

}