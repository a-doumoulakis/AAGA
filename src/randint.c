#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* We use Knuth & Lewis generator (from Seminumerical Algorithms) */
long m = 4294967296; // 2^32
long x_n;

void init_random() {
  x_n = time(NULL) % m;
}

long rand_int(long upper_bound) {
  int a = 1664525;
  int c = 1013904223;
  x_n = (a * x_n + c) % m;
  return x_n % upper_bound;
}


// int main(void) {
//   init_random();
//   for(int i = 0; i < 10; i++) {
//     printf("%ld \n", rand_int(100000L));
//   }
//   return EXIT_SUCCESS;
// }
