#include <iostream>
using namespace std;

/* ---- Hash table for frequency: linear probing ---- */
#define HM 20011 /* capacity */
#define HEMP -1 /* empty marker */
#define HDEL -2 /* tombstone marker */

extern int HKey[HM]; /* key */
extern int HFreq[HM]; /* frequency */

/* Initialize the hash table arrays (HKey <- HEMP, HFreq <- 0) */
void htabInit();

/* Increment frequency of x; insert x if absent; return index of x in table */
int htabInc(int x);

/* Find x; return index or -1 if not found */
int htabFind(int x);

/* ---- Min-Heap of (freq,key) with capacity K ---- */
#define TMAX 10005

extern int HKFreq[TMAX];
extern int HKKey[TMAX];
extern int hkSize; /* current size */
extern int hkCap; /* capacity (set by hkInit) */

/* Initialize heap capacity to K and reset size to 0 */
void hkInit(int K);

/* Push (f,k) if size < hkCap; otherwise if (f, k) should be kept while root
is the smallest by (freq, key) ascending, replace root with (f,k) then heapify down.
Otherwise, do nothing. */
void hkPushOrReplace(int f, int k);

/* Pop the min pair (write to *pf, *pk); return 0 if empty, else 1 */
int hkPop(int *pf, int *pk);

/* Heapify helpers */
void hkDown(int i);
void hkUp(int i);

// 1 if pair at index a is smaller than pair at index b
int hkLess(int a, int b);

/* ---- Driver ----
Build the frequency table from arr[0..n-1], then feed exactly one (freq,key)
pair for each distinct key into the size-K heap using hkPushOrReplace.
Finally, pop up to K pairs into outKeys[] in descending frequency
(break ties by ascending key). Return the number of keys written (<= K). */
int topKFrequent(int arr[], int n, int K, int outKeys[]);

