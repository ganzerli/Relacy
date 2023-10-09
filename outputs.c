// output to use in all possible cases

#define OUT_SIZE 512

// returns always the same string, so development, debug, and for instance sending prompts or responses to client will be always exactly the same to read 
char* gnu_Output(unsigned int which , char* buffer){

    
    char output[][512]={
        "<h1> hello </h1>",
    };

    char* line = output[which];
    unsigned int i = 0;

    while (line[i] != '\0'){
        buffer[i] = line[i];
        i++;   
    }
    buffer[i] = '\0';
    return buffer;
}

// printing the carefully selected output
void o_ut(char* o ){
    printf("%s", o);
}