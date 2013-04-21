#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));

    // Between 10 and 1
    iSecret = rand() % 10 + 1;
    return 0;
}
