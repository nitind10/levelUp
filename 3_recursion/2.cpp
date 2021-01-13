//permutation combination type questions

//infinite coin permutations
int permute(vector<int>& coins, int target, string ans){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i=0; i<coins.size(); ++i){
        if(target - coins[i] >= 0)
            count += permute(coins, target - coins[i], ans + to_string(coins[i]));
    }
    return count;
}

//infinite coin combinations
int combination(vector<int>& coins, int target, string ans, int idx){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i=idx; i<coins.size(); ++i){
        if(target - coins[i] >= 0)
            count += combination(coins, target - coins[i], ans + to_string(coins[i]), i);
    }
    return count;
}

