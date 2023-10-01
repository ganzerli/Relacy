// output to use in all possible cases

#define OUT_SIZE 512

// returns always the same string, so development, debug, and for instance sending prompts or responses to client will be always exactly the same to read 
char* gnu_Output(unsigned int which , char* buffer){

    
    char output[][512]={
        "INSERT a WORD in something SIMILAR to plain english\nACCEPTED are also ( !,#,$,%,&,(,),*,+,,,-,.,:,;,<,=,>,?,@,[,],^,_,~,and of corse / )\nThe COMMUNITY did ALL that for free, if it was for you i had to pay just to try that\nBut WOW! if you look in internet could be that you can still call the police!! ;)\nIf you are in europe consider asking instead of to buy public oppression of others,\nso the encoding possible until now for relacy_e-pathy is the UTF-8 ASCII 1.0, no genital mutilation!\n",
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