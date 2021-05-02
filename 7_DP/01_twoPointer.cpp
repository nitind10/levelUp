//includes two pinter type questions
//i.e problems that are most optimized using two pointer type approach

#include<iostream>
#include<vector>
#include<list>
#include<algorithm>

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

//finonacchi ====================================================================================
//input n is >= 0

//recursive. time : O(2^N), space : O(N)
int fibo_rec(int n){
    if(n <= 1)
        return n;
    
    int ans = fibo_rec(n-1) + fibo_rec(n-2);
    return ans;
}

//memoized. time : O(N), space : O(N)
int fibo_memo(int n, vector<int>& dp){
    if(n <= 1)
        return dp[n] = n;

    if(dp[n] != -1)
        return dp[n];

    int ans = fibo_memo(n-1, dp) + fibo_memo(n-2, dp);

    return dp[n] = ans;
}

//tabulated. time : O(N), space : O(N)
int fibo_tab(int N, vector<int>& dp){
    for(int n = 0; n <= N; ++n){
        if(n <= 1){
            dp[n] = n;
            continue;
        }

        int ans = dp[n-1] + dp[n-2];
        dp[n] = ans;
    }
    return dp[N];
}

//two pointer. time : O(N), space : O(1)
int fibo_03(int N){
    int a = 0, b = 1;
    for(int n = 0; n < N; ++n){
        cout << a << " ";

        int sum = a + b;
        a = b;
        b = sum;
    }
    cout << a << " " << endl;
    return a;
}


//maze path 1 jump ===========================================================================================================

//recursive. time : O(3^(R+C))  number of calls ^ max ht of tree

//memoized. time : O(R*C)
int maze1_memo(int sr, int sc, int dr, int dc, vector<vector<int>>& dp){
    if(sr == dr && sc == dc)
        return dp[sr][sc] = 1;

    if(dp[sr][sc] != 0)
        return dp[sr][sc];
    
    int count = 0;
    if(sc+1 <= dc)
        count += maze1_memo(sr, sc+1, dr, dc, dp);
    if(sr+1 <= dr && sc <= dc)
        count += maze1_memo(sr+1, sc+1, dr, dc, dp);
    if(sr+1 <= dr)
        count += maze1_memo(sr+1, sc, dr, dc, dp);
    
    return dp[sr][sc] = count;
}

