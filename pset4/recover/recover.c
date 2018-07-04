#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw");
        return 1;
    }

    // remembers the file and checks for if file exists
    char *p_file = argv[1];
    FILE *file = fopen(p_file, "r");

    // check if file is valid
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s. \n", p_file);
        return 2;
    }
    //  variable declaration
    unsigned char buffer[512]; //size of buffer
    int counter = 0; // number of images
    FILE *img = NULL;
    int found = 0;

    // reads from the file
    while (fread(buffer, 512, 1, file) == 1)
    {

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0)
        {
            if (found == 1)
            {
                fclose(img);
            }
            else
            {
                found = 1;
            }
            char jpg[8];
            sprintf(jpg, "%03d.jpg", counter);
            img = fopen(jpg, "a");
            counter++;
        }

        if (found == 1)
        {
            fwrite (&buffer, 512, 1, img);
        }

    }

    fclose(file);
    fclose(img);
    return 0;


}