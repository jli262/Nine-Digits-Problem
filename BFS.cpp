#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

const int fac[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

int Board[9]; int iniPos;

int cases[362881] = { 0 };

class Step {
public:
    int board[9];
    int depth;
    int pos;
    Step(int* b, int d, int p){
        for (int i = 0; i < 9; i++) {
            board[i] = b[i];
        }
        depth = d;
        pos = p;
    }
};

struct CompareStep {
    bool operator()(Step const& s1, Step const& s2)
    {
        return s1.depth < s2.depth;
    }
};

int cantorExpansion(int input[]) {
    int result = 0;
    for (int i = 0; i < 9; i++) {
        int tmp = 0;
        for (int j = i + 1; j < 9; j++) {
            if (input[j] < input[i]) {
                tmp++;
            }
        }
        result += fac[8 - i] * tmp;
    }
    return result;
}

int* reverseCantor(int input) {
    int result[9];
    for (int i = 0; i < 9; i++) {
        int tmp = input / fac[8 - i];
        input = fac[8 - i];
        result[i] = i + tmp + 1;
    }
    return result;
}

void BFS() {
    priority_queue<Step, vector<Step>, CompareStep> pq;
    Step ini = Step(Board, 0, iniPos);
    cases[cantorExpansion(Board)] = -1;
    pq.push(ini);

    while (!pq.empty()) {
        Step s = pq.top();
        pq.pop();
        int cantor = cantorExpansion(s.board);
        int pos = s.pos;
        int x = pos % 3;
        int y = pos / 3;
        int depth = s.depth;
        if (x > 0) {
            int xx = x - 1;
            int tmpPos = y * 3 + xx;
            int tmp = s.board[tmpPos];
            Step tmpS = s;
            tmpS.board[tmpPos] = 0;
            tmpS.board[pos] = tmp;
            int tmpCantor = cantorExpansion(tmpS.board);
            if (tmpCantor == 0) {
                cases[tmpCantor] = cantor;
                return;
            }
            if (cases[tmpCantor] == 0) {
                tmpS.depth++;
                tmpS.pos = tmpPos;
                cases[tmpCantor] = cantor;
                pq.push(tmpS);
            }
        }
        if (x < 2) {
            int xx = x + 1;
            int tmpPos = y * 3 + xx;
            int tmp = s.board[tmpPos];
            Step tmpS = s;
            tmpS.board[tmpPos] = 0;
            tmpS.board[pos] = tmp;
            int tmpCantor = cantorExpansion(tmpS.board);
            if (tmpCantor == 0) {
                cases[tmpCantor] = cantor;
                return;
            }
            if (cases[tmpCantor] == 0) {
                tmpS.depth++;
                tmpS.pos = tmpPos;
                cases[tmpCantor] = cantor;
                pq.push(tmpS);
            }
        }
        if (y > 0) {
            int yy = y - 1;
            int tmpPos = yy * 3 + x;
            int tmp = s.board[tmpPos];
            Step tmpS = s;
            tmpS.board[tmpPos] = 0;
            tmpS.board[pos] = tmp;
            int tmpCantor = cantorExpansion(tmpS.board);
            if (tmpCantor == 0) {
                cases[tmpCantor] = cantor;
                return;
            }
            if (cases[tmpCantor] == 0) {
                tmpS.depth++;
                tmpS.pos = tmpPos;
                cases[tmpCantor] = cantor;
                pq.push(tmpS);
            }
        }
        if (y < 2) {
            int yy = y + 1;
            int tmpPos = yy * 3 + x;
            int tmp = s.board[tmpPos];
            Step tmpS = s;
            tmpS.board[tmpPos] = 0;
            tmpS.board[pos] = tmp;
            int tmpCantor = cantorExpansion(tmpS.board);
            if (tmpCantor == 0) {
                cases[tmpCantor] = cantor;
                return;
            }
            if (cases[tmpCantor] == 0) {
                tmpS.depth++;
                tmpS.pos = tmpPos;
                cases[tmpCantor] = cantor;
                pq.push(tmpS);
            }
        }
    }
}

void print() {
    stack<char> opr;
    int cur = 0;
    while (cases[cur] != -1) {
        int* board = reverseCantor(cur);
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                opr.push('A' + i);
            }
        }
        cur = cases[cur];
    }
    while (!opr.empty()) {
        cout << opr.top();
        opr.pop();
    }
}

int main() {

    for (int i = 0; i < 9; i++) {
        char x;
        cin >> x;
        Board[i] = x - '0';
        if (Board[i] == 0) {
            iniPos = i;
        }
    }

    BFS();

    print();

    return 0;
}