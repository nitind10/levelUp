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