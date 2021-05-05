#include<iostream>
#include<vector>
#include<algorithm>

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


//115 ================================================================================================================
//sir did it in diff direction (n,m) to (0,0) so see that java code in submissions 

int numDistinct_memo(string& s, int sIdx, string& t, int tIdx, vector<vector<int>>& dp){
        //s is finished but requirement is still there || requirement is > s
        if(sIdx == s.length() && tIdx < t.length() || (t.length() - tIdx) > (s.length() - sIdx))
            return dp[sIdx][tIdx] = 0;
        //requirement is finished
        if(tIdx == t.length())
            return dp[sIdx][tIdx] = 1;
        
        if(dp[sIdx][tIdx] != -1)
            return dp[sIdx][tIdx];
        
        int ans = 0;
        
        //considering
        if(s[sIdx] == t[tIdx])
            ans += numDistinct_memo(s, sIdx+1, t, tIdx+1, dp);
        
        //not considering
        ans += numDistinct_memo(s, sIdx+1, t, tIdx, dp);
        
        return dp[sIdx][tIdx] = ans;
    }
    
    int numDistinct_tab(string& s, int SIdx, string& t, int TIdx, vector<vector<int>>& dp){
        for(int sIdx = s.length(); sIdx > -1; --sIdx){
            for(int tIdx = 0; tIdx <= t.length(); ++tIdx){
               
                if(sIdx == s.length() && tIdx < t.length() || (t.length() - tIdx) > (s.length() - sIdx)){
                     dp[sIdx][tIdx] = 0;
                    continue;
                }
                   
                //requirement is finished
                if(tIdx == t.length()){
                    dp[sIdx][tIdx] = 1;
                    continue;
                }
                
                long ans = 0;

                //considering
                if(s[sIdx] == t[tIdx])
                    ans += dp[sIdx+1][tIdx+1];

                //not considering
                ans += dp[sIdx+1][tIdx];

                dp[sIdx][tIdx] = int(ans);
            }
        }
        return dp[SIdx][TIdx];
    }
    int numDistinct(string s, string t) {
        int sLen = s.length(), tLen = t.length();
        vector<vector<int>> dp(sLen+1, vector<int>(tLen+1, -1));
        int ans = numDistinct_memo(s, 0, t, 0, dp);
        for(vector<int>&v:dp){
            for(int ele:v)cout<<ele<<" ";
            cout<<endl;
        }
        return ans;
    }