#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<stack>
using namespace std;

//215 =============================================================
//can optime by making own heap
 //nlogk
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq; // min
        for (int ele : nums){
            pq.push(ele);
            if (pq.size() > k)
                pq.pop();
        }

        return pq.top();
    }

//703 =============================================================
//cant make own heap as data is not static
class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;
    KthLargest(int k, vector<int>& nums) {
        this -> k = k;
        for(int ele : nums){
            this->pq.push(ele);
            
            if(this->pq.size() > this -> k)
                this->pq.pop();
        }
    }
    int add(int val) {
        this->pq.push(val);
        if(this->pq.size() > this -> k)
            this->pq.pop();
        
        return this->pq.top();
    }
};

//349============================================================================
//unordeder_set : only keeps distinct keys, insert,search,delete -> on average o(1)
    //ordered set i.e only set : keeps keys in increasing order, self balancing bst, o(logn)
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set;
        
        for(int ele : nums1)
            set.insert(ele);
        
        vector<int> ans;
        
        for(int ele : nums2){
            if(set.find(ele) != set.end()){
                ans.push_back(ele);
                set.erase(ele);
            }
        }
        
        return ans;
    }

//350==================================================================================
 vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
         unordered_map<int,int> map;
        
        for(int ele : nums1)
            map[ele]++;
        
        vector<int> ans;
        
        for(int ele : nums2){
            if(map.find(ele) != map.end()){
                ans.push_back(ele);
                map[ele]--;
                
                if(map[ele] == 0)
                    map.erase(ele);
            }
        }
        
        return ans;
    }

//128==============================================================================
//as the number of things in unordered map/set increses, the complexity worsens
    //therefore for hashmap to perform better, remove unnecessary elements
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> set;
        
        for(int ele : nums)
            set.insert(ele);
        
        int len = 0;
        for(int ele : nums){
            if(set.find(ele) != set.end()){
                int ple = ele - 1; //potential right element
                int pre = ele + 1; //potential left element
                
                while(set.find(ple) != set.end())
                    set.erase(ple--);
                while(set.find(pre) != set.end())
                    set.erase(pre++);
                
                len = max(len, pre-ple-1);
            }
        }
        
        return len;
    }

//347 =========================================================================
 vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> map;
        
        for(int ele : nums) //n
            map[ele]++;
        
        //by default a comparator is written on 0th idx of vector and first element of a pair
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        
        for(pair<int,int> key : map){ //nlogk
            int val = key.first;
            int freq = key.second;
            
            pq.push({freq,val});
            
            if(pq.size() > k)
                pq.pop();
        }
        
        vector<int> ans;
        
        while(pq.size() != 0){ //klogk
            vector<int> rv = pq.top();
            pq.pop();
            
            int freq = rv[0];
            int val = rv[1];
            
            ans.push_back(val);
        }
        
        return ans;
    }

//973==========================================================================
//imp***********
//gave functionality to pq based on distance(int), avoid comapring floating ponits
//
class comparator{
      public:
        bool operator()(const vector<int>& a, const vector<int>& b) const{
            int d1Square = a[0]*a[0] + a[1]*a[1];
            int d2Square = b[0]*b[0] + b[1]*b[1];
            
            //maxPQ {other > this}
            return d2Square > d1Square;
        }
    };
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        //{x, y}
        priority_queue<vector<int>, vector<vector<int>>, comparator> pq;
        
        for(vector<int>& v : points){
            pq.push(v);
            if(pq.size() > k)
                pq.pop();
        }
        
        vector<vector<int>> ans;
        
        while(pq.size() != 0){
            vector<int> rv = pq.top();
            pq.pop();
            ans.push_back(rv);
        }
        
        return ans;
    }

//alternate approach
vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
{
    //{d,x,y}
    priority_queue<vector<int>> pq; // maxPQ

    for (vector<int> &p : points)
    {
        int x = p[0];
        int y = p[1];
        pq.push({x * x + y * y, x, y});
        if (pq.size() > k)
            pq.pop();
    }

    vector<vector<int>> ans;
    while (pq.size() != 0)
    {
        vector<int> p = pq.top();
        pq.pop();
        int x = p[1];
        int y = p[2];

        ans.push_back({x, y});
    }

    return ans;
}

