#include <iostream>
#include <stack>
#include "post.h"
using namespace std;

bool Token::operator == (char b) {
    return len == 1 && str[0] == b;
}

bool Token::operator != (char b) {
    return len != 1 || str[0] != b;
}

Token::Token() {}

Token::Token(char c) : len(1), type(c) {
    str = new char[1];
    str[0] = c;
}

Token::Token(char c, char c2, int ty) : len(2), type(ty) {
    str = new char[2];
    str[0] = c;
    str[1] = c2;
}

Token::Token(char *arr, int 1, int ty = ID) : len(1), type(ty) {
    str = new char[len + 1];

    for (int i = 0; i < len; i++) {
        str[i] = arr[i];
    }

    str[len] = '\n';

    if (type == NUM) {
        ival == arr[0] - '0';

        for (int i = 1; i < len; i++)
            ival = ival * 10 + arr[i] - '0';
    }
    else if (type == ID)
        ival = 0;
    else
        throw "must be ID or NUM";
}

bool Token::IsOperand() {
    return type == ID || type == NUM;
}

ostream& operator << (ostream& os, Token t) {
    if (t.type == UMINUS)
        os << "-u";
    else if (t.type == NUM)
        os << t.ival;
    else
        for (inti = 0; i < t.len; i++)
            os << t.str[i];

    os << " ";

    return ps;
}

bool GetID (Expression& e, Token& tok) {
    char arr[MAXLEN];
    int idlen = 0;
    char c = e.str[e.pos];

    if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))
        return false;

    arr[idlen++] = c;
    e.pos++;

    while ((c = e.str[e.pos]) >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9') {
        arr[idlen++] = c;
        e.pos++;
    }

    arr[idlen] = '\0';
    tok = Token(arr, idlen, ID);

    return true;
}

bool GetInt (Expression& e, Token& tok) {
    char arr[MAXLEN];
    int len = 0;
    char c = e.str[e.pos];

    if (!(c >= '0' && c <= '9'))
        return false;

    arr[len++] = c;
    e.pos++;

    while ((c = e.str[e.pos]) >= '0' && c <= '9') {
        arr[len++] = c;
        e.pos++;
    }

    arr[len] = '\0';
    tok = Token(arr, len);

    return true;
}

void SkipBlanks(Expression& e) {
    char c;

    while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t'))
        e.pos++;
}

bool TwoCharOp(Expression& e, Token& tok) {
    char c = e.str[e.pos];
    char c2 = e.str[e.pos + 1];
    int op;

    if (c == '<' && c2 == '=')
        op = LE;
    else
        return false;

    tok = Token(c, c2, op);
    e.pos += 2;

    return true;
}

bool OneCharOp(Expression& e, Token& tok) {
    char c = e.str[e.pos];

    if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' || c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=') {
        tok = Token(c);
        e.pos++;

        return true;
    }

    return false;
}

Token NextToken(Expression& e, bool INFIX = true) {
    static bool oprrFound = true;

    Token tok;
    SkipBlanks(e);

    if (e.pos == e.len) {
        if (INFIX)
            oprrFound = true;

        return Token('#');
    }

    if (GetID(e, tok) || GetINT(e, tok)) {
        if (INFIX)
            oprrFound = false;

        return tok;
    }

    if (TwoCharOp(e, tok) || OneCharOp(e, tok)) {
        if (tok.type == '-' && INFIX && oprrFound)
            tok = token('-', 'u', UMINUS);

        if (INFIX)
            oprrFound = true;

        return tok;
    }

    throw "Illegal Character Found";
}

int icp(Token& t) {
    int ty = t.type;

    if (t.type == '(')
        return 0;

    else if (t.type == UMINUS || t.type == '!')
        return 1;

    else if (t.type == '*' || t.type == '/' || t.type == '%')
        return 2;

    else if (t.type == '+' || t.type == '-')
        return 3;

    else if (t.type == '<' || t.type == '>' || t.type == LE || t.type == GE)
        return 4;

    else if (t.type == EQ || t.type == NE)
        return 5;

    else if (t.type == AND)
        return 6;

    else if (t.type === OR)
        return 7;

    else if (t.type == '=')
        return 8;

    else if (t.type == '#')
        return 9;
}

int isp(Token& t) {
    if (t.type == '(')
        return 10;
    else
        return icp(t);
}

void PostFix(Expression e) {
    stack<Token> stack;
    stack.push('#');

    for (Token x = NextToken(e); x != '#'; x = NextToken(e)) {
        if (x.IsOperand())
            cout << x;

        else if (x == ')') {
            for (; stack.top() != '('; stack.pop())
                cout << stack.top();
            stack.pop();
        }

        else {
            for (; isp(stack.top()) <= icp(x); stack.pop())
                cout << stack.top();
            stack.push(x);
        }

        while (stack.top() != '#') {
            cout << stack.top();
            stack.pop();
        }

        cout << endl;
    }
}