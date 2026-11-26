#include <iostream>
using namespace std;

// m value for modulus
#define PM 7

/* Fixed static set */
extern int Keys[4]; /* = Example: {10,22,37,40} */

/* Return 1 if h_{a,b}(x) = (a*x + b) % PM maps Keys injectively into [0..PM-1];
otherwise return 0. */
// Check whether all keys are collision free under the hash function defined by a and b
int isPerfect(int a, int b);

/* Brute-force search over 0 <= a,b < PM. If a perfect pair exists,
write it via *pa and *pb and return 1; else return 0. */
// Try different values of a and b to find a perfect hash function for the given keys
int findPerfect(int *pa, int *pb);

/* Build table hash_table[PM] with -1 for empty; place each key x at hash_table[h_{a,b}(x)]. */
// Places all keys into the perfect hash table
void buildPerfect(int a, int b, int hash_table[]);

/* Search key x in hash_table using the same h_{a,b}; return index in [0..PM-1] or -1. */
// Searches for a key using its hash index
int pSearch(int a, int b, int hash_table[], int x);

