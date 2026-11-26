#include "Problem4.h"

int Keys[4] = {10,22,37,40};

/* Return 1 if h_{a,b}(x) = (a*x + b) % PM maps Keys injectively into [0..PM-1];
otherwise return 0. */
// Check whether all keys are collision free under the hash function defined by a and b
int isPerfect(int a, int b) {
    int used[PM] = {0}; // Initialize all slots to 0 (not used)

    for (int i = 0; i < 4; i++) {
        int idx = (a * Keys[i] + b) % PM;

        if (used[idx])  return 0; // Collision detected

        used[idx] = 1; // Mark this index as used
    }
    return 1; // No collisions, perfect mapping
}

/* Brute-force search over 0 <= a,b < PM. If a perfect pair exists,
write it via *pa and *pb and return 1; else return 0. */
// Try different values of a and b to find a perfect hash function for the given keys
int findPerfect(int *pa, int *pb) {
    for (int a = 0; a < PM; a++) {
        for (int b = 0; b < PM; b++) {
            if (isPerfect(a, b)) {
                *pa = a;
                *pb = b;
                return 1; // Found a perfect pair
            }
        }
    }
    return 0; // No pair found
}

/* Build table hash_table[PM] with -1 for empty; place each key x at hash_table[h_{a,b}(x)]. */
// Places all keys into the perfect hash table
void buildPerfect(int a, int b, int hash_table[]) {
    for (int i = 0; i < PM; i++)
        hash_table[i] = -1; // Initialize all slots to -1 (empty)
    
    for (int i = 0; i < 4; i++) {
        int idx = (a * Keys[i] + b) % PM;
        hash_table[idx] = Keys[i]; // Place key at its hashed index
    }
}

/* Search key x in hash_table using the same h_{a,b}; return index in [0..PM-1] or -1. */
// Searches for a key using its hash index
int pSearch(int a, int b, int hash_table[], int x) {
    int idx = (a*x + b) % PM;

    if (hash_table[idx] == x) 
        return idx; // Found at index idx
    else
        return -1; // Not found
}

/* ------------- The template for main() -------------
*/
int main() {
    int a, b, ok;
    int hash_table[PM];
    ok = findPerfect(&a, &b);
    /* assert ok == 1 */
    if (!ok) {
        cout << "No perfect hash function found." << endl;
        return 0;
    }

    cout << "Perfect hash function found: a = " << a << ", b = " << b << endl;
    buildPerfect(a, b, hash_table);
    /* test: pSearch(a,b,hash_table,22), pSearch(a,b,hash_table,37), ... */
    cout << "\n Hash Table: \n";
    for (int i = 0; i < PM; i++) 
        cout << "hash_table[" << i << "] = " << hash_table[i] << endl;
    
    cout << "\n Search Tests: \n";
    cout << "Searching for 22: Index = " << pSearch(a, b, hash_table, 22) << endl;
    cout << "Searching for 37: Index = " << pSearch(a, b, hash_table, 37) << endl;
    cout << "Searching for 10: Index = " << pSearch(a, b, hash_table, 10) << endl;
    cout << "Searching for 40: Index = " << pSearch(a, b, hash_table, 40) << endl;
    cout << "Searching for 99: Index = " << pSearch(a, b, hash_table, 99) << endl; // Not in Keys
    return 0;
}