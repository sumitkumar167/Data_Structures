#include <iostream>
using namespace std;

/*!
    Problem 2: Unrolled Linked List [20 points]
    Problem Description. An unrolled linked list is a linked list where each node (called a
    block) stores multiple elements inside a small fixed-size array. This makes the list shorter (fewer
    pointers) and improves cache performance compared to a regular linked list where each node
    stores just one element.
    Each block can hold up to B elements. For example, if B = 4 and we want to store the sequence
    [1, 2, 3, 4, 5, 6, 7, 8], the structure looks like this:
    [1, 2, 3, 4] → [5, 6, 7, 8]
    If we insert one more element (say, 9) into the second block, it overflows. In that case, the block
    is split into two blocks, roughly half-and-half:
    [1, 2, 3, 4] → [5, 6] → [7, 8, 9]
    Similarly, if we delete elements and a block becomes too empty (fewer than half full), it may
    either borrow an element from a neighboring block or merge with its neighbor.
    We will use 0-based indexing across the entire list: the first element of the first block has index
    0, the second has index 1, and so on.
    —
    1. Diagram (5 pts). Let B = 4. Draw an unrolled linked list that stores the sequence
    [1, 2, 3, 4, 5, 6, 7, 8]. Show the blocks, their arrays (with used slots grouped at the front), each
    block’s cnt (number of items), and the next-pointers. Explain what lives on the heap (blocks
    and arrays) versus what lives on the stack (local variables, pointers).
*/


const int B = 4;

struct Block {
    int a[B]; // items packed in a[0..cnt-1]
    int cnt; // number of valid items in this block
    Block* next; // pointer to next block
};

// Unrolled linked list
struct UList {
    Block* head; // head block (nullptr if empty)
    int n; // total number of items
    UList(): head(nullptr), n(0) {}
};

// Build list from arr[0..n-1], filling blocks left-to-right.
void buildFromArray(const int* arr, int n, UList& L);

// Return the value at global index idx.
int getAt(const UList& L, int idx);

// Insert x at global index idx, shifting items as needed.
// If a block is full, split it.
void insertAt(UList& L, int idx, int x);

// Erase the element at global index idx, shifting items as needed.
// If a block becomes under half full, borrow or merge with neighbor.
void eraseAt(UList& L, int idx);

// Helper: find block containing index idx, return pointer and local offset.
Block* findBlock(UList& L, int idx, int& off);

