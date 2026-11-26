#include "Problem3.h"

int Buck[BB][C];
int OFA[OF];

/* 
  Hash to bucket [0..BB-1]
  returns x % BB (non-negative) 
*/
int bh(int x) {
    return (x % BB);
}

/* Overflow start index [0..OF-1] */
/* returns (bh(x)) % OF */
int ofStart(int x) {
    return (bh(x) % OF);
}

/* Initialize Buck and OFA (EMPTY) */
void hyInit() {
    for (int i = 0; i < BB; i++)
        for (int j = 0; j < C; j++)
            Buck[i][j] = EMPTY;
    
    for (int i = 0; i < OF; i++)
        OFA[i] = EMPTY;
}

/* Insert x: first try Buck[b]; if full, place into OFA by linear probing
starting at ofStart(x); wrap modulo OF; return 1 if inserted, else 0 if OFA full */
int hyInsert(int x) {
    int b = bh(x);

    // First try to insert in the bucket
    for (int j = 0; j < C; j++) {
        if (Buck[b][j] == x) {
            return 0; // Already exists
        }
        if (Buck[b][j] == EMPTY) {
            Buck[b][j] = x;
            return 1; // Inserted successfully
        }
    }

    // If bucket is full, try to insert in the overflow area
    int start = ofStart(x);
    int firstDeletedIndex = -1;

    for (int k = 0; k < OF; k++) {
        int idx = (start + k) % OF;

        if (OFA[idx] == x)
            return 0; // Already exists
        
        if (OFA[idx] == DEL && firstDeletedIndex == -1)
            firstDeletedIndex = idx; // Remember the first deleted slot
        
        if (OFA[idx] == EMPTY) {
            if (firstDeletedIndex != -1) 
               idx = firstDeletedIndex; // Use the first deleted slot if available
            
            OFA[idx] = x;
            return 1; // Inserted successfully
        }
    }

    // If no empty slot was found, check if we can use a deleted slot
    if (firstDeletedIndex != -1) {
        OFA[firstDeletedIndex] = x;
        return 1; // Inserted successfully
    }

    return 0; // Failed to insert
}

/* Search x: scan Buck[b]; if not found, linear probe OFA from ofStart(x)
until EMPTY encountered (not counting DEL as a stop); return 1 if found else 0 */
int hySearch(int x) {
    int b = bh(x);

    // Search in the bucket first
    for (int j = 0; j < C; j++) {
        if (Buck[b][j] == x) return 1; // Found in bucket
    }

    // If not found in bucket, search in the overflow area
    int start = ofStart(x);

    for (int k = 0; k < OF; k++) {
        int idx = (start + k) % OF;

        if (OFA[idx] == EMPTY) return 0; // Not found, stop searching
        if (OFA[idx] == x) return 1; // Found in overflow area
    }
    return 0; // Not found
}

/* Optional: Delete x: if x in Buck[b], clear that inline slot to EMPTY.
Else, probe OFA and, if found, mark that slot DEL; return 1 if deleted else 0 */
int hyDelete(int x);

/* Optional: total number of OFA cells occupied (not EMPTY or DEL) */
int hyOFALength();



int main() {
    int keys[] = {23,43,13,27,5,25,15,35};
    int i, n = 8;
    hyInit();
    for (i = 0; i < n; i++) hyInsert(keys[i]);
    // print buckets and OFA; test a few searches and deletes
    for (i = 0; i < BB; i++) {
        cout << "Bucket " << i << ": ";
        for (int j = 0; j < C; j++) {
            if (Buck[i][j] == EMPTY) cout << "EMPTY ";
            else cout << Buck[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Overflow Area: ";
    for (i = 0; i < OF; i++) {
        cout << "OFA[" << i << "] = ";

        if (OFA[i] == EMPTY) cout << "EMPTY ";
        else if (OFA[i] == DEL) cout << "DEL ";
        else cout << OFA[i] << " ";

        cout << endl;
    }

    // cout << "Search for 25: " << (hySearch(25) ? "Found" : "Not Found") << endl;
    // cout << "Search for 100: " << (hySearch(100) ? "Found" : "Not Found") << endl;
    return 0;
}