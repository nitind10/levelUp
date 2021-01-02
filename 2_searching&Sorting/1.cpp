//34
vector<int> searchRange(vector<int>& nums, int target) {
    int n = nums.size();
    vector<int> ans(2,-1);

    if(n == 0) return ans;
    
    int low = 0, high = n-1, mid;
    
    while(low <= high){
        mid = (low + (high - low)/2);
    
        if(nums[mid] == target){
            if((mid-1 > -1) && nums[mid-1] == target) {
                high = mid - 1;
            }
            else{
                ans[0] = mid;
                break;
            }
        }

        else if(nums[mid] < target){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    
    int low2 = 0, high2 = n-1, mid2;
    
        while(low2 <= high2){
        mid2 = (low2 + (high2 - low2)/2);
        if(nums[mid2] == target){
            if((mid2+1 < n) && nums[mid2+1] == target) {
                low2 = mid2 + 1;
            }
            else{
                ans[1] = mid2;
                break;
            }
        }
        else if(nums[mid2] < target){
            low2 = mid2 + 1;
        }
        else{
            high2 = mid2 - 1;
        }
    }
    
    return ans;
}

//35
int searchInsert(vector<int>& nums, int target) {
    int n = nums.size();
    int si = 0, ei = n;
    while(si < ei){
        int mid = si + (ei - si)/2;
        if(nums[mid] < target) si = mid + 1;
        else ei = mid;
    }
    //noe si and ei are at same position
    return si;
}

//74
int searchInsert(vector<int>& nums, int target) {
    int n = nums.size();
    int si = 0, ei = n;
    while(si < ei){
        int mid = si + (ei - si)/2;
        if(nums[mid] < target) si = mid + 1;
        else ei = mid;
    }
    //noe si and ei are at same position
    return si;
}

//https://practice.geeksforgeeks.org/problems/floor-in-a-sorted-array-1587115620/1
int findFloor(vector<long long> v, long long n, long long x){
    
    // Your code here
    long long si = 0, ei = n-1;
    while(si <= ei){
        long long mid = si + (ei - si)/2;
        
        if(v[mid] == x) 
            cout << mid;
        else if(v[mid] < x) 
            si = mid + 1;
        else 
            ei = mid - 1;
    }
    
    //now si is 1 position ahead of ei, and if they exist, ei = floor indez and si = ciel index
    if(ei >= 0) 
        return ei;
    return -1;
}

//https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1
long long myInversion(long long arr[], long long si, long long mid, long long ei, vector<long long>& v){
    long long i = si, j = mid + 1, count = 0, k = si;
    
    //calculating inv count of parent, using already sorted left and right children,
    // aslo merging them in auxilary vector
    while(i <= mid && j <=ei){
        if(arr[i] > arr[j]){
           count += (mid - i + 1);
           v[k++] = arr[j++];
        }
        else{
            v[k++] = arr[i++];
        }
    }
    
    
    while(i <= mid) v[k++] = arr[i++];
    while(j <= ei) v[k++] = arr[j++];
    
    //rewrite the arr with sorted content
    while(si <= ei) arr[si] = v[si++];
    
    return count;
}
long long invCountRec(long long arr[], long long si, long long ei, vector<long long>& v){
    
    if(si >= ei)
        return 0;
    
    long long mid = si + (ei - si)/2;
    long long count = 0;
    
    count += invCountRec(arr, si, mid,v);
    count += invCountRec(arr, mid+1, ei,v);
    
    //now left and right child have given their inersion and also have sorted themselves
    //now calculation parents inversion
    count += myInversion(arr, si, mid, ei,v);
    
    return count;
}
long long int inversionCount(long long arr[], long long N)
{
    vector<long long> v(N);
    return invCountRec(arr, 0, N-1, v);
}

//775
bool isIdealPermutation(vector<int>& A) {
    int _max = -1, n = A.size();
    for(int i=0; i<n-2; ++i){
        _max = max(_max, A[i]);
        if(_max > A[i+2])
            return false;
    }
    return true;
}

//658
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int n = arr.size();
    if(n == 1) return arr;
    
    if(x <= arr[0]){
        vector<int> ans(arr.begin(), arr.begin() + k);
        return ans;
    }
    if(x >= arr[n-1]){
        vector<int> ans(arr.end() - k, arr.end() );
        return ans;
    }
    
    //find perfect position of x in arr, in both cases(i.e presence and absense)
    int si = 0, ei = n;
    while(si < ei){
        int mid = si + (ei - si)/2;
        if(arr[mid] < x) si = mid + 1;
        else ei = mid;
    }
    
    int idxOfX = si;
    //creating window of sufficient range
    si = max(idxOfX - k, 0);
    ei = min(idxOfX + k, n-1);
    while((ei - si + 1) > k){
        if(x - arr[si] > arr[ei] - x) si++;
        else ei--; //if diff is same, smaller index element will be preferred
    }
    
    vector<int> ans(arr.begin() + si, arr.begin() + ei + 1);
    return ans;
    
}

//300
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> v;
    for(int i=0; i<n; ++i){
        int si=0, ei = v.size();
        while(si < ei){
            int mid = si + (ei - si)/2;
            if(v[mid] < nums[i]) si = mid + 1;
            else ei = mid;
        }
        if(si == v.size()){
            v.push_back(nums[i]);
        }
        else{
            v[si] = nums[i];
        }
    }
    return v.size();
}

