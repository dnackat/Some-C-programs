# credit.py

# Include everything in the main function to match C


def main():
    # Prompt user for credit card number
    ccnumber = int(input("Enter a card number: "))

    # Check if the number > 0
    while ccnumber <= 0:
        ccnumber = int(input("Invalid number! Enter a card number: "))

    # Get the length of the card number
    count = len(str(ccnumber))

    # Store the digits of the card in a list for convenience
    digs = []
    m = ccnumber
    for i in range(count, 0, -1):
        # Do number mod 10 to get the last digit
        if i == count:
            digs.append(m % 10)
        else:
            # Divide (floor) number by 10 and then do modulo to get subsequent digits
            m //= 10
            digs.append(m % 10)

    # Multiply digits starting from the last but one'th position by 2 and and store in sum
    sum1 = 0
    for i in range(1, count, 2):
        # If the product > 10, split the digits and add them individually to sum1
        n = digs[i] * 2
        if n >= 10:
            sum1 += n % 10
            n //= 10
            sum1 += n
        else:
            sum1 += n

    # Sum over all the remaining digits and store them in sum2
    sum2 = 0
    for i in range(0, count, 2):
        sum2 += digs[i]

    # Check if card is valid
    if (sum1 + sum2) % 10 != 0:

        print("INVALID")

    else:
        if digs[count - 1] == 4 and (count == 13 or count == 16):

            print("VISA")

        elif digs[count - 1] == 5 and (digs[count - 2] == 1 or digs[count - 2] == 2 or
                                       digs[count - 2] == 3 or digs[count - 2] == 4 or digs[count - 2] == 5) and count == 16:

            print("MASTERCARD")

        elif digs[count - 1] == 3 and (digs[count - 2] == 5 or digs[count - 2] == 7) and count == 15:

            print("AMEX")

        else:

            print("INVALID")

    # Return 0
    return 0


# Call main by default
if __name__ == "__main__":
    main()
