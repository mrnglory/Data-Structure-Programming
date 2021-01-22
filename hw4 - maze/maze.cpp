#include <iostream>
#include <stack>
using namespace std;

const int MAXIZE = 100;
bool maze[MAXIZE + 2][MAXIZE + 2];
bool mark[MAXIZE + 1][MAXIZE + 1] = {0};

enum directions {N, NE, E, SE, S, SW, W, NW};

struct offsets {
    int a, b;
} move[8] = {-1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1};

struct Items {
    Items(int xx = 0, int yy = 0, int dd = 0): x(xx), y(yy), dir(dd) {}
    int x, y, dir;
};

template <class T>
ostream& operator << (ostream& os, stack<T>& s) {
    stack<T> s2;

    while (!s.empty()) {
        s2.push(s.top());
        s.pop();
    }

    while (!s2.empty()) {
        os << " -> " << s2.top();
        s2.pop();
    }

    return os;
}

ostream& operator << (ostream& os, Items& item) {
    static int count = 0;

    os << "(" << item.x << ", " << item.y << ")";
    count++;

    if ((count % 5) == 0)
        os << endl;

    return os;
}

void Path (const int m, const int p) {
    mark[1][1] = 1;
    stack<Items> stack;

    Items temp(1, 1, E);
    stack.push(temp);

    while (!stack.empty()) {
        temp = stack.top();
        stack.pop();

        int i = temp.x;
        int j = temp.y;
        int d = temp.dir;

        while (d < 8) {
            int g = i + move[d].a;
            int h = j + move[d].b;

            if ((g == m) && (h == p)) {
                int node = 0;

                cout << stack;

                temp.x = i;
                temp.y = j;
                cout << " -> " << temp;

                temp.x = m;
                temp.y = p;
                cout << " -> " << temp << endl;

                for (int i = 1; i < m + 1; i++)
                    for (int j = 1; j < p + 1; j++)
                        if (mark[i][j])
                            node++;

                cout << "#nodes visited = " << node << " out of " << m * p << endl;

                return;
            }

            if ((!maze[g][h]) && (!mark[g][h])) {
                mark[g][h] = 1;

                temp.x = i;
                temp.y = j;
                temp.dir = d + 1;

                stack.push(temp);
                i = g;
                j = h;
                d = N;
            } else d++;
        }
    }
    cout << "No path in maze." << endl;
}

void getdata (istream& is, int& m, int& p) {
    is >> m >> p;

    for (int i = 0; i < m + 2; i++) {
        maze[i][0] = 1;
        maze[i][p + 1] = 1;
    }

    for (int j = 1; j <= p; j++) {
        maze[0][j] = 1;
        maze[m + 1][j] = 1;
    }

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= p; j++)
            is >> maze[i][j];
}