// This program implements the greedy algorithm to calculate the least amount of coins needed for a certain change amount.

#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    // Get change amount from the user. Also initialize amount (called dollars)
    float dollars;
    do
    {
        dollars = get_float("Change owed (in dollars): ");
    }
    while (dollars < 0.0);

    // Convert dollar amount to cents and round off to the nearest cent. Initialize cents.
    int cents;
    cents = round(dollars * 100);

    // Initialize number of coins (called 'coins') and difference amount (called 'diff')
    int coins = 0;
    int diff = cents;

    // Use while loops to get the least amount of coins required starting with the largest coin. Quarters below:
    while (diff >= 25)
    {
        // Calculate difference amount
        diff -= 25;
        // Update number of coins
        coins += 1;
    }

    // Dime below
    while (diff >= 10)
    {
        // Calculate difference amount
        diff -= 10;
        // Update number of coins
        coins += 1;
    }

    // Nickel below.
    while (diff >= 5)
    {
        // Calculate difference amount
        diff -= 5;
        // Update number of coins
        coins += 1;
    }
    // Penny below.
    while (diff >= 1)
    {
        // Calculate difference amount
        diff -= 1;
        // Update number of coins.
        coins += 1;
    }

    // Print out the number of coins
    printf("%i\n", coins);
}