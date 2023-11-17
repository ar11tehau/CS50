#include <cs50.h>
#include <stdio.h>


void ligne(int h, int i);

int main(void)
{
    int h;
    //Asking the height between 1 and 8
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || 8 < h);

    for (int i = 1; i <= h; i++)
    {
        //Printing the lines
        ligne(h, i);
    }

}



void ligne(int h, int i)
{
    for (int j = (h - i); j > 0; j--) // left spaces
    {
        printf(" ");
    }
    for (int j = (h - i); j < h; j++) // left hashtags
    {
        printf("#");
    }
    printf("  ");
    for (int j = (h - i); j < h; j++) // right hashtags
    {
        printf("#");
    }
    printf("\n");
}