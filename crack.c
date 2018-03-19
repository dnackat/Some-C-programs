// This program cracks 5 letter alphabetical passwords encrypted with C's DES algorithm.

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#define _XOPEN_SOURCE 600
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, string argv[])
{
    // Check if the user input is correct. Use s to check if input is numeric. Initialize hash, h (string)
    char *h;
    if (argc == 1 || argc > 2)
    {
        printf("Incorrect input! Usage: ./crack hash\n");
        return EXIT_FAILURE;
    }
    else
    {
        // store the key in k
        h = argv[1];
    }

    //Salt is a string with first two chars of hash
    char s[3] = {h[0], h[1], '\0'};

    // Iterate over [a-zA-Z] to guess words (an array called pwd) starting with just 1 letter.
    // Create a hash in each try and compare this hash to h using strcmp. If successful, stop and return 0

    // Create a character array of size 6 to hold the password. Start with 1 letter and iterate from A to zzzzz
    char pwd[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
    // Assign pointer pnt to pwd. This is needed as it's one of the arguments in crypt().
    char *pnt = pwd;
    // Pointer of generated password try.
    char *pnthash;
    // Initialize n1...n5 for ASCII to char calculation
    int n1, n2, n3, n4, n5 = 0;

    // Create 5 loops of size since the password has 5 alphabets at most of uppercase or lowercase
    for (int a = 0; a < 52; a++)
    {
        for (int b = 0; b < 52; b++)
        {
            for (int c = 0; c < 52; c++)
            {
                for (int d = 0; d < 52; d++)
                {
                    for (int e = 0; e < 52; e++)
                    {
                        if (e < 26)
                        {
                            // Uppercase letters ('A' starts from 65)
                            n1 = e + 65;
                        }
                        else
                        {
                            // Lowercase letter ('a' starts from 97)
                            n1 = e + 71;
                        }
                        // First password try. 1st position in char array, pwd.
                        pwd[0] = (char) n1;
                        pnt = pwd;
                        // Generate hash for this try
                        pnthash = crypt(pnt, s);
                        // Compare this hash with the user-supplied hash
                        if (strcmp(h, pnthash) == 0)
                        {
                            // If successful, print password, return 0, and exit
                            printf("%s\n", pwd);
                            return EXIT_SUCCESS;
                            exit(0);
                        }
                    }

                    if (d < 26)
                    {
                        n2 = d + 65;
                    }
                    else
                    {
                        n2 = d + 71;
                    }
                    // 2nd position in char array, pwd.
                    pwd[1] = (char) n2;
                    pnt = pwd;
                    pnthash = crypt(pnt, s);
                    if (strcmp(h, pnthash) == 0)
                    {
                        printf("%s\n", pwd);
                        return EXIT_SUCCESS;
                        exit(0);
                    }
                }

                if (c < 26)
                {
                    n3 = c + 65;
                }
                else
                {
                    n3 = c + 71;
                }
                // 3rd position in char array, pwd.
                pwd[2] = (char) n3;
                pnt = pwd;
                pnthash = crypt(pnt, s);
                if (strcmp(h, pnthash) == 0)
                {
                    printf("%s\n", pwd);
                    return EXIT_SUCCESS;
                    exit(0);
                }
            }

            if (b < 26)
            {
                n4 = b + 65;
            }
            else
            {
                n4 = b + 71;
            }
            // 4th position in char array, pwd.
            pwd[3] = (char) n4;
            pnt = pwd;
            pnthash = crypt(pnt, s);
            if (strcmp(h, pnthash) == 0)
            {
                printf("%s\n", pwd);
                return EXIT_SUCCESS;
                exit(0);
            }
        }

        if (a < 26)
        {
            n5 = a + 65;
        }
        else
        {
            n5 = a + 71;
        }
        // 5th position in char array, pwd.
        pwd[4] = (char) n5;
        pnt = pwd;
        pnthash = crypt(pnt, s);
        if (strcmp(h, pnthash) == 0)
        {
            printf("%s\n", pwd);
            return EXIT_SUCCESS;
            exit(0);
        }
    }
}