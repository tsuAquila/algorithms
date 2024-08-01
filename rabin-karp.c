#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generate_sample_string(int size) {
  char* string = (char*)malloc((size + 1) * sizeof(char));
  if (string == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  const char charset[] = "abcdefghijklmnopqrstuvwxyz";
  int charset_size = sizeof(charset) - 1;

  srand(time(NULL));

  for (int i = 0; i < size; i++) {
    string[i] = charset[rand() % charset_size];
  }
  string[size] = '\0';

  return string;
}

int rabin_carp_matcher(char string[], int string_size, char pattern[],
                       int pattern_size, int prime, int base) {
  //   clock_t start, end;
  //   double cpu_time_used;

  //   start = clock();

  int pattern_hash = 0, string_hash = 0;
  int h = 1;

  for (int i = 0; i < pattern_size - 1; i++) h = (h * base) % prime;

  for (int i = 0; i < pattern_size; i++) {
    pattern_hash = (base * pattern_hash + pattern[i]) % prime;
    string_hash = (base * string_hash + string[i]) % prime;
  }

  for (int i = 0; i <= string_size - pattern_size; i++) {
    if (string_hash == pattern_hash) {
      int j;
      for (j = 0; j < pattern_size; j++) {
        if (string[i + j] != pattern[j]) break;
      }
      if (j == pattern_size) {
        // end = clock();
        // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        // printf("Time taken by Rabin-Karp algorithm: %f seconds\n",
        //        cpu_time_used);
        return i;
      }
    }

    if (i < string_size - pattern_size) {
      string_hash =
          (base * (string_hash - string[i] * h) + string[i + pattern_size]) %
          prime;
      if (string_hash < 0) string_hash += prime;
    }
  }

  //   end = clock();
  //   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  //   printf("Time taken by Rabin-Karp algorithm: %f seconds\n",
  //   cpu_time_used);

  return -1;
}



int main() {
  char pattern[] = {'a', 'b', 'c', 'd', '\0'};

  int size = INT_MAX - 1;

  printf("Generating Sample String\n");
  char* string = generate_sample_string(size);
  printf("Generation Complete\n");

  printf("%d",
         rabin_carp_matcher(string, size, pattern, strlen(pattern), 997, 256));

  return 0;
}