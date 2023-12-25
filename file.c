#define WORDSDUMP   "wordsdump.txt"
#define INDEXYX     "indexyx"

void relacy_check(){
    FILE *fp;

    fp=fopen(INDEXYX,"ab");          
    fseek(fp, 0, SEEK_END);                                                 // moving pointer to end file
    u32 bytes_count = ftell(fp);                                                   
    fclose(fp);
    u32 *np;
    // if nothing in file init with parallelized format
    if(bytes_count  == 0){                                                  
        fp=fopen(INDEXYX,"ab");   
        // write COUNT as 1 = only 1 word in file
        *np = 1;
        fwrite(np, sizeof (u32), 1, fp);
        // write first index as 0 , word "relacy" begins at index 0 of wordsdump
        *np = 0;
        fwrite(np, sizeof (u32), 1, fp);
        // next word expected at index 6 -> 0 to 6 is word relacy
        *np = 6;
        fwrite(np, sizeof (u32), 1, fp);

        fclose(fp);
        printf("file for indexes ready\n");

        // create a file
        fp = fopen(WORDSDUMP , "w");
        // init with word relacy
        fprintf(fp, "relacy");
        fclose(fp);

        printf("text file for wordks ready\n");
    }                                  
}

unsigned int file_load(char *buffer , char* filename){
    FILE * fp = fopen(filename,"r");    
    if(fp == NULL) printf("\nERROR OPENING FILE %s\n", filename);
    char c = fgetc(fp);
    unsigned int count = 0;
    while ( c != EOF){

        ///////////  BUG 
        buffer[count] = c;
        c = fgetc(fp);        
        printf("%c" , c);

        count++;
    }
    buffer[count] = '\0';
    fclose(fp);
    return count;
}

void file_write(char *filename , char* text){
    // creating file pointer to work with files
    FILE *fptr = fopen(filename, "w"); 
    // exiting program 
    if (fptr == NULL) printf("Error opening %s" , filename);
    fprintf(fptr, "%s", text);
    fclose(fptr);
}

void file_write_bin(char*filename , unsigned int size, void* buffer ){
    FILE *fp = fopen(filename, "wb");
    fwrite(buffer, size, 1, fp);
    fclose(fp);
}


unsigned int get_pic(int8_t *buffer , char*filename){

    FILE *pic ;
    int i;
    pic = fopen(filename, "rb"); 

    if( pic == NULL ) { printf("Error opening File\n");} 

    fseek(pic, 0, SEEK_END);
    int length = ftell(pic);
    fseek(pic, 0, SEEK_SET);

    for(i = 0; i < length; i++){
        buffer[i] = fgetc(pic);
    }

    fclose(pic); 
    return length;

}