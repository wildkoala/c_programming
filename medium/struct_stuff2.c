#include <stdio.h>

// I want to create an instance of animal from user input

#define BUFFER 200

struct animal {
    char name[50];
    int age;
    char sound[50];
    int num_legs;
    int color_blind;
};


struct animal make_animal() {

    struct animal temp;
    char given_name[50];
    int given_age;
    char given_sound[50];
    int given_num_legs;
    int given_color_blind;

    fgets(given_name, BUFFER, stdin);
    fgets(given_age, BUFFER, stdin);
    fgets(given_sound, BUFFER, stdin);
    fgets(given_num_legs, BUFFER, stdin);
    fgets(given_color_blind, BUFFER, stdin);
    
    temp.name = given_name;
    temp.age = given_age;
    temp.sound = given_sound;
    temp.num_legs = given_num_legs;
    temp.color_blind = given_color_blind;
    return temp;
}


int main(){
    struct animal dog = {"Dog", 2, "BORKBORK", 4, 1};
    struct animal user_animal;

    printf("Here's an animal's name: %s\n", dog.name);
    printf("Here's an animal's age: %d\n", dog.age);
    printf("Here's an animal's sound: %s\n", dog.sound);
    printf("Here's an animal's number of legs: %d\n", dog.num_legs);
    printf("Here's an animal's color blindness: %d\n", dog.color_blind);



    user_animal = make_animal();
    printf("Here's your animal's name: %s\n", user_animal.name);
    printf("Here's your animal's age: %d\n", user_animal.age);
    printf("Here's your animal's sound: %s\n", user_animal.sound);
    printf("Here's your animal's number of legs: %d\n", user_animal.num_legs);
    printf("Here's your animal's color blindness: %d\n", user_animal.color_blind);
}
