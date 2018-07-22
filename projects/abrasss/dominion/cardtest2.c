#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VERBOSE 0

/* Tests the ADVENTURER card
 *
 * initialize_game, set player, insert adventurer card
 * play card
 * player’s hand should have all cards that were in it before, except adventurer
 *    plus two treasure cards
 *    can’t draw any conclusions about the state of the deck or discard pile
 */

int deleteCards (int *SetA, int *SetB, int lenA, int lenB);

int   assertTrue( int evaluate ) {
	if (evaluate) return(0);
	else return(1);
}

int checkAdventurer(struct gameState *state, int *K, int Seed, int CardPosition ) {
  
	int i;
	int r, c, a=-1, b=-1;
	int handBefore[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int countBefore;

	if (VERBOSE) { printf ("test values:  %d Seed, %d CardPosition\n",
		Seed, CardPosition);}

  initializeGame(MAX_PLAYERS, K, Seed, state); // initialize the game
	int Player=0;
  if ( CardPosition > 4 || CardPosition < 0 ) CardPosition = abs(CardPosition%5);
	state->hand[Player][CardPosition] = adventurer;

	countBefore = state->handCount[Player];
	for (i=0; i < countBefore; i++ ) {
		// Uncomment if adventurer should not be in the hand after playing
		// if ( i != CardPosition )
			handBefore[i] = state->hand[Player][i];
	}
	if (VERBOSE) printf("Players handcount is %d\n", state->handCount[Player]);
	if (VERBOSE) printf("Players deck count is %d\n", state->deckCount[Player]);
	if (VERBOSE) printf("Players discard count is %d\n", state->discardCount[Player]);

	playCard(CardPosition, -1, -1, -1, state);


	if (VERBOSE) printf("    ++  handcount is %d\n", state->handCount[Player]);
	if (VERBOSE) printf("    ++  deck count is %d\n", state->deckCount[Player]);
	if (VERBOSE) printf("    ++  discard count is %d\n", state->discardCount[Player]);
	if ( state->discardCount[Player] > 0  && VERBOSE)
		printf ("     ==  discarded card is %d\n", state->discard[Player][0]);

	c = assertTrue( state->handCount[Player] == countBefore + 2);

	deleteCards(state->hand[Player],handBefore, state->handCount[Player],countBefore);
	for (i=0; i < state->handCount[Player]; i++ ) {
		int thisCard = state->hand[Player][i];
	 	if ( thisCard != -1 ) {
			if (a < 0 )
				a = assertTrue( thisCard == copper || thisCard == silver || thisCard == gold);
			else
				b = assertTrue( thisCard == copper || thisCard == silver || thisCard == gold);
			
			if (VERBOSE) printf ("Still have card %d\n", state->hand[Player][i]);
		}
	}

	r = c | a | b;

	if (VERBOSE) printf ("result is %d\n", r );
	return ( r );
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
	int TestData[][2] = {
		// Seed, CardPosition
		{23, 1},
		{19, 3},
		{117, 4}
	};

  for ( i=0; i < (sizeof TestData / sizeof TestData[0]); i++ )
	{
  	printf ("Testing Adventurer()");
		r = checkAdventurer(&state, Kingdom[i],TestData[i][0],TestData[i][1]); 
		if (r != 0) printf (".... FAILED **\n"); else printf (".... PASSED\n");
	}
  exit(0);
}
/* ******************************************************************* */

int deleteCards (int *SetA, int *SetB, int lenA, int lenB) 
{
	int a,b;
	int found=0;

  for (b=0; b<lenB; b++) {
		if ( SetB[b] == -1 )
			continue;
		if (DEBUG) printf ("Looking for %d in Set A\n", SetB[b]);
  	for (a=0; a<lenA; a++) {
			if ( SetA[a] == SetB[b] ) {
				if (DEBUG) printf ("Deleting %d from Set A\n", SetB[b]);
				SetA[a] = -1;
				found=1;
				break;
			}
		}
		if ( ! found ) {
			if (DEBUG) printf ("Card in SetB not found in SetA: %d\n", SetB[b]);
		}
	}
	return(0);
}

