#include<iostream>
#include<vector>

using namespace std;

//516 ================================================================================================
 int longPaliSubseq_memo(int i, int j, vector<vector<int>>& dp, string& s){
        if(i >= j){
            return dp[i][j] = (i > j) ? 0 : 1;
        }
        if(dp[i][j] != -1)
            return dp[i][j];
        
        if(s[i] == s[j])
            return longPaliSubseq_memo(i+1, j-1, dp, s) + 2;
        //not equal case
        return dp[i][j] = max(longPaliSubseq_memo(i+1, j, dp, s), longPaliSubseq_memo(i, j-1, dp, s));
    }
    
     int longPaliSubseq_tab_01(int I, int J, vector<vector<int>>& dp, string& s){
         int n = s.length();
        for(int i = n-1; i > -1; --i){
            for(int j = 0; j < n; ++j){
                 if(i >= j){
                    dp[i][j] = (i > j) ? 0 : 1;
                    continue;
                }
    
                if(s[i] == s[j]){
                    dp[i][j] = dp[i+1][j-1] + 2;
                    continue;
                }
                
                //not equal case
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
         return dp[I][J];
    }
    
    //gap methof filling, diagonally
    int longPaliSubseq_tab_02(int I, int J, vector<vector<int>>& dp, string& s){
        //here passed dp should have 0's by default (imp)
        int n = s.length();
        for(int gap = 0; gap < n; ++gap){
            for(int i = 0, j = gap; j < n; ++i,++j){
                if(i == j){
                    dp[i][j] = 1;
                    continue;
                }
                
                if(s[i] == s[j]){
                    dp[i][j] = dp[i+1][j-1] + 2;
                    continue;
                }
                
                //not equal case
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
        return dp[I][J];
    }
    
     //takes a lot of space
     int longPaliSubseq_tab_03_printAns(int I, int J, string& s){
         int n = s.length();
         vector<vector<string>> dp(n, vector<string>(n, ""));
        
        for(int gap = 0; gap < n; ++gap){
            for(int i = 0, j = gap; j < n; ++i,++j){
                if(i == j){
                    dp[i][j] = s[i];
                    continue;
                }
                
                if(s[i] == s[j]){
                    dp[i][j] = s[i] + dp[i+1][j-1] + s[i];
                }
                else{
                dp[i][j] = (dp[i+1][j].length() > dp[i][j-1].length()) ? dp[i+1][j] : dp[i][j-1];
                }
            }
        }
        cout << dp[I][J] << endl;
        return dp[I][J].length();
    }
    
    
    //backEngineering
    string longPaliSubseq_printAns_backEngineering(int i, int j, string& s, vector<vector<int>>& dp){
        //we need filled int dp for this
        if(dp[i][j] == 0)
            return "";
        if(dp[i][j] == 1)
            return string(1, s[i]);
        
        string rres;
        if(s[i] == s[j]){
            rres = longPaliSubseq_printAns_backEngineering(i+1, j-1, s, dp);
            rres = s[i] + rres + s[i];
        }
        else{
            if(dp[i][j-1] > dp[i+1][j])
                rres = longPaliSubseq_printAns_backEngineering(i, j-1, s, dp);
            else
                rres = longPaliSubseq_printAns_backEngineering(i+1, j, s, dp);  
        }
        return rres;
    }
    
    
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        //vector<vector<int>> dp(n, vector<int>(n, -1));
        
        
        //for tab_02, we need default 0's in dp
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int ans = longPaliSubseq_tab_02(0, n-1, dp, s);
        
        string res = longPaliSubseq_printAns_backEngineering(0, n-1, s, dp);
        cout << res << endl;
        return res.length();
        
        //return longPaliSubseq_printAns_backEngineering();
        
        //return longPaliSubseq_tab_03_printAns(0, n-1, s);
    }


//