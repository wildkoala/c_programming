#include <stdio.h>
#include <stdlib.h>

#define BUFFER 200
#define NUM_PLAYERS 4 //get this from user in eventually

typedef struct card_tag {
    int num;
    char suit;
} Card;

typedef struct deck_tag {
	int top_card;
	Card cards[52];
} Deck;

typedef struct hands_tag{
    Deck *hands[NUM_PLAYERS]; // an array of pointers to decks (1 per player)
} Hands;

/*
typedef struct pile_tag{
	int next_slot;
	Card cards[52];
} Pile;
*/

/*
'->'' means "access the thing at the end of this pointer"
access individual members in a struct by saying "struct.member"
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
    temp->top_card = 0;
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

// this makes a deck that is uninitialized, there's probably a better way, idk. Maybe a condtional statement in the make_deck func.
Deck *make_empty_deck(){
    Deck *temp = calloc(1, sizeof(Deck));
    int deck_c = 0;
    int suit_c;
    int num_c;
    char suits[5] = {'S', 'H', 'D', 'C'};
    temp->top_card = 0;
    for (suit_c=0; suit_c<4; suit_c++){
    	for (num_c=2; num_c<15; num_c++){
    		temp->cards[deck_c].num = 0; // Is this going to correctly write into the memory?
    		//printf("Wrote %d into Card %d\n", num_c, deck_c);
    		temp->cards[deck_c].suit = 'O';
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

void print_hands(Hands *h){
  	int i;
  	for(i=0; i<NUM_PLAYERS; i++){
  		printf("Hand shown: %d\n", i);
  		print_deck(h->hands[i]);
  	}
}

void place_card(int round_c, int player_going, Deck *game_pile, Hands *game_hands){
	game_pile->cards[round_c] = game_hands->hands[player_going]->cards[round_c];
	game_hands->hands[player_going]->cards[round_c].num = 0; // will assigning like this work?  https://stackoverflow.com/questions/330793/how-to-initialize-a-struct-in-accordance-with-c-programming-language-standards
	game_hands->hands[player_going]->cards[round_c].suit = 'O'; // I'm certain there's a less hacky way to do that.
}

void swap_cards(Deck *d, int first, int second){ 
	// I think I'm going to have to allocate a spot in memory to save this card for a sec while I do the swap.
	Card *saved = calloc(1, sizeof(Card));
	saved->num = d->cards[first].num;
	saved->suit = d->cards[first].suit;

	//printf("Card saved successfully: %d, %c\n", saved->num, saved->suit); // keep in mind that saved is a pointer to a card rn.

	// Swap the first card with the second
	d->cards[first].num = d->cards[second].num;
	d->cards[first].suit = d->cards[second].suit;

	// Grab the saved card and write it into the second to complete the swap.
	d->cards[second].num = saved->num;
	d->cards[second].suit = saved->suit;

	//printf("Cards swapped successfully\n");
}

void shuffle(Deck *d){
	// Shuffle will be a series of card swaps. I will swap a set amount of times. 100 for now.
	int swaps;
	for (swaps=0; swaps<100; swaps++){
		int r1 = rand() % 52; // mod 52 will always give me between 0 and 51.
		int r2 = rand() % 52; 
		swap_cards(d, r1, r2);
		// printf("Random numbers generated: %d, %d\n", r1, r2);
	}
}

Hands *deal_hands(Deck *d, int num_players){ // right now should just have empty hands for every player.
    int i;
    int deck_i;
    int current_player=0;
    Hands *dealt_hands;
    dealt_hands = calloc(1, sizeof(Hands));

    for (i=0;i<num_players;i++){
        dealt_hands->hands[i] = make_empty_deck(); 
        //printf("In loop making empty decks\n");
    }
    //printf("Out of empty deck loop\n");
    // Oh shit, this doesn't work because I didn't initialize the top card!! fixed it.
    // hm, didn't get this to change anything.
    for (deck_i=0; deck_i<52; deck_i++){ // can i initialize this outside of the loop and use it later?
       	//printf("In deck dealing loop\n");
       	
       	Deck *current_player_deck = dealt_hands->hands[current_player];
       	/*
       	//current_player_d->cards[current_player_d->top_card] = d->cards[deck_i]; // can I assign a whole card like this?
       	// lets try it this way.
       	current_player_d->cards[current_player_d->top_card].num = d->cards[deck_i].num;
       	current_player_d->cards[current_player_d->top_card].suit = d->cards[deck_i].suit;
		*/
		// array of deck pointers->specific deck pointer[]->cards[specific_deck_pointer->top_card]

		// this is looping properly.

		int curr_index = current_player_deck->top_card;
		//printf("Current top card value: %d\n", curr_index);
    	//print_card(dealt_hands->hands[current_player]->cards[curr_index]);
		current_player_deck->cards[current_player_deck->top_card] = d->cards[deck_i]; // can I assign a whole card like this?
       	//print_card(current_player_deck, current_player_deck->top_card);

       	// Increment top card index
       	dealt_hands->hands[current_player]->top_card++;
       	// go on to the next player, wrap around when you've gone to every player.
       	current_player = (current_player+1)%num_players;
    }

    //printf("\nHands have been dealt...\n");
    return dealt_hands;
}



int main(){
	/*
	Card *my_card;
	my_card = make_card(14, 'S');
	print_card(my_card);
	*/

	//printf("\n\nNow let's try a deck\n\n");
  	int winner = 0;
  	int round_winner = 0;
  	int round_counter = 0;
  	int player_going = 0;
	Deck *my_deck;
	my_deck = make_deck();
	//print_deck(my_deck);
	//swap_cards(my_deck, 0,1);
	shuffle(my_deck);
	//print_deck(my_deck);
  	Hands *game_hands;
  	game_hands = deal_hands(my_deck, NUM_PLAYERS);
  	//print_hands(game_hands);

  	Deck *game_pile;
  	game_pile = make_empty_deck();
  	// Hands have been dealt. begin game loop

  	while (winner != 1){
  		printf("In game loop\n");
  		// Player 0 places a card
  		place_card(round_counter, player_going, game_pile, game_hands);
  		printf("Here's the game pile now:\n");
  		print_deck(game_pile);
  		printf("Here's the first player's pile now:\n");
  		print_deck(game_hands->hands[0]);
  		winner = 1;
  		// next player places a card

  	}
  	printf("Exited the game loop, winner = 1\n");

	return 0;
}



























