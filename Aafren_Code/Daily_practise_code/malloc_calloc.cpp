/**
malloc() allocates uninitialized memory. calloc() allocates memory and initializes all bytes to zero.
**/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 5;

    int *first = malloc(size * sizeof(int));
    int *second = calloc(size, sizeof(int));

    if (first == NULL || second == NULL) {
        printf("Memory allocation failed\n");
        free(first);
        free(second);
        return 1;
    }

    printf("calloc values: ");

    for (int i = 0; i < size; i++) {
        printf("%d ", second[i]);
    }

    free(first);
    free(second);

    first = NULL;
    second = NULL;

    return 0;
}
