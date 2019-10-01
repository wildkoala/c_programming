#include<stdio.h>
#include<stdlib.h>

#define BUFFER 250

typedef struct board_tag{
	int spaces[9];
} Board;

void print_board(Board *b);
void print_instructions();

int main(){

	print_instructions();

	Board *board = calloc(1,sizeof(Board));
	print_board(board);

	char *user_input = calloc(BUFFER,sizeof(char));
	int player=0;
	int space = 0;
	while(1){
		printf("Where? > ");
		fgets(user_input,BUFFER,stdin);
		space = atoi(user_input) -1;
		if(player==0 && board->spaces[space] == 0){
			board->spaces[space] = 1;
		}
		else if(player==1 && board->spaces[space] == 0){
			board->spaces[space] = 2;
		}
		if (player == 0 ) player=1;
		else player = 0;
		print_board(board);
	}

	return 0;

}

void print_instructions(){
	const char *board_format = "Board Layout:\n\
#############\n\
#   #   #   #\n\
# 1 # 2 # 3 #\n\
#   #   #   #\n\
#############\n\
#   #   #   #\n\
# 4 # 5 # 6 #\n\
#   #   #   #\n\
#############\n\
#   #   #   #\n\
# 7 # 8 # 9 #\n\
#   #   #   #\n\
#############\n";

		printf(board_format);
}

void print_board(Board *b){
	const char *board_format = "Board:\n\
#############\n\
#   #   #   #\n\
# %c # %c # %c #\n\
#   #   #   #\n\
#############\n\
#   #   #   #\n\
# %c # %c # %c #\n\
#   #   #   #\n\
#############\n\
#   #   #   #\n\
# %c # %c # %c #\n\
#   #   #   #\n\
#############\n";

	char spaces_selected[9];

	int i;
	for (i=0;i<9;i++){
		if(b->spaces[i]==1){
			spaces_selected[i] = '1';
		}
		else if(b->spaces[i]==2){
			spaces_selected[i] = '2';
		}else{
			spaces_selected[i] = 'x';
		}

	}

	printf(board_format, spaces_selected[0],\
				spaces_selected[1],\
				spaces_selected[2],\
				spaces_selected[3],\
				spaces_selected[4],\
				spaces_selected[5],\
				spaces_selected[6],\
				spaces_selected[7],\
				spaces_selected[8]);
}
