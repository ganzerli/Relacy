#include<stdio.h>
#include<stdlib.h>
#include "utils.h"

#define MAX_SIZE 20
#define MIN_SIZE 4


int main(){

int size = 1024 * 1024 * 3; /* 5 MB*/
char* buf1 = malloc(size);
char* path = "/home/name/Desktop/crowler/RELACY/DATA/wordsdump.txt\0";

int fileSize = readFile(buf1,size,path);
printf("%s %d\n", "FILE READ, size: ",fileSize);

// fitting buffer for ignore html
char* buf2 = malloc(fileSize);
char* nojs = malloc(fileSize);

// save all but NOT <script> ... </script>
ignoreJs(buf1,nojs,fileSize);

// buf 1 is container of raw html, in buf2 words without html
free(buf1);

// cut all html tags and free buffer
ignoreHtml(nojs,buf2,fileSize);
free(nojs);

// replace new lines with spaces
replaceChar(buf2,'\n',' ');

//  PUT ALL WORDS IN FROM FILE-BUFFER IN STRUCTS, TO COLLECT INFO ABOUT SIGLE WORDS
// _wrdArr[].word[MAX_SIZE] has MAX_SIZE chars per word
int sz= fileSize/MAX_SIZE;

// save info in structs
struct words *_wrdArr = malloc(sz * sizeof *_wrdArr);
int words_num = trimUnwantedStrLength(buf2, _wrdArr,fileSize, MIN_SIZE, MAX_SIZE);

// free last buffer, all is in structs array..
free(buf2);

// words in structs are saved also with unwanted chars, not counted jet
// setflag in struct if word is found and how many times..
words_num = count_reduce(_wrdArr,words_num,MAX_SIZE);

printf("\n\n%d\n", words_num);

// ready to write in file

for (int i = 0; i < words_num; i++){

      printf("%d %s %s %s %d %s %d \n", _wrdArr[i].count, "): ", _wrdArr[i].word ," n-found  " , _wrdArr[i].timesFound , " size ",_wrdArr[i].size );

    }











printf("\n %s \n", "a###########################################################");
printf("%s \n", "a###########################################################");
printf("%s \n", "a###########################################################");









}