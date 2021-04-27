#include<iostream>
#include<vector>

using namespace std;

void print1D(vector<int>& arr){
    for(int ele : arr)
        cout << ele << " ";
    cout << endl;
}

void print2D(vector<vector<int>>& arr){
    for(vector<int>& v : arr)
        print1D(v);
}

//finonacchi ====================================================================================
//input n is >= 0

//recursive. time : O(2^N), space : O(N)
int fibo_rec(int n){
    if(n <= 1)
        return n;
    
    int ans = fibo_rec(n-1) + fibo_rec(n-2);
    return ans;
}

//memoized. time : O(N), space : O(N)
int fibo_memo(int n, vector<int>& dp){
    if(n <= 1)
        return dp[n] = n;

    if(dp[n] != -1)
        return dp[n];

    int ans = fibo_memo(n-1, dp) + fibo_memo(n-2, dp);

    return dp[n] = ans;
}

//tabulated. time : O(N), space : O(N)
int fibo_tab(int N, vector<int>& dp){
    for(int n = 0; n <= N; ++n){
        if(n <= 1){
            dp[n] = n;
            continue;
        }

        int ans = dp[n-1] + dp[n-2];
        dp[n] = ans;
    }
    return dp[N];
}

//two pointer. time : O(N), space : O(1)
int fibo_03(int N){
    int a = 0, b = 1;
    for(int n = 0; n < N; ++n){
        cout << a << " ";

        int sum = a + b;
        a = b;
        b = sum;
    }
    cout << a << " " << endl;
    return a;
}


//maze path 1 jump ===========================================================================================================

//recursive. time : O(3^max(R,C))

//memoized. time : O(R*C)
int maze1_memo(int sr, int sc, int dr, int dc, vector<vector<int>>& dp){
    if(sr == dr && sc == dc)
        return dp[sr][sc] = 1;

    if(dp[sr][sc] != 0)
        return dp[sr][sc];
    
    int count = 0;
    if(sc+1 <= dc)
        count += maze1_memo(sr, sc+1, dr, dc, dp);
    if(sr+1 <= dr && sc <= dc)
        count += maze1_memo(sr+1, sc+1, dr, dc, dp);
    if(sr+1 <= dr)
        count += maze1_memo(sr+1, sc, dr, dc, dp);
    
    return dp[sr][sc] = count;
}

//tabulated
int maze1_tab(int sr, int sc, int dr, int dc, vector<vector<int>>& dp){
    for(sr = dr; sr > -1; --sr){
        for(sc = dc; sc > -1; --sc){
            
            if(sr == dr && sc == dc){ 
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            if(sc+1 <= dc)
                count += dp[sr][sc+1]; //maze1_memo(sr, sc+1, dr, dc, dp);
            if(sr+1 <= dr && sc <= dc)
                count += dp[sr+1][sc+1]; //maze1_memo(sr+1, sc+1, dr, dc, dp);
            if(sr+1 <= dr)
                count += dp[sr+1][sc]; //maze1_memo(sr+1, sc, dr, dc, dp);
            
            dp[sr][sc] = count;
        }
    }

    //since we changed sr and sc in loop, therefore cant use them now
    return dp[0][0];
}


//maze path multiple jump ===========================================================================================================

//memoized
int maze2_memo(int sr, int sc, int dr, int dc, vector<vector<int>>& dp){
    if(sr == dr && sc == dc)
        return dp[sr][sc] = 1;

    if(dp[sr][sc] != 0)
        return dp[sr][sc];
    
    int count = 0;
    for(int i = 1; i <= dc; ++i)
        if(sc+i <= dc)
            count += maze2_memo(sr, sc+i, dr, dc, dp);

    for(int i = 1; i <= min(dr,dc); ++i)
        if(sr+i <= dr && sc+i <= dc)
            count += maze2_memo(sr+i, sc+i,dr, dc, dp);

    for(int i = 1; i <= dr; ++i)
        if(sr+i <= dc)
            count += maze2_memo(sr+i, sc, dr, dc, dp);

    return dp[sr][sc] = count;
}

//tabulated
int maze2_tab(int sr, int sc, int dr, int dc, vector<vector<int>>& dp){
    for(sr = dr; sr > -1; --sr){
        for(sc = dc; sc > -1; --sc){

            if(sr == dr && sc == dc){
                dp[sr][sc] = 1;
                continue;
            }
                
            int count = 0;
            for(int i = 1; i <= dc; ++i)
                if(sc+i <= dc)
                    count += dp[sr][sc+i];

            for(int i = 1; i <= min(dr,dc); ++i)
                if(sr+i <= dr && sc+i <= dc)
                    count += dp[sr+i][sc+i];

            for(int i = 1; i <= dr; ++i)
                if(sr+i <= dc)
                    count += dp[sr+i][sc];

            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}


int main(){

    int r = 3, c = 3;
    vector<vector<int>> dp(r, vector<int>(c,0));
    cout << maze2_tab(0,0,r-1,c-1,dp) << endl;
    print2D(dp);
    return 0;
}