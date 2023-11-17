#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"
int moy(int height, int width, RGBTRIPLE stored[height][width], int row, int col, char color);
int sober(int height, int width, RGBTRIPLE stored[height][width], int row, int col, char color);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int value;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            value = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / (float) 3);
            //printf("value = %i, fvalue = %f\n", value, fvalue);
            image[i][j].rgbtRed = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtBlue = value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*old_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            old_image[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = old_image[i][(width - 1) - j];
        }
    }
    free(old_image);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*old_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            old_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = moy(height, width, old_image, i, j, 'r');
            image[i][j].rgbtGreen = moy(height, width, old_image, i, j, 'g');
            image[i][j].rgbtBlue = moy(height, width, old_image, i, j, 'b');
        }
    }

    free(old_image);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*old_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            old_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = sober(height, width, old_image, i, j, 'r');
            image[i][j].rgbtGreen = sober(height, width, old_image, i, j, 'g');
            image[i][j].rgbtBlue = sober(height, width, old_image, i, j, 'b');
        }
    }

    free(old_image);
    return;
}

int sober(int height, int width, RGBTRIPLE stored[height][width], int row, int col, char color)
{
    //printf("init _ stored[%i][%i].%c\n", row, col, color);
    int gxsum = 0;
    int gysum = 0;
    int moy = 0;
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int in[3][3];
    //Get the adresse for the upper left pixel
    row--;
    col--;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (0 <= (i + row) && (i + row) < height && 0 <= (j + col) && (j + col) < width)
            {
                if (color == 'r')
                {
                    in[i][j] = stored[i + row][j + col].rgbtRed;
                }
                else if (color == 'g')
                {
                    in[i][j] = stored[i + row][j + col].rgbtGreen;
                }
                else if (color == 'b')
                {
                    in[i][j] = stored[i + row][j + col].rgbtBlue;
                }
            }
            else
            {
                in[i][j] = 0;
                //printf("in[%i][%i] = %i\n", i, j, in[i][j]);
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gxsum += in[i][j] * Gx[i][j];
            gysum += in[i][j] * Gy[i][j];
        }
    }
    moy = round(sqrt(pow(gxsum, 2) + pow(gysum, 2)));
    if (moy > 255)
    {
        moy = 255;
    }
    //printf("%c gxsum = %i gysum = %i moy = %i\n", color, gxsum, gysum, moy);
    return moy;
}

int moy(int height, int width, RGBTRIPLE stored[height][width], int row, int col, char color)
{
    int somme = 0;
    int k = 0;
    int moy = 0;
    //Get the adresse for the upper left pixel
    row--;
    col--;
    if (color == 'r')
    {
        for (int i = row; i < row + 3; i++)
        {
            for (int j = col; j < col + 3; j++)
            {
                if (0 <= i && i < height && 0 <= j && j < width)
                {
                    somme += stored[i][j].rgbtRed;
                    k++;
                }
            }
        }
    }
    else if (color == 'g')
    {
        for (int i = row; i < row + 3; i++)
        {
            for (int j = col; j < col + 3; j++)
            {
                if (0 <= i && i < height && 0 <= j && j < width)
                {
                    somme += stored[i][j].rgbtGreen;
                    k++;
                }
            }
        }
    }
    else if (color == 'b')
    {
        for (int i = row; i < row + 3; i++)
        {
            for (int j = col; j < col + 3; j++)
            {
                if (0 <= i && i < height && 0 <= j && j < width)
                {
                    somme += stored[i][j].rgbtBlue;
                    k++;
                }
            }
        }
    }
    moy = round(somme / (float) k);
    return moy;
}