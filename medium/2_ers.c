#include <stdio.h>
#include <stdlib.h>

#define BUFFER 200

typedef struct card_tag {
    int num;
    char suit;
} Card;

typedef struct deck_tag {
	Card cards[52];
} Deck;

/*

// I don't need this because I'm creating space for all the cards when I make a deck. I just need to initialize the cards in my deck.

Card *make_card(int given_num, char given_suit){
    Card *temp = calloc(1, sizeof(Card));
    temp->num = given_num;
    temp->suit = given_suit; // since this is just 1 char I think I use this. It's one value.
    //snprintf(temp->suit, BUFFER, given_suit); // or do I: temp->suit = given_suit
    return temp;
}
*/

// I want deck struct to be a struct that contains 52 card structs.
// Each Card struct contains a int that's the number and a char that represents the suit.

Deck *make_deck(){
    Deck *temp = calloc(1, sizeof(Deck));
    int deck_c = 0;
    int suit_c;
    int num_c;
    char suits[5] = {'S', 'H', 'D', 'C'};
    for (suit_c=0; suit_c<4; suit_c++){
    	for (num_c=2; num_c<15; num_c++){
    		temp->cards[deck_c].num = num_c; // Is this going to correctly write into the memory?
    		//printf("Wrote %d into Card %d\n", num_c, deck_c);
    		temp->cards[deck_c].suit = suits[suit_c];
    		//printf("Wrote %c into Card %d\n", suits[suit_c], deck_c);
    		deck_c++;
    	}
    }

    return temp;
}


void print_card(Deck *d, int i){ //maybe I should have this take a card as an argument instead of a pointer to a deck and an index?
	printf("Card: %d, %c\n", d->cards[i].num, d->cards[i].suit);
}


void print_deck(Deck *d){
	int i;
	for (i=0;i<52;i++){
		print_card(d, i);
	}
}

int main(){
	/*
	Card *my_card;
	my_card = make_card(14, 'S');
	print_card(my_card);
	*/

	printf("\n\nNow let's try a deck\n\n");

	Deck *my_deck;
	my_deck = make_deck();
	print_deck(my_deck);
	return 0;
}


