/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Changes a bmp file by factor of n.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    const int TRIPLESIZE = sizeof(RGBTRIPLE);
    
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames and size increase
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }
    
    // initialise outfile metadata
    BITMAPFILEHEADER obf = bf;
    BITMAPINFOHEADER obi = bi;
    // increase metadata values
    obi.biHeight = bi.biHeight * n; 
    obi.biWidth = bi.biWidth * n;
    // determine padding for scanlines
    int opadding =  (4 - (obi.biWidth * TRIPLESIZE) % 4) % 4;
    obi.biSizeImage = abs(obi.biHeight * (obi.biWidth * TRIPLESIZE + opadding));
    obf.bfSize = obi.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&obf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&obi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // number of times scanline has been repeated
    int scount = 0;
    
    // number of times pixel has been repeated
    int pcount = 0;
    
    // input bmp padding
    int ipadding =  (4 - (bi.biWidth * TRIPLESIZE) % 4) % 4;
    
    // iterate over infile's scanlines
    for (int i = 0, obiHeight = abs(obi.biHeight); i < obiHeight; i++)
    {
         // iterate over pixels in scanline
        for (int j = 0; j < obi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, TRIPLESIZE, 1, inptr);
            
            // write RGB triple to outfile
            fwrite(&triple, TRIPLESIZE, 1, outptr);    
            pcount++;
            
            // check if pixel has be repeated enough times
            if (pcount < n)
            {
                // move cursor back in order to rewrite pixel
                fseek(inptr, -TRIPLESIZE, SEEK_CUR);
            }
            else 
            {
                pcount = 0;
            }
            
        }
        
        // skip over padding, if any
        fseek(inptr, ipadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < opadding; k++)
        {
            fputc(0x00, outptr);
        }
        scount++;
        
        // check if scanline has been repeated enough times
        if (scount < n)
        {
            // move cursor to the beginning of scanline to repeat it again
            fseek(inptr, -((bi.biWidth * TRIPLESIZE + ipadding)), SEEK_CUR);
        }
        else
        {
            scount = 0;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
