#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COINS 10

int max(int v1, int v2) {
	return v1 > v2 ? v1 : v2;
}

int min(int v1, int v2) {
	return v1 < v2 ? v1 : v2;
}

int max_coin(int* p1, int* p2) {
	if (p1 == p2) return 0;
	if (&p1[1] == p2) return max(p1[0], p2[0]);
	int left = min(max_coin(&p1[1], &p2[-1]), max_coin(&p1[2], p2)) + p1[0];
	int right = min(max_coin(p1, &p2[-2]), max_coin(&p1[1], &p2[-1])) + p2[0];
	return max(left, right);
}

int main() {
    srand(time(NULL));

    // seed coin array
    int* coins = malloc(sizeof(int) * COINS);
    int i;
    for (i = 0; i < COINS; i++) {
    	coins[i] = rand() % 10;
    	printf("%d ", coins[i]);
    }
    printf("\nMAX: %d", max_coin(coins, &coins[COINS-1]));
}