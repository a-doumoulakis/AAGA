#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* We use Knuth & Lewis generator (from Seminumerical Algorithms) */
long m = 4294967296; // 2^32
long x_n;
/*Will hold the number of random bits generated*/
long ran_bits = 0;

void init_random() {
  x_n = time(NULL) % m;
}

long rand_int(long upper_bound) {
  int a = 1664525;
  int c = 1013904223;
  x_n = (a * x_n + c) % m;
  ran_bits = ran_bits + (long)(ceil(log2(upper_bound)));
  return x_n % upper_bound;
}

long get_rand_bits(){
  return ran_bits;
}


// int main(void) {
//   init_random();
//   for(int i = 0; i < 10; i++) {
//     printf("%ld \n", rand_int(100000L));
//   }
//   return EXIT_SUCCESS;
// }
