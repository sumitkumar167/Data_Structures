#include "Problem5.h"

int HKey[HM]; /* key */
int HFreq[HM]; /* frequency */

int HKFreq[TMAX];
int HKKey[TMAX];
int hkSize; /* current size */
int hkCap; /* capacity (set by hkInit) */

/* Initialize the hash table arrays (HKey <- HEMP, HFreq <- 0) */
void htabInit() {
    for (int i = 0; i < HM; i++) {
        HKey[i] = HEMP;
        HFreq[i] = 0;
    }
}

/* Increment frequency of x; insert x if absent; return index of x in table */
int htabInc(int x) {
    int idx = x % HM;
    for (int i = 0; i < HM; i++) {
        if (HKey[idx] == HEMP) {
            HKey[idx] = x;
            HFreq[idx] = 1;
            return idx;
        }
        else if (HKey[idx] == x) {
            HFreq[idx]++;
            return idx;
        }
        else {
            // Linear probing
            idx = (idx + 1) % HM;
        }
    }
    return -1; // table full
}

/* Find x; return index or -1 if not found */
int htabFind(int x)
 {
    int idx = x % HM;
    for (int i = 0; i < HM; i++) {
        if (HKey[idx] == HEMP)
            return -1; // Not found
        else if (HKey[idx] == x)
            return idx; // Found
        else{
            // Linear probing
            idx = (idx+1) % HM;
        }
    }
    return -1; // Not found
 }

/* Initialize heap capacity to K and reset size to 0 */
void hkInit(int K) {
    hkSize = 0;
    hkCap = K;
}

// 1 if pair at index a is smaller than pair at index b
int hkLess(int a, int b) {
    return HKFreq[a] < HKFreq[b] ||
           (HKFreq[a] == HKFreq[b] && HKKey[a] < HKKey[b]);
}

/* Heapify helpers */
void hkDown(int i) {
    if (i >= hkSize) return; // Index out of bounds

    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if (left < hkSize && hkLess(left, smallest)) smallest = left;
    if (right < hkSize && hkLess(right, smallest)) smallest = right;
    if (smallest != i) {
        swap(HKFreq[smallest], HKFreq[i]);
        swap(HKKey[smallest], HKKey[i]);
        hkDown(smallest);
    }
}

void hkUp(int i) {
    if (i == 0) return; // Already at root
    int parent = (i - 1) / 2;

    if (HKFreq[i] < HKFreq[parent] ||
        (HKFreq[i] == HKFreq[parent] && HKKey[i] < HKKey[parent])) {
        swap(HKFreq[i], HKFreq[parent]);
        swap(HKKey[i], HKKey[parent]);
        hkUp(parent); // Recursively heapify up
    }
}

/* Push (f,k) if size < hkCap; otherwise if (f, k) should be kept while root
is the smallest by (freq, key) ascending, replace root with (f,k) then heapify down.
Otherwise, do nothing. */
void hkPushOrReplace(int f, int k) {
    // If the heap is not full, append at end
    if (hkSize < hkCap) {
        HKFreq[hkSize] = f;
        HKKey[hkSize] = k;
        hkSize++;
        hkUp(hkSize - 1);
    }
    // If it is full, overwrite the root
    else if (f > HKFreq[0] ||
            (f == HKFreq[0] && k > HKKey[0])) {
        HKFreq[0] = f;
        HKKey[0] = k;
        hkDown(0);
    }
}

/* Pop the min pair (write to *pf, *pk); return 0 if empty, else 1 */
int hkPop(int *pf, int *pk) {
    if (hkSize == 0) return 0;

    *pf = HKFreq[0];
    *pk = HKKey[0];

    swap(HKFreq[0], HKFreq[hkSize-1]);
    swap(HKKey[0], HKKey[hkSize-1]);
    hkSize--;
    hkDown(0);
    return 1;
}

/* ---- Driver ----
Build the frequency table from arr[0..n-1], then feed exactly one (freq,key)
pair for each distinct key into the size-K heap using hkPushOrReplace.
Finally, pop up to K pairs into outKeys[] in descending frequency
(break ties by ascending key). Return the number of keys written (<= K). */
int topKFrequent(int arr[], int n, int K, int outKeys[]) {
    // Count every value
    htabInit();
    for (int i = 0; i < n; i++)
        htabInc(arr[i]);
    
    // feed 1 pair per distict key into heap
    hkInit(K);
    for (int i = 0; i < HM; i++) {
        if (HKey[i] != HEMP && HKey[i] != HDEL)
            hkPushOrReplace(HFreq[i], HKey[i]);
    }

    // pop everything
    static int tf[TMAX], tk[TMAX];
    int m = 0, f, k;
    while (hkPop(&f, &k)) {
        tf[m] = f;
        tk[m] = k;
        m++;
    }

    // insertion sort
    for (int a = 1; a < m; a++) {
        int cf = tf[a], ck = tk[a];
        int b = a - 1;
        while (b >= 0 && (tf[b] < cf || (tf[b] == cf && tk[b] > ck))) {
            tf[b + 1] = tf[b];
            tk[b + 1] = tk[b];
            b--;
        }
        tf[b + 1] = cf;
        tk[b + 1] = ck;
    }

    // 5) copy the keys out
    for (int i = 0; i < m; i++) {
        outKeys[i] = tk[i];
    }
    return m; 
}

/* ---- Expected program flow ---- */
int main() {
    int A[] = {1,1,1,2,2,3};
    int n = 6, K = 2, out[2];
    int count = topKFrequent(A, n, K, out);

    for (int i = 0; i < count; i++) {
        printf("%d ", out[i]);
    }
    printf("\n");
    return 0;
    return 0;
}