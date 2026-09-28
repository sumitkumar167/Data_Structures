/* Huffman Coding */

#include <iostream>
using namespace std;

struct Node {
    int weight;      // frequency or sum
    char sym;        // 'A'....'Z' for leaves; 0 for internal
    Node *left, *right;
    Node *next;
};

// Push node u at the front of the alive list
// Note: Passing a reference allows to change the value of the argument
void pushFront(Node* &head, Node* u);

// Find the two smallest-weight nodes in the alive list (single pass)
// Returns pointers to the minima and their predecessors (to splice in O(1))
void pickTwoMin(Node *head,
                Node* &min1, Node* &min1Prev,
                Node* &min2, Node* &min2Prev);

// Build the Huffman tree from the given dataset; return teh root
Node* buildHuffman();

// Pre-order traversal: print "<sym> : <bits>" at leaves 
// buf holds the current path
// len: current length
// Use recursion
void emitCodesPreorder(Node *u, char buf[], int len);


