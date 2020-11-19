// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <unistd.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
int dictSize = 0;

// Number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    char checkWordBuff[LENGTH + 1];
    int wordLen = strlen(checkWordBuff);

    strcpy(checkWordBuff, word);
    for(int i = 0; i < wordLen ; i++){
        checkWordBuff[i] = tolower(checkWordBuff[i]);
     }
    
    unsigned int index = hash(checkWordBuff);
    struct node * cursor = NULL;

    cursor = table[index];

    
    if(table[index] == NULL) {
        
        return false;
    }
    

    while(cursor != NULL)
    {
        
        int cmpresult = strcasecmp(word, cursor -> word);
        if(cmpresult == 0)
        {
            
            return true;
            break;
        }
        
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char * word)
{
    
    // P and M
	int p = 31;
	int m = 676;
	long long powerP = 1;
	unsigned int hashVal = 0;

	// Loop to calculate the hash value
	// by iterating over the elements of string
	for (int i = 0; i < strlen(word); i++) {
		hashVal = (hashVal + (word[i] - 'a' + 1) * powerP) % m;
		powerP = (powerP * p) % m;
	}
    

    if(hashVal > N){
        hashVal = hashVal % m;
    }
    
	return hashVal;
}
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dictp = fopen(dictionary, "r");
    if(dictp == NULL){
        printf("could not open file");
        return false;
    }
    
    //reseting the hashtable
    for(int i = 0; i < N; i++){
        table[i] = NULL;
    }

    char wordBuff[LENGTH + 1];

    while(fscanf(dictp, "%s \n", wordBuff) != EOF)
    {
        
        node *newWord = malloc(sizeof(node));
        if(newWord == NULL){
            printf("could not allocate memory\n");
            return 2;
        }

        strcpy(newWord -> word, wordBuff);
        
        //makes the word to lower for the hash func
        for(int i = 0; i < strlen(wordBuff); i++){
            wordBuff[i] = tolower(wordBuff[i]);
        }
        unsigned int index = hash(wordBuff);
        

        // Inserts new nodes at beginning of lists
        if (table[index] == NULL)
        {
            table[index] = newWord;
            dictSize++;
        }
        else
        {
            newWord -> next = table[index];
            table[index] = newWord;
            dictSize++;
        }
        
    }

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictSize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int tableSize = N; //table size declared
    for(int i = 0; i < tableSize; i++){
        struct node *cursor, *tmp = NULL;
        cursor = table[i];
        tmp = cursor;
        while(cursor -> next != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
