#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n"); // prompts for user's name
    printf("hello, %s\n", name); // prints hello and their name
}