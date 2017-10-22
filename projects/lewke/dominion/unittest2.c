/* -----------------------------------------------------------------------
 * Unit test for gainCard() function
 * Include the following lines in your makefile:
 *
 * unittest1: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i, j;  // loop counter
    int numPlayers = 2;
    int seed = 10;
    int k[10] = {adventurer, council_room, embargo, village, minion, mine,
        cutpurse, sea_hag, tribute, smithy};
    struct gameState game;
    int player = 0;
    int supplyPos = k[0];
    int toFlag = 0;
    int result;
    int failFlag = 0;
    int passedTests = 0;
    int totalTests = 0;
    int deckCount, handCount, discardCount;

    initializeGame(numPlayers, k, seed, &game);

    // Test Case 1: Card not in use
    for (i = curse; i <= treasure_map; i++)
    {
        result = gainCard(i, &game, toFlag, player);
        if (result == -1)
        {
            totalTests++;
            j = 0;
            printf("gainCard() test: Card %d not used", i);
            while (failFlag != 1 && j < 10)
            {
                if (i == k[j])
                {
                    printf(" [FAILED]\n");
                    failFlag = 1;
                }
                j++;
            }
            if (failFlag == 0)
            {
                printf(" [PASS]\n");
                passedTests++;
            }
        }
    }

    while (game.supplyCount[supplyPos] != 0)
    {
        // Test case toFlag = 0: add to discard
        discardCount = game.discardCount[player];
        result = gainCard(supplyPos, &game, 0, player);
        totalTests++;
        printf("gainCard() test: Discard card\n");
        printf("Expected discard: %d, Actual discard: %d\n", supplyPos, game.discard[player][discardCount]);
        if (game.discard[player][discardCount] == supplyPos)
        {
            printf("[PASS]\n");
            passedTests++;
        }
        else
        {
            printf("[FAILED]\n");
        }

        // Test case toFlag = 1: add to deck
        deckCount = game.deckCount[player];
        result = gainCard(supplyPos, &game, 1, player);
        totalTests++;
        printf("gainCard() test: Add card to deck\n");
        printf("Expected top of deck: %d, Actual top of deck: %d\n", supplyPos, game.deck[player][deckCount]);
        if (game.deck[player][deckCount] == supplyPos)
        {
            printf("[PASS]\n");
            passedTests++;
        }
        else
        {
            printf("[FAILED]\n");
        }

        // Test case toFlag = 2: add to hand
        handCount = game.handCount[player];
        result = gainCard(supplyPos, &game, 2, player);
        totalTests++;
        printf("gainCard() test: Add card to hand\n");
        printf("Expected hand: %d, Actual hand: %d\n", supplyPos, game.deck[player][deckCount]);
        if (game.hand[player][handCount] == supplyPos)
        {
            printf("[PASS]\n");
            passedTests++;
        }
        else
        {
            printf("[FAILED]\n");
        }
    }
    //Test Case: Supply pile is empty
    totalTests++;
    result = gainCard(supplyPos, &game, toFlag, player);
    printf("gainCard() test: Supply pile empty");
    if (result == -1)
    {
        printf(" [PASS]\n");
        passedTests++;
    }
    else
    {
        printf(" [FAILED]\n");
    }


    printf("Tests Passed: %d out of %d\n", passedTests, totalTests);

    return 0;
}
