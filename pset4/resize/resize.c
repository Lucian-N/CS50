/**
 * Resizes an image by a scaling factor
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *term = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];
    int nsize =atol(term);

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
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPFILEHEADER r_bf = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    BITMAPINFOHEADER r_bi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // resized height and width for header info
    r_bi.biWidth = bi.biWidth * nsize;
    r_bi.biHeight = bi.biHeight * nsize;

    // determine padding for scanlines
    int r_padding = (4 - (r_bi.biWidth * sizeof(RGBTRIPLE)) % 4 ) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int ls = sizeof(RGBTRIPLE) * bi.biWidth;

    // resize file / info header
    r_bi.biSizeImage=((sizeof(RGBTRIPLE)*r_bi.biWidth)+r_padding)*abs(r_bi.biHeight);
    r_bf.bfSize= r_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&r_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&r_bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int h = 0; h <nsize-1; h++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int w=0; w<nsize; w++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            //  add outfile padding
            for (int p = 0; p < r_padding; p++)
            {
                fputc(0x00, outptr);
            }
            fseek(inptr, -ls, SEEK_CUR);
        }
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for(int k = 0; k < nsize; k++)
            {
            // write RGB triple to outfile n times
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        //  add outfile padding
        for (int p = 0; p < r_padding; p++)
        {
        fputc(0x00, outptr);
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
