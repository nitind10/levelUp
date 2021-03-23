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
