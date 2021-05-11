#include<iostream>
#include<vector>

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


int main(){
    coinChange();
    return 0;
}