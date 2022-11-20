#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //asking the user for how tall will be the pyramid
    int n;
    do
    {
        n = get_int("How tall will be the pyramid?: ");
    }
    while (n < 1 || n > 8); // loop will run until the user gives input between 1 to 8 (includin 1 and 8 )

    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1 ; j > i; j--) //first printing a blank inverted triangle
        {
            printf(" ");

        }

        for (int j = 0; j <= i; j++) // now printing the first triangle
        {
            printf("#");
        }

        for (int j = 0; j < 2; j++) // printing a rectangular space
        {
            printf(" ");
        }

        for (int j = 0; j <= i; j++) // now printing 2nd tringle
        {
            printf("#");
        }

        printf("\n");

    }

}