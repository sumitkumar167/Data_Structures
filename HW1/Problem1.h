#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class CircularLinkedList {
    Node* front;
    Node* back;
    Node* current;

    public:
    CircularLinkedList() {
        front = nullptr;
        back = nullptr;
        current = nullptr;
        back->next = front;
    }

    ~CircularLinkedList() {}

    void NEXT(int k);
    void DEL();
    /*! 
       Builds a circular list of 1..n nodes, returns pointer to head,
       initializes cur appropriately, and sets size = n.
    */
    Node* buildCircle(int n, Node*& cur, int& size);

    // Advances cur by k % size steps.
    void nextK(Node*& cur, int& size, int k);

    // Deletes the node at cur, updates links, and sets cur = next node.
    void delCurrent(Node*& cur, int& size);

    // Prints the list once around starting from cur (or EMPTY if size = 0).
    void printOnce(Node* cur);
};