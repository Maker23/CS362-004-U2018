#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VERBOSE 0

/* Tests the SMITHY card
 *
 * initialize_game; this creates hands of cards.
 * set player
 * insert a smithy card into the hand in some position, 0-1-2-3-4
 * playCard(position, -1, -1, -1, state)
 * test: handsize should be 7 (draw three cards)
 * 
 */


int   assertTrue( int evaluate ) {
	if (evaluate) return(0);
	else return(1);
}

int checkSmithy(struct gameState *state, int *K, int Seed, int CardPosition ) {
  
	int i;

	if (VERBOSE) { printf ("test values:  %d Seed, %d CardPosition\n",
		Seed, CardPosition);}
	if (0) { 
		for (i=0; i<10; i++) {
			printf("\tK[%d] = %d\n", i, K[i]);
		}	
	}

  initializeGame(MAX_PLAYERS, K, Seed, state); // initialize the game
	int Player=0;

  if ( CardPosition > 4 || CardPosition < 0 ) CardPosition = abs(CardPosition%5);
	state->hand[Player][CardPosition] = smithy;
	playCard(CardPosition, -1, -1, -1, state);

	if (VERBOSE) printf ("result is %d\n", assertTrue(state->handCount[Player] == 7));
	return ( assertTrue( state->handCount[Player] == 7 ));
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
		{119, 4}
	};

  for ( i=0; i < (sizeof TestData / sizeof TestData[0]); i++ )
	{
  	printf ("Testing Smithy()");
		r = checkSmithy(&state, Kingdom[i],TestData[i][0],TestData[i][1]); 
		if (r != 0) printf (".... FAILED **\n"); else printf (".... PASSED\n");
	}
  exit(0);
}
