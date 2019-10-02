#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// I want to create an instance of animal from user input

#define BUFFER 200

typedef struct animal_tag {
    char name[BUFFER];
    int age;
    char sound[BUFFER];
    int num_legs;
    int color_blind;
} Animal;


Animal *create_animal() {
	
    Animal *temp = calloc(1,sizeof(Animal));

    snprintf(temp->name,BUFFER,"default");
    temp->age = 0;
    snprintf(temp->sound,BUFFER,"no sound");
    temp->num_legs = 4;
    temp->color_blind = 0;

    return temp;
}

void prompt_animal(Animal *a){

    printf("Edit animal (%s) : \n", a->name);
    char given_name[BUFFER];
    char given_age[BUFFER];
    char given_sound[BUFFER];
    char given_num_legs[BUFFER];
    char given_color_blind[BUFFER];

    printf("Name? > ");
    fgets(given_name, BUFFER, stdin);
    printf("Age? > ");
    fgets(given_age, BUFFER, stdin);
    printf("Sound? > ");
    fgets(given_sound, BUFFER, stdin);
    printf("Number of legs? > ");
    fgets(given_num_legs, BUFFER, stdin);
    printf("Is color blind? > ");
    fgets(given_color_blind, BUFFER, stdin);
    
    strncpy(a->name,given_name,BUFFER);
    a->age = atoi(given_age);
    strncpy(a->sound,given_sound,BUFFER);
    a->num_legs = atoi(given_num_legs);
    a->color_blind = atoi(given_color_blind);
}

void print_animal(Animal *a){
	
	const char *format = \
"\
Animal: \n\
Name:\t\t%s\n\
Age:\t\t%d\n\
Sound:\t\t%s\n\
Legs:\t\t%d\n\
CB?:\t\t%d\n\n\
";

	printf(format,a->name,a->age,a->sound,a->num_legs,a->color_blind);

}

int main(){
    Animal dog = {"Dog", 2, "BORKBORK", 4, 1};
    Animal *user_animal;

    print_animal(&dog);
    prompt_animal(&dog);
    printf("Here is the new dog:\n");
    print_animal(&dog);

    user_animal = create_animal();

    prompt_animal(user_animal);
    print_animal(user_animal);
    

}
