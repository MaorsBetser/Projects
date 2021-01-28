#include <stdio.h>

int main(void)
{
    char *name = "max";
    printf("%c\n", *name);
    printf("%c\n", &name + 1);
}