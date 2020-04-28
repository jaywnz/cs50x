// determines whether a given credit card number is valid

#include <stdio.h>
#include <cs50.h>

int get_length(long n);
int get_first_digit(long n, int len);
int get_second_digit(long n, int len);
bool get_checksum(long n, int len);

int main(void)
{
    long cred = 0;

    do  // loop ensures no negative numbers are entered
    {
        cred = get_long("Enter number: ");
    }
    while (cred < 0);

    int len = 0;
    len = get_length(cred); // fn gets length of card no. for later testing

    int first = 0;
    int second = 0;
    bool checksum;
    first = get_first_digit(cred, len); // fn gets first digit of card no.
    second = get_second_digit(cred, len); // fn gets second digit of card no.
    checksum = get_checksum(cred, len); // fn calculates checksum and returns bool
    // if/else blocks check different card conditions
    if (checksum && first == 4 && (len == 13 || len == 16))
    {
        printf("VISA\n");
    }
    else if (checksum && first == 5 && (second == 1 || second == 2 || second == 3 || second == 4 || second == 5) && len == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (checksum && first == 3 && (second == 4 || second == 7) && len == 15)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int get_length(long n) // returns length of credit card number
{
    int counter = 0;
    while (n != 0)
    {
        n /= 10; // removes the last digit
        counter++;
    }
    return counter;
}

int get_first_digit(long n, int len) // returns first digit of card number
{
    int first = 0;
    int counter = 0;
    while (counter < len) // extracts first digit by stopping at length of n
    {
        first = n % 10; // stores last digit
        n /= 10; // removes last digit
        counter++;
    }
    return first;
}

int get_second_digit(long n, int len) // returns second digit of card number
{
    int second = 0;
    int counter = 0;
    while (counter < len - 1) // extracts second digit by stopping one place before length of n
    {
        second = n % 10; // stores last digit
        n /= 10; // removes last digit
        counter++;
    }
    return second;
}

bool get_checksum(long n, int len) // calculates card no. checksum
{
    int even_total = 0;
    int odd_total = 0;
    for (int counter = 0; counter < len; counter++)
    {
        int digit = n % 10; // gets last digit of n
        n /= 10; // removes last digit
        if (counter % 2 != 0) // odd counter (starts at 0)
        {
            digit *= 2;
            int last_digit = digit % 10; // gets last digit
            int first_digit = digit / 10; // gets first digit (max 18), will return 0 for single digits
            odd_total += last_digit + first_digit;
        }
        else // even counter
        {
            even_total += digit;
        }
    }
    int total = even_total + odd_total;
    if (total % 10 == 0) // checks if last digit is 0
    {
        return true;
    }
    else
    {
        return false;
    }
}