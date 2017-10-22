/* -----------------------------------------------------------------------
 * Unit test for getCost() function
 * Include the following lines in your makefile:
 *
 * unittest1: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i;  // loop counter
    int numPlayers = 2;
    int seed = 10;
    int k[10] = {adventurer, council_room, embargo, village, minion, mine,
        cutpurse, sea_hag, tribute, smithy};
    int c[treasure_map + 1] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
    struct gameState game;
    int cost;
    int passedTests = 0;
    int totalTests = 0;

    initializeGame(numPlayers, k, seed, &game);

    printf("getCost() test: Get card cost\n");
    for (i = curse; i <= treasure_map; i++)
    {
        cost = getCost(i);
        totalTests++;
        printf("Card %d: Expected cost: %d, Actual cost: %d ", i, c[i], cost);
        if (cost == c[i])
        {
            printf(" [PASS]\n");
            passedTests++;
        }
        else
        {
            printf(" [FAILED]\n");
        }
    }

    printf("getCost() test: Get cost of invalid card number (-1)\n");
    cost = getCost(-1);
    totalTests++;
    printf("Card %d: Expected cost: %d, Actual cost: %d ", -1, -1, cost);
    if (cost == -1)
    {
        printf(" [PASS]\n");
        passedTests++;
    }
    else
    {
        printf(" [FAILED]\n");
    }

    printf("getCost() test: Get cost of invalid card number (27)\n");
    cost = getCost(27);
    totalTests++;
    printf("Card %d: Expected cost: %d, Actual cost: %d ", 27, -1, cost);
    if (cost == -1)
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
