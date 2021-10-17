# Prints two Mario pyramids of a given height

from cs50 import get_int

# Accept valid input from user
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

blanks = height - 1
hashes = height - blanks

# Loop to print each row
for row in range(height):
    print(" " * blanks, end="")
    print("#" * hashes, end="")
    print(" " * 2, end="")
    print("#" * hashes)
    hashes += 1
    blanks -= 1