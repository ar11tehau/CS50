def main():
    try:
        # Checking if the lenght number if correct
        number = int(input("Number: "))
        if (len(str(number)) in [13, 15, 16]):
            number
            if (luhn(number)):
                digits(number)
        else:
            print("INVALID")
    # Intercept if the input contains some string
    except ValueError:
        print("INVALID")


# Using the Luhn's alogrithm
def luhn(number):
    number = str(number)
    i = len(number) - 2
    # Initialize the sum of every other digit mutiply by 2, starting with the number's second-to-last digit
    first = []
    sum = 0
    # Create an array with the products
    while (i >= 0):
        result = int(number[i]) * 2
        first.append(result)
        i -= 2
    # Checking if there is two digits number
    for i in first:
        if len(str(i)) > 1:
            for j in str(i):
                sum += int(j)
        else:
            sum += i

    # Initialize the sum of the digits that weren’t multiplied by 2.
    i = len(number) - 1
    while (i >= 0):
        sum += int(number[i])
        i -= 2

    if (sum % 10) == 0:
        return True
    else:
        return False


def digits(number):
    snumber = str(number)
    if int(snumber[0:2]) in [34, 37]:
        print("AMEX")
    elif int(snumber[0:2]) in range(51, 56):
        print("MASTERCARD")
    elif int(snumber[0]) == 4:
        print("VISA")


if __name__ == "__main__":
    main()
