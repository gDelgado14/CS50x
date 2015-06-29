/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define MYFILE "card.raw"
#define BLOCK 512
int main(int argc, char* argv[])
{
    
    typedef uint8_t  BYTE;
    
    
    //ensure proper usage
    if (argc != 1)
    {
        printf("No arguments\n");
        return 1;  
    }
    
    // open .raw file for reading only
    FILE* analyze = fopen(MYFILE, "r");
    if (analyze == NULL)
    {
        printf("Could not open %s.\n", MYFILE);
        return 2;
    }
    
    // array to store the image's blocks
    BYTE temp[BLOCK];
    
    bool found = false;
    int fcounter = 0;
    
    FILE *img;
    
    // iterate over file's blocks
    while (fread(&temp,sizeof(BYTE),BLOCK,analyze) == BLOCK)
    {
            
        // start of new file
        if ( (temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff && temp[3] == 0xe0 ) ||
           ( temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff && temp[3] == 0xe1 ) )
        {
            found = true;
            
            if (fcounter > 0)
            {
                fclose(img);
            }
            // filename holder
            char ftitle[7];
            
            sprintf(ftitle, "%.3d.jpg",fcounter);
            
            img = fopen(ftitle, "w");
            
            fwrite(&temp, sizeof(BYTE), BLOCK, img);
            
            fcounter++;
        }
        
        else if (found)
        {
            // continue processing current jpeg
            fwrite(&temp, sizeof(BYTE), BLOCK, img);
        }
   
    }
    
    
    fclose(analyze);
    fclose(img);
    
    return 0;
}
