#include <stdio.h>
#include <stdlib.h>


// Driver code
int main()
{
  char *str = "w12345abc";
  char *endptr;
  long int num;

  num = strtol(str, &endptr, 10);
  if (endptr == str) {
    printf("No digits were found.\n");
  } else if (*endptr != '\0') {
    printf("Invalid character: %c\n", *endptr);
    printf("The number is: %ld\n", num);
  } else {
    printf("The number is: %ld\n", num);
  }
  return 0;
}
