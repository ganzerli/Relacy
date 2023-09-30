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