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


//1143 =========================================================================================
int longestCommonSubsequence_memo(string& s, int sIdx, string& t, int tIdx, vector<vector<int>>& dp){
        if(sIdx == s.length() || tIdx == t.length()){
            return dp[sIdx][tIdx] = 0;
        }
        if(dp[sIdx][tIdx] != -1){
            return dp[sIdx][tIdx];
        }
        if(s[sIdx] == t[tIdx]){
            return dp[sIdx][tIdx] = longestCommonSubsequence_memo(s, sIdx+1, t, tIdx+1, dp) + 1;
        }else{
            return dp[sIdx][tIdx] = max(longestCommonSubsequence_memo(s, sIdx+1, t, tIdx, dp), longestCommonSubsequence_memo(s, sIdx, t, tIdx+1, dp));
        }
    }
    
    int longestCommonSubsequence_tab(string& s, int SIdx, string& t, int TIdx, vector<vector<int>>& dp){
        for(int sIdx = s.length(); sIdx > -1; --sIdx){
            for(int tIdx = t.length(); tIdx > -1; --tIdx){
                if(sIdx == s.length() || tIdx == t.length()){
                    dp[sIdx][tIdx] = 0;
                    continue;
                }
               
                if(s[sIdx] == t[tIdx])
                    dp[sIdx][tIdx] = dp[sIdx+1][tIdx+1] + 1;
                else
                    dp[sIdx][tIdx] = max(dp[sIdx+1][tIdx], dp[sIdx][tIdx+1]);
            }
        }
        return dp[SIdx][TIdx];
    }
    int longestCommonSubsequence(string s, string t) {
        vector<vector<int>> dp(s.length()+1, vector<int>(t.length()+1, -1));
        int ans = longestCommonSubsequence_tab(s, 0, t, 0, dp);
        
        for(vector<int>& v : dp){
            for(int ele : v)
                cout << ele << " ";
            cout << endl;
        }
        return ans;
    }

//1035 =================================================================================
int maxUncrossedLines_memo(vector<int>& A, int aIdx, vector<int>& B, int bIdx, vector<vector<int>>& dp){
        if(aIdx == A.size() || bIdx == B.size())
            return dp[aIdx][bIdx] = 0;
        if(dp[aIdx][bIdx] != -1)
            return dp[aIdx][bIdx];
        
        if(A[aIdx] == B[bIdx])
            return dp[aIdx][bIdx] = maxUncrossedLines_memo(A, aIdx+1, B, bIdx+1, dp) + 1;
        else
            return dp[aIdx][bIdx] = max(maxUncrossedLines_memo(A, aIdx+1, B, bIdx, dp), maxUncrossedLines_memo(A, aIdx, B, bIdx+1, dp));
    }
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        vector<vector<int>> dp(A.size()+1, vector<int>(B.size()+1, -1));
        return maxUncrossedLines_memo(A,0,B,0,dp);
    }


//1458 ================================================================================================
int maxDotProduct_memo(vector<int>& nums1, int i, vector<int>& nums2, int j, vector<vector<int>>& dp){
        if(i == nums1.size() || j == nums2.size()){
            //returninng INT_MIN will overflow in includingBothIandJ case;
            return dp[i][j] = -1e7;
        }
        if(dp[i][j] != -1e9)
            return dp[i][j];
        
        int myProduct = nums1[i]*nums2[j];
        int includingBothIandJ = myProduct + maxDotProduct_memo(nums1, i+1, nums2, j+1, dp);
        int notConsideringJ = maxDotProduct_memo(nums1, i, nums2, j+1, dp);
        int notConsideringI = maxDotProduct_memo(nums1, i+1, nums2, j, dp);
        
        return dp[i][j] = max({myProduct, includingBothIandJ, notConsideringJ, notConsideringI});
    }
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size()+1, vector<int>(nums2.size()+1, -1e9));
        return maxDotProduct_memo(nums1, 0, nums2, 0, dp);
    }

