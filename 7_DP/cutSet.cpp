#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
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

//matrix chain https://practice.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1 ========================================
int matrixChainMult_memo(vector<int> dimensions, int n, int si, int ei, vector<vector<int>>& dp){
    if(si + 1 == ei)
        return dp[si][ei] = 0;
    
    if(dp[si][ei] != -1)
        return dp[si][ei];

    int minCost = 1e9;

    for(int cut = si+1; cut < ei; ++cut){
        int lans = matrixChainMult_memo(dimensions, n, si, cut, dp);
        int rans = matrixChainMult_memo(dimensions, n, cut, ei, dp);

        int myAns = lans + rans + (dimensions[si] * dimensions[ei] * dimensions[cut]);
        minCost = min(minCost, myAns);
    }
    return dp[si][ei] = minCost;
}

int matrixChainMult_tab(vector<int> dimensions, int n, int SI, int EI, vector<vector<int>>& dp){
    for(int gap = 1; gap < n; ++gap){
        for(int si = 0, ei = gap; ei < n; ++si, ++ei){
            if(si + 1 == ei){
                dp[si][ei] = 0;
                continue;
            }
                
            int minCost = 1e9;

            for(int cut = si+1; cut < ei; ++cut){
                int lans = dp[si][cut];
                int rans = dp[cut][ei];

                int myAns = lans + rans + (dimensions[si] * dimensions[ei] * dimensions[cut]);
                minCost = min(minCost, myAns);
            }
            dp[si][ei] = minCost;
        }
    }
    return dp[SI][EI];
}

void mcm(){
    vector<int> dimensions {40,20,30,10,30};
    int n = dimensions.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    cout << matrixChainMult_tab(dimensions, n, 0, n-1, dp) << endl;
    print2D(dp);
}


//min max of expression https://www.geeksforgeeks.org/minimum-maximum-values-expression/ ================================================
class myPair {
        public:
            int minValue = 1e9;
            int maxValue = -1e9;

            string minExpression = "";
            string maxExpression = "";

            myPair() {
            }

            myPair(int minValue, int maxValue) {
                this -> minValue = minValue;
                this -> maxValue = maxValue;
            }

            myPair(int minValue, int maxValue, string minExpression, string maxExpression) {
                this -> minValue = minValue;
                this -> maxValue = maxValue;
                this -> minExpression = minExpression;
                this -> maxExpression = maxExpression;
            }
    };

    int evaluate(int a, int b, char ch) {
        if (ch == '+')
            return a + b;
        else
            return a * b;
    }

    myPair* minMaxEvalutaion(string str, int si, int ei, vector<vector<myPair*>>& dp) {
        if (si == ei) {
            int val = str[si] - '0';
            return dp[si][ei] = new myPair(val, val, to_string(val) + "", to_string(val) + "");
        }

        if (dp[si][ei] != nullptr)
            return dp[si][ei];

        myPair* res = new myPair();
        for (int cut = si + 1; cut < ei; cut += 2) {
            myPair* lans = minMaxEvalutaion(str, si, cut - 1, dp); // (si,i-1)
            myPair* rans = minMaxEvalutaion(str, cut + 1, ei, dp); // (i+1,ei);, first number = (si, i-1), second number =
                                                                // (i +1, ii - 1), i = ii

            int minValue = evaluate(lans->minValue, rans->minValue, str[cut]);
            int maxValue = evaluate(lans->maxValue, rans->maxValue, str[cut]);

            // res.minValue = Math.min(res.minValue, minValue);
            // res.maxValue = Math.max(res.maxValue, maxValue);

            if (minValue < res->minValue) {
                res->minValue = minValue;
                res->minExpression = "(" + lans->minExpression + " " + str[cut] + " " + rans->minExpression + ")";
            }

            if (maxValue > res->maxValue) {
                res->maxValue = maxValue;
                res->maxExpression = "(" + lans->maxExpression + " " + str[cut] + " " + rans->maxExpression + ")";
            }

        }
        return dp[si][ei] = res;
    }

    void minMaxEvalutaion_() {
        string str = "1+2*3+4*5";
        int n = str.length();
        vector<vector<myPair*>> dp(n, vector<myPair*>(n, nullptr));
    
        myPair* res = minMaxEvalutaion(str, 0, n - 1, dp);
        cout << "Min Value: " + to_string(res->minValue) + "\nMin Expression: " + res->minExpression;
        cout << "\nMax Value: " + to_string(res->maxValue) + "\nMax Expression: " + res->maxExpression;
    }

