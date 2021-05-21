#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

void print1D(vector<int>& arr) {
    for (int ele : arr) {
        cout << ele << " ";
    }
    cout << endl;
}

void print2D(vector<vector<int>>& arr) {
    for (vector<int>& ar : arr) {
        print1D(ar);
    }
}

//infinite coin
int coinChangePermutation_memo(vector<int>&arr, int tar, vector<int>& dp) {
    if (tar == 0) {
        return dp[tar] = 1;
    }

    if (dp[tar] != -1)
        return dp[tar];

    int count = 0;
    for (int ele : arr) {
        if (tar - ele >= 0) {
            count += coinChangePermutation_memo(arr, tar - ele, dp);
        }
    }

    return dp[tar] = count;
}

int coinChangePermutation_tab(vector<int>&arr, int Tar, vector<int>& dp) {
    dp[0] = 1;
    for (int tar = 0; tar <= Tar; tar++) {
        for (int ele : arr) {
            if (tar - ele >= 0) {
                dp[tar] += dp[tar - ele];
            }
        }
    }

    return dp[Tar];
}

int coinChangeCombination_memo(vector<int>&arr, int tar, int li, vector<vector<int>>& dp) {
    if (tar == 0) {
        return dp[li][tar] = 1;
    }
    int count = 0;
    for (int i = li; i >= 0; i--)
        if (tar - arr[i] >= 0) {
            count += coinChangeCombination_memo(arr, tar - arr[i], i, dp);
        }

    return dp[li][tar] = count;
}

int coinChangeCombination_2D_tab(vector<int>&arr, int Tar, int LI, vector<vector<int>>& dp) {

    for (int li = 0; li <= LI; li++) {
        for (int tar = 0; tar <= Tar; tar++) {
            if (tar == 0) {
                dp[li][tar] = 1;
                continue;
            }

            for (int i = li; i >= 0; i--)
                if (tar - arr[i] >= 0) {
                    dp[li][tar] += dp[i][tar - arr[i]];
                }
        }
    }

    return dp[LI][Tar];
}

int coinChangeCombination_1D_tab(vector<int>&arr, int Tar, vector<int>& dp) {
    dp[0] = 1;
    for (int ele : arr) {
        for (int tar = ele; tar <= Tar; tar++) {
            if (tar - ele >= 0) {
                dp[tar] += dp[tar - ele];
            }
        }
    }
    return dp[Tar];

}

void coinChange() {
    vector<int> arr = { 2, 3, 5, 7 };
    int tar = 10;

    vector<vector<int>> dp(arr.size(), vector<int>(tar + 1));
    cout << coinChangeCombination_2D_tab(arr, tar, arr.size() - 1, dp) << endl;
    print2D(dp);
}

//518 =========================================================================================
int change(int amount, vector<int>& coins) {
        vector<int> dp(amount+1, 0);
        dp[0] = 1;
        
        for(int i = 0; i < coins.size(); ++i){
            for(int j = coins[i]; j <= amount; ++j){
                dp[j] += dp[j - coins[i]];
            }
        }
        return dp[amount];
    }

//322 ==================================================================================
int coinChangeHelper(vector<int>& coins, int tar, vector<int>& dp){
        if(tar == 0)
            return 0;
        if(dp[tar] != -1)
            return dp[tar];
        
        int myAns = 1e9;
        for(int coin : coins){
            if(tar - coin >= 0)
                myAns = min(myAns, coinChangeHelper(coins, tar-coin, dp));
        }
        return dp[tar] = myAns + 1;
    }
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1,-1);
        int ans = coinChangeHelper(coins, amount, dp);
        return ans == 1e9 + 1 ? -1 : ans;
    }

