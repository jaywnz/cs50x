# Determines Coleman-Liau readability index for a given text

from cs50 import get_string

# Prompt for input
text = get_string("Text: ")

letters = 0
words = 1
sentences = 0

# Count letters, words and sentences
for char in text:
    if char.isalpha():
        letters += 1
    elif char.isspace():
        words += 1
    elif char == "." or char == "!" or char == "?":
        sentences += 1

# Calculate Coleman-Liau
letters_avg = (letters / words) * 100.0
sentences_avg = (sentences / words) * 100.0
index = (0.0588 * letters_avg) - (0.296 * sentences_avg) - 15.8

# Print grade level
if round(index) >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {round(index)}")
