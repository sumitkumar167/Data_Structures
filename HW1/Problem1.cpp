#include "Problem1.h"

CircularLinkedList::CircularLinkedList() {}

void CircularLinkedList::NEXT(int k) {
    for (int i = 0; i < k; i++) {
        current = current->next;
    }
}

void CircularLinkedList::DEL() {
    if (current == nullptr) 
        return;
    
    // If the list only has 1 node
    if (current == front && current == back) {
        delete current;
        front = nullptr;
        back = nullptr;
        current = nullptr;
        return;
    }

    // Save the node to be deleted, and next node to move current to
    Node* victim = current;
    Node* nextNode = victim->next;

    // Find the node before current
    Node* prevNode = front;
    if (victim != front) {
        while (prevNode->next != victim)
            prevNode = prevNode->next;
    }

    // If the list has multiple nodes
    if (victim == front) {
        front = nextNode;
        back->next = front;
    }
    else {
        prevNode->next = nextNode;
    }

    if (victim==back) {
        back = prevNode;
    }

    current = nextNode;
    delete victim;
}

// Builds a circular list of 1..n nodes, returns pointer to head,
// initializes cur appropriately, and sets size = n.
Node* CircularLinkedList::buildCircle(int n, Node*& cur, int& size) {
    front = new Node;
    front->data = 1;
    front->next = front; // Point to itself to become circular

    back = front;

    for (int i = 2; i <= n; i++) {
        Node* newNode = new Node;
        newNode->data = i;
        newNode->next = front; // Point to front for circular
        back->next = newNode;  // The last node should point to new one

        back = newNode;
    }
    cur = front; // Initialize current to front
    size = n;
    return front;
}

// Advances cur by k % size steps.
void CircularLinkedList::nextK(Node*& cur, int& size, int k) {
    int steps = k % size;
    for (int i = 0; i < steps; i++) {
        cur = cur->next;
    }
}


// Deletes the node at cur, updates links, and sets cur = next node.
void CircularLinkedList::delCurrent(Node*& cur, int& size) {
    if (cur == nullptr || size = 0)
        return;
    if (size = 1) {
        delete cur;
        cur = nullptr;
        size--;
        return;
    }
    else if (size > 1) {
        Node* nextNode = cur->next;
        Node* prevNode = cur;

        // Find previous node
        Node* temp = nextNode;
        while (temp->next != cur)
            temp = temp->next;
        
        prevNode = temp;
        delete cur;
        cur = nextNode;
        size--;
    }
}

// Prints the list once around starting from cur (or EMPTY if size = 0).
void CircularLinkedList::printOnce(Node* cur) {
    Node* temp = cur;
    if (cur == nullptr) {
        cout << "EMPTY" << endl;
        return;
    }
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
        if (cur == temp)
            break;
    }
}