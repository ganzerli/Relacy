// output to use in all possible cases

#define OUT_SIZE 512

// returns always the same string, so development, debug, and for instance sending prompts or responses to client will be always exactly the same to read 
char* gnu_Output(unsigned int which , char* buffer){

    
    char output[][512]={
        "INSERT a WORD in something SIMILAR to plain english, encoding ASCII 1.0\nACCEPTED are also  !#$%&()*+-.:,;<=>?@[]^_~/ \n",
        "Selected word",
        "third output",
        "forth",
        "diminished five",
        "6",
        "7",
        "8",
        "9",
        "A",
        "B",
        "C",
        "D",
        "E"
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