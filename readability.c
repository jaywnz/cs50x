#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <cs50.h>

int count_letters (string text);
int count_words(string text);
int count_sentences(string text);
float calc_index(int l, int w, int s);

int main(void)
{
    string text = get_string("Text: ");
    int l = count_letters(text);
    int w = count_words(text);
    int s = count_sentences(text);
    float index = calc_index(l, w, s);
    printf("%f\n", index);

    if (round(index) >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string text) // counts the number of letters in a string
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text) // counts the number of words
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isblank(text[i]))
        {
            count++;
        }
    }
    return count + 1; // adds one to account for last word
}

int count_sentences(string text) // counts the number of sentences
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

float calc_index(int l, int w, int s) // calculates Coleman-Liau index
{
    float letters_avg = ((float) l / (float) w) * 100;
    float sentences_avg = ((float) s / (float) w) * 100;
    float index = (0.0588 * letters_avg) - (0.296 * sentences_avg) - 15.8;
    return index;
}