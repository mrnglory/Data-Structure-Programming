#include "matrixa.h"
#include <iostream>
using namespace std;

int main() {
    Matrix matrix1(1, 2, 3, 4);
    Matrix matrix2(1, 1, 1, 1);
    Matrix matrix3;

    cout << "----------------" << endl;
    cout << "Matrix Transpose" << std::endl;
    cout << "----------------" << endl;

    matrix1.Transpose();
    matrix1.ShowMatrix();
    matrix1.Transpose();

    cout << "----------------" << endl;
    cout << "Matrix Add" << std::endl;
    cout << "----------------" << endl;

    matrix3 = matrix1 + matrix2;
    matrix3.ShowMatrix();

    cout << "----------------" << endl;
    cout << "Matrix Sub" << std::endl;
    cout << "----------------" << endl;

    matrix3 = matrix1 - matrix2;
    matrix3.ShowMatrix();

    cout << "----------------" << endl;
    cout << "Matrix Multi" << std::endl;
    cout << "----------------" << endl;

    matrix3 = matrix1 * matrix2;
    matrix3.ShowMatrix();

    cout << "----------------" << endl;

    return 0;
}