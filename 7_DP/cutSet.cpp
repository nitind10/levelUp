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



    int main(){
        minMaxEvalutaion_();
        return 0;
    }