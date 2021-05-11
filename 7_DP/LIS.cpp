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

//https://practice.geeksforgeeks.org/problems/maximum-sum-increasing-subsequence4749/1# =======================================================
int maxSumIS(int arr[], int n)  
	{  
	    // Your code goes here
	    vector<int> dp(n,0);
	    int maxAns = 0;
	    
	    for(int i = 0; i < n; ++i){
	        dp[i] = arr[i];
	        int prevAns = 0;
	        for(int j = i-1; j > -1; --j){
	            if(arr[j] < arr[i]){
	                prevAns = max(prevAns, dp[j]);
	            }
	        }
	        dp[i] += prevAns;
	        maxAns = max(maxAns, dp[i]);
	    }
	    return maxAns;
	}


//https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence0824/1 ===============================================
vector<int> lisLR(vector<int>& nums){
	    int n = nums.size();
	    vector<int> dp(n,0);
	    
	    for(int i = 0; i < n; ++i){
	        dp[i] = 1;
	        for(int j = i-1; j > -1; --j){
	            if(nums[j] < nums[i])
	                dp[i] = max(dp[i], dp[j]+1);
	        }
	    }
	    return dp;
	}
	vector<int> lisRL(vector<int>& nums){
	    int n = nums.size();
	    vector<int> dp(n,0);
	    
	    for(int i = n-1; i > -1; --i){
	        dp[i] = 1;
	        for(int j = i+1; j < n; ++j){
	            if(nums[j] < nums[i])
	                dp[i] = max(dp[i], dp[j]+1);
	        }
	    }
	    return dp;
	}
	int LongestBitonicSequence(vector<int>nums)
	{   
	    int n = nums.size();
	    
	    //lis @ i = lis from [0 to i]
	    //=> this is lds from [i to 0]
	    vector<int> lis_LtoR = lisLR(nums);
	   // for(int ele : lis_LtoR)cout<<ele<<" ";
	   // cout<<endl;
	    
	    //lis @ i = lis from [n-1 to i]
	    //=> this is lds from [i to n-1]
	    vector<int> lis_RtoL = lisRL(nums);
	   // for(int ele : lis_RtoL)cout<<ele<<" ";
	   // cout<<endl;
	    
	    int ans = 0;
	    for(int i = 0; i < n; ++i)
	        ans = max(ans, lis_LtoR[i] + lis_RtoL[i] - 1);
	        
	   return ans;
	}

	//673 ==============================================================================================
	void printLIS(vector<vector<int>>& mapping, vector<int>& nums, int len, int idx, string ans){
        if(len == 0){
            cout << ans << endl;
            return;
        }
        for(int nbr : mapping[len]){
            if(nbr < idx && nums[nbr] < nums[idx])
                printLIS(mapping, nums, len-1, nbr, to_string(nums[nbr]) + " " + ans);
        }
    }
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        
        //lis length at ith index
        vector<int> dp(n, 0);
        //count of lis ending at ith index
        vector<int> count(n, 0);
        
        int lis = 0, countOfLis = 0;
        for(int i = 0; i < n; ++i){
            dp[i] = 1;
            count[i] = 1;
            for(int j = i-1; j > -1; --j){
                if(nums[j] < nums[i]){
                    if(dp[i] < dp[j]+1){
                        dp[i] = dp[j]+1;
                        count[i] = count[j];
                    }
                    else if(dp[i] == dp[j]+1){
                        count[i] += count[j];
                    }
                }
            }
            if(lis < dp[i]){
                lis = dp[i];
                countOfLis = count[i];
            }
            else if(lis == dp[i]){
                countOfLis += count[i];
            }
        }
        
        
        //*********PRINTING THOSE LIS*********************
        vector<vector<int>> mapping(lis+1);
        for(int i = 0; i < n; ++i){
            mapping[dp[i]].push_back(i);
        }
        
        //for(int idx : mapping[lis])
            //printLIS(mapping, nums, lis-1, idx, to_string(nums[idx]));
        //******************************************
        
        
        return countOfLis;
    }
