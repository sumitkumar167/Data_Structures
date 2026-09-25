#include "Problem4.h"

// Build a polynomial from arrays coef[i], exp[i], i=0..m-1.
// Insert terms one-by-one so that the final list is strictly descending in exp
// and contains no duplicate exponents (combine coefs; drop zero terms).
Term* buildFromArrays(const double* coef, const int* exp, int m) {
    Term* head = nullptr;

    for (int i = 0; i < m; i++) {
        if (coef[i] == 0) continue; // skip zero coeff
        insertTerm(head, coef[i], exp[i]);
    }
    return head;
}

// Insert (c,e) into the sorted list (descending exponents).
// Combine coefficients if exp already exists; remove node if coef becomes 0.
void insertTerm(Term*& head, double c, int e) {
    if (c == 0) return;

    Term* prev = nullptr;
    Term* cur = head;

    // Find insertion point
    while (cur != nullptr && cur->exp > e) {
        prev = cur;
        cur = cur->next;
    }

    // same exponent present
    if (cur != nullptr && cur->exp == e) {
        cur->coef += c;

        // If coeff becomes 0
        if (cur->coef == 0) {
            if (prev == nullptr) {
                head = cur->next;
            }
            else {
                prev->next = cur->next;
            }
            delete cur;
        }
        return;
    }

    // Insert new term
    Term* newTerm = new Term(c, e);
    newTerm->next = cur;

    if (prev == nullptr)
        head = newTerm;
    else
        prev->next = newTerm;
}

// Remove the term with exponent e, if present.
void eraseExp(Term*& head, int e) {
    Term* prev = nullptr;
    Term* cur = head;

    while (cur != nullptr && cur->exp > e) {
        prev = cur;
        cur = cur->next;
    }

    if (cur != nullptr && cur->exp == e) {
        if (prev == nullptr) {
            head = cur->next;
        }
        else {
            prev->next = cur->next;
        }
        delete cur;
    }
}

// Recursively compute x^k for k>=0 using fast exponentiation.
// Must run in O(log k).
double powInt(double x, int k) {
    if (k == 0) return 1;

    double half = powInt(x, k/2);

    if (k%2 == 0) 
        return half * half;
    else
        return x * half * half;
}

// Recursive evaluation of the polynomial at x.
// Assume list is strictly descending in exp with no duplicates.
// Hint: if current node is (c,e) and next is (c2,e2), multiply the running
// value by x^(e - e2) before adding c2, and recurse.
double evalRecursive(const Term* head, double x) {
    if (head == nullptr) return 0;

    // Base case: single term
    if (head->next == nullptr) 
        return head->coef * powInt(x, head->exp);

    // Recursive case: current term + next terms
    return head->coef * powInt(x, head->exp) + evalRecursive(head->next, x);
}