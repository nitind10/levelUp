//positive negative
void positiveNegative(int a[], int n){
    int s = 0, e = n-1;
    while(s < e){
        if(a[s] > -1){
            s++;
        }
        if(a[e] < 0){
            e--;
        }
        if(a[s] < 0 && a[e] > -1){
            swap(a[s], a[e]);
            s++;
            e--;
        }
    }
}

//283
void moveZeroes(vector<int>& nums) {
    int n = nums.size();
    if(n == 0){
        return;
    }
    int numPtr = 0;
    for(int i=0; i<n; ++i){
        if(nums[i] != 0){
            swap(nums[i], nums[numPtr]);
            numPtr++;
        }
    }
}

//75
void sortColors(vector<int>& a) {
    int n = a.size();
    if(n == 0){
        return;
    }
    int low = -1, mid = 0, high = n;
    while(mid < high){
        if(a[mid] == 1){
            mid++;
        }
        else if(a[mid] == 0){
            low++;
            swap(a[low], a[mid]);
            mid++;
        }
        else if(a[mid] == 2){
            high--;
            swap(a[high], a[mid]);
        }
    }
}

//189
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k%n;
    reverse(nums,0,n-k-1);
    reverse(nums,n-k,n-1);
    reverse(nums,0,n-1);
}
void reverse(vector<int>& nums, int low, int high){
    while(low < high){
        swap(nums[low], nums[high]);
        low++;
        high--;
    }
}

//https://practice.geeksforgeeks.org/problems/max-sum-in-the-configuration/1
int max_sum(int arr[],int n)
{
    int sum = 0,rotatedSum = 0, n = arr.length;
        
        for(int ele : arr) sum += ele;
        for(int i = 0;i<arr.length;i++)  rotatedSum += arr[i] * i;

        int maxSum = rotatedSum;

        for(int i = 0;i<arr.length - 1;i++){
            rotatedSum  = rotatedSum - sum + arr[i] * n;
            maxSum = Math.max(maxSum, rotatedSum - sum + arr[i] * n);
        }

        return maxSum;
}

//3
int lengthOfLongestSubstring(string s) {
    int n = s.length();
    if(n == 0){
        return 0;
    }
    
    //128 will take care of all chars
    vector<int> map(128,0);
    int si=0, ei=0, count=0, len=0, maxsi=0, maxei=0;
    
    while(ei < n){
        /*here ++ is post incremnet so first map[s[ei]] > 0 will be checked after that expresion will modify values in right -> left direction that is,             first map[s[ei]]++ will happen then ei++ will happen if condition is true, count will decrement but the above post increment operations wil                 occur irrespective of condition being T or F 
        equivalent to:
        if(map[s[ei]] > 0){
            count++;
        }
        map[s[ei]]++;
        ei++;
        */
        if(map[s[ei++]]++ > 0){
            count++;
        }
        
        while(count > 0){
            //same post increment and decrement logic here
            if(map[s[si++]]-- > 1){
                count--;
            }
        }
        
        if(ei - si > len){
            len = ei - si;
            //maxsi and maxei can be used in end to display the longest non repeating substring using s.substr(maxsi,maxei-maxsi);
            maxsi = si;
            maxei = ei;
        }
    }
    //cout<<s.substr(maxsi,maxei-maxsi);
    return len;
}

//76
string minWindow(string s, string t) {
    int ns = s.length();
    int nt = t.length();
    
    vector<int> v(128,0);
    //ei creates a window containing all chars of t, si then tries to reduce it by removing unnessesary chars
    int si=0, ei=0, requirement = nt, len = 1e8, head = 0;
    
    for(int i=0; i<nt; ++i){
        v[t[i]]++;
    }

    while(ei < ns){
        
        if(v[s[ei++]]-- > 0){
            requirement--;
        }
        
        while(requirement == 0){
            if(ei-si < len){
                //moving right to left first head is assigned as si, then len = ei - head or si is done 
                len = ei- (head=si);
            }
            if(v[s[si++]]++ == 0){
                requirement++;
            }
        }
    }
    
    return len == 1e8 ? "" : s.substr(head, len);
}

