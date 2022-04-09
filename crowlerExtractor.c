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

void http_get(char *url, struct memory_struct *mem){
    CURL *curl_handle;
    CURLcode res;
    
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
        fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                curl_easy_strerror(res));
    }
 
    // cleanup
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
}




// @ MAIN FUNCTIONS
// main()

int main(int argc, char** args){
    char * path = "/home/name/Desktop/crowler/RELACY/DATA/domains.txt";
    printf("%s",path);


    int size = 1024*256;
    char buffer[size];

    readFile(buffer,size,path);

   // printf("%s",buffer);

    int count = strLen(buffer);
    int indexes[1024*4];
    int nLines = countLines(buffer,indexes);
    printf("%d\n",nLines);
    printf("%s","222222222222222222");
    
    // taking random 10 domains to call
    int num = count/nLines * 2;
    //about every 700 lines

   // printf("%d\n",nLines);



    int result [count/num][256];


// aboaut 7 lines
    //printf("%d",indexes[0] / num);


    const int calc_reasonable_amount = indexes[0]/num;

    char domains[calc_reasonable_amount][255];
    int charCounter = 0;
    int ct = 0;

    printf("%s","222222222222222222");


    // for (int i = 1; i < indexes[0]; i+= calc_reasonable_amount){

    //     while(buffer[indexes[i]+charCounter] != '\n'){
    //        domains[ct][charCounter] = buffer[indexes[i]+charCounter];
    //        charCounter++;
    //     }
    //     domains[ct][charCounter+1]='\0';
    //     ct ++;
    //     charCounter = 0;
    //     /* code */
    // }

    printf("%s","333333333");

    
// WITH AROUND 7 - 10 DOMAINS MAKE FILES

    struct memory_struct m;

    char resultBuffer[1024*1024];
    int length1 =0;
    int length2 =0;

     for (int i = 0; i < calc_reasonable_amount; i++){


         length1 = strLen(m.buffer);
         length2 = strLen(resultBuffer);
            printf("%s","making call ....");
          http_get(domains[i], &m);

         strConcat(resultBuffer, resultBuffer,length1,m.buffer,length2);

        // printf("%s",m.buffer);
     }
        
        
        printf("%s",resultBuffer);






    char url[255];
    printPorcamadonna();


    //m.buffer
    //fileWrite(m.buffer,"/home/name/Desktop/crowler/RELACY/DATA/test.html");

    return 0;
}