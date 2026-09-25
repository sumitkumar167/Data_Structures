#include "Problem5.h"

// Append ’kid’ at the end of directory ’dir’ child-list.
void addChild(Node* dir, Node* kid) {
    if (dir == nullptr || kid == nullptr) return;

    if (dir->child == nullptr) {
        dir->child = kid;
        kid->next = nullptr;
        return;
    }

    Node* cur = dir->child;
    while (cur->next != nullptr)
        cur = cur->next;
    
    cur->next = kid;
    kid->next = nullptr; // Ensure kid's next is null
}

// Append ’sib’ after node ’u’ in the sibling chain (attach at the end of u’s next-chain).
void appendSibling(Node* u, Node* sib) {
    if (u == nullptr || sib == nullptr) return;

    Node* cur = u;
    while (cur->next != nullptr) 
        cur = cur->next;
    
    cur->next = sib;
    sib->next = nullptr; // Ensure sib's next is null
}

// Recursively flatten the multilevel list rooted at ’head’ into a single-level
// preorder list. After flatten, all child pointers in reachable nodes must be nullptr.
// Return the head of the flattened list.
Node* flatten(Node* head) {
    if (head == nullptr) return nullptr;

    if (head->child != nullptr) {
        Node* childHead = flatten(head->child);
        Node* childTail = childHead;

        while (childTail->next != nullptr)
            childTail = childTail->next;
        
        Node* oldNext = head->next;
        childTail->next = oldNext;
        head->next = childHead;
        head->child = nullptr;
    }

    // Flatten the next sibling
    if (head->next != nullptr)
        flatten(head->next);

    return head;
}

// Print IDs once along ’next’ starting at head (e.g., "10 11 12 ...")
// or "EMPTY" if head==nullptr.
void printFlat(Node* head) {
    if (head == nullptr) {
        cout << "EMPTY" << endl;
        return;
    }

    Node* cur = head;
    while (cur != nullptr) {
        cout << cur->id << " ";
        cur = cur->next;
    }
    cout << endl;
}