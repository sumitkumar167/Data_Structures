#include "Problem2.h"


// Create a new node with given name.
Node* newNode(const char *label) {
    Node* temp = new Node;
    temp->name = label;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

// Build the topology from the above description; return the root ("R").
Node* buildNetwork() {
    // Create all nodes
    Node* R = newNode("R");
    Node* A1 = newNode("A1");
    Node* A2 = newNode("A2");
    Node* E1 = newNode("E1");
    Node* E2 = newNode("E2");
    Node* E3 = newNode("E3");
    Node* d1 = newNode("d1");
    Node* d2 = newNode("d2");
    Node* d3 = newNode("d3");
    Node* d4 = newNode("d4");
    Node* d5 = newNode("d5");
    Node* d6 = newNode("d6");
    // Build tree
    R->left = A1;
    R->right = A2;
    A1->left = E1;
    A1->right = E2;
    A2->left = E3;
    A2->right = nullptr;

    E1->left = d1;
    E1->right = d2;
    E2->left = d3;
    E2->right = d4;
    E3->left = d5;
    E3->right = d6;

    return R;
}

// Return true iff u is an endpoint (leaf).
bool isLeaf(Node *u) {
    bool flag_leaf = (u != nullptr) && (u->right == nullptr) && (u->left == nullptr);
    return flag_leaf;
}

// Count the number of endpoints in the network, ‘‘recursively’’.
int countLeaves(Node *u) {
    if (u == nullptr) return 0;
    if (isLeaf(u)) return 1;
    int number_leaves = countLeaves(u->left) + countLeaves(u->right);
    return number_leaves;
}

// List endpoints using your chosen traversal (pick ONE style and stick to it).
void listEndpoints(Node *u) {
    if (u == nullptr) return;
    if (isLeaf(u)) {
        cout << u->name << " ";
    }

    // visit left subtree
    listEndpoints(u->left);

    // visit right subtree
    listEndpoints(u->right);
}

int main() {
    Node *root = buildNetwork();
    std::cout << "Endpoints (chosen traversal):\n";
    listEndpoints(root);
    int leaves = countLeaves(root);
    std::cout << "Total endpoints: " << leaves << "\n";
    return 0;
}