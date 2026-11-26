#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
};

/* ---------- Min-Heap of Node* keyed by pointer->val ---------- */
extern Node* heap[]; // heap[0..heapSize-1]
extern int heapSize; // current number of elements

/* Swap two entries at indices i and j in heap[] */
void hSwap(int i, int j);

/* Return parent/children indices for a given i */
int hParent(int i); // (i - 1) / 2
int hLeft (int i); // 2*i + 1
int hRight (int i); // 2*i + 2

/* Push non-null pointer p into the min-heap */
void hPush(Node* p);

/* Pop from heap and return the smallest pointer; return nullptr if empty */
Node* hPop();

/* Heapify-down from index i within current heapSize */
void hDown(int i);

/* Heapify-up from index i within current heapSize */
void hUp(int i);

/* ---------- Merge driver ---------- */
/* Given heads[0..K-1], return head of merged list */
Node* mergeK(Node* heads[], int K);

