#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Add a vote if candidate name matches
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Print name and return if only one candidate in election
    if (candidate_count == 1)
    {
        printf("%s\n", candidates[0].name);
        return;
    }

    // Bubble sort array with greatest number of votes at start
    // Temporary struct to hold items being swapped
    candidate tmp[1];
    int swap_counter = -1;
    while (swap_counter != 0)
    {
        swap_counter = 0;
        for (int i = 0, n = candidate_count; i < n; i++)
        {
            if (candidates[i].votes < candidates[i + 1].votes)
            {
                tmp[0] = candidates[i];
                candidates[i] = candidates[i + 1];
                candidates[i + 1] = tmp[0];
                swap_counter++;
            }
        }
    }

    // Print winner(s) with greatest no. votes
    for (int j = 0, o = candidate_count; j < o; j++)
    {
        if (candidates[j].votes >= candidates[j + 1].votes && candidates[j + 1].name != NULL)
        {
            printf("%s\n", candidates[j].name);
        }
    }
    return;
}
