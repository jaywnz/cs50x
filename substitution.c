// Runs a substitution cipher on a user-submitted string
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void encipher(string key, string plaintext, int cipher[]);
int validate_key(string key);

const char KEY_INDEX[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    // Check whether key is present as an argument
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    // Check whether key is valid
    string key = argv[1];
    if (validate_key(key))
    {
        return 1;
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");
    int len = strlen(plaintext);
    int cipher[len];
    encipher(key, plaintext, cipher);

    // Print ciphertext
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", cipher[i]);
    }
    printf("\n");
    return 0;
}

// Encipher plaintext based on substitution key
void encipher(string key, string plaintext, int cipher[])
{
    for (int j = 0, o = strlen(plaintext); j < o; j++)
    {
        // Find out what position given char is in the key_index
        for (int k = 0, p = strlen(key); k < p; k++)
        {
            if (toupper(plaintext[j]) == KEY_INDEX[k])
            {
                if (isalpha(plaintext[j]))
                {
                    if (isupper(plaintext[j]))
                    {
                        cipher[j] = toupper(key[k]);
                        break;
                    }
                    else
                    {
                        cipher[j] = tolower(key[k]);
                        break;
                    }
                }
                // else
                // {
                //     cipher[j] = plaintext[j];
                // }
            }
            else
            {
                cipher[j] = plaintext[j];
            }
        }
    }
}

// Checks key to ensure validity
int validate_key(string key)
{
    // Check key length is 26
    if (strlen(key) != 26)
    {
        printf("Please supply a valid key (invalid length).\n");
        return 1;
    }

    // Check key is all alphanumeric characters
    for (int i = 0, n = 26; i < n; i++)
    {
        if (isalpha(key[i]) == false)
        {
            printf("Please supply a valid key (non-alpha characters).\n");
            return 1;
        }
    }

    // Check key contains each letter and only once
    int counter = 0;
    for (int j = 0, o = 26; j < o; j++)
    {
        for (int k = 0, p = 26; k < p; k++)
        {
            if (toupper(key[j]) == KEY_INDEX[k])
            {
                counter++;
                break;
            }
        }
    }
    if (counter != 26)
    {
        printf("Please supply a valid key (characters absent or multiple).\n");
    }

    // If all checks are passed
    return 0;
}
