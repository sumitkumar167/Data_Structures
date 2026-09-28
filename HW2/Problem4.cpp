#include "Problem4.h"

// Create a new node with a given C-string (assume lifetime >= program).
Node* newNode(const char *w) {
    Node* u = new Node;
    u->word = w;
    u->left = nullptr;
    u->right = nullptr;

    return u;
}

// Insert word into BST by strcmp (ties to the right).
// Use recursive implementation.
// Return the (new or existing) node.
Node* insert(Node* &root, const char *w) {
    Node* cur = nullptr;
    if (root == nullptr) {
        root = newNode(w);
        return root;
    }
    if (strcmp(w, root->word) >= 0)
    {
        cur = insert(root->right, w);
    }
    else {
        cur = insert(root->left, w);
    }
    return cur;
}

// Return true iff the word exists in the BST.
bool contains(Node *root, const char *w) {
    bool node_present = false;
    Node* cur = root;
    if (root == nullptr) {
        return false;
    }
    int cmp = strcmp(w, root->word);

    if (cmp == 0) return true;
    if (cmp < 0) return contains(root->left, w);
    return contains(root->right, w);
}

// Return the number of words that start with ‘prefix’.
// Hint: recurse into both sides; count this node if strncmp(...)==0.
int prefixCount(Node *root, const char *prefix) {
    if (root == nullptr) return 0;
    int count = 0;

    if (strncmp(root->word, prefix, strlen(prefix)) == 0) count = 1;

    count += prefixCount(root->left, prefix);
    count += prefixCount(root->right, prefix);
    return count;
}

// In-order print (ascending)
void inorder(Node *u) {
    if (u == nullptr) return;
    inorder(u->left);
    cout << u->word << " ";
    inorder(u->right);
}



int main() {
    Node *root = nullptr;
    // Insert fixed dataset (one call per word):
    insert(root, "cat");
    insert(root, "dog");
    insert(root, "door");
    insert(root, "dove");
    insert(root, "cart");
    insert(root, "car");
    insert(root, "care");
    insert(root, "careful");
    insert(root, "do");
    insert(root, "zebra");
    // Example checks (optional):
    std::cout << "contains(’care’) = " << contains(root, "care") << std::endl;
    std::cout << "prefixCount(’car’) = " << prefixCount(root, "car") << std::endl;
    return 0;
}