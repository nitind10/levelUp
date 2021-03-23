#include<iostream>
#include<vector>
using namespace std;

//200 =============================================================================
vector<vector<int>> dir {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

void islandsHelper(int sr, int sc, vector<vector<char>>& grid){
    grid[sr][sc] = 0;
    
    for(int i = 0; i < dir.size(); ++i){
        int r = sr + dir[i][0];
        int c = sc + dir[i][1];
        
        if(r > -1 && r < grid.size() && c > -1 && c < grid[0].size() && grid[r][c] == '1')
            islandsHelper(r, c, grid);
    }
}
int numIslands(vector<vector<char>>& grid) {
    
    int islands = 0;
    for(int i = 0; i < grid.size(); ++i){
        for(int j = 0; j < grid[0].size(); ++j){
            if(grid[i][j] == '1'){
                islandsHelper(i, j, grid);
                islands++;
            }
        }
    }
    return islands;
}

//695 ===================================================================
vector<vector<int>> dir {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int helper(int sr, int sc, vector<vector<int>>& grid){
    grid[sr][sc] = 0;
    int area = 1;
    
    for(int i = 0; i < dir.size(); ++i){
        int r = sr + dir[i][0];
        int c = sc + dir[i][1];
        
        if(r > -1 && r < grid.size() && c > -1 && c < grid[0].size() && grid[r][c] == 1)
            area += helper(r, c, grid);
    }
    return area;
}
int maxAreaOfIsland(vector<vector<int>>& grid) {
    int maxArea = -1e8;
    for(int i = 0; i < grid.size(); ++i){
        for(int j = 0; j < grid[0].size(); ++j){
            if(grid[i][j] == 1){
                int ans = 0;
                ans = helper(i, j, grid);
                maxArea = max(maxArea, ans);
            }
        }
    }
    return maxArea == -1e8 ? 0 : maxArea;
}

//463 =========================================================================
int islandPerimeter(vector<vector<int>>& grid) {
    int ones = 0, nbrs = 0;
    for(int i = 0; i < grid.size(); ++i){
        for(int j = 0; j < grid[0].size(); ++j){
            if(grid[i][j] == 1){
                ones++;
                
                //front nbr
                if(j != grid[0].size() - 1 && grid[i][j+1] == 1)
                    nbrs++;
                //down nbr
                if(i != grid.size() - 1 && grid[i + 1][j] == 1)
                    nbrs++;
            }
        }
    }
    return (4 * ones) - (2 * nbrs);
}

//130 ===================================================================
void dfs(int sr, int sc, vector<vector<char>>& board, vector<vector<int>>& dir){
    board[sr][sc] = '@';
    
    for(int i = 0; i < dir.size(); ++i){
        int r = sr + dir[i][0];
        int c = sc + dir[i][1];
        
        if(r > -1 && r < board.size() && c > -1 && c < board[0].size() && board[r][c] == 'O')
            dfs(r, c, board, dir);
    }
}
void solve(vector<vector<char>>& board) {
    int r = board.size();
    int c = board[0].size();
    
    vector<vector<int>> dir {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    for(int i = 0; i < r; ++i){
        if(board[i][0] == 'O'){
            dfs(i, 0, board, dir);
        }
        if(board[i][c - 1] == 'O'){
            dfs(i, c - 1, board, dir);
        }
    }
    
    for(int j = 0; j < c; ++j){
        if(board[0][j] == 'O'){
            dfs(0, j, board, dir);
        }
        if(board[r - 1][j] == 'O'){
            dfs(r - 1, j, board, dir);
        }
    }
    
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            if(board[i][j] == 'O')
                board[i][j] = 'X';
            if(board[i][j] == '@')
                board[i][j] = 'O';
        }
        
    }
}