#include <stdio.h>
#include <stdlib.h>

#define BUFFER 200

typedef struct card_tag {
    int num;
    char suit;
} Card;

Card *make_card(int given_num, char given_suit){
    Card *temp = calloc(1, sizeof(Card));
    temp->num = given_num;
    temp->suit = given_suit; // since this is just 1 char I think I use this. It's one value.
    //snprintf(temp->suit, BUFFER, given_suit); // or do I: temp->suit = given_suit
    return temp;
}

void print_card(Card *c){
	printf("Card: %d, %c\n", c->num, c->suit);
}

int main(){
	Card *my_card;
	my_card = make_card(14, 'S');
	print_card(my_card);
	return 0;
}

