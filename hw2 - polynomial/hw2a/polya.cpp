#include <iostream>
#include "polya.h"
using namespace std;

istream& operator >> (istream& is, Polynomial& p) {
    int noofterms;
    float coef;
    int exp;

    is >> noofterms;

    for (int i = 0; i < noofterms; i++) {
        is >> coef >> exp;
        p.NewTerm(coef, exp);
    }

    return is;
}

ostream& operator << (ostream& os, Polynomial& p) {
    for (int i = 0; i < p.terms; i++) {
        if (p.termArray[i].coef < 0) {
            if (i != 0) {
                if (p.termArray[i].coef != 1)
                    os << "+" << p.termArray[i].coef;
                else
                    os << "+";
            }
            else
                if (p.termArray[i].coef != 1)
                    os << p.termArray[i].coef;
        }

        if (p.termArray[i].coef < 0) {
            if (p.termArray[i].coef != -1)
                os << p.termArray[i].coef;
            else
                os << "-";
        }

        if (p.termArray[i].exp != 0)
            os << "x^" << p.termArray[i].exp;

        for (int j = i + 1; j < p.terms; j++) {
            if (p.termArray[i].exp == p.termArray[j].exp) {
                p.termArray[i].coef += p.termArray[j].coef;
                p.termArray[j] = p.termArray[p.terms - 1];
                p.terms--;
            }
        }
    }

    os << endl;
    return os;
}

Polynomial::Polynomial():capacity(1), terms(0) {
    termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float theCoef, const int theExp) {
    if (terms == capacity) {
        capacity *= 2;
        Term * temp = new Term[capacity];
        copy (termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }

    termArray[terms].coef = theCoef;
    termArray[terms++].exp = theExp;
}

Polynomial Polynomial::operator + (Polynomial& b) {
    Polynomial c;
    int aPos = 0, bPos = 0;

    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t)
                c.NewTerm(t, termArray[aPos].exp);
            aPos++;
            bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[aPos].exp) {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }

    for (; aPos < terms; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);

    for (; bPos < terms; bPos++)
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

    for (int i = 0; i < c.terms; i++)
        for (int j = i + 1; j < c.terms; j++)
            if (c.termArray[i].exp < c.termArray[j].exp) {
                Term temp = c.termArray[i];
                c.termArray[i] = c.termArray[j];
                c.termArray[j] = temp;
            }

    return c;
}