#include <iostream>
using namespace std;

#define BB 7 /* number of buckets */
#define C 2 /* inline capacity per bucket */
#define OF 11 /* overflow area size */
#define EMPTY -1
#define DEL -2

/* Storage */
extern int Buck[BB][C]; /* -1 empty; each bucket has C slots */
extern int OFA[OF]; /* -1 empty, -2 tombstone */

/* Hash to bucket [0..BB-1] */
int bh(int x); /* returns x % BB (non-negative) */

/* Overflow start index [0..OF-1] */
int ofStart(int x); /* returns (bh(x)) % OF */

/* Initialize Buck and OFA (EMPTY) */
void hyInit();

/* Insert x: first try Buck[b]; if full, place into OFA by linear probing
starting at ofStart(x); wrap modulo OF; return 1 if inserted, else 0 if OFA full */
int hyInsert(int x);

/* Search x: scan Buck[b]; if not found, linear probe OFA from ofStart(x)
until EMPTY encountered (not counting DEL as a stop); return 1 if found else 0 */
int hySearch(int x);

/* Optional: Delete x: if x in Buck[b], clear that inline slot to EMPTY.
Else, probe OFA and, if found, mark that slot DEL; return 1 if deleted else 0 */
int hyDelete(int x);

/* Optional: total number of OFA cells occupied (not EMPTY or DEL) */
int hyOFALength();

