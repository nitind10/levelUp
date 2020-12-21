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


