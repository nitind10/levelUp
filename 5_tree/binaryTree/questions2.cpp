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

//top view of tree ==============================================================================
void topView(TreeNode* root){
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


