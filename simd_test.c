#include <immintrin.h>
#include <stdio.h>
#include <time.h>

#define ARRAY_SIZE 230000000
#define ALIGN_TO 32

// Function to add arrays using SIMD
void add_arrays_simd(float* a, float* b, float* c, int size) {
  for (int i = 0; i < size; i += 4) {
    __m128 va = _mm_load_ps(&a[i]);
    __m128 vb = _mm_load_ps(&b[i]);
    __m128 vc = _mm_add_ps(va, vb);
    _mm_store_ps(&c[i], vc);
  }
}

// Function to add arrays without SIMD
void add_arrays_normal(float* a, float* b, float* c, int size) {
  for (int i = 0; i < size; i++) {
    c[i] = a[i] + b[i];
  }
}

int main() {
  float *a, *b, *c_simd, *c_normal;
  clock_t start, end;
  double cpu_time_used;

  // Allocate aligned memory
  a = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), ALIGN_TO);
  b = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), ALIGN_TO);
  c_simd = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), ALIGN_TO);
  c_normal = (float*)_mm_malloc(ARRAY_SIZE * sizeof(float), ALIGN_TO);

  // Initialize arrays
  for (int i = 0; i < ARRAY_SIZE; i++) {
    a[i] = (float)i;
    b[i] = (float)(ARRAY_SIZE - i);
  }

  // Perform addition using SIMD
  start = clock();
  add_arrays_simd(a, b, c_simd, ARRAY_SIZE);
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Time taken by SIMD function: %f seconds\n", cpu_time_used);

  // Perform addition without SIMD
  start = clock();
  add_arrays_normal(a, b, c_normal, ARRAY_SIZE);
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Time taken by normal function: %f seconds\n", cpu_time_used);

  // Verify results
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (c_simd[i] != c_normal[i]) {
      printf("Mismatch at index %d: SIMD = %f, Normal = %f\n", i, c_simd[i],
             c_normal[i]);
      break;
    }
  }

  // Free aligned memory
  _mm_free(a);
  _mm_free(b);
  _mm_free(c_simd);
  _mm_free(c_normal);

  return 0;
}