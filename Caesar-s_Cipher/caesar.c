// This program implements the caesar's cipher to encrypt plaintext and print out ciphertext

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, string argv[])
{
    // Check if the user input is correct. Use s to check if input is numeric. Initialize key, k
    int k = 0;
    if (argc == 1 || argc > 2 || atoi(argv[1]) < 0 || atoi(argv[1]) == 0)
    {
        printf("Incorrect input! Please enter a single positive integer after ./caesar.\n");
        return EXIT_FAILURE;
    }
    else
    {
        // Convert key to an ineteger value
        k = atoi(argv[1]);
        // Check if k >= 26
        if (k >= 26)
        {
            k = k % 26;
        }
    }

    // Prompt user for plaintext and read it as string input
    printf("plaintext: ");
    string p = get_string();

    // Print ciphertext
    printf("ciphertext: ");

    // Iterate through chars in the string to shift chars by key, k to get ciphertext, c
    // c is the cipher array of the same length as p. Initialize it as a int array to store ASCII characters of p shifted by key, k.
    int c[strlen(p)];
    // b is an integer used to change ASCII to alphabetical index, i.e., A = 0 instead of 65. Used for enciphering calculation.
    int b;

    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha((char) p[i]))
        {
            if (isupper((char) p[i]))
            {
                b = (int) p[i] - 65;
                c[i] = ((b + k) % 26) + 65;
            }
            else
            {
                b = (int) p[i] - 97;
                c[i] = ((b + k) % 26) + 97;
            }
        }
        else
        {
            c[i] = (int) p[i];
        }
        //printf("b[%i] = %i\n", i, b[i]);
        printf("%c", c[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
