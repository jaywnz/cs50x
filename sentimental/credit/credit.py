# Validates a credit card number

from cs50 import get_string

# Prompt for user input
while True:
    cred = get_string("Enter number: ")
    if int(cred) > 0:
        break

# Slice first and second digits
first = cred[0:1]
second = cred[1:2]

# Calculate checksum
even_total = 0
odd_total = 0
# Multiply every other digit starting from second-to-last and add products' digits
for n in range(len(cred) - 2, -1, -2):
    x = int(cred[n]) * 2
    first_digit = x % 10
    last_digit = x // 10
    odd_total += last_digit + first_digit
# Add remaining digits
for o in range(len(cred) - 1, -1, -2):
    even_total += int(cred[o])
total = odd_total + even_total

if total % 10 == 0:
    checksum = True
else:
    checksum = False

# Check for card type and print result
if first == "4" and (len(cred) == 13 or len(cred) == 16) and checksum == True:
    print("VISA")
elif first == "5" and (second == "1" or second == "2" or second == "3" or second == "4" or second == "5") and len(cred) == 16 and checksum == True:
    print("MASTERCARD")
elif first == "3" and (second == "4" or second == "7") and len(cred) == 15 and checksum == True:
    print("AMEX")
else:
    print("INVALID")
