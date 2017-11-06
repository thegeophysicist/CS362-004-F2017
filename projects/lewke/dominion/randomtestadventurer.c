/* -----------------------------------------------------------------------
 * Random test for adventurer card effect
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
    G->hand[0][0] = adventurer;
}

void randomizeDeck(struct gameState *G, int kingdomCards[10])
{
    int i;
    int validCards[13];
    int deckCount = rand() % G->deckCount[0] + 1;

    for (i = 0; i < 10; i++)
    {
        validCards[i] = kingdomCards[i];
    }
    validCards[10] = copper;
    validCards[11] = silver;
    validCards[12] = gold;

    for (i = 0; i < deckCount; i++)
    {
        G->deck[0][i] = validCards[rand() % 13];
    }
    G->deckCount[0] = deckCount;
}

int main()
{
    srand(time(NULL));

    int i, j;  // loop counter
    int newCards = 0;
    int discarded = 1;
    int seed = 10;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState game, testGame;
    int k[10] = {adventurer, council_room, embargo, village, minion, mine,
        cutpurse, sea_hag, tribute, smithy};
    int treasureBefore = 0;
    int treasureAfter = 0;
    int card;
    int failedTests = 0;
    int totalTests = 0;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int iterations = 1000;
    int test1 = 0, test2 = 0, test3 = 0;

    printf("=== Random Testing: Adventurer Card ===\n");

    for (j = 1; j <= iterations; j++)
    {
        // initialized game
        initializeGame(numPlayers, k, seed, &game);

        // randomize game state
        randomizeHand(&game, k);
        randomizeDeck(&game, k);
        // copy the game state to a test case
        memcpy(&testGame, &game, sizeof(struct gameState));
    	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
        newCards = 2;

        // Test: Hand count + 2 - discarded
        totalTests++;
        if (testGame.handCount[thisPlayer] != game.handCount[thisPlayer] + newCards - discarded)
        {
            failedTests++;
            test1++;
        }

        // Test: Deck count - 2
        totalTests++;
        if ((testGame.deckCount[thisPlayer] + testGame.discardCount[thisPlayer])  != (game.deckCount[thisPlayer] + game.discardCount[thisPlayer] - newCards))
        {
            failedTests++;
            test2++;
        }

        // Test: Gained two treasure in hand
        for (i = 0; i < game.handCount[thisPlayer]; i++)
        {
            card = game.hand[thisPlayer][i];
            if (card == copper || card == silver || card == gold)
            {
                treasureBefore++;
            }
        }
        for (i = 0; i < testGame.handCount[thisPlayer]; i++)
        {
            card = testGame.hand[thisPlayer][i];
            if (card == copper || card == silver || card == gold)
            {
                treasureAfter++;
            }
        }
        totalTests++;
        if (treasureAfter != treasureBefore + newCards)
        {
            failedTests++;
            test3++;
        }
    }
    printf("[FAILED] Hand count test %d times.\n", test1);
    printf("[FAILED] Deck + Discard count test %d times.\n", test2);
    printf("[FAILED] Treasure in hand test %d times.\n", test3);
    printf("\n%d Iterations: Failed %d out of %d tests.\n", iterations, failedTests, totalTests);

	return 0;
}
