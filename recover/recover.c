#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    const int BLOCK_SIZE = 512;
    //Ensure only one argument and proper usage
    if (argc != 2)
    {
        printf("Usage ./recover.c [RAW_FILE]\n");
        return 1;
    }


    //Open the file
    FILE *data = fopen(argv[1], "r");
    if (data == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    //Declare the variable to store the jpeg bytes
    BYTE *buffer = malloc(BLOCK_SIZE);

    //variable to count the number of files
    int k = 0;
    char *outname = malloc(sizeof("%03d.jpg"));
    int fnum = 0;
    sprintf(outname, "%03d.jpg", fnum);
    FILE *jpeg = fopen(outname, "w");
    //printf("%03d\n", 10);
    bool first = true;
    bool found = false;
    while (fread(buffer, 1, BLOCK_SIZE, data) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            k++;
            found = true;
            if (jpeg != NULL)
            {
                fclose(jpeg);
                sprintf(outname, "%03d.jpg", fnum++);
                jpeg = fopen(outname, "w");
            }
        }
        if (found)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpeg);
        }
    }
    //printf("%i\n", k);
    fclose(jpeg);
    fclose(data);
    free(outname);
    free(buffer);
}
