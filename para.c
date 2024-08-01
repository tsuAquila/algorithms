#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void swap_int(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int power_of_two(int exponent) { return 1 << exponent; }

struct ThreadArgs {
  int *a;
  int *b;
};

void *asc_sort(void *args) {
  struct ThreadArgs *int_args = (struct ThreadArgs *)args;
  if (*(int_args->a) > *(int_args->b)) {
    /* code */
  }
}

int main() {
  int q_pow = 3;
  int p_pow = 2;

  int size = power_of_two(q_pow);
  int p = power_of_two(p_pow);

  // printf("%d, %d", size, p);

  int seq_size = size - p;

  pthread_t threads[p];

  int k = q_pow - p_pow;

  for (size_t i = k; i > 0; i--) {
    /* code */
  }

  // pthread_create(&threads[0], NULL, add_nums, (void *)&arg);

  // pthread_join(threads[0], NULL);

  // printf("%d + %d = %d\n", arg.a, arg.b, arg.sum);

  // pthread_create(&thread_a, NULL, task_a, NULL);
  // pthread_create(&thread_b, NULL, task_b, NULL);
  // pthread_create(&thread_c, NULL, task_c, NULL);

  // pthread_join(thread_a, NULL);
  // pthread_join(thread_b, NULL);
  // pthread_join(thread_c, NULL);

  // int arr[] = {4, 9, 1, 1, 3, 1, 7, 4};
  // pthread_t threads[8];

  // for (int i = 0; i < 8; i += 2) {
  // }

  // printf("All tasks completed\n");

  return 0;
}