//377 =============================================================================================
 int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target+1, 0);
        dp[0] = 1;
        
        for(int i = 1; i <= target; ++i){
            for(int j = 0; j < nums.size(); ++j){
                if(i - nums[j] > -1)
                    dp[i] += dp[i - nums[j]];
            }
        }
        return dp[target];
    }

 // https://www.geeksforgeeks.org/find-number-of-solutions-of-a-linear-equation-of-n-variables/ ===========================================
    int numberOfSolution(vector<int>& arr, int Tar) {
        vector<int> dp(Tar + 1, 0);

        for (int tar = 0; tar <= Tar; tar++) {
            for (int ele : arr) {
                if (tar - ele >= 0)
                    dp[tar] += dp[tar - ele];
            }
        }

        return dp[Tar];
    }

    int numberOfSolution_print(vector<int>& arr, int Tar, int aTar, int idx, vector<int>& coff) {
        if (Tar == 0) {
            for (int i = 0; i < arr.size(); i++) {
                cout << arr[i] <<  "(" << coff[i] << ")";
                if (i != arr.size() - 1)
                    cout << " + ";
            }

            cout << " = " <<  aTar << endl;
            return 1;
        }

        int count = 0;
        for (int i = idx; i < arr.size(); i++) {
            if (Tar - arr[i] >= 0) {
                coff[i]++;
                count += numberOfSolution_print(arr, Tar - arr[i], aTar, i, coff);
                coff[i]--;
            }
        }

        return count;
    }

    void numberOfSolution() {
        vector<int> arr = { 2, 3, 5, 7 };
        int tar = 10;
        vector<int> coff(arr.size(), 0);
        cout << numberOfSolution_print(arr, tar, tar, 0, coff) << endl;
    }

//https://www.geeksforgeeks.org/subset-sum-problem-dp-25/ ==============================================
// {2,3,5,7} target = 10, return true or false

int isTargetPossible_memo(vector<int>& arr, int tar, int idx, vector<vector<int>>& dp){
    if(idx == arr.size() || tar == 0){
        return dp[idx][tar] = (tar == 0) ? 1 : 0;
    }

    if(dp[idx][tar] != -1)
        return dp[idx][tar];

    bool res = false;
    if(tar - arr[idx] >= 0)
        res = res || (isTargetPossible_memo(arr, tar-arr[idx], idx+1, dp) == 1);
    res = res || isTargetPossible_memo(arr, tar, idx+1, dp);

    return dp[idx][tar] = res ? 1 : 0;
}

//passing n as idx initially
int isTargetPossible_memo_02(vector<int>& arr, int tar, int n, vector<vector<int>>& dp){
    if(n == 0 || tar == 0){
        return dp[n][tar] = (tar == 0) ? 1 : 0;
    }

    if(dp[n][tar] != -1)
        return dp[n][tar];

    bool res = false;
    if(tar - arr[n-1] >= 0)
        res = res || (isTargetPossible_memo_02(arr, tar-arr[n-1], n-1, dp) == 1);
    res = res || isTargetPossible_memo_02(arr, tar, n-1, dp);

    return dp[n][tar] = res ? 1 : 0;
}


bool isTargetPossible_tab_02(vector<int>& arr, int Tar, int N, vector<vector<bool>>& dp){

    for(int n = 0; n <= N; ++n){
        for(int tar = 0; tar <= Tar; ++tar){
            if(n == 0 || tar == 0){
                dp[n][tar] = (tar == 0) ? true : false;
                continue;
            }
            
            if(tar - arr[n-1] >= 0)
                dp[n][tar] =  dp[n-1][tar-arr[n-1]];

            dp[n][tar] = dp[n][tar] || dp[n-1][tar];
        }
    }
    return dp[N][Tar];
}

//back engineering
void printTheSubarray(int n, int tar, string asf, vector<int>& arr, vector<vector<bool>>& dp2){
    if(tar == 0){
        cout << asf << endl;
        return;
    }
    if(tar - arr[n-1] >= 0 && dp2[n-1][tar-arr[n-1]])
        printTheSubarray(n-1, tar-arr[n-1], to_string(arr[n-1]) + "," + asf, arr, dp2);
    if(dp2[n-1][tar])
        printTheSubarray(n-1, tar, asf, arr, dp2);
}

//counting ways of possibility
int countTargetWays_tab(vector<int>& arr, int Tar, int N, vector<vector<int>>& dp){

    for(int n = 0; n <= N; ++n){
        for(int tar = 0; tar <= Tar; ++tar){
            if(n == 0 || tar == 0){
                dp[n][tar] = (tar == 0) ? 1 : 0;
                continue;
            }
            
            if(tar - arr[n-1] >= 0)
                dp[n][tar] +=  dp[n-1][tar-arr[n-1]];

            dp[n][tar] += dp[n-1][tar];
        }
    }
    return dp[N][Tar];
}


