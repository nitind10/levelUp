//permutation combination type questions

//infinite coin permutations
int infCoinPermute(vector<int>& coins, int target, string ans){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i=0; i<coins.size(); ++i){
        if(target - coins[i] >= 0)
            count += infCoinPermute(coins, target - coins[i], ans + to_string(coins[i]));
    }
    return count;
}

//infinite coin combinations
int infCoinCombination(vector<int>& coins, int target, string ans, int idx){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i=idx; i<coins.size(); ++i){
        if(target - coins[i] >= 0)
            count += infCoinCombination(coins, target - coins[i], ans + to_string(coins[i]), i);
    }
    return count;
}

//single coin combinations
int singleCoinCombination(vector<int>& coins, int target, string ans, int idx){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i=idx; i<coins.size(); ++i){
        if(target - coins[i] >= 0)
            count += singleCoinCombination(coins, target - coins[i], ans + to_string(coins[i]), i+1);
    }
    return count;
}

//single coin permutations
int singleCoinPermute(vector<int>& coins, int target, string ans){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i=0; i<coins.size(); ++i){
        if(coins[i] > 0 && target - coins[i] >= 0){
            int ele = coins[i];
            coins[i] *= -1;
            count += singleCoinPermute(coins, target - ele, ans + to_string(ele));
            coins[i] *= -1;
        }
    }
    return count;
}

//single coin combinations using subsequence approach
int singleCoinCombinationSubSeq(vector<int>& coins, int target, int idx, string ans){
    if(idx == coins.size() || target == 0){
        if(target == 0){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    if(target - coins[idx] >= 0)
        count += singleCoinCombinationSubSeq(coins, target - coins[idx], idx + 1, ans + to_string(coins[idx]));
    count += singleCoinCombinationSubSeq(coins, target, idx + 1, ans);
    return count;
}

//infinite coin comination subsequence approach
int infCoinCombinationSubSeq(vector<int>& coins, int target, int idx, string ans){
    if(idx == coins.size() || target == 0){
        if(target == 0){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    if(target - coins[idx] >= 0){
        count += infCoinCombinationSubSeq(coins, target - coins[idx], idx, ans + to_string(coins[idx]));
    }
    count += infCoinCombinationSubSeq(coins, target, idx + 1, ans);
    return count;
}

//infinite coin permutation subsequence approach
int infCoinPermutationSubSeq(vector<int>& coins, int target, int idx, string ans){
    if(idx == coins.size() || target == 0){
        if(target == 0){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    if(target - coins[idx] >= 0){
        count += infCoinPermutationSubSeq(coins, target - coins[idx], 0, ans + to_string(coins[idx]));
    }
    count += infCoinPermutationSubSeq(coins, target, idx + 1, ans);
    return count;
}

//single coin permutation subsequence approach
int singleCoinPermutationSubSeq(vector<int>& coins, int target, int idx, string ans){
    if(idx == coins.size() || target == 0){
        if(target == 0){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    if(target - coins[idx] >= 0 && coins[idx] > 0){
        int ele = coins[idx];
        coins[idx] *= -1;
        count += singleCoinPermutationSubSeq(coins, target - ele, 0, ans + to_string(ele));
        coins[idx] *= -1;
    }
    count += singleCoinPermutationSubSeq(coins, target, idx + 1, ans);
    return count;
}

