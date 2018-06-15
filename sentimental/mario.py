# mario.py

# Check if input is numeric and between 0 and 23
while True:
    try:
        height = int(input("Please enter the size of the pyramid: "))
    except ValueError:
        print("Invalid input! Please enter a number between 0 and 23.")
        continue
    if height < 0 or height > 23:
        print("Invalid input! Please enter a number between 0 and 23.")
    else:
        break


# Build the pyramid
for i in range(height):
    # Loop to add spaces for left-indenting
    for j in range(height - (i + 1)):
        # Print space
        print(" ", end="")

    # Print hashes
    if i == 0:
        print("#  #", end="")
    else:
        for k in range(i + 1):
            # Print left hashes
            print("#", end="")

        # Print 2 spaces
        print("  ", end="")

        # Print right hashes
        for k in range(i + 1):
            # Print left hashes
            print("#", end="")

    # Print a new line before the next loop
    print()