/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 * 
 * Goal of the game is to get tiles in ascending order i.e. 1,2,3,4,5
 * Tiles start out in descending order. 
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// empty tile row and column numbers
int etile_r;
int etile_c;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int max_num = d*d - 1;
    int count = 0;
    
    // populate 2D array with values in descending order
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            board[row][col] = max_num - count; 
            count++;
        }
    }
    
    // set empty tile location
    etile_r = d-1;
    etile_c = d-1;
    
    // swap last two values if the dimensions are even
    if (d%2 == 0)
    {
        int temp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (row == etile_r && col == etile_c)
            {
                // display empty tile to screen
                printf("  _");
            }
            else
            {
                // display tile value to screen
                printf("%3d", board[row][col]);
            }
        }
        // new line for new row
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // user tiles row and column numbers
    int u_row;
    int u_col;
    
    // check if tile is in correct range
    if (tile > d*d-1 || tile < 1)
    {
        return false;
    }
    
    // search for user tile
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (board[row][col] == tile)
            {
                u_row = row;
                u_col = col;
                break;
            }
        }
    }
    
    // check if user tile can move into empty tile location
    if (u_row == etile_r || u_col == etile_c)
    {
        if (u_col == etile_c - 1 || u_col == etile_c + 1 || 
            u_row == etile_r + 1 || u_row == etile_r - 1)
        { 
            // make move 
            board[etile_r][etile_c] = board[u_row][u_col];
            board[u_row][u_col] = 0;
            // set new empty tile values
            etile_r = u_row;
            etile_c = u_col;
            return true;
        }
    }
    
    // cannot move 
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // check if last tile is the empty tile
    if (board[d-1][d-1] != 0)
    {
        return false;
    }
    
    int count = 1;
    // check to see if every tile is in correct position
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            // game not over condition
            if (board[row][col] != count && col != d-1 && row != d-1)
            {
                return false;
            }
            count++;
        }
    }
    
    // game is won
    return true;
}