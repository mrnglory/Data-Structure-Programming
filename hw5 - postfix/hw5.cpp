#include <iostream>
#include "post.h"
using namespace std;

void PostFix(Expression);

int main() {
    char line[MAXLEN];

    while (cin.getline(line, MAXLEN)) {
        Expression e(line);

        try {
            PostFix(e);
        } catch (char const *msg) {
            cerr << "Exception: " << msg << endl;
        }
    }
}