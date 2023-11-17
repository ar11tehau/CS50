#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool islocked(int mw); //mw maybe winner
int lockedloser(int winner);
void print_winner(void);
void read(int rankss[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;

//############### COPIER ICI ########################
// total number of voters
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);

        printf("\n");
    }

//############### COPIER ICI ########################


    add_pairs();
    //printf("pair_count : %d\n", pair_count);
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int i = 0;
    while (candidates[i] != NULL)
    {
        //printf("%d\n", candidate_count);
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return 1;
        }
        i++;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int k = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[i][j] > 0)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[k].winner = i;
                    pairs[k].loser = j;
                    k++;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[k].winner = j;
                    pairs[k].loser = i;
                    k++;
                }
            }
        }
    }
    pair_count = k;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int winner, loser;
    int win_i, los_i, win_j, los_j, p_i, p_j;
    if (pair_count > 0)
    {
        for (int i = 0; i < pair_count; i++)
        {
            for (int j = 0; j < pair_count; j++)
            {
                if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[i].winner][pairs[i].loser] && j > i)
                {
                    winner = pairs[i].winner;
                    loser = pairs[i].loser;
                    pairs[i].winner = pairs[j].winner;
                    pairs[i].loser = pairs[j].loser;
                    pairs[j].winner = winner;
                    pairs[j].loser = loser;
                }
            }
        }
    }
    return;
}

bool islocked(int mw) //mw maybe winner
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[mw][i] == 1)
        {
            return 1;
        }
    }
    return 0;
}

// return the locked loser
int iscycle(int source, int win) //is the loser locked as winner
{
    if (win == source)
    {
        return 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[win][i])
        {
            if (iscycle(source, i))
            {
                return 1;
            }
        }
    }
    return 0;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!iscycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            //printf("%s%s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
        }
        //printf("%s%s %d\n", candidates[pairs[i].winner], candidates[pairs[i].loser], locked[pairs[i].winner][pairs[i].loser]);
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int k;
    for (int i = 0; i < candidate_count; i++)
    {
        k = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == 0)
            {
                k++;
                if (k == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
