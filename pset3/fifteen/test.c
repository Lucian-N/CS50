#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
   
int main()
{
   int d = get_int();
    int board[d][d], vmax =(d*d)-1 ;
    for (int i =0; i<d; i++)
    {
        for (int j=0; j<d; j++)
        {
          board[i][j] = vmax;
          vmax--;
        }
    }
    if (d%2 == 0)
    {
        int temp =0;
        temp = board[d-1][d-2];
        board[d-1][d-2] =board[d-1][d-3];   
        board[d-1][d-3] = temp;
    }
    
    for (int i =0; i<d; i++)
    {
        for (int j=0; j<d; j++)
        {
        if (board[i][j]!=0)
            {
            printf("\t %2i", board[i][j]);    
            }
        else printf("  ");
        }
          printf("\n");
    }
}