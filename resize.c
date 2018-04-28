// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // Convert resize factor to an integer
    int n = atoi(argv[1]);

    // Check and make sure n is between 0 and 100
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Bad input: Factor must be a positive integer between 0 and 100");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfo;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    // Save a copy of file header to be modified for outfile
    bfo = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bio;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    // Save a copy of info header to be modified for outfile
    bio = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Change some header parameters before to outfile
    bio.biWidth = bi.biWidth * n;
    bio.biHeight = bi.biHeight * n;

    // Calculate padding for outfile
    int paddingOut = (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Calculate image size with these parameters
    bio.biSizeImage = ((bio.biWidth * sizeof(RGBTRIPLE)) + paddingOut) * abs(bio.biHeight);

    // Calculate total file size of outfile
    bfo.bfSize = bio.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines in infile
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // temp. array of struct RGBTRIPLE's for storing current row of outfile
        RGBTRIPLE buffArr[bio.biWidth];

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // store current RGB triple in row array 'n' times
            for (int m = 0; m < n; m++)
            {
                buffArr[n * j + m] = triple;
            }
        }

        // Write row to outfile and add padding 'n' times
        for (int r = 0; r < n; r++)
        {
            fwrite(buffArr, sizeof(RGBTRIPLE), bio.biWidth, outptr);

            // Add padding to outfile row
            for (int k = 0; k < paddingOut; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over infile padding, if any
        fseek(inptr, padding, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