//378============================================================================================
int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(), m = matrix[0].size();
        //{val,x,y};
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

        for (int i = 0; i < n; i++)
        {
            pq.push({matrix[i][0], i, 0});
        }

        int ans = 0;
        while (k-- > 0)
        {
            vector<int> rv = pq.top();
            pq.pop();
            int val = rv[0];
            int x = rv[1];
            int y = rv[2];

            ans = val;
            y++;
            if (y < m)
                pq.push({matrix[x][y], x, y});
        }

        return ans;
    }

//380=========================================================================================
class RandomizedSet
{
public:
    unordered_map<int, int> map;
    vector<int> list;

    RandomizedSet()
    {
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        if (map.find(val) != map.end())
            return false;

        list.push_back(val);
        map[val] = list.size() - 1;

        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        if (map.find(val) == map.end())
            return false;

        int idx = map[val];
        int lidx = list.size() - 1;

        list[idx] = list[lidx];
        map[list[lidx]] = idx;

        list.pop_back();
        map.erase(val);

        return true;
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        int idx = rand() % list.size();
        return list[idx];
    }
};

//895========================================================================================================================
class FreqStack {
        // val , freq
        unordered_map<int,int> freq;
        vector<stack<int>> freqMap;
        int maxFreq;
    public:
        FreqStack() {
            this -> maxFreq = 0;
            stack<int> st;
            this -> freqMap.push_back(st); //dummy
        }

        void push(int val) { // O(1)
            freq[val]++;
            maxFreq = max(maxFreq, freq[val]);
            
            if(freq[val] == freqMap.size()){
                stack<int> st;
                freqMap.push_back(st);
            }
            freqMap[freq[val]].push(val);
        }

        int pop() { // O(1)
            int rv = freqMap[maxFreq].top();
            freqMap[maxFreq].pop();
            if (freqMap[maxFreq].size() == 0){
                freqMap.pop_back();
                maxFreq--;
            }
                
            freq[rv]--;
            if (freq[rv] == 0)
                freq.erase(rv);

            return rv;
        }
    };

//approach2 using pq
//priority queue approach, not a good complexity 
class FreqStack
{
private:
    class pair
    {
    public:
        int val = 0;
        int freq = 0;
        int idx = 0;

        pair(int val, int freq, int idx)
        {
            this->val = val;
            this->freq = freq;
            this->idx = idx;
        }
    };

    class comp
    {
    public:
        bool operator()(const pair &a, const pair &b) const
        {
            if (a.freq == b.freq)
                return b.idx > a.idx;
            return b.freq > a.freq;
        }
    };

    unordered_map<int, int> freqMap;
    priority_queue<pair, vector<pair>, comp> pq;
    int idx = 0;

public:
    FreqStack()
    {
    }

    void push(int val)
    { // Log(n)
        freqMap[val]++;
        pq.push(pair(val, freqMap[val], idx++));
    }

    int pop()
    { // Log(n)
        pair p = pq.top();
        pq.pop();
        freqMap[p.val]--;
        if (freqMap[p.val] == 0)
            freqMap.erase(p.val);

        return p.val;
    }
};


//407 ================================================================================================
int trapRainWater(vector<vector<int>> &heightMap)
{
    int n = heightMap.size(), m = heightMap[0].size();
    //{height, i,j}
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
            {
                vis[i][j] = true;
                pq.push({heightMap[i][j], i, j});
            }
        }
    }

    vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int minBoun = 0, water = 0;

    while (pq.size() != 0)
    {
        vector<int> rp = pq.top();
        pq.pop();
        int height = rp[0];
        int i = rp[1], j = rp[2];

        minBoun = max(minBoun, height);
        water += minBoun - height;

        for (int d = 0; d < 4; d++)
        {
            int r = i + dir[d][0];
            int c = j + dir[d][1];

            if (r >= 0 && c >= 0 && r < n && c < m && !vis[r][c])
            {
                vis[r][c] = true;
                pq.push({heightMap[r][c], r, c});
            }
        }
    }
    return water;
}

