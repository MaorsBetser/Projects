#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: recover image\n");
        return 1;
    }


    char *in_file = argv[1];
    FILE *in_file_ptr = fopen(in_file, "r");
    if(in_file_ptr == NULL)
    {
        printf("cant open in file");
        return 2;
    }

    int counter = 0;
    BYTE buffer[512];

    char filename[8];
    FILE *out_file_ptr = NULL;

    while(true)
    {
        printf("------while------\n");
        size_t bytes_read = fread(buffer,sizeof(BYTE),BLOCK_SIZE,in_file_ptr);

        if ()
        {
            printf("end of file\n");
            break;
        }

        bool contains_jpeg_header = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
        printf("buffer[0] : %i buffer[1] %i buffer [2]%i buffer [3]%i\n", buffer[0], buffer[1] , buffer[2], buffer[3]);



        if(contains_jpeg_header && out_file_ptr != NULL)
        {
            printf("----------first if----------\n");
            counter++;
        }

        if(contains_jpeg_header)
        {
            printf("------------second if----------\n");
            sprintf(filename, "%03i.jpeg", counter);
            out_file_ptr = fopen(filename, "w");

        }
        if(out_file_ptr != NULL)
        {
            printf("------------third if----------\n");
            fwrite(buffer, sizeof(BYTE), bytes_read, out_file_ptr);
        }
    }

    fclose(in_file_ptr);
    fclose(out_file_ptr);
    return 0;
}