

#include <stdio.h>
#include <string.h>
#include <time.h>
#define EMPTY 0
#define QUEEN 1

int queen[100][100];
int n, total_solutions;

// simple display algorithm
void display()
{
    int i, j;

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            printf("%c ", queen[i][j] ? 'Q' : '-');
        }
        printf("\n");
    }
    printf("\n");
}


// check iterates through the board and checks 
// for clashes with already placed queens
// return 0 if no conflicts, 1 otherwise
int check(int row, int column)
{
    int i, j;

    //check the column positions above this position
    for(i = 1; i < row; i++)
    {
        if(queen[i][column] == QUEEN)
            return 1;
    }

    //check upper left diagonal
    for(i = row - 1, j = column - 1; i > 0 && j > 0; i--, j--)
    {
        if(queen[i][j] == QUEEN)
            return 1;
    }

    //check upper right diagonal
    for(i = row - 1, j = column + 1; i > 0 && j <= n; i--, j++)
    {
        if(queen[i][j] == QUEEN)
            return 1;
    }

    return 0;
}

// backtrack is a recursive function
// we first check if the number of rows has been met
// if so, we display the board
// then we iterate row by row
void backtrack(int queen_row)
{
    int i;

    //check if rows have been met
    //print solution
    if(queen_row > n)
    {
        total_solutions++;
        printf("solution number %d :\n", total_solutions);
        display();
        return;
    }

    // iterate row by row, recursively
    // solve using depth first
    for(i = 1; i <= n; i++)
    {
        if(!check(queen_row, i))
        {
            queen[queen_row][i] = QUEEN;

            backtrack(queen_row + 1);

            queen[queen_row][i] = EMPTY;
        }
    }
}

int main()
{
    
    // timer implementation
    clock_t start_t, end_t;

    double cpu_time_used;

    // intro statements
    printf("N-Queens Problem Solver\n\n");

    printf("This program will calculate all solutions up to 100x100 size boards.\n");
    printf("WARNING: This program will run for several minutes to several hours on larger sized N (15x15+) boards!\n\n");

    printf("Enter Board size: ");
    scanf("%d", &n);

    // set memory
    memset(queen, EMPTY, sizeof(queen));

    // start the clock
    start_t = clock();

    // call backtrack to start the recursive search
    backtrack(1);
    
    end_t = clock();

    // print the total number of solutions
    printf("Total Solutions: %d\n", total_solutions);

    cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
    printf("\nTotal time taken by CPU: %f\n", cpu_time_used  );
 
    // exit
    printf("\nExiting of the program...\n");
    return 0;

}
