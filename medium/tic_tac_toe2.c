// this version accepts user input


#include <stdio.h>


int check_win(char board[]) { // is this the proper way to pass a string
    if (board[0] == board[1] == board[2] && board[0] != ' ') {
        return 1;
    }
    if (board[3] == board[4] == board[5] && board[3] != ' ') {
        return 1;
    }
    if (board[6] == board[7] == board[8] && board[6] != ' ') {
        return 1;
    }
    if (board[0] == board[3] == board[6] && board[0] != ' ') {
        return 1;
    }
    if (board[1] == board[4] == board[7] && board[1] != ' ') {
        return 1;
    }
    if (board[2] == board[5] == board[8] && board[2] != ' ') {
        return 1;
    }
    if (board[0] == board[4] == board[8] && board[0] != ' ') {
        return 1;
    }
    if (board[2] == board[4] == board[6]) {
        return 1;
    }
    return 0;
}

void init_board() {
    printf("Welcome to tic-tac-toe!!\n");
    printf("       |       |       \n");
    printf("   1   |   2   |   3   \n");
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   4   |   5   |   6   \n");
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   7   |   8   |   9   \n");
    printf("       |       |       \n");
    printf("It's X's turn!\n");
}

void update_board(char player, char *board) {

    int location; 
    if (player == 'X'){
        printf("Enter the place you want to go: ");
        scanf("%d", &location);
        printf("You entered: %d\n", location);
    }
    if (player == 'Y'){
        printf("Enter the place you want to go: ");
        scanf("%d", &location);
        printf("You entered: %d\n", location);
    }

    printf("This is my location var: %d\n", location);
    printf("This is my board var, it's a pointer: %p\n", board);
    printf("This is the selected location??: \"%c\"\n", board[location-1]);
    board[location-1] = player;
    printf("Updated character: \"%c\"\n", board[location-1]);

    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c   \n", board[0], board[1], board[2]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c   \n", board[3], board[4], board[5]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c   \n", board[6], board[7], board[8]);
    printf("       |       |       \n");
}

int main() {

    // create an initial board
    int move_number;
    char player;
    char board[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};

    // draw the initial board
    init_board();
    while(1){ //idk if i need this semi-colon in the while condition. Could just stick to 1
        player = 'X';
        update_board(player,board);
        if (check_win(board)){
            printf("Player X won!");
            return 0;
        }
        player = 'Y';
        update_board(player,board);
        if (check_win(board)) {
            printf("Player Y won!");
            return 0;
        }
    }
    return 0;
}
