#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void print_scheduling_pattern(int rq[], int n) {
  printf("Scheduling Pattern: ");
  for (int i = 0; i < n; i++) {
    printf("%d\t", rq[i]);
  }
  printf("\n");
}

void print_total_head_movement(int total_head_movement) {
  printf("Total Head Movement is %d.\n", total_head_movement);
}

void evaluate_requests(int rq[], int n, int block_size) {
  for (int i = 0; i < n; i++) {
    if (rq[i] > block_size) {
      printf("Error %d is greater than disk size %d.\n", rq[i], block_size);
      return;
    }
  }
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

int find_initial_position(int rq[], int initial, int n) {
  for (int i = 0; i < n; i++) {
    if (rq[i] == initial) {
      return i;
    }
  }
  return -1;
}

void fcfs(int rq[], int n) {
  printf("\nFCFS\n");

  int total_head_movement = 0;
  for (int i = 1; i < n; i++) {
    total_head_movement += abs(rq[i] - rq[i - 1]);
  }

  print_scheduling_pattern(rq, n);
  print_total_head_movement(total_head_movement);
}

void scan(int rq[], int initial, int size, int n) {
  printf("\nSCAN\n");

  int move, index, total_head_movement = 0;
  printf("Enter the head movement direction for high 1 and for low 0: ");
  scanf("%d", &move);

  call_quick_sort(rq, n);
  index = find_initial_position(rq, initial, n);

  printf("Scheduling Pattern:");
  if (move == 1) {
    for (int i = index; i < n; i++) printf("\t%d", rq[i]);
    printf("\t%d", size - 1);
    for (int i = index - 1; i >= 0; i--) printf("\t%d", rq[i]);

    total_head_movement = (size - 1) * 2 - rq[0] - initial;
  } else if (move == 0) {
    for (int i = index; i >= 0; i--) printf("\t%d", rq[i]);
    printf("\t%d", 0);
    for (int i = index + 1; i < n; i++) printf("\t%d", rq[i]);

    total_head_movement = rq[n - 1] + initial;
  }

  printf("\n");
  print_total_head_movement(total_head_movement);
}

void cscan(int rq[], int initial, int size, int n) {
  printf("\nC-SCAN\n");

  int move, index, total_head_movement = 0;
  printf("Enter the head movement direction for high 1 and for low 0: ");
  scanf("%d", &move);

  call_quick_sort(rq, n);
  index = find_initial_position(rq, initial, n);

  printf("Scheduling Pattern:");
  if (move == 1) {
    for (int i = index; i < n; i++) printf("\t%d", rq[i]);
    printf("\t%d\t%d", size - 1, 0);
    for (int i = 0; i <= index - 1; i++) printf("\t%d", rq[i]);

    total_head_movement = (size - 1) * 2 - (rq[index] - rq[index - 1]);
  } else if (move == 0) {
    for (int i = index; i >= 0; i--) printf("\t%d", rq[i]);
    printf("\t%d\t%d", 0, size - 1);
    for (int i = n - 1; i >= index + 1; i--) printf("\t%d", rq[i]);

    total_head_movement = (size - 1) * 2 - (rq[index + 1] - rq[index]);
  }

  printf("\n");
  print_total_head_movement(total_head_movement);
}

void get_input(int rq[], int* n, int* size, int* initial) {
  printf("Enter the number of Requests: ");
  scanf("%d", n);

  printf("Enter the total disk size: ");
  scanf("%d", size);

  printf("Enter the initial Head Position: ");
  scanf("%d", initial);
  rq[0] = *initial;

  printf("Enter the Requests Sequence:\n");
  for (int i = 1; i <= *n; i++) {
    scanf("%d", &rq[i]);
  }
  return evaluate_requests(rq, n, size);
}

void print_menu() {
  printf("\nEnter your choice:\n");
  printf("1. FCFS\n");
  printf("2. SCAN\n");
  printf("3. C-SCAN\n");
  printf("0. Exit\n");
}

int main() {
  printf("Disk Scheduling\n");

  int rq[100], n, initial, size;
  get_input(rq, &n, &size, &initial);

  int choice;
  while (1) {
    print_menu();
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        fcfs(rq, n + 1);
        break;
      case 2:
        scan(rq, initial, size, n + 1);
        break;
      case 3:
        cscan(rq, initial, size, n + 1);
        break;
      case 0:
        return 0;
      default:
        printf("Invalid choice\n");
        break;
    }
  }
  return 0;
}