//5 =========================================================================================
string longestPalindrome(string s) {
        int n = s.length();
        
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int len = 0, si = 0;
        
        for(int gap = 0; gap < n; ++gap){
            for(int i = 0, j = gap; j < n; ++i, ++j){
                
                //single char
                if(gap == 0){
                    dp[i][j] = 1;
                }
                
                //2 chars
                else if(gap == 1){
                    dp[i][j] = (s[i] == s[j]) ? 2 : 0;
                }
                
                else{
                    if(s[i] == s[j] && dp[i+1][j-1] > 0)
                        dp[i][j] = dp[i+1][j-1] + 2;
                }
                
                 if(dp[i][j] > len){
                     len = dp[i][j];
                     si = i;
                 }
            }
        }
        
        return s.substr(si, len);
    }

//132 ===================================================================================================
int minCut_memo(string str, int si, vector<vector<bool>>& isPlaindrome, vector<int>& dp) {
        if (isPlaindrome[si][str.length() - 1])
            return dp[si] = 0;
        if (dp[si] != -1)
            return dp[si];

        int minAns = 1e9;
        for (int cut = si; cut < str.length(); cut++) {
            if (isPlaindrome[si][cut]) {
                minAns = min(minAns, minCut_memo(str, cut + 1, isPlaindrome, dp) + 1);
            }
        }

        return dp[si] = minAns;
    }

    int minCut_tab(string str, int SI, vector<vector<bool>>& isPlaindrome, vector<int>& dp) {
        for (int si = str.length() - 1; si >= 0; si--) {
            if (isPlaindrome[si][str.length() - 1]) {
                dp[si] = 0;
                continue;
            }

            int minAns = 1e9;
            for (int cut = si; cut < str.length(); cut++) {
                if (isPlaindrome[si][cut]) {
                    minAns = min(minAns, dp[cut + 1] + 1);
                }
            }

            dp[si] = minAns;
        }

        return dp[SI];
    }

    int minCut(string str) {
        int n = str.length();
        vector<vector<bool>> isPlaindrome(n, vector<bool>(n, false));
        for (int gap = 0; gap < n; gap++) {
            for (int i = 0, j = gap; j < n; i++, j++) {
                if (gap == 0)
                    isPlaindrome[i][j] = true;
                else if (gap == 1)
                    isPlaindrome[i][j] = str[i] == str[j];
                else
                    isPlaindrome[i][j] = str[i] == str[j] && isPlaindrome[i + 1][j - 1];
            }
        }

        vector<int> dp(n, -1);
        return minCut_memo(str, 0, isPlaindrome, dp);
    }

//312 ================================================================================================
int maxCoins(vector<int>& nums, int si, int ei, vector<vector<int>>& dp) {
        if (dp[si][ei] != -1)
            return dp[si][ei];

        int lval = si - 1 == -1 ? 1 : nums[si - 1];
        int rval = ei + 1 == nums.size() ? 1 : nums[ei + 1];

        int maxAns = 0;
        for (int cut = si; cut <= ei; cut++) {
            int lans = (cut == si) ? 0 : maxCoins(nums, si, cut - 1, dp);
            int rans = (cut == ei) ? 0 : maxCoins(nums, cut + 1, ei, dp);

            maxAns = max(maxAns, lans + lval * nums[cut] * rval + rans);
        }

        return dp[si][ei] = maxAns;

    }

    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
       
        return maxCoins(nums, 0, n - 1, dp);
    }

//1039 ===================================================================================
int minScoreTriangulation(vector<int>& arr, int si, int ei, vector<vector<int>>& dp) {
        if (ei - si <= 1) {
            return dp[si][ei] = 0;
        }

        if (dp[si][ei] != -1)
            return dp[si][ei];

        int minAns = 1e9;
        for (int cut = si + 1; cut < ei; cut++) {
            int lans = minScoreTriangulation(arr, si, cut, dp);
            int rans = minScoreTriangulation(arr, cut, ei, dp);

            minAns = min(minAns, lans + arr[si] * arr[cut] * arr[ei] + rans);
        }

        return dp[si][ei] = minAns;

    }

    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));

        return minScoreTriangulation(values, 0, n - 1, dp);
    }


    

    int main(){
        minMaxEvalutaion_();
        return 0;
    }