//https://practice.geeksforgeeks.org/problems/smallest-distant-window/0
void SmallestdistinctWindow(){
    string str;
    cin>>str;
    int n = str.length();
    vector<int> v(128,0);
    int requirement = 0, len = INT_MAX, head = 0;
    for(int i=0; i<n; ++i){
        if(v[str[i]] == 0){
            v[str[i]]++;
            requirement++;
        }
    }
    int s=0, e=0;
    while(e<n){
        
        if(v[str[e++]]-- > 0){
            requirement--;
        }
        
        while(requirement == 0){
            if(e-s < len){
                len = e-s;
                head=s;
            }
            
            if(v[str[s++]]++ == 0){
                requirement++;
            }
        }
    }

    cout << len <<endl;
}

//159 locked
string _2distinct(string s){
    int n = s.length();
    if(n ==0){
        return "";
    }
    if(n <= 2){
        return s;
    }

    int si = 0, ei = 0, dc = 0, len = 0, head = 0;
    vector<int> freq(128,0);
    while(ei < n){
        if(freq[s[ei++]]++ == 0)
            dc++;

        while(dc > 2)
            if(freq[s[si++]]-- == 1)
                dc--;
            
        len = (ei - si) > len ? ei - (head = si) : len;
    }

    return s.substr(head, len);
}

//340 locked
string _2distinct(string s, int k){
    int n = s.length();
    if(n ==0){
        return "";
    }

    int si = 0, ei = 0, dc = 0, len = 0, head = 0;
    vector<int> freq(128,0);
    while(ei < n){
        if(freq[s[ei++]]++ == 0)
            dc++;

        while(dc > k)
            if(freq[s[si++]]-- == 1)
                dc--;
            
        len = (ei - si) > len ? ei - (head = si) : len;
    }

    return s.substr(head, len);
}

//1456
bool isvowel(char c){
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}
int maxVowels(string s, int k) {
    int n = s.length();
    int si=0, ei=0,vcount=0, maxvcount=0;
    while(ei<n){
        if(isvowel(s[ei++])){
            vcount++;
        }
        if(ei-si == k){
            maxvcount = max(maxvcount, vcount);
            if(isvowel(s[si++])){
                vcount--;
            }
        }
    }
    return maxvcount;
}

//239
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    //nlogn worst case (increasing order, none of the element gets popped)
    //nlogk best case (dec order of input)
    int n = nums.size();
    if(n == 1 || k == 1){
        return nums;
    }
    
    //{nums[i], i}
    priority_queue <pair<int,int> > pq;
    
    vector<int> ans;
    
    for(int i=0; i<n; ++i){
        
        //removing elements that dont belong in current window and are on top
        while(pq.size() != 0 && pq.top().second <= i-k){
            pq.pop();
        }
        //adding possible maximum candidate of current window
        pq.push({nums[i],i});
        
        //window over, add max of curr window
        if(i >= k-1){
            ans.push_back(pq.top().first);
        }
    }
    
    return ans;
}

//https://practice.geeksforgeeks.org/problems/largest-subarray-of-0s-and-1s/1
int maxLen(int nums[], int n)
{
// Your code here
    if(n <= 1){
        return 0;
    }
    int len = 0, sum=0;
    map<int,int> m; //sum,idx
    m[0] = -1;
    
    for(int i=0; i<n; ++i){
        int curVal = nums[i];
        //considering 0s as -1 for ease
        if(curVal == 0){
            curVal = -1;
        }
        sum += curVal;
        
        if(m.find(sum) != m.end()){
            len = max(len, i-m[sum]);
        }
        else{
            m[sum] = i;
        }
        
    }
    return len;
}

//https://practice.geeksforgeeks.org/problems/count-subarrays-with-equal-number-of-1s-and-0s-1587115620/1
long long int countSubarrWithEqualZeroAndOne(int nums[], int n)
{
//Your code here
    if(n <= 1){
        return 0;
    }
    int sum=0;
    int count=0;
    map<int,int> m; //sum,freq_of_sum
    m[0] = 1;
    
    for(int i=0; i<n; ++i){
        int curVal = nums[i];
        //considering 0s as -1 for ease
        if(curVal == 0){
            curVal = -1;
        }
        sum += curVal;
        m[sum]++;
    }
    for(pair<int,int> p : m){
        count += (p.second * (p.second-1))/2;
    }
    return count;
}

