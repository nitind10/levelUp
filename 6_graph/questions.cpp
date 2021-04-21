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




// === topolocial sort type ==============================================
//207 
bool kahnsAlgo(vector<vector<int>>& graph){
    int N = graph.size();
    vector<int> indegree(N, 0);

    for(int i = 0; i < N; ++i){
        for(int e : graph[i])
            indegree[e]++;
    }

    queue<int> que;
    int count = 0;

    for(int i = 0; i < N; ++i)
        if(indegree[i] == 0)
            que.push(i);

    while(que.size() != 0){
        int size = que.size();

        while(size--){
            int rv = que.front();
            que.pop();
            count++;

            for(int e : graph[rv]){
                if(--indegree[e] == 0)
                    que.push(e);
            }
        }
    }

    return count == N;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    if(prerequisites.size() == 0)
        return true;
    
    vector<vector<int>> graph(numCourses);
    for(int i = 0; i < prerequisites.size(); ++i)
        graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
    
    return kahnsAlgo(graph);
    
}

//210 ===================================================================
vector<int> kahnsAlgo(vector<vector<int>>& graph){
        int N = graph.size();
        vector<int> indegree(N, 0);

        for(int i = 0; i < N; ++i){
            for(int e : graph[i])
                indegree[e]++;
        }

        queue<int> que;
        vector<int> ans;

        for(int i = 0; i < N; ++i)
            if(indegree[i] == 0)
                que.push(i);

        while(que.size() != 0){
            int size = que.size();

            while(size--){
                int rv = que.front();
                que.pop();
                ans.push_back(rv);

                for(int e : graph[rv]){
                    if(--indegree[e] == 0)
                        que.push(e);
                }
            }
        }

        if(ans.size() == N){
            reverse(ans.begin(), ans.end());
            return ans;
        }
         else
             return {};
}
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    for(int i = 0; i < prerequisites.size(); ++i)
        graph[prerequisites[i][0]].push_back(prerequisites[i][1]);

    return kahnsAlgo(graph);
}

//329 ===================================================================================
void findIndegree(vector<vector<int>>& indegree, vector<vector<int>>& matrix, int m, int n, vector<vector<int>>& dir){
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                for(int k = 0; k < dir.size(); ++k){
                    int r = i + dir[k][0];
                    int c = j + dir[k][1];
                    
                    if(r > -1 && r < m && c > -1 && c < n && matrix[r][c] > matrix[i][j])
                        indegree[r][c]++;
                }
            }
        }
    }
    
int kahnsAlgo(int m, int n, vector<vector<int>>& indegree, vector<vector<int>>& matrix, vector<vector<int>>& dir){
    queue<int> que;
    
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            if(indegree[i][j] == 0){
                int oneDidx = i * n + j;
                que.push(oneDidx);
            }
        }
    }
    
    int level = 0;
    while(que.size() != 0){
        int size = que.size();
        
        while(size--){
            int rv = que.front();
            que.pop();
            
            int x = rv / n;
            int y = rv % n;
            
            for(int k = 0; k < dir.size(); ++k){
                int r = x + dir[k][0];
                int c = y + dir[k][1];
                
                if(r > -1 && r < m && c > -1 && c < n && matrix[r][c] > matrix[x][y]){
                    if(--indegree[r][c] == 0){
                        int oneDidx = r * n + c;
                        que.push(oneDidx);
                    }
                }     
            }  
        }
        level++;
    }
    return level;
}

int longestIncreasingPath(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    
        vector<vector<int>> dir {{-1,0}, {0,1}, {1,0}, {0,-1}};
    
    vector<vector<int>> indegree(m, vector<int>(n, 0));
    findIndegree(indegree, matrix, m, n, dir);
    
    return kahnsAlgo(m, n, indegree, matrix, dir);
}


//union find type ==========================================================
//684 ========================================
vector<int> par;

int findPar(int u){
    return par[u] == -1 ? u : par[u] = findPar(par[u]);
}

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    
    par.resize(n+1, -1);
    
    for(vector<int>& edge : edges){
        int p1 = findPar(edge[0]);
        int p2 = findPar(edge[1]);
        
        if(p1 != p2){
            par[p2] = p1;
            //or write this: par[p1] = p2;
        }
        else{
            return edge;
        }
    }
    return  {};
}

