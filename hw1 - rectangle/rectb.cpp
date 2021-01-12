#include <iostream>
#include "rectb.h"
using namespace std;

Rectangle::Rectangle (int x = 0, int y = 0, int h = 0, int w = 0)
: xLow(x), yLow(y), height(h), width(w) {}
ostream& operator << (ostream& os, Rectangle& s)
{
    os << "Position" << s.xLow << " " << s.yLow << ";Height = " << s.height << "Width = " << s.width << endl;
    return os;
}

bool Rectangle::operator < (Rectangle& s)
{
    if (height * width < s.height * s.width)
        return true;
    else
        return false;
}

bool Rectangle::operator == (Rectangle& s)
{
    if (height * width == s.height * s.width)
        return true;
    else
        return false;
}

int Rectangle::GetHeight()
{
    return height;
}

int Rectangle::GetWidth()
{
    return width;
}