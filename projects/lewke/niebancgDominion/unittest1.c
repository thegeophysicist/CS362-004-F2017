/* -----------------------------------------------------------------------
 * Unit test for isGameover() function
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
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
    struct gameState game;
    int result;
    int passedTests = 0;
    int totalTests = 0;

    // Test Case 1: newly initialized game
    initializeGame(numPlayers, k, seed, &game);
    totalTests++;
    result = isGameOver(&game);
    printf("isGameOver() test: Create new game - Game is not over\n");
    printf("Expected result: %d, Actual result: %d\n", 0, result);
    if (result == 0)
    {
        printf("[PASS]\n");
        passedTests++;
    }
    else
    {
        printf("[FAILED]\n");
    }

    // Test Case 2: province pile is empty
    initializeGame(numPlayers, k, seed, &game);
    game.supplyCount[province] = 0;
    totalTests++;
    result = isGameOver(&game);
    printf("isGameOver() test: Province pile empty - Game is over\n");
    printf("Expected result: %d, Actual result: %d\n", 1, result);
    if (result == 1)
    {
        printf("[PASS]\n");
        passedTests++;
    }
    else
    {
        printf("[FAILED]\n");
    }

    // Test Case 3: First three supply piles are empty
    initializeGame(numPlayers, k, seed, &game);
    i = 0;
    do
    {
        totalTests++;
        result = isGameOver(&game);
        printf("isGameOver() test: Front %d Supply pile(s) empty - Game is not over\n", i);
        printf("Expected result: %d, Actual result: %d\n", 0, result);
        if (result == 0)
        {
            printf("[PASS]\n");
            passedTests++;
        }
        else
        {
            printf("[FAILED]\n");
        }
        game.supplyCount[i] = 0;
        i++;
    } while (i < 3);
    totalTests++;
    result = isGameOver(&game);
    printf("isGameOver() test: Front %d Supply pile(s) empty - Game is over\n", i);
    printf("Expected result: %d, Actual result: %d\n", 1, result);
    if (i >= 3 && result == 1)
    {
        printf("[PASS]\n");
        passedTests++;
    }
    else
    {
        printf("[FAILED]\n");
    }

    // Test Case 4: Last three supply piles are empty
    initializeGame(numPlayers, k, seed, &game);
    i = 0;
    do
    {
        totalTests++;
        result = isGameOver(&game);
        printf("isGameOver() test: Back %d Supply pile(s) empty - Game is not over\n", i);
        printf("Expected result: %d, Actual result: %d\n", 0, result);
        if (result == 0)
        {
            printf("[PASS]\n");
            passedTests++;
        }
        else
        {
            printf("[FAILED]\n");
        }
        game.supplyCount[treasure_map - i] = 0;
        i++;
    } while (i < 3);
    totalTests++;
    result = isGameOver(&game);
    printf("isGameOver() test: Back %d Supply pile(s) empty - Game is over\n", i);
    printf("Expected result: %d, Actual result: %d\n", 1, result);
    if (i >= 3 && result == 1)
    {
        printf("[PASS]\n");
        passedTests++;
    }
    else
    {
        printf("[FAILED]\n");
    }

    printf("Tests Passed: %d out of %d\n", passedTests, totalTests);

    return 0;
}
