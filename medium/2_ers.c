#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// I think that adding the bottom_card to the struct will let me place down cards properly, can't reference things by round, since you can put down multiple in a round.
void place_card(int player_going, Deck *game_pile, Hands *game_hands){
	Deck *player_deck = game_hands->hands[player_going];
	game_pile->cards[game_pile->top_card] = player_deck->cards[player_deck->bottom_card]; // top card in the game_deck is now set.
	player_deck->cards[player_deck->bottom_card].num = 0; // will assigning like this work?  https://stackoverflow.com/questions/330793/how-to-initialize-a-struct-in-accordance-with-c-programming-language-standards
	player_deck->cards[player_deck->bottom_card].suit = 'O'; // I'm certain there's a less hacky way to do this.
	player_deck->bottom_card++;
	game_pile->top_card++; // increment top card to the next open slot.
}

void swap_cards(Deck *d, int first, int second){ 
	// I think I'm going to have to allocate a spot in memory to save this card for a sec while I do the swap.
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


// this function will break my program, as the round_c index will not work anymore. it will reference a card that is now a 0 'O' instead of a legit card.
// I fixed it by creating a "bottom_card" int, and I just reference that to place a card down. It's incremented at the same time game_pile is, so they are both correct.


// I want this function to return the player that wins the round.
// BUG: This function seems to work for everything except Jacks? (11) FIX: break statement
int face_card(int player_going, Deck *game_pile, Hands *game_hands){
	int chances = game_pile->cards[game_pile->top_card-1].num - 10; // is this supposed to be minus one? hold on. yes, I believe so, the card is already on the pile.
	
  int i;
	printf("chances: %d\n", chances);
	for (i=0;i<chances;i++){
		place_card(player_going, game_pile, game_hands);
  		
    Card played_card;
    played_card = game_pile->cards[game_pile->top_card - 1];
    printf("SAVE ATTEMPT %d: Player %d played:\n", i+1, (player_going%4)+1);
    print_card(game_pile, game_pile->top_card-1); // must be top_card minus 1 index to see the most recently played card. "top_card" is the first open space a new card can go into.
  	
    
    if (played_card.num >= 11){
      printf("SAVED. Next player...\n");
      player_going = (player_going+1)%NUM_PLAYERS;
      face_card(player_going, game_pile, game_hands);
      break; // Does this fix it? Yes it does. Need to break out of the loop once face_card returns
    }
	}
	return player_going-1; //this should be the player that won the round
}



// You'll always want to reset a deck before you add cards to it.
// you'll always have to check to see if you won and have all the cards
// right after you add the pile to your hand. 

/*
if (d->top_card == 52){
    player_wins()
}
*/
void reset_deck(Deck *d){
    printf("Clearing a deck now...\n");
    int shift_amount = d->bottom_card; 
    int i;
    
    //shift cards so that cards start at index 0 again.
    for (i=0;i<d->top_card;i++){
        d->cards[i] = d->cards[i+shift_amount];
    }
    d->top_card = d->top_card-shift_amount;
    d->bottom_card = 0;
    printf("New bottom card num: %d\n", d->bottom_card);
    printf("New top card num: %d\n", d->top_card);
}

// This will reset each of your player hands and the game deck.
void reset_all_decks(Hands *player_hands, Deck *game_pile){
  printf("Resetting decks...\n");
  int i;
  for (i=0;i<NUM_PLAYERS;i++){
    reset_deck(player_hands->hands[i]);
  }
  reset_deck(game_pile);
  printf("All decks reset\n");
}

int main(){

  	int winner = 0;
  	int round_winner = 0;
  	int player_going = 0;
  	Deck *my_deck;
  	my_deck = make_deck();
    shuffle(my_deck);  
  	Hands *game_hands;
  	game_hands = deal_hands(my_deck, NUM_PLAYERS);
  	Deck *game_pile;
  	game_pile = make_empty_deck();

  	// Hands have been dealt. begin game loop
  	while (winner != 1){
  		
  		place_card(player_going, game_pile, game_hands);
  		Card played_card = game_pile->cards[game_pile->top_card-1];
  		printf("Player %d played: ", (player_going%NUM_PLAYERS)+1); //Displays current player
  		print_card(game_pile, game_pile->top_card-1); // this is the most recent card to be set on the pile.
 
  		player_going = (player_going + 1)%NUM_PLAYERS; // onto the next player

  		if (played_card.num >= 11) { 
  			printf("Face card played!\n");
  			int round_winner;
  			round_winner = face_card(player_going, game_pile, game_hands);

        // BUG: This print statement isn't exactly right... Including 0 when it should be 1-4
        printf("Round over! Player %d wins the pile\n", (round_winner%NUM_PLAYERS)+1);

        
        reset_all_decks(game_hands, game_pile);
        
        winner = 1; // this isnt really true as only one round is actually over.
  		}
  		
  		else{
  			continue;
  		}
  	}
  	printf("Exited the game loop\n");

	return 0;
}






/*

When a round is over, everyone resets their deck, so that their bottom card is
back to 0, and then the top_card points to the first open slot.

Then, add each card from top down the game pile to the players hand.

Check all of the players hands. If any of them have a card in the last card slot, then they must have 52 cards, which is all the cards, so they win. Exit the game loop

If there wasn't a winner, start a new round
*/
