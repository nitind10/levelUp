// keypad extention, 10 = "+-*" , 11 = "/%^"
static string keypad[] = {
    ".;",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tu",
    "vwx",
    "yz",
    "+-*",
    "/%^"
};
void printKPC(string qsf, string asf) {
    if (qsf.length() == 0) {
        cout << asf;
        return;
    }
    char c = qsf[0];
    string ros = qsf.substr(1);
    int key = c - '0';
    string word = keypad[key];

    for (int i = 0; i < word.length(); ++i) {
        char inhand = word[i];
        printKPC(ros, asf + inhand);
    }
    
    if(qsf.length() >= 2){
        if( (qsf[0] - '0') * 10 + (qsf[1] - '0') == 10 || (qsf[0] - '0') * 10 + (qsf[1] - '0') == 11 ){
            string word2 = keypad[(qsf[0] - '0') * 10 + (qsf[1] - '0')];

            for (int i = 0; i < word2.length(); ++i) {
                char inhand = word2[i];
                printKPC(qsf.substr(2), asf + inhand);
            } 
        }
    }

}

//unique permutations in string
int printPermutationUnique(string str, string ans) {
    if (str.length() == 0) {
        cout << ans;
        return 1;
    }
    
    int count = 0;
    bool vis[26];
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (!vis[ch - 'a']) {
            vis[ch - 'a'] = true;
            string ros = str.substr(0, i) + str.substr(i + 1); // ros : rest of the string
            count += printPermutationUnique(ros, ans + ch);
        }
    }
    return count;
}

//unique paths in 8 directions with one jump
/* passed from main
    vector<string> dirS = {"U", "E", "R", "S", "D", "W", "L", "N"};
    vector<vector<int> > dir = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};

*/
int _8dirPaths(int sr, int sc, int dr, int dc, string psf, vector<vector<bool> > & visited, vector<string> & dirS, vector<vector<int> > dir){
    if(sr == dr && sc == dc){
        cout << psf << endl;
        return 1;
    }
    int count = 0;
    visited[sr][sc] = true;

    for(int i = 0; i < dirS.size(); ++i){
        int r = sr + dir[i][0];
        int c = sc + dir[i][1];
        if(r >= 0 && r <= dr && c >= 0 && c <= dc && visited[r][c] == false){
            count += _8dirPaths(r, c, dr, dc, psf + dirS[i], visited, dirS, dir);
        }
    }

    visited[sr][sc] = false;
    return count;
}

//unique path in 8 dir with jumps
int _8dirPaths(int sr, int sc, int dr, int dc, string psf, vector<vector<bool> > & visited, vector<string> & dirS, vector<vector<int> > dir){
    if(sr == dr && sc == dc){
        cout << psf << endl;
        return 1;
    }
    int count = 0;
    int rows = visited.size();
    int cols = visited[0].size();

    visited[sr][sc] = true;
    
    for(int i = 0; i < dirS.size(); ++i){

        for(int rad = 1; rad < max(rows, cols); ++rad){
            
            int r = sr + rad * dir[i][0];
            int c = sc + rad * dir[i][1];
            if(r >= 0 && r <= dr && c >= 0 && c <= dc){
                //we have put this visited condition inside, bcoz if cell at 2th jump is blocked, but at say 3th jump is open, then we want to do that 3th jump
                if(visited[r][c] == false)
                    count += _8dirPaths(r, c, dr, dc, psf + dirS[i] + to_string(rad), visited, dirS, dir);
            }
            else{
                break;
            }
        }
    }

    visited[sr][sc] = false;
    return count;
}

//https://practice.geeksforgeeks.org/problems/rat-in-a-maze-problem/1
vector<string> ratMaze(int m[MAX][MAX], int n, vector<string>& dirS, vector<vector<int> >& dir, int sr, int sc, int dr, int dc, vector<vector<bool> >& visited){
    
    if(sr == dr && sc == dc){
        vector<string> base;
        base.push_back("");
        return base;
    }
    
    vector<string> ans;
    visited[sr][sc] = true;
    for(int i=0; i<dirS.size(); ++i){
        int r = sr + dir[i][0];
        int c = sc + dir[i][1];
        if(r > -1 && r < n && c > -1 && c < n && m[r][c] != 0 && visited[r][c] == false){
            vector<string> rres = ratMaze(m, n, dirS, dir, r, c, n-1, n-1, visited);
            for(string s : rres){
                ans.push_back(dirS[i] + s);
            }
        }
    }
    visited[sr][sc] = false;
    return ans;
}
vector<string> printPath(int m[MAX][MAX], int n) {
    // Your code goes here
    if(m[0][0] == 0) return {};
    
    vector<vector<bool> > visited(n, vector<bool> (n, false));
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(m[i][j] == 0)
                visited[i][j] = true;
        }
    }
    vector<string> dirS = {"U","D","L", "R"};
    vector<vector<int> > dir = {{-1,0}, {1,0}, {0, -1}, {0, 1}};
    vector<string> ans = ratMaze(m, n, dirS, dir, 0, 0, n-1, n-1, visited);
    sort(ans.begin(), ans.end());
    return ans;
}