//tabulated
int maze1_tab(int sr, int sc, int dr, int dc, vector<vector<int>>& dp){
    for(sr = dr; sr > -1; --sr){
        for(sc = dc; sc > -1; --sc){
            
            if(sr == dr && sc == dc){ 
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            if(sc+1 <= dc)
                count += dp[sr][sc+1]; //maze1_memo(sr, sc+1, dr, dc, dp);
            if(sr+1 <= dr && sc <= dc)
                count += dp[sr+1][sc+1]; //maze1_memo(sr+1, sc+1, dr, dc, dp);
            if(sr+1 <= dr)
                count += dp[sr+1][sc]; //maze1_memo(sr+1, sc, dr, dc, dp);
            
            dp[sr][sc] = count;
        }
    }

    //since we changed sr and sc in loop, therefore cant use them now
    return dp[0][0];
}


//maze path multiple jump ===========================================================================================================

//recursive. time : O( 3(R+C) ^ (R+C) )

//memoized. time : O((R*C)(R+C))
int maze2_memo(int sr, int sc, int dr, int dc, vector<vector<int>>& dp){
    if(sr == dr && sc == dc)
        return dp[sr][sc] = 1;

    if(dp[sr][sc] != 0)
        return dp[sr][sc];
    
    int count = 0;
    for(int i = 1; sc+i <= dc; ++i)
        count += maze2_memo(sr, sc+i, dr, dc, dp);

    for(int i = 1; sr+i <= dr && sc+i <= dc; ++i)
        if(sr+i <= dr && sc+i <= dc)
            count += maze2_memo(sr+i, sc+i,dr, dc, dp);

    for(int i = 1; sr+i <= dr; ++i)
        count += maze2_memo(sr+i, sc, dr, dc, dp);

    return dp[sr][sc] = count;
}

//tabulated. time : O((R*C)(R+C))
int maze2_tab(int sr, int sc, int dr, int dc, vector<vector<int>>& dp){
    for(sr = dr; sr > -1; --sr){
        for(sc = dc; sc > -1; --sc){

            if(sr == dr && sc == dc){
                dp[sr][sc] = 1;
                continue;
            }
                
            int count = 0;
            for(int i = 1; sc+i <= dc; ++i)
                count += dp[sr][sc+i];

            for(int i = 1; sr+i <= dr && sc+i <= dc; ++i)
                count += dp[sr+i][sc+i];

            for(int i = 1; sr+i <= dr; ++i)
                count += dp[sr+i][sc];

            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}


//dice on number line =============================================================================

int diceAndLine_memo(int src, int dest, vector<int>& dice, vector<int>& dp){
    if(src == dest)
        return dp[src] = 1;

    if(dp[src] != 0)
        return dp[src];

    int count = 0;
    for(int i = 0; i < dice.size() && src + dice[i] <= dest; ++i){
        count += diceAndLine_memo(src + dice[i], dest, dice, dp);
    }
    return dp[src] = count;
}

//time: O(6N) (if we consider dice is fixed as 1,2,3,4,5,6) space: o(n)
int diceAndLine_tab(int SRC, int dest, vector<int>& dice, vector<int>& dp){
    for(int src = dest; src >= SRC; --src){
        if(src == dest){
            dp[src] = 1;
            continue;
        }

        int count = 0;
        for(int i = 0; i < dice.size() && src + dice[i] <= dest; ++i){
            count += dp[src+dice[i]];
        }
        dp[src] = count;
    }
    return dp[SRC];
}

//more optimized time: O(N) space: O(7) i.e constant
int diceAndLine_03(int SRC, int dest, vector<int>& dice){
    list<int> l; //by default it is a doubly linkedlist with tail pointer
    for(int src = dest; src >= SRC; --src){
        if(src >= dest - 1)
            l.push_front(1); //o(1)
        else{
            if(l.size() <= 6){ //complexity not stated clearly::  if size variable kept in class => o(1) else o(n)
                l.push_front(l.front() * 2);
            }
            else{
                int ele = l.back();
                l.pop_back(); //o(1)
                l.push_front(l.front() * 2 - ele);
            }
        }
    }
    return l.front();
}


//70 =======================================================================================
int memo(int src, int dest, vector<int>& dp){
        if(src == dest){
            return dp[src] = 1;
        }
        
        if(dp[src] != 0)
            return dp[src];
        
        int ways = 0;
        if(src+1 <= dest)
            ways += memo(src+1, dest, dp);
        if(src+2 <= dest)
            ways += memo(src+2, dest, dp);
        return dp[src] = ways;
    }
    int climbStairs(int n) {
        vector<int> dp(n+1, 0);
        return memo(0, n, dp);
    }

//tabulated
 int climbStairs(int dest) {
        vector<int> dp(dest+1, 0);
    
        for(int src = dest; src > -1; --src){
             if(src == dest){
                 dp[src] = 1;
                 continue;
             }

            int ways = 0;
            if(src+1 <= dest)
                ways += dp[src+1];
            if(src+2 <= dest)
                ways += dp[src+2];
            
            dp[src] = ways;
        }
        return dp[0];
    }

//optimized, can be done simply too, using a and b pointer
int climbStairs(int dest) {
       //ver imp, as (l.front() * 2) can overflow
        list<long> l;
    
        for(int src = dest; src > -1; --src){
             if(src >= dest-1){
                 l.push_front(1);
             }
             else{
                 if(l.size() <= 2)
                     l.push_front(l.front() * 2);
                 else{
                     int ele = l.back();
                     l.pop_back();
                     l.push_front(l.front() * 2 - ele);
                 }
             }
        }
        return l.front();
    }


//746 ==============================================================================================
int fn(vector<int>& cost, int src, int dest, vector<int>& dp){
        if(src == dest)
            return dp[src] = 0;
        
        if(dp[src] != -1)
            return dp[src];
        
        int ans1 = 1e9, ans2 = 1e9;
        
        if(src+1 <= dest)
            ans1 = fn(cost, src+1, dest, dp);
        if(src+2 <= dest)
            ans2 = fn(cost, src+2, dest, dp);
        
        if(src==0)
            return dp[src] = min(ans1, ans2+cost[src]);
        else
            return dp[src] = min(ans1, ans2) + cost[src];
    }
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n+1, -1);
        return fn(cost,0, n, dp);
    }

//tabulated
int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n+1, -1);
        
        int dest = n;
        for(int src = n; src > -1; --src){
            if(src == dest){
                dp[src] = 0;
                continue;
            }
                
            int ans1 = 1e9, ans2 = 1e9;

            if(src+1 <= dest)
                ans1 = dp[src+1];
            if(src+2 <= dest)
                ans2 = dp[src+2];

            if(src == 0)
                dp[src] = min(ans1, ans2+cost[src]);
            else
                dp[src] = min(ans1, ans2) + cost[src];
        }
        return dp[0];
    }

