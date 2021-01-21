#include <iostream>
#include "matrixb.h"
using namespace std;

Matrix::Matrix(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
    int arr[3][3] = {a, b, c, d, e, f, g, h, i};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = arr[i][j];
}

void Matrix::Transpose() {
    int arr[3][3];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            arr[i][j] = m[i][j];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = arr[j][i];
}

Matrix Matrix::operator + (const Matrix &a) {
    int arr[3][3];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            arr[i][j] = m[i][j] + a.m[i][j];

    return Matrix(arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
}

Matrix Matrix::operator - (const Matrix &a) {
    int arr[3][3];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            arr[i][j] = m[i][j] - a.m[i][j];

    return Matrix(arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
}

Matrix Matrix::operator * (const Matrix &a) {
    int arr[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                arr[i][k] += m[i][j] * a.m[j][k];

    return Matrix(arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
}

void Matrix::operator = (const Matrix &a) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = a.m[i][j];
}

void Matrix::ShowMatrix() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
}