//72 ========================================================================================================
int minDistance_memo(string& word1, int i, string& word2, int j, vector<vector<int>>& dp){
        if(i == word1.length() && j == word2.length())
            return dp[i][j] = 0;
        if(i == word1.length() || j == word2.length())
            return dp[i][j] = (i == word1.length()) ? word2.length() - j : word1.length() - i;
            
        if(dp[i][j] != -1)
            return dp[i][j];
        
        if(word1[i] == word2[j])
            return minDistance_memo(word1, i+1, word2, j+1, dp);
        //not equal
        int insert_ = 1 + minDistance_memo(word1, i, word2, j+1, dp);
        int delete_ = 1 + minDistance_memo(word1, i+1, word2, j, dp);
        int replace_ = 1 + minDistance_memo(word1, i+1, word2, j+1, dp);
        
        return dp[i][j] = min({insert_, delete_, replace_}); 
    }
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.length()+1, vector<int>(word2.length()+1, -1));
        return minDistance_memo(word1, 0, word2, 0, dp);
    }

//44 =================================================================================================
int wildMathch_memo(string& s, int i, string& p, int j, vector<vector<int>>& dp){
        if(i == s.length() && j == p.length())
            return dp[i][j] = 1;
        if(i == s.length() || j == p.length()){
            if(j == p.length())
                return dp[i][j] = 0;
            
            //s has ended
            if(j == p.length() - 1 && p[j] == '*')
                return dp[i][j] = 1;
            return dp[i][j] = 0;
        }
        
        if(dp[i][j] != -1)
            return dp[i][j];
            
        if(s[i] == p[j] || p[j] == '?')
            return dp[i][j] = wildMathch_memo(s, i+1, p, j+1, dp);
        
        else if(p[j] == '*'){
            bool res = false;
            
            //matcing * with ""
            res = res || (wildMathch_memo(s, i, p, j+1, dp) == 1);
            //matching * with some char
            res = res || (wildMathch_memo(s, i+1, p, j, dp) == 1);
            
            return dp[i][j] = res ? 1 : 0;
        }
        else
            return dp[i][j] = 0;
    }
    
    bool isMatch(string s, string p) {
        string temp;
        for(int i = 0; i < p.length(); ++i){
            //this is o(1) opearation in c++, in java it is o(n), therefore we use StringBuilder to make it o(1)
            temp += p[i];
            if(p[i] == '*'){
                while(i+1 < p.length() && p[i+1] == '*')
                    i++;
            }
        }
        
        vector<vector<int>> dp(s.length()+1, vector<int>(temp.length()+1, -1));
        return wildMathch_memo(s, 0, temp, 0, dp) == 0 ? false : true;
    }

//https://practice.geeksforgeeks.org/problems/count-palindromic-subsequences/1 ==================================================================
    int mod = 1e9 + 7;
    long long int palSubseq(string& s, int i, int j, vector<vector<long long int>>& dp){
        if(i >= j){
            return dp[i][j] = (i == j) ? 1 : 0; 
        }
        
        if(dp[i][j] != -1)
            return dp[i][j];
        
        long long int excludingI = palSubseq(s, i+1, j, dp);
        long long int excludingJ = palSubseq(s, i, j-1, dp);
        long long int excludingBoth = palSubseq(s, i+1, j-1, dp);
        
        // (a+b)%m = (a%m + b%m)%m
        long long int ans = ((excludingI % mod) + (excludingJ % mod)) % mod;
        
        if(s[i] == s[j]){
            return dp[i][j] = ans + 1;
        }
        else{
            // (a-b)%m = (a%m - b%m + m)%m
            return dp[i][j] = ((ans % mod) - (excludingBoth % mod) + mod) % mod;
        }
    }
    long long int  countPS(string str)
    {
       //Your code here
       int n = str.length();
       vector<vector<long long int>> dp(n, vector<long long int>(n, -1));
       return palSubseq(str, 0, n-1, dp);
    }