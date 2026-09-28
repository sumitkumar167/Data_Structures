#include <iostream>
using namespace std;

struct Node {
    const char *name;
    Node *left, *right, *parent;
};

// Create a new node with a given name.
Node* newNode(const char *s);

// Helper: set L and R as children of p and set their parent pointers.
void linkLR(Node *p, Node *L, Node *R);

// Build the given tree; return root.
Node* buildTree();

// Pre-order search by name; return pointer or nullptr.
Node* findPreorder(Node *u, const char *target);

// Depth in edges from u up to root (root has depth 0).
int depth(Node *u);

// LCA via parent pointers only.
// Steps: raise deeper node until both at same depth; then climb both until equal.
Node* lca(Node *a, Node *b);

// Compare two C-style strings
bool stringEqual(const char *a, const char *b);