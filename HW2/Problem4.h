#include <iostream>
#include <cstring> // for strcmp/strncmp
using namespace std;

struct Node {
    const char *word; // stored as lowercase ASCII
    Node *left, *right;
};

// Create a new node with a given C-string (assume lifetime >= program).
Node* newNode(const char *w);

// Insert word into BST by strcmp (ties to the right).
// Use recursive implementation.
// Return the (new or existing) node.
Node* insert(Node* &root, const char *w);

// Return true iff the word exists in the BST.
bool contains(Node *root, const char *w);

// Return the number of words that start with ‘prefix’.
// Hint: recurse into both sides; count this node if strncmp(...)==0.
int prefixCount(Node *root, const char *prefix);

// In-order print (ascending)
void inorder(Node *u);