//https://practice.geeksforgeeks.org/problems/longest-subarray-with-sum-divisible-by-k1259/1
int longSubarrWthSumDivByK(int arr[], int n, int k)
{
    // Complete the function
    if(n == 0){
        return 0;
    }
    map<int,int> m; //sum,idx
    m[0] = -1;
    int sum=0, mod=0, len=0;
    for(int i=0; i<n; ++i){
        sum += arr[i];
        mod = (sum%k + k)%k;
        if(m.find(mod) != m.end() ){
            len = max(len, i-m[mod]);
        }
        else{
            m[mod] = i;
        }
    }
    return len;
}

//974
int subarraysDivByK(vector<int>& arr, int k) {
    int n = arr.size();
    if(n==0){
        return 0;
    }
    
    long long sum = 0, mod;
    long long count = 0;
    map<int,int> m; //mod,freq
    m[0]=1;
    
    for(int i=0; i<n; ++i){
        sum += arr[i];
        mod = (sum % k + k) % k; //to get correct mod when sum is negative
        m[mod]++;
    }
    for(pair<int,int> p : m){
        count += (p.second * (p.second-1))/2;
    }
    return count;
}

//781
int numRabbits(vector<int>& answers) {
    int n = answers.size();
    if(n == 0){
        return 0;
    }
    // map<int,int> m; //rabbit in hand, same other possible rabbits
    vector<int> m(1000,0);
    int count = 0;
    for(int i=0; i<n; ++i){
        if(m[answers[i]] == 0){
            count += answers[i]+1;
            m[answers[i]] = answers[i];
        }
        else{
            m[answers[i]]--;
        }
    }
    
    return count;
}

//930
int noOfSubarraysWithAtmostKSum(vector<int>& A, int S){
    int n = A.size();
    int si=0, ei=0, count=0, presum=0;
    while(ei < n){
        presum += A[ei++];
        while(presum > S){
            presum -= A[si++];
        }
        count += ei-si;
    }
    return count;
}
int numSubarraysWithSum(vector<int>& A, int S) {
    int n = A.size();
    if(n == 0){
        return 0;
    }
    return noOfSubarraysWithAtmostKSum(A, S) - ( (S > 0) ? noOfSubarraysWithAtmostKSum(A, S-1) : 0 ) ;
}

//1248
int numberOfSubarrayWithAtmostKOddNumbers(vector<int>& nums, int k){
    int n = nums.size();
    int si=0, ei=0, count = 0, presum=0;
    while(ei < n){
        
        if(nums[ei++] & 1){
            presum++;
        }
        
        while(presum > k){
            if(nums[si++] & 1){
                presum--;
            }
        }
        count += ei-si;
    }
    return count;
}
int numberOfSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    return numberOfSubarrayWithAtmostKOddNumbers(nums, k) - numberOfSubarrayWithAtmostKOddNumbers(nums, k-1); 

}

//1004
int longestOnes(vector<int>& A, int K) {
    int n = A.size();
    //ques can be interpreted as longest subarray with atmost k zeroes
    int si=0, ei=0, len=0, zeroCount = 0;
    while(ei < n){
        if(A[ei++] == 0) zeroCount++;
        
        while(zeroCount > K){
            if(A[si++] == 0) zeroCount--;
        }
        len = max(len, ei-si);
    }
    return len;
}

//904
int totalFruit(vector<int>& tree) {
    int n = tree.size();
    int si=0, ei=0, len=0, dc=0;
    // map<int, int> m; //val, freq
    vector<int> m(400001,0);
    while(ei < n){
        if(m[tree[ei++]]++ == 0) dc++;
        
        while(dc > 2){
            if(m[tree[si++]]-- == 1) dc--;
        }
        len = max(len,ei-si);
    }
    return len;
}

//209
int minSubArrayLen(int s, vector<int>& nums) {
    int n = nums.size();
    int si = 0, ei = 0, len = 1e8, sum = 0;
    while(ei < n){
        sum += nums[ei++];
        
        while(sum >= s){
            len = min(len, ei - si);
            sum -= nums[si++];
        }
    }
    return (len == 1e8) ? 0 : len;
}

