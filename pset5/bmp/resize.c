/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4 ||  0 >= atoi(argv[1]) > 100)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    int n = atoi(argv[1]);
    
    if (n < 1 || n > 100)
    {
        printf("n must be [1,100]\n");
        return 2;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
   
    // create outfile's new file header info
    BITMAPFILEHEADER *pbf;
    BITMAPFILEHEADER r_bf;
    pbf = &bf;
    r_bf = *pbf;
    
    // create outfile's new info header info
    BITMAPINFOHEADER *pbi;
    BITMAPINFOHEADER r_bi;
    pbi = &bi;
    r_bi = *pbi;
    
    r_bi.biWidth = r_bi.biWidth * n;
    r_bi.biHeight = r_bi.biHeight * n;
    
    //determine padding for outfile
    int r_padding = (4 - (r_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    r_bi.biSizeImage = (r_bi.biWidth * abs(r_bi.biHeight) * sizeof(RGBTRIPLE)) + (r_padding * abs(r_bi.biHeight));
    
    r_bf.bfSize = r_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&r_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&r_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // determine padding for infile
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
            
        // temporary array declaration
        RGBTRIPLE rwColor[r_bi.biWidth];
        
        int start = 0;
        int limit = n;
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
             
            // write RGB triple to outfile n times (horiontal expansion)
            while (start < limit)
            {
                rwColor[start] = triple;
                start += 1;
            }
            
            limit += n;
        }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        
        // vertical expansion write
        for (int vex = 0; vex < n; vex++)
        {
            // horizontal expansion write
            for (int hex = 0; hex < r_bi.biWidth; hex++)
            {
            
                // write the contents of RGB array to outfile
                fwrite(&rwColor[hex], sizeof(RGBTRIPLE), 1, outptr);
            
            }
            
            // Add padding using outfile's padding
            for (int l = 0; l < r_padding; l++)
            {
                // one byte worth of zeroes
                fputc(0x00, outptr);
            }
        
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
