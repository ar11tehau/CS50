#include <cs50.h>
#include <stdio.h>
#include <math.h>

int digit(long number, int l, int i);
int length(long number);
bool test(long number);
int luhn(long number);

int main(void)
{
    long number = 4003600000000014;
    bool res = false;
    do
    {
        long n = get_long("Number: ");
        res = test(n);
    }
    while (res == false);
}

// Try Luhn's Algorithm
int luhn(long number)
{
    // Create an array with the given number
    int l = length(number);
    int array[l];
    for (int x = 0; x < l; x++)
    {
        array[x] = number % 10;
        number = number / 10;
    }
    // Create the sum of every other digit mutiply by 2, starting with the number's second-to-last digit
    int prod = 0;
    int sum_prod = 0;

    for (int i = 1; i < l; i += 2)
    {
        prod = array[i] * 2;
        if (prod <= 9)
        {
            sum_prod += prod;
        }
        else // if prod has two digits
        {
            int lp = length(prod);
            int dig[lp];
            for (int x = 0; x < lp; x++)
            {
                dig[x] = prod % 10;
                prod = prod / 10;
            }
            for (int j = 0; j < lp; j++)
            {
                sum_prod += dig[j];              //add the two digits to the sum
            }
        }
    }

    // Create the sum of the digits that weren’t multiplied by 2.
    int sum_sum = 0;
    for (int i = 0; i < l; i += 2)
    {
        {
            sum_sum += array[i];
        }
    }
    int sum = (sum_prod + sum_sum) % 10;

    return sum;
}

//Function to get the 'i' first digits of a number with l as lenght
int digit(long number, int l, int i)
{
    int td = number / (pow(10, l - i));
    return td;
}


//Function to find the length of the number
int length(long number)
{
    long n = number;
    int length = 0;
    while (number != 0)
    {
        number = number / 10;
        length++;
    }
    return length;
}

// Try if the number has the correct length and the correct start
bool test(long number)
{
    int l = length(number);
    int dig = digit(number, l, 1);
    // VISA
    if (dig == 4 && (l == 13 || l == 16) && luhn(number) == 0)
    {
        printf("VISA\n");
        return true;
    }
    else
    {
        dig = digit(number, l, 2);
        // AMEX
        if (l == 15 && (dig == 34 || dig == 37) && luhn(number) == 0)
        {
            printf("AMEX\n");
            return true;
        }
        // MTD
        else if (l == 16 && (dig == 51 || dig == 52 || dig == 53 || dig == 54 || dig == 55) && luhn(number) == 0)
        {
            printf("MASTERCARD\n");
            return true;
        }
        else
        {
            printf("INVALID\n");
            return true;
        }
    }
}
