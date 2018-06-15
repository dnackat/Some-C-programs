# vigenere.py

import sys
import string

# Define a main function to match C code


def main():
    # Check if input is correct
    if len(sys.argv) == 1 or len(sys.argv) > 2 or not str.isalpha(sys.argv[1]):
        print("Usage ./vignere k")
        sys.exit(1)
    else:
        # Convert key to lowercase
        key = str.lower(sys.argv[1])

    # Create a dictionary containing numerical shifts corresponding to alphabets
    shifts = {list(string.ascii_lowercase)[i]: i for i in range(26)}

    # Get plaintext from user
    p = input("plaintext: ")

    # Get ready to print cyphertext
    print("ciphertext: ", end="")

    # Loop over all letters and do shifts
    c = []
    # Variable to keep track of position in keyword
    t = 0
    for k in range(len(p)):
        # Check if letter is an alphabet
        if str.isalpha(p[k]):
            # Check if uppercase or lowercase
            if str.isupper(p[k]):
                # Shift by ASCII value (A = 0 instead of 65)
                s = ord(p[k]) - 65
                # Apply the ciphering formula
                c.append(chr(((s + shifts[key[t % len(key)]]) % 26) + 65))
                # Update keyword position
                t += 1
            else:
                # Shift by ASCII value (a = 0 instead of 97)
                s = ord(p[k]) - 97
                # Apply the ciphering formula
                c.append(chr(((s + shifts[key[t % len(key)]]) % 26) + 97))
                # Update keyword position
                t += 1
        else:
            c.append(p[k])

    # Print ciphertext
    for ch in c:
        print(ch, end="")

    # Print newline
    print()

    # Return 0 if successful
    return 0


if __name__ == "__main__":
    main()