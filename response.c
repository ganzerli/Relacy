
#define BF_SIZE 1024 * 1024

struct HTTP_response{
        char protocol[9];
        char status_code[25];
        char headers[1024 * 2];
        unsigned int content_length;
        u8 *content;
        char *response_buffer;
        unsigned int response_length;
}http_response;

void add_response_header(char* str){
        unsigned int len = str_len(str);
        len++;
        char header[len];
        header[0] = '\n';
        header[1] = '\0';
        // rewriting request buffer with headers
        str_cat(header, header, str);                                                                           // add last header
        str_cat(http_response.headers, http_response.headers , header);
}

void response_config(char * res_bf){
        http_response.response_buffer = res_bf;                                                                 // defining which buffer contains the response
        http_response.response_length = 0;
        // setting defaults 
        str_cpy(http_response.status_code , "200 OK");
        str_cpy(http_response.protocol , "HTTP/1.1");   
        http_response.headers[0] = '\0';
}

void response_send_file( char* filename ){

        // load the file to send
        char file[BF_SIZE];
        file_load(file , filename);
        // set content in struct
        http_response.content_length = str_len(file);
        http_response.content = file;
        // creating http response

        add_response_header("Content-Type: text/html; charset=utf-8");
        
        unsigned int size;

        char first_line[128];
        str_cpy(first_line , http_response.protocol);
        str_cat(first_line , first_line , " ");
        str_cat(first_line , first_line , http_response.status_code);

        snprintf(http_response.response_buffer , BF_SIZE , "%s%s\nContent-Length: %u\r\n\r\n", first_line , http_response.headers , http_response.content_length);
        http_response.response_length = str_cat(http_response.response_buffer , http_response.response_buffer , file);

}


void response_send_pic(char* filename){

        int8_t content[BF_SIZE - 256];
        size_t size = get_pic(content , filename);

        http_response.content_length = (unsigned int)size;
        http_response.content = content;

        add_response_header("Content-Type: image/png");
        
        char first_line[128];
        str_cpy(first_line , http_response.protocol);
        str_cat(first_line , first_line , " ");
        str_cat(first_line , first_line , http_response.status_code);

        unsigned int head_req_len = snprintf(http_response.response_buffer , BF_SIZE , "%s%s\nContent-Length: %u\r\n\r\n", first_line , http_response.headers , http_response.content_length);

        memcpy(http_response.response_buffer + head_req_len, content, size);

        http_response.response_length = size + head_req_len;

}