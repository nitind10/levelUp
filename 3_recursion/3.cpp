//queen problems

//combination of queens in boxes (1D)
int queensInBoxes1DCombinations(int boxes, int queens, int currBox, int currQueen, string ans){

    if(currQueen == queens){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i = currBox; i < boxes; ++i){
        count += queensInBoxes1DCombinations(boxes, queens, i + 1, currQueen + 1, ans + "b" + to_string(i) + "q" + to_string(currQueen));
    }
    return count;
}

//permutations of queens in boxes (1D)
int queensInBoxes1DPermutations(int boxes, int queens, int currBox, int currQueen, string ans, vector<bool>& visited){

    if(currQueen == queens){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i = currBox; i < boxes; ++i){
        if(!visited[i]){
            visited[i] = true;
            count += queensInBoxes1DPermutations(boxes, queens, 0, currQueen + 1, ans + "b" + to_string(i) + "q" + to_string(currQueen), visited);
            visited[i] = false;
        }
    }
    return count;
}

//combination of queens in boxes (1D) SubSeq method
int queensInBoxes1DCombinationsSubSeq(int boxes, int queens, int currBox, int currQueen, string ans){

    if(currBox == boxes || currQueen == queens){
        if(currQueen == queens){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    
    count += queensInBoxes1DCombinationsSubSeq(boxes, queens, currBox + 1, currQueen + 1, ans + "b" + to_string(currBox) + "q" + to_string(currQueen));
    count += queensInBoxes1DCombinationsSubSeq(boxes, queens, currBox + 1, currQueen, ans);
    
    return count;
}

//permutation of queens in boxes (1D) SubSeq method
int queensInBoxes1DPermutationsSubSeq(int boxes, int queens, int currBox, int currQueen, string ans, vector<bool>& visited){

    if(currBox == boxes || currQueen == queens){
        if(currQueen == queens){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    
    if(!visited[currBox]){
        visited[currBox] = true;
        count += queensInBoxes1DPermutationsSubSeq(boxes, queens, 0, currQueen + 1, ans + "b" + to_string(currBox) + "q" + to_string(currQueen), visited);
        visited[currBox] = false;
    }
    count += queensInBoxes1DPermutationsSubSeq(boxes, queens, currBox + 1, currQueen, ans, visited);
    
    return count;
}

//combinations of queens in boxes (2D)
int queensInBoxes2DCombinations(int boxes, int queens, int currBox, string ans, int cols){

    if(queens == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i = currBox; i < boxes; ++i){
        count += queensInBoxes2DCombinations(boxes, queens - 1, i + 1, ans + "(" + to_string(i / cols) + "," + to_string(i % cols) + ") ", cols);
    }
    return count;
}

//permutations of queens in boxes (2D)
int queensInBoxes2DPermutations(int boxes, int queens, int currBox, string ans, vector<bool>& visited, int cols){

    if(queens == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i = currBox; i < boxes; ++i){
        if(!visited[i]){
            visited[i] = true;
            count += queensInBoxes2DPermutations(boxes, queens - 1, 0, ans + "(" + to_string(i / cols) + "," + to_string(i % cols) + ") ", visited, cols);
            visited[i] = false;
        }
    }
    return count;
}

// nqueens1 - least optimized - we go to every box check for safety(O(N)) and then placing
bool isSafe(int currRow, int currCol, vector<vector<bool>>& board){
    vector<vector<int>> dir = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    int r = board.size(); int c = board[0].size();
    
    for(int j = 0; j < dir.size(); ++j){
        for(int rad = 1; rad < max(r, c); ++rad){
            int rIdx = currRow + rad * dir[j][0];
            int cIdx = currCol + rad * dir[j][1];

            if(rIdx > -1 && rIdx < r && cIdx > -1 && cIdx < c){
                if(board[rIdx][cIdx])
                    return false;
            }
            else{
                break;
            }
        }
    }
    return true;
}
int nQueens1(int idx, int n, vector<vector<bool>>& board, int currQueens, int totalQueens, string ans){
    if(currQueens == totalQueens){
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for(int i = idx; i < n * n; ++i){ 
        int r = i / n;
        int c = i % n;
        if(isSafe(r, c, board)){
            board[r][c] = true;
            count += nQueens1(i + 1, n, board, currQueens + 1, totalQueens, ans + "(" + to_string(r) + "," + to_string(c) + ") ");
            board[r][c] = false;
        }
    }
    return count;
}

//nqueens2 - slightly optimized from 1 as checking safety is O(1), by using 4 arrays, also not keeping board matrix
//resize these vectors in main
vector<bool> row, col, diagonal, antiDiagonal;
void toggle(int r, int c, int n){
    row[r] = !row[r];
    col[c] = !col[c];
    diagonal[r - c + n - 1] = !diagonal[r - c + n - 1];
    antiDiagonal[r + c] = !antiDiagonal[r + c];
 }
int nQueens2(int idx, int n, int currQueens, int totalQueens, string ans){
    if(currQueens == totalQueens){
        cout << ans << endl;
        return 1;
    }
    int count = 0;

    for(int i = idx; i < n * n; ++i){ 
        int r = i / n;
        int c = i % n;
        if(!row[r] && !col[c] && !diagonal[r - c + n - 1] && !antiDiagonal[r + c]){
            toggle(r, c, n);
            count += nQueens2(i + 1, n, currQueens + 1, totalQueens, ans + "(" + to_string(r) + "," + to_string(c) + ") ");
            toggle(r, c, n);
        }
    }
    return count;
}