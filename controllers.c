
/* // // // // // // // // // // // // // // // // // //    INFO ABOUT REQUEST

struct HTTP_request{
    char* method;
    char* URI;
    char* HTTP_version;
    unsigned int headers_count;
    char** headers;
    unsigned int attributes_count;
    char* body;
}http_request;

*/

// // // // // // // // // // // // // // // // // // // // GET CONTROLLERS

// '/favicon.ico'
void ctrl_favicon(){
    response_send_pic("E-pachy_512x512.png");
}

    // '/'
void ctrl_home(){


    unsigned int indexes[512];
    char* sentence = "hello <-abc-> hello2 , ansdn sdlkjsd slkjslkja ,lks <-a-> dklslkjdlkjsd <-b->";


    void find_in_str (char * str, char* from , char* to , unsigned int* indexes){
        
        unsigned int i = 0;

        char frs_c = from[0];
        char lst_c = to[ ( str_len(to)-1 ) ];

        char c = sentence[0];

        unsigned int check_(char* sentence, unsigned int i , char* begin  , char* end) {

            u8 bg_sz = str_len(begin);
            u8 nd_sz = str_len(end);

            unsigned int index_begin = 0;
            unsigned int index_end = 0;

            unsigned int j = 0;

            if(str_cmp( bg_sz , begin , &sentence[i] ) ){
                index_begin = i;
                j = bg_sz;

                while ( sentence[ i + j ] != '\0'){

                    if( sentence [i + j] == end[0]){
                        printf("found at %u\n" , i+j );

                        if ( str_cmp(nd_sz , end , &sentence [ i + j ] ) ){

                            index_end = i + j + nd_sz - 1;
                            return index_end;

                        }
                    }
                    j++;
                }
            } 

            printf("begin: %u ,  end %u" , index_begin , index_end);
            return 0;
        }
        unsigned int counter = 0;
        unsigned int index_end = 0;
        while (c != '\0'){
            printf("%c" , c);

            if(c == frs_c){
                // check if
                index_end = check_( sentence , i , "<-" , "->");
                if(index_end != 0){
                    indexes[counter] = i;
                    indexes[counter+1] = index_end;
                    index_end = 0;
                    counter += 2;
                }else{
                    break;
                }     

            }
            i++;
            c = sentence[i];
        }

        for(i = 0 ; i < counter; i+=2 ) printf("begin -> [%u] , end -> [%u]" , indexes[i] , indexes [i+1]);

    }
    
    
    find_in_str(sentence , "<-" , "->" , indexes);



    add_response_header("Server: E-pache 1.0");
    response_send_file("views/html.html");
}


// // // // // // // // // // // // // // // // // // // // // POST CONTROLLERS
// '/'
void ctrl2(){
        response_send_pic("E-pachy_512x512.png");
}