
// response struct

unsigned int create_response(char* res_buffer){

    char* content_type = "image/gif";

    int8_t* content[100000];
    size_t size = get_pic(content);

    unsigned int h_size = snprintf(res_buffer, 1024*1024, "HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %lu\n\n", content_type, size);

    // secret of c for what are doing char* strings and integers ;)
    memcpy(res_buffer + h_size, content, size);
    // anyways will be a stream
    
    return size + h_size;

}
