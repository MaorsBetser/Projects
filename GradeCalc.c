#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string text = get_string("Text: ");
    int n = strlen(text);
    int ltrCnt = 0;
    int wrdCnt = 1;
    int sntCnt = 0;
    
    
    
    for(int i = 0; i < n; i++)
    {
        if(isalpha(text[i]))
        {
            ltrCnt++;
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        if(isspace(text[i]))
        {
            wrdCnt++;
        }
    }
    
    for(int i = 0; i < n; i++)
    {
       if(text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sntCnt++;
        }
    }
    
     int grade = 0.0588 * (100 * ltrCnt / wrdCnt) - 0.296 * (100 * sntCnt / wrdCnt) - 15.8;
    
    
      if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
    
    printf("Letters :%i \n Words: %i\n Sentences: %i\n ]", ltrCnt, wrdCnt, sntCnt);
}
