#include <stdio.h>
int my_int_array[10];
char my_ltr;

int main() {
    scanf("Give me 10, space seperated integers:\n", &my_int_array);
    scanf("Give me a letter:\n", &my_ltr);
    printf("Here's the array: %d\n", &my_int_array);
    printf("Here's my letter: %c\n");
    return 0;
}
