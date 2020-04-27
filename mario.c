// prints two mario pyramids of given height

#include <stdio.h>
#include <cs50.h>

void blanks(int n);
void hashes(int n);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: "); // prompts the user for height input
    }
    while (height < 1 || height > 8);

    int k = height - 1;
    int m = height - k;
    for (int j = 0; j < height; j++) // loops same number of times as height
    {
        blanks(k);
        hashes(m);
        printf("  ");
        hashes(m);
        printf("\n");
        m++;
        k--;
    }
}

void blanks(int n) // prints blank spaces
{
    for (int a = 0; a < n; a++)
    {
        printf(" ");
    }
}

void hashes(int n) // prints hashes
{
    for (int a = 0; a < n; a++)
    {
        printf("#");
    }
}
