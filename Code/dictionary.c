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

/* CR - IMPORTANT GENERAL NOTE
 *   You shouldn't use strlen, strcpy etc as a GENERAL RULE. That's because they don't have length limit.
 *   Meaning if you give them a huge string, they'll just cause buffer overflow and all sorts of problems.
 *   You have equivalents with length limits - strnlen, strncpy. These are THE SAME, except you also give them a limit.
 *   In this case, your limit is LENGTH + 1.
 */

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // CR - It's good practice to initialize to 0! "char checkWordBuff[LENGTH + 1] = {0};"
    char checkWordBuff[LENGTH + 1];
    // CR - Why are you strlen-ing the buffer? don't you want to do it for the word parameter?
    int wordLen = strlen(checkWordBuff);

    strcpy(checkWordBuff, word);
    for(int i = 0; i < wordLen ; i++){
        checkWordBuff[i] = tolower(checkWordBuff[i]);
     }
    
    // CR - Variable initialization should happen in the start of the function, with for-loop variables as the ONLY exception.
    //   So you should do "unsigned int index = 0;" in the beginning, then later "index = hash(checkWordBuff);"
    unsigned int index = hash(checkWordBuff);
    // CR - This is great, just move to the top of the function!
    struct node * cursor = NULL;

    cursor = table[index];

    // CR - You're checking for NULL in the while-loop condition. Do you need to do it here too?
    if(table[index] == NULL) {
        
        return false;
    }
    
    while(cursor != NULL)
    {
        // CR - Do you really need to use cmpresult? how about "if(strcasecmp(word, cursor->word) == 0)"?
        int cmpresult = strcasecmp(word, cursor -> word);
        if(cmpresult == 0)
        {
            
            return true;
            // CR - Do you need to break if you return in the previous line?
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
    // CR - Does p change? If not, maybe it should be a constant instead of a variable.
	int p = 31;
    // CR - You already have 676 defined right? You can use that instead of another variable.
	int m = 676;
    // CR - Why is powerP a long long? Seems like it's never bigger than m, right? What type can hold up to 676?
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
    // CR - It's good practice to check parameters if their not null, otherwise you might crash.
    //   You should probably check if dictionary is not NULL before using it.
    FILE *dictp = fopen(dictionary, "r");
    if(dictp == NULL){
        printf("could not open file");
        return false;
    }
    
    //reseting the hashtable
    // CR - Since NULL is just 0, you can just use memset - "memset(table, 0, sizeof(table));"
    for(int i = 0; i < N; i++){
        table[i] = NULL;
    }

    // CR - This definition should go to the top of the function, and be initialized to 0's! "char wordBuff[LENGTH + 1] = {0};"
    char wordBuff[LENGTH + 1];

    // CR - You should be careful of fscanf! It's kind of scary that they still teach it. It can be used for exploitations!
    //   Anyway, are you sure you need the space after %s in the format string?
    while(fscanf(dictp, "%s \n", wordBuff) != EOF)
    {
        // CR - variable initialization to the top! (do it for the rest of the variables in the function)
        node *newWord = malloc(sizeof(node));
        if(newWord == NULL){
            printf("could not allocate memory\n");
            // CR - Doesn't the function return true or false?
            return 2;
        }

        // CR - strncpy instead!
        strcpy(newWord -> word, wordBuff);
        
        //makes the word to lower for the hash func
        // CR - use strnlen instead!
        //   Also, you wrote this for-loop with tolower twice - might want to put it in a separate function instead!
        for(int i = 0; i < strlen(wordBuff); i++){
            wordBuff[i] = tolower(wordBuff[i]);
        }
        unsigned int index = hash(wordBuff);
        
        // CR - This comment is very good, but it only applies to the if and not the else. You should put it after the if!
        // Inserts new nodes at beginning of lists
        // CR - You need to check if index is bigger than the table limit! Otherwise you might cause buffer overflow.
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
    // CR - Do you need tableSize? Why not just use N?
    int tableSize = N; //table size declared
    for(int i = 0; i < tableSize; i++){
        // CR - To the top! Each variable should be declared in a separate line.
        struct node *cursor, *tmp = NULL;
        
        /* CR - This can look nicer if you use "current" and "next" instead of "cursor" and "tmp"
         * Also, notice what happens if there's only 1 node - will it be freed?
         * Consider this:
            current = table[i];
            while(current != NULL)
            {
                next = current->next;
                free(current);
                current = next;
            }
         */
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