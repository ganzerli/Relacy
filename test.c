#include<stdio.h>
#include "utils.h"

int main(){

int size = 1024 * 1024 * 3; /* 5 MB*/
char buf1[size];
char buf2[size];
const char* path = "/home/name/Desktop/crowler/RELACY/DATA/wordsdump.txt";

// read file in buf1;

printf("\n %s \n", "a###########################################################");
printf("%s \n", "a###########################################################");
printf("%s \n", "a###########################################################");


int fileSize = readFile(buf1,size,path);
ignoreHtml(buf1,buf2,fileSize);
replaceChar(buf2,'\n',' ');

//fileWrite(buf2,path);
//printf("%s", buf2);

printf("\n %s \n", "a###########################################################");
printf("%s \n", "a###########################################################");
printf("%s \n", "a###########################################################");









}