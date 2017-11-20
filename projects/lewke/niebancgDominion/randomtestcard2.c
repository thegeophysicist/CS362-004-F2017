/* -----------------------------------------------------------------------
 * Random test for sea hag card effect
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

void randomizeHand(struct gameState *G, int kingdomCards[10])
{
    int i;
    int validCards[13];
    int handCount = rand() % G->handCount[0] + 1;

    for (i = 0; i < 10; i++)
    {
        validCards[i] = kingdomCards[i];
    }
    validCards[10] = copper;
    validCards[11] = silver;
    validCards[12] = gold;

    for (i = 0; i < handCount; i++)
    {
        G->hand[0][i] = validCards[rand() % 13];
    }
    G->hand[0][0] = sea_hag;
}

void randomizeDecks(struct gameState *G, int kingdomCards[10])
{
    int i, j;
    int validCards[13];
    int deckCount;

    for (i = 0; i < 10; i++)
    {
        validCards[i] = kingdomCards[i];
    }
    validCards[10] = copper;
    validCards[11] = silver;
    validCards[12] = gold;

    for (j = 0; j < G->numPlayers; j++)
    {
        deckCount = rand() % G->deckCount[j] + 1;
        for (i = 0; i < deckCount; i++)
        {
            G->deck[j][i] = validCards[rand() % 13];
        }
        G->deckCount[j] = deckCount;
    }
}

int main() {
    int j;  // loop counter
    int newCards = 0;
    int discarded = 1;
    int seed = 10;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState game, testGame;
    int k[10] = {adventurer, council_room, embargo, village, minion, mine,
        cutpurse, sea_hag, tribute, smithy};
    int failedTests = 0;
    int totalTests = 0;
    int handPos = 3, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int iterations = 1000;
    int test1 = 0, test2 = 0, test3 = 0, test4 = 0 , test5 = 0, test6 = 0;

    printf("=== Random Testing: Sea Hag Card ===\n");

    for (j = 1; j <= iterations; j++)
    {
        // initialized game
        initializeGame(numPlayers, k, seed, &game);

        // randomize game state
        randomizeHand(&game, k);
        randomizeDecks(&game, k);
        // copy the game state to a test case
        memcpy(&testGame, &game, sizeof(struct gameState));
    	cardEffect(sea_hag, choice1, choice2, choice3, &testGame, handPos, &bonus);

        // Test: Hand count - discarded
        totalTests++;
        if (testGame.handCount[thisPlayer] != game.handCount[thisPlayer] + newCards - discarded)
        {
            failedTests++;
            test1++;
        }

        // Test: Deck count - 2
        totalTests++;
        if ((testGame.deckCount[thisPlayer] + testGame.discardCount[thisPlayer]) != (game.deckCount[thisPlayer] + game.discardCount[thisPlayer] - newCards))
        {
            failedTests++;
            test2++;
        }

        // Test: No change to other players' states
        totalTests++;
        if (testGame.handCount[otherPlayer] != game.handCount[otherPlayer])
        {
            failedTests++;
            test3++;
        }

        totalTests++;
        if ((testGame.deckCount[otherPlayer] + testGame.discardCount[otherPlayer]) != (game.deckCount[otherPlayer] + game.discardCount[otherPlayer]))
        {
            failedTests++;
            test4++;
        }

        totalTests++;
        if (testGame.discard[otherPlayer][testGame.discardCount[otherPlayer] - 1] != game.deck[otherPlayer][game.deckCount[otherPlayer] - 1])
        {
            failedTests++;
            test5++;
        }

        totalTests++;
        if (testGame.deck[otherPlayer][testGame.deckCount[otherPlayer] - 1] != curse)
        {
            failedTests++;
            test6++;
        }
    }
    printf("[FAILED] Hand count test %d times.\n", test1);
    printf("[FAILED] Deck + Discard count test %d times.\n", test2);
    printf("[FAILED] Opposing player Hand count test %d times.\n", test3);
    printf("[FAILED] Opposing player Deck + Discard count test %d times.\n", test4);
    printf("[FAILED] Opposing player Discard test %d times.\n", test5);
    printf("[FAILED] Top of Deck is Curse test %d times.\n", test6);
    printf("\n%d Iterations: Failed %d out of %d tests.\n", iterations, failedTests, totalTests);

	return 0;
}
