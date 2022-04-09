#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>
#include<string.h>
#include"utils.h"

char *url = NULL;


// having a string, define begin char and other char, an index of second [...+second] to mind the word "h"ell"o"
// char to finish the string "\n" "\0"
// returns the searched stringS pattern: hello .......... "\§" --> separed by "\n"

char* findStrings(char* string , char* buffer, char firstChar, char lastCharFirstWord, signed int lCFWRelIndex, char endChar ){
    
    signed int counter = 0;
    char tempchar = ' ';
    signed int end = strLen(string);

    for (signed int i = 0; i < end ; i++){
       if(string[i] == firstChar && string[i+lCFWRelIndex] == lastCharFirstWord ){
            // print suppose string
            signed int j = 0;
            // '\"'
            while(string[i+j] != endChar){
                tempchar = string[i+j];
 //               printf("%c",tempchar);
                buffer[counter] = tempchar;
                j++;
                counter++;
            }
            // printf("%c",'\n');
            // printf("%d",i);
            // printf("%s","  of  ");
            // printf("%d\n",end);



            // set i at the end of the link '\n'
            i = i + j-1;
            buffer[counter]='\n';

            // reset j
            j=0;

            counter++;
        }
    }

    return buffer;
}



// END UTIL

// struct for 2 strings same size
struct str_buf_struct{
    char* buffer;
    char* buffer2;
    char* buffer3;
    char* str;
    int size;
};

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

int scanLinks(char* content, char* str1){
    int counter = 0;

    char tempchar = ' ';
    int end = strLen(content);
    for (int i = 0; i < end ; i++){
        if(content[i] == 'h' && content[i+4] == '=' ){
            // print suppose string
            int j = 6;
            while(content[i+j] != '\"'){
                tempchar = content[i+j];
                //printf("%c",content[i+j]);
                str1[counter] = tempchar;
                j++;
                counter++;
            }
        i = i + j-1;
        
        str1[counter]='\n';
        counter++;

        }
    }
    
    str1[counter]='\0';
    str1[counter+1]='\0';

    fileWrite(str1,"/home/name/Desktop/crowler/RELACY/DATA/domains.txt");

    printf("%s","Links scanned...\n");

    return 0;
}

//@ RESTORE LINKS
//  make links complete from the file and rewrite the file

char* formatLinks(char* str, char* result){

    signed int end = strLen(str);
    signed int counter = 0;
    // printf("%s\n","1111111111");
    // printf("%d\n",end);
    // printf("%s\n","1111111111");
    int overflow = 0;
    // INIT
    result[counter]= 'h';
    //       printf("%c",result[counter]);
    result[counter+1]= 't';
    //       printf("%c",result[counter+1]);
    result[counter+2]= 't';
    //       printf("%c",result[counter+2]);
    result[counter+3]= 'p';
    //       printf("%c",result[counter+3]);
    result[counter+4]= 's';
    //       printf("%c",result[counter+4]);
    result[counter+5]= ':';
    //       printf("%c",result[counter+5]);
    // overflow += 6;
    // for the whole file
    while(counter < end ){
        result[counter+overflow]= 'h';
                // printf("%c",result[counter+overflow]);
        result[counter+overflow+1]= 't';
                // printf("%c",result[counter+overflow+1]);
        result[counter+overflow+2]= 't';
                // printf("%c",result[counter+overflow+2]);
        result[counter+overflow+3]= 'p';
                // printf("%c",result[counter+overflow+3]);
        result[counter+overflow+4]= 's';
                // printf("%c",result[counter+overflow+4]);
        result[counter+overflow+5]= ':';
                // printf("%c",result[counter+overflow+5]);
        overflow += 6;
        
        //printf("%d",counter);
        while(str[counter] != '\n'){
            result[counter + overflow] = str[counter];    
            // printf("%c",result[counter + overflow]);
            counter++;
        }
        result[counter+overflow] = '\n';
                // printf("%s","   ");
               // printf("%d",counter);
                // printf("%c",'\n');
                // printf("%c",'\n');
                // printf("%c",'\n');
    counter++;
    } ;

    result[counter+overflow+1] = '\0';

    return result;
}


// @ MAIN FUNCTIONS
// main()

int main(int argc, char** args){

    char url[255];
    printf("%s","insert domain to visit: https://en.wikipedia.org/wiki/Amsterdam\n");
    scanf("%s", url);
    printf("trying to make http request to: %s\n", url);
    struct memory_struct m;
    http_get(url, &m);
    fileWrite(m.buffer,"/home/name/Desktop/crowler/RELACY/DATA/test.html");
    // filling struct
    struct str_buf_struct s_b;
    s_b.size = 1024 * 256;
    char* string = malloc(s_b.size);
    s_b.str = string;
    char* buffer = malloc(s_b.size);
    s_b.buffer = buffer;
    char buffer2[s_b.size];
    scanLinks(m.buffer, s_b.str);
    char* domain = "https://en.wikipedia.org";
    // restore links
    char* twoSlashes = findStrings( s_b.str, buffer, '/','/', 1, '\n');
    signed int end = strLen(twoSlashes);
    char* result;
    result = malloc(end * 2);
    char* formattedLinks = formatLinks(twoSlashes, result);
    char* https = findStrings( s_b.str, buffer2, 'h',':', 5, '\n');
    int sizeFormLinks = strLen(formattedLinks);
    int sizeHttps = strLen(https);
    char *buffer3 = malloc(s_b.size);
    char *fileTemplate = strConcat(buffer3,formattedLinks,sizeFormLinks,https,sizeHttps);
    printf("%s",fileTemplate);
    fileWrite(fileTemplate,"/home/name/Desktop/crowler/RELACY/DATA/domains.txt");
    free(buffer);
    free(string);
    return 0;
}