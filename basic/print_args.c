#include <stdio.h>

int main (int argc, char *argv[]) {
    int counter;
    for (counter=0;counter < argc; counter++) {
        printf("Here's the number of arguments: %d\nHere's the arg given: %s\n", argc, argv[counter]);
    }
    return 0;
}