//can be optimized too


//friends pairing https://practice.geeksforgeeks.org/problems/friends-pairing-problem5425/1# ==================================
 int mod = 1e9 + 7;
    long countFriendsPairings_memo(int n, vector<long>&dp){
        if(n <= 1){
            return dp[n] = 1;
        }
        
        if(dp[n] != 0)
            return dp[n];
        
        long single = countFriendsPairings_memo(n-1, dp);
        long pairup = countFriendsPairings_memo(n-2, dp) * (n-1);
        
        return dp[n] = ((single % mod + pairup % mod) % mod);
    }

    long countFriendsPairings_tab(int N, vector<long>&dp){
        for(int n = 0; n <= N; ++n){
            if(n <= 1){
                dp[n] = 1;
                continue;
            }
        
            long single = dp[n-1];
            long pairup = dp[n-2] * (n-1);
            
            dp[n] = ((single % mod + pairup % mod) % mod);
        }
        return dp[N];
    }
    long countFriendsPairings(int n) 
    { 
        // code here
        vector<long> dp(n+1, 0);
        return countFriendsPairings_tab(n, dp);
    }

//can be optimized too

//printing all the answers (no dp possible)
long printFriendsPairing(string friends, string ans) {
    if (friends.length() == 0) {
        cout << ans << endl;
        return 1;
    }

    char ch = friends[0];
    long count = 0;
    count += printFriendsPairing(friends.substr(1), ans + ch + " ");
    for (int i = 1; i < friends.length(); i++) {
        string rstr = friends.substr(1, i-1) + friends.substr(i + 1);
        count += printFriendsPairing(rstr, ans + ch + friends[i] + " ");
    }
    return count;
}

//goldmine https://practice.geeksforgeeks.org/problems/gold-mine-problem2608/1 =====================================================
 int goldMine_memo(int n, int m, vector<vector<int>>& M, int ri, int ci, vector<vector<int>>& dp){
        if(ci == m-1)
            return dp[ri][ci] = M[ri][ci];
            
        if(dp[ri][ci] != -1)
            return dp[ri][ci];
            
        int ans = 0;
        //this loop works for these directions
        for(int i = 0; i <= 2; ++i)
            if(ri+i-1 > -1 && ri+i-1 < n)
                ans = max(ans, goldMine_memo(n, m, M, ri+i-1, ci+1, dp));
        
        return dp[ri][ci] = ans + M[ri][ci];
    }
    int goldMine_tab(int n, int m, vector<vector<int>>& M, vector<vector<int>>& dp){
        
        for(int ci = m-1; ci > -1; --ci){
            for(int ri = n-1; ri > -1; --ri){
                
                if(ci == m-1){
                    dp[ri][ci] = M[ri][ci];
                    continue;
                }
                
                int ans = 0;
                for(int i = 0; i <= 2; ++i)
                    if(ri+i-1 > -1 && ri+i-1 < n)
                        ans = max(ans, dp[ri+i-1][ci+1]);
                
                dp[ri][ci] = ans + M[ri][ci];
            }
        }
        
        int gold = 0;
        for(int i = 0; i < n; ++i)
            gold = max(gold, dp[i][0]);
        
        return gold;
    }
    int maxGold(int n, int m, vector<vector<int>> M)
    {
        // code here
        //int gold = 0;
        vector<vector<int>> dp(n, vector<int>(m, -1));
        
        // for(int i = 0; i < n; ++i){
        //     gold = max(gold, goldMine_memo(n , m, M, i, 0, dp));
        // }
        // return gold;
        
        return goldMine_tab(n, m, M, dp);
    }


