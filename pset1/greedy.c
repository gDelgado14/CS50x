#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

float change;
int cents;
int coins;
int quarters=0;
int dimes=0;
int nickels=0;
int pennies=0;

    do
    {
        printf("Change owed: $");
        change = GetFloat();
        if (change <= 0)
            printf("Please enter valid amount!\n");
    }while (change <= 0);
    
    //printf("%.2f\n", change);
    
    cents = round(change * 100);
    
    //printf("%.2f dollars = %d cents",change,cents);
    
    do
    {
    
    if (cents >= 25)
    {
        cents = cents - 25;
        quarters = quarters + 1;
    }
    
    else if (cents >= 10)
    {
        cents = cents - 10;
        dimes = dimes + 1;
    }
    
    else if (cents >= 5)
    {
        cents = cents - 5;
        nickels = nickels + 1;
    }
    
    else if (cents >=1)
    {
        cents = cents - 1;
        pennies = pennies + 1;
    }
    
    }while (cents >0);
    
    coins = pennies + nickels + dimes + quarters;
    
    printf("%d\n",coins);
    
}
