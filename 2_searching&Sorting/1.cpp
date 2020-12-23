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