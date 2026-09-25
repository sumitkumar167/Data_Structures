/*
    Problem 4: Polynomial Representation & Recursive Evaluation [20 points]
    Problem Description. We represent a polynomial
    as a singly linked list of terms, each term storing a coefficient ci and an integer exponent ei. Terms
    are kept in strictly descending exponent order (largest exponent first). Example (descending
    exponents): 3x5 + 2x3 − x + 4 is stored as the list
    (3, 5) → (2, 3) → (−1, 1) → (4, 0).
    When evaluating, note that exponents can be sparse (e.g., there is no x2 term above). A
    convenient recursive strategy is to “bridge” the exponent gap between consecutive terms using
    a power of x.
*/

#include <iostream>
using namespace std;

struct Term {
    double coef;
    int exp;
    Term* next;
    Term(double c, int e): coef(c), exp(e), next(nullptr) {}
};

// Build a polynomial from arrays coef[i], exp[i], i=0..m-1.
// Insert terms one-by-one so that the final list is strictly descending in exp
// and contains no duplicate exponents (combine coefs; drop zero terms).
Term* buildFromArrays(const double* coef, const int* exp, int m);
// Insert (c,e) into the sorted list (descending exponents).
// Combine coefficients if exp already exists; remove node if coef becomes 0.
void insertTerm(Term*& head, double c, int e);
// Remove the term with exponent e, if present.
void eraseExp(Term*& head, int e);
// Recursively compute x^k for k>=0 using fast exponentiation.
// Must run in O(log k).
double powInt(double x, int k);

// Recursive evaluation of the polynomial at x.
// Assume list is strictly descending in exp with no duplicates.
// Hint: if current node is (c,e) and next is (c2,e2), multiply the running
// value by x^(e - e2) before adding c2, and recurse.
double evalRecursive(const Term* head, double x);