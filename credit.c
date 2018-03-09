// This program implements Luhn's algorithm to check a given credit card number and output if it's AMEX, VISA, MasterCard,
// or, INVALID.

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for credit card number
    long long ccnumber;
    do
    {
        ccnumber = get_long_long("Enter a card number: ");
    }
    while (ccnumber <= 0);

    // Get the length of the number (count). Initialize count and a temp. variable n, required for the calculation
    int count = 0;
    long long n = ccnumber;
    while (n != 0)
    {
        n /= 10;
        count++;
    }

    // Get the digits and store them in an array (digs) for easy retrieval. Initialize digs and m (for calc. only) before the loop.
    // Start the loop from the last digit and run it backward
    int digs[count];
    long long m = ccnumber;
    for (int i = count - 1; i >= 0; i--)
    {
        if (i == count - 1)
        {
            digs[i] = m % 10;
        }
        else
        {
            // Use m to a calculation to get successive digits
            m /= 10;
            digs[i] = m % 10;
        }
    }

    // Calculate the sum of products of 2 and every alternate number starting from last but one digit (sum1). Initialize sum1.
    int sum1 = 0;
    for (int i = count - 2; i >= 0; i = i - 2)
    {
        // If the product >= 10, split the digits and add them individually. Use n, like we did before. Intialize it.
        n = digs[i] * 2;
        if (digs[i] * 2 >= 10)
        {
            sum1 += n % 10;
            n /= 10;
            sum1 += n;
        }
        else
        {
            // If product is < 10, add it to sum1
            sum1 += digs[i] * 2;
        }
    }

    // Calculate the sum of every alternate number that wasn't chosen in the above step (sum2). Initialize sum2.
    int sum2 = 0;
    for (int i = count - 1; i >= 0; i = i - 2)
    {
        sum2 += digs[i];
    }

    // Check if the card belongs to AMEX, VISA, MasterCard, or if it's invalid
    if ((sum1 + sum2) % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // VISA has 16 digits and starts with 4
        if (digs[0] == 4 && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }
        //MasterCard has 16 digits ansd starts with 51, 52, 53, 54, or 55
        else if (digs[0] == 5 && ((digs[1] == 1) || (digs[1] == 2) || (digs[1] == 3) || (digs[1] == 4) || (digs[1] == 5)) && count == 16)
        {
            printf("MASTERCARD\n");
        }
        // AMEX has 13 digits and starts with 35 or 37
        else if (digs[0] == 3 && ((digs[1] == 5) || (digs[1] == 7)) && count == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            // Print invalid if all 3 checks fail
            printf("INVALID\n");
        }
    }
}