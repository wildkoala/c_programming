#include <stdio.h>
#include <stdbool.h> 


int check_win(int board[]) {
    if (board[0] == board[1] == board[2] && board[0] != 0) {
        return 1;
    }
    if (board[3] == board[4] == board[5] && board[3] != 0) {
        return 1;
    }
    if (board[6] == board[7] == board[8] && board[6] != 0) {
        return 1;
    }
    if (board[0] == board[3] == board[6] && board[0] != 0) {
        return 1;
    }
    if (board[1] == board[4] == board[7] && board[1] != 0) {
        return 1;
    }
    if (board[2] == board[5] == board[8] && board[2] != 0) {
        return 1;
    }
    if (board[0] == board[4] == board[8]) {
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

int * update_board(char player, int *board) { //this function is broken somehow

    int location = 5; // just gonna hard code this for a minute 
    if (player == 'X'){
        printf("I'm player X\n");
    }
    if (player == 'Y'){
        printf("I'm player Y\n");
    }

    printf("This is my location var: %d\n", location);
    printf("This is my board var, i think it's a pointer: %p\n", board);

    printf("       |       |       \n");
    printf("   %d   |   %d   |   %d   \n", board[0], board[1], board[2]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %d   |   %d   |   %d   \n", board[3], board[4], board[5]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %d   |   %d   |   %d   \n", board[6], board[7], board[8]);
    printf("       |       |       \n");
    return board;
}

int main() {

    // create an initial board
    int move_number;
    char player;
    int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

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
        break;
    }
    return 0;
}
