
#include <string.h>

unsigned int create_response(char* res_buffer){

    // char* response_headers ="HTTP/1.0 200 OK\nServer: E-pacy1.0 Jerryfish\nDate: Mon, 30 Feb 1970 00:11:10 GMT\nContent-type: text/html; charset=UTF-8\nContent-Length: 417\r\n\r\n";
    // str_cpy(res_buffer , response_headers);
    // char html[512];
    // file_load(html , "views/html.html");
    // str_cat( res_buffer, response_headers , html );
    // return str_len(res_buffer);
    
    char* content_type = "image/gif";

    int8_t* content[100000];
    size_t size = get_pic(content);

    unsigned int h_size = snprintf(res_buffer, 1024*1024, "HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %lu\n\n", content_type, size);

    // secret of c for what are doing char* strings and integers ;)
    memcpy(res_buffer + h_size, content, size);
    // anyways will be a stream
    
    return size + h_size;

}