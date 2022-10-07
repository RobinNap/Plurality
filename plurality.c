#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of canidates 
#define MAX 9

// Canidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
canidate;

// Array of canidates 
canidate canidates[MAX];

// Number of canidates
int canidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [canidate . . .]\n");
        return 1;
    }

    // Populate array of canidates
    canidate_count = argc - 1;
    if (canidate_count > MAX)
    {
        printf("Maximum number of canidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < canidate_count; i++)
    {
        canidates[i].name = argv[i + 1];
        canidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of selection
    print_winner();
}

// Update vote tools given a new vote
int get_index(string name)
{
    for (int i = 0; i < canidate_count; i++)
    if (strcmp(name, canidates[i].name) == 0)
        return i;

    return -1;
}
//Update vote totals given new vote
bool vote(string name)
{
    int canidate_index = get_index(name);
    if (canidate_index != -1)
    {
        canidates[canidate_index].votes++;
        return true;
    }
    return false;
}

int get_max(void)
{
    int max_votes = canidates[0].votes;
    for (int i = 1; i < canidate_count; i++)
        if (canidates[i].votes > max_votes)
        max_votes = canidates[i].votes;

    return max_votes;
}

// Print the winner (or winners) of the selection
void print_winner(void)
{
    int max_votes = get_max();

    for (int i = 0; i < canidate_count; i++)
    {
        if (canidates[i].votes == max_votes)
        printf("%s\n", canidates[i].name);
    }
}
