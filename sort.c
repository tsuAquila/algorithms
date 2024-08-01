#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BSTNode {
  int val;
  struct BSTNode *left;
  struct BSTNode *right;
  int count;
} BSTNode;

int *generate_random_array(int size, int min, int max) {
  int *arr = malloc(sizeof(int) * size);
  if (!arr) return NULL;

  srand((unsigned int)time(NULL));
  for (int i = 0; i < size; i++) {
    arr[i] = (rand() % (max - min + 1)) + min;
  }
  return arr;
}

void print_array(const int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubble_sort(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

void call_bubble_sort(int arr[], int size) { bubble_sort(arr, size); }

static void merge(int arr[], int start, int mid, int end) {
  int left_size = mid - start + 1;
  int right_size = end - mid;

  int left[left_size], right[right_size];

  for (int i = 0; i < left_size; i++) left[i] = arr[start + i];
  for (int j = 0; j < right_size; j++) right[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = start;

  while (i < left_size && j < right_size) {
    if (left[i] <= right[j]) {
      arr[k++] = left[i++];
    } else {
      arr[k++] = right[j++];
    }
  }

  while (i < left_size) arr[k++] = left[i++];
  while (j < right_size) arr[k++] = right[j++];
}

void merge_sort(int arr[], int start, int end) {
  if (start >= end) return;
  int mid = start + (end - start) / 2;
  merge_sort(arr, start, mid);
  merge_sort(arr, mid + 1, end);
  merge(arr, start, mid, end);
}

void call_merge_sort(int arr[], int size) { merge_sort(arr, 0, size - 1); }

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

static BSTNode *create_node(int val) {
  BSTNode *node = malloc(sizeof(BSTNode));
  if (node) {
    node->val = val;
    node->left = node->right = NULL;
    node->count = 1;
  }
  return node;
}

static BSTNode *insert(BSTNode *root, int val) {
  if (!root) return create_node(val);

  if (val == root->val) {
    root->count++;
  } else if (val < root->val) {
    root->left = insert(root->left, val);
  } else {
    root->right = insert(root->right, val);
  }
  return root;
}

static void inorder_traversal(BSTNode *root, int arr[], int *index) {
  if (!root) return;
  inorder_traversal(root->left, arr, index);
  for (int i = 0; i < root->count; i++) {
    arr[(*index)++] = root->val;
  }
  inorder_traversal(root->right, arr, index);
}

void bst_sort(int arr[], int size) {
  BSTNode *root = NULL;
  for (int i = 0; i < size; i++) {
    root = insert(root, arr[i]);
  }
  int index = 0;
  inorder_traversal(root, arr, &index);
  free_bst(root);  // faster without for obvious reasons
}

void free_bst(BSTNode *root) {
  if (root) {
    free_bst(root->left);
    free_bst(root->right);
    free(root);
  }
}

void call_bst_sort(int arr[], int size) { bst_sort(arr, size); }

void shuffle(int arr[], int size) {
  for (int i = size - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap(&arr[i], &arr[j]);
  }
  // print_array(arr, size);
}

bool is_sorted(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return false;
    }
  }
  return true;
}

void bogo_sort(int arr[], int size) {
  bool flag = false;
  while (!flag) {
    flag = is_sorted(arr, size);
    shuffle(arr, size);
  }
}

void call_bogo_sort(int arr[], int size) { bogo_sort(arr, size); }

void bitonic_sort(int arr[], int size) {}

int main() {
  const int SIZE = 16;
  const int MAX = 10;
  int *arr = generate_random_array(SIZE, 0, MAX);
  if (!arr) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }
  print_array(arr, SIZE);

  // bogo_sort(arr, SIZE);

  free(arr);
  return 0;
}