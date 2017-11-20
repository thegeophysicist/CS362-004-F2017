/* -----------------------------------------------------------------------
 * Unit test for buyCard() function
 * Include the following lines in your makefile:
 *
 * unittest1: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int numPlayers = 2;
    int seed = 10;
    int k[10] = {adventurer, council_room, embargo, village, minion, mine,
        cutpurse, sea_hag, tribute, smithy};
    struct gameState game;
    int supplyCount, coinCount, discard, discardCount, handCount, deckCount, numBuys;
    int player = 0;
    int supplyPos = k[2];
    int result;
    int passedTests = 0;
    int totalTests = 0;

    initializeGame(numPlayers, k, seed, &game);

    // Test Case 1: No buys left
    totalTests++;
    game.numBuys = 0;
    result = buyCard(supplyPos, &game);
    printf("buyCard() test: No buys left\n");
    printf("Expected buys left: %d, Actual buys left: %d\n", 0, game.numBuys);
    if (result == -1)
    {
        printf("[PASS]\n");
        passedTests++;
    }
    else
    {
        printf("[FAILED]\n");
    }

    // Test Case 2: No more in supply pile
    result = 0;
    game.numBuys = 1;
    game.supplyCount[supplyPos] = 1;
    totalTests++;
    printf("buyCard() test: Supply pile of card %d is not empty\n", supplyPos);
    printf("Expected supplyCount: %d, Actual supplyCount: %d\n", 1, game.supplyCount[supplyPos]);
    if (game.supplyCount[supplyPos] > 0)
    {
        printf("[PASS]\n");
        passedTests++;
    }
    else
    {
        printf("[FAILED]\n");
    }
    result = buyCard(supplyPos, &game);  // buy last card

    // try to buy again
    game.numBuys = 1;
    result = buyCard(supplyPos, &game);
    totalTests++;
    printf("buyCard() test: Supply pile of card %d is empty\n", supplyPos);
    printf("Expected supplyCount: %d, Actual supplyCount: %d\n", 0, game.supplyCount[supplyPos]);
    if (result == -1)
    {
        printf("[PASS]\n");
        passedTests++;
    }
    else
    {
        printf("[FAILED]\n");
    }

    // Test Case 3: Not enough coins
    game.coins = 0;
    game.supplyCount[supplyPos] = 1;
    result = buyCard(supplyPos, &game);
    while (result == -1)
    {
        game.numBuys = 1;
        totalTests++;
        printf("buyCard() test: Not enough coins\n");
        printf("Expected coins: %d, Actual coins: %d\n", 2, game.coins);
        if (result == -1)
        {
            printf("[PASS]...Adding a coin, ");
            game.coins++;
            printf("Now coins = %d\n", game.coins);
            passedTests++;
        }
        else
        {
            printf("[FAILED]\n");
        }
        result = buyCard(supplyPos, &game);
    }

    // Test Case 4: Buying a card does not change unrelated game state
    initializeGame(numPlayers, k, seed, &game);
    // save before state
    supplyCount = game.supplyCount[supplyPos];
    coinCount = game.coins;
    discard = 0;
    discardCount = game.discardCount[player];
    handCount = game.handCount[player];
    deckCount = game.deckCount[player];
    numBuys = game.numBuys;
    // buy a card
    result = buyCard(supplyPos, &game);
    totalTests++;
    printf("buyCard() test: Buying card %d with cost of %d\n", supplyPos, 2);
    printf("Before supplyCount: %d, After supplyCount: %d\n", supplyCount, game.supplyCount[supplyPos]);
    printf("Before coinCount: %d, After coinCount: %d\n", coinCount, game.coins);
    printf("Before top of discard: %d, After top of discard: %d\n", discard, game.discard[player][0]);
    printf("Before discardCount: %d, After discardCount: %d\n", discardCount, game.discardCount[player]);
    printf("Before handCount: %d, After handCount: %d\n", handCount, game.handCount[player]);
    printf("Before deckCount: %d, After deckCount: %d\n", deckCount, game.deckCount[player]);
    printf("Before numBuys: %d, After numBuys: %d\n", numBuys, game.numBuys);

    if ((supplyCount - 1 == game.supplyCount[supplyPos])
        && (coinCount - 2 == game.coins)
        && (discard != game.discard[player][0])
        && (discardCount + 1 == game.discardCount[player])
        && (handCount == game.handCount[player])
        && (deckCount == game.deckCount[player])
        && (numBuys - 1 == game.numBuys))
    {
        printf("[PASS]\n");
        passedTests++;
    }
    else{
        printf("[FAILED]\n");
    }

    printf("Tests Passed: %d out of %d\n", passedTests, totalTests);

    return 0;
}
