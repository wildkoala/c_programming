#include <stdio.h>
#include <stdlib.h>

#define BUFFER 250

/*
win function is broken fixed, needed to make a blank version of the board with spaces
*/


// Define structs
typedef struct board_tag{
    char marks[9];
} Board;


// Declare functions
void print_board(Board *a_board);
void print_instructions();
int check_win(Board *a_board);
void update_board(Board *a_board, char p_token, int selected_box);
Board *make_board();

// Call main
int main(){

    // define some preconditions
    int win = 0;
    int turn_counter = 0;
    char player_token = 'X';
    Board *game_board = make_board();

    // print the instructions
    print_instructions();

    // start the game loop
    while (!win && turn_counter <= 8){
        char *player_input = calloc(1, sizeof(char));
        int selected_box;

        // this is going to come in as a string, but i need an int.
        printf("Mark a space >");
        fgets(player_input, BUFFER, stdin); 
        selected_box = atoi(player_input);

        // Update the board
        update_board(game_board, player_token, selected_box);

        // Draw the board
        print_board(game_board);

        // Check for win
        win = check_win(game_board);
        if (win){
            break;
        }
        // flip the player token
        if (player_token == 'X'){
            player_token = 'Y';
        }
        else if (player_token == 'Y'){
            player_token = 'X';
        }
        turn_counter++;
    }

    // Print winner
    printf("%c wins!\n", player_token);
    return 0;
}

void print_instructions(){
    const char *board_format = "Welcome to Tic-Tac-Toe!\n"
"Press the number of the corresponding box to place your symbol.\n"
"Get 3 in a row in any direction to win!\n"
"#############\n"
"#   #   #   #\n"
"# 1 # 2 # 3 #\n"
"#   #   #   #\n"
"#############\n"
"#   #   #   #\n"
"# 4 # 5 # 6 #\n"
"#   #   #   #\n"
"#############\n"
"#   #   #   #\n"
"# 7 # 8 # 9 #\n"
"#   #   #   #\n"
"#############\n";
    printf("%s", board_format);
}

void print_board(Board *a_board){
    const char *board_format = "\n"
"#############\n"
"#   #   #   #\n"
"# %c # %c # %c #\n"
"#   #   #   #\n"
"#############\n"
"#   #   #   #\n"
"# %c # %c # %c #\n"
"#   #   #   #\n"
"#############\n"
"#   #   #   #\n"
"# %c # %c # %c #\n"
"#   #   #   #\n"
"#############\n";

    // the method below turns out to not work so great. Need char literals.
    // If you want to use %c, you must use single quotes.
    char *given_board = calloc(1, sizeof(Board));
    int i;
    for(i=0; i<9; i++){
        if(a_board->marks[i] == 'X'){
            given_board[i] = 'X';
        }
        else if(a_board->marks[i] == 'Y'){
            given_board[i] = 'Y';
        }
        else{
            given_board[i] = ' ';
        }
    }

    printf(board_format, given_board[0],\
                         given_board[1],\
                         given_board[2],\
                         given_board[3],\
                         given_board[4],\
                         given_board[5],\
                         given_board[6],\
                         given_board[7],\
                         given_board[8]);
}


int check_win(Board *a_board){
    // Check for horizontal win
    if (\
    (a_board->marks[0] == a_board->marks[1] && a_board->marks[1]== a_board->marks[2]) &&\
    a_board->marks[0] != ' '\
    ){
        return 1;
    }
    if (\
    (a_board->marks[3] == a_board->marks[4] && a_board->marks[4]== a_board->marks[5]) &&\
    a_board->marks[3] != ' '\
    ){
	    return 1;
    }
    if (\
    (a_board->marks[6] == a_board->marks[7] && a_board->marks[7]== a_board->marks[8]) &&\
    a_board->marks[8] != ' '\
    ){
        return 1;
    }

    // Check for vertical win
    if (\
    (a_board->marks[0] == a_board->marks[3] && a_board->marks[3]== a_board->marks[6]) &&\
    a_board->marks[3] != ' '\
    ){
        return 1;
                }
    if (\
    (a_board->marks[1] == a_board->marks[4] && a_board->marks[4]== a_board->marks[7]) &&\
    a_board->marks[1] != ' '\
    ){
        return 1;
    }
    if (\
    (a_board->marks[2] == a_board->marks[5] && a_board->marks[5]== a_board->marks[8]) &&\
    a_board->marks[5] != ' '\
    ){
        return 1;
    }

    // Check for diagonal win
    if (\
    (a_board->marks[0] == a_board->marks[4] && a_board->marks[4]== a_board->marks[8]) &&\
    a_board->marks[0] != ' '\
    ){
        return 1;
    }
    if (\
    (a_board->marks[2] == a_board->marks[4] && a_board->marks[4]== a_board->marks[6]) &&\
    a_board->marks[6] != ' '\
    ){
        return 1;
    }
    return 0;
}

void update_board(Board *a_board, char p_token, int selected_box){
    // a_board->marks[box] = token is equivalent.
    if (a_board->marks[selected_box-1] == 'X' || a_board->marks[selected_box-1] == 'Y'){
        printf("Invalid choice, you've lost your turn! :(");
    }
    else {
        a_board->marks[selected_box-1] = p_token;
    }
}

// new function
Board *make_board(){
    Board *new_board = calloc(1, sizeof(Board));
    snprintf(new_board->marks, 9,"         "); // used a "" for a string
    return new_board;
}
