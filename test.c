#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory for an integer on the heap
    int *ptr = (int *)malloc(sizeof(int));

    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Assign a value to the allocated memory
    *ptr = 42;

    // Free the allocated memory
    free(ptr);

    // Attempt to access the freed memory
    int value = *ptr; // This will trigger a heap-use-after-free error

    // The program should not reach this point
    printf("Value: %d\n", value);

    return 0;
}
