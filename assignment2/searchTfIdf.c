#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "c99.h"


typedef struct Node *urlN;

// Node containing a url
struct Node {
    char *url;
    double tfidf;
    int num;
    urlN next;
} Node;

urlN newURLNode(char *url, double tfidf);
urlN updateURLList(urlN listHead, char *searchTerm, int nDocs);
int sTermURLs(char *searchTerm, char *urlArray[BUFSIZ]);
urlN URLInList(urlN list, char *u);
urlN insertURL(urlN listHead, urlN url);
urlN sortList(urlN listHead, urlN url);
urlN deleteURL(urlN listHead, urlN url);
int Ntexts();
double termFrequency(char *term, char *url);
double inverseDocumentFrequency(double containingDocs, double nDocs);
void lowercase(char *word);
char *removePunctuation(char *string);
void showURLList(urlN listHead);
void freeURLList(urlN listHead);


// argc-->number of command in commandline         argv-->link to the content of each command 

int main(int argc, char *argv[]){       // Make a sorted list of urls based on number of matching search terms and tfidf
    urlN newNode = NULL;                //make a new node in list
    int nTexts = Ntexts();              //the number of how many arguments
       
    int i = 1;
    while(i < argc){                    // For each URL, add to and update URLList
        newNode = updateURLList(newNode, argv[i], nTexts);
        i++;
    }
    
    showURLList(newNode);               //printf
    
    freeURLList(newNode);               //free
}


//fscanf return the number of arguments
int Ntexts() {     // Get the number of documents in collection.txt
    FILE *get = fopen("collection.txt", "r");   //open the file and read it
    
    int nTexts = 0;                             //count the number of arguments
    char temp[BUFSIZ];                          //to save the text
    
    while (fscanf(get, " %s", temp) == 1) {     //if we can read the file up to now we will write them into "temp" and count = count + 1
        nTexts++;
    }
    fclose(get);                                //close the file

    return nTexts;
}


// urlN listHead--> the first node in the list       searchTerm-->
// nDocs-->

urlN updateURLList(urlN listHead, char *searchTerm, int nDocs){   // Add and update URLList by urls containing the search term
    // Collect list of URLs containing the search term
    char *URLArray[BUFSIZ];
    int nURLs = sTermURLs(searchTerm, URLArray);
    
    if (nURLs == 0){                                              //
       return listHead;
    }
    
    double tfidf, idf = inverseDocumentFrequency(nURLs, nDocs);

    urlN url = NULL;
    int i = 0;
    
    // Insert the first url into the list
    if (listHead == NULL) {
        tfidf = termFrequency(searchTerm, URLArray[i]) * idf;
        url = newURLNode(URLArray[i], tfidf);
        listHead = url;
        i++;
    }
    
    // Make changes to the URLList according to the URLs containing the search term
    while(i < nURLs){
        tfidf = termFrequency(searchTerm, URLArray[i]) * idf;
        if((url = URLInList(listHead, URLArray[i])) != NULL){ // Updates existing node position
            url->num++;
            url->tfidf += tfidf;
            listHead = sortList(listHead, url); // Reposition url based on num and tfidf
        }else{    // Adds new URL to list
            url = newURLNode(URLArray[i], tfidf);
            listHead = insertURL(listHead, url); // Position url based on num and tfidf
        }
        i++;
    }

    return listHead;
}


int sTermURLs(char *searchTerm, char *urlArray[BUFSIZ]) {      // Returns array of URLs matching terms
    char file[BUFSIZ];
    char *shouldfind;
    char *term;
    int found = 0;                                             //judge found or not
    FILE *ivIndx = fopen("invertedIndex.txt", "r");            //open the file and read it
    
    while (fgets(file, BUFSIZ, ivIndx) != NULL){               // read through all of the file save in file and find terms
        shouldfind = strdup(file);              // duplicate the content of file
        term = strsep(&shouldfind, " ");        // to separate and save in term
        if (strcmp(term, searchTerm) == 0) {    // check if this is the line what we should to find.
            strsep(&shouldfind, " ");           // Skip the second space                  ???
            found = 1;                          // found
            break;
        }
    }
    
    if (found == 0){                            // if search term doesn't exist
        return 0;
    }
        
    char *urlseg = strsep(&shouldfind, " ");  // separate and save what we should to find
    int i;
    for(i = 0;shouldfind != '\0';i++){          // go through 'shouldfind'
        urlArray[i] = malloc(strlen(urlseg) + 1); //allocate space for what we should find  
        strcpy(urlArray[i], urlseg);            //copy urlseg to urlArray
        urlseg = strsep(&shouldfind, " ");      //separate and save what we should to find
    }
 
    if (urlseg != NULL) {                       
        urlseg = strsep(&urlToken, "\n");       // Strip the trailing newline
        urlArray[i] = malloc(strlen(urlseg) + 1);
        strcpy(urlArray[i], urlseg);
        i++;
    }
    
    fclose(ivIndx);
    return i;
}

