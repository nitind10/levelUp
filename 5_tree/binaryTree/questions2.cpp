//Bread-First-Search
//level order type questions

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

  //level order prints =======================================================================
  //1: simple
void levelOrder1(TreeNode* node){
    queue<TreeNode*> q;
    q.push(node);
    
    while(!q.empty()){
        TreeNode* rn = q.front();  //rn : removed node
        cout << rn -> val << " ";
        q.pop();
        
        if(rn -> left != nullptr) q.push(rn -> left);
        if(rn -> right != nullptr) q.push(rn -> right);
    }
    cout << endl;
}

//2: using 2 queues, orignal queue and child queue
void levelOrder2(TreeNode* node){
    queue<TreeNode*> q, cq;
    q.push(node);
    int level = 0;
    cout << "Level " << level << ": ";
    
    while(!q.empty()){
        TreeNode *rn = q.front();
        cout << rn -> val << " ";
        q.pop();
        
        if(rn -> left != nullptr) cq.push(rn -> left);
        if(rn -> right != nullptr) cq.push(rn -> right);
        
        if(q.empty()){
            if(!cq.empty())
                cout << "\nLevel " << ++level << ": ";
            swap(q, cq);
        }
    }
}

//3: using delimiter
void levelOrder3(TreeNode* node){
    queue<TreeNode*> q;
    q.push(node);
    q.push(nullptr);
    
    int level = 0;
    cout << "Level " << level << ": ";
    
    while(q.size() != 1){
        TreeNode *rn = q.front();
        cout << rn -> val << " ";
        q.pop();
        
        if(rn -> left != nullptr) q.push(rn -> left);
        if(rn -> right != nullptr) q.push(rn -> right);
        
        if(q.front() == nullptr && q.size() != 1){
            cout << "\nLevel " << ++level << ": ";
            q.pop();
            q.push(nullptr);
        }  
    }
}

//4: 
void levelOrder4(TreeNode* node){
    queue<TreeNode*> q;
    q.push(node);
    
    int level = 0;
    cout << "Level " << level << ": ";
    
    while(!q.empty()){
        int size_ = q.size();
        
        while(size_--){
            TreeNode *rn = q.front();
            cout << rn -> val << " ";
            q.pop();
            
            if(rn -> left != nullptr) q.push(rn -> left);
            if(rn -> right != nullptr) q.push(rn -> right);
        }
        if(!q.empty())
            cout << "\nLevel " << ++level << ": "; 
    }
}

//102 ===============================================================================
vector<vector<int>> findLevels(TreeNode* root){
    vector<vector<int>> ans;
    int level = 0;
    queue<TreeNode*> q;
    q.push(root);
    
    while(!q.empty()){
        int size_ = q.size();
        
        while(size_--){
            TreeNode *rn = q.front();
            q.pop();
            if(level == ans.size())
                ans.push_back({});
            ans.back().push_back(rn -> val);
            
            if(rn -> left != nullptr) q.push(rn -> left);
            if(rn -> right != nullptr) q.push(rn -> right);
        }
        level++;
    }
    
    return ans;
}

//199 =====================================================================================
vector<int> rightSideView(TreeNode* root) {
    if(root == nullptr) return {};
    vector<int> ans;

    queue<TreeNode*> q;
    q.push(root);
    
    while(!q.empty()){
        int size_ = q.size();
        ans.push_back(q.front() -> val);
        
        while(size_--){
            TreeNode *rn = q.front();
            q.pop();
            
            if(rn -> right != nullptr) q.push(rn -> right);
            if(rn -> left != nullptr) q.push(rn -> left);
        }
    }
    return ans;
}

//vertical level of tree ==============================================================================
void verticalLevelTraversal(TreeNode* root){
            //node, its width idx
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    
                //width idx, all nodes' vals with that width idx: level wise
    unordered_map<int, vector<int>> map;
    
    int minWidthIdx = 1e9, maxWidthIdx = -1e9;
    
    while(!q.empty()){
        pair<TreeNode*, int> rp = q.front();
        q.pop();
        
        map[rp.second].push_back(rp.first -> val);
        
        minWidthIdx = min(minWidthIdx, rp.second);
        maxWidthIdx = max(maxWidthIdx, rp.second);
        
        if(rp.first -> left != nullptr) 
            q.push({rp.first -> left, rp.second - 1});
        if(rp.first -> right != nullptr) 
            q.push({rp.first -> right, rp.second + 1});
    }
    
    vector<vector<int>> res;
    
    while(minWidthIdx <= maxWidthIdx)
        res.push_back(map[minWidthIdx++]);
}

//width of tree ==============================================================
void width(TreeNode* root, int widthIdx, pair<int,int> &minMax){
    if(root == nullptr)
        return;
    
    minMax.first = min(minMax.first, widthIdx);
    minMax.second = max(minMax.second, widthIdx);
    
    width(root -> left, widthIdx - 1, minMax);
    width(root -> right, widthIdx + 1, minMax);
}

//vertical sum ======================================================================
void width(TreeNode* root, int widthIdx, pair<int,int> &minMax){
    if(root == nullptr)
        return;

    minMax.first = min(minMax.first, widthIdx);
    minMax.second = max(minMax.second, widthIdx);

    width(root -> left, widthIdx - 1, minMax);
    width(root -> right, widthIdx + 1, minMax);
}
vector<int> verticalSum(TreeNode* root){   
    pair<int,int> minMax = {1e9, -1e9};
    width(root, 0, minMax);
    int wid = minMax.second - minMax.first + 1;
    vector<int> res(wid); 
        
            //node, its width idx
    queue<pair<TreeNode*, int>> q;
    q.push({root, -minMax.first});

    while(!q.empty()){
        pair<TreeNode*, int> rp = q.front();
        q.pop();
        
        res[rp.second] += rp.first -> val;
        
        if(rp.first -> left != nullptr) 
            q.push({rp.first -> left, rp.second - 1});
        if(rp.first -> right != nullptr) 
            q.push({rp.first -> right, rp.second + 1});
    }
    return res;
}

