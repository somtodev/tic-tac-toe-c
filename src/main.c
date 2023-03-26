#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    char winner = ' ';
    bool no_free_space = checkFreeSpaces() != 0;

    resetBoard();

    while (winner == ' ' && checkFreeSpaces() != 0)
    {
        printBoard();

        playerMove();
        winner = checkWinner();

        if (winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }

        computerMove();
        winner = checkWinner();

        if (winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
    }

    printBoard();
    printWinner(winner);

    return 0;
}

void resetBoard()
{
    for (int outer = 0; outer < 3; outer++)
    {
        for (int inner = 0; inner < 3; inner++)
        {
            board[outer][inner] = ' ';
        }
    }
}

void printBoard()
{
    for (int row = 0; row < 3; row++)
    {
        printf(" %c | %c | %c", board[row][0], board[row][1], board[row][2]);
        if (row != 2)
            printf("\n---|---|---\n");
    }
    printf("\n");
}

int checkFreeSpaces()
{
    int free_spaces = 9;

    for (int outer = 0; outer < 3; outer++)
    {
        for (int inner = 0; inner < 3; inner++)
        {
            if (board[outer][inner] != ' ')
            {
                free_spaces--;
            }
        }
    }

    return free_spaces;
}

void playerMove()
{
    int row;
    int col;

    do
    {
        printf("Enter Row(1-3): ");
        scanf("%d", &row);
        row--;

        printf("Enter Col(1-3): ");
        scanf("%d", &col);
        col--;

        if (board[row][col] != ' ')
        {
            printf("Invalid Move :(\n");
        }
        else
        {
            board[row][col] = PLAYER;
            break;
        }

    } while (board[row][col] != ' ');
}

void computerMove()
{
    // Creates a seed based on current time
    srand(time(0));
    int row, col;

    if (checkFreeSpaces() > 0)
    {
        do
        {
            row = rand() % 3;
            col = rand() % 3;
        } while (board[row][col] != ' ');

        board[row][col] = COMPUTER;
    }
    else
        printWinner(' ');
}

char checkWinner()
{
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][0] == board[row][2])
        {
            return board[row][0];
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] == board[1][col] && board[0][col] == board[2][col])
        {
            return board[0][col];
        }
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }

    if (board[0][2] == board[1][1] && board[0][0] == board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}

void printWinner(char winner)
{
    if (winner == PLAYER)
    {
        printf("YOU WIN!");
    }
    else if (winner == COMPUTER)
    {
        printf("YOU LOSE!");
    }
    else
    {
        printf("DRAW");
    }

    printf("\n");
}