#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int word_number(string s);
void grade(int i);

int main(void)
{
    string s = get_string("Text: ");
    grade(word_number(s));
}

//Counts the number of letters, words and sentences then return the index
int word_number(string s)
{
    int i, n_lettre = 0, n_mot = 1, n_phrase  = 0;
    for (i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]) != 0)
        {
            n_lettre++;
        }
        else if (isspace(s[i]) != 0)
        {
            n_mot++;
        }
        if (s[i] == 33 || s[i] == 46 || s[i] == 63)
        {
            n_phrase++;
        }
    }
    float L = ((float) n_lettre / n_mot) * 100;
    float S = ((float) n_phrase / n_mot) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}

//Determines the grade from the index
void grade(int i)
{
    if (i < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (i >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", i);
    }
}