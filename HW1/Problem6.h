/*!
    Problem 6: Real-Time Task Scheduling with a Ring Buffer Deque [20 points]
Problem Description. In a small real-time executive, runnable tasks are dispatched in short
time slices. To accommodate both urgent and background work, the scheduler uses a doubleended
queue (deque) so it can insert and remove tasks at either end:
• urgent tasks are enqueued at the front (high priority, sooner dispatch),
• background tasks are enqueued at the back (lower priority),
• a preempted task may be returned to the front,
• the least-important queued task may be dropped from the back under memory pressure.
The deque is implemented as a ring buffer (circular array) for O(1) amortized operations and
predictable memory use.
Example. Let the queue hold Task{id} items and start empty with capacity C = 5. Operations
(left = front, right = back):
ENQ_HIGH(10) ⇒ [ 10 ], ENQ_LOW(20) ⇒ [ 10 | 20 ], ENQ_HIGH(11) ⇒ [ 11, 10 | 20 ].
A dispatch step removes from the front: DISPATCH() yields 11 and the queue becomes [ 10 | 20 ].
If PREEMPT(10) occurs, put 10 back to the front: [ 10 | 20 ] → [ 10, 10 | 20 ] (illustrative; in
the assignment below, PREEMPT(id) enqueues a given id at the front).
1. Diagram (5 pts). Draw a ring-buffer deque of capacity C = 6 (array indices 0..5) after
each operation in the sequence below. Show the positions of head, tail, and the current count.
Indicate which indices are occupied and which are free.
ENQ_LOW(21), ENQ_LOW(22), ENQ_HIGH(11), ENQ_LOW(23), DISPATCH(), ENQ_HIGH(12), DROP_LOW().
Explain briefly what lives on the heap (the deque array) vs. on the stack (local variables like
indices, temporary task objects

*/

#include <iostream>
using namespace std;

struct Task {
    int id; // unique task identifier
    // you may add small fields if needed (e.g., stamp), but not STL containers
};

struct DequeRB {
    Task* a; // circular array on the heap
    int cap; // capacity (fixed at construction)
    int head; // index of front element (valid iff count > 0)
    int tail; // index one past the back element (in ring space)
    int count; // number of elements currently stored

    DequeRB(int C) : cap(C), head(0), tail(0), count(0) { 
        // allocate a[C], set fields for empty deque
        a = new Task[C];
    }

    ~DequeRB() { 
        // delete[] a
        delete[] a; 
    }
    bool empty() const {
        return count ==0;
    }

    bool full() const {
        return count == cap;
    }

    // push to front/back; pre: not full (ENQ_HIGH/PREEMPT)
    void pushFront(const Task& t) {
        head = (head - 1 + cap) % cap; // move head backward in ring
        a[head] = t;
        count++;
    }
    // ENQ_LOW
    void pushBack (const Task& t) {
        a[tail] = t;
        tail = (tail + 1) % cap;
        count++;
    }

    // pop from front/back; pre: not empty
    //DISPATCH()
    Task popFront() {
        Task t = a[head];
        head = (head + 1) % cap;
        count--;
        return t;
    }

    // DROP_LOW()
    Task popBack () {
        tail = (tail - 1 + cap) % cap;
        Task t = a[tail];
        count--;
        return t;
    }

    // accessors; pre: not empty
    Task& front() {
        return a[head];
    }
    Task& back () {
        int backIdx = (tail - 1 + cap) % cap;
        return a[backIdx];
    }
};

// Simple scheduler facade using the deque.
// ENQ_HIGH -> pushFront, ENQ_LOW -> pushBack,
// DISPATCH -> popFront (returns dispatched Task id)
// PREEMPT(id) -> pushFront(Task{id}),
// DROP_LOW() -> popBack().
struct Scheduler {
    DequeRB q;

    Scheduler(int C);

    void ENQ_HIGH(int id) {
        q.pushFront(Task{id});
    }

    void ENQ_LOW (int id) {
        q.pushBack(Task{id});
    }

    int DISPATCH() {// returns id of dispatched Task 
    Task t = q.popFront();
    return t.id;        
    }

    void PREEMPT(int id) {// place given id back at front 
        q.pushFront(Task{id});
    }

    void DROP_LOW() { // remove one Task from the back
        q.popBack();
    }
};

Scheduler::Scheduler(int C) : q(C) {}