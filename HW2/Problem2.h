#include <iostream>
using namespace std;

struct Node {
    const char *name; // e.g., "R", "A1", "d1"
    Node *left; // first downstream link (may be nullptr)
    Node *right; // second downstream link (may be nullptr)
};

// Create a new node with given name.
Node* newNode(const char *label);

// Build the topology from the above description; return the root ("R").
Node* buildNetwork();

// Return true iff u is an endpoint (leaf).
bool isLeaf(Node *u);

// Count the number of endpoints in the network, ‘‘recursively’’.
int countLeaves(Node *u);

// List endpoints using your chosen traversal (pick ONE style and stick to it).
void listEndpoints(Node *u);
