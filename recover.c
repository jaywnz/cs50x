#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Accept only 1 command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file for reading
    FILE *card = fopen(argv[1], "r");
    // Check whether file can be opened for reading
    if (!card)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    // Create 512 byte buffer
    BYTE *buffer = malloc(512 * sizeof(BYTE));

    // Allocate memory to store filename in string
    char *filename = malloc(8 * sizeof(char));

    // Initialise counter for file naming
    int jpeg_count = -1;

    FILE *img = NULL;

    // Repeat until fread cannot return 512 (denoting EOF)
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Find start of new JPEG by header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Count each JPEG found
            jpeg_count++;

            // Check if it is the first JPEG
            if (jpeg_count == 0)
            {
                // Generate filename, open new file and write buffer
                sprintf(filename, "%03i.jpg", jpeg_count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
            else
            {
                // Close previous file
                fclose(img);
                // Generate filename, open new file and write buffer
                sprintf(filename, "%03i.jpg", jpeg_count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
        }
        else if (jpeg_count > 0)
        {
            // Keep writing to JPEG already open
            fwrite(buffer, 1, 512, img);
        }
    }
    free(filename);
    free(buffer);
    fclose(img);
    fclose(card);

    return 0;
}
