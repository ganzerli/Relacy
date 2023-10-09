unsigned int create_response(char* res_buffer){
    char* response_headers ="HTTP/1.0 200 OK\nServer: E-pacy1.0 Jerryfish\nDate: Mon, 30 Feb 1970 00:11:10 GMT\nContent-type: text/html; charset=UTF-8\nContent-Length: 417\r\n\r\n";
    str_cpy(res_buffer , response_headers);
    char html[512];
    file_load(html , "views/html.html");
    str_cat( res_buffer, response_headers , html );
    return str_len(res_buffer);
}