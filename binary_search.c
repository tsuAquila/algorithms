#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
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

int random_number_from_array(int *arr, int size) {
  int random_index = rand() % size;
  return arr[random_index];
}

static int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return i + 1;
}

void quick_sort(int arr[], int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
  }
}

void call_quick_sort(int arr[], int size) { quick_sort(arr, 0, size - 1); }

int binarySearch(int arr[], int size, int target) {
  int left = 0;
  int right = size - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
      return mid;
    }

    if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1;
}

int main() {
  int size = 100000000;
  int max = INT_MAX - 1;

  int *arr = generate_random_array(size, 0, max);

  call_quick_sort(arr, size);

  int elt = random_number_from_array(arr, size);
  int res = binarySearch(arr, size, elt);

  if (res != -1) {
    printf("%d found at %d\n", elt, res);
  }

  return 0;
}