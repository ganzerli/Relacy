

void manage_request(char *buffer , unsigned int size , struct HTTP_request* http_request){
    buffer[size] = '\0';

    char** request = str_split( "\n" , buffer );                                // str_split allocates the memory!!
    
    char* first_line = request[0];                                            // separate first line of request from rest
    char** headers = &request[1];                                              // keep only headers
    unsigned int headers_count = get_strgs_counter()-1;                        // remember count of the headers -> str_split sets counter
                                                                                    
    char** first_line_ = str_split(" " , first_line);                          // split first line
    //set_strgs_counter(3);
    //print_strings(first_line_);

    const char* METHOD = first_line_[0];
    const char* URI = first_line_[1];
    const char* HTTP_VERSION = first_line_[2];


    //printf("last header: %s \n" , headers[headers_count-1]);

    http_request->method  = METHOD;
    http_request->URI  = URI;
    http_request->HTTP_version  =  HTTP_VERSION ;
    http_request->headers_count  = headers_count ;
    http_request->headers  = headers ;
    http_request->body  =  headers[headers_count-1];

    // str_split & print_strings are not good nested
    //set_strgs_counter(headers_count);
    //print_strings(headers);

}


