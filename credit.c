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
    len = get_length(cred); // fn gets length of card no.

    int first = 0;
    int second = 0;
    bool checksum;
    first = get_first_digit(cred, len); // fn gets first digit of card no.
    second = get_second_digit(cred, len); // fn gets second digit of card no.
    checksum = get_checksum(cred, len); // fn calculates checksum and returns true/false

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
        n /= 10;
        counter++;
    }
    return counter;
}

int get_first_digit(long n, int len) // returns first digit of card number
{
    int first = 0;
    int counter = 0;
    while(counter < len) // extracts the first digit
    {
        first = n % 10;
        n /= 10; // moves up a number
        counter++;
    }
    return first;
}

int get_second_digit(long n, int len) // returns first digit of card number
{
    int second = 0;
    int counter = 0;
    while(counter < len - 1) // extracts the second digit
    {
        second = n % 10;
        n /= 10; // moves up a number
        counter++;
    }
    return second;
}

bool get_checksum(long n, int len) // returns checksum pass/fail
{
    int x = 10;
    int even_total = 0;
    int odd_total = 0;
    int mod0 = 0;
    int mod1 = 0;
    float digit = 0; // needs to be more precise for division operation
    for (int i = 0; i < len; i++)
    {
        if ((i + 1) % 2 == 0) // if the counter is in an even position
        {
            mod0 = n % x; // gets digits from the end of card no. according to x
            mod1 = n % (x / 10); // gets numbers after digit above
            digit = mod0 - mod1; // extracts number with trailing zeroes
            digit = (digit / x) * 10; // drops trailing zeroes
            int sub_total = digit * 2; // doubles the digit
            even_total += sub_total % 10; // deals with two digit number by adding last digit
            even_total += (sub_total - (sub_total % 10)) / 10; // adds first digit of two digit number
        }
        else // if the counter is odd
        {
            mod0 = n % x;
            mod1 = n % (x / 10);
            digit = mod0 - mod1;
            digit = (digit / x) * 10;
            odd_total += digit;
        }
        x *= 10;
    }
    int total = 0;
    total = even_total + odd_total;
    if (total % 2 == 0) //
    {
        return true;
    }
    else
    {
        return false;
    }
}