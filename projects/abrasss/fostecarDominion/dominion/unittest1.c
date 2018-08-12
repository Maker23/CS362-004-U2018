#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG 0
#define VERBOSE 0

int   assertTrue( int evaluate ) {
	if (evaluate) return(0);
	else return(1);
}

int checkUpdateCoins(struct gameState *state, int tGold,int tSilver,int tCopper,int tBonus) {
  
	if (VERBOSE) { printf ("test values:  %d gold, %d silver , %d copper , %d bonus\n",
		tGold, tSilver, tCopper, tBonus);}

	int player=1;
	int cardpos=0;
	int j;
	int r;
	int result = 0;

	for (j=0; j < tGold; j++)
		{ state->hand[player][cardpos++] = gold; }
	for (j=0; j < tSilver; j++)
		{ state->hand[player][cardpos++] = silver; }
	for (j=0; j < tCopper; j++)
		{ state->hand[player][cardpos++] = copper; }
  state->handCount[player] = cardpos;

	result = (3 * tGold) + (2 * tSilver) + tCopper + tBonus;


	r = updateCoins(player, state, tBonus);

  assertTrue (r == 0);

  if (VERBOSE) {
		printf("result is %d, numcards = %d\n", result, cardpos);
  	printf("function return is %d\n", state->coins);
	}
	return (assertTrue(state->coins == result));
}

int main () {
	int i;
	int r;
  
	// Initialize a gameState struct
  struct gameState state;
	memset(&state, 0, sizeof state);

	int coinValues[][4] = {
		// gold, silver, copper, bonus
		{3,1,5,0},
		{0,0,0,0},
		{5,5,5,25}
	};
	for (i=0; i < (sizeof coinValues / sizeof coinValues[0]); i ++ )
	{
  	printf ("Testing updateCoins()");
  	r = checkUpdateCoins(&state, coinValues[i][0], coinValues[i][1], coinValues[i][2], coinValues[i][3]);
		if (r) 	
			printf (".... FAILED **\n");
		else
			printf (".... PASSED\n");
	}
  exit(0);
}
