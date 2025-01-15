#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int getFirstLine(const char *filename) {
  FILE *f = fopen(filename, "r");
  if(f == NULL) {
    perror("File does not exist");
    return INT_MAX;
  }
  
  int res;
  if(fscanf(f, "%d", &res) == 1) {
    fclose(f);
    return res;
  }
  
  fclose(f);
  return INT_MAX;
}

void readFileToArray(const char *filename, int *array) {
  FILE *f = fopen(filename, "r");
  if(f == NULL) {
    perror("File does not exist");
    return;
  }

  int i = 0;
  int flag = 0;
  while(fscanf(f, "%d", &array[i]) == 1)
    if(flag) i++;
    else flag = 1;
}

void change(int *coins, int n, int r) {
  int *C = malloc((r + 1) * sizeof(int));
  int *D = malloc((r + 1) * sizeof(int));

  for(int i = 0; i <= r; i++) {
    C[i] = -1;
    D[i] = -1;
  } C[0] = 0;

  for(int i = 1; i <= r; i++)
    for(int j = 0; j < n; j++)
      if(coins[j] >= i && C[i - coins[j]] != -1) {
        if(C[i] > C[i - coins[j]] + 1)
          C[i] = C[i - coins[j]] + 1;
        if(C[i] != -1)
          D[i] = coins[j];
      }
      
  if(C[r] == -1) {
    printf("%d ==> No solution!\n", r);
  } else {
    printf("%d ==> %d\n", r, C[r]);
    int *res = calloc(n, sizeof(int));
    int left = r, idx;
    while(left > 0) {
      idx = D[left];
      res[idx]++;
      left -= coins[idx];
    }
    for(int i = 0; i < n; i++)
      if(res[i] > 0)
        printf("\t%d x %d\n", coins[i], res[i]);
    free(res);
  }

  free(C);
  free(D);
}

int main(int argc, char *argv[]) {
  const char *filename = argv[1];
  
  int coinsCount = getFirstLine(filename);
  int coins[coinsCount];
  readFileToArray(filename, coins);
  
  int inputCount = argc - 2;
  int r[inputCount];
  for(int i = 2; i < inputCount + 2; i++)
    change(coins, coinsCount, atoi(argv[i]));

  return 0;
}
