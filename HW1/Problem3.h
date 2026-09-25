/*!
    Problem 3: LRU Cache [20 points]
    Problem Description. An LRU (Least Recently Used) cache stores up to a fixed number (C)
    of key–value pairs. When the cache is full and a new key must be inserted, the least recently
    used key is evicted. On every successful access (read or write), that key becomes most recently
    used.
    In this problem, keys are integers in the range [0,K). We implement LRU without hashing by
    using: (1) a doubly linked list that maintains recency order (head = most recent, tail = least
    recent), and (2) an array directory dir[0..K − 1] that maps each key to its node (or nullptr
    if absent).
    The cache supports:
    • get(key) → returns the value if present (and moves key to the front), or “not found,”
    • put(key, val) → inserts/updates; if full and inserting a new key, evict the LRU (tail).
*/

#include <iostream>
using namespace std;

struct Node {
    int key, val;
    Node *prev, *next;
    Node(int k, int v): key(k), val(v), prev(nullptr), next(nullptr) {}
};

struct LRU {
    int cap; // capacity C
    int size; // current number of keys in cache
    int K; // key range upper bound (keys in [0, K))
    Node **dir; // array directory: dir[key] = Node* or nullptr
    Node *head; // most recently used (MRU)
    Node *tail; // least recently used (LRU)
    LRU(): cap(0), size(0), K(0), dir(nullptr), head(nullptr), tail(nullptr) {}
};

// Initialize the cache with capacity Ccap and key range K.
// Allocate dir on the heap and set all entries to nullptr.
void initLRU(LRU &C, int Ccap, int K);

// Return true and set outVal if present (and move node to MRU); else return false.
bool get(LRU &C, int key, int &outVal);

// Insert or update (key, val). If inserting and size==cap, evict LRU.
// Move the (possibly new) key to MRU position
void put(LRU &C, int key, int val);

// (Helpers students should implement/and may call from get/put)
// Remove node u from list in O(1).
void detach(LRU &C, Node *u);

// Insert node u at head (MRU) in O(1).
void pushFront(LRU &C, Node *u);

// Evict the LRU (tail) node in O(1); update dir and size; delete the node.
void evictLRU(LRU &C);