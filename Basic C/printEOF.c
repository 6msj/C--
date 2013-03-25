#include <stdio.h>

int main() {
    printf("getchar: %d\n", (getchar() != EOF));
    printf("EOF: %d", EOF);
    return 0;
}
