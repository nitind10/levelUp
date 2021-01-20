//sudoku solutions
#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> board = {{3, 0, 0, 0, 0, 0, 0, 0, 0},
                             {5, 2, 0, 0, 0, 0, 0, 0, 0},
                             {0, 8, 7, 0, 0, 0, 0, 3, 1},
                             {0, 0, 3, 0, 1, 0, 0, 8, 0},
                             {9, 0, 0, 8, 6, 3, 0, 0, 5},
                             {0, 5, 0, 0, 9, 0, 6, 0, 0},
                             {1, 3, 0, 0, 0, 0, 2, 5, 0},
                             {0, 0, 0, 0, 0, 0, 0, 7, 4},
                             {0, 0, 5, 2, 0, 6, 3, 0, 0}};

vector<int> rowBits(9, 0);
vector<int> colBits(9, 0);
vector<int> matrixBits(9, 0);

bool isValid(int r, int c, int n){
    bool res1 = false, res2 = false, res3 = false;
    int mask = (1 << n);

    if((rowBits[r] & mask) != 0) res1 = true;
    if((colBits[c] & mask) != 0) res2 = true;
    if((matrixBits[(r / 3) * 3 + (c / 3)] & mask) != 0) res3 = true;

    if(res1 || res2 || res3) 
        return true;

    return false;
}

void toggleBits(int r, int c, int n){
        int mask = (1 << n);
        rowBits[r] ^= mask;
        colBits[c] ^= mask;
        matrixBits[(r / 3) * 3 + (c / 3)] ^= mask;
}

//function to mark bits releveant to initial non zero numbers of baord to 1
void initialToggle(){
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            if(board[i][j] != 0)
                toggleBits(i, j, board[i][j]);
        }
    }
}

void display()
{
    for (vector<int>& ar : board){ 
        for (int ele : ar){ 
            cout << ele << " ";
        }
        cout << endl;
    }
}

//very unoptimized, i did not use this for sudoku1, i could directly think of bits solution, so wrote it just for refference
bool isSafeToPlaceNumber(int r, int c, int num)
{
    // Row
    for (int i = 0; i < board[0].size(); i++)
        if (board[r][i] == num)
            return false;

    //Col
    for (int i = 0; i < board.size(); i++)
        if (board[i][c] == num)
            return false;

    // 3 X 3 matrix
    r = (r / 3) * 3;
    c = (c / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[r + i][c + j] == num)
                return false;
        }
    }

    return true;
}

//Sudoku 1
//uses bitmasking, counts and displays all possible solutions
int sudoku1(int idx)
{
    if (idx == 81){
        display();
        cout << endl;
        return 1;
    }

    int r = idx / 9;
    int c = idx % 9;
    int count = 0;

    if (board[r][c] != 0){
        return sudoku1(idx + 1);
    }

    for (int n = 1; n <= 9; n++){
        if (!isValid(r, c, n)){
            board[r][c] = n;
            toggleBits(r, c, n);
            count += sudoku1(idx + 1);
            toggleBits(r, c, n);
            board[r][c] = 0;
        }
    }
    return count;
}

//Sudoku 2 - prints 1st solution
bool sudoku2(int idx){
    if(idx == 81){
        display();
        return true;
    }

    bool res = false;
    int r = idx / 9;
    int c = idx % 9;

    if(board[r][c] != 0)
        return sudoku2(idx + 1);

    for(int n = 1; n <= 9; ++n){
        if(!isValid(r, c, n)){
            board[r][c] = n;
            toggleBits(r, c, n);
            res = res || sudoku2(idx + 1);
            toggleBits(r, c, n);
            board[r][c] = 0;
        }
    }
    return res;
}