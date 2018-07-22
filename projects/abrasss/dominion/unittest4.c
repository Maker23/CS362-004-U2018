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

int checkBuyCard(struct gameState *state, int *K, int Card, int Coins, int numBuys, int Result ) {
  
	int i;
	int r;
	int Seed = 17;

	if (VERBOSE) { printf ("test values:  %d Card , %d Coins , %d Result\n",
		Card, Coins, Result);}
	//if (VERBOSE) { 
	if (0) { 
		for (i=0; i<10; i++) {
			printf("\tK[%d] = %d\n", i, K[i]);
		}	
	}
	
  initializeGame(2, K, Seed, state); // initialize the game
	state->whoseTurn = 1; // Ready Player One
	state->coins = Coins;
	state->numBuys = numBuys;

	r = buyCard(Card,state); // 1 if over, 0 if not
	if (VERBOSE) printf ("result is %d\n", r);

  return (assertTrue (r == Result));

}

int main () {
  
	// Initialize a gameState struct
  struct gameState state;
	memset(&state, 0, sizeof state);
	int r;
	int i;

	int Kingdom[10] = {
		tribute,ambassador,cutpurse,embargo,salvager,treasure_map,baron,great_hall,steward,feast
	};
	int Buy[][4] = {
		// card, coins, numBuys; 0 or -1 (succeed or fail)
		{province,10,1, 0}, 	// Buy a card we can afford
		{province, 4,1, -1},      // Buy a card we can't afford
		{council_room,10,1, -1}, // Buy a card that isn't in the kingdom
		{ambassador,10,0, -1} // Buy a card when no buys are left
	};

  for (i=0; i < (sizeof Buy / sizeof Buy[0]); i++) {
  	printf ("Testing buyCard()");
		r = checkBuyCard(&state, Kingdom,Buy[i][0], Buy[i][1], Buy[i][2], Buy[i][3]);
		if (r) printf (".... FAILED **\n"); else printf (".... PASSED\n");

	}

  exit(0);
}