//LOCKED 1061 =======================================================================
string smallestEquivalentString(string A, string B, string S)
{
    for (int i = 0; i < 26; i++)
        par.push_back(i);
    // par.resize(26,-1);

    for (int i = 0; i < A.length(); i++)
    {
        int p1 = findPar(A[i] - 'a');
        int p2 = findPar(B[i] - 'a');

        par[p1] = min(p1, p2);
        par[p2] = min(p1, p2);

        //     if(p1 < p2)
        //         par[p2] = p1;
        //     else if(p2 < p1)par[p1] = p2;
        //
    }

    string ans = "";
    for (int i = 0; i < S.length(); i++)
    {
        ans += (char)(findPar(S[i] - 'a') + 'a');
    }

    return ans;
}

//839 =======================================================================
vector<int> par;
    int findPar(int u){
        return par[u] == u ? u : par[u] = findPar(par[u]);
    }
    
    bool isSimilar(string &s1, string &s2)
{
    int count = 0;
    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] != s2[i] && ++count > 2)
            return false;
    }

    return true;
}

int numSimilarGroups(vector<string> &strs)
{

    int count = strs.size();
    int n = strs.size();

    par.resize(n);
    for (int i = 0; i < n; i++)
        par[i] = i;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (isSimilar(strs[i], strs[j]))
            {
                int p1 = findPar(i);
                int p2 = findPar(j);

                if (p1 != p2)
                {
                    par[p1] = p2;
                    count--;
                }
            }
        }
    }

    return count;
}

//305 ============================================================================
vector<int> numIslands2(int m, int n, vector<vector<int>> &positions)
{
    par.resize(m * n, -1);

    vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    vector<vector<int>> grid(m, vector<int>(n, 0));
    int count = 0;
    vector<int> ans;
    for (vector<int> &pos : positions)
    {
        int i = pos[0];
        int j = pos[1];

        if (grid[i][j] != 1)
        {

            grid[i][j] = 1;
            count++;

            for (int d = 0; d < 4; d++)
            {
                int x = i + dir[d][0];
                int y = j + dir[d][1];

                if (x >= 0 && y >= 0 && x < m && y < n && grid[x][y] == 1)
                {
                    int p1 = findPar(i * n + j);
                    int p2 = findPar(x * n + y);

                    if (p1 != p2)
                    {
                        count--;
                        par[p1] = p2;
                    }
                }
            }
        }

        ans.push_back(count);
    }

    return ans;
}

//method2 without space
vector<int> numIslands2(int m, int n, vector<vector<int>> &positions)
{
    par.resize(m * n, -1);

    vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int count = 0;
    vector<int> ans;
    for (vector<int> &pos : positions)
    {
        int i = pos[0];
        int j = pos[1];

        if (par[i * n + j] == -1)
        {

            par[i * n + j] = (i * n + j);
            count++;

            for (int d = 0; d < 4; d++)
            {
                int x = i + dir[d][0];
                int y = j + dir[d][1];

                if (x >= 0 && y >= 0 && x < m && y < n && par[x * n + y] != -1)
                {
                    int p1 = findPar(i * n + j);
                    int p2 = findPar(x * n + y);

                    if (p1 != p2)
                    {
                        count--;
                        par[p1] = p2;
                    }
                }
            }
        }

        ans.push_back(count);
    }

    return ans;
}

//1168 ===================================================================================
vector<int> par;
int minCostToSupplyWater_(int N, vector<vector<int>> &Edges)
{

    for (int i = 0; i <= N; i++)
    {
        par.push_back(i);
    }

    int cost = 0;

    for (vector<int> &edge : Edges)
    {
        int u = edge[0], v = edge[1], w = edge[2];
        int p1 = findPar(u);
        int p2 = findPar(v);

        if (p1 != p2)
        {
            par[p1] = p2;
            cost += w;
        }
    }

    return cost;
}

