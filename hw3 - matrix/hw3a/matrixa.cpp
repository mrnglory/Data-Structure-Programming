#include <iostream>
#include "matrixa.h"
using namespace std;

Matrix::Matrix(int a, int b, int c, int d) {
    int arr[2][2] = {a, b, c, d};

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            m[i][j] = arr[i][j];
}

void Matrix::Transpose() {
    int arr[2][2];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            arr[i][j] = m[i][j];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            m[i][j] = arr[i][j];
}

Matrix Matrix::operator + (const Matrix &a) {
    int arr[2][2];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            arr[i][j] = m[i][j] + a.m[i][j];

    return Matrix(arr[0][0], arr[0][1], arr[1][0], arr[1][1]);
}

Matrix Matrix::operator - (const Matrix &a) {
    int arr[2][2];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            arr[i][j] = m[i][j] - a.m[i][j];

    return Matrix(arr[0][0], arr[0][1], arr[1][0], arr[1][1]);
}

Matrix Matrix::operator * (const Matrix &a) {
    int arr[2][2] = {0, 0, 0, 0};

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                arr[i][k] = m[i][j] * a.m[j][k];

    return Matrix(arr[0][0], arr[0][1], arr[1][0], arr[1][1]);
}

void Matrix::operator = (const Matrix &a) {
    int arr[2][2];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            m[i][j] = a.m[i][j];
}

void Matrix::ShowMatrix() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
}