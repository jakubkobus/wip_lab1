#include <stdio.h>
#include <stdlib.h>

#define GUESS_SIZE  4
#define GUESS_MIN   1
#define GUESS_MAX   6

#define GUESS_RANGE (GUESS_MAX - GUESS_MIN + 1)

typedef struct CompareResult {
  int hits;
  int misplaced;
} CompareResult;

CompareResult compare(int *correct, int *guess) {
  int hits = 0, misplaced = 0, i;
  int countCorrect[GUESS_RANGE];
  int countGuess[GUESS_RANGE];

  for(i = 0; i < GUESS_RANGE; i++) {
    countCorrect[i] = 0;
    countGuess[i] = 0;
  }

  for(i = 0; i < GUESS_SIZE; i++)
    if(correct[i] == guess[i])
      hits++;
    else {
      countCorrect[correct[i] - GUESS_MIN]++;
      countGuess[guess[i] - GUESS_MIN]++;
    }

  for(i = 0; i < GUESS_RANGE; i++)
    misplaced += (countCorrect[i] < countGuess[i]) ? countCorrect[i] : countGuess[i];

  return (CompareResult){ hits, misplaced };
}

void generateCombination(int index, int *combination) {
  for(int i = GUESS_SIZE - 1; i >= 0; i--) {
    combination[i] = GUESS_MIN + (index % GUESS_RANGE);
    index /= GUESS_RANGE;
  }
}

int main() {
  int totalCombinations = 1, i;
  int guess[GUESS_SIZE];
  int hits = 0, attempt = 1, misplaced;

  for(i = 0; i < GUESS_SIZE; i++) {
    totalCombinations *= GUESS_RANGE;
    guess[i] = GUESS_MIN;
  }

  int *validIndexes = malloc(totalCombinations * sizeof(int));
  for(i = 0; i < totalCombinations; i++)
    validIndexes[i] = i;

  int validCount = totalCombinations, newValidCount;
  int currentCombination[GUESS_SIZE];
  while(hits != GUESS_SIZE) {
    printf("%d: ", attempt++);
    for(i = 0; i < GUESS_SIZE; i++)
      printf("%d ", guess[i]);
    printf("?\n");

    printf("Na swoim miejscu: ");
    scanf("%d", &hits);
    printf("Nie na swoim miejscu: ");
    scanf("%d", &misplaced);

    newValidCount = 0;
    for(i = 0; i < validCount; i++) {
      generateCombination(validIndexes[i], currentCombination);

      CompareResult result = compare(currentCombination, guess);
      if(result.hits == hits && result.misplaced == misplaced)
        validIndexes[newValidCount++] = validIndexes[i];
    }

    if(validCount == 0) {
      printf("Oszukujesz!\n");
      break;
    }

    validCount = newValidCount;
    generateCombination(validIndexes[0], guess);
  }

  if(hits == GUESS_SIZE && validCount > 0)
    printf("Wygralem.\n");

  free(validIndexes);
  return 0;
}
