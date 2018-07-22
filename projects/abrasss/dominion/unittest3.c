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

int checkScoreFor(struct gameState *state, int *Hand, int *Discard, int *Deck ) {
  
	int i;
	int r;
	int player=2;
	int handCount=0;
	int discardCount=0;
	int deckCount=0;
	int score=0;

	if (0) { 
		for (i=0; i<6; i++) {
			printf("\t   Hand[%d] = %d\n", i, Hand[i]);
			printf("\tDiscard[%d] = %d\n", i, Discard[i]);
			printf("\t   Deck[%d] = %d\n", i, Deck[i]);
		}	
	}

	for (i=0; i < Hand[0]; i++ ) { state->hand[player][handCount++] = curse; }
	for (i=0; i < Hand[1]; i++ ) { state->hand[player][handCount++] = estate; }
	for (i=0; i < Hand[2]; i++ ) { state->hand[player][handCount++] = duchy; }
	for (i=0; i < Hand[3]; i++ ) { state->hand[player][handCount++] = province; }
	for (i=0; i < Hand[4]; i++ ) { state->hand[player][handCount++] = great_hall; }
	for (i=0; i < Hand[5]; i++ ) { state->hand[player][handCount++] = gardens; }

	for (i=0; i < Discard[0]; i++ ) { state->discard[player][discardCount++] = curse; }
	for (i=0; i < Discard[1]; i++ ) { state->discard[player][discardCount++] = estate; }
	for (i=0; i < Discard[2]; i++ ) { state->discard[player][discardCount++] = duchy; }
	for (i=0; i < Discard[3]; i++ ) { state->discard[player][discardCount++] = province; }
	for (i=0; i < Discard[4]; i++ ) { state->discard[player][discardCount++] = great_hall; }
	for (i=0; i < Discard[5]; i++ ) { state->discard[player][discardCount++] = gardens; }

	for (i=0; i < Deck[0]; i++ ) { state->deck[player][deckCount++] = curse; }
	for (i=0; i < Deck[1]; i++ ) { state->deck[player][deckCount++] = estate; }
	for (i=0; i < Deck[2]; i++ ) { state->deck[player][deckCount++] = duchy; }
	for (i=0; i < Deck[3]; i++ ) { state->deck[player][deckCount++] = province; }
	for (i=0; i < Deck[4]; i++ ) { state->deck[player][deckCount++] = great_hall; }
	for (i=0; i < Deck[5]; i++ ) { state->deck[player][deckCount++] = gardens; }

	state->handCount[player] = handCount;
	state->discardCount[player] = discardCount;
	state->deckCount[player] = deckCount;

	score += (Hand[0] + Discard[0] + Deck[0]) * -1;
	score += (Hand[1] + Discard[1] + Deck[1]) * 1;
	score += (Hand[2] + Discard[2] + Deck[2]) * 3;
	score += (Hand[3] + Discard[3] + Deck[3]) * 6;
	score += (Hand[4] + Discard[4] + Deck[4]) * 1;
	score += (fullDeckCount(player,0,state) / 10 );

	r = scoreFor(player,state); 

  return (assertTrue (r == score) );

	//return(0);
}

int main () {
  
	// Initialize a gameState struct
  struct gameState state;
	memset(&state, 0, sizeof state);
	int i;
	int r;

	int Cards[][3][6] = {
		{
			// curse, estate, duchy, province, great_hall, gardens
			{0,2,2,2,2,2},  // hand
			{3,4,2,6,2,8},  // discard
			{1,20,12,25,2,38} //deck
		},
		{
			{0,0,0,0,0,0},  // hand
			{0,0,0,0,0,0},  // discard
			{0,0,0,0,0,0} 	//deck
		},
		{
			{2,0,0,0,0,0},  // hand
			{1,0,0,0,0,0},  // discard
			{3,0,0,0,0,0} 	//deck
		},
	};

	for (i=0; i<3; i++)
	{
  	printf ("Testing scoreFor() ");
		r=checkScoreFor(&state, Cards[i][0], Cards[i][1], Cards[i][2]);
		if ( r ) 
			printf (".... FAILED **\n");
		else
			printf (".... PASSED\n");
	}

  exit(0);
}
