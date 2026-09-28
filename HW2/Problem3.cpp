#include "Problem3.h"

// Create a new node with a given name.
Node* newNode(const char *s) {
    Node* u = new Node;
    u->name = s;
    u->left = nullptr;
    u->right = nullptr;
    u->parent = nullptr;
    return u;
}

// Helper: set L and R as children of p and set their parent pointers.
void linkLR(Node *p, Node *L, Node *R) {
    p->left = L;
    p->right = R;

    if (L != nullptr)
        L->parent = p;
    if (R != nullptr)
        R->parent = p;
}

// Build the given tree; return root.
Node* buildTree() {
    Node* root = newNode("root");
    Node* home = newNode("home");
    Node* var = newNode("var");
    Node* alice = newNode("alice");
    Node* bob = newNode("bob");
    Node* tmp = newNode("tmp");
    Node* lib = newNode("lib");
    Node* docs = newNode("docs");
    Node* pics = newNode("pics");
    Node* games = newNode("games");
    Node* logs = newNode("logs");

    linkLR(root, home, var);
    linkLR(home, alice, bob);
    linkLR(alice, docs, pics);
    linkLR(bob, games, logs);
    linkLR(var, tmp, lib);
    return root;
}

// Pre-order search by name; return pointer or nullptr.
Node* findPreorder(Node *u, const char *target) {
    if (u == nullptr) return nullptr;

    // Check current node
    if (stringEqual(u->name, target)) return u;

    // Search left subtree
    Node* result = findPreorder(u->left, target);

    if (result != nullptr) return result;

    // Search right subtree
    return findPreorder(u->right, target);
}

// Compare two C-style strings
bool stringEqual(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        ++i;
    }
    return a[i] == b[i];
}

// Depth in edges from u up to root (root has depth 0).
int depth(Node *u) {
    int d = 0;
    while (u != nullptr && u->parent != nullptr) {
        u = u->parent;
        ++d;
    }
    return d;
}

// LCA via parent pointers only.
// Steps: raise deeper node until both at same depth; then climb both until equal.
Node* lca(Node *a, Node *b) {
    int da = depth(a);
    int db = depth(b);

    // Move deeper node upward
    while (da > db) {
        a = a->parent;
        --da;
    }
    while (db > da) {
        b = b->parent;
        --db;
    }

    // Now both nodes have same depth
    // Move both up until they meet
    while (a != b) {
        a = a->parent;
        b = b->parent;
    }
    return a;
}

int main() {
    Node *root = buildTree();
    const char *Q[][2] = {
        {"docs","pics"}, // expect: alice
        {"docs","games"}, // expect: home
        {"logs","tmp"}, // expect: root
        {"lib","tmp"}, // expect: var
        {"alice","games"} // expect: home
    };
    for (int i = 0; i < 5; ++i) {
        Node *a = findPreorder(root, Q[i][0]);
        Node *b = findPreorder(root, Q[i][1]);
        Node *c = lca(a, b);
        std::printf("LCA(%s,%s) = %s\n", Q[i][0], Q[i][1], c ? c->name : "(null)");
    }
    return 0;
}