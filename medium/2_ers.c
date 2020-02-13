/*
BUGS:

1. Need to add exception handling for when a player doesn't have anymore cards to place. (They've lost and need to be skipped) Breaks program right now
2. Need next round to start with the person that just won the previous round.

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUFFER 200
#define NUM_PLAYERS 4 //get this from user in eventually

typedef struct card_tag {
    int num;
    char suit;
} Card;

typedef struct deck_tag {
	int bottom_card;
	int top_card;
	Card cards[52];
} Deck;

typedef struct hands_tag{
    Deck *hands[NUM_PLAYERS]; // an array of pointers to decks (1 per player)
} Hands;

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

// In retrospect, I might have wanted to do this with a linked list.

Deck *make_deck(){
    Deck *temp = calloc(1, sizeof(Deck));
    int deck_c = 0;
    int suit_c;
    int num_c;
    temp->top_card = 0;
    temp->bottom_card = 0;
    char suits[5] = {'S', 'H', 'D', 'C'};
    for (suit_c=0; suit_c<4; suit_c++){
    	for (num_c=2; num_c<15; num_c++){
    		temp->cards[deck_c].num = num_c; // Is this going to correctly write into the memory?
    		temp->cards[deck_c].suit = suits[suit_c];
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
    temp->bottom_card = 0;
    for (suit_c=0; suit_c<4; suit_c++){
    	for (num_c=2; num_c<15; num_c++){
    		temp->cards[deck_c].num = 0; 
    		temp->cards[deck_c].suit = 'O';
    		deck_c++;
    	}
    }

    return temp;
}


void print_card(Deck *d, int i){ //maybe I should have this take a card as an argument instead of a pointer to a deck and an index?
	printf("Card: %d, %c\n", d->cards[i].num, d->cards[i].suit);
}


void print_deck(Deck *d){
	printf("PRINTING DECK:\n");
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


// Returns the index of the player that won a round. Keep it 0 indexed for now, that's the way it is throughout the game.
int round_winner(int player_going){
	if(player_going == 0){
		return NUM_PLAYERS-1;
	}
	return player_going-1;
}


void place_card(int player_going, Deck *game_pile, Hands *game_hands){
	Deck *player_deck = game_hands->hands[player_going];
	// Need to check if they have a card first, then play card.
	game_pile->cards[game_pile->top_card] = player_deck->cards[player_deck->bottom_card]; 
	player_deck->cards[player_deck->bottom_card].num = 0; // will assigning like this work?  https://stackoverflow.com/questions/330793/how-to-initialize-a-struct-in-accordance-with-c-programming-language-standards
	player_deck->cards[player_deck->bottom_card].suit = 'O'; // I'm certain there's a less hacky way to do this.
	player_deck->bottom_card++;
	game_pile->top_card++; // increment top card to the next open slot.
}

void swap_cards(Deck *d, int first, int second){ 
	Card *saved = calloc(1, sizeof(Card));
	saved->num = d->cards[first].num;
	saved->suit = d->cards[first].suit;

	// Swap the first card with the second
	d->cards[first].num = d->cards[second].num;
	d->cards[first].suit = d->cards[second].suit;

	// Grab the saved card and write it into the second to complete the swap.
	d->cards[second].num = saved->num;
	d->cards[second].suit = saved->suit;
}

void shuffle(Deck *d){
	// Shuffle will be a series of card swaps. I will swap a set amount of times. 100 for now.
	srand(time(NULL));
	int swaps;
	for (swaps=0; swaps<100; swaps++){
		int r1 = rand() % 52;
		int r2 = rand() % 52; 
		swap_cards(d, r1, r2);
	}
}

Hands *deal_hands(Deck *d, int num_players){ 
    int i;
    int deck_i;
    int current_player=0;
    Hands *dealt_hands;
    dealt_hands = calloc(1, sizeof(Hands));

    for (i=0;i<num_players;i++){
        dealt_hands->hands[i] = make_empty_deck();
    }

    for (deck_i=0; deck_i<52; deck_i++){
       	Deck *current_player_deck = dealt_hands->hands[current_player];
		    int curr_index = current_player_deck->top_card;
		    current_player_deck->cards[current_player_deck->top_card] = d->cards[deck_i]; 
       	dealt_hands->hands[current_player]->top_card++;
       	current_player = (current_player+1)%num_players;
    }
    return dealt_hands;
}


// You'll always want to reset a deck BEFORE you add cards to it. 
// you'll always have to check to see if you won and have all the cards
// Right after you add the pile to your hand. 

void add_winnings(Deck *player_hand, Deck *game_pile){
	int num_cards = game_pile->top_card;
	int i;

	for (i=0;i<num_cards;i++){
		// Put the card from the bottom of the pile and put it on top of the winners hand
		player_hand->cards[player_hand->top_card] = game_pile->cards[i];
		
		// Have to increment the top card now
		player_hand->top_card = (player_hand->top_card) + 1;

		//Reset that card in the game_pile
		game_pile->cards[i].num = 0;
		game_pile->cards[i].suit = 'O';
	}
}


void reset_deck(Deck *d){
    int shift_amount = d->bottom_card; 
    int i;
    
    //shift cards so that cards start at index 0 again.
    for (i=0;i<d->top_card;i++){
        d->cards[i] = d->cards[i+shift_amount];
    }
    d->top_card = d->top_card-shift_amount;
    d->bottom_card = 0;
}

// This will reset each of your player hands and the game deck.
void reset_all_decks(Hands *player_hands, Deck *game_pile){
  int i;
  for (i=0;i<NUM_PLAYERS;i++){
    reset_deck(player_hands->hands[i]);
  }
  reset_deck(game_pile);
}

int face_card2(int player_c, Deck *game_deck, Hands *p_hands){
	int chances = game_deck->cards[game_deck->top_card-1].num - 10; 
	printf("Chances: %d\n", chances);
	int i;
	for (i=0; i<chances; i++){
		//user places a card
		place_card(player_c, game_deck, p_hands);
		
		Card played_card;
		played_card = game_deck->cards[game_deck->top_card - 1];
		printf("ATTEMPT %d: Player %d played:\n", i+1, (player_c%NUM_PLAYERS));
		print_card(game_deck, game_deck->top_card-1);
		sleep(2);

		if (played_card.num >= 11){
			printf("SAVED\n");
			return 1;
		}
	}
	printf("Didn't pass the save...\n");
	return 0;
}

int face_card_placed(Card played_card){
	if (played_card.num >= 11) { 
		printf("Face card played!\n");
		return 1;
	}
	return 0;
}

int check_win(Deck *p_hand){
	if(p_hand->top_card == 52){
		return 1;
	}
	return 0;
}

int main(){

  	int winner = 0;
  	int player_going = 0;
  	Deck *my_deck;
  	my_deck = make_deck();
    shuffle(my_deck);  
  	Hands *game_hands;
  	game_hands = deal_hands(my_deck, NUM_PLAYERS);
  	Deck *game_pile;
  	game_pile = make_empty_deck();

  	// Hands have been dealt. begin game loop
  	while (winner != 2){ // tRYING TO GET TWO ROUNDS
  		
  		place_card(player_going, game_pile, game_hands);
  		Card played_card = game_pile->cards[game_pile->top_card-1];
  		printf("Player %d played: ", (player_going%NUM_PLAYERS)); //Displays current player
  		print_card(game_pile, game_pile->top_card-1); // this is the most recent card to be set on the pile.
		sleep(2);
  		player_going = (player_going + 1)%NUM_PLAYERS; // onto the next player

		int face_card;
		face_card = face_card_placed(played_card);

		if (face_card){
			int round_end = 0;
			while (round_end != 1){ 
				int saved;
				saved = face_card2(player_going, game_pile, game_hands); 
				if (saved){
					// changed player_going, let's see if we still seg fault. No, now it's just not iterating??
					// Changed from ++ to +1, let's see if that's it. Yep, that did it.
					/*
						player_going = (++player_going)%NUM_PLAYERS;

						=

						player_going++;
						player_going = (player_going)%NUM_PLAYERS;


						player_going = (player_going++)%NUM_PLAYERS;

						=

						player_going = (player_going)%NUM_PLAYERS;
						player_going++;


						player_going = ( player_going + 1 )%NUM_PLAYERS;

						==

						player_going = player_going + 1;
						player_going = ( player_going )%NUM_PLAYERS;
					*/

					player_going = (++player_going)%NUM_PLAYERS;
				}
				else{
					round_end = 1;
				}
			}
			// Print who won the round
			int round_winner_index;
			round_winner_index = round_winner(player_going);
			printf("Player %d won the round.\n", round_winner_index);

			reset_all_decks(game_hands, game_pile);

			// and add the winnings to the winners deck
			add_winnings(game_hands->hands[round_winner_index], game_pile);

			// Check if the winner has 52 cards.
			//winner = check_win(game_hands->hands[player_going]); // this plays until there's a winner
			player_going = round_winner_index; // this means the round winner will go first next round.
			//winner = 1; // this means there will only be one round
			winner++; //hopefully gets me two rounds
			printf("STARTING NEW ROUND\n");
			
				
		}
  	}
  	printf("Exited the game loop\n");

	return 0;
}



/* Implement event queue that's globally accessible in the program

semefors - finer control, thread sends messages to other threads
mutex locks - lock everyone else out until done.

1. User sends a 'space bar' or '^' command to the server as their client_action
2. Server takes the client_action, verifies it is a valid action, and which client sent it. // maybe i dont need to check, just don't have an action for it.
3. Server creates an event struct. 
4. The server calculates the unix time (need something more to get it down to miliseconds). // maybe in the future account for latency?
5. Event struct includes the client, client_action and time. 
6. Events are placed into an event queue. (Priority queue where priority is based on time)
7. Game loop takes the events, tries to pop first one off
	a. If no event, loop back through game loop
	b. else	{
			if (event.client_action == ' '){
				if (is_pair() || is_sandwich()){
					round_over = 1;
				}
				else{
					penalty();
				}
			}
			if (event.client_action == '^'){
				if(player_going == event.client){
					place_card();
				}
			}			
		}


when in game loop, execute everything in the queue.
*/