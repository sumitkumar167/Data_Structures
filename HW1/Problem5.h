/*!
    Problem 5: Filesystem Flattening [20 points]
Problem Description. We model a tiny filesystem as a multilevel linked list. Each node
represents either a directory or a file. Siblings within the same directory are connected by next,
and a directory’s first entry (its sublist of children) is reached via child. Your goal is to flatten
the hierarchy into a single-level list using next pointers only, in preorder (visit a directory,
then its entire subtree, left-to-right), clearing all child pointers in the result.
Example. Arrows = next, downward arrow = child:
1 (dir) ↓
2 (file) → 3 (dir) → 4 (file)
, 3 ↓
5 (file) → 6 (file)
 
Preorder flattening produces: 1 → 2 → 3 → 5 → 6 → 4, with all child pointers set to nullptr.
*/

#include <iostream>
using namespace std;

struct Node {
    int id; // unique ID (e.g., 1..n)
    bool isDir; // true = directory, false = file
    Node* next; // next sibling (or next in flattened list)
    Node* child; // first child if directory, else nullptr
    Node(int i, bool d): id(i), isDir(d), next(nullptr), child(nullptr) {}
};

// Append ’kid’ at the end of directory ’dir’ child-list.
void addChild(Node* dir, Node* kid);

// Append ’sib’ after node ’u’ in the sibling chain (attach at the end of u’s next-chain).
void appendSibling(Node* u, Node* sib);

// Recursively flatten the multilevel list rooted at ’head’ into a single-level
// preorder list. After flatten, all child pointers in reachable nodes must be nullptr.
// Return the head of the flattened list.
Node* flatten(Node* head);

// Print IDs once along ’next’ starting at head (e.g., "10 11 12 ...")
// or "EMPTY" if head==nullptr.
void printFlat(Node* head);

