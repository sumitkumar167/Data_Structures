#include "Problem1.h"

// Push node u at the front of the alive list
// Note: Passing a reference allows to change the value of the argument
void pushFront(Node* &head, Node* u) {
    u->next = head;
    head = u;
}

// Find the two smallest-weight nodes in the alive list (single pass)
// Returns pointers to the minima and their predecessors (to splice in O(1))
void pickTwoMin(Node *head,
                Node* &min1, Node* &min1Prev,
                Node* &min2, Node* &min2Prev) {
    Node *cur = head;
    Node* prev = nullptr;

    min1 = nullptr;
    min1Prev = nullptr;
    min2 = nullptr;
    min2Prev = nullptr;

    while (cur->next != nullptr)
    {
        if (min1 == nullptr || cur->weight < min1->weight) {
            // Current min becomes second min
            min2 = min1;
            min2Prev = min1Prev;

            // Current node becomes first min
            min1 = cur;
            min1Prev = prev;
        }
        else if (min2 == nullptr || cur->weight < min2->weight) {
            min2 = cur;
            min2Prev = prev;
        }

        prev = cur;
        cur = cur->next;
    }
}

// Build the Huffman tree from the given dataset; return teh root
Node* buildHuffman() {
    Node *alive = nullptr;
    // Create leaves A to F and push them into alive list (any order)
    const char symbols[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    const int weights[] = {5, 9, 12, 13, 16, 45};

    for (int i = 0; i < 6; ++i)
    {
        Node* u = new Node;
        u->weight = weights[i];
        u->sym = symbols[i];
        u->left = nullptr;
        u->right = nullptr;
        u->next = nullptr;

        pushFront(alive, u);
    }
    // Repeatedly pick two smallest, merge, and push parent back
    while (alive != nullptr && alive->next != nullptr) {
        Node *min1 = nullptr;
        Node *min2 = nullptr;
        Node *min1Prev = nullptr;
        Node *min2Prev = nullptr;
        pickTwoMin(alive, min1, min1Prev, min2, min2Prev);
        // Remove min1 from list
        if (min1Prev == nullptr) {
            alive = min1->next;
        }
        else {
            min1Prev->next = min1->next;
        }

        // Create parent node;
        Node* parent = new Node;
        parent->weight = min1->weight + min2->weight;
        parent->sym = 0;
        parent->left = min1;
        parent->right = min2;
        parent->next = nullptr;

        // Put parent into alive list
        pushFront(alive, parent);
    }

    // Return the last remaining node
    return alive;
}


// Pre-order traversal: print "<sym> : <bits>" at leaves 
// buf holds the current path
// len: current length
// Use recursion
void emitCodesPreorder(Node *u, char buf[], int len) {
    if (u == nullptr) return;

    // Leaf
    if (u->left == nullptr && u->right == nullptr) {
        buf[len] = '\0';
        cout << u->sym << " : " << buf << endl;
        return;
    }

    // GO left = 0
    buf[len] = '0';
    emitCodesPreorder(u->left, buf, len+1);

    // Go right = 1
    buf[len] = '1';
    emitCodesPreorder(u->right, buf, len+1);
}


int main() {
    Node *root = buildHuffman();
    char buf[64];
    emitCodesPreorder(root, buf, 0);
    return 0;
}