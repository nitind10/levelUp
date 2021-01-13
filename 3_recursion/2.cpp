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

