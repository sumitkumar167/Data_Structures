#include "Problem2.h"

// Build list from arr[0..n-1], filling blocks left-to-right.
void buildFromArray(const int* arr, int n, UList& L) {
    Block* current = new Block;
    current->cnt = 0;
    current->next = nullptr;

    L.head = current;
    L.n = n;

    for (int i = 0; i < n; i++) {
        // When the current block is full
        if (current->cnt == B) {
            Block* newBlock = new Block;
            newBlock->cnt = 0;
            newBlock->next = nullptr;

            current->next = newBlock;
            current = newBlock;
        }
        current->a[current->cnt] = arr[i];
        current->cnt++;
    }
}

// Return the value at global index idx.
int getAt(const UList& L, int idx) {
    int offset = 0;
    Block* cur = L.head;

    while(cur != nullptr) {
        if (idx < offset + cur->cnt) {
            int local_idx = idx - offset;
            return cur->a[local_idx];
        }
        offset += cur->cnt;
        cur = cur->next;
    }

    return -1; // invalid index
}

// Insert x at global index idx, shifting items as needed.
// If a block is full, split it.
void insertAt(UList& L, int idx, int x) {
    int offset = 0;
    Block* cur = L.head;

    while (cur!= nullpr && (offset + cur->cnt < idx)) {
        offset += cur->next;
        cur = cur->next;
    }

    // If idx is at end, cdreate new block at tail
    if (cur = nullptr) {
        Block* tail = L.head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }

        cur = new Block;
        cur->cnt = 0;
        cur->next = nullptr;
        tail->next = cur;
        offset = L.n;
    }

    // If the block is full, split it
    if (cur->cnt = B) {
        int mid = B/2;
        Block* right = new Block;
        right->cnt = 0;
        right->next = cur->next;

        //move upper half to new block
        for (int i = 0; i < (B-mid); i++) {
            right->a[i] = cur->a[mid+i];
        }
        right->cnt = B - mid;
        cur->cnt = mid;
        
        // Decide which side the insertion belongs to
        if (idx >= offset + mid) {
            offset += mid;
            cur = right;
        }
    }

    // local index inside the chosen block
    int local = idx - offset;

    // shift elements right to make room
    for (int i = cur->cnt; i > local; i--) {
        cur->a[i] = cur->a[i-1];
    }

    cur->a[local] = x;
    cur->cnt++;
    L.n++;
}

// Erase the element at global index idx, shifting items as needed.
// If a block becomes under half full, borrow or merge with neighbor.
void eraseAt(UList& L, int idx) {
    if (L.head == nullptr || idx < 0 || idx >= L.n) {
        return;
    }

    int offset = 0;
    Block* cur = L.head;

    while (cur != nullptr) {
        if (idx < offset + cur->cnt) {
            int local_idx = idx - offset;

            // shift left to remove element
            for (int i = local_idx; i < cur->cnt - 1; i++) {
                cur->a[i] = cur->a[i+1];
            }

            cur->cnt--;
            L.n--;

            // Rebalance if block is too empty
            if (cur->cnt < B/2) {
                Block* next = cur->next;

                if (next != nullptr && next->cnt > B/2) {
                    // Borrow one item from next block
                    cur->a[cur->cnt] = next->a[0];

                    for (int i = 0; i < next->cnt - 1; i++) {
                        next->a[i] = next->a[i+1];
                    }

                    next->cnt--;
                    cur->cnt++;
                }
                else if (next != nullptr) {
                    // merge with next block
                    for (int i = 0; i < next->cnt; i++) {
                        cur->a[cur->cnt++] = next->a[i];
                    }

                    Block* temp = next;
                    cur->next = next->next;
                    delete temp;
                }
            }
            return;
        }

        offset += cur->cnt;
        cur = cur->next;
    }
}

// Helper: find block containing index idx, return pointer and local offset.
Block* findBlock(UList& L, int idx, int& off) {
    int offset = 0;
    Block* cur = L.head;

    while (cur != nullptr) {
        if (idx < offset + cur->cnt) {
            off = idx - offset;
            return cur;
        }
        offset += cur->cnt;
        cur = cur->next;
    }

    off = -1;
    return nullptr;
}
