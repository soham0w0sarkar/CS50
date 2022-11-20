// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t H[HEADER_SIZE]; //array of size 44
    fread(H, HEADER_SIZE, 1, input);
    fwrite(H, HEADER_SIZE, 1, output);

    int16_t b; //creating a buffer
    while (fread(&b, sizeof(int16_t), 1, input))
    {
        b *= factor; //multiplyinf buffer with factor
        fwrite(&b, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
