#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // string word1 = "Questions?";
    // string word2 = "Questions!";
    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    printf("score1 : %d score2: %d\n", score1, score2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;
    int temp = 0;
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        temp = toupper(word[i]) - 65;
        if (0 <= temp && temp <= 25)
        {
            score += POINTS[toupper(word[i]) - 65];
        }
    }

    return score;
}
