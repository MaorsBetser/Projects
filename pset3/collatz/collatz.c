#include <stdio.h>
#include <cs50.h>

int collatz();

int main (void)
{
    int n = get_int("Number To Collatz:");
    printf("%i\n", collatz(n));
}
int collatz(n)
{
    if(n == 1)
    
        return 0;
    
    else if(n % 2 == 0)
    
        return 1 + collatz(n / 2);
    
    else
    
        return 1 + collatz(3 * n + 1);

}