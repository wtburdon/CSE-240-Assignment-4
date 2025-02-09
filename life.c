#include <stdio.h>
#include <string.h>
#define NUM_ROWS 5
#define NUM_COLS 5

typedef enum {F = 0, T = 1} Bool;

int tokenToInteger(char token[])
{
    int multiplier = 1;
    int res = 0;

    for(int i = strlen(token) - 1; i >= 0; i--)
    {
        res += ((token[i] - '0') * multiplier);

        multiplier*=10;
    }

    return res;
}

int GetInitialState(int init_state[])
{
    //ask numbers, return array
    int num_alive = 0;
    char initStateInput[50]; //5*5 = 25 possible inputs, sesperated by 24 commas

    printf("Enter the offsets for the live cells: \n");
    scanf(" %s", initStateInput);

    char* token = strtok(initStateInput, " ,");

    while(token != NULL)
    {   
        // printf("Token: %s\n", token);
        int index = tokenToInteger(token);

        // printf("Converted Index: %d\n", index);

        if(index >= 0 && index < 25)
        {   
            num_alive++;
            init_state[index] = 1;
        }

        token = strtok(NULL, " ,");
    }

    return num_alive;
}

void SetInitialState(char board[][NUM_COLS], int init_state[], int num_alive)
{
    // take array of numbers, convert to indexes, set indexs to char '*'

    for(int i = 0; i < NUM_ROWS * NUM_COLS; i++)
    {
        if(init_state[i])
        {
            int row = i / NUM_ROWS;
            int col = i % NUM_COLS;

            board[row][col] = '*';
        }
    }
}

int CountLiveNeighbors(char board[][NUM_COLS], int row, int col)
{
    /*
    center: [1,1] row, col
    [row-1, col-1][row-1, col][row-1, col+1]
    [row, col-1]  [row, col]  [row, col+1]
    [row+1, col-1][row+1, col][row+1, col+1]

    ---
    -*-
    ---
    
    */

    int neighbors = 0;

    for(int r = -1; r < 2; r++)
    {

        for(int c = -1; c < 2; c++)
        {
            if(r == 0 && c == 0)
            {
                continue;
            }
            else if(row+r < 0 || row+r > NUM_ROWS-1)
            {
                continue;
            }
            else if(col+c < 0 || col+c > NUM_COLS-1)
            {
                continue;
            }


            if(board[row+r][col+c] == '*')
            {
                neighbors++;
            }

        }

    }

    return neighbors;
}

void NextGeneration(char board[][NUM_COLS])
{
    //copy of board
    char prev_board[NUM_ROWS][NUM_COLS];

    memcpy(prev_board, board, sizeof(prev_board));

    for(int row = 0; row < NUM_ROWS; row++)
    {

        for(int col = 0; col < NUM_COLS; col++)
        {

            int neighbors = CountLiveNeighbors(prev_board, row, col);
            
            if(prev_board[row][col] == '*' && (neighbors < 2 || neighbors > 3))
            {
                board[row][col] = '-';
            }
            else if(prev_board[row][col] == '-' && neighbors == 3)
            {
                board[row][col] = '*';
            }

        }

    }
}

void PrintBoard(char board[][NUM_COLS])
{
    for(int row = 0; row < NUM_ROWS; row++)
    {
        for(int col = 0; col < NUM_COLS; col++)
        {
            printf("%c", board[row][col]);
        }

        printf("\n");
    }

}

void PlayGameOfLife()
{
    char board[NUM_ROWS][NUM_COLS] = {{'-', '-', '-', '-', '-'}, {'-', '-', '-', '-', '-'}, {'-', '-', '-', '-', '-'}, {'-', '-', '-', '-', '-'}, {'-', '-', '-', '-', '-'}};
    int init[NUM_ROWS * NUM_COLS] = {0};

    int num_alive = GetInitialState(init);

    SetInitialState(board, init, num_alive);

    int generation = 0;

    while(generation < 7)
    {   
        printf("\ngeneration = %d\n\n", generation);
        PrintBoard(board);

        NextGeneration(board);

        generation++;
    }

    printf("Good life!\n");

}

int main()
{
    char userInput;
    
    printf("Welcome! Press 'q' to quit or any other key to continue: ");
    scanf(" %c", &userInput);
    printf("\n");

    while(userInput != 'q')
    {
        PlayGameOfLife();

        printf("Press 'q' to quit or any other key to continue: ");
        scanf(" %c", &userInput);
        printf("\n");
    }

    printf("Bye bye!");

    return 0;
}