/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }
    
    char* infile = argv[1];
    
    // size of the block that will be read and written
    const int BLOCK_SIZE = 512;
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    unsigned char buffer[BLOCK_SIZE];
    
    // pointer to outfile
    FILE* outptr = NULL;
    
    // make space for jpg file name
    char image[7];
    
    // number of image files created
    int n = 0;

    // search until jpg is found
    while(fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        // find the beginning of an jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // close image file if one has been created
            if (n > 0)
            {
                fclose(outptr);
            }
            // make name for nth image
            sprintf(image, "%03d.jpg", n);
            
            // open nth image file
            outptr = fopen(image, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", image);
                return 3;
            }
            
            // increment number of image files created
            n++;
        }
        
        // write to image file only if one exists 
        if (outptr != NULL)
        {
            // write to image file
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }
    
    // close last image file
    fclose(outptr);
    
    // close card.raw
    fclose(inptr);
    
    // that's all folks
    return 0;
}
