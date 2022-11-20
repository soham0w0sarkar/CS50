#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int f, string argv[])
{
    if (f != 2 || strlen(argv[1]) != 26)
    {
        printf("key must be of 26 letters\n");
        return 1;
    }

    int c[26];
    for (int i = 0; i < 26; i++) //checking if the character occured twice
    {
        c[i] = 0;
        if (islower(argv[1][i]))
        {
            c[argv[1][i] - 97]++; // -97 in lower case allows us to access the position of that charachter with a starting from 0
        }
        else if (isupper(argv[1][i]))
        {
            c[argv[1][i] - 65]++;
        }
    }

    for (int i = 0; i <= 26; i++)
    {
        if (isdigit(argv[1][i]))
        {
            printf("Key must be all characters\n");
            return 1;
        }
        else if (c[i] == 2)
        {
            printf("Character should occur only once\n");
            return 1;
        }
    }
    string text = get_string("plaintext: "); //taking plain text input

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int ch;
        if (isupper(text[i]))
        {
            ch = text[i] - 65; //ch target the position of character as a being 0
            argv[1][ch] = toupper(argv[1][ch]); //converting argument vector to uppercase as text has a upper case character here
            text[i] = argv[1][ch]; //storing the key element in text
        }
        else if (islower(text[i]))
        {
            ch = text[i] - 97;
            argv[1][ch] = tolower(argv[1][ch]);
            text[i] = argv[1][ch];
        }
    }

    printf("ciphertext: %s\n", text);

    return 0;

}