#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define blocksize 512

int main(int argc, char *argv[])
{
    if (argc != 2) // checking if the file name is entered or not
    {
        printf("mention the file name or too many commands\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "r"); // opening the file asked for
    FILE *out = NULL; // creating a null output file
    if (in == NULL)
    {
        printf("could not open the file %s", argv[1]); // checking if input file opens or not
        return 1;
    }

    uint8_t buffer[blocksize]; // making a buffer pointer

    int count = 0; // jpg counter
    char *filename = malloc(9 * sizeof(char)); // creating fine as all file different name

    while (fread(buffer, sizeof(uint8_t), 512, in) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0)) // checking for headers
        {
            if (out != NULL) // if file is not null and header is found close the existing file
            {
                fclose(out);
            }
            sprintf(filename, "%03i.jpg", count); //  creating file name
            out = fopen(filename, "w"); // opening output file
            count++;
        }
        if (count > 0 && out != NULL) // if file is found write
        {
            fwrite(buffer, sizeof(buffer), 1, out);
        }

    }

    free(filename);// free malloc
    fclose(out); // close out
    fclose(in); // close in

    return 0;
}