
def main():
    height = 0

    try:
        # Checking that the value of height is between 1 and 8 included
        while height < 1 or height > 8:
            height = int(input("Height : "))
    # Catching Error, if the user input is an int
    except ValueError:
        main()

    space = height - 1
    wall = 1
    while (wall <= height):
        # Creating the line
        print(" " * space + "#" * wall + "  " + "#" * wall)
        space -= 1
        wall += 1


if __name__ == "__main__":
    main()