#include "Problem2.h"

void swapInt(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int leftChild(int i) {
    return 2*i + 1;
}

int rightChild(int i) {
    return 2*i + 2;
}

/* Return 1 if Max-Heap property holds at index i (i.e., children <= C[i]),
otherwise return 0. Only checks local condition at i. */
int holdsAt(int C[], int cN, int i) {
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < cN && C[left] > C[i]) {
        return 0;
    }
    if (right < cN && C[right] > C[i]) {
        return 0;
    }
    return 1;
}

// -1 if no children
int largerChildIndex(int C[], int cN, int i) {
    int left = leftChild(i);
    int right = rightChild(i);

    if (left >= cN) return -1; // No children

    if (right >= cN) return left; // Only left child exists

    // Return index of larger child
    return (C[left] >= C[right]) ? left : right; 
}

/* Restore Max-Heap property by heapifying down from index i only.
Arguments: array C[0..cN-1], heap size cN, start index i. */
void maxHeapifyFrom(int C[], int cN, int i) {
    while(true) {
        int child = largerChildIndex(C, cN, i);
        
        if (child == -1 || C[i] >= C[child]) break;

        swapInt(&C[i], &C[child]);
        i = child;
    }
}

/* Return 1 if the entire array C[0..cN-1] satisfies the Max-Heap property,
otherwise return 0. */
int isMaxHeap(int C[], int cN) {
    for (int i = 0; i < cN; i++) {
        if (!holdsAt(C, cN, i)) return 0;
    }

    return 1;
}

int main() {
    int C[] = {90, 70, 10, 40, 60, 30, 80}; // example from statement
    int n = 7;
    maxHeapifyFrom(C, n, 2);

    cout << "Final Array: ";
    for (int i = 0; i < n; i++)
        cout << C[i] << " ";
    cout << "\n Is Max-heap? : " << isMaxHeap(C, n) << endl;
    // print the final array C
    return 0;
}