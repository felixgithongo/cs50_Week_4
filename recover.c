#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        // accept a single CLA
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // open memory card
    FILE *card = fopen(argv[1], "r");

    // check if the card is empty
    if (card == NULL)
    {
        printf("%s could not be opened.\n", argv[1]);
        return 2;
    }

    // create a buffer for a block of a JPEG
    uint8_t buffer[512];

    // create the array that will hold the new image file names after extraction and initialize the
    // names at zero
    char filename[10];
    int filecount = 0;

    FILE *img = NULL; // to create the image file we will write to

    while (fread(buffer, 1, 512, card) == 512)
    {
        // create JPEGs from the data

        // look for JPEGS
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if already writing an img file, close it
            if (img != NULL)
            {
                fclose(img);
                img = NULL;
            }

            sprintf(filename, "%03i.jpg", filecount); // create a new filename
            filecount++;                              // increment the names on every loop

            img = fopen(filename, "w"); // open the filename for writing

            if (img == NULL) // check if the newly opened file has space
            {
                fclose(card); // close the card file and end the program if there is no space
                return 3;
            }
        }

        if (img != NULL) // if there is space, write on it
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    if (img != NULL) // close open JPEGs
    {
        fclose(img);
    }
    fclose(card);

    return 0;
}