//53
int maxSubArray(vector<int>& nums) {
    //this is generic, i.e works for whole -ve array also
    int n = nums.size();
    int gmax = nums[0], runningSum = gmax;
    for(int i=1; i<n; ++i){
        //new start at nums[i] is benefical or continue old runningSum + nums[i]
        runningSum = max(nums[i], runningSum + nums[i]);
        //update gmax
        gmax = max(gmax, runningSum);
    }
    return gmax;
}

//1191
int kConcatenationMaxSum(vector<int>& arr, int k) {
    /*if k==1 simple kadane
    if sum of array < 0 then kadane of 2 copies of array
    if sum > 0 then ans = kadane of two copies + (k-2)*sum */
    
    int n = arr.size();
    int mod = (1e9 +7);

    if(k == 1){
        //generic kadane i.e works for all -ve nums too
        int gSum = arr[0], runningSum = arr[0];
        for(int i=1; i<n; ++i){
            runningSum = max(arr[i], runningSum + arr[i]);
            runningSum %= mod;
            gSum = max(gSum, runningSum);
            gSum %= mod;
        }
        return gSum;
    }
    
    long long sum = 0;
    for(int i=0; i<n; ++i) {
        sum += arr[i];
        sum %= mod;
    }
    
    //kadane of 2 copies of arr
    int count = 1;
    int gSum2 = arr[0], runningSum2 = arr[0];
        for(int i=1; i<n; ++i){
            runningSum2 = max(arr[i], runningSum2 + arr[i]);
            runningSum2 %= mod;
            gSum2 = max(gSum2, runningSum2);
            gSum2 %= mod;
            
            //for 2nd traversal
            if(count == 1 && i == n-1){
                count--;
                i = -1;
            }
        }
    
    if(sum < 0) return ((gSum2 > 0) ? gSum2 : 0);
    if(sum >= 0){
        long long bwSum = ( (k-2) * sum ) % mod;
        long long ans = ( gSum2 + bwSum ) % mod;
        return ans;
    }
    return 0;
}

//1074
int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    int r = matrix.size();
    int c = matrix[0].size();
    
    //creating prefix matrix, that is every cell is sum of itself + all column elements above it
    for(int i=1; i<r; ++i){
        for(int j=0; j<c; ++j){
            matrix[i][j] += matrix[i-1][j];
        }
    }
    int count = 0;
    for(int base=0; base<r; ++base){
        
        for(int row=base; row<r; ++row){
            
            map<int,int> m; //sum,freq
            m[0] = 1;
            int sum = 0;
            for(int j=0; j<c; ++j){
                
                sum += matrix[row][j] - ((base > 0) ? matrix[base-1][j] : 0);
                if(m.find(sum-target) != m.end()){
                    count += m[sum-target];
                }  
                m[sum]++;
            }
        }
    }
    return count;
}

//363
int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int n = matrix.size(), m = matrix[0].size();
    for(int i = 1;i<n;i++){
        for(int j = 0;j<m;j++)
            matrix[i][j] += matrix[i-1][j];
    }

    int maxSum = -1e9;
    for(int base = 0; base < n;base++){ 

        for(int row = base;row < n;row++){
            
            
            int gSum = -1e9, rsum = 0;
            for(int j = 0; j < m; j++){
                int val  = matrix[row][j] - (base != 0 ? matrix[base - 1][j] : 0);
                
                rsum = max(val,rsum + val);
                gSum = max(gSum, rsum);

                if(gSum == k) return k;
            }
            
            if(gSum < k){
                maxSum = max(maxSum, gSum);
                continue;
            }
            
            
            set<int> map;
            int sum = 0;
            map.insert(0);

            for(int j = 0; j <m ; j++){
                sum += matrix[row][j] - (base != 0 ? matrix[base - 1][j] : 0);
                
                if(map.find(sum - k) != map.end()) return k;
                
                auto it = map.upper_bound(sum - k);
                if(it != map.end()){
                    maxSum = max(maxSum,sum - (*it));
                }
                map.insert(sum);
            }
        } 
    }
    return maxSum;
}

//152
int maxProduct(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;
    
    int ans = nums[0];
    int left = 0, right = 0;
    
    for(int i=0; i<n; ++i){
        left = (left == 0 ? 1 : left) * nums[i];
        right = (right ==0 ? 1 : right) * nums[n-i-1];
        ans = max(ans, max(left, right));
    }
    return ans;
}