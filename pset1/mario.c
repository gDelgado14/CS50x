#include <stdio.h>
#include <cs50.h>

int main (void)

{

int n;
int space;
int hash;

    do
    {
      printf("Height: ");
      n = GetInt();             //number of rows
    }while (n<0 || n>23);
    
        
    space=n-1;                  //number of spaces in first row
    hash=2;                     //number of hashes in first row
    
    //loop runs for the amount of rows
    for (int mainloop = n; mainloop>0;mainloop--)
    {
        //adds required number of spaces for current row
        for (int spaceloop=space;spaceloop>0;spaceloop--)
        {
            printf(" ");
        }
        space=space-1;
        
        //adds required number of #'s for current row
        for (int hashloop=hash;hashloop>0;hashloop--)
        {
            printf("#");
        }
        hash=hash+1;
        
        printf("\n");
    }
}
