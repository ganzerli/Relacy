#define WORDSDUMP   "wordsdump.txt"
#define INDEXYX     "indexyx"


void relacy_check(){
    FILE *fp;

    fp=fopen(INDEXYX,"ab");                                            
    fclose(fp);
    printf("file for indexes ready\n");

    fp= fopen(WORDSDUMP, "a");
    fclose(fp);
    printf("text file for wordks ready\n");
}

unsigned int file_load(char *buffer , char* filename){
    FILE * fp = fopen(filename,"r");    
    if(fp == NULL) printf("\nERROR OPENING FILE %s\n", filename);
    char c = fgetc(fp);
    unsigned int count = 0;
    while ( c != EOF){
        buffer[count++] = c;
        c = fgetc(fp);
    }
    buffer[count] = '\0';
    fclose(fp);
    return count;
}