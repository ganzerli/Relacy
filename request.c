void manage_request(char *buffer , unsigned int size){
    buffer[size] = '\0';
    char** request = str_split( "\n" , buffer );

    const char* first_line = request[0];
    const char** headers = &request[1];

    // printing
    printf("%s", first_line);

    set_strgs_counter( get_strgs_counter()-1 );
    print_strings(headers);
}