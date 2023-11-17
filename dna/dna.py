import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage ./dna.py FILE.csv FILE.txt")

    # TODO: Read database file into a variable
    file = open(sys.argv[1], "r")
    database = csv.DictReader(file)
    file.close

    file = open(sys.argv[1], "r")
    col = csv.reader(file)
    file.close

    for i in col:
        subsequences = i[1:]
        break

    # TODO: Read DNA sequence file into a variable
    file = open(sys.argv[2], "r")
    for i in file:
        sequence = i.strip("\n")
    file.close

    # TODO: Find longest match of each STR in DNA sequence
    unkown = {}
    for subsequence in subsequences:
        unkown[str(subsequence)] = longest_match(sequence, subsequence)

    # TODO: Check database for matching profiles
    for i in database:
        found = False
        for subsequence in subsequences:
            if int(unkown[subsequence]) == int(i[subsequence]):
                found = True
            else:
                found = False
                break
        if (found):
            print(i["name"])
            return
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
