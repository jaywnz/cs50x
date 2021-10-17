# Imports characters from CSV into students database

import csv
import cs50
from sys import argv, exit

# Check for correct command-line arguments
if len(argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)

# Open database
db = cs50.SQL("sqlite:///students.db")

# Open CSV file for reading
with open(argv[1], "r") as characters:
    reader = csv.DictReader(characters)

    # Import characters in database
    for row in reader:
        full_name = row["name"]
        name = full_name.split()
        first = ""
        middle = None
        last = ""
        if len(name) == 2:
            first = name[0]
            last = name[1]
        else:
            first = name[0]
            middle = name[1]
            last = name[2]

        house = row["house"]
        birth = row["birth"]

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   first, middle, last, house, birth)
exit(0)
