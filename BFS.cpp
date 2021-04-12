#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

const int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int Board[9]; int iniPos;

bool cases[362881] = {0};

struct Step {
    int board[9];
    int depth;
    int pos;
    Step(int* board, int depth, int pos):board(board), depth(depth), pos(pos){}
};

struct CompareStep {
    bool operator()(Step const& s1, Step const& s2)
    {
        return s1.depth < s2.depth;
    }
};

int cantorExpansion(int input[]) {
    int result = 0;
    for (int i = 0; i < 9; i++){
        int tmp = 0;
        for (int j=i+1; j<9;j++){
            if(input[j]<input[i]){
                tmp++;
            }
        }
        result+=fac[8 - i]*tmp;
    }
}

int* reverseCantor(int input) {
    int result[9];
    for (int i = 0; i < 9; i++){
        int tmp = input/fac[8-i];
        input input%fac[8-i];
        result[i] = i + tmp + 1;
    }
}

void BFS(){
    priority_queue<Step, vector<Step>, CompareStep> pq;
    Step ini = new Step(Board, 0, iniPos);
    cases[cantorExpansion(Board)] = -1;
    pq.push(ini);

    while(!pq.empty()){
        Step s = pq.pop();
        int cantor = cantorExpansion(s.board);
        int pos = s.pos;
        int x = pos % 3;
        int y = pos / 3;
        int depth = s. depth;
        if(x > 0){
            int xx = x - 1;
            int tmpPos = y*3 + xx;
            int tmp = s.board[tmpPos];
            Step tmpS = s;
            tmpS.board[tmpPos] = 0;
            tmpS.board[pos] = tmp;
            int tmpCantor = cantorExpension(tmpS.board);
            if(tmpCantor == 0) {
                cases[tmpCantor] = cantor;
                return;
            }
            if(cases[tmpCantor] == 0){
                tmpS.depth ++;
                tmpS.pos = tmpPos;
                cases[tmpCantor] = cantor;
                pq.push(tmpS);
            }
        }
        if(x < 2){
            int xx = x + 1;
            int tmpPos = y*3 + xx;
            int tmp = s.board[tmpPos];
            Step tmpS = s;
            tmpS.board[tmpPos] = 0;
            tmpS.board[pos] = tmp;
            int tmpCantor = cantorExpension(tmpS.board);
            if(tmpCantor == 0) {
                cases[tmpCantor] = cantor;
                return;
            }
            if(cases[tmpCantor] == 0){
                tmpS.depth ++;
                tmpS.pos = tmpPos;
                cases[tmpCantor] = cantor;
                pq.push(tmpS);
            }
        }
        if(y > 0){
            int yy = y - 1;
            int tmpPos = yy*3 + x;
            int tmp = s.board[tmpPos];
            Step tmpS = s;
            tmpS.board[tmpPos] = 0;
            tmpS.board[pos] = tmp;
            int tmpCantor = cantorExpension(tmpS.board);
            if(tmpCantor == 0) {
                cases[tmpCantor] = cantor;
                return;
            }
            if(cases[tmpCantor] == 0){
                tmpS.depth ++;
                tmpS.pos = tmpPos;
                cases[tmpCantor] = cantor;
                pq.push(tmpS);
            }
        }
        if(y < 2){
            int yy = y + 1;
            int tmpPos = yy*3 + x;
            int tmp = s.board[tmpPos];
            Step tmpS = s;
            tmpS.board[tmpPos] = 0;
            tmpS.board[pos] = tmp;
            int tmpCantor = cantorExpension(tmpS.board);
            if(tmpCantor == 0) {
                cases[tmpCantor] = cantor;
                return;
            }
            if(cases[tmpCantor] == 0){
                tmpS.depth ++;
                tmpS.pos = tmpPos;
                cases[tmpCantor] = cantor;
                pq.push(tmpS);
            }
        }
    }
}   

void print() {
    Stack<char> opr;
    int cur = 0;
    while(cases[cur] != -1) {
        int* boardX = reverseCantor(cases[cur]);
        int* boardY = reverseCantor(cur);
        int posX, posY;
        for (int i=0;i<9;i++){
            if(boardX[i] == 0){
                posX = i;
            }
            if(boardY[i] == 0){
                posY = i;
            }
        }
        x1 = posX%3;
        y1 = posX/3;
        x2 = posY%3;
        y2 = posY/3;
        
    }
}

int main(){
    
    for(int i=0;i<9;i++){
        char x;
        cin >> x;
        Board[i] = x - '0';
        if(Board[i] == 0){
            iniPos = i;
        }
    }

    BFS();

    print();

    return 0;
}