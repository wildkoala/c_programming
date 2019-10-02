#include <stdio.h>

struct animal {
    char name[50];
    int age;
    char sound[50];
    int num_legs;
    int color_blind;
};

/* make_animal:  make an animal from its features
struct animal make_animal(int age, char sound[], int num_legs, int color_blind){
    struct animal a;
    a.name = name;
    a.age = age;
    a.sound = sound;
    a.num_legs = num_legs;
    a.color_blind = color_blind;
	return a;
}
*/

int main(){
    struct animal dog = {"Dog", 2, "BORKBORK", 4, 1};
    printf("Here's your animal's name: %s\n", dog.name);
    printf("Here's your animal's age: %d\n", dog.age);
    printf("Here's your animal's sound: %s\n", dog.sound);
    printf("Here's your animal's number of legs: %d\n", dog.num_legs);
    printf("Here's your animal's color blindness: %d\n", dog.color_blind);
}
