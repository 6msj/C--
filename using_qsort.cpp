#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int compare(const void *i, const void *j);

int main() {
    int arr[10] = {1, 13, 14, 2, 23, 2, 8, 9, 20, 211};
    qsort(arr, 10, sizeof(int), compare);

    for (int i = 0; i < 10; ++i) {
        printf ("%d\n", arr[i]);
    }

    return 0;
}


int compare(const void *i, const void *j) {
    if (*(int*)i > *(int*)j) {
        return 1;
    } else if (*(int*)i < *(int*)j) {
        return -1;
    } else {
        return 0;
    }
}
