/*
#include "Problem3.h"

int main() {
    LRU C;
    initLRU(C, 3, 10);

    put(C, 2, 20);
    put(C, 5, 50);
    put(C, 7, 70);

    int out;
    cout << get(C, 5, out) << " " << out << endl;

    return 0;
}
    */


    /*
#include "Problem4.h"

int main() {
    double coef[] = {3, 2, -1, 4};
    int exp[] = {5, 3, 1, 0};

    Term* p = buildFromArrays(coef, exp, 4);

    cout << "Polynomial: 3x^5 + 2x^3 - x + 4" << endl;

    cout << "P(2) = " << evalRecursive(p, 2.0) << endl;
    cout << "P(0) = " << evalRecursive(p, 0.0) << endl;
    cout << "P(1) = " << evalRecursive(p, 1.0) << endl;

    // Optional: test insert and erase
    insertTerm(p, 5, 2);
    cout << "After insert 5x^2: P(2) = " << evalRecursive(p, 2.0) << endl;

    eraseExp(p, 2);
    cout << "After erase x^2: P(2) = " << evalRecursive(p, 2.0) << endl;

    // Clean up dynamically allocated nodes
    while (p != nullptr) {
        Term* temp = p;
        p = p->next;
        delete temp;
    }

    return 0;
}
    */

/*
#include "Problem5.h"

int main() {
    Node* n10 = new Node(10, true);   // dir
    Node* n11 = new Node(11, false);  // file
    Node* n12 = new Node(12, true);   // dir
    Node* n13 = new Node(13, false);  // file
    Node* n14 = new Node(14, true);   // dir
    Node* n15 = new Node(15, false);  // file
    Node* n16 = new Node(16, false);  // file

    // 10 children: 11 -> 12 -> 13
    addChild(n10, n11);
    addChild(n10, n12);
    addChild(n10, n13);

    // 12 children: 14 -> 16
    addChild(n12, n14);
    addChild(n12, n16);

    // 14 child: 15
    addChild(n14, n15);

    Node* flat = flatten(n10);
    printFlat(flat);

    // optional: check child pointers are cleared
    Node* cur = flat;
    while (cur != nullptr) {
        cout << "node " << cur->id << " child = " << (cur->child == nullptr ? "nullptr" : "non-null") << endl;
        cur = cur->next;
    }

    // cleanup
    cur = flat;
    while (cur != nullptr) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }

    return 0;
}*/
/*
#include "Problem6.h"

int main() {
    Scheduler s(6);

    s.ENQ_LOW(21);
    s.ENQ_LOW(22);
    s.ENQ_HIGH(11);
    s.ENQ_LOW(23);

    cout << "front = " << s.q.front().id << endl;
    cout << "back  = " << s.q.back().id << endl;

    return 0;
}

*/

#include "Problem7.h"
#include <iostream>
using namespace std;

int main()
{
    const int N = 4;
    const double dt = 0.5;

    // Initial particle data
    double x[]  = {10.0, 20.0, 30.0, 40.0};
    double y[]  = { 5.0, 10.0, 15.0, 20.0};
    double vx[] = { 1.0,  2.0,  3.0,  4.0};
    double vy[] = { 2.0,  3.0,  4.0,  5.0};

    // ---------------- AoS ----------------
    AoS A;

    aosInit(A, N, x, y, vx, vy);

    cout << "Initial AoS particles:\n";
    for (int i = 0; i < A.N; ++i) {
        cout << "P[" << i << "] = {"
             << A.p[i].x << ", "
             << A.p[i].y << ", "
             << A.p[i].vx << ", "
             << A.p[i].vy << "}\n";
    }

    // Advance simulation
    aosStep(A, dt);

    // Center of mass
    double cx, cy;
    aosCenterOfMass(A, cx, cy);

    cout << "\nAfter AoS step (dt = " << dt << "):\n";
    for (int i = 0; i < A.N; ++i) {
        cout << "P[" << i << "] = {"
             << A.p[i].x << ", "
             << A.p[i].y << ", "
             << A.p[i].vx << ", "
             << A.p[i].vy << "}\n";
    }

    cout << "AoS Center of Mass = ("
         << cx << ", " << cy << ")\n";


    // ---------------- SoA ----------------
    SoA S;

    soaInit(S, N, x, y, vx, vy);

    cout << "\nInitial SoA particles:\n";
    for (int i = 0; i < S.N; ++i) {
        cout << "P[" << i << "] = {"
             << S.x[i] << ", "
             << S.y[i] << ", "
             << S.vx[i] << ", "
             << S.vy[i] << "}\n";
    }

    // Advance simulation
    soaStep(S, dt);

    // Center of mass
    soaCenterOfMass(S, cx, cy);

    cout << "\nAfter SoA step (dt = " << dt << "):\n";
    for (int i = 0; i < S.N; ++i) {
        cout << "P[" << i << "] = {"
             << S.x[i] << ", "
             << S.y[i] << ", "
             << S.vx[i] << ", "
             << S.vy[i] << "}\n";
    }

    cout << "SoA Center of Mass = ("
         << cx << ", " << cy << ")\n";


    // ---------------- Test AoS -> SoA ----------------
    SoA S2;
    soaInit(S2, N, x, y, vx, vy);

    aosToSoa(A, S2);

    cout << "\nAfter AoS -> SoA conversion:\n";
    for (int i = 0; i < S2.N; ++i) {
        cout << "P[" << i << "] = {"
             << S2.x[i] << ", "
             << S2.y[i] << ", "
             << S2.vx[i] << ", "
             << S2.vy[i] << "}\n";
    }


    // ---------------- Test SoA -> AoS ----------------
    AoS A2;
    aosInit(A2, N, x, y, vx, vy);

    soaToAos(S, A2);

    cout << "\nAfter SoA -> AoS conversion:\n";
    for (int i = 0; i < A2.N; ++i) {
        cout << "P[" << i << "] = {"
             << A2.p[i].x << ", "
             << A2.p[i].y << ", "
             << A2.p[i].vx << ", "
             << A2.p[i].vy << "}\n";
    }


    // ---------------- Free memory ----------------
    aosFree(A);
    aosFree(A2);

    soaFree(S);
    soaFree(S2);

    return 0;
}