int minCostToSupplyWater(int n, vector<int> &wells, vector<vector<int>> &pipes)
{
    for (int i = 0; i < wells.size(); i++)
    {
        pipes.push_back({0, i + 1, wells[i]});
    }

    sort(pipes.begin(), pipes.end(), [](vector<int> &a, vector<int> &b) {
        return a[2] < b[2];
    });

    return minCostToSupplyWater_(n, pipes);

//200 ===============================================================
 int findPar(int u, vector<int>& par){
        return par[u] == -1 ? u : par[u] = findPar(par[u], par);
    }
    void unionFind(vector<vector<char>>& grid, vector<int>& par, vector<vector<int>>& dir, int idx){
        int m = grid.size();
        int n = grid[0].size();
        int r = idx / n;
        int c = idx % n;
        int p1 = findPar(r*n + c, par);
        
        for(int i = 0; i < dir.size(); ++i){
            int x = r + dir[i][0];
            int y = c + dir[i][1];
            
            if(x > -1 && x < m && y > -1 && y < n && grid[x][y] == '1'){
                int p2 = findPar(x*n +y, par);
                if(p1 != p2){
                    par[p2] = p1;
                }
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dir {{1,0}, {0,1}};
        
        vector<int> par(m*n, -1);
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] == '1'){
                    unionFind(grid, par, dir, i*n + j);
                }
            }
        }
        
        int islands = 0;
        for(int i = 0; i < par.size(); ++i){
            cout<<par[i] << " ";
            if(par[i] == -1 && grid[i/n][i%n] == '1')
                islands++;
        }
        return islands;
    }

//695 similar
//journey to moon hackerrank

//mr president https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/mr-president/ ==================================================================
int findPar(int u, vector<int>& par){
	return par[u] == u ? u : par[u] = findPar(par[u], par);
}

int unionFind(vector<vector<int>>& edges, int n, long k){
	vector<int> par(n + 1);
	for(int i = 0; i <= n; ++i)
		par[i] = i;
	
	long mCost = 0;
	vector<int> mstWeights;
	for(vector<int>& edge : edges){
		int u = edge[0], v = edge[1], w = edge[2];
		int p1 = findPar(u, par);
		int p2 = findPar(v, par);
		if(p1 != p2){
			par[p2] = p1;
			mstWeights.push_back(w);
			mCost += w;
			n--;
		}
	}

	//disconnected graph, no ans possible
	if(n > 1)
		return -1;
	//no transformation needed
	if(mCost <= k)
		return 0;
	
	int i = mstWeights.size() - 1;
	int ans = 0;
	while(mCost > k && i > -1){
		mCost -= mstWeights[i--];
		mCost++;
		ans++;
	}
	return mCost <= k ? ans : -1;
}

int mainForThisQues(){
	//wrote this for fast i/o
	ios_base::sync_with_stdio(false);

	int n,m;
	long k;
	cin >> n >> m >> k;

	vector<vector<int>> edges(m, vector<int>(3));
	for(int i = 0; i < m; ++i){
		cin >> edges[i][0];
		cin >> edges[i][1];
		cin >> edges[i][2];
	}
	sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b){
		return a[2] < b[2];
	});

	cout << unionFind(edges, n, k) << endl;
	return 0;
}

//815 ===================================================================================================================
 int numBusesToDestination(vector<vector<int>> &routes, int src, int dest)
{

    if (src == dest)
        return 0;
    int n = routes.size();
    unordered_map<int, vector<int>> busStandMapping;
    int busNumber = 0;
    for (vector<int> &busStandList : routes)
    {
        for (int busStand : busStandList)
        {
            busStandMapping[busStand].push_back(busNumber);
        }
        busNumber++;
    }

    unordered_set<int> isBusStandSeen;
    vector<bool> isBusSeen(n, false);

    queue<int> que;
    que.push(src);
    isBusStandSeen.insert(src);

    int level = 0;
    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            int busStand = que.front();
            que.pop();

            vector<int> allBuses = busStandMapping[busStand];
            for (int busNo : allBuses)
            {
                if (isBusSeen[busNo])
                    continue;

                for (int bs : routes[busNo]) // bs is bus stand
                {
                    if (isBusStandSeen.find(bs) == isBusStandSeen.end())
                    {
                        que.push(bs);
                        isBusStandSeen.insert(bs);

                        if (bs == dest)
                            return level + 1;
                    }
                }

                isBusSeen[busNo] = true;
            }
        }
        level++;
    }

    return -1;
}
