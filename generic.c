#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_array(const int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int *generate_random_array(int size, int min, int max) {
  int *arr = malloc(sizeof(int) * size);
  if (!arr) return NULL;

  srand((unsigned int)time(NULL));
  for (int i = 0; i < size; i++) {
    arr[i] = (rand() % (max - min + 1)) + min;
  }
  return arr;
}