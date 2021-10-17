# Matches a DNA sequence to a person

import csv
import re
from sys import argv, exit

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

str_counts = {}

# Open CSV data file
with open(argv[1], newline='') as csvfile:
    data = csv.reader(csvfile)
    fields = next(data)

    # Open sequence file
    with open(argv[2], 'r') as txtfile:
        sequence = txtfile.readlines()

    # Extract STRs
    for i in range(len(fields) - 1):
        current_str = fields[i + 1]
        str_length = len(current_str)

        # Count longest run of consecutive repeats of STRs
        # Line 29 adapted from https://www.geeksforgeeks.org/python-maximum-consecutive-substring-occurrence/
        matches = max(re.findall('(?:' + current_str + ')*', sequence[0]))
        count = len(matches) / len(current_str)
        str_counts[current_str] = int(count)

    # Check STR counts against individuals in CSV file and print result
    values = list(str_counts.values())
    for row in data:
        individual_str = [int(i) for i in row[1:]]
        if values == individual_str:
            print(row[0])
            exit(0)
    print('No match')
    exit(0)
