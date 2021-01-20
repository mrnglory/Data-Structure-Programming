#include <iostream>
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
using namespace std;

class Polynomial;
class Term {
public:
    friend class Polynomial;
    friend ostream& operator << (ostream&, Polynomial&);
    friend istream& operator >> (istream&, Polynomial&);

private:
    float coef;
    int exp;
};

class Polynomial {
public:
    Polynomial();
    Polynomial operator + (Polynomial&);
    void NewTerm(const float, const int);

    friend ostream& operator << (ostream&, Polynomial);
    friend istream& operator >> (istream&, Polynomial);

private:
    Term *termArray;
    int capacity;
    int terms;
};
#endif