//91 ==============================================================================================================
 int numDecodings_memo(string s, int idx, vector<int>& dp){
        if(idx == s.length())
            return dp[idx] = 1;
        
        if(s[idx] == '0')
            return dp[idx] = 0;
        
        if(dp[idx] != -1)
            return dp[idx];
        
        int count = 0;
        count += numDecodings_memo(s, idx+1, dp);
        
        if(idx < s.length() - 1){
            int num = (s[idx] - '0') * 10 + (s[idx+1] - '0');
            if(num <= 26)
                count += numDecodings_memo(s, idx+2, dp);
        }
        return dp[idx] = count;
    }
    
    int numDecodings_tab(string s, int IDX, vector<int>& dp){
        
        for(int idx = s.length(); idx > -1; --idx){
            
             if(idx == s.length()){
                 dp[idx] = 1;
                 continue;
             }
             if(s[idx] == '0'){
                 dp[idx] = 0;
                 continue;
             }
               
            int count = 0;
            count += dp[idx+1];

            if(idx < s.length() - 1){
                int num = (s[idx] - '0') * 10 + (s[idx+1] - '0');
                if(num <= 26)
                    count += dp[idx+2];
            }
            dp[idx] = count;
        }
        
        return dp[IDX];
    }
    
    int numDecodings_optimized(string s, int idx){
        int a = 0, b = 1;
        int sum = a + b;
        
        while(idx > -1){
            if(s[idx] == '0'){
                sum = 0;
            }
            else{
                sum = b;
                if(idx < s.length()-1){
                    int num = (s[idx]-'0')*10 + (s[idx+1]-'0');
                    if(num <= 26)
                        sum += a;
                }
            }
            a = b;
            b = sum;
            idx--;
        }
        return b;
    }
    
    int numDecodings(string s) {
        int n = s.length();
        //vector<int> dp(n+1, -1);
             
        return numDecodings_optimized(s, n-1);
    }