//https://practice.geeksforgeeks.org/problems/rat-maze-with-multiple-jumps/0#
void display(vector<vector<int>>& ans){
    for(int i=0; i<ans.size(); ++i){
        for(int j=0; j<ans[0].size(); ++j){
            cout  << ans[i][j] <<  " ";
        }
        cout << endl;
    }
}
bool mazeSolver(vector<vector<int>>& maze, vector<vector<int>>& ans, int sr, int sc, int dr, int dc, vector<vector<int>>& dir){
    
    if(sr == dr && sc == dc){
        ans[sr][sc] = 1;
        display(ans);
        ans[sr][sc] = 0;
        return true;
    }
    
    //mark yourself in path
    ans[sr][sc] = 1;
    bool res = false;
    
    for(int rad = 1; rad <= maze[sr][sc]; ++rad){
        for(int call = 0; call < dir.size(); ++call){
            int r = sr + rad * dir[call][0];
            int c = sc + rad * dir[call][1];
            if(r >= 0 && r <= dr && c >=0 && c <= dc)
                res = res || mazeSolver(maze, ans, r, c, dr, dc, dir); //will not call, after recieving 1st true
        }
    }
    
    ans[sr][sc] = 0;
    return res;
}
void inputfn(){
    int n;
    cin >> n;
    vector<vector<int>> maze(n, vector<int>(n, 0));
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin >> maze[i][j];
        }
    }
    bool res = false;
    if(maze[0][0] != 0){
        vector<vector<int>> ans(n, vector<int>(n, 0));
        vector<vector<int>> dir = { {0, 1}, {1, 0} };
        res = mazeSolver(maze, ans, 0, 0, n-1, n-1, dir);
    }

    if(res == false){
        cout << -1 << endl;
    }
}

//longest & shortest path to destination
pair<int, string> longest(int sr, int sc, int dr, int dc, vector<vector<int>>& vis, vector<vector<int>>& dir, vector<string>& dirS){
    if(sr == dr && sc == dc){
        return {0, ""};
    }
    pair<int, string> ans = {-1, ""};
    vis[sr][sc] = 1;
    for(int i=0; i<dirS.size(); ++i){
        int r = sr + dir[i][0];
        int c = sc + dir[i][1];
        if(r >=0 && r <= dr && c >=0 && c <= dc && vis[r][c] != 1){
            pair<int, string> rres = longest(r, c, dr, dc, vis, dir, dirS);
            // rres,first >= 0 is put for avoiding blockage area return and comparisons 
            if(rres.first >= 0 && rres.first + 1 > ans.first){
                ans.first = rres.first + 1;
                ans.second = dirS[i] + rres.second;
            }
        }
            
    }
    vis[sr][sc] = 0;
    return ans;
}
pair<int, string> shortest(int sr, int sc, int dr, int dc, vector<vector<int>>& vis, vector<vector<int>>& dir, vector<string>& dirS){
    if(sr == dr && sc == dc){
        return {0, ""};
    }
    pair<int, string> ans = {INT_MAX, ""};
    vis[sr][sc] = 1;
    for(int i=0; i<dirS.size(); ++i){
        int r = sr + dir[i][0];
        int c = sc + dir[i][1];
        if(r >=0 && r <= dr && c >=0 && c <= dc && vis[r][c] != 1){
            pair<int, string> rres = shortest(r, c, dr, dc, vis, dir, dirS);
            // rres,first != INT_MAX  is very imp, bcoz if we get lost(cell other than desitnation) and cant move anywhere we'll return intmax but cant do intmax+1, therefore dont compare for it
            if( rres.first != INT_MAX && rres.first + 1 < ans.first){
                ans.first = rres.first + 1;
                ans.second = dirS[i] + rres.second;
            }
        }
            
    }
    vis[sr][sc] = 0;
    return ans;
}
void inputfn(){
    int r, c;
    cin >> r >> c;
    vector<string> dirS = { "U", "D", "L", "R"};
    vector<vector<int> > dir = {{-1,0}, {1,0}, {0, -1}, {0, 1}};
    //considering no blockage here, can put cases like 0,0 should not be blocked etc if there was blockage
    vector<vector<int>> vis(r, vector<int> (c, 0));
    pair<int, string> ans = longest(0, 0, r-1, c-1, vis, dir, dirS);
    cout << ans.first << " " << ans.second << endl;
    pair<int, string> ans2 = shortest(0, 0, r-1, c-1, vis, dir, dirS);
    cout << ans2.first << " " << ans2.second << endl;
}


 


