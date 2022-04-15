#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>
#include<string.h>
#include"utils.h"

char *url = NULL;
// struct for hoding http response.
struct memory_struct{
    char   *buffer;
    size_t size;
};

// write response data to the memory buffer.
static size_t
mem_write(void *contents, size_t size, size_t nmemb, void *userp){
    // initialize memory_struct
    size_t realsize = size * nmemb;
    struct memory_struct *mem = (struct memory_struct *)userp;
    
    char *ptr = realloc(mem->buffer, mem->size + realsize + 1);
    if(ptr == NULL) {
        /* out of memory! */
        printf("%s","not enough memory (realloc returned NULL)\n");
        return 0;
    }

    // copy the response contents to memory_struct buffer.
    mem->buffer = ptr;
    memcpy(&(mem->buffer[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->buffer[mem->size] = 0;

    // return the size of content that is copied.
    return realsize;
}

int http_get(char *url, struct memory_struct *mem){
    CURL *curl_handle;
    CURLcode res;

    int num = 0;
    
    mem->buffer = malloc(1);
    mem->size   = 0;
    
    curl_global_init(CURL_GLOBAL_ALL);

    // initialize curl
    curl_handle = curl_easy_init();

    // specify url, callback function to receive response, buffer to hod
    // response and lastly user agent for http request.
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, mem_write);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)mem);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "custom-agent");
 
    // make the http request.
    res = curl_easy_perform(curl_handle);
 
    // check for errors.
    if(res != CURLE_OK){
        num = 1;
        fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                curl_easy_strerror(res));
                
    }
    // cleanup
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
    return num;
}
// @ MAIN FUNCTION
// main()

//  GET FROM LINKS, SOME LINKS, MAKES HTTP CALL, AND PUTS ALL HTML PAGES IN WORDSDUMP.TXT
int main(int argc, char** args){
    char * path = "/home/name/Desktop/crowler/RELACY/DATA/domains.txt";
    // printf("%s",path);
    int size = 1024*256;
    char buffer[size];
    readFile(buffer,size,path);
//    printf("%s","################");
//    printf("%s",buffer);
//    printf("%s","###########");
    int count = strLen(buffer);
    int indexes[1024*4];
    int nLines = countLines(buffer,indexes);
    int result [10][256];
    const int calc_reasonable_amount = nLines/10;
    char domains[10][256];
    int charCounter = 0;
    int ct = 0;

    for (int i = 1; i < nLines; i+= calc_reasonable_amount){
        while(buffer[indexes[i]+charCounter] != '\n'){
           domains[ct][charCounter] = buffer[indexes[i]+charCounter];
        //    printf("%c",domains[ct][charCounter]);
           charCounter++;
        }
        domains[ct][charCounter+1]='\n';
        ct ++;
        charCounter = 0;
        // printf("%c",'\n');
    }
    struct memory_struct m;
    char resultBuffer[1024*256];
    path = "/home/name/Desktop/crowler/RELACY/DATA/wordsdump.txt";
    FILE *fp;
    fp = fopen(path, "w");
    if(fp == NULL) {
        // printf("file couldn't be opened\n");
        exit(1);
    }
    for (int i = 0; i < calc_reasonable_amount -1; i++){
        if(!http_get(domains[i], &m)){
          // printf("%s",m.buffer);
          fputs(m.buffer,fp);
        };
    }

        fputs("@@@",fp);
        fclose(fp);
        // printf("%s",resultBuffer);
    return 0;
}