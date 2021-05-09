#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//300 longest increasing subsequence ========================================================================================
//LtoR = left to right
    int lengthOfLIS_LtoR_memo(vector<int>& nums, int i, vector<int>& dp){
        if(dp[i] != 0)
            return dp[i];
        
        int myLen = 1;
        for(int j = i-1; j > -1; --j){
            if(nums[j] < nums[i]){
                 int prevLen =  lengthOfLIS_LtoR_memo(nums, j, dp);
                 myLen = max(myLen, prevLen+1);
            }
        }
        return dp[i] = myLen;
    }
    
    int lengthOfLIS_LtoR_tab(vector<int>& nums, int n, vector<int>& dp){
        int lis = 0;
        for(int i = 0; i < n; ++i){
            dp[i] = 1;
            for(int j = i-1; j > -1; --j){
                if(nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j]+1);
            }
            lis = max(lis, dp[i]);
        }
        return lis;
    }
    
    int lengthOfLIS_LtoR(vector<int>& nums, int n) {
        vector<int> dp(n,0);
        
        //memo
        int lis = 0;
        for(int i = 0; i < n; ++i){
            lis = max(lis, lengthOfLIS_LtoR_memo(nums, i, dp));
        }
        return lis;
        
        //tab
        return lengthOfLIS_LtoR_tab(nums, n, dp);
    }
    
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        
        //left to right
        return lengthOfLIS_LtoR(nums, n);
    }



//min deletion to make array sorted ==============================================================================
int minDeletions_tab(vector<int>& nums, int n, vector<int>& dp){
    int lis = 0;
    for(int i = 0; i < n; ++i){
        dp[i] = 1;
        for(int j = i-1; j > -1; --j){
            if(nums[j] <= nums[i])
                dp[i] = max(dp[i], dp[j]+1);
        }
        lis = max(lis, dp[i]);
    }
    return n - lis;
}