//639 ====================================================================================================================
int mod = 1e9 + 7;
    //passed string by refference because in a very big test case it was giving tle otherwise
    long numDecodings_memo(string& s, int n, int idx, vector<long>& dp){
        if(idx == n)
            return dp[idx] = 1;
        if(s[idx] == '0')
            return dp[idx] = 0;
        
        if(dp[idx] != -1)
            return dp[idx];
        
        long count = 0;
        
        //s[idx] is number
        if(s[idx] != '*'){
            //taking only 1 digit
            count = (count%mod + numDecodings_memo(s, n, idx+1, dp)%mod) % mod;
            
            //taking 2 digits if possible
            if(idx < n-1){
                //2nd digit is number
                if(s[idx+1] != '*'){
                    int num = (s[idx]-'0')*10 + (s[idx+1]-'0');
                    if(num <= 26)
                        count = (count%mod + numDecodings_memo(s, n, idx+2, dp)%mod) % mod;
                }
                //2nd digit is star
                else{
                    if(s[idx] == '1')
                         count = (count%mod + 9*numDecodings_memo(s, n, idx+2, dp)%mod) % mod;
                    else if(s[idx] == '2')
                         count = (count%mod + 6*numDecodings_memo(s, n, idx+2, dp)%mod) % mod;
                }
            }
        }
        
        //s[idx] is *
        else{
             count = (count%mod + 9*numDecodings_memo(s, n, idx+1, dp)%mod) % mod;
            
            //taking 2 digits if possible
            if(idx < n-1){
                //2nd digit is number
                if(s[idx+1] != '*'){
                    if(s[idx+1] >= '0' && s[idx+1] <= '6')
                        count = (count%mod + 2*numDecodings_memo(s, n, idx+2, dp)%mod) % mod;
                    else
                        count = (count%mod + numDecodings_memo(s, n, idx+2, dp)%mod) % mod;
                }
                //2nd digit is *
                else{
                    count = (count%mod + 15*numDecodings_memo(s, n, idx+2, dp)%mod) % mod;
                }
            }
        }
        
        return dp[idx] = count;
    }
    
    long numDecodings_tab(string s, int n, int IDX, vector<long>& dp){
        for(int idx = n; idx > -1; --idx){
             if(idx == n){
                 dp[idx] = 1;
                 continue;
             }   
             if(s[idx] == '0'){
                 dp[idx] = 0;
                 continue;
             }
        
            long count = 0;

            //s[idx] is number
            if(s[idx] != '*'){
                //taking only 1 digit
                count = (count%mod + dp[idx+1]%mod) % mod;

                //taking 2 digits if possible
                if(idx < n-1){
                    //2nd digit is number
                    if(s[idx+1] != '*'){
                        int num = (s[idx]-'0')*10 + (s[idx+1]-'0');
                        if(num <= 26)
                            count = (count%mod + dp[idx+2]%mod) % mod;
                    }
                    //2nd digit is star
                    else{
                        if(s[idx] == '1')
                             count = (count%mod + 9*dp[idx+2]%mod) % mod;
                        else if(s[idx] == '2')
                             count = (count%mod + 6*dp[idx+2]%mod) % mod;
                    }
                }
            }

            //s[idx] is *
            else{
                 count = (count%mod + 9*dp[idx+1]%mod) % mod;

                //taking 2 digits if possible
                if(idx < n-1){
                    //2nd digit is number
                    if(s[idx+1] != '*'){
                        if(s[idx+1] >= '0' && s[idx+1] <= '6')
                            count = (count%mod + 2*dp[idx+2]%mod) % mod;
                        else
                            count = (count%mod + dp[idx+2]%mod) % mod;
                    }
                    //2nd digit is *
                    else{
                        count = (count%mod + 15*dp[idx+2]%mod) % mod;
                    }
                }
            }

            dp[idx] = count;
        }
        return dp[IDX];
    }
    
     long numDecodings_optimized(string s, int n, int idx){
        long a = 0, b = 1;
        long sum = a + b;
        
        while(idx > -1){
            if(s[idx] == '0'){
                sum = 0;
            }
            else{
               if(s[idx] != '*'){
                   //one digit
                   sum = b;
                   
                    //taking 2 digits if possible
                    if(idx < n-1){
                        //2nd digit is number
                        if(s[idx+1] != '*'){
                            int num = (s[idx]-'0')*10 + (s[idx+1]-'0');
                            if(num <= 26)
                                sum = (sum%mod + a%mod) % mod;
                        }
                        //2nd digit is star
                        else{
                            if(s[idx] == '1')
                                 sum = (sum%mod + 9*a%mod) % mod;
                            else if(s[idx] == '2')
                                 sum = (sum%mod + 6*a%mod) % mod;
                        }
                    }
                }

                //s[idx] is *
                else{
                    //one digit
                    sum = 9*b%mod;
                    
                    //taking 2 digits if possible
                    if(idx < n-1){
                        //2nd digit is number
                        if(s[idx+1] != '*'){
                            if(s[idx+1] >= '0' && s[idx+1] <= '6')
                                sum = (sum%mod + 2*a%mod) % mod;
                            else
                                sum = (sum%mod + a%mod) % mod;
                        }
                        //2nd digit is *
                        else{
                            sum = (sum%mod + 15*a%mod) % mod;
                        }
                    }
                }
            }

            a = b;
            b = sum;
            idx--;
        }
        return b;
    }
    
    int numDecodings(string s) {
        int n = s.length();
        vector<long> dp(n+1, -1);
        return int(numDecodings_optimized(s, n, n-1));
    }




int main(){
    cout << printFriendsPairing("ABCDE", "") << endl;
    return 0;
}