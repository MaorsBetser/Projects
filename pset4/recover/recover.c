#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
      printf("invalid use, try: ./recover card.raw");
      return 1;
  }
    char *inFile = argv[1];
    FILE *inFilePtr = fopen(inFile, "r");

    if(inFile == NULL)
    {
        printf("could not open File");
        return 2;
    }


  BYTE buffer[512] = {0};
  int imgCnt = 0;

  char filename[10];
  FILE *outFilePtr = NULL;

  while(!feof(inFilePtr))
  {
    fread(buffer, sizeof(BYTE), BLOCK_SIZE, inFilePtr);// reads the given file

    bool JpegHeader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0; //checks for the jpeg header

    if(JpegHeader)//jpeg header is found
      {
            if(outFilePtr != NULL)
            {
              printf("Out file ptr is not null and closing it\n");
              fclose(outFilePtr);
            }
            //creates new file name
            sprintf(filename, "%03i.jpeg", imgCnt);
            outFilePtr = fopen(filename, "w");
            imgCnt++;
        }
      }
      //writes all the data that is not header
      if(outFilePtr != NULL)
      {
        fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, outFilePtr);
      }
  }
  fclose(outFilePtr);
  fclose(inFilePtr);
}