//875
bool isPossibleToEat(vector<int>& piles, int eatingSpeed, int H){
    int n = piles.size(), hours = 0;
    for(int i=0; i<n; ++i){
        hours += piles[i] / eatingSpeed;
        if(piles[i] % eatingSpeed > 0)
            hours++;
        if(hours > H)
            return false;
    }
    return true;
}
int minEatingSpeed(vector<int>& piles, int H) {
    int n = piles.size();
    int minSpeed = 1, maxSpeed = 1e9;
    while(minSpeed < maxSpeed){
        int eatingSpeed = minSpeed + (maxSpeed - minSpeed)/2;
        
        if(isPossibleToEat(piles, eatingSpeed,H))
            maxSpeed = eatingSpeed;
        else
            minSpeed = eatingSpeed + 1;
    }
    
    return minSpeed;
}

//cakes and guests
bool isPossible(vector<double>& cakeArea, int guests, double mid ){
    int n = cakeArea.size(), count = 0;
    for(int i=0; i<n; ++i){
        count += cakeArea[i]/mid;
        if(count >= guests)
            return true;
    }
    return false;
}
double largestPiece(vector<double>& cakeArea, int guests) {
    
    double si = 0.0, ei = 100000000.0;
    
    while(ei - si > 0.0001){ //bcoz ans is required in 4 decimal places
        double mid = si + (ei - si)/2.0;
        
        if(isPossible(cakeArea, guests, mid))
            si = mid;
        else
            ei = mid;
    }
    return si;
}

//774 locked
bool isValid(vector<int>& station, int k, double mid){
    int n = station.size();
    int count = 0;
    for(int i=1; i<n; ++i){
        count += (station[i] - station[i-1]) / mid;
        if(count > k)
            return true;
    }
    return false;
}

double minimizeMaxDistance(vector<int>& station, int k){
    double si = 0.0, ei = 1e9, mid;
    while((ei - si) >= 1e-6){
        mid = si + (ei - si)/2.0;
        if(isValid(station,k,mid))
            si = mid;
        else
            ei = mid;
    } 
    cout << mid;
    return mid;
}

//33
int search(vector<int>& nums, int target) {
    int n = nums.size();
    int si=0, ei=n-1, mid;
    while(si <= ei){
        mid = (si+ei)/2;
        if(nums[mid] == target) 
            return mid;
        else if(nums[mid] >= nums[si]){
            if(target >= nums[si] && target < nums[mid])
                ei = mid - 1;
            else
                si = mid + 1;
        }
        else{
            if(target <= nums[ei] && target > nums[mid])
                si = mid + 1;
            else
                ei = mid - 1;
        }
    }
    return -1;
}

//81
bool search(vector<int>& nums, int target) {
    //worst case O(n) Avg case O(logN)
    int n = nums.size();
    int si=0, ei=n-1, mid;
    while(si <= ei){
        mid = (si+ei)/2;
        
        if(nums[mid] == target || nums[si] == target) 
            return true;
        
        else if(nums[mid] > nums[si]){
            if(target > nums[si] && target < nums[mid])
                ei = mid - 1;
            else
                si = mid + 1;
        }
        
        else if(nums[mid] < nums[ei]){
            if(target <= nums[ei] && target > nums[mid])
                si = mid + 1;
            else
                ei = mid - 1;
        }
        else{
            si++;
        }
    }
    return false;
}

//153
int findMin(vector<int>& nums) {
    int n = nums.size();
    int lo = 0, hi = n - 1, mid;
    while(lo < hi){
        mid = lo + (hi - lo)/2;
        if(nums[mid] > nums[hi]) lo = mid + 1;
        else hi = mid;
    }
    return nums[hi];
}

//1
vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    unordered_map<int,int> m;
    vector<int> ans;
    for(int i=0; i<n; ++i){
        if(m.find(target - nums[i]) != m.end()) return {i,m[target - nums[i]]};
        m[nums[i]] = i;
    }
    return {};
}

//167
vector<int> twoSum(vector<int>& numbers, int target) {
    int n = numbers.size();
    int si = 0, ei = n - 1;
    while(si < ei){
        if(numbers[si] + numbers[ei] == target)
            return {si+1, ei+1};
        else if(numbers[si] + numbers[ei] > target)
                ei--;
        else   
            si++;
    }
    return {};
}

