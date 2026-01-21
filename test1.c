// C program to write to a
// binary file
#include <stdio.h>
#include <stdlib.h>

// Struct declared
struct Num {
    int n1, n2;
};

// Driver code
int main()
{
    // variables declared
    int n;
    struct Num obj;

    // File Pointers declared
    FILE* fptr;

    // Failure Condition
    if ((fptr = fopen("temp.bin", "wb")) == NULL) {
        printf("Error! opening file");

        // if file pointer returns NULL program
        // will exit
        exit(1);
    }


    for (n = 1; n < 10; n++) {
        obj.n1 = n;
        obj.n2 = 12 + n;

        // Data written
        fwrite(&obj, sizeof(struct Num), 1, fptr);
    }

    // File closed
    fclose(fptr);

    printf("Data in written in Binary File\n\n");

    return 0;
}