#include <stdio.h>
#include <stdlib.h>

#define BUFFER 250

/*
For now, lets just have two rooms, when you search the second room
you'll get a key, and when you get the key, you can interact with the
door to escape


Room layout, numbered.
--------------------------------
     0        |        1
--------------------------------
     2        |        3
--------------------------------
*/


// STRUCT DEFINITIONS
typedef struct player_tag{
    int has_key;
    int current_room;
} Player;

Player *make_player(){
    Player *new_p = calloc(1,sizeof(Player));
    new_p->has_key = 0; // I think I can write to this without snprintf bc int
    new_p->current_room = 0;
    return new_p; // should I return a player like this, or a pointer to a player?
}

// FUNCTION DECLARATIONS
void intro();
int first_room(); // return the room number they want to go to.
int test_input();
void show_room(Player *p); // describe the room and the possible options
void show_room_0(Player *p);
void show_room_1(Player *p);
// void show_room_2(Player *p);


// MAIN FUNCTION
int main () {
    intro();
    int escaped = 0;
    Player *p1 = make_player();
    p1->current_room = first_room();


    while(!escaped){
        // Determine which room we're in
        // Give description of room
        show_room(p1);
        // Give options
        // Select option
        // Update room
        // Update player
        // Move if applicable
        // Check if escaped
        // break;
    }
    if (escaped){
        printf("\nCONGRATS - YOU ESCAPED\n");
    }
    return 0;
}


// FUNCTIONS
void intro() {
    const char *print_format = "\n\
Find the key and escape the house...\n\n";
    printf(print_format);
}


// Handle everything in the first room.
int first_room(){
    char user_input_char[1];
    int user_data;
    char second_char[1];
    int second_int;

    const char *print_format = "\
You find yourself in a room you don't recognize.\n\
What do you do?\n\n\
1. Look around\n\
2. Yell for help\n> ";

    printf(print_format);


    fgets(user_input_char, BUFFER, stdin);
    user_data = atoi(user_input_char);

    printf("Selected: %d\n", user_data);

    if (user_data == 1) {
        printf("You see a set of solid oak double doors... it looks like it leads out!! But the doors are locked...\n");
        printf("There's a second door to your right. Would you like to open it?\n1. Yes\n2. No\n> ");
        fgets(second_char, BUFFER, stdin);
        second_int = atoi(second_char);

        if (second_int == 1){
            return 1;
        }
        else{
            printf("Don't be lame man. You'll break the game\n");
            return 0;
        }
    }

    else if (user_data == 2) {
        printf("Why did you think that would be helpful?\n");
        return 0;
    }
}




// Display what is in a room, and what the options are.
void show_room(Player *p){

    char user_input_char[5];
    char second_input[5];

    // This is what's run if in the main room (first room)
    if (p->current_room == 0){
        show_room_0(p);
    }

    else if (p->current_room == 1){
        show_room_1(p);
    }
}

void show_room_0(Player *p){
    char user_input_char[5];
    char second_input[5];

    const char *room_format = "\n\
You see a set of solid oak double doors... it looks like it leads out!! But the doors are locked...\n\
There\'s a door to the north.\n\
What would you like to do?\n\");


    printf(room_format);

    // If they want to look around
    fgets(user_input_char, BUFFER, stdin);
/*
    if (atoi(user_input_char) == 1){
        printf("There's a shimmer beneath a rickety chair... It's a key! Would you like to grab it?\n1. Yes\n2. No\n> ");
        fgets(second_input, BUFFER, stdin);
        if (atoi(second_input)){
            printf("You place the key in your pocket\n");
            p->has_key = 1;
        }
        else{
            printf("You leave it there. For some reason. I mean, you do you- but... you're clearly supposed to take it.");
        }
    }

    // If they want to tap on the wall
    else if (atoi(user_input_char) == 2){
        printf("You quietly but firmly rap your knuckles against the wall... but nothing happens.");
    }

    // If they want to go back to the main room
    else if (atoi(user_input_char) == 3){
        printf("You walk back to the main room");
        p->current_room = 0;
    }
*/
}



void show_room_1(Player *p){
    char user_input_char[5];
    char second_input[5];

    const char *room_format = "\
A cool breeze sweeps across your face, and light pours in from behind you.\n\
What do you do?\n\n\
1. Look around\n\
2. Tap on the wall\n\
3. Go back to the main room\n> ";

    printf(room_format);

    // If they want to look around
    fgets(user_input_char, BUFFER, stdin);
    if (atoi(user_input_char) == 1){
        printf("There's a shimmer beneath a rickety chair... It's a key! Would you like to grab it?\n1. Yes\n2. No\n> ");
        fgets(second_input, BUFFER, stdin);
        if (atoi(second_input)){
            printf("You place the key in your pocket\n");
            p->has_key = 1;
        }
        else{
            printf("You leave it there. For some reason. I mean, you do you- but... you're clearly supposed to take it.");
        }
    }

    // If they want to tap on the wall
    else if (atoi(user_input_char) == 2){
        printf("You quietly but firmly rap your knuckles against the wall... but nothing happens.");
    }

    // If they want to go back to the main room
    else if (atoi(user_input_char) == 3){
        printf("You walk back to the main room");
        p->current_room = 0;
    }
}
