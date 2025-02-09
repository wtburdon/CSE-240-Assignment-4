#include <stdio.h>
#define NUM_ROWS 5
#define NUM_COLS 5

typedef enum {F = 0, T = 1} Bool;

int GetInitialState(int init_state[])
{

}

void SetInitialState(char board[][NUM_COLS], int init_state[], int num_alive)
{

}

int CountLiveNeighbors(char board[][NUM_COLS], int row, int col)
{

}

void NextGeneration(char board[][NUM_COLS])
{

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
    //printf("test");

    //char board[NUM_ROWS][NUM_COLS];
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