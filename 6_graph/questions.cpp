#include<iostream>
#include<vector>
using namespace std;

//DFS ===============================================================

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

//BFS ============================================================================

//1091 ======================================================================
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int r = grid.size();
    int c = r;
    
    if(grid[0][0] == 1 || grid[r-1][c-1] == 1)
        return -1;
    
    //src = grid[0][0], in  1d it will be x*c + y , where x = 0, y = 0
    queue<int> que;
    que.push(0);
    grid[0][0] = 1;
    
    int level = 1;
    vector<vector<int>> dir {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};
    
    while(que.size() != 0){
        int size = que.size();
        
        while(size--){
            int rv = que.front();
            que.pop();
            
            int x = rv / c;
            int y = rv % c;
            
            if(x == r - 1 && y == c - 1)
                return level;
            
            for(int i = 0; i < dir.size(); ++i){
                int ri = x + dir[i][0];
                int ci = y + dir[i][1];
                
                if(ri > -1 && ri < r && ci > -1 && ci < c && grid[ri][ci] == 0){
                    grid[ri][ci] = 1;
                    int oneDidx = ri * c + ci;
                    que.push(oneDidx);
                }
            }
            
        }
        level++;
    }
    return -1;
}

//785 ===================================================================
bool helper(int src, vector<int>& visited, vector<vector<int>>& graph){
    bool isCycle = false;

    int color = 0;
    
    //in visited array
    //-1 : not visited, 0 : red color, 1 : green color

    queue<int> que;
    que.push(src);

    while(que.size() != 0){
        int size = que.size();

        while(size--){
            int rv = que.front();
            que.pop();

            if(visited[rv] != -1){
                isCycle = true;
                
                if(visited[rv] != color)
                    return false;
                
                continue;
            }

            visited[rv] = color;

            for(int e : graph[rv]){
                if(visited[e] == -1)
                    que.push(e);
            }
        }
        color = (color + 1) % 2;
    }
    return true;
}
bool isBipartite(vector<vector<int>>& graph) {
    int N = graph.size();
    bool res = true;
    vector<int> visited(N, -1);
    
    //given graph can have more than 1 component too, hence do for every part of graph
    for(int i = 0; i < N; ++i){
        if(visited[i] == -1){
            res = res && helper(i, visited, graph);
        }
    }
    
    return res;
}

//994 =======================================================
int orangesRotting(vector<vector<int>>& grid) {
    int r = grid.size();
    int c = grid[0].size();
    
    vector<vector<int>> dir {{-1,0}, {0,1}, {1,0}, {0,-1}};
    int fresh = 0;
    queue<int> que;
    int time = 0;
    
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            if(grid[i][j] == 2){
                int oneDidx = i * c + j;
                que.push(oneDidx);
            }
            else if(grid[i][j] == 1){
                fresh++;
            }
        }
    }
    
    if(fresh == 0)
        return 0;
    
    while(que.size() != 0){
        int size = que.size();
        
        while(size--){
            int rv = que.front();
            que.pop();
            
            int x = rv / c;
            int y = rv % c;
            
            for(int i = 0; i < dir.size(); ++i){
                int ri = x + dir[i][0];
                int ci = y + dir[i][1];
                
                if(ri > -1 && ri < r && ci > -1 && ci < c && grid[ri][ci] == 1){
                    int oneDidx = ri * c + ci;
                    que.push(oneDidx);
                    grid[ri][ci] = 2;
                    fresh--;
                    if(fresh == 0)
                        return time + 1;
                }
            }
        }
        time++;
    }
    
    return -1;
}