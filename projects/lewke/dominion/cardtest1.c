/* -----------------------------------------------------------------------
 * Unit test for smithy card effect
 * Include the following lines in your makefile:
 *
 * unittest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    int i, j;  // loop counter
    int newCards = 0;
    int discarded = 1;
    int seed = 10;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState game, testGame;
    int k[10] = {adventurer, council_room, embargo, village, minion, mine,
        cutpurse, sea_hag, tribute, smithy};
    int failFlag = 0;
    int passedTests = 0;
    int totalTests = 0;
    int testHand[5] = {smithy, adventurer, gold, gold, gold};
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    // initialized game
    initializeGame(numPlayers, k, seed, &game);
    // load test hand
    for (i = 0; i < game.handCount[thisPlayer]; i++)
    {
        game.hand[thisPlayer][i] = testHand[i];
    }

    // Test Case:  Draw three cards
    printf("Smithy Card: Draw three cards, then discard Smithy - Card %d\n", smithy);
	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
    newCards = 3;

    // Test: Hand count + 3 - discarded
	printf("Hand count: Previous = %d, Current = %d, Expected = %d", game.handCount[thisPlayer], testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards - discarded);
    totalTests++;
    if (testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards - discarded)
    {
        printf(" [PASS]\n");
        passedTests++;
    }
    else
    {
        printf(" [FAILED]\n");
    }

    // Test: Deck count - 3
    printf("Deck count: Previous = %d, Current = %d, Expected = %d", game.deckCount[thisPlayer], testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards);
    totalTests++;
    if (testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards)
    {
        printf(" [PASS]\n");
        passedTests++;
    }
    else
    {
        printf(" [FAILED]\n");
    }

    // Test: Played cards + 1
    printf("Played count: Previous = %d, Current = %d, Expected = %d", game.playedCardCount, testGame.playedCardCount, game.playedCardCount + discarded);
    totalTests++;
    if (testGame.playedCardCount == game.playedCardCount + discarded)
    {
        printf(" [PASS]\n");
        passedTests++;
    }
    else
    {
        printf(" [FAILED]\n");
    }

    // Test: Played card is Smithy
    printf("Played Card: Previous = %d, Current = %d, Expected = %d", game.playedCards[0], testGame.playedCards[0], smithy);
    totalTests++;
    if (testGame.playedCards[0] == smithy)
    {
        printf(" [PASS]\n");
        passedTests++;
    }
    else
    {
        printf(" [FAILED]\n");
    }

    // Show previous and current hands
    printf("Previous hand: ");
    for (i = 0; i < game.handCount[thisPlayer]; i++)
        printf("%d ", game.hand[thisPlayer][i]);
    printf("Current hand: ");
    for (i = 0; i < testGame.handCount[thisPlayer]; i++)
        printf("%d ", testGame.hand[thisPlayer][i]);
    printf("\n");

    // Test: No change to other players' states
    printf("Checking other players...\n");
	printf("Hand count: Previous = %d, Current = %d, Expected = %d", game.handCount[otherPlayer], testGame.handCount[otherPlayer], game.handCount[otherPlayer]);
    totalTests++;
    if (testGame.handCount[otherPlayer] == game.handCount[otherPlayer])
    {
        printf(" [PASS]\n");
        passedTests++;
    }
    else
    {
        printf(" [FAILED]\n");
    }
    printf("Deck count: Previous = %d, Current = %d, Expected = %d", game.deckCount[otherPlayer], testGame.deckCount[otherPlayer], game.deckCount[otherPlayer]);
    totalTests++;
    if (testGame.deckCount[otherPlayer] == game.deckCount[otherPlayer])
    {
        printf(" [PASS]\n");
        passedTests++;
    }
    else
    {
        printf(" [FAILED]\n");
    }

    // Test: No change to victory and kingdom piles
    printf("Checking victory and kingdom piles...\n");
    totalTests++;
    for (i = curse; i <= gold; i++)
    {
        if (testGame.supplyCount[i] != game.supplyCount[i])
        {
            failFlag = 1;
            printf("Supply pile %d: Previous = %d, Current = %d, Expected = %d\n", i, game.supplyCount[i], testGame.supplyCount[i], game.supplyCount[i]);
        }
    }
    for (j = 0; j < 10; j++)
    {
        if (testGame.supplyCount[k[j]] != game.supplyCount[k[j]])
        {
            failFlag = 1;
            printf("Supply pile %d: Previous = %d, Current = %d, Expected = %d\n", i, game.supplyCount[k[j]], testGame.supplyCount[k[j]], game.supplyCount[k[j]]);
        }
    }
    printf("Supply piles did not change");
    if (failFlag)
    {
        printf(" [FAILED]\n");
    }
    else
    {
        printf(" [PASS]\n");
        passedTests++;
    }

    printf("Tests Passed: %d out of %d\n", passedTests, totalTests);

	return 0;
}
