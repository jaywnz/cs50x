# Queries database and prints house roster

import cs50
from sys import argv, exit

# Check for correct command-line arguments
if len(argv) != 2:
    print("Usage: python roster.py house")
    exit(1)

# Open database
db = cs50.SQL("sqlite:///students.db")

# Query database
student = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last", argv[1])

# Print students in house
for i in student:
    if i["middle"] is None:
        print("{} {}, born {}".format(i["first"], i["last"], i["birth"]))
    else:
        print("{} {} {}, born {}".format(i["first"], i["middle"], i["last"], i["birth"]))
exit(0)
