
#define BF_SIZE 1024 * 1024

struct HTTP_response{
        char protocol[9];
        char status_code[25];
        char* headers;
        unsigned int content_length;
        u8 *content;
        char *response_buffer;
        unsigned int response_length;
}http_response;

void add_response_header(char* str){
        unsigned int len = str_len(str);
        char header[len+1];
        header[0] = '\n';
        header[1] = '\0';
        // rewriting request buffer with headers
        str_cat(http_response.response_buffer, http_response.response_buffer, str);                             // add last header
        str_cat(http_response.response_buffer, http_response.response_buffer , header);
        http_response.headers = http_response.response_buffer;
}

void response_config(char * res_bf){
        res_bf[0] = '\0';                                                                                       // reset buffer for str_ functions()
        http_response.response_buffer = res_bf;                                                                 // defining which buffer contains the response
        http_response.response_length = 0;
        // setting defaults 
        str_cpy(http_response.status_code , "200 OK");
        str_cpy(http_response.protocol , "HTTP/1.1");
}

void response_send_file( char* filename ){
        // load the file to send
        char file[BF_SIZE];
        file_load(file , filename);
        // set content in struct
        http_response.content_length = str_len(file);
        http_response.content = file;
        // creating http response
        http_response.response_length = snprintf(http_response.response_buffer , BF_SIZE , "%s %s%s\nContent-Length: %u\n\n%s", http_response.protocol, http_response.status_code, http_response.headers , http_response.content_length, http_response.content );
}