//778 =======================================================================================
 int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size(), m = n;

        //{elevation, x, y}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

        vector<vector<int>> dir = { {1,0}, {-1,0}, {0,1}, {0,-1} };
        
        //no need of visited, i can mark by putting elevation as -1, and i already stored elevation in pq

        pq.push({grid[0][0], 0, 0});
        grid[0][0] = -1;

        int minHeight = 0, time = 0;

        while (pq.size() != 0) {
            vector<int> rv = pq.top();
            pq.pop();
            int i = rv[1];
            int j = rv[2];
            int height = rv[0];

            time += max(0, height - minHeight);
            if (i == n-1 && j == m-1)
                break;

            minHeight = max(minHeight, height);

            for (int d = 0; d < dir.size(); d++) {
                int r = i + dir[d][0];
                int c = j + dir[d][1];

                if (r >= 0 && c >= 0 && r < n && c < m && grid[r][c] != -1) {
                    pq.push({grid[r][c], r, c});
                    grid[r][c] = -1;
                }
            }
        }
    
        //can also return minHeight, as it'll be the same as time
        return time;
    }


//295 ============================================================================================
class MedianFinder{
    private:
        priority_queue<int> maxPQ;
        priority_queue<int, vector<int>, greater<int>> minPQ;

    public:
        /** initialize your data structure here. */
        MedianFinder() {

        }

        void addNum(int num) {
            if (maxPQ.size() == 0 || num <= maxPQ.top())
                maxPQ.push(num);
            else
                minPQ.push(num);

            if (maxPQ.size() - minPQ.size() == 2){
                minPQ.push(maxPQ.top());
                maxPQ.pop();
            }   
            
            if (maxPQ.size() - minPQ.size() == -1){
                maxPQ.push(minPQ.top());
                minPQ.pop();
            } 
        }

        double findMedian(){
            if (maxPQ.size() == minPQ.size())
                return ((maxPQ.top() + minPQ.top()) / 2.0);
            else
                return maxPQ.top() * 1.0;
        }
};


//502 do Yourself

//023 ============================================================================================
 //(NK)Log(K) using heap
    class comp
    {
    public:
        bool operator()(const ListNode *a, const ListNode *b) const
        {
            return a->val > b->val;
        }
    };
    ListNode *mergeKLists(vector<ListNode *> lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, comp> pq;

        for (int i = 0; i < lists.size(); i++)
            if (lists[i] != nullptr)
                pq.push(lists[i]);

        ListNode *dummy = new ListNode(-1);
        ListNode *prev = dummy;

        while (pq.size() != 0)
        {
            ListNode *rn = pq.top();
            pq.pop();
            prev->next = rn;
            prev = prev->next;

            if (rn->next != nullptr)
                pq.push(rn->next);
        }
        return dummy->next;
    }

//632 ============================================================================================
//N.M.Log(N)
    vector<int> smallestRange(vector<vector<int>>& nums){     
        int n = nums.size();

        // {val,r,c}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

        int maxValue = -1e9;
        for(int i=0; i<n; i++){
            pq.push({nums[i][0],i,0});
            maxValue = max(maxValue,nums[i][0]);
        }
    
        int range = 1e9;
        int sp = -1, ep = -1;

        while(pq.size() == n){
            vector<int> re = pq.top(); // re : removed Element
            pq.pop();
            int val = re[0], r = re[1], c = re[2];

            if(maxValue - val < range){
                range = maxValue - val;
                sp = val;
                ep = maxValue;
            }

            c++;
            
            if(c < nums[r].size()){
                pq.push({nums[r][c],r,c});
                maxValue = max(maxValue,nums[r][c]);
            }            
        }

        return {sp,ep};
    }