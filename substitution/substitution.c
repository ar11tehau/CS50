#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void sub(string in, string key);

int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            for (int i = 0; i < strlen(key); i++)
            {
                if (isalpha(key[i]) == 0)
                {
                    printf("Key must contain only letters.\n");
                    return 1;
                }
            }
        }

    }
    int c = 0;
    for (int j = 0; j < strlen(key); j++)
    {
        for (int k = 0; k < strlen(key); k++)
        {
            if (key[j] == key[k])
            {
                c++;
            }
        }
        if (c != 1)
        {
            printf("Key must contains all alphabet letters\n");
            return 1;
        }
        c = 0;
    }

    //string key = "yukfrnlbavmwzteogxhcipjsqd";
    string in = get_string("plaintext: ");
    //string in = "This is CS50";
    sub(in, key);
    return 0;
}

//The cipher
void sub(string in, string key)
{
    char k_out[strlen(key)];
    for (int j = 0; j < strlen(key); j++)
    {
        if isupper(key[j])
        {
            k_out[j] = key[j];
        }
        else
        {
            k_out[j] = key[j] - 32;
        }
        k_out[j + 1] = '\0';
    }
    char out[strlen(in)];
    //Pour chaque charactère effectuer le changement ou pas
    for (int i = 0; i < strlen(in); i++)
    {
        //Si ce n'est pas une lettre ne rien changer
        if (isalpha(in[i]) == 0)
        {
            out[i] = in[i];
        }
        else
        {
            //Si c'est une majuscule remplacer par la majuscule de la clé
            if (isupper(in[i]) != 0)
            {
                out[i] = k_out[in[i] - 65];
            }
            //Sinon remplacer par la minuscule de la clé
            else
            {
                out[i] = k_out[in[i] - 97] + 32;
            }
        }
        out[i + 1] = '\0';
    }
    printf("ciphertext: %s\n", out);
}