//416 ===========================================================================================================
 bool isTargetPossible_tab_02(vector<int>& arr, int Tar, int N, vector<vector<bool>>& dp){

    for(int n = 0; n <= N; ++n){
        for(int tar = 0; tar <= Tar; ++tar){
            if(n == 0 || tar == 0){
                dp[n][tar] = (tar == 0) ? true : false;
                continue;
            }
            
            if(tar - arr[n-1] >= 0)
                dp[n][tar] =  dp[n-1][tar-arr[n-1]];

            dp[n][tar] = dp[n][tar] || dp[n-1][tar];
        }
    }
    return dp[N][Tar];
}
    
    bool canPartition(vector<int>& nums) {
        int tar = 0;
        for(int ele : nums)
            tar += ele;
        if((tar&1) == 1)
            return false;
        
        tar /= 2;
        int n = nums.size();
        vector<vector<bool>> dp(n+1, vector<bool>(tar+1, false));
        
        return isTargetPossible_tab_02(nums, tar, n, dp);
    }

//494 =====================================================================================
//test cases are week, therefore only recursion will also work
    int fnTarget(vector<int>& nums, int target, int idx){
        if(idx == 0){
            return (target == 0) ? 1 : 0;
        }
        int count = 0;
        count += fnTarget(nums, target - nums[idx-1], idx-1); //taking as positive
        count += fnTarget(nums, target - (-nums[idx-1]), idx-1); //taking as negative 
        return count;
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = 0;
        
        for(int ele : nums)
            sum += ele;
        
        if(target > sum || target < -sum)
            return 0;
        
        return fnTarget(nums, target, n);
    }

//memoized sol
int fnTarget(vector<int>& nums, int starting, int target, int n, vector<vector<int>>& dp){
        if(n == 0){
            dp[n][starting] = (starting == target) ? 1 : 0;
        }
        
        if(dp[n][starting] != -1)
            return dp[n][starting];
        
        int count = 0;
        count += fnTarget(nums, starting+nums[n-1], target, n-1, dp); //taking as positive
        count += fnTarget(nums, starting-nums[n-1], target, n-1, dp); //taking as negative 
        
        return dp[n][starting] = count;
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = 0;
        
        for(int ele : nums)
            sum += ele;
        
        if(target > sum || target < -sum)
            return 0;
        
        
        vector<vector<int>> dp(n+1, vector<int>(2*sum +1, -1));
        return fnTarget(nums, sum, sum+target, n, dp);
    }

//knapsack 0/1 https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1
int knapSack01(int bagWt, int wt[], int val[], int n, vector<vector<int>>& dp){
        if(bagWt == 0 || n == 0)
            return dp[n][bagWt] = 0;
            
        if(dp[n][bagWt] != -1)
            return dp[n][bagWt];
            
        int ans = 0;
        if(bagWt - wt[n-1] >= 0)
            ans = knapSack01(bagWt-wt[n-1], wt, val, n-1, dp) + val[n-1];
        
        ans = max(ans, knapSack01(bagWt, wt, val, n-1, dp));
        return dp[n][bagWt] = ans;
    }
    int knapSack(int bagWt, int wt[], int val[], int n) 
    { 
      vector<vector<int>> dp(n+1, vector<int>(bagWt+1, -1));
      return knapSack01(bagWt, wt, val, n, dp);
    }

//unbounded knapsack (same as inf coin comb) https://practice.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1
 int knapSack_unbounded(int n, int BagWeight, int value[], int weight[]) {
        // combination
        
        vector<int> dp(BagWeight + 1, 0);
        
        for (int i = 0; i < n; i++) {
            for (int bagWeight = weight[i]; bagWeight <= BagWeight; bagWeight++) {
                dp[bagWeight] = max(dp[bagWeight], dp[bagWeight - weight[i]] + value[i]);
            }
        }

        return dp[BagWeight];
    }


//

void targetSum(){
    vector<int> arr {2,3,5,7};
    int n = arr.size();
    int tar = 10;
    //vector<vector<int>> dp(n+1, vector<int>(tar+1, -1));
    // bool res = isTargetPossible_memo_02(arr, tar, n, dp) == 1;
    // cout << boolalpha << res << endl;
    //print2D(dp);
    vector<vector<bool>> dp2(n+1, vector<bool>(tar+1, false));
    cout << boolalpha << isTargetPossible_tab_02(arr, tar, n, dp2) << endl;
    // for (vector<bool>& ar : dp2) {
    //     for(bool ele : ar)cout << ele << " ";
    //     cout<<endl;
    // }
    printTheSubarray(n, tar, "", arr, dp2);

    vector<vector<int>> dp3(n+1, vector<int>(tar+1, 0));
    cout << countTargetWays_tab(arr, tar, n, dp3) << endl; 
}

int main(){
    //coinChange();
    targetSum();
    return 0;
}