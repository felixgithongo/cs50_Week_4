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

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE]; // create a buffer

    fread (header, HEADER_SIZE, 1, input); // read the header from the input file, no need of &header coz arrays declarations are addresses

    fwrite (header, HEADER_SIZE, 1, output); // write the header to the output file

    // TODO: Read samples from input file and write updated data to output file

    int16_t buffer;// create the buffer of one sample size to use

    while (fread(&buffer, sizeof(int16_t), 1, input)) // read samples from input to the buffer while there are samples to read
    {
        buffer *= factor; // modify the size of the samples to modify the volume

        fwrite(&buffer, sizeof(int16_t), 1, output); // write the modified file to output
    }
    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
