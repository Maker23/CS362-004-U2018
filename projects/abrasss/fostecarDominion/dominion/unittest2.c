#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VERBOSE 0

int   assertTrue( int evaluate ) {
	if (evaluate) return(0);
	else return(1);
}

int checkGameOver(struct gameState *state, int *K, int Seed, int *Cards, int Over ) {
  
	int i;
	int r;

	if (VERBOSE) { printf ("test values:  %d Seed, %d Card1 , %d Card2 , %d Card3, %d Over\n",
		Seed, Cards[0], Cards[1], Cards[2], Over);}
	if (VERBOSE) { 
		for (i=0; i<10; i++) {
			printf("\tK[%d] = %d\n", i, K[i]);
		}	
	}

	
  initializeGame(2, K, Seed, state); // initialize the game


  // zero some number of cards (the condition for ending the game)
	for (i=0; i < 3; i++ ) {
		state->supplyCount[Cards[i]] = 0;
		state->supplyCount[Cards[i]] = 0;
		state->supplyCount[Cards[i]] = 0;
	}


	r = isGameOver(state); // 1 if over, 0 if not
	if (VERBOSE) printf ("result is %d\n", r);

  return (assertTrue (r == Over));

}

int main () {
  
	// Initialize a gameState struct
  struct gameState state;
	memset(&state, 0, sizeof state);
	int r;

	int Kingdom[][10] = {
		{adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall},
		{adventurer, gardens,embargo,village,minion,mine,outpost,sea_hag,tribute,smithy},
		{tribute,ambassador,cutpurse,embargo,salvager,treasure_map,baron,great_hall,steward,feast}
	};
	int Zero[][3] = {
		{mine,gardens,smithy}, // Game is over - three cards zeroed
		{province},            // Game is over - province zeroed
		{ambassador,treasure_map} // Game is not over - two cards zeroed
	};



  printf ("Testing isGameOver()");
	r = checkGameOver(&state, Kingdom[0],23,Zero[0],1); // Game is over
	if (r) printf (".... FAILED **\n"); else printf (".... PASSED\n");

  printf ("Testing isGameOver()");
	if (r) printf (".... FAILED **\n"); else printf (".... PASSED\n");
	r = checkGameOver(&state, Kingdom[1],19,Zero[1],1); // Game is over

  printf ("Testing isGameOver()");
	r = checkGameOver(&state, Kingdom[2],119,Zero[2],0); // Game is not over
	if (r) printf (".... FAILED **\n"); else printf (".... PASSED\n");

  exit(0);
}
