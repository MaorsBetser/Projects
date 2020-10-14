#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main (int argc, string argv[])
{
    if(argc == 2)
    {
        int key = atoi(argv[1]);
        if(key > 26)
        {
            key = key % 26;
        }

        string msg = get_string("Enter Text to be cihpered \n");
        int n = strlen(msg);
        for(int i = 0; i < n; i++)
        {
            if(isalpha(msg[i]))
            {

                int encryptedCharAscii = msg[i] + key;
                char text = encryptedCharAscii;

                if(msg[i] >= 65 && msg[i] <= 90) // upper case case
                {
                    if(encryptedCharAscii > 90)
                    {
                        text = encryptedCharAscii - 26;
                    }
                }
                else
                {
                    if(encryptedCharAscii > 122)
                    {
                        text = encryptedCharAscii - 26;
                    }
                }
                printf("%c", text);
            }
            else
            {
                printf("%c", msg[i] + key);
            }

        }
        printf("\n");
        printf("%s \n", msg);

    }
    else
    {
        printf("Usage: ./ceaser key \n");
    }



}
