#include "Problem1.h"

Node* min_heap[10000];
int heapSize = 0;

/* Swap two entries at indices i and j in heap[] */
void hSwap(int i, int j) {
    Node* temp = min_heap[i];
    min_heap[i] = min_heap[j];
    min_heap[j] = temp;
}

/* Return parent/children indices for a given i */
int hParent(int i) {
    // (i - 1) / 2
    return (i-1) / 2;
}
int hLeft (int i) {
    // 2*i + 1
    return 2*i + 1;
}

int hRight (int i){
    return 2*i + 2;
}

/* Heapify-down from index i within current heapSize */
void hDown(int i){
    while(true){
        int smallest = i;
        int left = hLeft(i);
        int right = hRight(i);

        if ((left < heapSize) &&
            (min_heap[left]->val < min_heap[smallest]->val)) {
                smallest = left;
        }
        if ((right < heapSize) && 
            (min_heap[right]->val < min_heap[smallest]->val)) {
                smallest = right;
        }
        if (smallest == i)
            break;
        
        hSwap(i, smallest);
        i = smallest;
    }
}

/* Heapify-up from index i within current heapSize */
void hUp(int i) {
    while (i > 0) {
        int parent = hParent(i);

        if (min_heap[i]->val <= min_heap[parent]->val) {
            break;
        }

        hSwap(parent, i);
        i = parent;
    }
}

/* Push non-null pointer p into the min-heap */
void hPush(Node* p) {
    if (p == nullptr) return;
    min_heap[heapSize] = p;
    hUp(heapSize);
    ++heapSize;
}

/* Pop from heap and return the smallest pointer; return nullptr if empty */
Node* hPop() {
    if (heapSize == 0) return nullptr;

    Node* result = min_heap[0];
    --heapSize;

    if (heapSize > 0) {
        min_heap[0] = min_heap[heapSize];
        hDown(0);
    }
    return result;
}



/* ---------- Merge driver ---------- */
/* Given heads[0..K-1], return head of merged list */
Node* mergeK(Node* heads[], int K) {
    heapSize = 0;

    // Insert the initial head of each non-empty list
    for (int i =0; i< K; ++i) {
        if (heads[i] != nullptr)
            hPush(heads[i]);
    }

    Node* mergedHead = nullptr;
    Node* tail = nullptr;

    while (heapSize > 0) {
        // Extract the smallest node
        Node* current = hPop();

        // Save its successor before modifying links
        Node* successor = current->next;

        // Append the node to the merged list
        current->next = nullptr; // Disconnect from its original list

        if (mergedHead == nullptr) {
            mergedHead = current;
            tail = current;
        }
        else {
            tail->next = current;
            tail = current;
        }

        // Insert the successor from the same original list
        if (successor != nullptr)
            hPush(successor);
    }
    return mergedHead;
}

/* ---------- Minimal driver template (for understanding call flow) ----------
This template is NOT a solution and may not compile as-is.
It only indicates how the above functions are expected to be used.
You do not need to fill out this main function.
*/
int main() {
    // 1. Build four sorted linked lists
    Node* L0 = new Node{0, nullptr};
    L0->next = new Node{7, nullptr};

    Node* L1 = new Node{1, nullptr};
    L1->next = new Node{4, nullptr};
    L1->next->next = new Node{5, nullptr};

    Node* L2 = new Node{1, nullptr};
    L2->next = new Node{3, nullptr};
    L2->next->next = new Node{4, nullptr};

    Node* L3 = new Node{2, nullptr};
    L3->next = new Node{6, nullptr};

    // 2. Store the heads of all lists in an array
    const int K = 4;
    Node* heads[K] = {L0, L1, L2, L3};

    // 3. Merge the K sorted lists
    Node* merged = mergeK(heads, K);

    // 4. Print the merged list
    Node* current = merged;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr)
            cout << " -> ";
        current = current->next;

    }

    cout << endl;

    return 0;
}