urlN newURLNode(char *url, double tfidf) {      // Make a new URL node
    urlN new = malloc(sizeof(Node));
    assert(new != NULL);
    new->url = strdup(url);
    new->tfidf = tfidf;
    new->num = 1;
    new->next = NULL;
    return new;
}



// Returns node if url is in list
urlN URLInList(urlN list, char *u){
    urlN curr = list;
    while(curr != NULL){
        if(strcmp(curr->url, u) == 0){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// Insert a URL into the URLList
urlN insertURL(urlN listHead, urlN url) {
    urlN curr = listHead, prev = NULL;
    
    // url is new listHead
    if (listHead == NULL || url->num > listHead->num ||
        (url->num == listHead->num && url->tfidf > listHead->tfidf)) {
        url->next = listHead;
        return url;
    }
    
    // Get to the nodes with the same num as url
    while (curr != NULL && curr->num > url->num) {
        prev = curr;
        curr = curr->next;
    }
    // Get to the right tfidf position
    while (curr != NULL && curr->num == url->num && curr->tfidf > url->tfidf) {
        prev = curr;
        curr = curr->next;
    }
    
    // Insert the url
    if (curr == NULL) { // Append
        prev->next = url;
    }else{ // Put url before curr
        prev->next = url;
        url->next = curr;
    }
    
    return listHead;
}

// Deletes old url and inserts new url into correct position
urlN sortList(urlN listHead, urlN url) {
    listHead = deleteURL(listHead, url);
    listHead = insertURL(listHead, url);

    return listHead;
}

// Delete a url from the URLList
urlN deleteURL(urlN listHead, urlN url){
    if (listHead == url) {
        return url->next;
    }
    else {
        urlN curr = listHead;
        while (curr->next != url) {
            curr = curr->next;
        }  
        curr->next = url->next;
    }
    return listHead;
}


// Calculate the term frequency of a term within a page, proportionate to the number of words
double termFrequency(char *term, char *url) {
    // Open the url file
    char *fileName = strdup(url);
    fileName = realloc(fileName, strlen(url) + strlen(".txt") + 1);
    strcat(fileName, ".txt");  
    FILE *page = fopen(fileName, "r");

    double count = 0.0, words, termFreq;
    fscanf(page, "%*[^\n]%*[^#]#%*[^#]#%*[^\n]\n"); // Skip to section 2 

    char word[BUFSIZ];
    fscanf(page, " %s", word);
        
    // Loop through words to find term frequency
    for (words = 0.0; strcmp(word, "#end") != 0; words++) {
        // Normalise the word
        lowercase(word);
        strcpy(word,removePunctuation(word));
        
        if (strcmp(term,word) == 0)
            count++;
        fscanf(page, " %s", word);
    }
    
    termFreq = count/words;
    return termFreq;
}

// Calculate inverse document frequency
double inverseDocumentFrequency(double containingDocs, double nDocs) {
    double quotient = nDocs/containingDocs;
    double inverseDocFreq = log10(quotient);
    return inverseDocFreq;
}



// From https://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
// Make a word lowercase
void lowercase(char *word) {
    for ( ; *word; ++word) *word = tolower(*word);
}

// Remove trailing punctuation
char *removePunctuation(char *string) { //FIXME is there a better way? edit string directly
    char *str = strdup(string);
    if (string[strlen(string)-1] == '.' || string[strlen(string)-1] == ',' || string[strlen(string)-1] == ';' || string[strlen(string)-1] == '?') {
        str[strlen(str)-1] = '\0';
    } 
    return str;  
}

void showURLList(urlN listHead) {
    urlN curr = listHead;
    int i = 0;
    while(curr != NULL && i < 30) {
        printf("%s  %.6f\n", curr->url, curr->tfidf);
        curr = curr->next;
        i++;
    }
}

// clean up the urllist
void freeURLList(urlN listHead) {
    urlN curr = listHead, next;
    while (curr != NULL) {
        free(curr->url);
        next = curr->next;
        free(curr);
        curr = next;
    }
}


