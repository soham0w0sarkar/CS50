#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    string text = get_string("TEXT : "); //taking text input from user

    int letters = count_letters(text); //fucntion for counting letter
    int words = count_words(text); //fucntion for counting words
    int sentences = count_sentences(text); //fucntion for counting sentences

    float L = ((float)letters / words * 100); //average letters per 100 words
    float S = ((float)sentences / words * 100); //average sentences per 100 words

    printf("%d,%d,%d,%f,%f",letters,words,sentences,L,S);
    int x = round(0.0588 * L - 0.296 * S - 15.8); //formula

    if (x >= 16) //if level is 16 or greater
    {
        printf("Grade 16+\n");
    }
    else if (x < 1) //if level if less than 1
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", x);
    }


}

int count_letters(string s)
{
    int c = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i])) //if the character is a alphabet
        {
            c++;
        }
    }
    return c;
}

int count_words(string s)
{
    int c = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isspace(s[i])) //checking for space
        {
            c++;
        }
    }
    c++; //counting the last word

    return c;
}

int count_sentences(string s)
{
    int c = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!') //checking for end of sentences with ? . !
        {
            c++;
        }
    }
    return c;
}
