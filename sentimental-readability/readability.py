def main():
    text = input("Text: ")

    # Initializing
    sentences = 0
    words = 1
    letters = 0

    # Incrementing
    for i in text:
        if i in ["!", ".", "?"]:
            sentences += 1
        if i.isalpha():
            letters += 1
        if i == " ":
            words += 1

    # Average number of letters per 100 words in text
    L = (letters / words) * 100

    # Average number of sentences per 100 words in text
    S = (sentences / words) * 100

    # Coleman-Liau index
    CL = round(0.0588 * L - 0.296 * S - 15.8)

    # Condition on CL
    if CL < 1:
        print(f"Before Grade 1")
    elif CL > 16:
        print(f"Grade 16+")
    else:
        print(f"Grade {CL}")


if __name__ == "__main__":
    main()