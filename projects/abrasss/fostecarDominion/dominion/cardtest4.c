#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VERBOSE 0

/* Tests the SALVAGER card
 * initialize game; insert salvager card; set player
 * salvager requires a choice card, give a position - set that card ? yes, must set
 *   test state->coins has increased by the cost of the card
 *   test playedCardCount goes up by 1
 *   test handCount goes down by 2
 */


int   assertTrue( int evaluate ) {
	if (evaluate) return(0);
	else return(1);
}

int checkSalvager(struct gameState *state, int *K, int Seed, int CardToSalvage ) {
  
	int r, t, p;
	int moneyBefore=0;
	int cardPosition = 2; //eh, hardcode this

	if (VERBOSE) { printf ("test values:  %d Seed, %d CardToSalvage, %d value\n", Seed, CardToSalvage,getCost(CardToSalvage));}

  initializeGame(MAX_PLAYERS, K, Seed, state); // initialize the game
	int Player=0;

	state->hand[Player][0] = salvager;
	state->hand[Player][cardPosition] = CardToSalvage;
	updateCoins(Player, state, 0);
	moneyBefore = state->coins;
	if (VERBOSE) printf ("\tmoneyBefore = %d\n", moneyBefore);

	playCard(0, cardPosition, -1, -1, state);
	if (state->playedCardCount > 1) {
		p = state->playedCardCount - 2 ;
		t = assertTrue(state->playedCards[p] != CardToSalvage);
		if (VERBOSE) printf ("trashed Card = %d\n", state->playedCards[p]);
	}
	else 
		t = 0;

	r = assertTrue(state->coins == (moneyBefore + getCost(CardToSalvage)));

	if (VERBOSE) printf ("\tmoney After = %d\n", state->coins);
	if (VERBOSE) printf ("result is %d, trashed is %d\n", r, t);
	return ( r | t );
}

int main () {
  
	// Initialize a gameState struct
  struct gameState state;
	memset(&state, 0, sizeof state);
	int r;
	int i;

	int Kingdom[][10] = {
		{adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall},
		{adventurer, gardens,embargo,village,minion,mine,outpost,sea_hag,tribute,smithy},
		{tribute,ambassador,cutpurse,embargo,salvager,treasure_map,baron,great_hall,steward,feast}
	};
	int TestData[][3] = {
		// Seed, Card to Salvage, Expected result
		{23, estate, 0},
		{19, feast, 0},
		{53, province, 0},
		{119, curse, 0}
	};

  for ( i=0; i < (sizeof TestData / sizeof TestData[0]); i++ )
	{
  	printf ("Testing Salvager()");
		r = checkSalvager(&state, Kingdom[i],TestData[i][0],TestData[i][1]); 
		if (r != TestData[i][2]) printf (".... FAILED **\n"); else printf (".... PASSED\n");
	}
  exit(0);
}