//15
vector<vector<int>> threeSum(vector<int>& arr) {
    
    //T(N) = NLogN + N^2 i.e O(N) = N^2, space constant
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;
    
    for(int i=0; i<n; ++i){
        
        //removing duplicacy in i
        while(i != 0 && i<n && arr[i] == arr[i-1]) i++;
        
        int j = i+1, k = n-1;
        while(j < k){
            if(arr[i] + arr[j] + arr[k] == 0){
                ans.push_back({arr[i], arr[j], arr[k]});
                j++; k--;
                //removing duplicacy of j and k for a particular i
                while(j < k && arr[j] == arr[j-1]) j++;
                while(k > j && arr[k] == arr[k+1]) k--;
            } 
            else if(arr[i] + arr[j] + arr[k] > 0){
                k--;
            }
            else{
                j++;
            }
        }
    }
    return ans;
}

//18
vector<vector<int>> fourSum(vector<int>& arr, int target) {
    // nlogn + n^3 , space constant
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;
    
    for(int i=0; i<n; ++i){
        //removing i duplicacy
        while(i != 0 && i<n && arr[i] == arr[i-1]) i++;
        
        for(int j=i+1; j<n; ++j){
            
            //removing j duplicacy for a particular i
            while(j != i+1 && j < n && arr[j] == arr[j-1]) j++;
            int k = j + 1, l = n - 1;
            
            while(k < l){
                
                if(arr[i] + arr[j] + arr[k] + arr[l] == target){
                    ans.push_back({arr[i], arr[j], arr[k], arr[l]});
                    k++; l--;
                    //removing k and l duplicacy for a particular j and i
                    while(k < l && arr[k] == arr[k-1]) k++;
                    while(l > k && arr[l] == arr[l+1]) l--;  
                }
                else if(arr[i] + arr[j] + arr[k] + arr[l] < target){
                    k++;
                }
                else{
                    l--;
                }
                
            }
            
        }
    }
    return ans;
}

//454
//time n^2 logn , space n^2
int _4sumCount(vector<int>& ab, vector<int>& cd){
    int count = 0;
    sort(ab.begin(), ab.end());
    sort(cd.begin(), cd.end());
    int i = 0, j = cd.size() - 1;
    
    while(i < ab.size() && j > -1){
        if(ab[i] + cd[j] == 0){
            int countab = 1, countcd = 1;
            while(++i < ab.size() && ab[i] == ab[i-1]) countab++;
            while(--j > -1 && cd[j] == cd[j+1]) countcd++;
            count += countab * countcd;
        }
        else if(ab[i] + cd[j] > 0){
            j--;
            
        }
        else{
            i++;
        }
    }
    
    return count;
}
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    int n = A.size();
    vector<int> ab, cd;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            ab.push_back(A[i] + B[j]);
            cd.push_back(C[i] + D[j]);
        }
    }
    return _4sumCount(ab, cd);   
}

//240
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int r = matrix.size();
    int c = matrix[0].size();
    
    int i = 0, j = c - 1;
    while(i < r && j > -1){
        if(matrix[i][j] == target) return true;
        else if(matrix[i][j] < target) i++;
        else j--;
    }
    return false;
}

//4
double findMedianSortedArrays(vector<int>& arr1, vector<int>& arr2) {
    //https://www.youtube.com/watch?v=LPFhl65R7ww&t=444s best explanation
    //O(min(log(m,n))) , space constant
    int m = arr1.size();
    int n = arr2.size();
    if(m > n){
        return findMedianSortedArrays(arr2, arr1);
    }
    
    int si = 0, ei = m, mid;
    
    while(si <= ei){
        int partition1 = (si + ei)/2;
        int partition2 = (m + n +1)/2 - partition1;
        
        int maxLeft1 = (partition1 == 0) ? INT_MIN : arr1[partition1 - 1];
        int minRight1 = (partition1 == m) ? INT_MAX : arr1[partition1];
        
        int maxLeft2 = (partition2 == 0) ? INT_MIN : arr2[partition2 - 1];
        int minRight2 = (partition2 == n) ? INT_MAX : arr2[partition2];
        
        if(maxLeft1 <= minRight2 && maxLeft2 <= minRight1){
            //total elements are odd
            if((m + n) & 1){
                return max(maxLeft1, maxLeft2) * 1.0;
            }
            else{//even total elements
                return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
            }
        }
        else if(maxLeft1 > minRight2){
            ei = partition1 - 1;
        }
        else{ //maxLeft2 > minRight1
            si = partition1 + 1;
        }
    }
    
    //will never reach here
    return 0.0;
}

//134
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int extraGas = 0, deficit = 0, sp = 0;
    for(int i=0; i<gas.size(); ++i){
        extraGas += gas[i] - cost[i];
        if(extraGas < 0){
            sp = i+1;
            deficit += extraGas;
            extraGas = 0;
        }
    }
    
    // both are correct
    // return ((extraGas + deficit) >= 0 ) ? sp : -1;
    return (sp == gas.size() || extraGas + deficit < 0) ? -1 : sp;
}