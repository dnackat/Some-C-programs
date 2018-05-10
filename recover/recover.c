// This program recovers JPEG files from a FAT based memory card image.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define unsigned integer (8 bits) type for buffer
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check if argc = 1
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open raw image for reading
    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Initialize outfile pointer to keep the compiler happy
    FILE *outptr = NULL;

    // Read the file one block (512 B) at a time until EOF. Initialize jpegCounter for filename
    int jpegCounter = 0;
    int blockSize = 512;

    // Temp. buffer to check for EOF
    char bfTemp[blockSize];

    while (fread(bfTemp, sizeof(bfTemp), 1, inptr) == 1)
    {
        // Move pointer to beginning of block
        fseek(inptr, -blockSize, SEEK_CUR);

        // Dyn. allocate memory for read buffer
        BYTE *bfRead = malloc(blockSize * sizeof(char));

        // Read current block
        fread(bfRead, blockSize, 1, inptr);

        // Check if start of JPEG
        if (bfRead[0] == 0xff && bfRead[1] == 0xd8 && bfRead[2] == 0xff && (bfRead[3] & 0xf0) == 0xe0)
        {
            if (jpegCounter > 0)
            {
                // Close the previous jpeg file
                fclose(outptr);
            }

            // Open a new JPEG file for writing
            char *filename = malloc(10 * sizeof(char));
            sprintf(filename, "%03i.jpg", jpegCounter);
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", filename);
                return 2;
            }

            // Write current block to image file
            fwrite(bfRead, blockSize, 1, outptr);

            // Update jpeg Counter
            jpegCounter++;

            // Free memory allocated to filename
            free(filename);
        }
        else
        {
            if (jpegCounter > 0)
            {
                // Continue writing to the opened jpeg file
                fwrite(bfRead, blockSize, 1, outptr);
            }
        }

        // Free memory allocated to buffer
        free(bfRead);
    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Success
    return 0;
}