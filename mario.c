#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for height of the half-pyramid. Initialize height.
    int height;

    do
    {
        height = get_int("Enter the desired height (0 to 23): ");
    }
    while(height < 0 || height > 23);

    // Construct the pyramid of the specified height. Row loop below.
    for (int i = 0; i < height; i++)
    {
        // Print spaces to make the pyramid right aligned. Space loop below.
        for (int j = (height - (i+1)); j > 0; j--)
        {
            printf(" ");
        }

        // Print hashes. Hash loop below.
        if (i == 0)
        {
            printf("#  #");
        }
        else
        {
            // Left hashes.
            for (int j = 0; j < (i+1); j++)
            {
                printf("#");
            }

            // Print 2 spaces.
            printf("  ");

            // Right hashes.
            for (int j = 0; j < (i+1); j++)
            {
                printf("#");
            }
        }


        // Print a new line to go to the next row
        printf("\n");
    }
}