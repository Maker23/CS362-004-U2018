#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VERBOSE 0

/* Tests the SEA HAG card
 *
 * initialize game; insert sea_hag card; set player
 * play card no arguments
 * for all players, not this player:
 *   top card in deck should now be a curse, 
 *   discard count goes up by 1,
 *   top of discard pile should be card that was top of deck
 *  
 */


int   assertTrue( int evaluate ) {
	if (evaluate) return(0);
	else return(1);
}

int checkSeaHag(struct gameState *state, int *K, int Seed, int NumPlayers ) {
  
	int i,D,T,C,x;
	int r=0; // default to true
	int opponentTopCardBefore[NumPlayers];
	int opponentDiscardCount[NumPlayers];
	int Player=0; // hard code this for now

  if ( NumPlayers > MAX_PLAYERS || NumPlayers < 0 ) NumPlayers = abs(NumPlayers%MAX_PLAYERS);
	if (VERBOSE) { printf ("test values:  %d Seed, %d NumPlayers\n",
		Seed, NumPlayers);}

  initializeGame(NumPlayers, K, Seed, state); // initialize the game
	state->hand[Player][0] = sea_hag;
	
	// Store information before the card is played
	for (i=0; i< NumPlayers; i++) {
		if (VERBOSE) printf ("Storing data for player %d\n", i);
		if ( i != Player ) {
			opponentTopCardBefore[i] = state->deck[i][state->deckCount[i]-1];
			opponentDiscardCount[i] =  state->discardCount[i];
			if (VERBOSE) printf ("\tOpponent Top Card = %d, DiscardCount= %d, DeckCount = %d\n", opponentTopCardBefore[i],
			opponentDiscardCount[i], state->deckCount[i] );
			if (0) {
				for ( x=0; x < state->deckCount[i]; x++) {
					printf ("\t\tCard %d = %d\n", x, state->deck[i][x]);
				}
			}
		}
	}

	playCard(0, -1, -1, -1, state);
	// Compare information after the card is played
	for (i=0; i< NumPlayers; i++) {
		if (VERBOSE) printf ("Checking player %d\n", i);
		if ( i != Player ) {
			if (VERBOSE) printf ("\tOpponent Top Card = %d, DiscardCount= %d, DeckCount = %d\n", state->deck[i][state->deckCount[i]-1],state->discardCount[i],state->deckCount[i]);
			D = assertTrue ( state->discardCount[i] == opponentDiscardCount[i] + 1);
			C = assertTrue ( state->discard[i][state->discardCount[i]-1] == opponentTopCardBefore[i]);
			T = assertTrue ( state->deck[i][state->deckCount[i]-1] == curse );
			if (VERBOSE) printf ("\tDiscardCount check:%d, TopCard check:%d, TopDeck check=%d\n", D,C,T);

			r = D | C | T;
		}
	}
	return (r);

}

int main () {
  
	// Initialize a gameState struct
  struct gameState state;
	memset(&state, 0, sizeof state);
	int r;
	int i;

	int Kingdom[][10] = {
		{sea_hag,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall},
		{adventurer, gardens,embargo,village,minion,mine,outpost,sea_hag,tribute,smithy},
		{tribute,ambassador,cutpurse,embargo,salvager,sea_hag,baron,great_hall,steward,feast}
	};
	int TestData[][3] = {
		// Seed, Num Players, Expected result
		{23, 2, 0},
		{19, 3, 0 },
		{119, 4, 0 } 
	};

  for ( i=0; i < (sizeof TestData / sizeof TestData[0]); i++ )
	{
  	printf ("Testing SeaHag()");
		r = checkSeaHag(&state, Kingdom[i],TestData[i][0],TestData[i][1]); 
		if (r != TestData[i][2]) printf (".... FAILED **\n"); else printf (".... PASSED\n");
	}
  exit(0);
}