//bottom view ==============================================================
void width(TreeNode* root, int widthIdx, pair<int,int> &minMax){
    if(root == nullptr)
        return;

    minMax.first = min(minMax.first, widthIdx);
    minMax.second = max(minMax.second, widthIdx);

    width(root -> left, widthIdx - 1, minMax);
    width(root -> right, widthIdx + 1, minMax);
}
vector<int> bottomView(TreeNode* root){   
    pair<int,int> minMax = {1e9, -1e9};
    width(root, 0, minMax);
    int wid = minMax.second - minMax.first + 1;
    vector<int> res(wid); 
        
            //node, its width idx
    queue<pair<TreeNode*, int>> q;
    q.push({root, -minMax.first});

    while(!q.empty()){
        pair<TreeNode*, int> rp = q.front();
        q.pop();
        
        res[rp.second] = rp.first -> val;
        
        if(rp.first -> left != nullptr) 
            q.push({rp.first -> left, rp.second - 1});
        if(rp.first -> right != nullptr) 
            q.push({rp.first -> right, rp.second + 1});
    }
    return res;
}

//top view ===================================================================
void width(TreeNode* root, int widthIdx, pair<int,int> &minMax){
    if(root == nullptr)
        return;

    minMax.first = min(minMax.first, widthIdx);
    minMax.second = max(minMax.second, widthIdx);

    width(root -> left, widthIdx - 1, minMax);
    width(root -> right, widthIdx + 1, minMax);
}
vector<int> topView(TreeNode* root){   
    pair<int,int> minMax = {1e9, -1e9};
    width(root, 0, minMax);
    int wid = minMax.second - minMax.first + 1;
    vector<int> res(wid, -1e9); 
        
            //node, its width idx
    queue<pair<TreeNode*, int>> q;
    q.push({root, -minMax.first});

    while(!q.empty()){
        pair<TreeNode*, int> rp = q.front();
        q.pop();
        
        //if -1e9 is in range for node val, keep some bool visited etc
        if(res[rp.second] == -1e9)
            res[rp.second] = rp.first -> val;
        
        if(rp.first -> left != nullptr) 
            q.push({rp.first -> left, rp.second - 1});
        if(rp.first -> right != nullptr) 
            q.push({rp.first -> right, rp.second + 1});
    }
    return res;
}

//diagonal traversal ===================================================================================
void diagonalTraversal(TreeNode* root){
            //node, its width idx
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    
                //width idx, all nodes' vals with that width idx: level wise
    unordered_map<int, vector<int>> map;
    
    int minWidthIdx = 1e9, maxWidthIdx = -1e9;
    
    while(!q.empty()){
        pair<TreeNode*, int> rp = q.front();
        q.pop();
        
        map[rp.second].push_back(rp.first -> val);
        
        minWidthIdx = min(minWidthIdx, rp.second);
        maxWidthIdx = max(maxWidthIdx, rp.second);
        
        if(rp.first -> left != nullptr) 
            q.push({rp.first -> left, rp.second - 1});
        if(rp.first -> right != nullptr) 
            q.push({rp.first -> right, rp.second});
    }
    
    vector<vector<int>> res;
    
    while(minWidthIdx <= maxWidthIdx)
        res.push_back(map[minWidthIdx++]);
}

//987 ====================================================================================
void levelWiseSort(vector<pair<int,int>>& v){
    int prev = 0, curr = 1;
    while(curr < v.size()){
        if(v[curr].second != v[prev].second){
            sort(v.begin() + prev, v.begin() + curr);
            prev = curr;
        }
        curr++;
    }
    if(prev != v.size() - 1)
        sort(v.begin() + prev, v.begin() + curr); 
}

vector<vector<int>> verticalLevelTraversal(TreeNode* root){
            //node, its width idx
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});

                //width idx, node's val and its level
    unordered_map<int, vector<pair<int,int>>> map;

    int minWidthIdx = 1e9, maxWidthIdx = -1e9;
    int level = 0;

    while(!q.empty()){
        int size_ = q.size();
        while(size_--){
            pair<TreeNode*, int> rp = q.front();
            q.pop();

            map[rp.second].push_back({rp.first -> val, level});

            minWidthIdx = min(minWidthIdx, rp.second);
            maxWidthIdx = max(maxWidthIdx, rp.second);

            if(rp.first -> left != nullptr) 
                q.push({rp.first -> left, rp.second - 1});
            if(rp.first -> right != nullptr) 
                q.push({rp.first -> right, rp.second + 1});
            }
        level++;
    }

    vector<vector<pair<int,int>>> res;
        
    while(minWidthIdx <= maxWidthIdx)
        res.push_back(map[minWidthIdx++]);
        
    //doing level wise sorting
    for(int i = 0; i < res.size(); ++i){
        levelWiseSort(res[i]);
    }
        
    //creating final answer
    vector<vector<int>> ans(res.size());
    for(int i = 0; i < res.size(); ++i){
        for(auto x : res[i])
            ans[i].push_back(x.first);
    }
        
    return ans;
}
vector<vector<int>> verticalTraversal(TreeNode* root) {
    return verticalLevelTraversal(root);
}


