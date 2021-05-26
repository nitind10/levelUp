//https://www.geeksforgeeks.org/applications-of-catalan-numbers/

//96 ==================================================
int numTrees(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        
        for(int i = 1; i <= n; ++i){
            for(int j = 0, k = i-1; k > -1; ++j, --k){
                dp[i] += (dp[j] * dp[k]);
            }
        }
        
        return dp[n];
    }

//1216

//40

//1278

//10

//95