#include "Problem3.h"

// Initialize the cache with capacity Ccap and key range K.
// Allocate dir on the heap and set all entries to nullptr.
void initLRU(LRU &C, int Ccap, int K) {
    C.cap = Ccap;
    C.K = K;
    C.size = 0;
    C.dir = new Node*[K];
    for (int i = 0; i < K; i++) {
        C.dir[i] = nullptr;
    }
}

// Return true and set outVal if present (and move node to MRU); else return false.
bool get(LRU &C, int key, int &outVal) {
    if (key < 0 || key >= C.K || C.dir[key] == nullptr)
        return false;
    outVal = C.dir[key]->val;

    // Move the accessed node to front (MRU)
    detach(C, C.dir[key]);
    pushFront(C, C.dir[key]);
    return true;
}

// Insert or update (key, val). If inserting and size==cap, evict LRU.
// Move the (possibly new) key to MRU position
void put(LRU &C, int key, int val) {
    if (key < 0 || key > C.K) 
        return;
    if (C.dir[key] != nullptr) {
        // key exists, update value and move to front
        C.dir[key]->val = val;
        detach(C, C.dir[key]);
        pushFront(C, C.dir[key]);
    } else {
        // key does not exist, insert new node
        if (C.size == C.cap) {
            evictLRU(C);
        }
        Node* newNode = new Node(key, val);
        pushFront(C, newNode);
        C.dir[key] = newNode;
        C.size++;
    }
}

// (Helpers students should implement/and may call from get/put)
// Remove node u from list in O(1).
void detach(LRU &C, Node *u) {
    if (u == nullptr) return;
    if (u->prev != nullptr)   // u is not head node
        u->prev->next = u->next;
    else                    // u is head node
        C.head = u->next;
    if (u->next != nullptr) // u is not a tail node
        u->next->prev = u->prev;
    else                    // u is a tail node
        C.tail = u->prev;
    u->prev = nullptr;
    u->next = nullptr;
}

// Insert node u at head (MRU) in O(1).
void pushFront(LRU &C, Node *u) {
    if (u == nullptr) return;
    u->next = C.head;
    u->prev = nullptr;

    if (C.head != nullptr)  // non-empty list
        C.head->prev = u;
    else                    // empty list
        C.tail = u;
    
    C.head = u;

}

// Evict the LRU (tail) node in O(1); update dir and size; delete the node.
void evictLRU(LRU &C) {
    if (C.tail == nullptr) return;

    Node* oldTail = C.tail;

    //remove from directory
    C.dir[oldTail->key] = nullptr;

    // remove from DLL
    if (oldTail->prev != nullptr) {     // More tahn 1 node present
        oldTail->prev->next = nullptr;
        C.tail = oldTail->prev;
    } else {                    // Only 1 node presetn
        C.head = nullptr;
        C.tail = nullptr;
    }

    //update size
    C.size--;

    delete oldTail;
    
}