#include <iostream>
using namespace std;

int leftChild(int i);
int rightChild(int i);

/* Restore Max-Heap property by heapifying down from index i only.
Arguments: array C[0..cN-1], heap size cN, start index i. */
void maxHeapifyFrom(int C[], int cN, int i);

/* Return 1 if Max-Heap property holds at index i (i.e., children <= C[i]),
otherwise return 0. Only checks local condition at i. */
int holdsAt(int C[], int cN, int i);

/* Return 1 if the entire array C[0..cN-1] satisfies the Max-Heap property,
otherwise return 0. */
int isMaxHeap(int C[], int cN);

void swapInt(int* a, int* b);

// -1 if no children
int largerChildIndex(int C[], int cN, int i);
