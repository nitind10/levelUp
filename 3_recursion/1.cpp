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




